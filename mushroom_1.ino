#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include "humid_cont.h"

#define DHTPIN 2
#define DHTTYPE DHT21
#define MASHROOM_HUMIDITY_SETPOINT 60

LiquidCrystal_I2C lcd(0x27, 20, 4);
DHT dht(DHTPIN, DHTTYPE);  //Initialize DHT sensor for normal 16mhz Arduino

float hum; //hygrometer 
float temp;//thermocouple
bool hum_state = false; //control the humidity machine true = ON, false = OFF

void setup() {
  Serial.begin(9600);
  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("Welcome to");
  lcd.setCursor(1, 1);
  lcd.print("Mushroom ROOM");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Humidity in room");
  lcd.setCursor(3, 1);
  lcd.print("set to:");
  lcd.setCursor(11, 1);
  lcd.print(MASHROOM_HUMIDITY_SETPOINT);
  delay(2000);
  lcd.clear();
}

void loop() {

  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  //control the humidifier based on the hygrometer 
  if (hum<MASHROOM_HUMIDITY_SETPOINT && !hum_state)
      hum_state = humidControl(hum_state);
  if (hum>MASHROOM_HUMIDITY_SETPOINT && hum_state)
      hum_state = humidControl(hum_state);

//print to LCD
 lcd.setCursor(0, 0);
 lcd.print("TEMP: ");
 lcd.print(temp);
 lcd.setCursor(0, 1);
 lcd.print("Humid: ");
 lcd.print(hum);
 lcd.setCursor(11, 1);
 if (hum_state)
  lcd.print("  ON ");
 else 
  lcd.print("  OFF");
 delay(500);
}