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

#define SS_RX 9
#define SS_TX 8

#define track_lenth 3000 // Длинна трека в милисекундах для проверки
#define directory_buttons_1 50 // Папка с мелодиями кнопок
#define directory_buttons_2 51
#define directory_buttons_3 52

int track_count = 1; // количесто треков в каждой папке
int volume = 15; // Гормкость 0-30

SoftwareSerial mySoftwareSerial(SS_RX, SS_TX);  // RX, TX
DFRobotDFPlayerMini myDFPlayer;


// Для часов
// #include <DS1302.h>

// const int kCePin   = 5;  // Chip Enable
// const int kIoPin   = 6;  // Input/Output
// const int kSclkPin = 7;  // Serial Clock
// Time switch_vol_1(2013, 21, 00, 1, 38, 50, Time::kSunday); // Время переключения громкости 1
// Time switch_vol_2(2013, 8, 00, 1, 38, 50, Time::kSunday); // Время переключения громкости 2

// DS1302 rtc(kCePin, kIoPin, kSclkPin);


// Для входа сигнализации
#define ALARM_PIN 2 // Пин подключения сигналов после оптореле
#define DELAY_SIGNALS 300 // Задержка между сигналами в миллисекундах
bool is_alrm = false;

unsigned long nowTime; // Последнее время срабатывания сигнала
int signals;


// Функция для подсчета количества сигналов
int readCommand() {
        int signalsCount = 1; // Количесво поступающих сигналов
        while (true) {
                if ((millis() - nowTime)>DELAY_SIGNALS) {
                        return signalsCount;
                }
                if (digitalRead(ALARM_PIN)) {
                        nowTime = millis();
                        signalsCount++;
                }
        }

}



void setup() {
        mySoftwareSerial.begin(9600);
        Serial.begin(9600); // Вывод
        // Для сигнализации
        pinMode(ALARM_PIN, INPUT);
        attachInterrupt(digitalPinToInterrupt(ALARM_PIN), inter_alrm, RISING);
        // Часы
        // rtc.writeProtect(false);
        // rtc.halt(false);
        // Подключение плеера
        // ADCSRA &= ~(1 << ADEN);
        if (!myDFPlayer.begin(mySoftwareSerial)) { // запуск плеера//инициализац//более 2 секунд
                Serial.println(F("Ошибка подключения плеера:"));
                Serial.println(F("1.Проверьте подключение!"));
                Serial.println(F("2.Пожалуйста, вставьте cd карту!"));
                while(true);
        }
        myDFPlayer.setTimeOut(500);
        myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
        myDFPlayer.volume(volume); //громкость (0~30).
        myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
        myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
        delay(200); // даем немного времени,ждем начало проигрывания
}

void loop() {
        // Проверка входа сигнализации
        if (is_alrm) {
                nowTime = millis(); // Запись текущего времени в миллисекундах,
                                    // прошедшего с момента запуска, в переменную nowTime
                signals = readCommand();
                myDFPlayer.pause();
                delay(50);
                track_count = myDFPlayer.readFileCountsInFolder(signals);
                myDFPlayer.playFolder(signals, random(track_count));
        }

        // Проверка времени
        // Time t = rtc.time();
        // if ((t.hr==switch_vol_1.hr) & (t.min==switch_vol_1.min)) {
        // volume = 15;
        // }
        // else if ((t.hr==switch_vol_2.hr) & (t.min==switch_vol_2.min)) {
        // volume = 30;
        // }


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
                }
                else if (butt1.isHold()) {
                        track_count = myDFPlayer.readFileCountsInFolder(1);
                        myDFPlayer.playFolder(directory_buttons_1, random(track_count));
                }

                if (butt2.isSingle()) {
                        track_count = myDFPlayer.readFileCountsInFolder(2);
                        myDFPlayer.playFolder(directory_buttons_2, random(track_count));
                }
                else if (butt2.isHold()) {
                        track_count = myDFPlayer.readFileCountsInFolder(2);
                        myDFPlayer.playFolder(directory_buttons_2, random(track_count));
                }

                if (butt3.isSingle()) {
                        track_count = myDFPlayer.readFileCountsInFolder(3);
                        myDFPlayer.playFolder(directory_buttons_3, random(track_count));
                }
                else if (butt3.isHold()) {
                        track_count = myDFPlayer.readFileCountsInFolder(3);
                        myDFPlayer.playFolder(directory_buttons_3, random(track_count));
                }
        }
}


void inter_alrm() {
        is_alrm = true;
}
