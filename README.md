### pmledctrlr
# Arduino Pro Mini LED Controller

I needed a small LED controller for lighting up a project.  I designed this to have a simple single button configuration interface.

```
/*
 *  WS2812b LED Controller with single button interface
 *
 *  Hold button for 1000ms to cycle through states
 *  Onboard LED blinks to indicate selected state
 *
 *  State 1: LED Effect
 *      click           = Next LED Effect
 *      double_click    = Previous LED Effect
 *
 *  State 2: Brightness
 *      click           = Increase Brightness
 *      double_click    = Decrease Brightness
 *
 *  State 3: Speed
 *      click           = Increase Speed
 *      double_click    = Decrease Speed
 *
 *  State 4: Color
 *      click           = Increment Color + 20
 *      double_click    = Decrement Color - 1
 *
 *  State 5: Length Add
 *      click           = Add 1 LED
 *      double_click    = Add 10 LEDs
 *
 *  State 6: Length Delete
 *      click           = Delete 1 LED
 *      double_click    = Delete 10 LED
 *
 *  Hold button for 5000ms to save settings to EEPROM
 */
 ```


 ## Parts List

 Qty|Part
 ---|----
 1|[Arduino Pro Mini 5V 16Mhz](https://www.aliexpress.com/wholesale?SearchText=Arduino+Pro+Mini+5V+16Mhz)
 1|[WS2812b LED Strip](https://www.aliexpress.com/wholesale?SearchText=WS2812b+LED+Strip)
 2|[18650 Battery](https://www.aliexpress.com/wholesale?SearchText=18650+Battery)
 2|[18650 Single Battery Holder with Wire Leads](https://www.aliexpress.com/wholesale?SearchText=18650+Single+Battery+Holder+Wire)
  1|[6x6x5MM 4PIN G90 Tactile Tact Push Button Micro Switch](https://www.aliexpress.com/wholesale?SearchText=6x6x5MM+4PIN+G90+Tactile+Push+Button+Micro+Switch) (Configuration Switch)
 1|[8.5mm x 8.5mm Tactile Power Micro Switch Self Lock On/Off](https://www.aliexpress.com/wholesale?SearchText=8.5mm+push+on+push+off+switch+tactile+power+micro) (Power Switch)
 1|[1000uf 10v Electrolytic Capacitor](https://www.aliexpress.com/wholesale?SearchText=1000uf+10v+electrolytic+capacitor)
 1|[470 ohm 1/4w metal film resistor](https://www.aliexpress.com/wholesale?SearchText=470+ohm+1%2F4w+resistor+metal+film)
 1|[100k ohm 1/4w metal film resistor](https://www.aliexpress.com/wholesale?SearchText=100k+ohm+1%2F4w+resistor+metal+film)




 I used the really awesome [WS2812FX](https://github.com/kitesurfer1404/WS2812FX) and [OneButton](https://github.com/mathertel/OneButton) libraries with a few adjustments.

 Effects
-------

* **Static** - No blinking. Just plain old static light.
* **Blink** - Normal blinking. 50% on/off time.
* **Breath** - Does the "standby-breathing" of well known i-Devices. Fixed Speed.
* **Color Wipe** - Lights all LEDs after each other up. Then turns them in that order off. Repeat.
* **Color Wipe Random** - Turns all LEDs after each other to a random color. Then starts over with another color.
* **Random Color** - Lights all LEDs in one random color up. Then switches them to the next random color.
* **Single Dynamic** - Lights every LED in a random color. Changes one random LED after the other to another random color.
* **Multi Dynamic** - Lights every LED in a random color. Changes all LED at the same time to new random colors.
* **Rainbow** - Cycles all LEDs at once through a rainbow.
* **Rainbow Cycle** - Cycles a rainbow over the entire string of LEDs.
* **Scan** - Runs a single pixel back and forth.
* **Dual Scan** - Runs two pixel back and forth in opposite directions.
* **Fade** - Fades the LEDs on and (almost) off again.
* **Theater Chase** - Theatre-style crawling lights. Inspired by the Adafruit examples.
* **Theater Chase Rainbow** - Theatre-style crawling lights with rainbow effect. Inspired by the Adafruit examples.
* **Running Lights** - Running lights effect with smooth sine transition.
* **Twinkle** - Blink several LEDs on, reset, repeat.
* **Twinkle Random** - Blink several LEDs in random colors on, reset, repeat.
* **Twinkle Fade** - Blink several LEDs on, fading out.
* **Twinkle Fade Random** - Blink several LEDs in random colors on, fading out.
* **Sparkle** - Blinks one LED at a time.
* **Flash Sparkle** - Lights all LEDs in the selected color. Flashes single white pixels randomly.
* **Hyper Sparkle** - Like flash sparkle. With more flash.
* **Strobe** - Classic Strobe effect.
* **Strobe Rainbow** - Classic Strobe effect. Cycling through the rainbow.
* **Multi Strobe** - Strobe effect with different strobe count and pause, controled by speed setting.
* **Blink Rainbow** - Classic Blink effect. Cycling through the rainbow.
* **Chase White** - Color running on white.
* **Chase Color** - White running on color.
* **Chase Random** - White running followed by random color.
* **Chase Rainbow** - White running on rainbow.
* **Chase Flash** - White flashes running on color.
* **Chase Flash Random** - White flashes running, followed by random color.
* **Chase Rainbow White** - Rainbow running on white.
* **Chase Blackout** - Black running on color.
* **Chase Blackout Rainbow** - Black running on rainbow.
* **Color Sweep Random** - Random color intruduced alternating from start and end of strip.
* **Running Color** - Alternating color/white pixels running.
* **Running Red Blue** - Alternating red/blue pixels running.
* **Running Random** - Random colored pixels running.
* **Larson Scanner** - K.I.T.T.
* **Comet** - Fireing comets from one end.
* **Fireworks** - Firework sparks.
* **Fireworks Random** - Random colored firework sparks.
* **Merry Christmas** - Alternating green/red pixels running.
* **Fire Flicker** - Fire flickering effect. Like in harsh wind.
* **Fire Flicker (soft)** - Fire flickering effect. Runs slower/softer.
