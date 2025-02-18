#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>


#define LED 15
const char  *ssid = "BOORNEUSH";
const char  *password ="87654321";
unsigned char status_led=0;

WiFiServer server(80);

void setup() {
Serial.begin(115200);
pinMode(LED, OUTPUT);
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED )
{
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
server.begin();
Serial.println("Server started");
Serial.println(WiFi.localIP());
}

void loop() {
WiFiClient client = server.available();
if (!client) {
return;
}

Serial.println("new client");
while(!client.available())
{
delay(1);
}
String req = client.readStringUntil('\r');
Serial.println(req);
client.flush();
if (req.indexOf("/ledoff") != -1)
{
status_led=0;
digitalWrite(LED,LOW);
Serial.println("LED OFF");
}
else if(req.indexOf("/ledon") != -1)
{
status_led=1;
digitalWrite(LED,HIGH);
Serial.println("LED ON");
}
String web = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
web += "<html>\r\n";
web += "<body>\r\n";
 
web += "<h1>LED Status</h1>\r\n";
web += "<p>\r\n";
if(status_led==1)
web += "LED On\r\n";
else
web += "LED Off\r\n";
web += "</p>\r\n";
web += "</p>\r\n";
web += "<a href=\”/ledon\”>\r\n";
web += "<button>LED On</button >\r\n";
web += "</a>\r\n";
web += "</p>\r\n";

web += "<a href=\"/ledoff\">\r\n";
web += "<button>LED Off</button >\r\n";
web += "</a>\r\n";

web += "</body>\r\n";
web += "</html>\r\n";

client.print(web);
}
