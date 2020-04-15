// Copyright (c) 2020
// Sketch for playing song for car alarm system
//
// This file for configuration


// КНОПКИ

#define BUT1_PIN 7           // Пин первой кнопки
const short directory_buttons_1 = 50; // Папка с мелодиями первой кнопоки

#define BUT2_PIN 6             // Пин второй кнопки
const short directory_buttons_2 = 51; // Папка с мелодиями второй кнопоки

#define BUT3_PIN 5              // Пин третьей кнопки
const short directory_buttons_3 = 52; // Папка с мелодиями третьей кнопоки


// ПЛЕЕР

#define SS_RX 3     // SS_RX пин
#define SS_TX 2     // SS_TX пин
#define BUSY_PIN A0 // Пин busy

// Гормкость при запуске (0-30)
// до первого срабатывания часов
int volume = 28;


// ЧАСЫ

#define RST 8  // rst пин
#define CLK 9  // clk пин
#define DAT 10 // dat пин

// Если хотите настроить время на модуле, раскомментируйте строчку ниже
// (Уберите //) и задайте время в currenttime

// #define SetTime

// ВАЖНО! После загрузки платы с этой опцией отключите модуль часов,
// закомментируйте строчку обратно, и загрузите скетч.
// Потом продолжайте использывание.

// Задайте текущее время
#define set_hour 16 // Час (0-24)
#define set_minute 44 // Минута (0-60)
#define set_second 0 // Секунда (0-60)
#define set_day 14 // Число (0-31)
#define set_month 4 // Месяц (0-12)
#define set_year 20 // Год (20, 21, 22 ...)
#define set_week_day 2 // День недели начиная с понедельника (1-7)

const short switch_vol_1_hour = 21; // Час (0-24)
const short volume1 = 15; // Громкость, которая будет включаться в это время (0-30)

const short switch_vol_2_hour = 9; // Час (0-24)
const short volume2 = 30; // Громкость для второго срабатывания

const short play_1_hour = 8; // Час (0-24)
const short time_play_folder_1 = 53; // Папка из которой будет включаться случайный трек,
// в заданное выше время
const short play_2_hour = 20; // Час (0-24)
const short time_play_folder_2 = 53; // Аналогично


// ДРУГОЕ

// Пин подключения сигналов после оптореле
#define ALARM_PIN 4

// Свободный аналоговый пин для настройки шума random
#define randompin A4

// Дефолтная задержка программы в мс
const int pleerdelay = 100;

// Пин управления питанием усилителя
#define amp_power_pin A1
// Задержка выключеня в милисеккундах
const unsigned long turn_off_delay = 3000; // (1000 мс = 1 с)
#define dinamic_pin A2

// Папка с максимальной громкостью всегда
const short max_volume_folder = 6;
