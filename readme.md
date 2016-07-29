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
float accel_x();
float accel_y();
float accel_z();
float accel_comp();
void accel_print_xyz();
```

## Switch

You can get switch info about pushed or not.

```
bool switch_pushed();
```

# License

MIT
