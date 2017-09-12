#include "HaLakeKit.h"

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

void HaLakeKit::begin() {
  pinMode(HALAKE_KIT_SWITCH_PIN, INPUT);

  // Arduino initializations
  Wire.begin(4, 14);
  delay(40);

  I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_2000_DPS);
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_16_G);

  // trun on magnetometer
  I2CwriteByte(MPU9250_ADDRESS, 0x37, 0x02);
  delay(10);

  mag_read_adjust_values();
  mag_set_mode(AK8963_MODE_POWERDOWN);
  mag_set_mode(AK8963_MODE_CONTINUOUS_8HZ);
}

void HaLakeKit::accel_update() {
  I2Cread(MPU9250_ADDRESS, 0x3B, 14, accel_buf);
}

float HaLakeKit::accel_get(int highIndex, int lowIndex) {
  int16_t v = -(accel_buf[highIndex]<<8 | accel_buf[lowIndex]);
  return ((float)v) * 16.0/32768.0;
}

float HaLakeKit::accel_x() {
  accel_update();
  return accel_get(0, 1);
}

float HaLakeKit::accel_y() {
  accel_update();
  return accel_get(2, 3);
}

float HaLakeKit::accel_z() {
  accel_update();
  return accel_get(4, 5);
}

float HaLakeKit::accel_comp() {
  accel_update();
  return sqrt(pow(accel_get(0, 1), 2) +
    pow(accel_get(2, 3), 2) +
    pow(accel_get(4, 5), 2));
}

void HaLakeKit::accel_print_xyz() {
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

bool HaLakeKit::switch_pushed() {
  return HIGH == digitalRead(HALAKE_KIT_SWITCH_PIN) ? false : true;
}

void HaLakeKit::mag_set_mode(uint8_t mode) {
  I2CwriteByte(MAG_ADDRESS, AK8963_RA_CNTL1, mode);
  delay(10);
}

const float Pi = 3.14159;

float HaLakeKit::mag_horiz_direction() {
  return atan2((float) mag_x(), (float) mag_y()) * 180 / Pi;
}

void HaLakeKit::mag_update() {
  I2Cread(MAG_ADDRESS, AK8963_RA_HXL, 7, mag_buf);
}

int16_t HaLakeKit::mag_get(uint8_t high_index, uint8_t low_index) {
  return (((int16_t)mag_buf[high_index]) << 8) | mag_buf[low_index];
}

uint16_t adjust_mag_value(int16_t value, uint8_t adjust) {
  return (value * ((((adjust - 128) * 0.5) / 128) + 1));
}

int16_t HaLakeKit::mag_x() {
  return adjust_mag_value(mag_get(1, 0), mag_x_adjust) + mag_x_offset;
}

int16_t HaLakeKit::mag_y() {
  return adjust_mag_value(mag_get(3, 2), mag_y_adjust) + mag_y_offset;
}

int16_t HaLakeKit::mag_z() {
  return adjust_mag_value(mag_get(5, 4), mag_z_adjust) + mag_z_offset;
}

void HaLakeKit::mag_read_adjust_values() {
  mag_set_mode(AK8963_MODE_POWERDOWN);
  mag_set_mode(AK8963_MODE_FUSEROM);
  uint8_t buff[3];
  I2Cread(MAG_ADDRESS, AK8963_RA_ASAX, 3, buff);
  mag_x_adjust = buff[0];
  mag_y_adjust = buff[1];
  mag_z_adjust = buff[2];
}
