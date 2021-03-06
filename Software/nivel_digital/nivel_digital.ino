/**************************************************************************
Adicionar

RANGE 0-90° E 0-180°
Ajustar leitura do sensor 

ZERO RELATIVO
Verificar as medições relativas ou absolutas

HOLD
Mantém o valor da leitura na tela

**************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_ADXL345.h>         // SparkFun ADXL345 Library

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

/*********** COMMUNICATION SELECTION ***********/
/*    Comment Out The One You Are Not Using    */
//ADXL345 adxl = ADXL345(10);           // USE FOR SPI COMMUNICATION, ADXL345(CS_PIN);
ADXL345 adxl = ADXL345();             // USE FOR I2C COMMUNICATION

#define LOGO_HEIGHT   64
#define LOGO_WIDTH    128
#define M_POS_X       22
#define M_POS_Y       36

// 'angulo180', 25x14px
const unsigned char bitmap_angulo180 [] PROGMEM = {
  0x00, 0x1c, 0x00, 0x00, 0x00, 0xdd, 0x80, 0x00, 0x03, 0xdd, 0xe0, 0x00, 0x07, 0x1c, 0x70, 0x00, 
  0x0e, 0x1c, 0x38, 0x00, 0x1c, 0x1c, 0x1c, 0x00, 0x38, 0x1c, 0x0e, 0x00, 0x30, 0x1c, 0x06, 0x00, 
  0x60, 0x1c, 0x03, 0x00, 0x60, 0x1c, 0x03, 0x00, 0x60, 0x1c, 0x03, 0x00, 0x00, 0x1c, 0x00, 0x00, 
  0xff, 0xff, 0xff, 0x80, 0xff, 0xff, 0xff, 0x80
};
// 'angulo90', 13x14px
const unsigned char bitmap_angulo90 [] PROGMEM = {
  0xc0, 0x00, 0xd8, 0x00, 0xde, 0x00, 0xc7, 0x00, 0xc3, 0x80, 0xc1, 0xc0, 0xc0, 0xe0, 0xc0, 0x60, 
  0xc0, 0x30, 0xc0, 0x30, 0xc0, 0x30, 0xc0, 0x00, 0xff, 0xf8, 0xff, 0xf8
};

// 'battery_low', 31x14px
const unsigned char bitmap_battery_low [] PROGMEM = {
  0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xf8, 0xc0, 0x00, 0x00, 0x18, 0xd8, 0x00, 0x00, 0x18, 
  0xdc, 0x00, 0x00, 0x1e, 0xdc, 0x00, 0x00, 0x1e, 0xdc, 0x00, 0x00, 0x1e, 0xde, 0x00, 0x00, 0x1e, 
  0xde, 0x00, 0x00, 0x1e, 0xde, 0x00, 0x00, 0x1e, 0xdf, 0x00, 0x00, 0x18, 0xc0, 0x00, 0x00, 0x18, 
  0xff, 0xff, 0xff, 0xf8, 0xff, 0xff, 0xff, 0xf8
};

// 'logos_senai_preto', 128x64px
const unsigned char logo_senai_preto [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0x80, 0x1f, 0xfe, 0x07, 0xff, 0xfe, 0x7f, 0xc0, 0x3f, 0x00, 0x7f, 0x80, 0x1f, 0x81, 0xff, 
  0xff, 0x80, 0x7f, 0xff, 0x87, 0xff, 0xfe, 0x7f, 0xe0, 0x7e, 0x00, 0xff, 0x80, 0x1f, 0x81, 0xff, 
  0x00, 0x00, 0xff, 0xff, 0x87, 0xff, 0xfc, 0xff, 0xe0, 0x7e, 0x01, 0xff, 0xc0, 0x1f, 0x80, 0x00, 
  0x00, 0x01, 0xff, 0xff, 0xc7, 0xff, 0xfc, 0xff, 0xe0, 0x7e, 0x01, 0xff, 0xc0, 0x3f, 0x80, 0x00, 
  0xff, 0x81, 0xfc, 0x3f, 0xc7, 0xe0, 0x00, 0xff, 0xe0, 0x7e, 0x03, 0xff, 0xc0, 0x3f, 0x81, 0xff, 
  0xff, 0x83, 0xf8, 0x1f, 0xcf, 0xe0, 0x00, 0xff, 0xf0, 0x7e, 0x03, 0xef, 0xc0, 0x3f, 0x01, 0xff, 
  0x00, 0x03, 0xf8, 0x1f, 0x8f, 0xe0, 0x00, 0xfb, 0xf0, 0xfc, 0x07, 0xef, 0xc0, 0x3f, 0x00, 0x00, 
  0x00, 0x03, 0xfc, 0x00, 0x0f, 0xc0, 0x01, 0xfb, 0xf0, 0xfc, 0x0f, 0xc7, 0xc0, 0x7f, 0x00, 0x00, 
  0xff, 0x83, 0xff, 0x80, 0x0f, 0xc0, 0x01, 0xfb, 0xf0, 0xfc, 0x0f, 0xc7, 0xe0, 0x7f, 0x01, 0xff, 
  0xff, 0x83, 0xff, 0xf8, 0x1f, 0xff, 0xf1, 0xf9, 0xf0, 0xfc, 0x1f, 0x87, 0xe0, 0x7f, 0x01, 0xff, 
  0x00, 0x01, 0xff, 0xfc, 0x1f, 0xff, 0xf1, 0xf9, 0xf9, 0xf8, 0x1f, 0x87, 0xe0, 0x7e, 0x00, 0x00, 
  0x00, 0x00, 0xff, 0xfe, 0x1f, 0xff, 0xf3, 0xf1, 0xf9, 0xf8, 0x3f, 0x07, 0xe0, 0x7e, 0x00, 0x00, 
  0xff, 0x80, 0x1f, 0xff, 0x1f, 0xff, 0xf3, 0xf1, 0xf9, 0xf8, 0x7f, 0x07, 0xe0, 0xfe, 0x01, 0xff, 
  0xff, 0x80, 0x03, 0xff, 0x1f, 0x80, 0x03, 0xf0, 0xf9, 0xf8, 0x7f, 0xff, 0xf0, 0xfe, 0x01, 0xff, 
  0x00, 0x00, 0x00, 0x7f, 0x3f, 0x80, 0x03, 0xf0, 0xfd, 0xf8, 0xff, 0xff, 0xf0, 0xfe, 0x00, 0x00, 
  0x00, 0x0f, 0xe0, 0x7f, 0x3f, 0x80, 0x03, 0xf0, 0xff, 0xf0, 0xff, 0xff, 0xf0, 0xfc, 0x00, 0x00, 
  0xff, 0x8f, 0xe0, 0x7f, 0x3f, 0x00, 0x07, 0xe0, 0xff, 0xf1, 0xff, 0xff, 0xf1, 0xfc, 0x01, 0xff, 
  0xff, 0x8f, 0xe0, 0xfe, 0x3f, 0x00, 0x07, 0xe0, 0x7f, 0xf3, 0xff, 0xff, 0xf1, 0xfc, 0x01, 0xff, 
  0x00, 0x0f, 0xfb, 0xfe, 0x3f, 0xff, 0xe7, 0xe0, 0x7f, 0xf3, 0xf0, 0x07, 0xf9, 0xfc, 0x00, 0x00, 
  0x00, 0x07, 0xff, 0xfc, 0x7f, 0xff, 0xe7, 0xe0, 0x7f, 0xe7, 0xf0, 0x03, 0xf9, 0xf8, 0x00, 0x00, 
  0xff, 0x87, 0xff, 0xf8, 0x7f, 0xff, 0xe7, 0xe0, 0x7f, 0xe7, 0xe0, 0x03, 0xf9, 0xf8, 0x01, 0xff, 
  0xff, 0x83, 0xff, 0xe0, 0x7f, 0xff, 0xef, 0xc0, 0x3f, 0xef, 0xc0, 0x03, 0xfb, 0xf8, 0x01, 0xff, 
  0x00, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//Entradas
int bt_zero = 2;
int bt_hold = 3;
const int bateria = A0;


//Variáveis globais
bool zeroRelativo = false;
bool hold = false;
int range = 90;

void setup() {
  Serial.begin(9600);
  
  pinMode(bt_zero, INPUT_PULLUP);
  pinMode(bt_hold, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  configuraAcelerometro();

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  desenhaLogoSENAI();
  delay(1000);
}

void loop() {

  display.clearDisplay();
  if(digitalRead(bt_zero) == 0){
    if(zeroRelativo) zeroRelativo = false;
    else zeroRelativo = true;
    delay(200);
  }
  if(digitalRead(bt_hold) == 0){
    if(hold) hold = false;
    else hold = true;
    delay(200);
  }
  if(range == 90) desenha_90();
  else desenha_180();
  if(hold) ligaFuncaoHold();
  if(zeroRelativo) ligaFuncaoZero();
  
  if(nivelBateria() < 20) desenhaBateriaBaixa();

  leAcelerometro();
  mostraAngulo();

  display.display();
  delay(100);
}

int leAcelerometro(){
    // Accelerometer Readings
  int x,y,z;   
  adxl.readAccel(&x, &y, &z);         // Read the accelerometer values and store them in variables declared above x,y,z

  // Output Results to Serial
  /* UNCOMMENT TO VIEW X Y Z ACCELEROMETER VALUES */  
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.println(z);
  return y;
}

void configuraAcelerometro(){
  adxl.powerOn();                     // Power on the ADXL345

  adxl.setRangeSetting(16);           // Give the range settings
                                      // Accepted values are 2g, 4g, 8g or 16g
                                      // Higher Values = Wider Measurement Range
                                      // Lower Values = Greater Sensitivity

  adxl.setSpiBit(0);                  // Configure the device to be in 4 wire SPI mode when set to '0' or 3 wire SPI mode when set to 1
                                      // Default: Set to 1
                                      // SPI pins on the ATMega328: 11, 12 and 13 as reference in SPI Library 
   
  adxl.setActivityXYZ(1, 0, 0);       // Set to activate movement detection in the axes "adxl.setActivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setActivityThreshold(75);      // 62.5mg per increment   // Set activity   // Inactivity thresholds (0-255)
 
  adxl.setInactivityXYZ(1, 0, 0);     // Set to detect inactivity in all the axes "adxl.setInactivityXYZ(X, Y, Z);" (1 == ON, 0 == OFF)
  adxl.setInactivityThreshold(75);    // 62.5mg per increment   // Set inactivity // Inactivity thresholds (0-255)
  adxl.setTimeInactivity(10);         // How many seconds of no activity is inactive?

  adxl.setTapDetectionOnXYZ(0, 0, 1); // Detect taps in the directions turned ON "adxl.setTapDetectionOnX(X, Y, Z);" (1 == ON, 0 == OFF)
 
  // Set values for what is considered a TAP and what is a DOUBLE TAP (0-255)
  adxl.setTapThreshold(50);           // 62.5 mg per increment
  adxl.setTapDuration(15);            // 625 μs per increment
  adxl.setDoubleTapLatency(80);       // 1.25 ms per increment
  adxl.setDoubleTapWindow(200);       // 1.25 ms per increment
 
  // Set values for what is considered FREE FALL (0-255)
  adxl.setFreeFallThreshold(7);       // (5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(30);       // (20 - 70) recommended - 5ms per increment
 
  // Setting all interupts to take place on INT1 pin
  //adxl.setImportantInterruptMapping(1, 1, 1, 1, 1);     // Sets "adxl.setEveryInterruptMapping(single tap, double tap, free fall, activity, inactivity);" 
                                                        // Accepts only 1 or 2 values for pins INT1 and INT2. This chooses the pin on the ADXL345 to use for Interrupts.
                                                        // This library may have a problem using INT2 pin. Default to INT1 pin.
  
  // Turn on Interrupts for each mode (1 == ON, 0 == OFF)
  adxl.InactivityINT(0);
  adxl.ActivityINT(0);
  adxl.FreeFallINT(0);
  adxl.doubleTapINT(0);
  adxl.singleTapINT(0);
}

int nivelBateria(){
  int cargaBateria = 83;
  cargaBateria = analogRead(bateria);
  return map(cargaBateria, 0, 1023, 0, 100);
  //return cargaBateria;
}

void ligaFuncaoZero(){
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(40,0);
  //display.print("Z");
  display.write('Z');
}

void ligaFuncaoHold(){
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(60,0);
  display.print("H");
}

float leAngulo(){
  //Comunicação com ADXL345
  float angulo = 45;
  return angulo;
}

void mostraAngulo(){
  display.setTextSize(4);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(M_POS_X,M_POS_Y);
  display.print(String(leAngulo(),1));
  display.drawCircle(M_POS_X + 100, M_POS_Y + 3, 3, SSD1306_WHITE);
}

void desenha_90(){
  display.drawBitmap(80, 0, bitmap_angulo90, 13, 14, 1);
}

void desenha_180(){
  display.drawBitmap(80, 0, bitmap_angulo180, 25, 14, 1);
}

// 'battery_low', 31x14px
//const unsigned char bitmap_battery_low [] PROGMEM = {
void desenhaBateriaBaixa(){
  display.drawBitmap(0, 0, bitmap_battery_low, 31, 14, 1);
}

void desenhaLogoSENAI(void) {
  display.clearDisplay();
  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_senai_preto, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
}
