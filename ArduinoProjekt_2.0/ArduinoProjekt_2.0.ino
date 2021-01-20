

#include <SFE_BMP180.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#define DHTPIN 2          // Hier die Pin Nummer eintragen wo der Sensor angeschlossen ist
#define DHTTYPE DHT22

// You will need to create an SFE_BMP180 object, here called "pressure":

SFE_BMP180 pressure;

#define ALTITUDE 1655.0 // Altitude of SparkFun's HQ in Boulder, CO. in meters
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


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

float pressureArray[14];
float pressureChange;



void setup()
{
  lcd.begin(20, 4);
  lcd.createChar(0, customChar);
  lcd.home();


  Serial.begin(9600);
  Serial.println("REBOOT");


  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
  

    Serial.println("BMP180 init fail\n\n");
    while (1); // Pause forever.
  }
  dht.begin();

}

//draw battery level in position x,y
void batterylevel()
{
 
}
//read internal voltage
long readVcc() {
  long result;
  // Read 1.1V reference against AVcc
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Convert
  while (bit_is_set(ADCSRA, ADSC));
  result = ADCL;
  result |= ADCH << 8;
  result = 1126400L / result; // Back-calculate AVcc in mV
  return result;
}

void loop()
{
  lcd.clear();
  char status;
  double T, P, p0, a;

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    status = pressure.getTemperature(T);
    if (status != 0)
    {

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        status = pressure.getPressure(P, T);
        if (status != 0)
        {
          // Print out the measurement:
          lcd.setCursor(0, 4);
          lcd.print("Pressure: ");
          lcd.print(P, 2);
          lcd.print("hPa");
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");

  float h = dht.readHumidity();
  lcd.setCursor(0, 2);
  lcd.print("Humidity: ");
  lcd.print(h);
  lcd.print("%");
  float t = dht.readTemperature();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.write(byte(0));
  lcd.print("C");


  for (int a = 13 ; a >= 0 ; --a )
  {
    pressureArray[a] = pressureArray[a - 1];
  }
  pressureArray[0] = P;
  pressureChange = pressureArray[13] - pressureArray[0];
  lcd.setCursor(0, 1);
  lcd.print("Weather: ");
  if (pressureArray[13] != 0 && pressureChange >= 3000)
  {
    lcd.print("Rain (WIP)");
  }
  else
  {
    lcd.print("Sun (WIP)");
  }


 //read the voltage and convert it to volt
  double curvolt = double( readVcc() ) / 1000;
 // loop(curvolt); 
  // check if voltge is bigger than 4.2 volt so this is a power source
  if(curvolt > 4.2)
  {
    lcd.setCursor(15, 0);  
    lcd.print(curvolt);
    lcd.print("V"); 
  }
  if(curvolt <= 4.2 && curvolt > 4.0)
  {

  }
  if(curvolt <= 4.0 && curvolt > 3.8)
  {


  }
  if(curvolt <= 3.8 && curvolt > 3.6)
  {


  }
  if(curvolt <= 3.6 && curvolt > 3.4)
  {

  }
  if(curvolt <= 3.4 && curvolt > 3.2)
  {

  }
  if(curvolt <= 3.2 && curvolt > 3.0)
  {

  }
  if(curvolt < 3.0)
  {

  }
   
    delay(10000);  // Pause for 10 seconds.

  }
