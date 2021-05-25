#include <Keypad_Matrix.h>
#include <Adafruit_NeoPixel.h>

const byte ROWS = 3;
const byte COLS = 6;

// how the keypad has its keys laid out
const char keys[ROWS][COLS] = {
  {'a', 'b', 'c', 'd', 'e', 'f'},
  {'g', 'h', 'i', 'j', 'k', 'l'},
  {'m', 'n', 'o', 'p', 'q', 'r'},
};

int RXLED = 17;

const byte rowPins[ROWS] = {14,15,18}; //connect to the row pinouts of the keypad
const byte colPins[COLS] = {5,6,7,8,10,16}; //connect to the column pinouts of the keypad
const byte ledPin = 9;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, 9, NEO_GRB + NEO_KHZ800);
  // Create the Keypad
Keypad_Matrix kpd = Keypad_Matrix( makeKeymap (keys), rowPins, colPins, ROWS, COLS );

void keyDown (const char which)
{
  Serial.print (F("Key down: "));
  Serial.println (which);
}

void keyUp (const char which)
{
  Serial.print (F("Key up: "));
  Serial.println (which);
}


void setup() 
{
  pinMode(RXLED, OUTPUT);  // Set RX LED as an output
  Serial.begin (115200);
  Serial.println ("Starting.");
  strip.begin();
  strip.setBrightness(10);
  for(int i=0; i<12; i++) {
    strip.setPixelColor(i, strip.Color(0, 153, 255));
  }
  kpd.begin ();
  kpd.setKeyDownHandler (keyDown);
  kpd.setKeyUpHandler   (keyUp);
}

unsigned long previousMillis = 0;
bool swap = 0;
void loop() 
{
  digitalWrite(RXLED, HIGH);   // set the RX LED ON
  TXLED1;
  kpd.scan ();
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    swap = !swap;
    if(swap) {
      for(int i=0; i<12; i++) {
        strip.setPixelColor(i, strip.Color(0, 153, 255));
      }
    }
    else {
      for(int i=0; i<12; i++) {
        strip.setPixelColor(i, strip.Color(255, 153, 0));
      }
    }
  }

  strip.show();
}
