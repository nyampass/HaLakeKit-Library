# HaLakeKit-library
A library to control io of HaLakeKit.

[![image](https://robip.halake.com/images/halake-board-description.png)](https://robip.halake.com/halake-board.html)

# Install to Arduino IDE

1. Open library manager.

  Sketch -> Include library -> Manage Libraries

2. Search "HaLakeKit" on library manager.

3. Click "Install" button.

# Useage

## Begin

Plese call begin of HaLakeKit in setup of Arduino.

```c
HaLakeKit halakekit;

void setup() {
  halakekit.begin();
}
```


## Accel

You can get or print accel info.

```c
Serial.println(halakekit.accel_x());
Serial.println(halakekit.accel_y());
Serial.println(halakekit.accel_z());
Serial.println(halakekit.accel_comp());

halakekit.accel_print_xyz();
delay(100);
```

[An Example project for accel](examples/PrintAccelerator/PrintAccelerator.ino) is available.

## Switch

You can get switch info about pushed or not.

```c
if ( halakekit.switch_pushed() ) {
  // do something
}
```

## Magnetometer

Adjust offset value like this.
```
halakekit.mag_x_offset = -50;
halakekit.mag_y_offset = -55;
// halakekit.mag_z_offset = -10;
```

You gan get or print magnetometer values.
```
halakekit.mag_update();
Serial.println("print mag values");
Serial.println("mag_x: " + String(halakekit.mag_x()));
Serial.println("max_y: " + String(halakekit.mag_y()));
Serial.println("mag_z: " + String(halakekit.mag_z()));
Serial.println("horizontal direction: " + String(halakekit.mag_horiz_direction()));
```

# License

MIT
