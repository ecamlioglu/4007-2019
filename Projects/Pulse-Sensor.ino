#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <LiquidCrystal_I2C_AvrI2C.h> // I use this lib
LiquidCrystal_I2C_AvrI2C lcd(0x27, 16, 2);

const int OUTPUT_TYPE = SERIAL_PLOTTER;

const int PULSE_INPUT = A3; //Pulse sensor connect pin
const int PULSE_BLINK = 13;    // on-board led
const int PULSE_FADE = 5;
const int THRESHOLD = 550;   

PulseSensorPlayground pulseSensor;

void setup() {

  Serial.begin(115200);


  pulseSensor.analogInput(PULSE_INPUT);
  pulseSensor.blinkOnPulse(PULSE_BLINK);
  pulseSensor.fadeOnPulse(PULSE_FADE);

  pulseSensor.setSerial(Serial);
  pulseSensor.setOutputType(OUTPUT_TYPE);
  pulseSensor.setThreshold(THRESHOLD);
 if (!pulseSensor.begin()) {

    for(;;) {
      digitalWrite(PULSE_BLINK, LOW);
      delay(50);
      digitalWrite(PULSE_BLINK, HIGH);
      delay(50);
    }
  }
}

void loop() {
  delay(20);
 pulseSensor.outputSample();
  if (pulseSensor.sawStartOfBeat()) {
   pulseSensor.outputBeat();
  }
}
