#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <DHT.h>
#define DHTPIN 2          // Hier die Pin Nummer eintragen wo der Sensor angeschlossen ist
#define DHTTYPE DHT22

// You will need to create an SFE_BMP180 object, here called "pressure":

Adafruit_BMP085 pressure;

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

  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customChar);

  dht.begin();

  Serial.begin(9600);
  if (!pressure.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }

}


void loop()
{
  lcd.clear();
  char status;
  double T, P, p0, a;

  float t = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
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
  lcd.print("1000");
  lcd.print("ppm");



   
    delay(1000);  // Pause for 10 seconds.

  }
