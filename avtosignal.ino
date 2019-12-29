// Для кнопок
#include "GyverButton.h"

#define BUT1_PIN 3
#define BUT2_PIN 3
#define BUT3_PIN 3

GButton butt1(BUT1_PIN);
GButton butt2(BUT2_PIN);
GButton butt3(BUT3_PIN);


// для плеера
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define SS_RX 7
#define SS_TX 6
#define directory_start 1 // Папка с мелодией старта
#define trek_start  1 // Номер трека старта в папке мелодий старта
#define directory_alarm 2 // Папка с мелодиями сигнализаций
#define directory_buttons 3 // Папка с мелодиями кнопок
int volume = 15; // Гормкость 0-30

SoftwareSerial mySoftwareSerial(SS_RX, SS_TX);  // RX, TX
DFRobotDFPlayerMini myDFPlayer;


// Для часов
#include <DS1302.h>

const int kCePin   = 5;  // Chip Enable
const int kIoPin   = 6;  // Input/Output
const int kSclkPin = 7;  // Serial Clock
Time switch_vol_1(2013, 21, 00, 1, 38, 50, Time::kSunday); // Время переключения громкости 1
Time switch_vol_2(2013, 8, 00, 1, 38, 50, Time::kSunday); // Время переключения громкости 2

DS1302 rtc(kCePin, kIoPin, kSclkPin);


// Для входа сигнализации
#define ALARM_PIN 1 // Пин подключения сигналов после оптореле
#define DELAY_SIGNALS 300 // Задержка между сигналами в миллисекундах

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
  Serial.begin(9600); // Вывод
  // Для сигнализации
  pinMode(ALARM_PIN, INPUT);
  // Часы
  rtc.writeProtect(false);
  rtc.halt(false);
  // Подключение плеера
  // ADCSRA &= ~(1 << ADEN);
  if (!myDFPlayer.begin(mySoftwareSerial)) { // запуск плеера//инициализац//более 2 секунд
       Serial.println("st ?");
       while(true);
      }
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  myDFPlayer.volume(volume);   //громкость (0~30).
   myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
   myDFPlayer.playFolder(directory_start, trek_start); // играем старт (короткую мелодию из первой папки)
   delay(200);  // даем немного времени,ждем начало проигрывания//уснем после проигрывания мелодии старта
}

void loop() {
  // Проверка входа сигнализации
  if (digitalRead(ALARM_PIN)) {
      nowTime = millis(); // Запись текущего времени в миллисекундах,
                          // прошедшего с момента запуска, в переменную nowTime
      signals = readCommand();
      myDFPlayer.playFolder(directory_start, signals);
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

  if (butt1.isSingle()) {
    // first btn single
  }
  if (butt2.isSingle()) {
    // second btn single
  }
  if (butt3.isSingle()) {
    // third btn single
  }
  if (butt1.isHold()) {
    myDFPlayer.playFolder(directory_buttons, 1);
    nowTime = millis();
    while ((millis()-nowTime)<3000) {
      if (butt1.isRelease()) {
        myDFPlayer.pause();
        break;
      }
    }
  }
  if (butt2.isHold()) {
    myDFPlayer.playFolder(directory_buttons, 2);
    nowTime = millis();
    while ((millis()-nowTime)<3000) {
      if (butt1.isRelease()) {
        myDFPlayer.pause();
        break;
      }
    }
  }
  if (butt3.isHold()) {
    myDFPlayer.playFolder(directory_buttons, 3);
    nowTime = millis();
    while ((millis()-nowTime)<3000) {
      if (butt1.isRelease()) {
        myDFPlayer.pause();
        break;
      }
    }
  }
}
