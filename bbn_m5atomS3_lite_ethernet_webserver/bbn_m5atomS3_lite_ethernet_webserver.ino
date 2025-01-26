/**
   based on:

   @file HTTP.ino
   @author SeanKwok (shaoxiang@m5stack.com)
   @brief M5AtomS3 Atomic PoE Base HTTP Test
   @version 0.1
   @date 2023-12-13


   @Hardware: M5AtomS3 + Atomic PoE Base
   @Platform Version: Arduino M5Stack Board Manager v2.0.9
   @Dependent Library:
   M5GFX: https://github.com/m5stack/M5GFX
   M5Unified: https://github.com/m5stack/M5Unified
   M5AtomS3: https://github.com/m5stack/M5AtomS3
   M5_Ethernet: https://github.com/m5stack/M5-Ethernet
*/

#include <M5AtomS3.h>  // M5AtomLiteS3
//#include <M5Atom.h>  // M5AtomLite

#include <Arduino.h>
#include <SPI.h>
#include <M5_Ethernet.h>
#include <WebServer.h>

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

byte mac[] = {0xDE, 0xAD, 0xBE, 0xDE, 0xCA, 0xDE};  // Host name will be WIZnetDECADE on local LAN (WIZnet + 3 last MAC octects)

EthernetServer server(80);

void header_page(EthernetClient client, int request_status = 200) {   // The first half of the common PHP file
  client.println("HTTP/1.1 " + String(request_status) + " Not found");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  // the connection will be closed after completion of the response
  client.println("Refresh: 20");  // refresh the page automatically every 5 sec
  client.println();
  client.println("<!DOCTYPE HTML>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\"><title>Control LED</title><style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}.button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}.button-on {background-color: #3498db;}.button-on:active {background-color: #2980b9;}.button-off {background-color: #34495e;}.button-off:active {background-color: #2c3e50;}p {font-size: 14px;color: #888;margin-bottom: 10px;}</style></head>");
  client.println("<html><h1>ESP32 Web Server</h1><h3>Using Station Mode</h3>");
}

void footer_page(EthernetClient client) {   // The closing lines of every page
  client.println("</html>");
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

  // start the server
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    //Serial.println("new client");
    String client_message = "";
    int argument_reading = 0;

    // An http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        // get arguments. note: path arguments must not have any blank spaces
        if (String(c) == " " || String(c) == "?") argument_reading++;
        if (argument_reading == 1 && String(c) != " ") client_message = client_message + c;

        // check end of request
        if (c == '\n' && currentLineIsBlank) {
          // Send response
          // handle arguments
          if (client_message == "/") handle_OnConnect(client);
          else if (client_message == "/ledOn") handle_ledOn(client);
          else if (client_message == "/ledOff") handle_ledOff(client);
          else handle_NotFound(client, client_message);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
          //Serial.write("We're here");
        }
      }
    }
    // give the web browser time to receive the data
    delay(4);
    // close the connection:
    client.stop();
  }
}
