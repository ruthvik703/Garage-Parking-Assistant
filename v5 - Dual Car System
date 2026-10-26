#include <LiquidCrystal.h>
#include <Servo.h>
#include <DHT.h>
#include <EEPROM.h>

#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
float temp = 0;

const int rs = 10, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

Servo direction;

const int green = 6, yellow = 7, red = 8;
const int buzzer = 9;
long duration;
int distance;

//A2 is Profile 1 (Left Button)
//A3 is Profile 2 (Right Button)

int P1 = 0;
int P2 = 0;
int points;
int perfLeft = 19;
int perfRight = 20;

bool active = false;
bool revActive = false;
int finalDist;
const int detectionDist = 60;
bool left = false;
bool right = false;
int side = 1; // 1 is left, 2 is right
int consistency = 0;

int checkDist() {
  digitalWrite(12, LOW);
  delayMicroseconds(2);
  digitalWrite(12, HIGH);
  delayMicroseconds(12);
  digitalWrite(12, LOW);
  duration = pulseIn(13, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  direction.attach(A1, 600, 2300);
  direction.write(0);
  lcd.begin(16, 2);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);

  EEPROM.get(0, P1);
  EEPROM.get(1, P2);
}

void loop() {
  // put your main code here, to run repeatedly: 
  if (!revActive) {
    float newTemp = dht.readTemperature(true);
    if (!active) {
      if ((newTemp - temp) > 1.0) {
        
        direction.write(90); // Look left
        delay(1500);
        checkDist();
        if (distance <= detectionDist && !left) {
          side = 1;
          active = true;
        } else {
          direction.write(180); // Otherwise look right
          delay(1500);
          checkDist();
          if (distance <= detectionDist && !right) {
            side = 2;
            active = true;
          }
          if (distance > 70) {
            right = false;
          }
        }
        if (distance > 70) {
          left = false;
        }
      }
      temp = newTemp;
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    if (active) {
      lcd.print("Distance: ");
      lcd.print(distance);
      lcd.print("cm");
    } else {
      lcd.print(newTemp);
      lcd.write(223);
      lcd.print("F");
    }

    lcd.setCursor(9, 0);
    if (left && right) {
      lcd.print("Full");
    } else if (left) {
      lcd.print("Left");
    } else if (right) {
      lcd.print("Right");
    } else {
      lcd.print("Empty");
    }

    digitalWrite(red, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(green, LOW);

    if (active) {
      checkDist();
      lcd.setCursor(0, 1);
      if (side == 1) {
        lcd.print("Parking Left");
        //LEFT SPOT SETTINGS
        if (distance <= 10) {
        digitalWrite(green, HIGH);
        delay(200);
        digitalWrite(buzzer, HIGH);
        delay(50);
        digitalWrite(buzzer, LOW);
        consistency = 0;
        } else if (distance > 10 && distance <= 15) {
          digitalWrite(yellow, HIGH);
          delay(200);
          digitalWrite(buzzer, HIGH);
          delay(50);
          digitalWrite(buzzer, LOW);
          consistency = 0;
        } else if (distance > 15 && distance <= 25) {
          digitalWrite(red, HIGH);
          consistency = consistency + 1;
          if (consistency > 20) {
            if (direction.read() == 90) {
              left = true;
              active = false;
              revActive = true;
              finalDist = distance;
            } else if (direction.read() == 180) {
              right = true;
              active = false;
              revActive = true;
              finalDist = distance;
            }
            consistency = 0;
          }
        } else if (distance > 25 && distance <= 40) {
          digitalWrite(yellow, HIGH);
          delay(500);
          digitalWrite(buzzer, HIGH);
          delay(250);
          digitalWrite(buzzer, LOW);
          consistency = 0;
        } else if (distance > 40 && distance < detectionDist) {
          digitalWrite(green, HIGH);
          delay(250);
          digitalWrite(buzzer, HIGH);
          delay(250);
          digitalWrite(buzzer, LOW);
          consistency = 0;
        } else if (distance >= detectionDist) {
          digitalWrite(red, LOW);
          digitalWrite(yellow, LOW);
          digitalWrite(green, LOW);
          digitalWrite(buzzer, LOW);
          consistency = 0;
          active = false;
        }
      }
      if (side == 2) {
        lcd.print("Parking Right");
        //RIGHT SPOT SETTINGS
        if (distance <= 10) {
        digitalWrite(green, HIGH);
        delay(200);
        digitalWrite(buzzer, HIGH);
        delay(50);
        digitalWrite(buzzer, LOW);
        consistency = 0;
        } else if (distance > 10 && distance <= 15) {
          digitalWrite(yellow, HIGH);
          delay(200);
          digitalWrite(buzzer, HIGH);
          delay(50);
          digitalWrite(buzzer, LOW);
          consistency = 0;
        } else if (distance > 15 && distance <= 25) {
          digitalWrite(red, HIGH);
          consistency = consistency + 1;
          if (consistency > 20) {
            if (direction.read() == 90) {
              left = true;
              active = false;
              revActive = true;
              finalDist = distance;
            } else if (direction.read() == 180) {
              right = true;
              active = false;
              revActive = true;
              finalDist = distance;
            }
            consistency = 0;
          }
        } else if (distance > 25 && distance <= 40) {
          digitalWrite(yellow, HIGH);
          delay(500);
          digitalWrite(buzzer, HIGH);
          delay(250);
          digitalWrite(buzzer, LOW);
          consistency = 0;
        } else if (distance > 40 && distance < detectionDist) {
          digitalWrite(green, HIGH);
          delay(250);
          digitalWrite(buzzer, HIGH);
          delay(250);
          digitalWrite(buzzer, LOW);
          consistency = 0;
        } else if (distance >= detectionDist) {
          digitalWrite(red, LOW);
          digitalWrite(yellow, LOW);
          digitalWrite(green, LOW);
          digitalWrite(buzzer, LOW);
          consistency = 0;
          active = false;
        }
      }
    }
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Distance: ");
    lcd.print(distance);
    lcd.print("cm");
    lcd.setCursor(0, 1);
    lcd.print("Choose Profile");
    if (digitalRead(A2) == LOW) {
      points = std::abs(perfLeft - finalDist);
      P1 = P1 + points;
      EEPROM.put(0, P1);
      points = 0;
      revActive = false;
    } else if (digitalRead(A3) == LOW) {
      points = std::abs(perfRight - finalDist);
      P2 = P2 + points;
      EEPROM.put(1, P2);
      points = 0;
      revActive = false;
    }
  }

  delay(200);
}
