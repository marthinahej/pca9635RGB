#include "pca9635RGB.h"

/**
 * board_num is the number selected on the BCD rotary switch
 */
void pca9635RGB::begin(byte board_num, boolean wire_begin, boolean init_drivers)
{
    if (wire_begin)
    {
        I2c.begin();
    }
    if (init_drivers)
    {
        PCA9635.reset(); // This should reset all drivers on the bus
        PCA9635.set_sleep(0x0); // Wake up oscillators (via all-call)
        delayMicroseconds(500); // Wait for the oscillators to stabilize
        PCA9635.set_driver_mode(0x0); // Default to open-drain mode for all drivers (via all-call)
        PCA9635.set_led_mode(3); // Default to PWM mode for all drivers (via all-call)
    }
    // Initialize the pca9635 instances with correct addresses
    this->set_board_address(board_num);
    R.enable_subaddr(1);
    G.enable_subaddr(2);
    B.enable_subaddr(3);
}


void pca9635RGB::set_board_address(byte board_num)
{
    R.begin(board_num | (0x1 << 5), false, false);
    G.begin(board_num | (0x2 << 5), false, false);
    B.begin(board_num | (0x3 << 5), false, false);
}

// Funky way to handle default arguments
void pca9635RGB::begin(byte board_addr, boolean wire_begin)
{
    pca9635RGB::begin(board_addr, wire_begin, true);
}

void pca9635RGB::begin(byte board_addr)
{
    pca9635RGB::begin(board_addr, true, true);
}

void pca9635RGB::begin()
{
    pca9635RGB::begin(0x0, true, true);
}

boolean pca9635RGB::set_rgb(byte ledno, byte rcycle, byte gcycle, byte bcycle)
{
    // TODO: When I2C library allows lower level access write as single repeated-start sequence for atomicity
    boolean rstat = R.set_led_pwm(ledno, rcycle);
    boolean gstat = G.set_led_pwm(ledno, gcycle);
    boolean bstat = B.set_led_pwm(ledno, bcycle);
    return rstat && gstat && bstat;
}

/*
pca9635::set_led_pwm(byte ledno, byte cycle)
{

*/
