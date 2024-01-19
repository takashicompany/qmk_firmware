# This file intentionally left blank

POINTING_DEVICE_ENABLE = yes

#POINTING_DEVICE_DRIVER = analog_joystick

POINTING_DEVICE_DRIVER = custom
SRC += custom_joystick.c
ANALOG_DRIVER_REQUIRED = yes

CONSOLE_ENABLE = yes

