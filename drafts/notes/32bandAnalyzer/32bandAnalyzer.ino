/*
  Copyright (c) 2019 Shajeeb TM

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

// https://create.arduino.cc/projecthub/shajeeb/32-band-audio-spectrum-visualizer-analyzer-902f51?ref=search&ref_id=spectrum%20analyzer&offset=3

#include <arduinoFFT.h>
#include "FastLED.h"
#include <SPI.h>

#define NUM_LEDS 24
#define SAMPLES 64        //Must be a power of 2

#define  xres NUM_LEDS     // Total number of  columns in the display, must be <= SAMPLES/2
#define  yres 128          // Total number of  rows in the display

#define  MIC_PIN A0

CRGB leds[NUM_LEDS];

double vReal[SAMPLES];
double vImag[SAMPLES];
float data_avgs[xres];

int yvalue;
int displaycolumn , displayvalue;
int peaks[xres];

arduinoFFT FFT = arduinoFFT();                                    // FFT object

float maxvalue_analog = 50;
float maxvalue_vreal = 100;

void setup() {
  Serial.begin(250000);

  FastLED.addLeds<NEOPIXEL, 11>(leds, NUM_LEDS);
  FastLED.clear();
}

void loop() {
  // Sampling
  for (int i = 0; i < SAMPLES; i++)
  {
    int value = analogRead(MIC_PIN); //rough zero shift

    vReal[i] = map(value, 0, maxvalue_analog * 1.3, 0, 256);                   // Copy to bins after compressing
    vImag[i] = 0;

    maxvalue_analog = max(maxvalue_analog, (maxvalue_analog+value)/2);
    
    delayMicroseconds(195);
  }

  maxvalue_analog = max(30, maxvalue_analog * 0.98);
  maxvalue_vreal = max(100, maxvalue_vreal * 0.98);


  // FFT
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);


  // ++ re-arrange FFT result to match with no. of columns on display ( xres )
  int step = (SAMPLES / 2 - 2) / xres;
  int c = 0;
  for (int i = 2; i < (SAMPLES / 2); i += step)
  {
    data_avgs[c] = 0;
    for (int k = 0 ; k < step ; k++) {
      //Serial.println(vReal[i + k]);
      data_avgs[c] = data_avgs[c] + vReal[i + k];
    }
    data_avgs[c] = data_avgs[c] / step;
    c++;
  }
  // -- re-arrange FFT result to match with no. of columns on display ( xres )





  // ++ send to display according measured value
  for (int i = 0; i < xres; i++)
  {
    //Serial.println(data_avgs[i]);

   
    maxvalue_vreal = max(maxvalue_vreal, data_avgs[i]);
    data_avgs[i] = constrain(data_avgs[i], 0, maxvalue_vreal);          // set max & min values for buckets
    data_avgs[i] = map(data_avgs[i], 0, maxvalue_vreal, 0, yres);        // remap averaged values to yres
    yvalue = data_avgs[i];



    peaks[i] = peaks[i] - yres / 8; // decay by one light
    if (yvalue > peaks[i])
      peaks[i] = yvalue;
    yvalue = peaks[i];

    if (yvalue < yres / 10) {
      yvalue = 0;
    }
    else {
      //yvalue = map(yvalue * yvalue, 0, yres * yres, 0, yres);
    }

    /*
      for (int j = 0; j < yvalue; j++) {
      Serial.print("#");
      }
      Serial.println();
    */

    leds[i].setHSV(
//      map(yvalue, 0, yres, 80, 0),
      map(yvalue, 0, yres, 90, 255),
      255,
      map(yvalue, 0, yres, 0, 120)
    );
  }
  Serial.println("-----");

  FastLED.show();
  // -- send to display according measured value

  Serial.println(maxvalue_analog);
  Serial.println(maxvalue_vreal);

}
