int LED_pin = 2;
int turn_on = 0;
int turn_off = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, turn_off);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_pin, turn_on);
  delay(1000);
  digitalWrite(LED_pin, turn_off);
  delay(1000);
}
