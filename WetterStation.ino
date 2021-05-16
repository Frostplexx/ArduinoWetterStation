#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <DHT.h>
#include "CO2Sensor.h"
#define DHTPIN 2          // Hier die Pin Nummer eintragen wo der Sensor angeschlossen ist
#define DHTTYPE DHT22

// You will need to create an SFE_BMP180 object, here called "pressure":

Adafruit_BMP085 pressure;
CO2Sensor co2Sensor(A0, 0.99, 100);
#define ALTITUDE 1655.0 // Altitude of SparkFun's HQ in Boulder, CO. in meters
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,20,4);

byte customChar[] = {
  B00011,
  B00011,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup()
{

  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, customChar);
  co2Sensor.calibrate();
  dht.begin();
  co2Sensor.calibrate();
  Serial.begin(9600);
  if (!pressure.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }

}


void loop()
{
  
  char status;
  double T, P, p0, a;
  int co2 = co2Sensor.read();
  float t = dht.readTemperature();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.print(t);
  lcd.write(byte(0));
  lcd.print("C");

  float h = dht.readHumidity();
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");


  lcd.setCursor(0, 2);
  lcd.print("Pressure: ");
  lcd.print((float)pressure.readPressure()/100);
  lcd.print("hPa");

  lcd.setCursor(0, 3);
  lcd.print("CO2: ");
  lcd.print(co2);
  lcd.print("ppm");

    delay(10000);  // Pause for 10 seconds.

  }
