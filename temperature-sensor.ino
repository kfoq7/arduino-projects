#include <LiquidCrystal.h>

const int rpmMin = 580;
const int rpmMax = 950;

const int temperaturePin = A0;
const int potentiometer = A1;
const int motorPin = 8;
const int ledGreen = 9;
const int ledRed = 10;
const int switchPin = 1;

int rpmValue;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void cleanLcd(bool line = false) {
  if (line) {
    lcd.print("                ");
  } else {
    lcd.clear();
  }
}

void setup() {
  delay(100);

  pinMode(motorPin, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(switchPin, INPUT);

  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop() {
  rpmValue = analogRead(potentiometer);
  rpmValue = map(rpmValue, 0, 1023, 0, 3000);

  float temp;
  bool usePoten = digitalRead(switchPin);

  if (usePoten) {
    temp = analogRead(potentiometer);
  } else {
    temp = analogRead(temperaturePin);
  }

  temp = map(temp, 0, 1023, 0, 500);
  temp = temp - 49;

  temperature(temp);
}

void temperature(float temp) {
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");

  if (temp < 65) {
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledRed, LOW);
    lcd.setCursor(0, 1);
    cleanLcd(true);
    lcd.setCursor(0, 1);
    lcd.print("Frio ");
    analogWrite(8, 0);
  }

  if (temp >= 65 && temp <= 91) {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    lcd.setCursor(0, 1);
    cleanLcd(true);
    lcd.setCursor(0, 1);
    lcd.print("Ventilador: LOW");
    analogWrite(8, 200);
  }

  if (temp > 91) {
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledRed, HIGH);
    lcd.setCursor(0, 1);
    cleanLcd(true);
    lcd.setCursor(0, 1);
    lcd.print("Ventilador: HIGH");
    analogWrite(8, 200);
  }

  lcd.setCursor(6, 0);
  lcd.print(temp);
  Serial.println(temp);
  delay(1000);
}
