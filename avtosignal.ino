// Copyright (c) 2020
// Sketch for playing song for car alarm system
//
// Main sketch

#include <GyverButton.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <iarduino_RTC.h>
#include "avtosignal.h"


// Для кнопок
GButton butt1(BUT1_PIN);
GButton butt2(BUT2_PIN);
GButton butt3(BUT3_PIN);
// Для входа сигнализации
GButton alrm(ALARM_PIN);


// для плеера
SoftwareSerial playerSerial(SS_RX, SS_TX);
DFRobotDFPlayerMini myDFPlayer;

unsigned long lastplaytime;
boolean playingstate;
int max_volume = 0;


// Для часов
iarduino_RTC clock (RTC_DS1302, RST, CLK, DAT);


void checkerr();
void sound(int folder, int track_count=-1);
void turnOnApm();
void turnOffApm();

unsigned long nowTime;

bool turnedoffapm = false;

void setup() {
        Serial.begin(9600); // Вывод
        Serial.println("Loading...\nStarting serial output 9600");

        turnOffApm();

        alrm.setTickMode(MANUAL);
        butt1.setTickMode(MANUAL);
        butt2.setTickMode(MANUAL);
        butt3.setTickMode(MANUAL);


        // random
        unsigned long seed = 0;
        for (int i = 0; i < 16; i++) {
                seed *= 4;
                seed += analogRead(randompin) & 3;
        }
        randomSeed(seed);


        playerSerial.begin(9600);
        Serial.println("Staring playerSerial 9600...");

        // Часы
        clock.begin();
        #ifdef SetTime
        Serial.println("Setting time");
        clock.settime(
                set_second, set_minute, set_hour, set_day,
                set_month, set_year, set_week_day);
        #else
        Serial.println("Skipping setting time");
        #endif


        // Подключение плеера
        pinMode(amp_power_pin, OUTPUT);
        pinMode(dinamic_pin, OUTPUT);
        pinMode(BUSY_PIN, INPUT);
        delay(200);
        if (!myDFPlayer.begin(playerSerial)) {
                Serial.println(F("Unable to connect pleer!"));
        } else {
                Serial.println("Setting player");
                myDFPlayer.setTimeOut(500);
                myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
                myDFPlayer.volume(volume); // громкость (0~30).
                myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
                myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
        }
}


void loop() {
        checkerr();
        nowTime = millis();
        if (nowTime%1000==0) {
                playingstate = digitalRead(BUSY_PIN);
                if (playingstate == LOW) {
                        lastplaytime = nowTime;
                } else {
                        if ((lastplaytime+turn_off_delay)<nowTime)
                                turnOffApm();
                        if (max_volume!=0) {
                                volume = max_volume;
                                max_volume = 0;
                        }
                }
        }

        // Проверка входа сигнализации
        alrm.tick();
        if (alrm.isHold()) {
                sound(11);
                Serial.println("Тревога");
                delay(pleerdelay);
                alrm.tick();
                while (alrm.isHold()) {
                        delay(500);
                        Serial.println("Тревога2");
                        playingstate = digitalRead(BUSY_PIN);
                        if (playingstate == HIGH)
                                sound(11);
                        alrm.tick();
                }
                delay(pleerdelay);
                myDFPlayer.pause();
                lastplaytime = nowTime;
        }
        if (alrm.hasClicks()) {
                int signals = alrm.getClicks();
                sound(signals);
        }


        // Проверка времени
        if (nowTime%60000==0) {
                int h = clock.Hours;
                int m = clock.minutes;
                if ((h==switch_vol_1_hour) && (m==switch_vol_1_minute))
                        volume = volume1;
                else if ((h==switch_vol_2_hour) && (m==switch_vol_2_minute))
                        volume = volume2;
                if ((h==play_1_hour) && (m==play_1_minute))
                        sound(time_play_folder_1);
                else if ((h==play_2_hour) && (m==play_2_minute))
                        sound(time_play_folder_2);
                Serial.print(clock.gettime("d-m-Y, H:i:s, D"));
        }

        // Проверка кнопок
        butt1.tick();
        if (butt1.isSingle()) {
                myDFPlayer.pause();
                delay(pleerdelay);
                sound(directory_buttons_1, 1);
        }
        else if (butt1.isHold()) {
                myDFPlayer.pause();
                delay(pleerdelay);
                sound(directory_buttons_1, 2);
                butt1.tick();
                while (butt1.isHold()) {
                        butt1.tick();
                        delay(pleerdelay);
                }
                myDFPlayer.pause();
        }
        butt2.tick();
        if (butt2.isSingle()) {
                myDFPlayer.pause();
                delay(pleerdelay);
                sound(directory_buttons_2, 1);
        }
        else if (butt2.isHold()) {
                myDFPlayer.pause();
                delay(pleerdelay);
                sound(directory_buttons_2, 2);
                butt2.tick();
                while (butt2.isHold()) {
                        butt2.tick();
                        delay(pleerdelay);
                }
                myDFPlayer.pause();
        }
        butt3.tick();
        if (butt3.isSingle()) {
                myDFPlayer.pause();
                delay(pleerdelay);
                sound(directory_buttons_3, 1);
        }
        else if (butt3.isHold()) {
                myDFPlayer.pause();
                delay(pleerdelay);
                sound(directory_buttons_3, 2);
                butt3.tick();
                while (butt3.isHold()) {
                        butt3.tick();
                        delay(pleerdelay);
                }
                myDFPlayer.pause();
        }
}


void sound(int folder, int track_count=-1) {
        if (folder==max_volume_folder) {
                max_volume = volume;
                volume = 30;
        }
        turnOnApm();
        delay(pleerdelay);
        myDFPlayer.pause();
        delay(pleerdelay);
        if (track_count==-1) {
                track_count = myDFPlayer.readFileCountsInFolder(folder);
                track_count = random(track_count)+1;
                delay(pleerdelay);
        }
        myDFPlayer.playFolder(folder, track_count);
        delay(pleerdelay);
        Serial.print("PLAY track > ");
        Serial.print(track_count);
        Serial.print("  folder > ");
        Serial.println(folder);
        delay(pleerdelay);
        playingstate = digitalRead(BUSY_PIN);
        if (playingstate == HIGH) {
                Serial.print("PAY ATTENTION ERROR WITH ");
                Serial.print(track_count);
                Serial.print(" TRACK, IN ");
                Serial.print(folder);
                Serial.print(" FOLDER!!!");
        }
        lastplaytime = nowTime;
}


void turnOnApm() {
        digitalWrite(amp_power_pin, LOW);
        delay(dinamic_turn_on_delay);
        digitalWrite(dinamic_pin, LOW);
        turnedoffapm = false;
}


void turnOffApm() {
        if (!turnedoffapm) {
                digitalWrite(dinamic_pin, HIGH);
                delay(dinamic_turn_on_delay);
                digitalWrite(amp_power_pin, HIGH);
                turnedoffapm = true;
        }
}


void checkerr(){
        if (myDFPlayer.available()) {
                uint8_t type = myDFPlayer.readType();
                int value = myDFPlayer.read();
                Serial.print("Pleer info: ");
                switch (type) {
                case TimeOut:
                        Serial.println(F("Time Out!"));
                        break;
                case WrongStack:
                        Serial.println(F("Stack Wrong!"));
                        break;
                case DFPlayerCardInserted:
                        Serial.println(F("Card Inserted!"));
                        break;
                case DFPlayerCardRemoved:
                        Serial.println(F("Card Removed!"));
                        break;
                case DFPlayerCardOnline:
                        Serial.println(F("Card Online!"));
                        break;
                case DFPlayerUSBInserted:
                        Serial.println("USB Inserted!");
                        break;
                case DFPlayerUSBRemoved:
                        Serial.println("USB Removed!");
                        break;
                case DFPlayerPlayFinished:
                        Serial.print(F("Number: "));
                        Serial.print(value);
                        Serial.println(F(" Play Finished!"));
                        break;
                case DFPlayerError:
                        Serial.print(F("Pleer ERROR: "));
                        switch (value) {
                        case Busy:
                                Serial.println(F("Card not found"));
                                break;
                        case Sleeping:
                                Serial.println(F("Sleeping"));
                                break;
                        case SerialWrongStack:
                                Serial.println(F("Get Wrong Stack"));
                                break;
                        case CheckSumNotMatch:
                                Serial.println(F("Check Sum Not Match"));
                                break;
                        case FileIndexOut:
                                Serial.println(F("File Index Out of Bound"));
                                break;
                        case FileMismatch:
                                Serial.println(F("Cannot Find File"));
                                break;
                        case Advertise:
                                Serial.println(F("In Advertise"));
                                break;
                        default:
                                break;
                        }
                        break;
                default:
                        break;
                }
        }

}
