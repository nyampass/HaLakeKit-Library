#include <HaLakeKit.h>

HaLakeKit halakekit;

void setup() {
  Serial.begin(115200);
  halakekit.setup();
}

void loop() {
  delay(100);
  Serial.println("print xyz and comp");
  Serial.println(halakekit.accel_x());
  Serial.println(halakekit.accel_y());
  Serial.println(halakekit.accel_z());
  Serial.println(halakekit.accel_comp());

  halakekit.accel_print_xyz();
}
