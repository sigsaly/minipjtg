#include <ESP8266WiFi.h>
 
const char* ssid = "";
const char* password = "";

WiFiServer server(80);

int LED_pin = 14;
int turn_on = 0;
int turn_off = 1;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(LED_pin, OUTPUT);
  digitalWrite(LED_pin, turn_off);
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  // Match the request
  int value = turn_off;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(LED_pin, turn_on);
    value = turn_on;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(LED_pin, turn_off);
    value = turn_off;
  }
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("Led pin is now: ");

  if(value == turn_on) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />"); 
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}
