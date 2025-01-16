/* Reference Tone generator
 * Part of 4-Channel mixer project (synthbrigade.altervista.org)
 * 
 * by Barito
 */

const byte corrPin = 3;
const byte tonePin = 4;

int pitchRaw;
int pitchCorr;
int baseFreq = 440; // A4

void setup() {
  pinMode(corrPin, INPUT);
  pinMode(tonePin, OUTPUT);
  tone(tonePin, baseFreq); //A4
}

void loop() {
  if (analogRead(corrPin) != pitchRaw){
    pitchRaw = analogRead(corrPin); // 0/1023
    pitchCorr = pitchRaw >> 5; // 0/31
    pitchCorr = pitchCorr - pitchCorr/2; // -15/+15
    tone(tonePin, baseFreq + pitchCorr);
  }
}
