#include "GyverButton.h"

#define BUT1_PIN A1
#define BUT2_PIN A2
#define BUT3_PIN A3

GButton butt1(BUT1_PIN);
GButton butt2(BUT2_PIN);
GButton butt3(BUT3_PIN);


void setup() {
        Serial.begin(9600); // Вывод
        Serial.println("Out 9600");

}

void loop() {


        butt1.tick();
        butt2.tick();
        butt3.tick();

        if (butt1.isSingle()) Serial.println("1 Single");
        if (butt1.isDouble()) Serial.println("1 Double");
        if (butt1.isTriple()) Serial.println("1 Triple");
        if (butt2.isSingle()) Serial.println("2 Single");
        if (butt2.isDouble()) Serial.println("2 Double");
        if (butt2.isTriple()) Serial.println("2 Triple");
        if (butt3.isSingle()) Serial.println("3 Single");
        if (butt3.isDouble()) Serial.println("3 Double");
        if (butt3.isTriple()) Serial.println("3 Triple");
}
