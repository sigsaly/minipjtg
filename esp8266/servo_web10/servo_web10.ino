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
Servo servo[10];
String servoNum, servoPos;

int pnum[]={ND_D0,ND_D1,ND_D2,ND_D3,ND_D4,
ND_D5,ND_D6,ND_D7,ND_D8,ND_RX};

void setup() {
  Serial.begin(115200);
  for(int i=0; i<10; i++)
  {
    servo[i].attach(pnum[i]);
    servo[i].write(90);
  }
     
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
      servo[servoNum.toInt()].write(servoPos.toInt());   
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
      servo[servoNum.toInt()].write(servoPos.toInt());   
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
  client.print("<table width = \"100%\">");
  client.print("<tbody>");
  client.print("<tr>");
  client.print("<td>Servo 0 : <span id=\"servo0Text\">90</span></td>");
  client.print("<td>Servo 1 : <span id=\"servo1Text\">90</span></td>");  
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td><input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider0\" onchange=\"servoWrite(0,this.value)\"></td>");
  client.print("<td><input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider1\" onchange=\"servoWrite(1,this.value)\"></td>");
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td><br></td><td><br></td>");
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td>Servo 2 : <span id=\"servo2Text\">90</span></td>");
  client.print("<td>Servo 3 : <span id=\"servo3Text\">90</span></td>");
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td><input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider2\" onchange=\"servoWrite(2,this.value)\"></td>");
  client.print("<td><input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider3\" onchange=\"servoWrite(3,this.value)\"></td>");
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td><br></td><td><br></td>");
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td>Servo 4 : <span id=\"servo4Text\">90</span></td>");
  client.print("<td>Servo 5 : <span id=\"servo5Text\">90</span></td>");
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td><input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider4\" onchange=\"servoWrite(4,this.value)\"></td>");
  client.print("<td><input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider5\" onchange=\"servoWrite(5,this.value)\"></td>");
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td><br></td><td><br></td>");
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td>Servo 6 : <span id=\"servo6Text\">90</span></td>");
  client.print("<td>Servo 7 : <span id=\"servo7Text\">90</span></td>");
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td><input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider6\" onchange=\"servoWrite(6,this.value)\"></td>");
  client.print("<td><input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider7\" onchange=\"servoWrite(7,this.value)\"></td>");
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td><br></td><td><br></td>");
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td>Servo 8 : <span id=\"servo8Text\">90</span></td>");
  client.print("<td>Servo 9 : <span id=\"servo9Text\">90</span></td>");
  client.print("</tr>");
  client.print("<tr>");
  client.print("<td><input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider8\" onchange=\"servoWrite(8,this.value)\"></td>");
  client.print("<td><input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider9\" onchange=\"servoWrite(9,this.value)\"></td>");
  client.print("</tr>");                  
  client.print("</tbody>");
  client.print("</table>");
  client.print("<script>");
  
  client.print("var slider0 = document.getElementById(\"servoSlider0\");");
  client.print("var slider1 = document.getElementById(\"servoSlider1\");");
  client.print("var slider2 = document.getElementById(\"servoSlider2\");");
  client.print("var slider3 = document.getElementById(\"servoSlider3\");");
  client.print("var slider4 = document.getElementById(\"servoSlider4\");");
  client.print("var slider5 = document.getElementById(\"servoSlider5\");");
  client.print("var slider6 = document.getElementById(\"servoSlider6\");");
  client.print("var slider7 = document.getElementById(\"servoSlider7\");");
  client.print("var slider8 = document.getElementById(\"servoSlider8\");");
  client.print("var slider9 = document.getElementById(\"servoSlider9\");");
  client.print("var servoPos0 = document.getElementById(\"servo0Text\");");
  client.print("var servoPos1 = document.getElementById(\"servo1Text\");");
  client.print("var servoPos2 = document.getElementById(\"servo2Text\");");
  client.print("var servoPos3 = document.getElementById(\"servo3Text\");");
  client.print("var servoPos4 = document.getElementById(\"servo4Text\");");
  client.print("var servoPos5 = document.getElementById(\"servo5Text\");");
  client.print("var servoPos6 = document.getElementById(\"servo6Text\");");
  client.print("var servoPos7 = document.getElementById(\"servo7Text\");");
  client.print("var servoPos8 = document.getElementById(\"servo8Text\");");
  client.print("var servoPos9 = document.getElementById(\"servo9Text\");");
  client.print("\n");    
  client.print("slider0.oninput = function() { ");
  client.print("slider0.value = this.value;");
  client.print("servoPos0.innerHTML = this.value;}");
  client.print("\n");
  client.print("slider1.oninput = function() { ");
  client.print("slider1.value = this.value;");
  client.print("servoPos1.innerHTML = this.value;}");
  client.print("\n");
  client.print("slider2.oninput = function() { ");
  client.print("slider2.value = this.value;");
  client.print("servoPos2.innerHTML = this.value;}");
  client.print("\n");
  client.print("slider3.oninput = function() { ");
  client.print("slider3.value = this.value;");
  client.print("servoPos3.innerHTML = this.value;}");
  client.print("\n");
  client.print("slider4.oninput = function() { ");
  client.print("slider4.value = this.value;");
  client.print("servoPos4.innerHTML = this.value;}");
  client.print("\n");
  client.print("slider5.oninput = function() { ");
  client.print("slider5.value = this.value;");
  client.print("servoPos5.innerHTML = this.value;}");
  client.print("\n");
  client.print("slider6.oninput = function() { ");
  client.print("slider6.value = this.value;");
  client.print("servoPos6.innerHTML = this.value;}");
  client.print("\n");
  client.print("slider7.oninput = function() { ");
  client.print("slider7.value = this.value;");
  client.print("servoPos7.innerHTML = this.value;}");
  client.print("\n");
  client.print("slider8.oninput = function() { ");
  client.print("slider8.value = this.value;");
  client.print("servoPos8.innerHTML = this.value;}");
  client.print("\n");
  client.print("slider9.oninput = function() { ");
  client.print("slider9.value = this.value;");
  client.print("servoPos9.innerHTML = this.value;}");
  client.print("\n");
  client.print("$.ajaxSetup({timeout:1000});");
  client.print("function servoWrite(num, pos) {");
  client.print("  $.get(\"/num=\" + num + \",\" + \"pos=\" + pos + \"d\");");
  client.print("  {Connection: close};");
  client.print("}");
  client.print("</script>");
  client.print("</body>");
  client.print("</html>");
  
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}