// this programm will put out a PPM signal

//////////////////////CONFIGURATION///////////////////////////////
#define chanel_number 8          // set the number of chanels
#define default_servo_value 1500 // set the default servo value
#define PPM_FrLen                                                              \
  22500 // set the PPM frame length in microseconds (1ms = 1000µs)
#define PPM_PulseLen 300 // set the pulse length
#define onState 1 // set polarity of the pulses: 1 is positive, 0 is negative
#define PPM_Pin 3 // set PPM signal output pin on the arduino
//////////////////////////////////////////////////////////////////
// #include <Arduino.h>
/*this array holds the servo values for the ppm signal
 change theese values in your code (usually servo values move between 1000 and
 2000)*/
String a, substr;
int strEnd;
int strStart = 0;
int ppm[chanel_number];
int value = default_servo_value;
char input[50];
char *p;
char b;

void setup() {

  // initiallize default ppm values
  for (int i = 0; i < chanel_number; i++) {
    ppm[i] = default_servo_value;
  }

  pinMode(PPM_Pin, OUTPUT);
  digitalWrite(PPM_Pin,
               !onState); // set the PPM signal pin to the default state
                          //  (off)

  cli();
  TCCR1A = 0; // set entire TCCR1 register to 0
  TCCR1B = 0;

  OCR1A = 100;             // compare match register, change this
  TCCR1B |= (1 << WGM12);  // turn on CTC mode
  TCCR1B |= (1 << CS11);   // 8 prescaler: 0,5 microseconds at 16mhz
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  sei();
  Serial.begin(9600);
  for (int i = 0; i < chanel_number; i++) {
    ppm[i] = default_servo_value;
  }
}

void loop() {
  /* change ppm[] value here
  ppm[0] = 1300;
  ppm[2] = 1700;
  ppm[4] = 1000;
  */
  delay(10);
}

ISR(TIMER1_COMPA_vect) { // leave this alone
  static boolean state = true;

  TCNT1 = 0;

  if (state) { // start pulse
    digitalWrite(PPM_Pin, onState);
    OCR1A = PPM_PulseLen * 2;
    state = false;
  } else { // end pulse and calculate when to start the next pulse
    static byte cur_chan_numb;
    static unsigned int calc_rest;

    digitalWrite(PPM_Pin, !onState);
    state = true;

    if (cur_chan_numb >= chanel_number) {
      cur_chan_numb = 0;
      calc_rest = calc_rest + PPM_PulseLen; //
      OCR1A = (PPM_FrLen - calc_rest) * 2;
      calc_rest = 0;
    } else {
      OCR1A = (ppm[cur_chan_numb] - PPM_PulseLen) * 2;
      calc_rest = calc_rest + ppm[cur_chan_numb];
      cur_chan_numb++;
    }
  }
}
