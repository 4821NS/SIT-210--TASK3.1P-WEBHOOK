//all the libraries
#include <DHT.h>
#include <WiFiNINA.h>
#include <ThingSpeak.h>  // ThingSpeak library
//defining the dht pin at which it must be connected
#define DHTPIN 2       // Pin connected to DHT11 data pin
//we have used the dht22 sensor 
#define DHTTYPE DH22  // Type of DHT sensor

//my wifif and its password
//wifi name of my hotspot 
char ssid[] = "Nishant Sadwa;";
//my hotspot aor wifi password
char pass[] = "Sadwal"; // WiFi Passwor

//api key and the channel id 
//id for the channel at which data is to be printed on the thingspeak
unsigned long channelID = 2251725;         
//api key of my channel
const char *apiKey = "JHR4VU6SI27G2E70";   

//decleared the pin number at which it is connected and the type of the sensor
DHT dht(DHTPIN, DHTTYPE);

//created the variable of the client type
WiFiClient client;

void setup() {
  //baudrate is alatered to 9600 for the better communication
  Serial.begin(9600);
  dht.begin();
  connectWiFi();
  ThingSpeak.begin(client);
}

void loop() {
  //2 seconds delay between the readings
  delay(2000); 

// the tenmprature and the humidity
  float temperature = dht.readTemperature();    
  float humidity = dht.readHumidity();           

  if (!isnan(temperature) && !isnan(humidity)) {
    sendDataToThingSpeak(temperature, humidity);
  } else {
    Serial.println("can not read from dht sensor");
  }
  
  //30 seconds delay
  delay(30000); 
}

void connectWiFi() {
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Trying to connect to wifi");
    //wifi or hotspot name and the password to be entered
    WiFi.begin(ssid, pass);
    delay(1000);
  }
  Serial.println("Hurray connectedto wifi");
}

//sending teh data to thing speak
//temp and humidity
void sendDataToThingSpeak(float temp, float humidity) {
  ThingSpeak.setField(1, temp);       
  ThingSpeak.setField(2, humidity);   =
  
  int Code = ThingSpeak.writeFields(channelID, apiKey);
//if successfull then print the succesfull statement
  if (Code == 200) {
    Serial.println("Data is successfull sent to your channel at thingspeak");
  }
  //if error then print the error statement
   else {
    Serial.println("Error occurred while sending the data to  ThingSpeak");
  }
}