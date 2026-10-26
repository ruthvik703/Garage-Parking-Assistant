#include <LiquidCrystal.h>

const int rs = 10, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  delay(2500);
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
  lcd.setCursor(0, 1);
  lcd.print(distance);
  lcd.print("cm");

  delay(200);
}
