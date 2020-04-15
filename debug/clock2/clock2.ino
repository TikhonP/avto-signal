#include  <iarduino_RTC.h>


#define rst 8
#define clk 9
#define dat 10

iarduino_RTC  clock (RTC_DS1302, rst, clk, dat);

void setup() {
  Serial.begin(9600);
  clock.begin();
  clock.settime(0, 21, 14, 14, 4, 2020, 2);
}

void loop() {
  if(millis()%1000==0){ // если прошла 1 секунда
      Serial.println(clock.gettime("d-m-Y, H:i:s, D")); // выводим время
      delay(1); // приостанавливаем на 1 мс, чтоб не выводить время несколько раз за 1мс
    }
}
