//#include <ESP8266WiFi.h>
#include <DNSServer.h>
//#include <ESP8266WebServer.h>
#include <WiFi.h>
#include <WebServer.h> 
const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;
WebServer webServer(80);

String responseHTML = "<html>"
                      "<body><p>hello</p><form>"
                      "    <label for='wifi_ssid'>WiFi SSID:</label><br>"
                       "   <input type='text' id='wifi_ssid' name='wifi_ssid'><br>"
                        "  <label for='wifi_password'>WiFi Password:</label><br>"
                         " <input type='password' id='wifi_password' name='wifi_passwod'><br>"
                          "<button id='b_submit'>Submit</button>"
                      "</form><body><html>";

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP("DNSServer CaptivePortal example");

  // if DNSServer is started with "*" for domain name, it will reply with
  // provided IP to all DNS request
  dnsServer.start(DNS_PORT, "*", apIP);

  // replay to all requests with same HTML
  webServer.onNotFound([]() {
    webServer.send(200, "text/html", responseHTML);
  });
  webServer.begin();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();
}