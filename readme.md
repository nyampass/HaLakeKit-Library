# HalakeKit-library
A library to control io of halake-kit.

https://robip.halake.com/halake-board.html

# Setup

```
cd [arduino-sketch-dir]/libraries
git clone git@github.com:nyampass/HaLakeKit-Library.git
```

If you don't want to use git, you can use with wget.

```
cd [arduino-sketch-dir]/libraries
wget https://github.com/nyampass/HaLakeKit-Library/archive/master.zip -O halakekit.zip
unzip halakekit.zip
```

# Useage

## Accel

You can get or print accel info.

```
HalakeKit halake_kit;

Serial.println(halake_kit.accel_x());
Serial.println(halake_kit.accel_y());
Serial.println(halake_kit.accel_z());
Serial.println(halake_kit.accel_comp());

halake_kit.accel_print_xyz();
```

## Switch

You can get switch info about pushed or not.

```
HalakeKit halake_kit;

if ( halake_kit.switch_pushed() ) {
  // do something
}
```

# License

MIT
