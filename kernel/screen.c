#include "types.h"
#include "screen.h"

u16 offset = 0;

void reset_screen(void)
{
	u16 i = 0;

	while (i < SCREEN_SIZE)
	{
		((u8 *)SCREEN_ADDRESS)[i] = 0;
		++i;
	}
	offset = 0;
}

static void scroll_up(void)
{
	u8 *dst = (u8 *)SCREEN_ADDRESS;
	u8 *src = (u8 *)(SCREEN_ADDRESS + SCREEN_LENGTH);
	u16 i;
	while (src < (u8 *)SCREEN_LIMIT)
	{
		i = 0;
		while (i < SCREEN_LENGTH)
		{
			dst[i] = src[i];
			++i;
		}
		src += SCREEN_LENGTH;
		dst += SCREEN_LENGTH;
	}
	i = 0;
	while (i < SCREEN_LENGTH)
		dst[i++] = 0;
	offset -= SCREEN_LENGTH;
}

void put_char(u8 ch, u8 text_color)
{
	if (offset >= SCREEN_SIZE)
		scroll_up();
	switch (ch)
	{
		case '\n':
			offset += SCREEN_LENGTH - (offset % SCREEN_LENGTH);
			break ;
		default:
			((u8 *)SCREEN_ADDRESS)[offset++] = ch;
			((u8 *)SCREEN_ADDRESS)[offset++] = text_color;
	}
}

void print(u8 *str)
{
	while (*str != '\0')
		put_char(*(str++), SCREEN_GREEN);
}

