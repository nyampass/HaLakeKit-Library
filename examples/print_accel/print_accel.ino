#include <HalakeKit.h>

HalakeKit halake_kit;

void setup() {
  Serial.begin(115200);
}

void loop() {
  delay(100);
  Serial.println("print xyz and comp");
  Serial.println(halake_kit.accel_x());
  Serial.println(halake_kit.accel_y());
  Serial.println(halake_kit.accel_z());
  Serial.println(halake_kit.accel_comp());

  halake_kit.accel_print_xyz();
}
