#define ALARM_PIN 2 // Пин подключения сигналов после оптореле
#define SIGNALS_TIME 1000 // Задержка между сигналами в миллисекундах
#define SIGNALS_DELAY_TIME 300
#define MAX_SIGNALS 70
#define RATTLING_COEF 0.7
bool is_alrm = false;


unsigned long nowTime; // Последнее время срабатывания сигнала
int signals;
//

int readCommand() {
        int signalsCount = 1; // Количесво поступающих сигналов
        for (int i = 0; i<MAX_SIGNALS; i++) {
          if

                if (is_alrm) {
                        nowTime = millis();
                        while (true) {
                                if ((!is_alrm) && ((millis() - nowTime)>(SIGNALS_TIME*RATTLING_COEF))) {
                                        if ((millis() - nowTime)>DELAY_SIGNALS) {

                                        }
                                }
                        }
                }
        }
}

void alarm_up() {
        is_alrm = true;
}

void alarm_down() {
        is_alrm = false;
}


void setup() {
        Serial.begin(9600); // Вывод
        Serial.println("Out 9600");
        // Для сигнализации
        pinMode(ALARM_PIN, INPUT);
        attachInterrupt(0, alarm_up, RISING);
        attachInterrupt(0, alarm_down, FALLING);

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
