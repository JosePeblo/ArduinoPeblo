#include <Wire.h>
#include <RTClib.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11
RTC_DS3231 rtc;
DHT dht(DHTPIN, DHTTYPE);

int buzz = 5;
int enable = 6;
int in1 = 7;
int in2 = 8;
int red = 9;
int green = 10;
int blue = 11;
int waPin = A1;
void setup() {
  pinMode(buzz, OUTPUT);
  pinMode(enable, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Serial.begin(9600);
  dht.begin();
  if (! rtc.begin()) {
  Serial.println("Modulo RTC no encontrado !");
  while (1);
  }   
}

void loop() {
  DalyEvent();
  Sensores();
  Serial.println();
  delay(500);
}
void Sensores()
{
  float t = dht.readTemperature();
  int level = analogRead(waPin);
  if(isnan(t))
  {
    Serial.println("Error obteniendo datos del sensor ;(");
    return;
  }
  Serial.print("La temperatura es: ");
  Serial.println(t);
  Serial.print("El nivel es: ");
  Serial.println(level);
  if(t > 29)
  {
    analogWrite(red, 255);
    analogWrite(green, 0);
    analogWrite(blue, 0);
  }
  else if(t > 15 && t <= 29)
  {
    analogWrite(red, 0);
    analogWrite(green, 255);
    analogWrite(blue, 0);
  }
  else if(t <= 15)
  {
    analogWrite(red, 0);
    analogWrite(green, 0);
    analogWrite(blue, 255);
  }
  if(level < 300)
  {
    tone(buzz, 523);
  }
  else
  {
    noTone(buzz);
  }
}
void DalyEvent()
{
  DateTime fecha = rtc.now();
  Serial.print("Hora: ");
  Serial.print(fecha.hour());
  Serial.print(":");
  Serial.print(fecha.minute());
  Serial.print(":");
  Serial.println(fecha.second());
  if(fecha.hour() == 9 && fecha.minute() == 0 && fecha.second() == 0)
  {
    Motor();
  }
}
void Motor()
{
  digitalWrite(enable, HIGH);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  delay(66000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
