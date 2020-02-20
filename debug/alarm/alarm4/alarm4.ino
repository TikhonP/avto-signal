#define BTN_PIN 2
#include "GyverButton.h"

GButton butt1(BTN_PIN);

void setup() {
  Serial.begin(9600);
  // butt1.setTimeout(400);
}

void loop() {
  butt1.tick();

  if (butt1.hasClicks())
    Serial.println(butt1.getClicks());
}
