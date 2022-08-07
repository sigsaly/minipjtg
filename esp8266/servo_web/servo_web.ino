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
#define ND_S2 10
#define ND_S3 9

#define servoPin ND_D0

const char* ssid = "";
const char* password = "";
 
WiFiServer server(80);
Servo servo;
 
void setup() {
	Serial.begin(115200);
  servo.attach(servoPin);
  servo.write(90);
     
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
 
	if(request.indexOf("/pos=") >= 0) {
		int pos1 = request.indexOf('=');
		int pos2 = request.indexOf('d');
		String servoPos = request.substring(pos1+1, pos2);
 
		//myServo.write(servoPos.toInt());
		Serial.println(servoPos); 
	}
 
	client.print("<!DOCTYPE HTML>");
	client.print("<html>");
	client.print("<head>");
	client.print("<meta charset=\"UTF-8\">");
	client.print("<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.3.1/jquery.min.js\"></script>");
	client.print("</head>");
	client.print("<body>");
	client.print("<h2>Servo Control Page</h2>");
	client.print("Servo : <span id=\"servoText\">90</span>");
	client.print("<br>");
	client.print("<input type=\"range\" style=\"width:90%;\" min=\"0\" max=\"180\" id=\"servoSlider\" onchange=\"servoWrite(this.value)\"/>");
	client.print("<script>");
	client.print("var slider = document.getElementById(\"servoSlider\");");
	client.print("var servoPos = document.getElementById(\"servoText\");");
	client.print("slider.oninput = function() {");
	client.print("slider.value = this.value;");
	client.print("servoPos.innerHTML = this.value;}");
	client.print("\n");
	client.print("$.ajaxSetup({timeout:1000});");
	client.print("function servoWrite(pos) {");
	client.print("$.get(\"/pos=\" + pos + \"d\");");
	client.print("{Connection: close};}");
	client.print("</script>");
	client.print("</body>");
	client.print("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
