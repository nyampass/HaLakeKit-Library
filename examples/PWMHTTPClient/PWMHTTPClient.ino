#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <HaLakeKit.h>
​
#define USE_SERIAL Serial
​
String server_url    = "http://192.168.11.xx/";
const char *ssid     = "";
const char *password = "";
​
HaLakeKit halakekit;
ESP8266WiFiMulti WiFiMulti;
​
bool is_switch_on         = false;
bool current_switch_state = false;
bool prev_switch_state    = false;
unsigned long current_millisec;
unsigned long changed_to_pushed_millisec   = 0;
unsigned long changed_to_released_millisec = 0;
int switch_toggle_buffer_millisec          = 20;
​
void create_request() {
  HTTPClient http;
  Serial.println(server_url);
  http.begin(server_url);
  http.GET();
}
​
void setup() {
  Serial.begin(115200);
  halakekit.begin();
  // put your setup code here, to run once:
  WiFiMulti.addAP(ssid, password);
}
​
void loop() {
  if ((WiFiMulti.run() != WL_CONNECTED)) {
    return;
  }
​
  // update switch state
  prev_switch_state = current_switch_state;
  current_switch_state = halakekit.switch_pushed();
​
  current_millisec = millis();
  if ( current_switch_state == true ) {
    if ( prev_switch_state == false ) {
      changed_to_pushed_millisec = current_millisec;
    }
    if ( changed_to_pushed_millisec - current_millisec > switch_toggle_buffer_millisec ) {
      if ( !is_switch_on ) {
        Serial.println("Switch becomes ON");
        create_request();
        is_switch_on = true;
      }
    }
  } else { // current_switch_state == false
    if ( prev_switch_state == true ) {
      changed_to_released_millisec = current_millisec;
    }
    if ( changed_to_released_millisec - current_millisec > switch_toggle_buffer_millisec ) {
      if ( is_switch_on ) {
        Serial.println("Switch becomes OFF");
        is_switch_on = false;
      }
    }
  }
}
