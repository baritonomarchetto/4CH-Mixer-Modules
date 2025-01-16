/* Reference Tone generator
 * Part of 4-Channel mixer project (synthbrigade.altervista.org)
 * 
 * by Barito (last update jan 2025)
 */

const byte corrPin = 3;
const byte tonePin = 4;

int pitchCorr;
int baseFreq = 440; // A4

void setup() {
  pinMode(corrPin, INPUT);
  pinMode(tonePin, OUTPUT);
  //tone(tonePin, baseFreq); //A4
}

void loop() {
  pitchCorr = analogRead(corrPin) >> 7; // 0/7
  tone(tonePin, baseFreq + pitchCorr*2 -7);
}
