#include <Arduino.h>

// include SPI, VS1053 and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

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
  Serial.begin(115200);
  Serial.println("Hello....");

// initialise VS1053
  if (! musicPlayer.begin()) { 
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));

// initialise SD Card
  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }
  Serial.println(F("SD Card found"));

  musicPlayer.setVolume(1,1);   // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // Using DREQ int

  Serial.println(F("Playing track 003"));
  musicPlayer.playFullFile("/track007.mp3");

  Serial.println(F("Playing track 004"));
  musicPlayer.startPlayingFile("/track008.mp3");
}

void loop() {
 
}


