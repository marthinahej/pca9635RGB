// safety againts double-include
#ifndef pca9635RGB_h
#define pca9635RGB_h
#include <Arduino.h> 
#include <pca9635.h>

class pca9635RGB
{
    public:
        // Initialize the object and chip        
        void begin(byte board_num, boolean wire_begin, boolean init_drivers);
        // A funky way to handle optional arguments
        void begin(byte board_num, boolean wire_begin);
        void begin(byte board_num);
        void begin();
        void set_board_address(byte board_num);
        boolean set_rgb(byte ledno, byte rcycle, byte gcycle, byte bcycle);
        // Color channel instances, allow public access for debugging
        pca9635 R;
        pca9635 G;
        pca9635 B;
        
};

#endif
// *********** END OF CODE **********
