#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#define MIN_OUT_POWER 200
#define MAX_OUT_POWER 1024

#define MAX_ACCESS_PER_SEC 60

const char *ssid = "";
const char *password = "";

ESP8266WebServer server ( 80 );

int last_managed_sec = 0;
int current_time_sec = 0;

int post_count_per_sec = 0;

void setup() {
  Serial.begin(115200);

  WiFi.begin ( ssid, password );
  Serial.println ( "" );

  // Wait for connection
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  Serial.print ( "IP address: " );
  Serial.println ( WiFi.localIP() );

  if ( MDNS.begin ( "esp8266" ) ) {
    Serial.println ( "MDNS responder started" );
  }

  server.on ( "/", handleRoot );
  server.begin();
  Serial.println ( "HTTP server started" );

  pinMode(15, OUTPUT);
}

void loop() {
  current_time_sec = millis() / 1000;
  
  server.handleClient();

  if (current_time_sec != last_managed_sec) {
    last_managed_sec = current_time_sec;
    Serial.println(post_count_per_sec);
    Serial.println(power_to_out());
    analogWrite(15, power_to_out());
    post_count_per_sec = 0;
  }
}

void handleRoot() {
  char temp[400];
  int power = 500;

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    if (server.argName ( i ) == "power") {
      power = server.arg(i).toInt();
    }
  }
  snprintf ( temp, 400,"ok");
  server.send ( 200, "text/html", temp );

  post_count_per_sec++;
}

int power_to_out() {
  int power = ( MAX_OUT_POWER - MIN_OUT_POWER ) * post_count_per_sec / MAX_ACCESS_PER_SEC;
  if (power != 0 ) {
    power += MIN_OUT_POWER;
  }
  if ( power > 1024 ) {
    power = 1024;
  }
  return power;
}
