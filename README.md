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
 *  State 1: LED Animation
 *      click           = Next LED Animation
 *      double_click    = Previous LED Animation
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
 *  State 5: Add LED
 *      click           = Add 1 LED
 *      double_click    = Add 10 LEDs
 *
 *  State 6: Delete LED
 *      click           = Delete 1 LED
 *      double_click    = Delete 10 LED
 *
 *  Hold button for 5000ms to save settings to EEPROM
 */
 ```
 
 I used the really awesome [WS2812FX](https://github.com/kitesurfer1404/WS2812FX) and [OneButton](https://github.com/mathertel/OneButton) libraries with a few adjustments.
 
 ## Parts List
 
 Qty|Part
 ---|----
 1|[Arduino Pro Mini 5V 16Mhz](https://www.aliexpress.com/wholesale?SearchText=Arduino+Pro+Mini+5V+16Mhz)
 1|[WS2812b LED Strip](https://www.aliexpress.com/wholesale?SearchText=WS2812b+LED+Strip)
 2|[18650 Battery](https://www.aliexpress.com/wholesale?SearchText=18650+Battery)
 2|[18650 Single Battery Holder with Wire Leads](https://www.aliexpress.com/wholesale?SearchText=18650+Single+Battery+Holder+Wire)
  1|[6x6x5MM 4PIN G90 Tactile Tact Push Button Micro Switch](https://www.aliexpress.com/wholesale?SearchText=6x6x5MM+4PIN+G90+Tactile+Push+Button+Micro+Switch) (Configuration Switch)
 1|[8.5mm x 8.5mm Tactile Power Micro Switch Self Lock On/Off](https://www.aliexpress.com/wholesale?SearchText=8.5mm+push+on+push+off+switch+tactile+power+micro) (Power Switch)
 
 
