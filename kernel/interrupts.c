#include "types.h"
#include "screen.h"

void isr_default_int(void)
{
        /* print((u8 *)"interrupt\n"); */
}

void isr_clock_int(void)
{
        static int tic = 0;
        static int sec = 0;
        tic++;
        if (tic % 100 == 0) {
                sec++;
                tic = 0;
                print((u8 *)"clock\n");
        }
}

void isr_keyboard_int(void)
{
        print((u8 *)"keyboard\n");
}
 
