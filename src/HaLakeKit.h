// reference: https://gist.github.com/tnoborio/ce93328f84efd00afe448ce832d0c3dd
#ifndef HaLakeKit_h
#define HaLakeKit_h
#include <Arduino.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

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

#define AK8963_RA_HXL                   0x03
#define AK8963_RA_CNTL1                 0x0A
#define AK8963_RA_ASAX                  0x10

#define AK8963_MODE_POWERDOWN           0x0
#define AK8963_MODE_SINGLE              0x1
#define AK8963_MODE_CONTINUOUS_8HZ      0x2
#define AK8963_MODE_EXTERNAL            0x4
#define AK8963_MODE_CONTINUOUS_100HZ    0x6
#define AK8963_MODE_SELFTEST            0x8
#define AK8963_MODE_FUSEROM             0xF

#define HALAKE_KIT_SWITCH_PIN    3

class HaLakeKit {
  public:
  int16_t mag_x_offset, mag_y_offset, mag_z_offset;

  HaLakeKit():
    mag_x_offset(0),
    mag_y_offset(0),
    mag_z_offset(0) {};
  void begin();
  float accel_x();
  float accel_y();
  float accel_z();
  float accel_comp();
  void accel_print_xyz();
  bool switch_pushed();

  void mag_update();
  int16_t mag_x();
  int16_t mag_y();
  int16_t mag_z();
  void mag_set_mode(uint8_t mode);
  float mag_horiz_direction();
  float temperature();

  void httpServer(char *ssid, char *pass, std::function<void()> handle);
  void httpSend(String html);
  void httpLoop();

  private:
  uint8_t accel_buf[14];
  uint8_t mag_buf[7];
  uint8_t temp_buf[2];
  uint8_t mag_x_adjust, mag_y_adjust, mag_z_adjust;
  void mag_read_adjust_values();
  float accel_get(int high_index, int low_index);
  int16_t mag_get(uint8_t high_index, uint8_t low_index);
  void accel_update();
  void wifiClient(char *ssid, char * pass);
};

#endif
