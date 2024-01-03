
#ifndef SCREEN_H
# define SCREEN_H

# include "types.h"

// https://wiki.osdev.org/Printing_To_Screen

// SCREEN ADDRESS
# define SCREEN_ADDRESS 0xB8000
# define SCREEN_CHAR_HEIGHT 25 // print up to 25 characters
# define SCREEN_CHAR_LENGTH 80 // print up to 80 characters
# define SCREEN_HEIGHT 50
# define SCREEN_LENGTH 160
# define SCREEN_SIZE (SCREEN_CHAR_HEIGHT * SCREEN_CHAR_LENGTH * 2) // 2 bytes per character
# define SCREEN_LIMIT (SCREEN_ADDRESS + SCREEN_SIZE)

// COLORS
# define SCREEN_BLACK 0
# define SCREEN_BLUE 1
# define SCREEN_GREEN 2
# define SCREEN_CYAN 3
# define SCREEN_RED 4
# define SCREEN_PURPLE 5
# define SCREEN_BROWN 6
# define SCREEN_GRAY 7
# define SCREEN_DARK_GRAY 8
# define SCREEN_LIGHT_BLUE 9
# define SCREEN_LIGHT_GREEN 10
# define SCREEN_LIGHT_CYAN 11
# define SCREEN_LIGHT_RED 12
# define SCREEN_LIGHT_PURPLE 13
# define SCREEN_YELLOW 14
# define SCREEN_WHITE 15

void reset_screen(void);
void put_char(u8 ch, u8 text_color);
void print(u8 *str);

#endif
