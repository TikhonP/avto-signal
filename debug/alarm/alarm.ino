#define ALARM_PIN 2 // Пин подключения сигналов после оптореле
#define DELAY_SIGNALS 1000 // Задержка между сигналами в миллисекундах
bool is_alrm = false;

unsigned long nowTime; // Последнее время срабатывания сигнала
int signals;


int readCommand() {
        int signalsCount = 1; // Количесво поступающих сигналов
        while (true) {
                if ((millis() - nowTime)>DELAY_SIGNALS) {
                        // if (is_alrm) {
                        // signalsCount = 0;
                        // }
                        return signalsCount;
                }
                if (is_alrm) {
                        nowTime = millis();
                        signalsCount++;
                        is_alrm = false;
                        delay(DELAY_SIGNALS-1);
                }
        }

}

void inter_alrm() {
        is_alrm = true;
}


void setup() {
        Serial.begin(9600); // Вывод
        Serial.println("Out 9600");
        // Для сигнализации
        pinMode(ALARM_PIN, INPUT);
        attachInterrupt(0, inter_alrm, FALLING);
        Serial.println("ALARM_PIN pinmode");
}

void loop() {
        if (is_alrm) {
                nowTime = millis(); // Запись текущего времени в миллисекундах,
                signals = readCommand();
                Serial.print(signals);
                Serial.println("\tсигналов");
                is_alrm = false;
        }
}
