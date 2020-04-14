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

#define RST 8  // rst пин
#define CLK 9  // clk пин
#define DAT 10 // dat пин

// Если хотите настроить время на модуле, раскомментируйте строчку ниже
// (Уберите //) и задайте время в currenttime

// #define SetTime

// Задайте текущее время
#define set_hour 16
#define set_minute 44
#define set_second 0
#define set_day 14
#define set_month 4
#define set_year 20
#define set_week_day 2

#define switch_vol_1_hour 21
#define volume1 15 // Громкость, которая будет включаться в это время (0-30)

#define switch_vol_2_hour 9
#define volume2 30 // Громкость для второго срабатывания

#define play_1_hour 8
#define time_play_folder_1 53 // Папка из которой будет включаться случайный трек,
                              // в заданное выше время
#define play_2_hour 20
#define time_play_folder_2 53 // Аналогично





// Формат Time: (год, месяц, число, час, минута, секунда, день недели)
// Формат дня недели Time::kSunday - воскресенье,
// Time::kMonday - понедельник и т. д.

// Если хотите настроить время на модуле, раскомментируйте строчку ниже
// (Уберите //) и задайте время в currenttime


/*
// Задайте текущее время
Time currenttime(2013, 9, 22, 1, 38, 50, Time::kSunday);
// ВАЖНО! После загрузки платы с этой опцией отключите модуль часов,
// закомментируйте строчку обратно, и загрузите скетч.
// Потом продолжайте использывание.

// Задайте время первого переключения громкости.
// Так как смента громкости срабатывает раз в сутки, важены только час и минута
Time switch_vol_1(2020, 12, 22, 1, 38, 50, Time::kSunday);
#define volume1 15 // Громкость, которая будет включаться в это время (0-30)

// Аналогично первому второй время срабатывания
Time switch_vol_2(2020, 8, 22, 1, 38, 50, Time::kSunday);
#define volume2 30 // Громкость для второго срабатывания

// Задайте время первого включениия трека
Time play_1(2020, 8, 22, 8, 0, 0, Time::kSunday);
#define time_play_folder_1 53 // Папка из которой будет включаться случайный трек,
                              // в заданное выше время
// Аналогично первому второе включение трека
Time play_2(2020, 8, 22, 20, 0, 0, Time::kSunday);
#define time_play_folder_2 53 // Аналогично
*/

// ДРУГОЕ

// Пин подключения сигналов после оптореле
#define ALARM_PIN 4

// Свободный аналоговый пин для настройки шума random
#define randompin A4

// Дефолтная задержка программы в мс
#define pleerdelay 100

// Пин управления питанием усилителя
#define amp_power_pin A1
// Задержка выключеня в милисеккундах
#define turn_off_delay 3000 // (1000 мс = 1 с)
#define dinamic_pin A2

// Папка с максимальной громкостью всегда
#define max_volume_folder 6
