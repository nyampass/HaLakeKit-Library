#include <HaLakeKit.h>

HaLakeKit halakekit;

void setup() {
  Serial.begin(115200);
  halakekit.begin();

  // you can set your own offset for mag values
  // halakekit.mag_x_offset = -50;
  // halakekit.mag_y_offset = -55;
  // halakekit.mag_z_offset = -10;
}

void loop() {
  halakekit.mag_update();
  Serial.println("print mag values");
  Serial.println("mag_x: " + String(halakekit.mag_x()));
  Serial.println("max_y: " + String(halakekit.mag_y()));
  Serial.println("mag_z: " + String(halakekit.mag_z()));
  Serial.println("horizontal direction: " + String(halakekit.mag_horiz_direction()));

  Serial.println("at " + String(millis()) + "ms");
  delay(500);
}
