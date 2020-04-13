#define PIN_RELAY A1


void setup()
{
  pinMode(PIN_RELAY, OUTPUT);
  // digitalWrite(PIN_RELAY, HIGH);
  Serial.begin(9600);
}
void loop()
{
  digitalWrite(PIN_RELAY, LOW);
  Serial.println("LOW");
  delay(3000);
  digitalWrite(PIN_RELAY, HIGH);
  Serial.println("HIGH");
  delay(3000);
}
