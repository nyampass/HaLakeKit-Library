// reference: https://gist.github.com/tnoborio/ce93328f84efd00afe448ce832d0c3dd
#ifndef HaLakeKit_h
#define HaLakeKit_h
#include <Arduino.h>
#include <Wire.h>

#define MPU9250_ADDRESS          0x69
#define MAG_ADDRESS              0x0C

#define GYRO_FULL_SCALE_250_DPS  0x00
#define GYRO_FULL_SCALE_500_DPS  0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G       0x00
#define ACC_FULL_SCALE_4_G       0x08
#define ACC_FULL_SCALE_8_G       0x10
#define ACC_FULL_SCALE_16_G      0x18

#define HALAKE_KIT_SWITCH_PIN    0

class HaLakeKit {
  public:
  HaLakeKit();
  void setup();
  float accel_x();
  float accel_y();
  float accel_z();
  float accel_comp();
  void accel_print_xyz();
  bool switch_pushed();

  private:
  uint8_t accel_buf[14];
  float accel_get(int highIndex, int lowIndex);
  void accel_update();
};

#endif
