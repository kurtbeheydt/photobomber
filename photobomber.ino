#define BA {B010001, B010001, B010001, B011111, B010001, B010001, B001110}
#define BB {B011110, B010001, B010001, B011110, B010001, B010001, B011110}
#define BC {B001110, B010001, B010000, B010000, B010000, B010001, B001110}
#define BD {B011110, B010001, B010001, B010001, B010001, B010001, B011110}
#define BE {B011111, B010000, B010000, B011100, B010000, B010000, B011111}
#define BF {B010000, B010000, B010000, B011100, B010000, B010000, B011111}
#define BG {B001110, B010001, B010001, B010111, B010000, B010001, B011110}
#define BH {B010001, B010001, B010001, B011111, B010000, B010001, B010001}
#define BI {B001110, B000100, B000100, B000100, B000100, B000100, B001110}
#define BJ {B000110, B000010, B000010, B000010, B000010, B000010, B000010}
#define BK {B010001, B010010, B010100, B011000, B010100, B010010, B010001}
#define BL {B011111, B010000, B010000, B010000, B010000, B010000, B010000}
#define BM {B010001, B010001, B010001, B010001, B010101, B011011, B010001}
#define BN {B010001, B010001, B010001, B010011, B010101, B011001, B010001}
#define BO {B001110, B010001, B010001, B010001, B010001, B010001, B001110}
#define BP {B010000, B010000, B010000, B011110, B010001, B010001, B011110}
#define BQ {B001111, B010011, B010101, B010001, B010001, B010001, B001110}
#define BR {B010001, B010010, B010100, B011110, B010001, B010001, B011110}
#define BS {B001110, B010001, B000001, B001110, B010000, B010001, B001110}
#define BT {B000100, B000100, B000100, B000100, B000100, B000100, B011111}
#define BU {B001110, B010001, B010001, B010001, B010001, B010001, B010001}
#define BV {B000100, B001010, B010001, B010001, B010001, B010001, B010001}
#define BW {B010001, B011011, B010101, B010001, B010001, B010001, B010001}
#define BX {B010001, B010001, B001010, B000100, B001010, B010001, B010001}
#define BY {B000100, B000100, B000100, B000100, B001010, B010001, B010001}
#define BZ {B011111, B010000, B001000, B000100, B000010, B010001, B011111}

#define BNUL {B001110, B010001, B011001, B010101, B010011, B010001, B001110}
#define B1 {B001110, B000100, B000100, B000100, B000100, B001100, B000100}
#define B2 {B011111, B010000, B001000, B000010, B000001, B010001, B001110}
#define B3 {B001110, B010001, B000001, B001110, B000001, B010001, B001110}
#define B4 {B000010, B000010, B011111, B010010, B001010, B000110, B000010}
#define B5 {B001110, B010001, B000001, B011110, B010000, B010000, B011111}
#define B6 {B001110, B010001, B010001, B011110, B010000, B010001, B001110}
#define B7 {B001000, B001000, B001000, B000100, B000010, B000001, B011111}
#define B8 {B001110, B010001, B010001, B001110, B010001, B010001, B001110}
#define B9 {B001110, B010001, B000001, B001110, B010001, B010001, B001110}

#define SPACE    {B000000, B000000, B000000, B000000, B000000, B000000, B000000}
#define LINE     {B011111, B000000, B000000, B000000, B000000, B000000, B000000}
#define DASH     {B000000, B000000, B000000, B001110, B000000, B000000, B000000}
#define EXCLAMAT {B000100, B000000, B000100, B000100, B000100, B000100, B000100}
#define QUESTION {B000100, B000000, B000100, B000010, B000001, B010001, B001110}


int latchPin = 10;
int clockPin = 13;
int dataPin = 11;
int pinLeft = 4;
int pinMiddle = 2;
int pinRight = 3;
int clock = 9;
int Reset = 8;
int latchPinPORTB = latchPin - 8;
int clockPinPORTB = clockPin - 8;
int dataPinPORTB = dataPin - 8;
int i = 0;
long scrolling_word[8];
int array_turn=0;
byte your_text[4][8]={BN, BNUL, BNUL, BB};//PUT YOUR TEXT HERE


void setup(){
  Serial.begin(9600);
  pinMode(dataPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(latchPin,OUTPUT);
  pinMode(pinLeft,OUTPUT);
  pinMode(pinMiddle,OUTPUT);
  pinMode(pinRight,OUTPUT);
  pinMode(clock,OUTPUT);
  pinMode(Reset,OUTPUT);
  digitalWrite(Reset,HIGH);
  digitalWrite(Reset,LOW);
  setupSPI();
  Serial.println("ok");
}

void display_word(byte word_print[][8], int num_patterns) { // this function displays your symbols
  // resets the counter fot the 4017
  i = 0;
  
  for (int x = 0; x < num_patterns; x++) { // main loop, goes over your symbols
    for (int r = 0; r < 7; r++) { // rijen
      scrolling_word[r] |= word_print[x][r];
    }
    for (int z = 0; z < 6; z++) { //the scrolling action (Z is also pretty much a kerning variable- larger vale = more space between letters)
        for (int p = 0; p < 8; p++) {
          scrolling_word[p] = scrolling_word[p] << 1;
        }
        displayLeds();      
    }
  }
  // twee extra keer naar links
  for (int p = 0; p < 8; p++) {
    scrolling_word[p] = scrolling_word[p] << 1;
  }
  for (int p = 0; p < 8; p++) {
    scrolling_word[p] = scrolling_word[p] << 1;
  }
  
  while (true) { // delay function, it just loops over the same display
    displayLeds();
  }
}

void displayLeds()
{
  for (int y = 0; y < 8; y++) { // scaning the display
    if (i == 8) { // counting up to 8 with the 4017
      digitalWrite(Reset, HIGH);
      digitalWrite(Reset, LOW);
      i = 0;
      digitalWrite(pinLeft, HIGH);
      digitalWrite(pinMiddle, HIGH);
      //digitalWrite(pinRight, HIGH);
    }
    latchOff();
    spi_transfer(make_word(0x01000000,y));// sending the data
    spi_transfer(make_word(0x00010000,y));
    spi_transfer(make_word(0x00000100,y));
    latchOn();
    delayMicroseconds(500);//waiting a bit
    latchOff();
    spi_transfer(0);// clearing the data
    spi_transfer(0);
    spi_transfer(0);
    latchOn();
    digitalWrite(clock,HIGH);//counting up with the 4017
    digitalWrite(clock,LOW);
    digitalWrite(pinMiddle, LOW);
    digitalWrite(pinLeft, LOW);
    digitalWrite(pinRight, LOW);

    i++;
  }  
}

byte make_word (long posistion, byte turn) {
  byte dummy_word = 0;
  for (int q = 0; q < 8; q++) {
    if (scrolling_word[turn] & (posistion<<q)) {
      dummy_word |= 0x01<<q;
    }
  }
  return dummy_word;
}   


void loop() {
  display_word(your_text, 4);
}

void latchOn() {
  bitSet(PORTB,latchPinPORTB);
}

void latchOff() {
  bitClear(PORTB,latchPinPORTB);
}

void setupSPI() {
  byte clr;
  SPCR |= ( (1<<SPE) | (1<<MSTR) ); // enable SPI as master
  //SPCR |= ( (1<<SPR1) | (1<<SPR0) ); // set prescaler bits
  SPCR &= ~( (1<<SPR1) | (1<<SPR0) ); // clear prescaler bits
  clr=SPSR; // clear SPI status reg
  clr=SPDR; // clear SPI data reg
  SPSR |= (1<<SPI2X); // set prescaler bits
  //SPSR &= ~(1<<SPI2X); // clear prescaler bits

  delay(10);
}

byte spi_transfer(byte data) {
  SPDR = data;			  // Start the transmission
  while (!(SPSR & (1<<SPIF)))     // Wait the end of the transmission
  {
  };
  return SPDR;			  // return the received byte, we don't need that
}
