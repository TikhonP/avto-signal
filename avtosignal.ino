// Для кнопок
#include "GyverButton.h"

#define BUT1_PIN A1
#define BUT2_PIN A2
#define BUT3_PIN A3

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
#define ALARM_PIN 5 // Пин подключения сигналов после оптореле
#define DELAY_SIGNALS 500 // Задержка между сигналами в миллисекундах
GButton alrm(ALARM_PIN);

unsigned long nowTime; // Последнее время срабатывания сигнала
int signals;


void setup() {
        Serial.begin(9600); // Вывод
        Serial.println("Out 9600");

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
        int track_count = myDFPlayer.readFileCountsInFolder(1);
        myDFPlayer.playFolder(1, random(track_count));
}

void loop() {
        // Проверка входа сигнализации
        alrm.tick();
        if (alrm.isHold()) {
                myDFPlayer.pause();
                delay(50);
                track_count = myDFPlayer.readFileCountsInFolder(0);
                myDFPlayer.playFolder(0, random(track_count));
                Serial.println("Тревога");
        }
        if (alrm.hasClicks()) {
                signals = butt1.getClicks() + 1;
                myDFPlayer.pause();
                delay(50);
                track_count = myDFPlayer.readFileCountsInFolder(signals);
                myDFPlayer.playFolder(signals, random(track_count));
                Serial.print("PLAY track > ");
                Serial.print("\t");
                Serial.print(random(track_count));
                Serial.print("\t");
                Serial.print("folder > ");
                Serial.print("\t");
                Serial.print(signals);
        }

        // Проверка времени
        Time t = rtc.time();
        if ((t.hr==switch_vol_1.hr) & (t.min==switch_vol_1.min)) {
                volume = 15;
        }
        else if ((t.hr==switch_vol_2.hr) & (t.min==switch_vol_2.min)) {
                volume = 30;
        }


        // Проверка кнопки
        butt1.tick();
        butt2.tick();
        butt3.tick();

        // выключить воспроизведение, если нажата кнопка или отпущенна
        if (myDFPlayer.readState()) {
                if ((butt1.isRelease()) || (butt2.isRelease()) || (butt3.isRelease()) || (butt1.isSingle()) || (butt2.isSingle()) || (butt3.isSingle())) {
                        myDFPlayer.pause();
                }
        }
        else {
                // Включить трек, если нажата кнопка
                if (butt1.isSingle()) {
                        track_count = myDFPlayer.readFileCountsInFolder(1);
                        myDFPlayer.playFolder(directory_buttons_1, random(track_count));
                        Serial.print("PLAY track > ");
                        Serial.print("\t");
                        Serial.print(random(track_count));
                        Serial.print("\t");
                        Serial.print("folder > ");
                        Serial.print("\t");
                        Serial.print(directory_buttons_1);
                }
                else if (butt1.isHold()) {
                        track_count = myDFPlayer.readFileCountsInFolder(1);
                        myDFPlayer.playFolder(directory_buttons_1, random(track_count));
                        Serial.print("PLAY track > ");
                        Serial.print("\t");
                        Serial.print(random(track_count));
                        Serial.print("\t");
                        Serial.print("folder > ");
                        Serial.print("\t");
                        Serial.print(directory_buttons_1);
                }

                if (butt2.isSingle()) {
                        track_count = myDFPlayer.readFileCountsInFolder(2);
                        myDFPlayer.playFolder(directory_buttons_2, random(track_count));
                        Serial.print("PLAY track > ");
                        Serial.print("\t");
                        Serial.print(random(track_count));
                        Serial.print("\t");
                        Serial.print("folder > ");
                        Serial.print("\t");
                        Serial.print(directory_buttons_2);
                }
                else if (butt2.isHold()) {
                        track_count = myDFPlayer.readFileCountsInFolder(2);
                        myDFPlayer.playFolder(directory_buttons_2, random(track_count));
                        Serial.print("PLAY track > ");
                        Serial.print("\t");
                        Serial.print(random(track_count));
                        Serial.print("\t");
                        Serial.print("folder > ");
                        Serial.print("\t");
                        Serial.print(directory_buttons_2);
                }

                if (butt3.isSingle()) {
                        track_count = myDFPlayer.readFileCountsInFolder(3);
                        myDFPlayer.playFolder(directory_buttons_3, random(track_count));
                        Serial.print("PLAY track > ");
                        Serial.print("\t");
                        Serial.print(random(track_count));
                        Serial.print("\t");
                        Serial.print("folder > ");
                        Serial.print("\t");
                        Serial.print(directory_buttons_3);
                }
                else if (butt3.isHold()) {
                        track_count = myDFPlayer.readFileCountsInFolder(3);
                        myDFPlayer.playFolder(directory_buttons_3, random(track_count));
                        Serial.print("PLAY track > ");
                        Serial.print("\t");
                        Serial.print(random(track_count));
                        Serial.print("\t");
                        Serial.print("folder > ");
                        Serial.print("\t");
                        Serial.print(directory_buttons_3);
                }
        }
}
