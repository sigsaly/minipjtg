#include <Servo.h>

#define ND_D0 16
#define ND_D1 5
#define ND_D2 4
#define ND_D3 0
#define ND_D4 2
#define ND_D5 14
#define ND_D6 12
#define ND_D7 13
#define ND_D8 15
#define ND_RX 3
#define ND_TX 1 
#define ND_S2 10
#define ND_S3 9

#define servoPin ND_D0
Servo servo;

void setup() {
  servo.attach(servoPin);
  servo.write(0);
  delay(500);
}

void loop() {
  servo.write(90);
  delay(500);
  servo.write(180);
  delay(500);
  servo.write(90);
  delay(500);
  servo.write(0);
  delay(500);
}
