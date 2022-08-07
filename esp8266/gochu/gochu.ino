#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <SPI.h>

#define ND_D0 16  
#define ND_D1 5
#define ND_D2 4    
#define ND_D3 0
#define ND_D4 2   
#define ND_D5 14  // SPI SCK
#define ND_D6 12  // SPI MISO
#define ND_D7 13  // SPI MOSI
#define ND_D8 15  // SPI CS
#define ND_RX 3
#define ND_TX 1 
#define ND_S2 10
#define ND_S3 9
 
const char* ssid = "mit-wireless";
const char* password = "mit12345";

#define KEY_MOTOR1  ND_D1
#define KEY_MOTOR2  ND_D2
#define KEY_LED     ND_D3

#define OUT_MOTOR1  ND_D0
#define OUT_MOTOR2  ND_D4
#define OUT_LED     ND_D8

#define DEBUG 0

char tmbuf[] = {1,2,3,4,255};
int tcnt = 0;

int key_motor1 = 0;
int key_motor2 = 0;
int key_led = 0;
int key_led_old = 0;
int led_on = 0;

uint8_t en_auto_m1 = 0;
uint8_t en_auto_m2 = 0;

uint8_t motor_on_hour = 9;
uint8_t motor_on_min = 10;
uint8_t m1_duration = 1; 
uint8_t m2_duration = 2; 

int motor_on_time;
int m1_off_time;
int m2_off_time;
uint8_t m1_on = 0;
uint8_t m2_on = 0;

uint8_t en_led_auto = 0;
uint8_t en_led_auto_block = 0;
uint8_t led_on_hour = 9; 
uint8_t led_on_min = 0; 
uint8_t led_off_hour = 18; 
uint8_t led_off_min = 0; 
int led_on_time;
int led_off_time;

WiFiUDP ntpUDP;
ESP8266WebServer server(80);
NTPClient timeClient(ntpUDP, "kr.pool.ntp.org", 32400, 60000);

String sendHTML()
{
  String str = "<!DOCTYPE html> <html>\n";

  str += "<body> <h2>Auto Watering Control Page</h2>\n";
  str += "<form method ='post' action='/params'>\n";
  if(en_led_auto)
    str += "Auto LED control <input type='checkbox' name='EnLedAuto' value='true' checked><br><br>\n";
  else
    str += "Auto LED control <input type='checkbox' name='EnLedAuto' value='true'><br><br>\n"; 

  str += "LED On from <select name='LedOnHour'>\n";
  //str += "<option selected value=''>Hour</option>\n";
  if(led_on_hour == 0)
    str += "<option selected value='0'>00</option>\n";
  else
    str += "<option value='0'>00</option>\n";
  if(led_on_hour == 1)
    str += "<option selected value='1'>01</option>\n";
  else
    str += "<option value='1'>01</option>\n";
  if(led_on_hour == 2)
    str += "<option selected value='2'>02</option>\n";
  else
    str += "<option value='2'>02</option>\n";
  if(led_on_hour == 3)
    str += "<option selected value='3'>03</option>\n";
  else
    str += "<option value='3'>03</option>\n";
  if(led_on_hour == 4)
    str += "<option selected value='4'>04</option>\n";
  else
    str += "<option value='4'>04</option>\n";
  if(led_on_hour == 5)
    str += "<option selected value='5'>05</option>\n";
  else
    str += "<option value='5'>05</option>\n";
  if(led_on_hour == 6)
    str += "<option selected value='6'>06</option>\n";
  else
    str += "<option value='6'>06</option>\n";
  if(led_on_hour == 7)
    str += "<option selected value='7'>07</option>\n";
  else
    str += "<option value='7'>07</option>\n";
  if(led_on_hour == 8)
    str += "<option selected value='8'>08</option>\n";
  else
    str += "<option value='8'>08</option>\n";
  if(led_on_hour == 9)
    str += "<option selected value='9'>09</option>\n";
  else
    str += "<option value='9'>09</option>\n";
  if(led_on_hour == 10)
    str += "<option selected value='10'>10</option>\n";
  else
    str += "<option value='10'>10</option>\n";
  if(led_on_hour == 11)
    str += "<option selected value='11'>11</option>\n";
  else
    str += "<option value='11'>11</option>\n";
  if(led_on_hour == 12)
    str += "<option selected value='12'>12</option>\n";
  else
    str += "<option value='12'>12</option>\n";
  if(led_on_hour == 13)
    str += "<option selected value='13'>13</option>\n";
  else
    str += "<option value='13'>13</option>\n";
  if(led_on_hour == 14)
    str += "<option selected value='14'>14</option>\n";
  else
    str += "<option value='14'>14</option>\n";
  if(led_on_hour == 15)
    str += "<option selected value='15'>15</option>\n";
  else
    str += "<option value='15'>15</option>\n";
  if(led_on_hour == 16)
    str += "<option selected value='16'>16</option>\n";
  else
    str += "<option value='16'>16</option>\n";
  if(led_on_hour == 17)
    str += "<option selected value='17'>17</option>\n";
  else
    str += "<option value='17'>17</option>\n";
  if(led_on_hour == 18)
    str += "<option selected value='18'>18</option>\n";
  else
    str += "<option value='18'>18</option>\n";
  if(led_on_hour == 19)
    str += "<option selected value='19'>19</option>\n";
  else
    str += "<option value='19'>19</option>\n";
  if(led_on_hour == 20)
    str += "<option selected value='20'>20</option>\n";
  else
    str += "<option value='20'>20</option>\n";
  if(led_on_hour == 21)
    str += "<option selected value='21'>21</option>\n";
  else
    str += "<option value='21'>21</option>\n";
  if(led_on_hour == 22)
    str += "<option selected value='22'>22</option>\n";
  else
    str += "<option value='22'>22</option>\n";
  if(led_on_hour == 23)
    str += "<option selected value='23'>23</option>\n";
  else
    str += "<option value='23'>23</option>\n";
  str += "</select>\n";
  
  str += "<select name='LedOnMin'>\n";
  if(led_on_min == 0)
    str += "<option selected value='0'>00</option>\n";
  else
    str += "<option value='0'>00</option>\n";
  if(led_on_min == 1)
    str += "<option selected value='1'>10</option>\n";
  else
    str += "<option value='1'>10</option>\n";
  if(led_on_min == 2)
    str += "<option selected value='2'>20</option>\n";
  else
    str += "<option value='2'>20</option>\n";
  if(led_on_min == 3)
    str += "<option selected value='3'>30</option>\n";
  else
    str += "<option value='3'>30</option>\n";
  if(led_on_min == 4)
    str += "<option selected value='4'>40</option>\n";
  else
    str += "<option value='4'>40</option>\n";
  if(led_on_min == 5)
    str += "<option selected value='5'>50</option>\n";
  else
    str += "<option value='5'>50</option>\n";
  str += "</select>\n";
  
  str += "To <select name='LedOffHour'>\n";
  if(led_off_hour == 0)
    str += "<option selected value='0'>00</option>\n";
  else
    str += "<option value='0'>00</option>\n";
  if(led_off_hour == 1)
    str += "<option selected value='1'>01</option>\n";
  else
    str += "<option value='1'>01</option>\n";
  if(led_off_hour == 2)
    str += "<option selected value='2'>02</option>\n";
  else
    str += "<option value='2'>02</option>\n";
  if(led_off_hour == 3)
    str += "<option selected value='3'>03</option>\n";
  else
    str += "<option value='3'>03</option>\n";
  if(led_off_hour == 4)
    str += "<option selected value='4'>04</option>\n";
  else
    str += "<option value='4'>04</option>\n";
  if(led_off_hour == 5)
    str += "<option selected value='5'>05</option>\n";
  else
    str += "<option value='5'>05</option>\n";
  if(led_off_hour == 6)
    str += "<option selected value='6'>06</option>\n";
  else
    str += "<option value='6'>06</option>\n";
  if(led_off_hour == 7)
    str += "<option selected value='7'>07</option>\n";
  else
    str += "<option value='7'>07</option>\n";
  if(led_off_hour == 8)
    str += "<option selected value='8'>08</option>\n";
  else
    str += "<option value='8'>08</option>\n";
  if(led_off_hour == 9)
    str += "<option selected value='9'>09</option>\n";
  else
    str += "<option value='9'>09</option>\n";
  if(led_off_hour == 10)
    str += "<option selected value='10'>10</option>\n";
  else
    str += "<option value='10'>10</option>\n";
  if(led_off_hour == 11)
    str += "<option selected value='11'>11</option>\n";
  else
    str += "<option value='11'>11</option>\n";
  if(led_off_hour == 12)
    str += "<option selected value='12'>12</option>\n";
  else
    str += "<option value='12'>12</option>\n";
  if(led_off_hour == 13)
    str += "<option selected value='13'>13</option>\n";
  else
    str += "<option value='13'>13</option>\n";
  if(led_off_hour == 14)
    str += "<option selected value='14'>14</option>\n";
  else
    str += "<option value='14'>14</option>\n";
  if(led_off_hour == 15)
    str += "<option selected value='15'>15</option>\n";
  else
    str += "<option value='15'>15</option>\n";
  if(led_off_hour == 16)
    str += "<option selected value='16'>16</option>\n";
  else
    str += "<option value='16'>16</option>\n";
  if(led_off_hour == 17)
    str += "<option selected value='17'>17</option>\n";
  else
    str += "<option value='17'>17</option>\n";
  if(led_off_hour == 18)
    str += "<option selected value='18'>18</option>\n";
  else
    str += "<option value='18'>18</option>\n";
  if(led_off_hour == 19)
    str += "<option selected value='19'>19</option>\n";
  else
    str += "<option value='19'>19</option>\n";
  if(led_off_hour == 20)
    str += "<option selected value='20'>20</option>\n";
  else
    str += "<option value='20'>20</option>\n";
  if(led_off_hour == 21)
    str += "<option selected value='21'>21</option>\n";
  else
    str += "<option value='21'>21</option>\n";
  if(led_off_hour == 22)
    str += "<option selected value='22'>22</option>\n";
  else
    str += "<option value='22'>22</option>\n";
  if(led_off_hour == 23)
    str += "<option selected value='23'>23</option>\n";
  else
    str += "<option value='23'>23</option>\n";
  str += "</select>\n";
  
  str += "<select name='LedOffMin'>\n";
  if(led_off_min == 0)
    str += "<option selected value='0'>00</option>\n";
  else
    str += "<option value='0'>00</option>\n";
  if(led_off_min == 1)
    str += "<option selected value='1'>10</option>\n";
  else
    str += "<option value='1'>10</option>\n";
  if(led_off_min == 2)
    str += "<option selected value='2'>20</option>\n";
  else
    str += "<option value='2'>20</option>\n";
  if(led_off_min == 3)
    str += "<option selected value='3'>30</option>\n";
  else
    str += "<option value='3'>30</option>\n";
  if(led_off_min == 4)
    str += "<option selected value='4'>40</option>\n";
  else
    str += "<option value='4'>40</option>\n";
  if(led_off_min == 5)
    str += "<option selected value='5'>50</option>\n";
  else
    str += "<option value='5'>50</option>\n";
  str += "</select><br><br>\n"; 

  if(en_auto_m1)
    str += "Motor1 Auto <input type='checkbox' name='EnM1' value='true' checked><br>\n";
  else
    str += "Motor1 Auto <input type='checkbox' name='EnM1' value='true'><br>\n"; 
  if(en_auto_m2)
    str += "Motor2 Auto <input type='checkbox' name='EnM2' value='true' checked><br><br>\n";
  else
    str += "Motor2 Auto <input type='checkbox' name='EnM2' value='true'><br><br>\n"; 

  str += "Auto Watering On <select name='MotorOnHour'>\n";
  if(motor_on_hour == 0)
    str += "<option selected value='0'>00</option>\n";
  else
    str += "<option value='0'>00</option>\n";
  if(motor_on_hour == 1)
    str += "<option selected value='1'>01</option>\n";
  else
    str += "<option value='1'>01</option>\n";
  if(motor_on_hour == 2)
    str += "<option selected value='2'>02</option>\n";
  else
    str += "<option value='2'>02</option>\n";
  if(motor_on_hour == 3)
    str += "<option selected value='3'>03</option>\n";
  else
    str += "<option value='3'>03</option>\n";
  if(motor_on_hour == 4)
    str += "<option selected value='4'>04</option>\n";
  else
    str += "<option value='4'>04</option>\n";
  if(motor_on_hour == 5)
    str += "<option selected value='5'>05</option>\n";
  else
    str += "<option value='5'>05</option>\n";
  if(motor_on_hour == 6)
    str += "<option selected value='6'>06</option>\n";
  else
    str += "<option value='6'>06</option>\n";
  if(motor_on_hour == 7)
    str += "<option selected value='7'>07</option>\n";
  else
    str += "<option value='7'>07</option>\n";
  if(motor_on_hour == 8)
    str += "<option selected value='8'>08</option>\n";
  else
    str += "<option value='8'>08</option>\n";
  if(motor_on_hour == 9)
    str += "<option selected value='9'>09</option>\n";
  else
    str += "<option value='9'>09</option>\n";
  if(motor_on_hour == 10)
    str += "<option selected value='10'>10</option>\n";
  else
    str += "<option value='10'>10</option>\n";
  if(motor_on_hour == 11)
    str += "<option selected value='11'>11</option>\n";
  else
    str += "<option value='11'>11</option>\n";
  if(motor_on_hour == 12)
    str += "<option selected value='12'>12</option>\n";
  else
    str += "<option value='12'>12</option>\n";
  if(motor_on_hour == 13)
    str += "<option selected value='13'>13</option>\n";
  else
    str += "<option value='13'>13</option>\n";
  if(motor_on_hour == 14)
    str += "<option selected value='14'>14</option>\n";
  else
    str += "<option value='14'>14</option>\n";
  if(motor_on_hour == 15)
    str += "<option selected value='15'>15</option>\n";
  else
    str += "<option value='15'>15</option>\n";
  if(motor_on_hour == 16)
    str += "<option selected value='16'>16</option>\n";
  else
    str += "<option value='16'>16</option>\n";
  if(motor_on_hour == 17)
    str += "<option selected value='17'>17</option>\n";
  else
    str += "<option value='17'>17</option>\n";
  if(motor_on_hour == 18)
    str += "<option selected value='18'>18</option>\n";
  else
    str += "<option value='18'>18</option>\n";
  if(motor_on_hour == 19)
    str += "<option selected value='19'>19</option>\n";
  else
    str += "<option value='19'>19</option>\n";
  if(motor_on_hour == 20)
    str += "<option selected value='20'>20</option>\n";
  else
    str += "<option value='20'>20</option>\n";
  if(motor_on_hour == 21)
    str += "<option selected value='21'>21</option>\n";
  else
    str += "<option value='21'>21</option>\n";
  if(motor_on_hour == 22)
    str += "<option selected value='22'>22</option>\n";
  else
    str += "<option value='22'>22</option>\n";
  if(motor_on_hour == 23)
    str += "<option selected value='23'>23</option>\n";
  else
    str += "<option value='23'>23</option>\n";
  str += "</select>\n";
  
  str += "<select name='MotorOnMin'>\n";
  if(motor_on_min == 0)
    str += "<option selected value='0'>00</option>\n";
  else
    str += "<option value='0'>00</option>\n";
  if(motor_on_min == 1)
    str += "<option selected value='1'>10</option>\n";
  else
    str += "<option value='1'>10</option>\n";
  if(motor_on_min == 2)
    str += "<option selected value='2'>20</option>\n";
  else
    str += "<option value='2'>20</option>\n";
  if(motor_on_min == 3)
    str += "<option selected value='3'>30</option>\n";
  else
    str += "<option value='3'>30</option>\n";
  if(motor_on_min == 4)
    str += "<option selected value='4'>40</option>\n";
  else
    str += "<option value='4'>40</option>\n";
  if(motor_on_min == 5)
    str += "<option selected value='5'>50</option>\n";
  else
    str += "<option value='5'>50</option>\n";
  str += "</select><br><br>\n";

  str += "Motor1 Duration (seconds) <select name='M1Duration'>\n";
  if(m1_duration == 1)
    str += "<option selected value='1'>01</option>\n";
  else
    str += "<option value='1'>01</option>\n";
  if(m1_duration == 2)
    str += "<option selected value='2'>02</option>\n";
  else
    str += "<option value='2'>02</option>\n";
  if(m1_duration == 3)
    str += "<option selected value='3'>03</option>\n";
  else
    str += "<option value='3'>03</option>\n";
  if(m1_duration == 4)
    str += "<option selected value='4'>04</option>\n";
  else
    str += "<option value='4'>04</option>\n";
  if(m1_duration == 5)
    str += "<option selected value='5'>05</option>\n";
  else
    str += "<option value='5'>05</option>\n";
  if(m1_duration == 6)
    str += "<option selected value='6'>06</option>\n";
  else
    str += "<option value='6'>06</option>\n";
  if(m1_duration == 7)
    str += "<option selected value='7'>07</option>\n";
  else
    str += "<option value='7>07</option>\n";
  if(m1_duration == 8)
    str += "<option selected value='8'>08</option>\n";
  else
    str += "<option value='8'>08</option>\n";
  if(m1_duration == 9)
    str += "<option selected value='9'>09</option>\n";
  else
    str += "<option value='9'>09</option>\n";
  if(m1_duration == 10)
    str += "<option selected value='10'>10</option>\n";
  else
    str += "<option value='10'>10</option>\n";
  str += "</select><br>\n";
  
  str += "Motor2 Duration (seconds) <select name='M2Duration'>\n";
  if(m2_duration == 1)
    str += "<option selected value='1'>01</option>\n";
  else
    str += "<option value='1'>01</option>\n";
  if(m2_duration == 2)
    str += "<option selected value='2'>02</option>\n";
  else
    str += "<option value='2'>02</option>\n";
  if(m2_duration == 3)
    str += "<option selected value='3'>03</option>\n";
  else
    str += "<option value='3'>03</option>\n";
  if(m2_duration == 4)
    str += "<option selected value='4'>04</option>\n";
  else
    str += "<option value='4'>04</option>\n";
  if(m2_duration == 5)
    str += "<option selected value='5'>05</option>\n";
  else
    str += "<option value='5'>05</option>\n";
  if(m2_duration == 6)
    str += "<option selected value='6'>06</option>\n";
  else
    str += "<option value='6'>06</option>\n";
  if(m2_duration == 7)
    str += "<option selected value='7'>07</option>\n";
  else
    str += "<option value='7>07</option>\n";
  if(m2_duration == 8)
    str += "<option selected value='8'>08</option>\n";
  else
    str += "<option value='8'>08</option>\n";
  if(m2_duration == 9)
    str += "<option selected value='9'>09</option>\n";
  else
    str += "<option value='9'>09</option>\n";
  if(m2_duration == 10)
    str += "<option selected value='10'>10</option>\n";
  else
    str += "<option value='10'>10</option>\n";
  str += "</select>\n";
  
  str += "<br><br> <input type='submit' value='Submit'>\n";
  str += "</form> </body> </html>";

  return str;
}

void handleRoot()
{
  server.send(200, "text/html", sendHTML());
}

void setup() {
  Serial.begin(115200);
  delay(10);

  pinMode(KEY_MOTOR1,INPUT_PULLUP); 
  pinMode(KEY_MOTOR2,INPUT_PULLUP); 
  pinMode(KEY_LED,INPUT_PULLUP); 
  pinMode(OUT_MOTOR1,OUTPUT); 
  pinMode(OUT_MOTOR2,OUTPUT); 
  pinMode(OUT_LED,OUTPUT); 
  
  SPI.begin();
  
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

  server.on("/", handleRoot);
  server.on("/params", [](){
    String s_en_led = server.arg("EnLedAuto");  
    if (s_en_led == "true")
      en_led_auto = 1;
    else
      en_led_auto = 0;     
      
    String s_led_on_hour = server.arg("LedOnHour"); 
    String s_led_on_min = server.arg("LedOnMin"); 
    String s_led_off_hour = server.arg("LedOffHour"); 
    String s_led_off_min = server.arg("LedOffMin"); 
    led_on_hour = s_led_on_hour.toInt();  
    led_on_min = s_led_on_min.toInt();  
    led_off_hour = s_led_off_hour.toInt();  
    led_off_min = s_led_off_min.toInt();  

    led_on_time = led_on_hour * 3600 + led_on_min * 10 * 60;
    led_off_time = led_off_hour * 3600 + led_off_min * 10 * 60;
    
    String s_en_m1 = server.arg("EnM1");  
    if (s_en_m1 == "true")
      en_auto_m1 = 1;
    else
      en_auto_m1 = 0;     
      
    String s_en_m2 = server.arg("EnM2");  
    if (s_en_m2 == "true")
      en_auto_m2 = 1;
    else
      en_auto_m2 = 0;     
    
    String s_m_on_hour = server.arg("MotorOnHour"); 
    String s_m_on_min = server.arg("MotorOnMin"); 
    String s_m1_duration = server.arg("M1Duration"); 
    String s_m2_duration = server.arg("M2Duration"); 
    
    motor_on_hour = s_m_on_hour.toInt();  
    motor_on_min = s_m_on_min.toInt();  
    m1_duration = s_m1_duration.toInt(); 
    m2_duration = s_m2_duration.toInt(); 
    
    motor_on_time = motor_on_hour * 3600 + motor_on_min *10 * 60;
    m1_off_time = motor_on_time + m1_duration;
    m2_off_time = motor_on_time + m2_duration;
    
#if DEBUG    
    Serial.println(en_led_auto);
    Serial.println(led_on_hour);
    Serial.println(led_on_min);
    Serial.println(led_off_hour);
    Serial.println(led_off_min);
    Serial.println(en_auto_m1);
    Serial.println(en_auto_m2);
    Serial.println(motor_on_hour);
    Serial.println(motor_on_min);
    Serial.println(m1_off_time);
    Serial.println(m2_off_time);
#endif    
    server.send(200, "text/plain", "OK!");  
  });
  
  server.begin();
  
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
  
  key_motor1 = digitalRead(KEY_MOTOR1);
  key_motor2 = digitalRead(KEY_MOTOR2);
  key_led = digitalRead(KEY_LED);
  
  if (key_led_old != key_led)
  {
    delay(20);
    key_led = digitalRead(KEY_LED);
    if (key_led_old != key_led)
    {
      key_led_old = key_led;
      if (!key_led)
      {
        led_on = ~led_on;
        en_led_auto_block = 1;
      }
    }
  }
  if (led_on)
    digitalWrite(OUT_LED, 1);
  else
    digitalWrite(OUT_LED, 0);
  
  if(!m1_on)
    digitalWrite(OUT_MOTOR1, !key_motor1);
  if(!m2_on)  
    digitalWrite(OUT_MOTOR2, !key_motor2);
  
  tcnt++;

  if(tcnt > 100){
    timeClient.update();
    int curHours = timeClient.getHours();
    int curMinutes = timeClient.getMinutes();
    int curSeconds = timeClient.getSeconds();
    int cur_time = curHours*3600 + curMinutes*60 + curSeconds;
    int tmp = curHours/10;

#if DEBUG
    Serial.println(curHours);
    Serial.println(curMinutes);
    Serial.println(curSeconds);
#endif    

    if(tmp == 0)
      tmbuf[0] = 10;
    else
      tmbuf[0] = tmp;
    tmbuf[1] = curHours-tmp*10;
    tmbuf[2] = curMinutes/10;
    tmbuf[3] = curMinutes-tmbuf[2]*10;
    
    for(int i = 0; i<sizeof(tmbuf); i++)
      SPI.transfer(tmbuf[i]);

    if(en_auto_m1)
    {
      if((cur_time >= motor_on_time)&&(cur_time < m1_off_time))
      {
        m1_on = 1;
        digitalWrite(OUT_MOTOR1, 1);
      }
      else
      {
        m1_on = 0;
        digitalWrite(OUT_MOTOR1, 0);
      }
    }

    if(en_auto_m2)
    {
      if((cur_time >= motor_on_time)&&(cur_time < m2_off_time))
      {
        m2_on = 1;
        digitalWrite(OUT_MOTOR2, 1);
      }
      else
      {
        m2_on = 0;
        digitalWrite(OUT_MOTOR2, 0);
      }
    }

    if((cur_time >= 0)&&(cur_time < 10)) // reset blocking of led_auto
      en_led_auto_block = 0;
    
    if(en_led_auto && !en_led_auto_block)
    {
      if((cur_time >= led_on_time)&&(cur_time < led_off_time))
      {
        led_on = 1;
        digitalWrite(OUT_LED, 1);
      }
      else
      {
        led_on = 0;
        digitalWrite(OUT_LED, 0);     
      }
    }
       
    tcnt = 0;
  }
  delay(10);
}
