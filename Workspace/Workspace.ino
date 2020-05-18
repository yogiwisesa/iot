#include <dht11.h>
dht11 DHT11;

#include <ESP8266WiFi.h>

const char* ssid = "Yogi AP";
const char* password = "@Merpati07";

WiFiServer server(80);

// D2 - Fan Output
int pinFan = D2;

// D3 - Light Output
int pinLight = D3;

// D4 & D5 - Battery - Always ON
int pinBattery1 = D4;
int pinBattery2 = D5;

// D6 - Motion Sensor
int pinMotion = D6;

// D7- Temperature Sensor
int pinTemperature = D7;

// D8, D9

//int motionDelay = 30 * 1000 *60;
int motionDelay = 3 * 1000 * 60;
float lastMotionDetected;

bool isOverheat;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  delay(10);
  
  pinMode(pinFan, OUTPUT);
  pinMode(pinLight, OUTPUT);
  pinMode(pinBattery1, OUTPUT);
  pinMode(pinBattery2, OUTPUT);
  
  digitalWrite(pinBattery1, LOW);
  digitalWrite(pinBattery2, LOW);

  // Connect Wifi
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
  Serial.print("Use this URL : ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  // put your main code here, to run repeatedly:
  int motion = digitalRead(pinMotion);
  if (motion == HIGH) { 
    Serial.println("Motion Detected");
    digitalWrite(pinLight, LOW);

    if (isOverheat == false) {
      digitalWrite(pinFan, LOW);
    }
    
    lastMotionDetected = millis();
  }

  if (millis() > lastMotionDetected + motionDelay) {
    digitalWrite(pinFan, HIGH);
    digitalWrite(pinLight , HIGH);
  }

  int chk = DHT11.read(pinTemperature);
  Serial.print("Temperature: ");
  Serial.println((float)DHT11.temperature, 2);
   
  isOverheat = (float)DHT11.temperature > 35;

  if (isOverheat) {
    digitalWrite(pinFan, HIGH);
  }

  float timeDown = (lastMotionDetected + motionDelay) - millis();
  Serial.print("Shutting Down: ");
  Serial.println(timeDown / 1000 / 60);

  // Local webserver
  WiFiClient client = server.available();
  if (client) {
    // Return the response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println(""); //  do not forget this one
    client.println("<!DOCTYPE HTML>");
    client.println("<html>");
   
    client.println("Fan Temperature: ");
    client.println((float)DHT11.temperature, 2);
    client.println("c");
    client.println("<br>");
    client.println("Shutting Down in: ");
    client.println(timeDown / 1000 / 60);
    client.println("m");
    client.println("</html>");
  }
  
  delay(1000);
}
