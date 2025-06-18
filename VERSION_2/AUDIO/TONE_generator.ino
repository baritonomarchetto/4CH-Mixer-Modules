//Digital reference tone generator
//sythbrigade.altervista.org
const int potPin = 3;  // Input to set waveform period delta
const int outPin = 4;  // wave out
unsigned long sampleInterval;
unsigned long lastUpdate;

void setup() {
  pinMode(outPin, OUTPUT);
}

void loop() {
  if (micros() - lastUpdate >= sampleInterval) {
    digitalWrite(outPin, digitalRead(outPin) == HIGH ? LOW : HIGH); // flip the slow way
    sampleInterval = 900ul + (analogRead(potPin)>>2);
    lastUpdate = micros();
  }
}
