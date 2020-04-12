// Copyright (c) 2020
// Sketch for playing song for car alarm system
//
// This file for configuration


// КНОПКИ

#define BUT1_PIN 7             // Пин первой кнопки
#define directory_buttons_1 50 // Папка с мелодиями первой кнопоки

#define BUT2_PIN 6             // Пин второй кнопки
#define directory_buttons_2 51 // Папка с мелодиями второй кнопоки

#define BUT3_PIN 5             // Пин третьей кнопки
#define directory_buttons_3 52 // Папка с мелодиями третьей кнопоки


// ПЛЕЕР

#define SS_RX 3     // SS_RX пин
#define SS_TX 2     // SS_TX пин
#define BUSY_PIN A0 // Пин busy

// Гормкость при запуске (0-30)
// до первого срабатывания часов
int volume = 28;


// ЧАСЫ

#define KCEPIN 8    // kCePin пин
#define KIOPIN 9    // kIoPin пин
#define KSCLKPIN 10 // kSclkPin пин

// Формат Time: (год, месяц, число, час, минута, день недели)
// Формат дня недели Time::kSunday - воскресенье,
// Time::kMonday - понедельник и т. д.

// Если хотите настроить время на модуле, раскомментируйте строчку ниже
// (Уберите //) и задайте время в currenttime

// #define SetTime

// Задайте текущее время
Time currenttime(2013, 9, 22, 1, 38, 50, Time::kSunday);
// ВАЖНО! После загрузки платы с этой опцией отключите модуль часов,
// закомментируйте строчку обратно, и загрузите скетч.
// Потом продолжайте использывание.

// Задайте время первого переключения громкости.
// Так как смента громкости срабатывает раз в сутки, важены только час и минута
Time switch_vol_1(2020, 12, 22, 1, 38, 50, Time::kSunday);
#define volume1 15 // Громкость, которая будет включаться в это время (0-30)
#define time_play_folder_1 53 // Папка из которой будет включаться случайный трек,
                              // в заданное выше время
// Аналогично первому второй время срабатывания
Time switch_vol_2(2020, 8, 22, 1, 38, 50, Time::kSunday);
#define volume2 30 // Громкость для второго срабатывания
#define time_play_folder_2 53 // Аналогично


// ДРУГОЕ

// Пин подключения сигналов после оптореле
#define ALARM_PIN 4

// Свободный аналоговый пин для настройки шума random
#define randompin A4

// Дефолтная задержка программы в мс
#define pleerdelay 100

// Пин управления питанием усилителя
#define amp_power_pin A7
#define turn_off_delay 600000 // Задержка выключеня в милисеккундах
