#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TFMPlus.h>

#define PIN_FREQ_TEMP 4
#define DIST_MIN 0
#define DIST_MAX 200
#define FREQ_MIN 33
#define FREQ_MAX 1023

TFMPlus tfmini;
SoftwareSerial serialMini = SoftwareSerial(2, 3);

uint16_t tfDist;
uint16_t tfLux;
uint16_t tfTemp;

uint16_t freq_out(uint16_t val, uint16_t inMin, uint16_t inMax, uint16_t outMin, uint16_t outMax, byte pin)
{   
    if(outMin < FREQ_MIN) outMin = FREQ_MIN;
    if(outMax > FREQ_MAX) outMax = FREQ_MAX;
    uint16_t freq = map(val, inMin, inMax, outMin, outMax);
    tone(pin, freq);
    return(freq);
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(20);
  tfmini.begin(&serialMini);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  tfmini.getData(tfDist, tfLux, tfTemp);
  freq_out(tfDist, DIST_MAX, DIST_MAX, FREQ_MIN, FREQ_MAX, PIN_FREQ_TEMP);
  Serial.println(tfDist);
}