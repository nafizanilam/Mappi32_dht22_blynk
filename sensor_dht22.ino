#define BLYNK_TEMPLATE_ID "XXXXXXXXX"
#define BLYNK_DEVICE_NAME "XXXXXXXXXXXXXXXXXXX"
#define BLYNK_AUTH_TOKEN "XXXXXXXXXXXXXXXXXXXXXXXXXX"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>

//Libraries
#include <DHT.h>;

//Constants
#define DHTPIN 5     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino


//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "XXXXXXXXX"; //nama wifi
char pass[] = "XXXXXXXXX"; //password wifi

BlynkTimer timer;


void myTimerEvent()
{
  Blynk.virtualWrite(V5, millis() / 1000);
}

void setup()
{
  Wire.begin();
  Blynk.begin(auth, ssid, pass);
  Serial.begin(9600);
  dht.begin();
}

void loop()
{
  Blynk.run();
  timer.run();

  delay(500);
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temperature: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  delay(500); //Delay 2 sec.
  Blynk.virtualWrite(V1, temp);
  Blynk.virtualWrite(V2, hum);
  delay(1000);
}
