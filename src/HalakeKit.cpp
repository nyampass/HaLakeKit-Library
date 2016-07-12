#include "HalakeKit.h"

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data) {
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
 
  Wire.requestFrom(Address, Nbytes); 
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
}
 
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data) {
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

// Initializations
HalakeKit::HalakeKit() {
  // Arduino initializations
  Wire.begin(4, 14);
  delay(40);
  //Serial.begin(115200);

  I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_2000_DPS);
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_16_G);
  I2CwriteByte(MPU9250_ADDRESS,0x37,0x02);
  // I2CwriteByte(MAG_ADDRESS,0x0A,0x01);
  I2CwriteByte(MAG_ADDRESS,0x0A,1 << 4 || 0x02);
  delay(10);
}

void HalakeKit::accel_update() {
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, accel_buf);
}

float HalakeKit::accel_get(int highIndex, int lowIndex) {
  int16_t v = -(accel_buf[highIndex]<<8 | accel_buf[lowIndex]);
  return ((float)v) * 16.0/32768.0;
}

float HalakeKit::accel_x() {
  accel_update();
  return accel_get(0, 1);
}

float HalakeKit::accel_y() {
  accel_update();
  return accel_get(2, 3);
}

float HalakeKit::accel_z() {
  accel_update();
  return accel_get(4, 5);
}

float HalakeKit::accel_comp() {
  accel_update();
  return sqrt(pow(accel_get(0, 1), 2) +
    pow(accel_get(2, 3), 2) +
    pow(accel_get(4, 5), 2));
}

void HalakeKit::accel_print_xyz() {
  float x = accel_x();
  float y = accel_y();
  float z = accel_z();

  Serial.print(x); 
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);  
  Serial.print(": ");
  Serial.print(accel_comp());
  Serial.println();
}
