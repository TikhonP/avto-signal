// Для кнопок
#include "GyverButton.h"

#define BUT1_PIN 7
#define BUT2_PIN 6
#define BUT3_PIN 5

GButton butt1(BUT1_PIN);
GButton butt2(BUT2_PIN);
GButton butt3(BUT3_PIN);


// для плеера
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define SS_RX 3
#define SS_TX 2


#define directory_buttons_1 50 // Папка с мелодиями кнопок
#define directory_buttons_2 51
#define directory_buttons_3 52

int track_count = 1; // количесто треков в каждой папке
int volume = 15; // Гормкость 0-30

SoftwareSerial playerSerial(SS_RX, SS_TX);  // RX, TX
DFRobotDFPlayerMini myDFPlayer;


// Для часов
#include <DS1302.h>

Time currenttime(2013, 9, 22, 1, 38, 50, Time::kSunday); // Текущее время, если настройка
#define isSetTime false // Если нужна настройка времени

Time switch_vol_1(2013, 21, 00, 1, 38, 50, Time::kSunday); // Время переключения громкости 1
Time switch_vol_2(2013, 8, 00, 1, 38, 50, Time::kSunday); // Время переключения громкости 2

namespace {
const int kCePin   = 8;  // Chip Enable
const int kIoPin   = 9;  // Input/Output
const int kSclkPin = 10;  // Serial Clock

DS1302 rtc(kCePin, kIoPin, kSclkPin);
}

// Для входа сигнализации
#define ALARM_PIN 4 // Пин подключения сигналов после оптореле
#define DELAY_SIGNALS 500 // Задержка между сигналами в миллисекундах
GButton alrm(ALARM_PIN);

unsigned long nowTime; // Последнее время срабатывания сигнала
int signals;


void sound(int signls) {
        myDFPlayer.pause();
        delay(50);
        track_count = myDFPlayer.readFileCountsInFolder(signls);
        delay(50);
        myDFPlayer.playFolder(signls, random(track_count));
        delay(50);
        Serial.print("PLAY track > ");
        Serial.print(random(track_count));
        Serial.print("  folder > ");
        Serial.println(signls);
        // delay(2000);
}


void setup() {
        Serial.begin(9600); // Вывод
        Serial.println("Out 9600");


        alrm.setTickMode(MANUAL);
        butt1.setTickMode(MANUAL);
        butt2.setTickMode(MANUAL);
        butt3.setTickMode(MANUAL);


        playerSerial.begin(9600);
        Serial.println("playerSerial begin");

        /*
           Часы
           if (isSetTime) {
                Serial.println("setting time");
                rtc.writeProtect(false);
                rtc.halt(false);
                rtc.time(currenttime);
           }
           else {
                Serial.println("skipping setting time");
                rtc.writeProtect(true);
           }
         */

        // Подключение плеера
        delay(500);
        if (!myDFPlayer.begin(playerSerial)) { // запуск плеера//инициализац//более 2 секунд
                Serial.println(F("Ошибка подключения плеера:"));
        }

        Serial.println("Setting player");
        myDFPlayer.setTimeOut(500);
        myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
        myDFPlayer.volume(volume);         //громкость (0~30).
        myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
        myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
        delay(200);         // даем немного времени,ждем начало проигрывания
        Serial.println("Playing...");
        sound(0);
        delay(5000);
}

void loop() {
        if (myDFPlayer.available()) {
                printDetail(myDFPlayer.readType(), myDFPlayer.read()); //Print the detail message from DFPlayer to handle different errors and states.
        }
        // Проверка входа сигнализации
        alrm.tick();
        if (alrm.isHold()) {
                myDFPlayer.enableLoop();
                delay(50);
                myDFPlayer.pause();
                delay(50);
                track_count = myDFPlayer.readFileCountsInFolder(0);
                delay(50);
                myDFPlayer.playFolder(0, random(track_count));
                delay(50);
                Serial.print("PLAY track > ");
                Serial.print(random(track_count));
                Serial.print("  folder > ");
                Serial.println(0);
                while (alrm.isHold()) {
                        alrm.tick();
                        Serial.println("Тревога");
                        delay(500);
                }
                myDFPlayer.pause();
                delay(50);
                myDFPlayer.disableLoop();
        }
        else if (alrm.hasClicks()) {
                signals = alrm.getClicks();
                sound(signals);
        }


        /*
           // Проверка времени
           Time t = rtc.time();
           if ((t.hr==switch_vol_1.hr) & (t.min==switch_vol_1.min)) {
                volume = 15;
           }
           else if ((t.hr==switch_vol_2.hr) & (t.min==switch_vol_2.min)) {
                volume = 30;
           }
         */

        // Проверка кнопки
        butt1.tick();
        if (butt1.isSingle()) {
                if (myDFPlayer.readState()) {
                        myDFPlayer.pause();
                        Serial.println("Paused");
                } else {
                        sound(directory_buttons_1);

                }
        }
        butt2.tick();
        if (butt2.isSingle()) {
                if (myDFPlayer.readState()) {
                        myDFPlayer.pause();
                        Serial.println("Paused");
                } else {
                        sound(directory_buttons_2);

                }
        }
        butt3.tick();
        if (butt2.isSingle()) {
                if (myDFPlayer.readState()) {
                        myDFPlayer.pause();
                        Serial.println("Paused");
                } else {
                        sound(directory_buttons_2);

                }
        }
}




void printDetail(uint8_t type, int value){
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
                Serial.print(F("Number:"));
                Serial.print(value);
                Serial.println(F(" Play Finished!"));
                break;
        case DFPlayerError:
                Serial.print(F("DFPlayerError:"));
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
