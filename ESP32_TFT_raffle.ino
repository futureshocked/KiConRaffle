// I used this sketch to draw a random number from 1-4. 
// The winner got a free ticket to the first KiCad conference in Chicago, Illinois.
// Written by Dr Peter Dalmaris, March 31 2019.
// Techexplorations.com

// Using code from example sketch Unicode_test from TFT_eSPI library
#include <TFT_eSPI.h> // Hardware-specific library

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

uint16_t bg = TFT_BLACK;
uint16_t fg = TFT_WHITE;


void refresh_readings();
#define LED_PIN            17

void setup() {
  pinMode(LED_PIN, OUTPUT);
  tft.init();
  tft.setRotation(0); // portrait

  fg = TFT_WHITE;
  bg = TFT_BLACK;

  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }

  Serial.begin(9600);
  tft.setRotation(1);
  tft.fillScreen(bg);
  tft.setTextColor(fg, bg);
  tft.loadFont("NotoSansBold15");
  Serial.println("\r\nDrawing the lucky number...");
  tft.println("\r\nDrawing the lucky number...");
  delay(1000); 
  Serial.print("\r\n1...");
   tft.print("\r\n1...");
  delay(1000);
  Serial.print(" 2...");
  tft.print(" 2...");
  delay(1000);
  Serial.println(" 3...");
  tft.print(" 3...");
  delay(1000);
  lucky_number_draw();
}

void loop() {
  // No action here
}

void lucky_number_draw() {
  digitalWrite(LED_PIN, HIGH);
  tft.setTextColor(fg, bg);

  tft.loadFont("SansSerif-36"); // Create TTF fonts using instructions at https://pages.uoregon.edu/park/Processing/process5.html

  tft.fillScreen(bg);
  tft.setCursor(5,5);
  tft.println("Raffle Winner #:");

  tft.loadFont("SansSerif-48");
  tft.setTextColor(TFT_YELLOW, bg);
  tft.setCursor(150,100);
  randomSeed(36);
  tft.print(random(1, 4)); // Calling random number generator: https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/system/system.html

                            // The random function is overloaded here: https://github.com/espressif/arduino-esp32/blob/master/cores/esp32/WMath.cpp

  // Print logo 
  // This graphic is stored in the SPIFS. 
  // If you don't want to print a graphic, just comment out the next two lines, and
  // dissable SPIFS.
  drawBmp("/te.bmp", 160, 198);
  digitalWrite(LED_PIN, LOW);
}
