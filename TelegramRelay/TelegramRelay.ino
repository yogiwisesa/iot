/*******************************************************************
   An example of bot that show bot action message.
*                                                                 *
*                                                                 *
*                                                                  *
   written by Vadim Sinitski
 *******************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Initialize Wifi connection to the router
const char* ssid = "Yogi AP";
const char* password = "@Merpati07";

// Initialize Telegram BOT
#define BOTtoken "1232330899:AAF3VrZjnwl8x72ubvNeXLytwQirEiBRPu0"

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int Bot_mtbs = 1000; //mean time between scan messages
long Bot_lasttime;   //last time messages' scan has been done
bool Start = false;

int ledPin0 = D3;
int ledPin1 = D4;
int ledPin2 = D5;
int ledPin3 = D9;

String stat0 = "OFF";
String stat1 = "OFF";
String stat2 = "OFF";
String stat3 = "OFF";

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

  String status = "";

   if (text == "/1_on") {
      digitalWrite(ledPin0, LOW);
      stat0 = "ON";

      status = "Status: \n\n";
      status += "RELAY 1: " + stat0 + "\n";
      status += "RELAY 2: " + stat1 + "\n";
      status += "RELAY 3: " + stat2 + "\n";
      status += "RELAY 4: " + stat3 + "\n";
      
      bot.sendMessage(chat_id, status);
      
    } else if (text =="/1_off") {
      digitalWrite(ledPin0, HIGH);
      stat0 = "OFF";

      status = "Status: \n\n";
      status += "RELAY 1: " + stat0 + "\n";
      status += "RELAY 2: " + stat1 + "\n";
      status += "RELAY 3: " + stat2 + "\n";
      status += "RELAY 4: " + stat3 + "\n";
      
      bot.sendMessage(chat_id, status);
      
    } else if (text == "/2_on") {
      digitalWrite(ledPin1, LOW);
      stat1 = "ON";

      status = "Status: \n\n";
      status += "RELAY 1: " + stat0 + "\n";
      status += "RELAY 2: " + stat1 + "\n";
      status += "RELAY 3: " + stat2 + "\n";
      status += "RELAY 4: " + stat3 + "\n";
      
      bot.sendMessage(chat_id, status);
      
    } else if (text == "/2_off") {
       digitalWrite(ledPin1, HIGH);
       stat1 = "OFF";

      status = "Status: \n\n";
      status += "RELAY 1: " + stat0 + "\n";
      status += "RELAY 2: " + stat1 + "\n";
      status += "RELAY 3: " + stat2 + "\n";
      status += "RELAY 4: " + stat3 + "\n";
      
       bot.sendMessage(chat_id, status);
       
    }  else if (text == "/3_on") {
      digitalWrite(ledPin2, LOW);
      stat2 = "ON";

      status = "Status: \n\n";
      status += "RELAY 1: " + stat0 + "\n";
      status += "RELAY 2: " + stat1 + "\n";
      status += "RELAY 3: " + stat2 + "\n";
      status += "RELAY 4: " + stat3 + "\n";
      
      bot.sendMessage(chat_id, status);
      
    } else if (text == "/3_off") {
       digitalWrite(ledPin2, HIGH);
       stat2 = "OFF";

       status = "Status: \n\n";
      status += "RELAY 1: " + stat0 + "\n";
      status += "RELAY 2: " + stat1 + "\n";
      status += "RELAY 3: " + stat2 + "\n";
      status += "RELAY 4: " + stat3 + "\n";
      
       bot.sendMessage(chat_id, status);
       
    }  else if (text == "/4_on") {
      digitalWrite(ledPin3, LOW);
      stat3 = "ON";

      status = "Status: \n\n";
      status += "RELAY 1: " + stat0 + "\n";
      status += "RELAY 2: " + stat1 + "\n";
      status += "RELAY 3: " + stat2 + "\n";
      status += "RELAY 4: " + stat3 + "\n";
      
      bot.sendMessage(chat_id, status);
      
    } else if (text == "/4_off") {
       digitalWrite(ledPin3, HIGH);
       stat3 = "OFF";

      status = "Status: \n\n";
      status += "RELAY 1: " + stat0 + "\n";
      status += "RELAY 2: " + stat1 + "\n";
      status += "RELAY 3: " + stat2 + "\n";
      status += "RELAY 4: " + stat3 + "\n";
      
       bot.sendMessage(chat_id, status);
       
    } else if (text == "/status") {
      status = "Status: \n\n";
      status += "RELAY 1: " + stat0 + "\n";
      status += "RELAY 2: " + stat1 + "\n";
      status += "RELAY 3: " + stat2 + "\n";
      status += "RELAY 4: " + stat3 + "\n";
      
      bot.sendMessage(chat_id, status);
    }


    if (text == "/send_test_action") {
      bot.sendChatAction(chat_id, "typing");
      delay(4000);
      bot.sendMessage(chat_id, "Did you see the action message?");

      // You can't use own message, just choose from one of bellow

      //typing for text messages
      //upload_photo for photos
      //record_video or upload_video for videos
      //record_audio or upload_audio for audio files
      //upload_document for general files
      //find_location for location data

      //more info here - https://core.telegram.org/bots/api#sendchataction
    }

    if (text == "/start") {
      String welcome = "Welcome to Universal Arduino Telegram Bot library, " + from_name + ".\n";
      welcome += "This is Chat Action Bot example.\n\n";
      welcome += "/send_test_action : to send test chat action message\n";
      bot.sendMessage(chat_id, welcome);
    }
  }
}


void setup() {
  client.setInsecure();


  Serial.begin(9600);
   delay(10);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  // WiFi.mode(WIFI_STA);
  // WiFi.disconnect();
  // delay(100);
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  digitalWrite(ledPin0, HIGH);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);

  // attempt to connect to Wifi network:
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
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }

    Bot_lasttime = millis();
  }
}
