#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

// Used for software SPI
#define LIS3DH_CLK 14
#define LIS3DH_MISO 15
#define LIS3DH_MOSI 16
// Used for hardware & software SPI
#define LIS3DH_CS 17

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
  Serial.begin(9600);
  while (!Serial) delay(10);     // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("LIS3DH test!");
  
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");
  
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");
}

void loop() {
//  uncomment next four lines to show all results on a single line, otherwise results will display successively.
//  Serial.write(27);       // ESC command
//  Serial.print("[2J");    // clear screen command
//  Serial.write(27);
//  Serial.print("[H");     // cursor to home command
  
  lis.read();      // get X Y and Z data at once
  // Then print out the raw data
  Serial.print("X:  "); Serial.print(lis.x); 
  Serial.print("  \tY:  "); Serial.print(lis.y); 
  Serial.print("  \tZ:  "); Serial.print(lis.z); 

  /* Or....get a new sensor event, normalized */ 
  sensors_event_t event; 
  lis.getEvent(&event);
  
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
  Serial.print(" \tY: "); Serial.print(event.acceleration.y); 
  Serial.print(" \tZ: "); Serial.print(event.acceleration.z); 
  Serial.println(" m/s^2 ");

  Serial.println();

  delay(200);

  lis.read(); // get X Y and Z data at once
  double x = lis.x, y=lis.y, z=lis.z, pitch=0.00, roll=0.00; 
  Serial.print(lis.x);
  Serial.print(" ");
  Serial.print(lis.y);
  Serial.print(" ");
  Serial.println(lis.z);
  delay(10);

  roll = atan2(y, z) * 57.3;
  pitch = atan2((-x),sqrt(y*y+z*z))*57.3;
  Serial.print(roll);
  Serial.print(" ");
  Serial.print(pitch); 

}
