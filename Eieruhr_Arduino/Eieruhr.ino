/*
   Eieruhr Projekt, Sebastian Stünkel
   Anfang: 16.12.2021
   Ende:   20.1.2022
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//Die verschiedenen Buttons ihre Pins zuordnen.
int buttonPin1 = 5;                     //Button = weich
int buttonPin2 = 6;                     //Button = mittel
int buttonPin3 = 7;                     //Button = hart
int Zeit = 0;

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);                     //LED ROT
  pinMode(9, OUTPUT);                     //LED Grün
  pinMode(10, OUTPUT);                    //LED Weiß
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  lcd.begin();                            //intitialisierung des LCD Displays
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Countdown: ");
}

void loop() {
  boolean buttonState1 = !digitalRead(buttonPin1);
  boolean buttonState2 = !digitalRead(buttonPin2);
  boolean buttonState3 = !digitalRead(buttonPin3);
  //definierung der Zeit
  if (buttonState1 || buttonState2 || buttonState3) {
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    if (buttonState1) {
      Zeit = 240;       //Zeit für weiches Ei
    } else if (buttonState2) {
      Zeit = 300;       //Zeit für mittel gekochtes Ei
    } else if (buttonState3) {
      Zeit = 360;       //Zeit für ein hartes Ei
    }
    Serial.println(buttonState1);
    Serial.println(buttonState2);
    Serial.println(buttonState3);

    //for Schleife für Countdown
    for (int i = Zeit; i > 0; i--) {
      delay(1000);
      lcd.clear();
      lcd.print(i);
      //Aktuliesrierung Button State
      buttonState1 = digitalRead(buttonPin1);
      buttonState2 = digitalRead(buttonPin2);
      buttonState3 = digitalRead(buttonPin3);
    }
    if (buttonState1 || buttonState2 || buttonState3) {
      lcd.print("Countdown");
      lcd.setCursor(0, 1);
      lcd.print("Beendet");
      delay(1500);
      return;
    }
  }
  //Countdown Ende
  if (Zeit == 240) {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    lcd.print("Eier sind");
    lcd.setCursor(0, 1);
    lcd.print("weich Gekocht");
    tone(3, 100);  //Ton an und abschalten
    delay(1000);
    noTone(3);
  } else if (Zeit == 300) {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    lcd.print("Eier sind");
    lcd.setCursor(0, 1);
    lcd.print("mittel Gekocht");
    tone(3, 100);  //Ton an und abschalten
    delay(1000);
    noTone(3);
  } else if (Zeit == 360) {
    digitalWrite(8, LOW);
    digitalWrite(9, HIGH);
    lcd.print("Eier sind");
    lcd.setCursor(0, 1);
    lcd.print("hart Gekocht");
    tone(3, 100);  //Ton an und abschalten
    delay(1000);
    noTone(3);
  }
}
