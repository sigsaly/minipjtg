#include <ESP8266WiFi.h>
#include <Servo.h>

#define ND_D0 16
#define ND_D1 5
#define ND_D2 4
#define ND_D3 0
#define ND_D4 2
#define ND_D5 14
#define ND_D6 12
#define ND_D7 13
#define ND_D8 15
#define ND_RX 3
#define ND_TX 1

const char* ssid = "****";
const char* password = "****";

WiFiServer server(80);
Servo servo0, servo1;
String servoNum, servoPos;

void setup() {
  Serial.begin(115200);
  servo0.attach(ND_D0);
  servo0.write(90);
  servo1.attach(ND_D1);
  servo1.write(90);  
     
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();
  if(!client) return;
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  String request = client.readStringUntil('\r');
  Serial.println("request: ");
  Serial.println(request);
  client.flush();
   
  while(client.available()) {
     client.read();
  }

  if(request.indexOf("/num=") >= 0) {
    int pos1 = request.indexOf("/num=");
    int pos2 = request.indexOf(',');  
    servoNum = request.substring(pos1+5, pos2);
  }
    
  if(request.indexOf("pos=") >= 0) {
    int pos1 = request.indexOf("pos=");
    int pos2 = request.indexOf('d');   
    servoPos = request.substring(pos1+4, pos2);

    if(servoNum.toInt()==0)
      servo0.write(servoPos.toInt());
    else
      servo1.write(servoPos.toInt());   
  }
  Serial.println(servoNum);
  Serial.println(servoPos);
  client.print("<!DOCTYPE html>");
  client.print("<html>");
  client.print("<head>");
  client.print("<meta charset=\"UTF-8\">");
  client.print("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
  client.print("</head>");
  client.print("<body>");
  client.print("<h2>Servo Control Page</h2>");
  client.print("Servo 0 : <span id=\"servo0Text\">90</span>");
  client.print("<br>");
  client.print("<input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider0\" onchange=\"servoWrite(0,this.value)\">");
  client.print("<br>");
  client.print("Servo 1 : <span id=\"servo1Text\">90</span>");
  client.print("<br>");
  client.print("<input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider1\" onchange=\"servoWrite(1,this.value)\">");
  client.print("<br>");  
  client.print("<script>");
  client.print("var slider0 = document.getElementById(\"servoSlider0\");");
  client.print("var servoPos0 = document.getElementById(\"servo0Text\");");
  client.print("var slider1 = document.getElementById(\"servoSlider1\");");
  client.print("var servoPos1 = document.getElementById(\"servo1Text\");");
  client.print("slider0.oninput = function() {");
  client.print("slider0.value = this.value;");
  client.print("servoPos0.innerHTML = this.value;}");
  client.print("\n");    
  client.print("slider1.oninput = function() {");
  client.print("slider1.value = this.value;");
  client.print("servoPos1.innerHTML = this.value;}");
  client.print("\n");  
  client.print("$.ajaxSetup({timeout:1000});");
  client.print("function servoWrite(num,pos) {");
  client.print("$.get(\"/num=\" + num + \",\" + \"pos=\" + pos + \"d\");");
  client.print("{Connection: close};");
  client.print("}");
  client.print("</script>");  
  client.print("</body>");
  client.print("</html>");
  
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}