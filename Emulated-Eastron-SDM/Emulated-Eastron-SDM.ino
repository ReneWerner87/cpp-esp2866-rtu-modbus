//#include <ESP8266WiFi.h>
//#include <PubSubClient.h>
#include <SoftwareSerial.h>
#include <ModbusRTU.h>
// #include "private.h"

SoftwareSerial S(RX, TX);  // we need one serial port for communicating with RS 485 to TTL adapter

#define SLAVE_ID 2

ModbusRTU mb;

//WiFiClient espClient;
//PubSubClient client(espClient);
//long lastMsg = 0;

// **************************************************
void setup() {
  Serial.begin(9600);

//  setup_wifi();
//  client.setServer(mqtt_server, 1883);
//  client.setCallback(callback);

  S.begin(9600, SWSERIAL_8N1);  // software serial attached to the MAX485 module
  mb.begin(&S, D0);             // RE/DE connected to D0 of ESP8266

  mb.slave(SLAVE_ID);

  mb.addHreg(12);
  mb.Hreg(12, 1111);

  mb.addHreg(13);
  mb.Hreg(13, 2222);
}

// **************************************************
//void setup_wifi() {
//  delay(10);
//  // We start by connecting to a WiFi network
//  Serial.println();
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//
//  WiFi.begin(ssid, password);
//
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//
//  Serial.println("");
//  Serial.println("WiFi connected");
//  Serial.println("IP address: ");
//  Serial.println(WiFi.localIP());
//}

// **************************************************
// steps to take when a power value is recieved via MQTT

//void callback(char* topic, byte* message, unsigned int length) {
//  Serial.print("Message arrived on topic: ");
//  Serial.print(topic);
//  Serial.print(": ");
//
//  // convert each byte to a char and build a string containing the mqtt message
//  String messageTemp;
//  for (int i = 0; i < length; i++) {
//    // Serial.print((char)message[i]);
//    messageTemp += (char)message[i];
//  }
//  Serial.println(messageTemp);  // print the topic message (it's a string at this point)
//
//  // convert the stirng (messageTemp) to an integer. I'm ignoring the fractional part so 123.456 will return 123
//  int power_in_watts;
//  const char* string1 = messageTemp.c_str();
//  power_in_watts = atoi(string1);
//  Serial.printf("Converted to int: %d \n", power_in_watts);
//
//  // update the Active power Watts (integer part)
//  mb.Ireg(4, power_in_watts);
//
//  // If a message is received on the topic shellies/shellyem-house/emeter/0/power
//  // if (String(topic) == mqtt_topic) {
//  //   //Serial.println("We have message!");
//  //   // determine is the power value is negative, ie we are exporting power to the grid
//  //   if (messageTemp == "on") {
//  //     Serial.println("on");
//  //   } else if (messageTemp == "off") {
//  //     Serial.println("off");
//  //   }
//  // }
//}

// **************************************************
//void reconnect() {
//  // Loop until we're reconnected
//  while (!client.connected()) {
//    Serial.print("Attempting MQTT connection...");
//    // Attempt to connect
//    if (client.connect(clientID, mqtt_username, mqtt_password)) {
//      Serial.println("Connected to MQTT Broker!");
//      // Subscribe
//      client.subscribe("shellies/shellyem-house/emeter/0/power");
//    } else {
//      Serial.print("failed, rc=");
//      Serial.print(client.state());
//      Serial.println(" try again in 5 seconds");
//      // Wait 5 seconds before retrying
//      delay(5000);
//    }
//  }
//}

// **************************************************
void loop() {
//  if (!client.connected()) {
//    reconnect();
//  }
//  client.loop();
  mb.task();
  yield();
}