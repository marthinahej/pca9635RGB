/**
 * RGB (3x PCA9625 drivers in a handy configuration) led driver board 
 *
 * @see https://github.com/HelsinkiHacklab/reactor/blob/master/blueprints/ledcontroller.brd
 *
 * Remember your I2C pull-up resistors
 */
// Get this from http://dsscircuits.com/articles/arduino-i2c-master-library.html
#include <I2C.h> // For some weird reason including this in the relevant .h file does not work
// For the weirdest reason this does not get to the scope of the libraries
#define I2C_DEVICE_DEBUG
#include <i2c_device.h> // For some weird reason including this in the relevant .h file does not work
#include <pca9635.h> // For some weird reason including this in the relevant .h file does not work
#include <pca9635RGB.h>

// Container for the device
pca9635RGB driverboard;

void setup()
{
    Serial.begin(115200);
    I2c.begin();
    I2c.timeOut(500); // 500ms timeout to avoid lockups
    I2c.pullup(false); //Disable internal pull-ups
    I2c.setSpeed(true); // Fast-mode support

    // Set device address and call I2c.begin()
    Serial.println(F("Initializing led drivers"));
    driverboard.begin(0);

    // Dump the driver mode registers to check they're correct
    driverboard.R.dump_registers(0x0, 0x01);
    driverboard.G.dump_registers(0x0, 0x01);
    driverboard.B.dump_registers(0x0, 0x01);
    // Dump the led mode registers to check they're correct
    driverboard.R.dump_registers(0x14, 0x17);
    driverboard.G.dump_registers(0x14, 0x17);
    driverboard.B.dump_registers(0x14, 0x17);



    Serial.println(F("Booted"));
}

const byte test_leds_max = 8;
void loop()
{
    for (byte ledno = 0; ledno < test_leds_max; ledno++)
    {
        Serial.print(F("Turning on R led "));
        Serial.println(ledno, DEC);
        //driverboard.R.set_led_mode(ledno, 1);
        driverboard.R.set_led_pwm(ledno, 255);
        delay(250);
        Serial.print(F("Turning off R led "));
        Serial.println(ledno, DEC);
        driverboard.R.set_led_pwm(ledno, 0);
        //driverboard.R.set_led_mode(ledno, 0);
        Serial.print(F("Turning on G led "));
        Serial.println(ledno, DEC);
        //driverboard.G.set_led_mode(ledno, 1);
        driverboard.G.set_led_pwm(ledno, 255);
        delay(250);
        Serial.print(F("Turning off G led "));
        Serial.println(ledno, DEC);
        driverboard.G.set_led_pwm(ledno, 0);
        //driverboard.G.set_led_mode(ledno, 0);
        Serial.print(F("Turning on B led "));
        Serial.println(ledno, DEC);
        //driverboard.B.set_led_mode(ledno, 1);
        driverboard.B.set_led_pwm(ledno, 255);
        delay(250);
        Serial.print(F("Turning off B led "));
        Serial.println(ledno, DEC);
        driverboard.B.set_led_pwm(ledno, 0);
        //driverboard.B.set_led_mode(ledno, 0);
    }
    delay(500);
    for (byte ledno = 0; ledno < test_leds_max; ledno++)
    {
        Serial.print(F("RGB Fading out led "));
        Serial.println(ledno, DEC);
        for (byte value=128; value > 0; value--)
        {
            driverboard.set_rgb(ledno, value, value, value);
            delay(5);
        }
        driverboard.set_rgb(ledno, 0x0, 0x0, 0x0);
        delay(250);
    }
    delay(500);
}
