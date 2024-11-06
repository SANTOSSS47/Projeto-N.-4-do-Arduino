#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0x3F); 

const int ledVerde = 2;
const int ledVermelho = 3;
const int buzzer = 4;
const int botao = 5;
const int sensorTempPin = A0;

const float tempMin = 15.0;
const float tempMax = 30.0;

void setup() {
  Serial.begin(9600);
  
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(botao, INPUT_PULLUP);
  
  lcd.begin(16, 2); 
  lcd.setBacklight(LOW); 
  
  lcd.print("Sistema de");
  lcd.setCursor(0, 1);
  lcd.print("Monitoramento");
  delay(2000);
}

void loop() {
  if (digitalRead(botao) == LOW) {
    lcd.clear();
    lcd.print("Sistema Resetado");
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, LOW);
    noTone(buzzer); 
    delay(1000); 
    lcd.clear();
  }

  int leituraAnalogica = analogRead(sensorTempPin);
  float temperatura = (leituraAnalogica * 5.0 / 1023.0) * 100.0; // Convertendo para °C
  
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(temperatura);
  lcd.print(" C");

  if (temperatura < tempMin || temperatura > tempMax) {
    digitalWrite(ledVerde, LOW);
    digitalWrite(ledVermelho, HIGH);
    tone(buzzer, 1000);
  } else {
    digitalWrite(ledVerde, HIGH);
    digitalWrite(ledVermelho, LOW);
    noTone(buzzer);
  }

  delay(1000); 
}
