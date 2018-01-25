#include <HaLakeKit.h>

HaLakeKit halakekit;

void setup() {
  Serial.begin(115200);
  halakekit.begin();
}

void loop() {
  delay(100);
  Serial.println("print temperature");
  Serial.println(halakekit.temperature());
}
