#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
const char* ssid = "";
const char* password = "";

WiFiUDP ntpUDP;

NTPClient timeClient(ntpUDP, "kr.pool.ntp.org", 32400, 60000);

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  timeClient.begin();
  // GMT + 9 = 3600 * 9 = 
  // timeClient.setTimeOffset(32400);
}

void loop() {
  
  timeClient.update();

  //timeClient.getEpochTime();  // return time in seconds since Jan. 1, 1970
  String curTime = timeClient.getFormattedTime(); // return time formatted like `hh:mm:ss`
  int curHours = timeClient.getHours();
  int curMinutes = timeClient.getMinutes();
  int curSeconds = timeClient.getSeconds();
  
  Serial.println(curTime);
  Serial.println(curHours);
  Serial.println(curMinutes);
  Serial.println(curSeconds);

  delay(1000);
}
