/*This program puts the servo values into an array,
 reagrdless of channel number, polarity, ppm frame length, etc...
 You can even change these while scanning!*/

#define PPM_Pin 3
int ppm[16]; // array for storing up to 16 servo signals

void read_ppm() {
  static unsigned int pulse;
  static unsigned long counter;
  static byte channel;

  counter = TCNT1;
  TCNT1 = 0;

  if (counter < 1020) { // must be a pulse
    pulse = counter;
  } else if (counter > 3820) { // sync
    channel = 0;
  } else { // servo values between 810 and 2210 will end up here
    ppm[channel] = (counter + pulse) / 2;
    channel++;
  }
}

void setup() {
  Serial.begin(250000);
  Serial.println("ready");

  pinMode(PPM_Pin, INPUT);
  attachInterrupt(PPM_Pin - 2, read_ppm, CHANGE);

  TCCR1A = 0x00; // COM1A1=0, COM1A0=0 => Disconnect Pin OC1 from Timer/Counter
                 // 1 -- PWM11=0,PWM10=0 => PWM Operation disabled
  TCCR1B = B00000010;  // 0x02;	   // 16MHz clock with prescaler means
                       // TCNT1 increments every .5 uS (cs11 bit set
  TIMSK1 = _BV(ICIE1); // enable input capture interrupt for timer 1
}

void loop() {
  // You can delete everithing inside loop() and put your own code here
  static int count;

  while (ppm[count] != 0) { // print out the servo values
    Serial.print(ppm[count]);
    Serial.print("  ");
    count++;
  }
  count = 0;
  Serial.println("");
  delay(10); // you can even use delays!!!
}
