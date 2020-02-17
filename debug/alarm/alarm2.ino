#define ALARM_PIN 2 // Пин подключения сигналов после оптореле
#define DELAY_SIGNALS 1000 // Задержка между сигналами в миллисекундах
bool Seren_activity = false;
unsigned long nowTime;

void setup() {
        pinMode(ALARM_PIN, INPUT);
}


void loop() {
        if (!Seren_activity && digitalRead(ALARM_PIN))
        {
                ZonaSeren++;
                Seren_activity=true;
                nowTime = millis();
        }
        else if (Seren_activity && !digitalRead(SEREN)) Seren_activity=0;
        //-----------------------посчитав колич.коротких сигналов сирены --действуем----------------------------
        if (millis()-SEREN_time > DELAY_SIGNALS && ZonaSeren)
        {
                SEREN_time = millis();            // перезапускаем таймер
                if (!Seren_activity) myDFPlayer.playFolder(randNumber, ZonaSeren);         // если cирена отпищала -то играем свою мелодию
                else myDFPlayer.playFolder(randNumber, ALARM7);         //если играет непрерывно//играем тревогу //мелодия должна быть длинной 20-30 сек
                // ниже пауза,до старта плеера,но не более "sbros_time", чтобы выйти из цикла,не зависнуть
                while( digitalRead(BUSY)&& millis()-SEREN_time < sbros_time)  {}        //при выходе из цикла,после старта плеера-сброс счетчика сирен
                if  (!digitalRead(BUSY)) ZonaSeren=0;
        }
        else if (digitalRead(BUSY)&& millis()-SEREN_time>sbros_time && !ZonaSeren && !digitalRead(SEREN)) OF_Power ();         // если отиграла мелодию
}
