// segmenten: a = 4, b = 5, c = 6, d = 7, e = 8, f = 9, g = 10
// digits: d1 = A0, d2 = A1, d3 = A2, d4 = A3
//buttons

bool knop_start = PD2; //B0000 0010
bool knop_reset = PD3;  //B0000 0100
bool toggle = false;
//tijd
int chrono = 0;
double tijd = millis(); //als deze int is zorgt het voor problemen!

//omzetting naar cijfers
byte cijfersD[] = {0xF0,0x60,0xB0,0xF0,0x60,0xD0,0xD0,0x70,0xF0,0xF0}; // 0 1 2 3 4 5 6 7 8 9
byte cijfersB[] = {0x03,0x00,0x05,0x04,0x06,0x06,0x07,0x00,0x07,0x06}; // 0 1 2 3 4 5 6 7 8 9
byte tel[] = {0x00,0x00,0x00,0x00};

void setup() {

  //SEGMENT op low
  for(byte i = 0x04; i < 0x08; i++){
    DDRD |= 1 << i;
  }
  for(byte i = 0x00; i < 0x04; i++){
    DDRB |= 1 << i;
  }
  //DIGITS op high
  for(byte i = 0x00; i < 0x04; i++){
    DDRC |= 1 << i;
  }
}
void loop() {
knop_start = (PIND & B00000100) >> 1;
knop_reset =  (PIND & B00001000) >> 1;
//beide registers aanspreken PORTD en PORTB om zo een getal te vervoledigen
if(knop_start){
  DDRC = 0x00;
  _delay_ms(500);
  toggle = !toggle;
}

if(knop_reset){
  DDRC = 0x00;
  _delay_ms(500);
  for(byte i = 0x00; i < 0x04; i++){
      tel[i] = 0x00;
  }
}
    _delay_ms(1);
   //DIGIT 1
    DDRC = 0x08;
    PORTD = cijfersD[tel[0]];
    PORTB = cijfersB[tel[0]];
    //DIGIT 2
    _delay_ms(1);
    DDRC = 0x04;
    PORTD = cijfersD[tel[1]];
    PORTB = cijfersB[tel[1]];
    //DIGIT 3
    _delay_ms(1);
    DDRC = 0x02;
    PORTD = cijfersD[tel[2]];
    PORTB = cijfersB[tel[2]];
    //DIGIT 4
    _delay_ms(1);
    DDRC = 0x01; 
    PORTD = cijfersD[tel[3]];
    PORTB = cijfersB[tel[3]];
   
   if ((millis()-tijd) > 1004) {
    tijd = millis();
    
    //enkel als de knop ingedrukt is geweest zal het beginnen tellen
    if(toggle){
      tel[0]++;
    }
    

    //TELLEN
    if(tel[0] > 9){
      tel[0] = 0x00;
      tel[1]++;
      if(tel[1] > 5){
        tel[1] = 0x00;
        tel[2]++;
        if(tel[2] > 9){
          tel[2] = 0x00;
          tel[3]++;
          if(tel[3] > 5){
            for(byte i = 0x00; i < 0x04; i++){
            tel[i] = 0x00;
            }
          }
        }
      }
    }
    // Reset
    if (chrono>9999) chrono=0;
  }
  
}
