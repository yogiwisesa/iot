#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

WiFiClientSecure client;

// TELEGRAM
#define BOTtoken "1232330899:AAF3VrZjnwl8x72ubvNeXLytwQirEiBRPu0"

UniversalTelegramBot bot(BOTtoken, client);
int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;

#define chatIdYogi "133046982"
#define chatIdBapak"1020197704"

// OUTPUT
int pin2 = D2;
int pin3 = D3;
int pin4 = D4;
int pin5 = D5;
int pin6 = D6;
int pin7 = D7;
int pin8 = D8;
int pin9 = D9;

// INPUT
int pin10 = D10;
int pin11 = D11;
int pin12 = D12;
int pin13 = D13;

// MOTION
int valMotion1;

// UTILS
int second = 1000;        // Multiply with second to get value in second
int minute = 60 * second; // Multiply with minuteto get value in minute

// WIFI
const char* ssid = "Yogi AP";
const char* password = "@Merpati07";

void setup() {
  Serial.begin(9600);
  
  Serial.println("Starting...");

  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
  pinMode(pin9, OUTPUT);
  
  digitalWrite(pin2, HIGH);
  digitalWrite(pin3, HIGH);
  digitalWrite(pin4, HIGH);
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, LOW);
  digitalWrite(pin7, LOW);
  digitalWrite(pin8, LOW);
  digitalWrite(pin9, LOW);

  // CONNECT WIFI
  client.setInsecure();
  
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  valMotion1 = digitalRead(pin10);
  Serial.println(valMotion1);
  
  if (valMotion1 == LOW) {
    //-- NO MOTION
    digitalWrite(pin5, HIGH);
    Serial.println("No motion");
   } else {
    //-- MOTION
    digitalWrite(pin5, LOW);
    Serial.println("motion");
    bot.sendMessage(chatIdYogi, "Ada Orang");
    bot.sendMessage(chatIdBapak, "Ada Orang");
    delay(3 * second);
   }

   if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("Got Message");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }

  delay(1*second);
}

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/who_am_i") {
      String message = "Chat id: " + chat_id + "\nName: " + from_name;
      bot.sendMessage(chat_id, message);
    }

    if (text == "/start") {
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Chat Action Bot example.\n\n";
      welcome += "/send_test_action : to send test chat action message\n";
      bot.sendMessage(chat_id, welcome);
    }
    
  }
  
}
