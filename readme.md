# HaLakeKit-library
A library to control io of halake-kit.

https://robip.halake.com/halake-board.html

# Install to Arduino IDE

1. Open library manager.

Sketch -> Include library -> Manage Libraries

2. Search "HaLakeKit" on library manager.

3. Click "Install" button.

# Useage

## Setup

Plese call setup of HaLakeKit in setup.

```
HaLakeKit halakekit;

void setup() {
  halakekit.setup();
}
```


## Accel

You can get or print accel info.

```
Serial.println(halakekit.accel_x());
Serial.println(halakekit.accel_y());
Serial.println(halakekit.accel_z());
Serial.println(halakekit.accel_comp());

halakekit.accel_print_xyz();
delay(100);
```

Example project for accel is available.

## Switch

You can get switch info about pushed or not.

```
if ( halakekit.switch_pushed() ) {
  // do something
}
```

# License

MIT
