//#include "Wire.h"
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <Fonts/hebEng5x7avia.h>

#define PIN 12

// MATRIX DECLARATION:
// Parameter 1 = width of NeoPixel matrix
// Parameter 2 = height of matrix
// Parameter 3 = pin number (most are valid)
// Parameter 4 = matrix layout flags, add together as needed:
//   NEO_MATRIX_TOP, NEO_MATRIX_BOTTOM, NEO_MATRIX_LEFT, NEO_MATRIX_RIGHT:
//     Position of the FIRST LED in the matrix; pick two, e.g.
//     NEO_MATRIX_TOP + NEO_MATRIX_LEFT for the top-left corner.
//   NEO_MATRIX_ROWS, NEO_MATRIX_COLUMNS: LEDs are arranged in horizontal
//     rows or in vertical columns, respectively; pick one or the other.
//   NEO_MATRIX_PROGRESSIVE, NEO_MATRIX_ZIGZAG: all rows/columns proceed
//     in the same order, or alternate lines reverse direction; pick one.
//   See example below for these values in action.
// Parameter 5 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)


// Example for NeoPixel Shield.  In this application we'd like to use it
// as a 5x8 tall matrix, with the USB port positioned at the top of the
// Arduino.  When held that way, the first pixel is at the top right, and
// lines are arranged in columns, progressive order.  The shield uses
// 800 KHz (v2) pixels that expect GRB color data.
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_BOTTOM     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);
const uint16_t colors[] = {
  matrix.Color(148, 0, 211), matrix.Color(75, 0, 130), matrix.Color(0, 0, 255), matrix.Color(0, 255, 0), matrix.Color(255, 255, 0), matrix.Color(255, 127, 80) , matrix.Color(255, 0, 0)};
// אבגדהוזחטיכךלמםנןסעפףצץקרשת//
//char replybuffer[255]={0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,0x90,0x91,0x92,0x93,0x94,0x96,0x97,0x98,0x99,0x9A};
// this is a large buffer for replies
char replybuffer[255]={0x21,0x21,0x21,0x8F,0x9A,0x8E,0x20,0x9A,0x87,0x94,0x99,0x8E,0x8E,0x20,0x87,0x8E,0x99,0x20,0x8D,0x89,0x98,0x85,0x94};
uint8_t msgLen = 19;              // Empty message
int x    = msgLen * -6;//matrix.width();
int pass = 0; // variable we'll use to keep track of a cycling of colors
int i;
unsigned long prevFrameTime = 0L;             // For animation timing
#define FPS 20                                // Scrolling speed
// Pin 7 has an LED connected on FLORA.
// give it a name:
int led = 7;

void setup() {
  Serial.begin(115200);
  Serial.println(F("LCD test"));
  Serial.println(F("Initializing....(May take 3 seconds)"));

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
  matrix.setFont(&hebEng5x7avia);


  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);    

  delay(1000);
}



void loop() {
  
   unsigned long t = millis(); // Current elapsed time, milliseconds.
  // millis() comparisons are used rather than delay() so that animation
  // speed is consistent regardless of message length & other factors.
   if((t - prevFrameTime) >= (1000L / FPS)) { // Handle scrolling
        matrix.fillScreen(0);
        matrix.setCursor(x, 1);
        for(i=0;i<=strlen(replybuffer);i++)
        {
            matrix.setTextColor(colors[i%7]);
            matrix.print(replybuffer[i]);
        }
        if(++x >= (msgLen * 6)) {
           x = msgLen * -6; // We must repeat!
           if(++pass >= 3) pass = 0;
              matrix.setTextColor(colors[pass]);
        }
      matrix.show();
      prevFrameTime = t;
     }

}
