const uint8_t NOTE_OFF = 0x80;
const uint8_t NOTE_ON = 0x90;
const uint8_t KEY_PRESSURE = 0xA0;
const uint8_t CC = 0xB0;
const uint8_t PROGRAM_CHANGE = 0xC0;
const uint8_t CHANNEL_PRESSURE = 0xD0;
const uint8_t PITCH_BEND = 0xE0;

void setup() {
  
//Serial.begin(31250);
Serial.begin(115200);
}
void handleMIDI(uint8_t statusByte, uint8_t data1, uint8_t data2 = 0) { ;
}

void loop() {
  
static uint8_t runningStatus = 0;
static uint8_t data1 = 0b10000000;

if (Serial.available()) {
  
uint8_t newByte = Serial.read();
Serial.write(newByte);
if (newByte & 0b10000000) { // Status byte received
runningStatus = newByte;
data1 = 0b10000000;
} else {
if (data1 != 0b10000000) { // Second data byte received
handleMIDI(runningStatus, data1, newByte);
data1 = 0b10000000;
return;
} else { // First data byte received
if (!runningStatus) // no status byte
return; // invalid data byte
if (runningStatus == PROGRAM_CHANGE
|| runningStatus == CHANNEL_PRESSURE) { // First data byte of Program Change orChannel Pressure
handleMIDI(runningStatus, newByte);
return;
} else if (runningStatus < 0xF0) { // First data byte of Note Off/On, Key
  data1 = newByte;
  return;
  } else {
    ;
  }
}}}

}

