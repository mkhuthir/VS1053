

// include libraries
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_VS1053.h>

// define the pins used
#define CLK     13      // SPI Clock, shared with SD card
#define MISO    12      // Input data, from VS1053/SD card
#define MOSI    11      // Output data, to VS1053/SD card
#define RESET   9       // VS1053 reset pin (output)
#define CS      10      // VS1053 chip select pin (output)
#define DCS     8       // VS1053 Data/command select pin (output)
#define CARDCS  4       // Card chip select pin
#define DREQ    3       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = Adafruit_VS1053_FilePlayer(RESET, CS, DCS, DREQ, CARDCS);
  
void setup() {

  // initialise Serial
  Serial.begin(115200);
  Serial.println("Hello....");

  // initialise SD Card
  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed!"));
    while (1); // halt
  }
  Serial.println(F("SD Card OK!"));

  // initialise VS1053
  if (! musicPlayer.begin()) { 
    Serial.println(F("VS1053 failed!"));
    while (1); // halt
  }
  Serial.println(F("VS1053 OK!"));
  musicPlayer.setVolume(1,1);                           // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // Using DREQ int
  musicPlayer.sineTest(0x44, 500);                      // Make a tone to indicate VS1053 is working

}

void loop() {

  // Start Playing a file
  Serial.println(F("Playing track001.mp3"));
  musicPlayer.startPlayingFile("/track001.mp3");
  
  while (musicPlayer.playingMusic) {
    // file is now playing in the 'background'
    Serial.print(".");
    delay(1000);
  }
  
  Serial.println("\nDone playing music");
  while (1); // halt
}


