/* LCD Pinout
 *  
 * 1  -> VSS (GND)
 * 2  -> VDD (5V)
 * 3  -> VO (GND/Potenciometro)
 * 4  -> RS (GPIO)
 * 5  -> R/W (GND/GPIO)
 * 6  -> E (GPIO)
 * 7  -> D0 (-/GPIO)
 * 8  -> D1 (-/GPIO)
 * 9  -> D2 (-/GPIO)
 * 10 -> D3 (-/GPIO)
 * 11 -> D4 (GPIO)
 * 12 -> D5 (GPIO)
 * 13 -> D6 (GPIO)
 * 14 -> D7 (GPIO)
 * 15 -> LED+ (220Ohm->5V)
 * 16 -> LED- (GND)
 */

#include <LiquidCrystal.h>
#include <SFE_BMP180.h>
#include <Wire.h>

// Pines rs, enable, d4, d5, d6, d7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Sensor de presion
SFE_BMP180 sensor;

// Variables
uint8_t readDelay;
float temperature;
float pressure;

void setup()
{
    sensor.begin();
    lcd.begin(16,2);
}

void loop()
{
    // Lectura de temperatura
    readDelay = sensor.startTemperature();
    delay(readDelay);
    sensor.getTemperature(temperature);
    
    // Lectura de presion
    readDelay = sensor.startPressure(3);
    delay(readDelay);
    sensor.getPressure(pressure, temperature);
    
    display_pressure(pressure);
    
    // Delay cercano a 0.5s
    delay(500);
}

void display_pressure(double pressure)
{
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("Presion:");
    
    lcd.setCursor(0,1);
    lcd.print("> "+String(pressure)+" Pa");
}
