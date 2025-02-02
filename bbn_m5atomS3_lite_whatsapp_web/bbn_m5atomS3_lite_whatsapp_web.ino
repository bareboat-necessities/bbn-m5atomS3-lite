/**
   @Hardware: M5AtomS3 + Atomic PoE Base
   @Platform Version: Arduino M5Stack Board Manager v2.0.9
   @Dependent Library:
   M5AtomS3: https://github.com/m5stack/M5AtomS3
   M5Unified: https://github.com/m5stack/M5Unified
   M5_Ethernet: https://github.com/m5stack/M5-Ethernet
*/

#include <M5AtomS3.h>  // M5AtomLiteS3
//#include <M5Atom.h>  // M5AtomLite

#include <SPI.h>
#include <M5_Ethernet.h>
#include <SSLClient.h>
#include <UrlEncode.h>
#include "trust_anchors.h"

#define SERVER "api.callmebot.com"

// M5AtomLiteS3
#define SCK  5
#define MISO 7
#define MOSI 8
#define CS   6

// M5AtomLite
//#define SCK  22
//#define MISO 23
//#define MOSI 33
//#define CS   19

byte mac[] = {0xDE, 0xAD, 0xBE, 0xDE, 0xCA, 0xDE};  // Host name will be WIZnetDECADE on local LAN (WIZnet + 3 last MAC octets)

EthernetServer server(80);

// Choose the analog pin to get semi-random data from for SSL
// Pick a pin that's not connected or attached to a randomish voltage source
const int rand_pin = 2; // 34 /* atom-lite */;

// Initialize the SSL client library
// We input an EthernetClient, our trust anchors, and the analog pin
EthernetClient base_client;
SSLClient ssl_client(base_client, TAs, (size_t)TAs_NUM, rand_pin);

// Variables to measure the speed
unsigned long beginMicros, endMicros;
unsigned long byteCount = 0;
bool printWebData = true;  // set to false for better speed measurement

const char settings_page[] PROGMEM = R"=====(
<!DOCTYPE HTML>
<html>
<body>
<form id="form" method="GET" action="/settings">
    Enter your phone number and generated CallMeBot API key for WhatsApp (see:
    <a target="_blank" rel="noopener noreferrer" href="https://www.callmebot.com/blog/free-api-whatsapp-messages/">the link</a>)<br>
    <br>
    <label for="phone">&nbsp;Phone number starting with + followed by country code and the rest of the number (digits only):</label><br><br>
    <input id="phone" type="text" name="phone" value="" placeholder="Phone.."><br><br>
    <br>
    <label for="api_key">&nbsp;API Key:</label><br><br>
    <input id="api_key" type="text" name="api_key" value="" placeholder="API Key.."><br><br>
    <br>
    <input id="button" type="submit" value="Submit">
</form>
)=====";

void header_page(EthernetClient client, int request_status = 200) {
  client.println("HTTP/1.1 " + String(request_status) + (request_status == 200 ? String(" OK") : String(" Not Found")));
  client.println("Content-Type: text/html");
  client.println("Connection: close");  // the connection will be closed after completion of the response
  client.print(settings_page);
  client.println();
}

void footer_page(EthernetClient client) {   // The closing lines of every page
  client.println("</body></html>");
}

void handle_OnConnect(EthernetClient client) {
  header_page(client);
  client.println("<a class=\"button button-on\" href=\"/ledOn\">LOW</a>");
  footer_page(client);
  Serial.println("Connection!\nQ: OFF");
}

void handle_ledOn(EthernetClient client) {
  header_page(client);
  client.println("<a class=\"button button-on\" href=\"/ledOff\">HIGH</a>");
  footer_page(client);
  Serial.println("Q: ON");
}

void handle_ledOff(EthernetClient client) {
  header_page(client);
  client.println("<a class=\"button button-on\" href=\"/ledOn\">LOW</a>");
  footer_page(client);
  Serial.println("Q: OFF");
}

void handle_NotFound(EthernetClient client, String url) {
  header_page(client, 400);
  client.println("<a>The path " + url + " doesn't exist</a>");
  Serial.println("Error, unrecognised path");
}

void setup() {
  M5.begin();
  Serial.begin(115200);

  Serial.println("Initializing SPI...");
  SPI.begin(SCK, MISO, MOSI, -1);
  Serial.println("Initializing ethernet...");
  Ethernet.init(CS);

  while (Ethernet.begin(mac) != 1) {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(2000);
  }

  // Check for Ethernet hardware present
  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
    Serial.println(
      "Ethernet shield was not found.  Sorry, can't run without "
      "hardware. :(");
    while (true) {
      delay(1);  // do nothing, no point running without Ethernet hardware
    }
  }
  if (Ethernet.linkStatus() == LinkOFF) {
    Serial.println("Ethernet cable is not connected.");
  }

  Serial.print("Local IP : ");
  Serial.println(Ethernet.localIP());
  Serial.print("Subnet Mask : ");
  Serial.println(Ethernet.subnetMask());
  Serial.print("Gateway IP : ");
  Serial.println(Ethernet.gatewayIP());
  Serial.print("DNS Server : ");
  Serial.println(Ethernet.dnsServerIP());

  Serial.println("Ethernet Successfully Initialized");

  // start the server
  server.begin();
  Serial.print("Server is at http://");
  Serial.println(Ethernet.localIP());
}

// +international_country_code + phone number
// Portugal +351, example: +351912345678
String phoneNumber = "REPLACE_WITH_YOUR_PHONE_NUMBER";
String apiKey = "REPLACE_WITH_API_KEY";

String message = "Test from M5 ESP32";

void loop() {
  M5.update();

  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    //Serial.println("new client");
    String url_path = "";
    String url_args = "";
    int argument_reading = 0;

    // An http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        // get arguments. note: path arguments must not have any blank spaces
        if (c == ' ' /* after GET or POST */ || c == '?') argument_reading++;
        if (argument_reading == 1 && c != ' ') url_path += c;
        if (argument_reading == 2 && c != '?') url_args += c;

        // check end of request
        if (c == '\n' && currentLineIsBlank) {
          // handle arguments
          Serial.println(url_path.c_str());
          Serial.println(url_args.c_str());
          if (url_path == "/") handle_OnConnect(client);
          else if (url_path == "/ledOn") handle_ledOn(client);
          else if (url_path == "/ledOff") handle_ledOff(client);
          else handle_NotFound(client, url_path);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(4);
    // close the connection:
    client.stop();
  }

  if (M5.BtnA.wasPressed()) {
    Serial.println("BtnA.wasPressed");
    if (ssl_client.connect(SERVER, 443)) {
      Serial.print("connected to ");
      // Make a HTTP request:
      ssl_client.println(String("GET ") + "/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message) + " HTTP/1.1");
      ssl_client.println("Host: api.callmebot.com");
      ssl_client.println("Connection: close");
      ssl_client.println();
    } else {
      // if you didn't get a connection to the server:
      Serial.println("connection failed");
    }
    beginMicros = micros();
  }

  if (ssl_client.connected()) {
    // if there are incoming bytes available
    // from the server, read them and print them:
    int len;
    while (len = ssl_client.available()) {
      if (len > 0) {
        byte buffer[80];
        if (len > 80) len = 80;
        ssl_client.read(buffer, len);
        if (printWebData) {
          Serial.write(buffer, len); // show in the serial monitor (slows some boards)
        }
        byteCount = byteCount + len;
      }
      delay(1);
    }
  }

  // if the server's disconnected, stop the ssl_client:
  if (!ssl_client.connected() && byteCount > 0) {
    endMicros = micros();
    Serial.println();
    Serial.println("disconnecting.");
    //ssl_client.stop();
    Serial.print("Received ");
    Serial.print(byteCount);
    Serial.print(" bytes in ");
    float seconds = (float)(endMicros - beginMicros) / 1000000.0;
    Serial.print(seconds, 4);
    float rate = (float)byteCount / seconds / 1000.0;
    Serial.print(", rate = ");
    Serial.print(rate);
    Serial.print(" kbytes/second");
    Serial.println();
    byteCount = 0;
  }
}
