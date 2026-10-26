#include <LiquidCrystal.h>

const int rs = 10, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int green = 6, yellow = 7, red = 8;
const int buzzer = 9;
long duration;
int distance;

bool active = false;
const int detectionDistLeft = 30;
const int detectionDistRight = 60;
bool left = false;
bool right = false;
int consistency = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(buzzer, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly: 
  digitalWrite(12, LOW);
  delayMicroseconds(2);
  digitalWrite(12, HIGH);
  delayMicroseconds(12);
  digitalWrite(12, LOW);
  duration = pulseIn(13, HIGH);
  distance = duration * 0.034 / 2;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("cm");
  lcd.setCursor(0, 1);
  lcd.print("Waiting...");

  digitalWrite(red, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);

  if (distance <= 10) {
    digitalWrite(green, HIGH);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
  } else if (distance > 10 && distance <= 15) {
    digitalWrite(yellow, HIGH);
    delay(200);
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
  } else if (distance > 15 && distance <= 25) {
    digitalWrite(red, HIGH);
    int consistency = consistency + 1;
    if (consistency > 20) {
      if (direction.read() == 90) {
        left == true;
      } else if (direction.read() == 180) {
        right == true;
      }
      consistency = 0;
    }
  } else if (distance > 25 && distance <= 40) {
    digitalWrite(yellow, HIGH);
    delay(500);
    digitalWrite(buzzer, HIGH);
    delay(250);
    digitalWrite(buzzer, LOW);
  } else if (distance > 40 && distance < detectionDist) {
    digitalWrite(green, HIGH);
    delay(250);
    digitalWrite(buzzer, HIGH);
    delay(250);
    digitalWrite(buzzer, LOW);
  } else if (distance >= detectionDist) {
    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);
    digitalWrite(buzzer, LOW);
    active = false;
  }

  delay(200);
}
