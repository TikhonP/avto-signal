#define butpin 2
#define maxtime 5000

int clicks=0;
bool wasclicked=false;

int count_clicks(int timeout) {
        int curcliks=1;
        bool pressed=false;
        unsigned long nowTime = millis();
        while ((millis()-nowTime) < timeout) {
                if (!pressed && digitalRead(butpin)) {
                        delay(15);
                        if (digitalRead(butpin)) {
                                pressed = true;
                                curcliks++;
                        }
                        else if (pressed && !digitalRead(butpin)) {
                                pressed = false;
                        }
                }
        }
        return curcliks;
}

void setup(){
        Serial.begin(9600);
        pinMode(butpin, INPUT);
}

void loop() {
        if (digitalRead(butpin)) {
                delay(15);
                if (digitalRead(butpin)) {
                        Serial.println("Cliks detected");
                        while (true) {
                                if (digitalRead(butpin)) {
                                        delay(15);
                                        if (digitalRead(butpin)) {
                                                clicks = count_clicks(maxtime);
                                                wasclicked=true;
                                                break;
                                        }
                                }
                        }
                }
        }
        if (wasclicked) {
                Serial.print(clicks);
                Serial.println("Cliked!");
        }
}
