/*
* 
*  Simple code for testing a R61529 LCD (320x480 pixels) display 8080 (MIPI-DBI Type B) connection
*  This example should run on any Arduino device (In my case it was ESP32) as it uses standard Arduino functions.
*  Please edit PIN definitions below according to your connection.
*
*/

#include <Arduino.h>
#define PIN_CSX 13
#define PIN_DCX 33
#define PIN_WRX 32
#define PIN_RDX 27
#define PIN_RESX 26
#define PIN_D0 16
#define PIN_D1 17
#define PIN_D2 18
#define PIN_D3 19
#define PIN_D4 21
#define PIN_D5 22
#define PIN_D6 23
#define PIN_D7 25

void setDataDirection(uint8_t mode){
  pinMode(PIN_D0, mode);
  pinMode(PIN_D1, mode);
  pinMode(PIN_D2, mode);
  pinMode(PIN_D3, mode);
  pinMode(PIN_D4, mode);
  pinMode(PIN_D5, mode);
  pinMode(PIN_D6, mode);
  pinMode(PIN_D7, mode);
}

void setDataPins(uint32_t data){
  digitalWrite(PIN_D0, (data & 0b00000001));
  digitalWrite(PIN_D1, ((data & 0b00000010)));
  digitalWrite(PIN_D2, ((data & 0b00000100)));
  digitalWrite(PIN_D3, ((data & 0b00001000)));
  digitalWrite(PIN_D4, ((data & 0b00010000)));
  digitalWrite(PIN_D5, ((data & 0b00100000)));
  digitalWrite(PIN_D6, ((data & 0b01000000)));
  digitalWrite(PIN_D7, ((data & 0b10000000)));
}

void writeData(uint32_t byte){
  digitalWrite(PIN_DCX, HIGH); //select to write data
  digitalWrite(PIN_WRX, LOW); //get ready to write data
  
  setDataPins(byte);
  //delayMicroseconds(1);
  digitalWrite(PIN_WRX, HIGH); //write in data to LCD

  //delayMicroseconds(1);
}

void writeCommand(uint32_t byte){
  digitalWrite(PIN_DCX, LOW); //select to write command
  digitalWrite(PIN_WRX, LOW); //get ready to write command

  setDataPins(byte);
  delayMicroseconds(1);
  digitalWrite(PIN_WRX, HIGH); //write in data to LCD

  delayMicroseconds(1);
}

void init(){
  delay(100);
  digitalWrite(PIN_CSX, LOW); //chip enable
  writeCommand(0x11); //exit sleep mode;
  delay(200);
  writeCommand(0xB0); //manufacturer command access protect
  writeData(0x04); //allow access to additional manufacturer's commands
  delay(1);

  writeCommand(0xB3); //Frame Memory Access and Interface Setting
  writeData(0x02); // reset start position of a window area address...
  writeData(0x00); //TE pin is used. TE signal is output every frame.
  writeData(0x00); // empty according to the datasheet - does nothing;
  writeData(0x00); // convert 16/18 bits to 24bits data by writing zeroes to LSBs. Sets image data write/read format(?)
  writeData(0x00);  // ???? (not needed?)
  delay(1);

  writeCommand(0xB4); //Display Mode
  writeData(0x00); //Uses internal oscillator
  delay(1);

  writeCommand(0xC0); // Panel Driving Setting;
  writeData(0x03); // Output polarity is inverted. Left/right interchanging scan. Forward scan. BGR mode (depends on other settings). S960 → S1 (depends)
  writeData(0xDF); // Number of lines for driver to drive - 480.
  writeData(0x40); // Scan start position - Gate1. (depend on other param);
  writeData(0x10); // Dot inversion. Dot inversion in not-lit display area. If 0x13 - both will be set to 'column inversion'.
  writeData(0x00); // settings for non-lit display area...
  writeData(0x01); // 3 frame scan interval in non-display area...
  writeData(0x00); // Source output level in retrace period...
  writeData(0x55);//54 . Internal clock divider = 5 (low and high periods).

  writeCommand(0xC1); //Display Timing Setting for Normal Mode
  writeData(0x07); // Clock devider = 12. 14MHz/12. Used by display circuit and step-up circuit.
  writeData(0x27); // These bits set the number of clocks in 1 line period. 0x27 - 39 clocks.
  writeData(0x08); // Number of back porch lines. 0x08 - 8 lines.
  writeData(0x08); // Number of front porch lines. 0x08 - 8lines.
  writeData(0x00); // Spacial configuriation mode 1 (?). 1 line inversion mode (?).

  writeCommand(0xC4); // Source/Gate Driving Timing Setting
  writeData(0x57); // falling position (stop) of gate driver - 4 clocks... gate start position - 8 clocks...
  writeData(0x00); // nothing to set up according to the datasheet
  writeData(0x05); // Source precharge period (GND) - 5 clocks.
  writeData(0x03); // source precharge period (VCI) - 3 clocks.

  writeCommand(0xC6); //DPI polarity control
  writeData(0x04); // VSYNC -Active Low. HSYNC - Active Low. DE pin enable data write in when DE=1. Reads data on the rising edge of the PCLK signal.

  //----Gamma setting start-----
  writeCommand(0xC8);
  writeData(0x03);
  writeData(0x12);
  writeData(0x1A);
  writeData(0x24);
  writeData(0x32);
  writeData(0x4B);
  writeData(0x3B);
  writeData(0x29);
  writeData(0x1F);
  writeData(0x18);
  writeData(0x12);
  writeData(0x04);

  writeData(0x03);
  writeData(0x12);
  writeData(0x1A);
  writeData(0x24);
  writeData(0x32);
  writeData(0x4B);
  writeData(0x3B);
  writeData(0x29);
  writeData(0x1F);
  writeData(0x18);
  writeData(0x12);
  writeData(0x04);

  writeCommand(0xC9);
  writeData(0x03);
  writeData(0x12);
  writeData(0x1A);
  writeData(0x24);
  writeData(0x32);
  writeData(0x4B);
  writeData(0x3B);
  writeData(0x29);
  writeData(0x1F);
  writeData(0x18);
  writeData(0x12);
  writeData(0x04);

  writeData(0x03);
  writeData(0x12);
  writeData(0x1A);
  writeData(0x24);
  writeData(0x32);
  writeData(0x4B);
  writeData(0x3B);
  writeData(0x29);
  writeData(0x1F);
  writeData(0x18);
  writeData(0x12);
  writeData(0x04);

  writeCommand(0xCA);
  writeData(0x03);
  writeData(0x12);
  writeData(0x1A);
  writeData(0x24);
  writeData(0x32);
  writeData(0x4B);
  writeData(0x3B);
  writeData(0x29);
  writeData(0x1F);
  writeData(0x18);
  writeData(0x12);
  writeData(0x04);

  writeData(0x03);
  writeData(0x12);
  writeData(0x1A);
  writeData(0x24);
  writeData(0x32);
  writeData(0x4B);
  writeData(0x3B);
  writeData(0x29);
  writeData(0x1F);
  writeData(0x18);
  writeData(0x12);
  writeData(0x04);
//---Gamma setting end--------

  writeCommand(0xD0); // Power (charge pump) settings
  writeData(0x99);//DC4~1//A5. Set up clock cycle of the internal step up controller.
  writeData(0x06);//BT // Set Voltage step up factor.
  writeData(0x08);// default according to the datasheet - does nothing.
  writeData(0x20);// VCN step up cycles.
  writeData(0x29);//VC1, VC2// VCI3 voltage = 2.70V;  VCI2 voltage = 3.8V.
  writeData(0x04);// default 
  writeData(0x01);// default 
  writeData(0x00);// default 
  writeData(0x08);// default
  writeData(0x01);// default
  writeData(0x00);// default
  writeData(0x06);// default
  writeData(0x01);// default
  writeData(0x00);// default
  writeData(0x00);// default
  writeData(0x20);// default

  writeCommand(0xD1);//VCOM setting
  writeData(0x00);//disable write to VDC[7:0].
  writeData(0x20);//45 38 VPLVL// voltage of γ correction registers for positive polarity
  writeData(0x20);//45 38 VNLVL// voltage of γ correction registers for negative polarity
  writeData(0x15);//32 2A VCOMDC// VNLVL x 0.063

  writeCommand(0xE0);//NVM Access Control
  writeData(0x00);//NVM access is disabled
  writeData(0x00);//Erase operation (disabled).
  writeData(0x00);//TE pin works as tearing effect pin. 
  // should be one more writeData(0x00); according to the datasheet.

  writeCommand(0xE1); //set_DDB_write_control
  writeData(0x00); 
  writeData(0x00);
  writeData(0x00);
  writeData(0x00);
  writeData(0x00);
  writeData(0x00);

  writeCommand(0xE2); //NVM Load Control
  writeData(0x00); // does not execute data load from the NVM to each command

  writeCommand(0x36); //set_address_mode
  writeData(0x00); // data is not flipped in any way?

  writeCommand(0x3A); // set_pixel_format
  writeData(0x77);// 16-Bit/pixel = 55h, 24-bit/pixel = 77h

  writeCommand(0x2A); //set_column_address
  writeData(0x00); // starts from 0th frame buffer address
  writeData(0x00);
  writeData(0x01);
  writeData(0x3F);//320 - uses all columns

  writeCommand(0x2B); //set_page_address
  writeData(0x00); // starts from 0th frame buffer address
  writeData(0x00);
  writeData(0x01);
  writeData(0xDF);//480 - uses all lines in the frame buffer

  writeCommand(0x29); //set_display_on - This command causes the display module to start displaying the image data on the display device.
  delay(20);

  //writeCommand(0x2C); // write_memory_start
  //delay(10000);
  //writeCommand(0x10);
}

void setup() {
  delay(500);

  pinMode(PIN_CSX, OUTPUT);
  pinMode(PIN_DCX, OUTPUT);
  pinMode(PIN_WRX, OUTPUT);
  pinMode(PIN_RDX, OUTPUT);
  pinMode(PIN_RESX, OUTPUT);
  setDataDirection(OUTPUT);
  digitalWrite(PIN_RESX, LOW);
  digitalWrite(PIN_CSX, HIGH);
  digitalWrite(PIN_DCX, HIGH);
  digitalWrite(PIN_WRX, HIGH);
  digitalWrite(PIN_RDX, HIGH);
  delay(200);
  digitalWrite(PIN_RESX, HIGH);
  
  init();

  //let's write green:
  writeCommand(0x2C); // write_memory_start
  for(uint32_t i = 0; i<=(480*320); i++) { // fill all screen (480x320) pixels with 3x8bit color
    writeData(0x00); //R
    writeData(0xFF); //G
    writeData(0x00); //B
  } 

  delay(5000);
  writeCommand(0x2C); // write_memory_start
  for(uint32_t i = 0; i<=(480*320); i++) { // fill all screen (480x320) pixels with 3x8bit color
    writeData(0xFF); //R
    writeData(0x00); //G
    writeData(0x00); //B
  } 

  delay(5000);
  writeCommand(0x2C); // write_memory_start
  for(uint32_t i = 0; i<=(480*320); i++) { // fill all screen (480x320) pixels with 3x8bit color
    writeData(0x00); //R
    writeData(0x00); //G
    writeData(0xFF); //B
  } 
  
  delay(5000);
  writeCommand(0x2C); // write_memory_start
  for(uint32_t i = 0; i<=(480*320); i++) { // fill all screen (480x320) pixels with 3x8bit color
    writeData(0x00); //R
    writeData(0x00); //G
    writeData(0x00); //B
  }

  delay(5000);
  writeCommand(0x2C); // write_memory_start
  for(uint32_t i = 0; i<=(480*320); i++) { // fill all screen (480x320) pixels with 3x8bit color
    writeData(0xFF); //R
    writeData(0xFF); //G
    writeData(0xFF); //B
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:
}
