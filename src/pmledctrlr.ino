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

#include <EEPROM.h>
#include <OneButton.h>
#include <WS2812FX.h>

#include <avr/pgmspace.h>

#define SerialPrintf(fmt, ...) _SerialPrintf(PSTR(fmt), ##__VA_ARGS__)

extern "C" {
    int serialputc(char c, FILE *fp)
    {
        if(c == '\n')
            Serial.write('\r');

        Serial.write(c);

        return 0;
    }
}

void _SerialPrintf(const char *fmt, ...)
{
    FILE stdiostr;
    va_list ap;

    fdev_setup_stream(&stdiostr, serialputc, NULL, _FDEV_SETUP_WRITE);

    va_start(ap, fmt);
    vfprintf_P(&stdiostr, fmt, ap);
    va_end(ap);
}

#define LED_PIN 10                       // 0 = GPIO0, 2=GPIO2
#define STATE_PIN 13

#define BRIGHTNESS_STEP 15              // in/decrease brightness by this amount per click
#define SPEED_STEP 10                   // in/decrease brightness by this amount per click
#define COUNT_STEP 10

#define CONFIG_VERSION "1.03"
#define CONFIG_START 0
#define CONFIG_SAVE_TRIGGER 5000

#define CONFIG_EFFECT 0
#define CONFIG_BRIGHTNESS 1
#define CONFIG_SPEED 2
#define CONFIG_COLOR 3
#define CONFIG_LENGTH_ADD 4
#define CONFIG_LENGTH_DEL 5

char *stateName[] = { "effect", "brightness",  "speed", "color", "length_add", "length_del"};

int state = CONFIG_EFFECT;
bool event_triggered = true;
int event_blink = 0;

struct objConfig {
    char version[5];
    int effect;
    int brightness;
    int speed;
    uint8_t color;
    uint16_t length;
} config = {
    CONFIG_VERSION,
    FX_MODE_STATIC,
    127,
    200,
    200,
    25
};

// Setup a new OneButton on pin A1.
OneButton button(A1, true);

WS2812FX ws2812fx = WS2812FX(config.length, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup(){
    Serial.begin(115200);
    Serial.println();
    Serial.println();

    loadSettings();
    SerialPrintf("PMLEDCTRLR v%s\n", config.version);

    Serial.println("Controls setup");
    // enable the standard led on pin 13.
    pinMode(STATE_PIN, OUTPUT);      // sets the digital pin as output

    // link the myClickFunction function to be called on a click event.
    button.attachClick(myClickFunction);

    // link the doubleclick function to be called on a doubleclick event.
    button.attachDoubleClick(myDoubleClickFunction);

    // link the doubleclick function to be called on a doubleclick event.
    button.attachLongPressStart(myLongPressStartFunction);
    button.attachLongPressStop(myLongPressStopFunction);

    // set 80 msec. debouncing time. Default is 50 msec.
    button.setDebounceTicks(80);

    Serial.println("WS2812FX setup");
    ws2812fx.init();
    ws2812fx.setMode(config.effect);
    ws2812fx.setBrightness(config.brightness);
    ws2812fx.setSpeed(config.speed);
    ws2812fx.setColor(config.color);
    ws2812fx.start();

    SerialPrintf("Ready!\n\n");
}


void loop() {
    //unsigned long now = millis();

    // keep watching the push button:
    button.tick();

    // report event
    if ( event_triggered ) {
        config.effect = ws2812fx.getMode();
        SerialPrintf("state: %d, [%s]\teffect: %d, [%s]\tpressed_ticks: %d\n",
                        state+1,
                        stateName[state],
                        config.effect,
                        ws2812fx.getModeName(config.effect),
                        button.getPressedTicks()
                    );

        config.brightness = ws2812fx.getBrightness();
        config.speed = ws2812fx.getSpeed();
        config.length = ws2812fx.getLength();

        SerialPrintf("brightness: %d, speed: %d, color: %d, length: %d\n\n",
                        config.brightness,
                        config.speed,
                        config.color,
                        config.length
                    );

        event_triggered = false;

        // blink led
        if ( event_blink ) {
            for(int i; i<state+1; i++) {
                digitalWrite(STATE_PIN, HIGH);
                delay(event_blink);
                digitalWrite(STATE_PIN, LOW);
                delay(event_blink);
            }
            event_blink = 0;
        }

        // save settings on CONFIG_SAVE_TRIGGER
        if ( button.getPressedTicks() > CONFIG_SAVE_TRIGGER ) {
            saveSettings();
            for(int i; i<15; i++) {
                digitalWrite(STATE_PIN, HIGH);
                delay(50);
                digitalWrite(STATE_PIN, LOW);
                delay(50);
            }
            button.reset();
        }
    }

    ws2812fx.service();
}

void loadSettings() {

    // To make sure there are settings, and they are YOURS!
    // If nothing is found it will use the default settings.
    if (EEPROM.read(CONFIG_START + 0) == CONFIG_VERSION[0] &&
        EEPROM.read(CONFIG_START + 1) == CONFIG_VERSION[1] &&
        EEPROM.read(CONFIG_START + 2) == CONFIG_VERSION[2] &&
        EEPROM.read(CONFIG_START + 3) == CONFIG_VERSION[3]) {

        for (unsigned int t=0; t<sizeof(config); t++)
            *((char*)&config + t) = EEPROM.read(CONFIG_START + t);

        ws2812fx.setMode(config.effect);
        ws2812fx.setBrightness(config.brightness);
        ws2812fx.setSpeed(config.speed);
        ws2812fx.setColor(ws2812fx.color_wheel(config.color));
        ws2812fx.setLength(config.length);
    }

}

void saveSettings() {
    SerialPrintf("event: save_settings\n");

    for (unsigned int t=0; t<sizeof(config); t++)
        EEPROM.write(CONFIG_START + t, *((char*)&config + t));

    event_triggered = true;
}

// this function will be called when the button is long pressed
void myLongPressStartFunction() {
    state++;
    if ( state > 5 )
        state = 0;

    SerialPrintf("event: long_press_start\n");
    event_triggered = true;
    event_blink = 200;
}

void myLongPressStopFunction() {
    SerialPrintf("event: long_press_stop\n");
    event_triggered = true;
}

// this function will be called when the button is pressed 1 time and them some time has passed.
void myClickFunction() {
    if ( state == CONFIG_EFFECT )
    {
        // Next Effect
        ws2812fx.setMode((ws2812fx.getMode() + 1) % ws2812fx.getModeCount());
    }
    else if ( state == CONFIG_BRIGHTNESS )
    {
        // Increase Brightness
        ws2812fx.increaseBrightness(BRIGHTNESS_STEP);
    }
    else if ( state == CONFIG_SPEED )
    {
        // Increase Speed
        ws2812fx.increaseSpeed(SPEED_STEP);
    }
    else if ( state == CONFIG_COLOR )
    {
        uint32_t color_code;

        // Increase Color
        config.color = config.color + 20;
        color_code = ws2812fx.color_wheel(config.color);
        ws2812fx.setColor(color_code);
    }
    else if ( state == CONFIG_LENGTH_ADD )
    {
        // Increase Length
        ws2812fx.increaseLength(1);
    }
    else if ( state == CONFIG_LENGTH_DEL )
    {
        // Decrease Length
        ws2812fx.decreaseLength(1);
    }

    SerialPrintf("event: click\n");
    event_triggered = true;
} // myClickFunction


// this function will be called when the button is pressed 2 times in a short timeframe.
void myDoubleClickFunction() {
    if ( state == CONFIG_EFFECT )
    {
        // Previous Effect
        ws2812fx.setMode((ws2812fx.getMode() - 1) % ws2812fx.getModeCount());
    }
    else if ( state == CONFIG_BRIGHTNESS )
    {
        // Decrease Brightness
        ws2812fx.decreaseBrightness(BRIGHTNESS_STEP);
    }
    else if ( state == CONFIG_SPEED )
    {
        // Decrease Speed
        ws2812fx.decreaseSpeed(SPEED_STEP);
    }
    else if ( state == CONFIG_COLOR )
    {
        uint32_t color_code;

        // Decrease Color
        config.color--;
        color_code = ws2812fx.color_wheel(config.color);
        ws2812fx.setColor(color_code);
    }
    else if ( state == CONFIG_LENGTH_ADD )
    {
        // Increase Length + 10
        ws2812fx.increaseLength(COUNT_STEP);
    }
    else if ( state == CONFIG_LENGTH_DEL )
    {
        // Decrease Length + 10
        ws2812fx.decreaseLength(COUNT_STEP);
    }

    SerialPrintf("event: double_click\n");
    event_triggered = true;
} // myDoubleClickFunction
