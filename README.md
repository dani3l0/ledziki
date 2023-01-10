# ledziki

A WS2812B LED strip controller with many colors, <u>gradients</u> and even **animations**, everything driven with Arduino (well, actually by its cheap fake board).

Board I used: `LGT8F328` ($2 Arduino Nano fake)


## Buttons

By default 5 buttons are attached. 4 of them are used to control 2 LED strips, the last one to set PWM LEDs brightness.

|  Name | In code |  Function |
| ------------ | ------------ | ----------- |
| Strip first button | `lx_up`  | **Strip `x` brightness** <br> Click to brighten (turns off after maximum brightness was reached), hold to turn off at any brightness |
| Strip second button | `lx_dn`  | **Strip `x` mode & color** <br> Hold to change mode, click to change color <br>Modes: _color_, _gradient_, _animation_ |
| PWM output button | `bulber` | **PWM LEDs brightness** <br> Click to brighten (turns off after maximum brightness was reached), hold to turn off at any brightness |

## Libraries

Only one library is required: `FastLED`.  Version `3.5.0` builds successfully.

-----

_Built with Arduino IDE version 1.8.13_

