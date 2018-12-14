#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <WiFiClient.h>
#include <IPAddress.h>
#include <Udp.h>

#define UDP_PORT          55555

IPAddress ip(192, 168, 0, 105);
IPAddress broadcastIp(192, 168, 0, 255);
IPAddress netmask(255, 255, 255, 0);

WiFiUDP udp;

const char *ssid = "citolin";
const char *password = "jirafo@1966";

char buff[100];

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  udp.begin(UDP_PORT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //udp.beginPacket(broadcastIp, UDP_PORT);
  //udp.write("hello");
  //udp.endPacket();

  
  memset(buff, '\0', sizeof(buff));
  int packet_size = udp.parsePacket();
  if(packet_size)
  {
    uint8_t bytes_received = udp.read(buff, sizeof(buff));
    if(bytes_received!=0)
    {
      Serial.printf("Received broadcast of size %d bytes:\n\t%s\nSERVER is on IP: %s\n", bytes_received, buff, udp.remoteIP().toString().c_str());
    }
  }

}
