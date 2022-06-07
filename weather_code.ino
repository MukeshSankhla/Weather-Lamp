#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <JsonListener.h>
#include <time.h>
#include <FastLED.h>
#include "OpenWeatherMapCurrent.h"

#define LED_PIN 4
#define NUM_LEDS 25
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define BRIGHTNESS  250
CRGB leds[NUM_LEDS];

OpenWeatherMapCurrent client;
String OPEN_WEATHER_MAP_APP_ID = "b7df78ef1d59c1e16cb759b09cf23acf";
String OPEN_WEATHER_MAP_LOCATION_ID = "1252699";
String OPEN_WEATHER_MAP_LANGUAGE = "en";
boolean IS_METRIC = true;

const char* ESP_HOST_NAME = "esp-" + ESP.getFlashChipId();

const char* ssid    = "KingsDIY";
const char* password = "balaji44";

int timezone = -5.5 * 3600;
int dst = 0;
   
WiFiClient wifiClient;

void connectWifi() 
{
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void setup() 
{
  Serial.begin(115200);
  delay(500);
  connectWifi();

  Serial.println();
  Serial.println("\n\nNext Loop-Step: " + String(millis()) + ":");
  LEDS.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
}

void loop()
{
  OpenWeatherMapCurrentData data;
  client.setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  client.setMetric(IS_METRIC);
  client.updateCurrentById(&data, OPEN_WEATHER_MAP_APP_ID, OPEN_WEATHER_MAP_LOCATION_ID);

  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  Serial.print("-------------------------------------------------\n");
  Serial.print("Date & Time : ");
  Serial.print(p_tm->tm_mday);
  Serial.print("/");
  Serial.print(p_tm->tm_mon + 1);
  Serial.print("/");
  Serial.print(p_tm->tm_year + 1900);
  Serial.print(" ");
  Serial.print(p_tm->tm_hour);
  Serial.print(":");
  Serial.print(p_tm->tm_min);
  Serial.print(":");
  Serial.println(p_tm->tm_sec);
  Serial.printf("main: %s\n", data.main.c_str());
  Serial.printf("description: %s\n", data.description.c_str());
  Serial.printf("temp: %f\n", data.temp);
  Serial.printf("clouds: %d\n", data.clouds);
  Serial.print("-------------------------------------------------\n");
  
  String c=data.description.c_str(); 
  int h=p_tm->tm_hour;
  int temp=data.temp;

  /*------------------------Morning-------------------------*/
  if(h >= 5 && h < 9 && (c == "clear sky" || c == "few clouds"))
  {
   leds[24].setRGB(255, 47, 0); 
   leds[23].setRGB(36, 0, 16);
   
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(0,0,0); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(0,0,0); 
   leds[21].setRGB(0,0,0);
   leds[22].setRGB(0,0,0);
   FastLED.show();
   delay(5000);
  }
  if(h >= 5 && h < 9 && c == "scattered clouds")
  {
   leds[24].setRGB(255, 47, 0); 
   leds[23].setRGB(36, 0, 16); 

   leds[16].setRGB(5, 173, 245); 
   leds[17].setRGB(245, 36, 5); 
   leds[18].setRGB(245, 36, 5); 
   leds[19].setRGB(245, 36, 5);
   leds[20].setRGB(245, 36, 5); 
   leds[21].setRGB(245, 36, 5);
   leds[22].setRGB(245, 36, 5);
   FastLED.show();
   delay(5000);
  }
  if(h >= 5 && h < 9 && (c == "broken clouds" || c == "overcast clouds"))
  {
   leds[16].setRGB(24, 82, 89); 
   leds[17].setRGB(24, 82, 89); 
   leds[18].setRGB(104, 0, 214); 
   leds[19].setRGB(104, 0, 214);
   leds[20].setRGB(104, 0, 214); 
   leds[21].setRGB(99, 12, 6);
   leds[22].setRGB(99, 12, 6);
   
   leds[24].setRGB(255, 47, 0); 
   leds[23].setRGB(36, 0, 16); 
   FastLED.show();
   delay(5000);
  }
  if(h >= 5 && h<9 && (c == "light rain" || c == "moderate rain" || c == "heavy intensity rain"))
  {
   leds[24].setRGB(255, 47, 0); 
   leds[23].setRGB(36, 0, 16);
   FastLED.show();
   
   leds[16].setRGB(59, 0, 79); 
   leds[17].setRGB(59, 0, 79); 
   leds[18].setRGB(59, 0, 79); 
   leds[19].setRGB(59, 0, 79);
   leds[20].setRGB(59, 0, 79); 
   leds[21].setRGB(59, 0, 79);
   leds[22].setRGB(59, 0, 79);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(59, 0, 79); 
   leds[17].setRGB(59, 0, 79); 
   leds[18].setRGB(59, 0, 79); 
   leds[19].setRGB(59, 0, 79);
   leds[20].setRGB(59, 0, 79); 
   leds[21].setRGB(59, 0, 79);
   leds[22].setRGB(59, 0, 79);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(59, 0, 79); 
   leds[17].setRGB(59, 0, 79); 
   leds[18].setRGB(59, 0, 79); 
   leds[19].setRGB(59, 0, 79);
   leds[20].setRGB(59, 0, 79); 
   leds[21].setRGB(59, 0, 79);
   leds[22].setRGB(59, 0, 79);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(59, 0, 79); 
   leds[17].setRGB(59, 0, 79); 
   leds[18].setRGB(59, 0, 79); 
   leds[19].setRGB(59, 0, 79);
   leds[20].setRGB(59, 0, 79); 
   leds[21].setRGB(59, 0, 79);
   leds[22].setRGB(59, 0, 79);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(59, 0, 79); 
   leds[17].setRGB(59, 0, 79); 
   leds[18].setRGB(59, 0, 79); 
   leds[19].setRGB(59, 0, 79);
   leds[20].setRGB(59, 0, 79); 
   leds[21].setRGB(59, 0, 79);
   leds[22].setRGB(59, 0, 79);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(59, 0, 79); 
   leds[17].setRGB(59, 0, 79); 
   leds[18].setRGB(59, 0, 79); 
   leds[19].setRGB(59, 0, 79);
   leds[20].setRGB(59, 0, 79); 
   leds[21].setRGB(59, 0, 79);
   leds[22].setRGB(59, 0, 79);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(59, 0, 79); 
   leds[17].setRGB(59, 0, 79); 
   leds[18].setRGB(59, 0, 79); 
   leds[19].setRGB(59, 0, 79);
   leds[20].setRGB(59, 0, 79); 
   leds[21].setRGB(59, 0, 79);
   leds[22].setRGB(59, 0, 79);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(59, 0, 79); 
   leds[17].setRGB(59, 0, 79); 
   leds[18].setRGB(59, 0, 79); 
   leds[19].setRGB(59, 0, 79);
   leds[20].setRGB(59, 0, 79); 
   leds[21].setRGB(59, 0, 79);
   leds[22].setRGB(59, 0, 79);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(59, 0, 79); 
   leds[17].setRGB(59, 0, 79); 
   leds[18].setRGB(59, 0, 79); 
   leds[19].setRGB(59, 0, 79);
   leds[20].setRGB(59, 0, 79); 
   leds[21].setRGB(59, 0, 79);
   leds[22].setRGB(59, 0, 79);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(59, 0, 79); 
   leds[17].setRGB(59, 0, 79); 
   leds[18].setRGB(59, 0, 79); 
   leds[19].setRGB(59, 0, 79);
   leds[20].setRGB(59, 0, 79); 
   leds[21].setRGB(59, 0, 79);
   leds[22].setRGB(59, 0, 79);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(59, 0, 79); 
   leds[17].setRGB(59, 0, 79); 
   leds[18].setRGB(59, 0, 79); 
   leds[19].setRGB(59, 0, 79);
   leds[20].setRGB(59, 0, 79); 
   leds[21].setRGB(59, 0, 79);
   leds[22].setRGB(59, 0, 79);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(59, 0, 79); 
   leds[17].setRGB(59, 0, 79); 
   leds[18].setRGB(59, 0, 79); 
   leds[19].setRGB(59, 0, 79);
   leds[20].setRGB(59, 0, 79); 
   leds[21].setRGB(59, 0, 79);
   leds[22].setRGB(59, 0, 79);
   delay(200);
  }


  /*------------------------Afternoon-------------------------*/
  if(h >= 9 && h < 17 && (c == "clear sky" || c == "few clouds"))
  {
   leds[23].setRGB(255, 47, 0); 
   leds[24].setRGB(255, 42, 0);
   
   leds[16].setRGB(245, 187, 93); 
   leds[17].setRGB(245, 187, 93); 
   leds[18].setRGB(245, 187, 93); 
   leds[19].setRGB(245, 187, 93);
   leds[20].setRGB(245, 187, 93); 
   leds[21].setRGB(245, 187, 93);
   leds[22].setRGB(245, 187, 93);
   FastLED.show();
   delay(5000);
  }
  if(h >= 9 && h < 17 && c == "scattered clouds")
  {
   leds[16].setRGB(255, 0, 0); 
   leds[17].setRGB(255, 0, 0); 
   leds[18].setRGB(230, 252, 255); 
   leds[19].setRGB(230, 252, 255);
   leds[20].setRGB(230, 252, 255); 
   leds[21].setRGB(230, 252, 255);
   leds[22].setRGB(230, 252, 255);
   
   leds[23].setRGB(255, 47, 0); 
   leds[24].setRGB(255, 42, 0);
    FastLED.show();
    delay(5000);
  }
  if(h >= 9 && h <17 && (c == "broken clouds" || c == "overcast clouds"))
  {
   leds[16].setRGB(24, 82, 89); 
   leds[17].setRGB(24, 82, 89); 
   leds[18].setRGB(24, 82, 89); 
   leds[19].setRGB(41, 8, 69);
   leds[20].setRGB(41, 8, 69); 
   leds[21].setRGB(99, 12, 6);
   leds[22].setRGB(99, 12, 6);
   
   leds[23].setRGB(255, 47, 0); 
   leds[24].setRGB(255, 42, 0);
    FastLED.show();
    delay(5000);
  }
  if(h >= 9 && h < 17 && (c == "light rain" || c == "moderate rain" || c == "heavy intensity rain"))
  {
   leds[23].setRGB(255, 47, 0); 
   leds[24].setRGB(255, 42, 0);
    FastLED.show();

   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(59, 44, 36); 
   leds[19].setRGB(59, 44, 36);
   leds[20].setRGB(59, 44, 36); 
   leds[21].setRGB(59, 44, 36);
   leds[22].setRGB(59, 44, 36);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(59, 44, 36); 
   leds[19].setRGB(59, 44, 36);
   leds[20].setRGB(59, 44, 36); 
   leds[21].setRGB(59, 44, 36);
   leds[22].setRGB(59, 44, 36);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(59, 44, 36); 
   leds[19].setRGB(59, 44, 36);
   leds[20].setRGB(59, 44, 36); 
   leds[21].setRGB(59, 44, 36);
   leds[22].setRGB(59, 44, 36);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(59, 44, 36); 
   leds[19].setRGB(59, 44, 36);
   leds[20].setRGB(59, 44, 36); 
   leds[21].setRGB(59, 44, 36);
   leds[22].setRGB(59, 44, 36);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(59, 44, 36); 
   leds[19].setRGB(59, 44, 36);
   leds[20].setRGB(59, 44, 36); 
   leds[21].setRGB(59, 44, 36);
   leds[22].setRGB(59, 44, 36);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(59, 44, 36); 
   leds[19].setRGB(59, 44, 36);
   leds[20].setRGB(59, 44, 36); 
   leds[21].setRGB(59, 44, 36);
   leds[22].setRGB(59, 44, 36);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(59, 44, 36); 
   leds[19].setRGB(59, 44, 36);
   leds[20].setRGB(59, 44, 36); 
   leds[21].setRGB(59, 44, 36);
   leds[22].setRGB(59, 44, 36);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(59, 44, 36); 
   leds[19].setRGB(59, 44, 36);
   leds[20].setRGB(59, 44, 36); 
   leds[21].setRGB(59, 44, 36);
   leds[22].setRGB(59, 44, 36);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(59, 44, 36); 
   leds[19].setRGB(59, 44, 36);
   leds[20].setRGB(59, 44, 36); 
   leds[21].setRGB(59, 44, 36);
   leds[22].setRGB(59, 44, 36);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(59, 44, 36); 
   leds[19].setRGB(59, 44, 36);
   leds[20].setRGB(59, 44, 36); 
   leds[21].setRGB(59, 44, 36);
   leds[22].setRGB(59, 44, 36);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(59, 44, 36); 
   leds[19].setRGB(59, 44, 36);
   leds[20].setRGB(59, 44, 36); 
   leds[21].setRGB(59, 44, 36);
   leds[22].setRGB(59, 44, 36);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
  }

  /*------------------------Evening-------------------------*/
  if(h >= 17 && h < 19 && (c == "clear sky" || c == "few clouds"))
  {
   leds[23].setRGB(255, 47, 0); 
   leds[24].setRGB(71, 42, 10);
   
   leds[16].setRGB(66, 16, 65); 
   leds[17].setRGB(66, 16, 65); 
   leds[18].setRGB(245, 36, 5); 
   leds[19].setRGB(245, 36, 5);
   leds[20].setRGB(245, 36, 5); 
   leds[21].setRGB(245, 36, 5);
   leds[22].setRGB(245, 36, 5);
   FastLED.show();
   delay(5000);
  }
  if(h >= 17 && h < 19 && c == "scattered clouds")
  {
   leds[23].setRGB(255, 47, 0); 
   leds[24].setRGB(71, 42, 10);
   FastLED.show();
   
   leds[16].setRGB(245, 36, 5); 
   leds[17].setRGB(245, 36, 5); 
   leds[18].setRGB(245, 36, 5); 
   leds[19].setRGB(0, 89, 110);
   leds[20].setRGB(245, 36, 5); 
   leds[21].setRGB(245, 36, 5);
   leds[22].setRGB(245, 36, 5);
   FastLED.show();
   delay(5000);
  }
  if(h >= 17 && h < 19 && (c == "broken clouds" || c == "overcast clouds"))
  {
   leds[23].setRGB(255, 47, 0); 
   leds[24].setRGB(71, 42, 10);
   
   leds[16].setRGB(245, 36, 5); 
   leds[17].setRGB(245, 36, 5); 
   leds[18].setRGB(66, 16, 65); 
   leds[19].setRGB(66, 16, 65);
   leds[20].setRGB(66, 16, 65); 
   leds[21].setRGB(66, 16, 65);
   leds[22].setRGB(66, 16, 65);
   FastLED.show(); 
   delay(5000);
  }
  if(h >= 17 && h < 19 && (c == "light rain" || c == "moderate rain" || c == "heavy intensity rain"))
  {
   leds[23].setRGB(255, 47, 0); 
   leds[24].setRGB(71, 42, 10); 
   FastLED.show(); 

   leds[16].setRGB(46, 15, 0); 
   leds[17].setRGB(46, 15, 0); 
   leds[18].setRGB(46, 15, 0); 
   leds[19].setRGB(46, 15, 0);
   leds[20].setRGB(46, 15, 0); 
   leds[21].setRGB(46, 15, 0);
   leds[22].setRGB(46, 15, 0);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(46, 15, 0); 
   leds[17].setRGB(46, 15, 0); 
   leds[18].setRGB(46, 15, 0); 
   leds[19].setRGB(46, 15, 0);
   leds[20].setRGB(46, 15, 0); 
   leds[21].setRGB(46, 15, 0);
   leds[22].setRGB(46, 15, 0);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(46, 15, 0); 
   leds[17].setRGB(46, 15, 0); 
   leds[18].setRGB(46, 15, 0); 
   leds[19].setRGB(46, 15, 0);
   leds[20].setRGB(46, 15, 0); 
   leds[21].setRGB(46, 15, 0);
   leds[22].setRGB(46, 15, 0);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(46, 15, 0); 
   leds[17].setRGB(46, 15, 0); 
   leds[18].setRGB(46, 15, 0); 
   leds[19].setRGB(46, 15, 0);
   leds[20].setRGB(46, 15, 0); 
   leds[21].setRGB(46, 15, 0);
   leds[22].setRGB(46, 15, 0);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(46, 15, 0); 
   leds[17].setRGB(46, 15, 0); 
   leds[18].setRGB(46, 15, 0); 
   leds[19].setRGB(46, 15, 0);
   leds[20].setRGB(46, 15, 0); 
   leds[21].setRGB(46, 15, 0);
   leds[22].setRGB(46, 15, 0);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(46, 15, 0); 
   leds[17].setRGB(46, 15, 0); 
   leds[18].setRGB(46, 15, 0); 
   leds[19].setRGB(46, 15, 0);
   leds[20].setRGB(46, 15, 0); 
   leds[21].setRGB(46, 15, 0);
   leds[22].setRGB(46, 15, 0);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(46, 15, 0); 
   leds[17].setRGB(46, 15, 0); 
   leds[18].setRGB(46, 15, 0); 
   leds[19].setRGB(46, 15, 0);
   leds[20].setRGB(46, 15, 0); 
   leds[21].setRGB(46, 15, 0);
   leds[22].setRGB(46, 15, 0);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(46, 15, 0); 
   leds[17].setRGB(46, 15, 0); 
   leds[18].setRGB(46, 15, 0); 
   leds[19].setRGB(46, 15, 0);
   leds[20].setRGB(46, 15, 0); 
   leds[21].setRGB(46, 15, 0);
   leds[22].setRGB(46, 15, 0);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(46, 15, 0); 
   leds[17].setRGB(46, 15, 0); 
   leds[18].setRGB(46, 15, 0); 
   leds[19].setRGB(46, 15, 0);
   leds[20].setRGB(46, 15, 0); 
   leds[21].setRGB(46, 15, 0);
   leds[22].setRGB(46, 15, 0);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(46, 15, 0); 
   leds[17].setRGB(46, 15, 0); 
   leds[18].setRGB(46, 15, 0); 
   leds[19].setRGB(46, 15, 0);
   leds[20].setRGB(46, 15, 0); 
   leds[21].setRGB(46, 15, 0);
   leds[22].setRGB(46, 15, 0);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(46, 15, 0); 
   leds[17].setRGB(46, 15, 0); 
   leds[18].setRGB(46, 15, 0); 
   leds[19].setRGB(46, 15, 0);
   leds[20].setRGB(46, 15, 0); 
   leds[21].setRGB(46, 15, 0);
   leds[22].setRGB(46, 15, 0);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(46, 15, 0); 
   leds[17].setRGB(46, 15, 0); 
   leds[18].setRGB(46, 15, 0); 
   leds[19].setRGB(46, 15, 0);
   leds[20].setRGB(46, 15, 0); 
   leds[21].setRGB(46, 15, 0);
   leds[22].setRGB(46, 15, 0);
   FastLED.show();
   delay(200);
  }

  /*------------------------Night-------------------------*/
  if((h >= 19 || h < 5)&& (c == "clear sky" || c == "few clouds"))
  {
   leds[23].setRGB(232, 224, 216); 
   leds[24].setRGB(61, 51, 48); 
   
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(20, 27, 31); 
   leds[19].setRGB(20, 27, 31);
   leds[20].setRGB(40, 51, 56); 
   leds[21].setRGB(40, 51, 56);
   leds[21].setRGB(40, 51, 56);
   FastLED.show();
   delay(5000);
  }
  if((h >= 19 || h < 5)&& c == "scattered clouds")
  {
   leds[23].setRGB(232, 224, 216); 
   leds[24].setRGB(61, 51, 48); 
   
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(16, 46, 71); 
   leds[19].setRGB(16, 46, 71);
   leds[20].setRGB(16, 46, 71); 
   leds[21].setRGB(40, 51, 56);
   leds[22].setRGB(40, 51, 56);
   FastLED.show();
   delay(5000);
  }
  if((h >= 19 || h < 5) && (c == "broken clouds" || c == "overcast clouds"))
  {
   leds[23].setRGB(232, 224, 216); 
   leds[24].setRGB(61, 51, 48); 
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(4, 12, 18); 
   leds[19].setRGB(4, 12, 18);
   leds[20].setRGB(4, 12, 18); 
   leds[21].setRGB(4, 12, 18);
   leds[22].setRGB(40, 51, 56);
   FastLED.show();
   delay(5000);
  }
  if((h >= 19 || h < 5) && (c == "light rain" || c == "moderate rain" || c == "heavy intensity rain"))
  {
   leds[23].setRGB(232, 224, 216); 
   leds[24].setRGB(61, 51, 48); 
    FastLED.show();

   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(0,0,0); 
   leds[19].setRGB(0, 17, 20);
   leds[20].setRGB(0, 17, 20); 
   leds[21].setRGB(0, 17, 20);
   leds[22].setRGB(0, 17, 20);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(0,0,0); 
   leds[19].setRGB(0, 17, 20);
   leds[20].setRGB(0, 17, 20); 
   leds[21].setRGB(0, 17, 20);
   leds[22].setRGB(0, 17, 20);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(0,0,0); 
   leds[19].setRGB(0, 17, 20);
   leds[20].setRGB(0, 17, 20); 
   leds[21].setRGB(0, 17, 20);
   leds[22].setRGB(0, 17, 20);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(0,0,0); 
   leds[19].setRGB(0, 17, 20);
   leds[20].setRGB(0, 17, 20); 
   leds[21].setRGB(0, 17, 20);
   leds[22].setRGB(0, 17, 20);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(0,0,0); 
   leds[19].setRGB(0, 17, 20);
   leds[20].setRGB(0, 17, 20); 
   leds[21].setRGB(0, 17, 20);
   leds[22].setRGB(0, 17, 20);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(0,0,0); 
   leds[19].setRGB(0, 17, 20);
   leds[20].setRGB(0, 17, 20); 
   leds[21].setRGB(0, 17, 20);
   leds[22].setRGB(0, 17, 20);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(0,0,0); 
   leds[19].setRGB(0, 17, 20);
   leds[20].setRGB(0, 17, 20); 
   leds[21].setRGB(0, 17, 20);
   leds[22].setRGB(0, 17, 20);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(0,0,0); 
   leds[19].setRGB(0, 17, 20);
   leds[20].setRGB(0, 17, 20); 
   leds[21].setRGB(0, 17, 20);
   leds[22].setRGB(0, 17, 20);
   FastLED.show();
   delay(50);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(0,0,0); 
   leds[19].setRGB(0, 17, 20);
   leds[20].setRGB(0, 17, 20); 
   leds[21].setRGB(0, 17, 20);
   leds[22].setRGB(0, 17, 20);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(0,0,0); 
   leds[19].setRGB(0, 17, 20);
   leds[20].setRGB(0, 17, 20); 
   leds[21].setRGB(0, 17, 20);
   leds[22].setRGB(0, 17, 20);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
   leds[16].setRGB(0,0,0); 
   leds[17].setRGB(0,0,0); 
   leds[18].setRGB(0,0,0); 
   leds[19].setRGB(0, 17, 20);
   leds[20].setRGB(0, 17, 20); 
   leds[21].setRGB(0, 17, 20);
   leds[22].setRGB(0, 17, 20);
   FastLED.show();
   delay(500);
   leds[16].setRGB(255, 255, 255); 
   leds[17].setRGB(255, 255, 255); 
   leds[18].setRGB(255, 255, 255); 
   leds[19].setRGB(255, 255, 255);
   leds[20].setRGB(255, 255, 255); 
   leds[21].setRGB(255, 255, 255);
   leds[22].setRGB(255, 255, 255);
   FastLED.show();
   delay(100);
  }

  /*-----------------------Temperature-------------------------*/
  if(temp<20)
  {
    leds[0].setRGB(0,255,255);
    leds[1].setRGB(0,255,255);
    leds[2].setRGB(0,255,255);
    leds[3].setRGB(0,255,255);
    leds[4].setRGB(0,255,255);
    leds[5].setRGB(0,255,255);
    leds[6].setRGB(0,255,255);
    leds[7].setRGB(0,255,255);
    leds[8].setRGB(0,255,255);
    leds[9].setRGB(0,255,255);
    leds[10].setRGB(0,255,255);
    leds[11].setRGB(0,255,255);
    leds[12].setRGB(0,255,255);
    leds[13].setRGB(0,255,255);
    leds[14].setRGB(0,255,255);
    leds[15].setRGB(0,255,255);
    FastLED.show();
  }
  if(temp>=20 && temp<30)
  {
    leds[0].setRGB(255, 251, 0);
    leds[1].setRGB(255, 251, 0);
    leds[2].setRGB(255, 251, 0);
    leds[3].setRGB(255, 251, 0);
    leds[4].setRGB(255, 251, 0);
    leds[5].setRGB(255, 251, 0);
    leds[6].setRGB(255, 251, 0);
    leds[7].setRGB(255, 251, 0);
    leds[8].setRGB(255, 251, 0);
    leds[9].setRGB(255, 251, 0);
    leds[10].setRGB(255, 251, 0);
    leds[11].setRGB(255, 251, 0);
    leds[12].setRGB(255, 251, 0);
    leds[13].setRGB(255, 251, 0);
    leds[14].setRGB(255, 251, 0);
    leds[15].setRGB(255, 251, 0);
    FastLED.show();
  }
  if(temp>=30 && temp<40)
  {
    leds[0].setRGB(255, 60, 0);
    leds[1].setRGB(255, 60, 0);
    leds[2].setRGB(255, 60, 0);
    leds[3].setRGB(255, 60, 0);
    leds[4].setRGB(255, 60, 0);
    leds[5].setRGB(255, 60, 0);
    leds[6].setRGB(255, 60, 0);
    leds[7].setRGB(255, 60, 0);
    leds[8].setRGB(255, 60, 0);
    leds[9].setRGB(255, 60, 0);
    leds[10].setRGB(255, 60, 0);
    leds[11].setRGB(255, 60, 0);
    leds[12].setRGB(255, 60, 0);
    leds[13].setRGB(255, 60, 0);
    leds[14].setRGB(255, 60, 0);
    leds[15].setRGB(255, 60, 0);
    FastLED.show();
  }
  if(temp>=40 && temp<50)
  {
    leds[0].setRGB(255, 0, 0);
    leds[1].setRGB(255, 0, 0);
    leds[2].setRGB(255, 0, 0);
    leds[3].setRGB(255, 0, 0);
    leds[4].setRGB(255, 0, 0);
    leds[5].setRGB(255, 0, 0);
    leds[6].setRGB(255, 0, 0);
    leds[7].setRGB(255, 0, 0);
    leds[8].setRGB(255, 0, 0);
    leds[9].setRGB(255, 0, 0);
    leds[10].setRGB(255, 0, 0);
    leds[11].setRGB(255, 0, 0);
    leds[12].setRGB(255, 0, 0);
    leds[13].setRGB(255, 0, 0);
    leds[14].setRGB(255, 0, 0);
    leds[15].setRGB(255, 0, 0);
    
    FastLED.show();
  }
}
