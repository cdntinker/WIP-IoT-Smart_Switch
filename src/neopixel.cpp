/* animations for neopixel control */
#include "LIBRARIES.h"

#include "DEFINES.h"

#include "EXTERNS.h"

#include "neopixel.h"

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, LED_TYPE + NEO_KHZ800);

void PIXELS_init()
{
  strip.begin();                   //              - INITIALIZE NeoPixel strip object (REQUIRED)
  strip.setBrightness(brightness); //              - set strip brightness
  PIXELS_colorWipe(0, 0, 0, 0); // neopixel.h   - turn all the led's off
}

void PIXELS_brightness()
{
  strip.setBrightness(brightness);
}

void PIXELS_colorWipe(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
  for (int a = 0; a < LED_COUNT; a++)
  {
    strip.setPixelColor(a, r, g, b, w); //  Set pixel's color (in RAM)
    strip.show();
  }
  //  neo_update[c] = false;
}

void PIXELS_colorSet(uint8_t c, uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
  strip.setPixelColor(c, r, g, b, w); //  Set pixel's color (in RAM)
  strip.show();
  neo_update[c] = false;
}

void PIXELS_doubleflash(uint8_t c, uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t w1)
{
  if ((millis() - lastdouble) > 100)
  {
    doubletime++;
    if (doubletime >= 14)
    {
      doubletime = 0;
    }
    lastdouble = millis();
  }

  if (doubletime == 0)
  {
    strip.setPixelColor(c, r, g, b, w); //  Set pixel's color (in RAM)
    strip.show();
  }
  if (doubletime == 1)
  {
    strip.setPixelColor(c, 0, 0, 0, 0); //  Set pixel's color (in RAM)
    strip.show();
  }
  if (doubletime == 2)
  {
    strip.setPixelColor(c, r, g, b, w); //  Set pixel's color (in RAM)
    strip.show();
  }
  if (doubletime == 8)
  {
    strip.setPixelColor(c, r1, g1, b1, w1); //  Set pixel's color (in RAM)
    strip.show();
  }
}

void PIXELS_doubleflashHUB(uint8_t r, uint8_t g, uint8_t b, uint8_t w, uint8_t r1, uint8_t g1, uint8_t b1, uint8_t w1)
{
  if ((millis() - lastdouble) > 100)
  {
    doubletime++;
    if (doubletime >= 14)
    {
      doubletime = 0;
    }
    lastdouble = millis();
  }

  if (doubletime == 0)
  {
    PIXELS_colorWipe(r, g, b, w); //  Set pixel's color (in RAM)
    strip.show();
  }
  if (doubletime == 1)
  {
    PIXELS_colorWipe(0, 0, 0, 0); //  Set pixel's color (in RAM)
    strip.show();
  }
  if (doubletime == 2)
  {
    PIXELS_colorWipe(r, g, b, w); //  Set pixel's color (in RAM)
    strip.show();
  }
  if (doubletime == 8)
  {
    PIXELS_colorWipe(r1, g1, b1, w1); //  Set pixel's color (in RAM)
    strip.show();
  }
}

/* animation for over / under volt */
void PIXELS_ringupdate()
{
  // if ((millis() - prevringMillis) > ringspeed)
  // {
  //   prevringMillis = millis();
  //   fwd++;
  //   if (fwd == 4)
  //   {
  //     fwd = 0;
  //   }
  // }
}

void PIXELS_voltring(uint8_t r1, uint8_t g1, uint8_t b1, uint8_t w1, uint8_t r2, uint8_t g2, uint8_t b2, uint8_t w2)
{
  // for (int a = 0; a < 4; a++)
  // {
  //   strip.setPixelColor(a, r1, g1, b1, w1);   //  Set pixel's color (in RAM)
  //   strip.setPixelColor(fwd, r2, g2, b2, w2); //  Set pixel's color (in RAM)
  //   strip.show();
  //   fwd_prev = fwd;
  // }
}

void PIXELS_success()
{ // all green - with delay

  PIXELS_colorWipe(0, 50, 0, 0);
  delay(1000);
  PIXELS_colorWipe(0, 0, 0, 0);
  connected_update = false;
}

void PIXELS_overrideColor()
{ // color mode to use while in override mode

  for (int f = 0; f < 4; f++) //  set flash state varible
  {
    flashState[f] = ledState;
  }

  // for (int x = 0; x < 4; x++) // check each led
  // {
    // if (overrideMODE == true && port_state[x] != 10 && port_state[x] != 11) // in override mode (TRUE), not over current hub or port
    // {
    //   if (ledmode[x] == 2) // flash led mode                  // flash the LED mode
    //   {
    //     if (flashState[x] != prevflash[x]) // the state has chnaged since the last time we updated the LED
    //     {
    //       if (ledState == HIGH) // LED state is high aka turn on the led
    //       {
    //         PIXELS_colorSet(x, rednew[x], grnnew[x], blunew[x], whinew[x]); // set LED to desired Color
    //       }
    //       else // otherwise we're turning off the LED
    //       {
    //         PIXELS_colorSet(x, 0, 0, 0, 0); // set LED off
    //       }
    //       prevflash[x] = flashState[x]; // set previous flash varible -- so we don't keep trying to update an LED
    //     }
    //   }
    //   if (ledmode[x] == 1) // just change the color mode
    //   {
    //     if (neo_override[x] == true) // we do need to update the led's
    //     {
    //       PIXELS_colorSet(x, rednew[x], grnnew[x], blunew[x], whinew[x]); // set led to desired color
    //       neo_override[x] = false;                                 // reset our update varible
    //     }
    //   }
    // }
  // }
}
