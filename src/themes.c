/*-------------------------------------------------------------------------
 *
 * themes.c
 *	  themes initialization
 *
 * Portions Copyright (c) 2017-2018 Pavel Stehule
 *
 * IDENTIFICATION
 *	  src/themes.c
 *
 *-------------------------------------------------------------------------
 */

#include "themes.h"
#include <string.h>

attr_t		theme_attrs[50];

#define theme_attr(id)		(COLOR_PAIR(id) | theme_attrs[id])

#ifndef A_ITALIC
#define A_ITALIC	A_DIM
#endif

static void
set_colour(short id, short foreground, short background, bool light, attr_t attrs)
{
	if (COLORS == 8 || foreground == -1)
	{
		init_pair(id, foreground, background);
		theme_attrs[id] = attrs | (light ? A_BOLD : 0);
	}
	else if (foreground < 8)
	{
		init_pair(id, foreground + (light ? 8 : 0), background);
		theme_attrs[id] = attrs;
	}
	else
	{
		init_pair(id, foreground, background);
		theme_attrs[id] = attrs;
	}
}

static int
if_in_int(int v, const int *s, int v1, int v2)
{
	while(*s != -1)
	{
		if (v == *s)
			return v1;
		s += 1;
	}
	return v2;
}

/* 0..255 rgb based colors */
static void
init_color_rgb_ff(short color, short r, short g, short b)
{
	init_color(color,
			   (r / 255.0) * 1000.0,
			   (g / 255.0) * 1000.0,
			   (b / 255.0) * 1000.0);
}

/*
 * Set color pairs based on style
 */
void
initialize_color_pairs(int theme, bool bold_labels, bool bold_cursor)
{
	attr_t labels_attr = bold_labels ? A_BOLD : 0;
	attr_t cursor_attr = bold_cursor ? A_BOLD : 0;

	init_pair(21, COLOR_WHITE, COLOR_BLACK);		/* Fx keys */

	switch (theme)
	{
		case 0:
			use_default_colors();

			set_colour(2, COLOR_BLACK, COLOR_WHITE, false, 0);			/* top bar colors */
			set_colour(3, -1, -1, false, 0);							/* data alphanumeric */
			set_colour(4, -1, -1, true, labels_attr);							/* fix rows, columns */
			set_colour(5, COLOR_BLACK, COLOR_WHITE, true, cursor_attr);			/* active cursor over fixed cols */
			set_colour(6, COLOR_BLACK, COLOR_WHITE, true, cursor_attr);			/* active cursor */
			set_colour(7, COLOR_BLACK, COLOR_WHITE, false, 0);			/* title color */
			set_colour(8, COLOR_BLACK, COLOR_WHITE, false, 0);			/* expanded header */
			set_colour(9, -1, -1, false, 0);							/* footer */
			set_colour(10, COLOR_BLACK, COLOR_WHITE, true, cursor_attr);		/* footer cursor */
			set_colour(11, COLOR_BLACK, COLOR_WHITE, false, 0);		/* cursor over decoration */
			set_colour(12, COLOR_BLACK, COLOR_WHITE, false, 0);		/* bottom bar colors */
			set_colour(13, COLOR_BLACK, COLOR_WHITE, false, 0);		/* light bottom bar colors */
			set_colour(14, COLOR_BLACK, COLOR_WHITE, false, 0);		/* color of bookmark lines */
			set_colour(15, COLOR_WHITE, COLOR_BLACK, false, 0);		/* color of marked search pattern */
			set_colour(16, -1, -1, false, 0);							/* color of line with pattern */
			set_colour(17, -1, -1, false, 0);							/* color of line art with pattern */
			set_colour(18, -1, -1, false, 0);		/* color of marked search pattern in no-hl line mode */
			set_colour(19, -1, -1, false, 0);		/* color of marked search pattern in cursor */
			set_colour(20, COLOR_WHITE, COLOR_BLACK, false, 0);
			set_colour(21, -1, -1, false, 0);							/* rownum colors */

			break;
		case 1:
			assume_default_colors(COLOR_WHITE, COLOR_BLUE);

			set_colour(2, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(3, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(4, COLOR_YELLOW, COLOR_BLUE, true, labels_attr);
			set_colour(5, COLOR_YELLOW, COLOR_CYAN, true, cursor_attr);
			set_colour(6, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(7, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(8, COLOR_RED, COLOR_BLUE, false, 0);
			set_colour(9, COLOR_CYAN, COLOR_BLUE, false, 0);
			set_colour(10, COLOR_BLACK, COLOR_CYAN, false, cursor_attr);
			set_colour(11, COLOR_WHITE, COLOR_CYAN, false, 0);
			set_colour(12, COLOR_WHITE, COLOR_CYAN, true, 0);
			set_colour(13, COLOR_YELLOW, COLOR_CYAN, true, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_YELLOW, COLOR_GREEN, true, 0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(17, COLOR_WHITE, COLOR_GREEN, false, 0);
			set_colour(18, COLOR_GREEN, COLOR_BLUE, false, 0);
			set_colour(19, COLOR_YELLOW, COLOR_CYAN, true, 0);
			set_colour(20, COLOR_WHITE, COLOR_BLACK, true, 0);
			set_colour(21, COLOR_WHITE, COLOR_CYAN, true, 0);
			break;
		case 2:
			assume_default_colors(COLOR_WHITE, COLOR_CYAN);

			set_colour(2, COLOR_BLACK, COLOR_WHITE, false,0);
			set_colour(3, COLOR_WHITE, COLOR_CYAN, true, 0);
			set_colour(4, COLOR_WHITE, COLOR_CYAN, true, labels_attr);
			set_colour(5, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(6, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(7, COLOR_YELLOW, COLOR_WHITE, true,0);
			set_colour(8, COLOR_WHITE, COLOR_BLUE, true,0);
			set_colour(9, COLOR_BLUE, COLOR_CYAN, false,0);
			set_colour(10, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(11, COLOR_WHITE, COLOR_BLUE, false,0);
			set_colour(12, COLOR_WHITE, COLOR_BLUE, true,0);
			set_colour(13, COLOR_WHITE, COLOR_BLUE, true,0);
			set_colour(14, COLOR_WHITE, COLOR_MAGENTA, true,0);
			set_colour(15, COLOR_YELLOW, COLOR_GREEN, true,0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false,0);
			set_colour(17, COLOR_WHITE, COLOR_GREEN, false,0);
			set_colour(18, COLOR_YELLOW, COLOR_GREEN, true,0);
			set_colour(19, COLOR_YELLOW, COLOR_BLUE, true,0);
			set_colour(20, COLOR_WHITE, COLOR_BLACK, false,0);
			set_colour(21, COLOR_WHITE, COLOR_CYAN, false,0);
			break;
		case 3:
			assume_default_colors(COLOR_BLACK, COLOR_CYAN);

			set_colour(2, COLOR_BLACK, COLOR_WHITE, false, 0);
			set_colour(3, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(4, COLOR_WHITE, COLOR_CYAN, true, labels_attr);
			set_colour(5, COLOR_WHITE, COLOR_BLACK, true, cursor_attr);
			set_colour(6, COLOR_CYAN, COLOR_BLACK, true, cursor_attr);
			set_colour(7, COLOR_BLACK, COLOR_WHITE, false, 0);
			set_colour(8, COLOR_WHITE, COLOR_CYAN, true, 0);
			set_colour(9, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(10, COLOR_CYAN, COLOR_BLACK, true, cursor_attr);
			set_colour(11, COLOR_CYAN, COLOR_BLACK, false, 0);
			set_colour(12, COLOR_CYAN, COLOR_BLACK, false, 0);
			set_colour(13, COLOR_WHITE, COLOR_BLACK, true, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_WHITE, COLOR_GREEN, true, 0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(17, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(18, COLOR_WHITE, COLOR_GREEN, true, 0);
			set_colour(19, COLOR_YELLOW, COLOR_BLACK, true, 0);
			set_colour(20, COLOR_WHITE, COLOR_BLUE, true, 0);
			set_colour(21, COLOR_BLACK, COLOR_CYAN, false, 0);

			break;
		case 4:
			assume_default_colors(COLOR_BLACK, COLOR_WHITE);

			set_colour(2, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(3, COLOR_BLACK, COLOR_WHITE, false, 0);
			set_colour(4, COLOR_BLACK, COLOR_WHITE, true, labels_attr);
			set_colour(5, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(6, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(7, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(8, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(9, COLOR_BLACK, COLOR_WHITE, false, 0);
			set_colour(10, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(11, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(12, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(13, COLOR_WHITE, COLOR_BLUE, true, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_YELLOW, COLOR_GREEN, false, 0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(17, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(18, COLOR_YELLOW, COLOR_GREEN, false, 0);
			set_colour(19, COLOR_YELLOW, COLOR_CYAN, false, 0);
			set_colour(20, COLOR_WHITE, COLOR_CYAN, false, 0);

			break;
		case 5:
			use_default_colors();

			set_colour(2, COLOR_GREEN, COLOR_BLUE, true, 0);
			set_colour(3, -1, -1, false, 0);
			set_colour(4, COLOR_CYAN, -1, true, labels_attr);
			set_colour(5, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(6, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(7, COLOR_GREEN, COLOR_BLUE, true, 0);
			set_colour(8, COLOR_BLACK, COLOR_BLUE, false, 0);
			set_colour(9, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(10, COLOR_BLACK, COLOR_CYAN, false, cursor_attr);
			set_colour(11, -1, COLOR_CYAN, false, 0);
			set_colour(12, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(13, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_YELLOW, COLOR_GREEN, false, 0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(17, -1, COLOR_GREEN, false, 0);
			set_colour(18, COLOR_YELLOW, COLOR_GREEN, false, 0);
			set_colour(19, COLOR_YELLOW, COLOR_CYAN, false, 0);
			set_colour(20, COLOR_WHITE, COLOR_CYAN, false, 0);

			break;
		case 6:
			assume_default_colors(COLOR_WHITE, COLOR_BLACK);

			set_colour(2, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(3, COLOR_WHITE, COLOR_BLACK, false, 0);
			set_colour(4, COLOR_CYAN, COLOR_BLACK, true, labels_attr);
			set_colour(5, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(6, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(7, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(8, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(9, COLOR_CYAN, COLOR_BLACK, false, 0);
			set_colour(10, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(11, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(12, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(13, COLOR_WHITE, COLOR_BLUE, true, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_YELLOW, COLOR_GREEN, false, 0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(17, COLOR_WHITE, COLOR_GREEN, false, 0);
			set_colour(18, COLOR_YELLOW, COLOR_BLACK, false, 0);
			set_colour(19, COLOR_CYAN, COLOR_BLUE, false, 0);
			set_colour(20, COLOR_CYAN, COLOR_BLUE, false, 0);

			break;
		case 7:
			assume_default_colors(COLOR_GREEN, COLOR_BLACK);

			set_colour(2, COLOR_CYAN, COLOR_BLACK, false, 0);
			set_colour(3, COLOR_GREEN, COLOR_BLACK, false, 0);
			set_colour(4, COLOR_GREEN, COLOR_BLACK, true, labels_attr);
			set_colour(5, COLOR_WHITE, COLOR_GREEN, true, cursor_attr);
			set_colour(6, COLOR_WHITE, COLOR_GREEN, true, cursor_attr);
			set_colour(7, COLOR_CYAN, COLOR_BLACK, false, 0);
			set_colour(8, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(9, COLOR_CYAN, COLOR_BLACK, false, 0);
			set_colour(10, COLOR_WHITE, COLOR_GREEN, true, cursor_attr);
			set_colour(11, COLOR_GREEN, COLOR_GREEN, true, 0);
			set_colour(12, COLOR_WHITE, COLOR_GREEN, true, 0);
			set_colour(13, COLOR_WHITE, COLOR_GREEN, true, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_WHITE, COLOR_CYAN, false, 0);
			set_colour(16, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(17, COLOR_GREEN, COLOR_CYAN, false, 0);
			set_colour(18, COLOR_CYAN, COLOR_BLACK, false, 0);
			set_colour(19, COLOR_CYAN, COLOR_GREEN, false, 0);
			set_colour(20, COLOR_WHITE, COLOR_BLACK, false, 0);
			set_colour(21, COLOR_CYAN, COLOR_BLACK, false, 0);

			break;
		case 8:
			assume_default_colors(COLOR_CYAN, COLOR_BLUE);

			set_colour(2, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(3, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(4, COLOR_WHITE, COLOR_BLUE, true, labels_attr);
			set_colour(5, COLOR_WHITE, COLOR_CYAN, true, cursor_attr);
			set_colour(6, COLOR_WHITE, COLOR_CYAN, true, cursor_attr);
			set_colour(7, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(8, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(9, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(10, COLOR_WHITE, COLOR_CYAN, true, cursor_attr);
			set_colour(11, COLOR_BLUE, COLOR_CYAN, false, 0);
			set_colour(12, COLOR_WHITE, COLOR_CYAN, true, 0);
			set_colour(13, COLOR_WHITE, COLOR_CYAN, true, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_YELLOW, COLOR_GREEN, true, 0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(17, COLOR_CYAN, COLOR_GREEN, false, 0);
			set_colour(18, COLOR_CYAN, COLOR_BLUE, false, 0);
			set_colour(19, COLOR_YELLOW, COLOR_CYAN, true, 0);
			set_colour(20, COLOR_YELLOW, COLOR_BLACK, true, 0);
			set_colour(21, COLOR_CYAN, COLOR_BLUE, false, 0);

			break;
		case 9:
			assume_default_colors(COLOR_WHITE, COLOR_BLUE);

			set_colour(2, COLOR_BLACK, COLOR_WHITE, false, 0);
			set_colour(3, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(4, COLOR_CYAN, COLOR_BLUE, true, labels_attr);
			set_colour(5, COLOR_WHITE, COLOR_CYAN, true, cursor_attr);
			set_colour(6, COLOR_WHITE, COLOR_CYAN, true, cursor_attr);
			set_colour(7, COLOR_BLACK, COLOR_WHITE, false, 0);
			set_colour(8, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(9, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(10, COLOR_WHITE, COLOR_CYAN, true, cursor_attr);
			set_colour(11, COLOR_WHITE, COLOR_CYAN, false, 0);
			set_colour(12, COLOR_WHITE, COLOR_CYAN, true, 0);
			set_colour(13, COLOR_WHITE, COLOR_CYAN, true, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_YELLOW, COLOR_GREEN, true, 0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(17, COLOR_WHITE, COLOR_GREEN, false, 0);
			set_colour(18, COLOR_YELLOW, COLOR_BLUE, true, 0);
			set_colour(19, COLOR_YELLOW, COLOR_CYAN, true, 0);
			set_colour(20, COLOR_YELLOW, COLOR_BLACK, true, 0);
			set_colour(21, COLOR_WHITE, COLOR_BLUE, false, 0);

			break;
		case 10:
			assume_default_colors(COLOR_BLUE, COLOR_CYAN);

			set_colour(2, COLOR_BLUE, COLOR_CYAN, false, 0);
			set_colour(3, COLOR_BLUE, COLOR_CYAN, false, 0);
			set_colour(4, COLOR_WHITE, COLOR_CYAN, true, labels_attr);
			set_colour(5, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(6, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(7, COLOR_BLUE, COLOR_CYAN, false, 0);
			set_colour(8, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(9, COLOR_BLUE, COLOR_CYAN, false, 0);
			set_colour(10, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(11, COLOR_CYAN, COLOR_BLUE, false, 0);
			set_colour(12, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(13, COLOR_WHITE, COLOR_BLUE, true, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_YELLOW, COLOR_GREEN, true, 0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(17, COLOR_BLUE, COLOR_GREEN, false, 0);
			set_colour(18, COLOR_YELLOW, COLOR_CYAN, true, 0);
			set_colour(19, COLOR_YELLOW, COLOR_BLUE, true, 0);
			set_colour(20, COLOR_WHITE, COLOR_BLACK, true, 0);
			set_colour(21, COLOR_BLUE, COLOR_CYAN, false, 0);

			break;
		case 11:
			assume_default_colors(COLOR_CYAN, COLOR_BLACK);

			set_colour(2, COLOR_WHITE, COLOR_BLUE, true, 0);
			set_colour(3, COLOR_CYAN, COLOR_BLACK, false, 0);
			set_colour(4, COLOR_CYAN, COLOR_BLACK, true, labels_attr);
			set_colour(5, COLOR_WHITE, COLOR_MAGENTA, true, cursor_attr);
			set_colour(6, COLOR_WHITE, COLOR_MAGENTA, true, cursor_attr);
			set_colour(7, COLOR_WHITE, COLOR_BLUE, true, 0);
			set_colour(8, COLOR_WHITE, COLOR_BLUE, true, 0);
			set_colour(9, COLOR_WHITE, COLOR_BLACK, false, 0);
			set_colour(10, COLOR_WHITE, COLOR_MAGENTA, true, cursor_attr);
			set_colour(11, COLOR_WHITE, COLOR_MAGENTA, false, 0);
			set_colour(12, COLOR_WHITE, COLOR_MAGENTA, true, 0);
			set_colour(13, COLOR_WHITE, COLOR_MAGENTA, true, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_YELLOW, COLOR_GREEN, true, 0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(17, COLOR_CYAN, COLOR_GREEN, false, 0);
			set_colour(18, COLOR_YELLOW, COLOR_BLACK, true, 0);
			set_colour(19, COLOR_CYAN, COLOR_MAGENTA, false, 0);
			set_colour(20, COLOR_WHITE, COLOR_BLUE, true, 0);

			break;
		case 12:
			assume_default_colors(COLOR_BLUE, COLOR_CYAN);

			set_colour(2, COLOR_BLUE, COLOR_CYAN, false, 0);
			set_colour(3, COLOR_WHITE, COLOR_CYAN, true, 0);
			set_colour(4, COLOR_BLUE, COLOR_CYAN, false, labels_attr);
			set_colour(5, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(6, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(7, COLOR_BLUE, COLOR_CYAN, false, 0);
			set_colour(8, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(9, COLOR_BLUE, COLOR_CYAN, false, 0);
			set_colour(10, COLOR_WHITE, COLOR_BLUE, true, cursor_attr);
			set_colour(11, COLOR_CYAN, COLOR_BLUE, false, 0);
			set_colour(12, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(13, COLOR_WHITE, COLOR_BLUE, true, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_YELLOW, COLOR_GREEN, true, 0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(17, COLOR_BLUE, COLOR_GREEN, false, 0);
			set_colour(18, COLOR_YELLOW, COLOR_CYAN, true, 0);
			set_colour(19, COLOR_CYAN, COLOR_BLUE, false, 0);
			set_colour(20, COLOR_WHITE, COLOR_MAGENTA, false, 0);
			set_colour(21, COLOR_CYAN, COLOR_CYAN, true, 0);

			break;
		case 13:
			assume_default_colors(COLOR_WHITE, COLOR_BLUE);

			set_colour(2, COLOR_WHITE, COLOR_BLACK, false, 0);
			set_colour(3, COLOR_WHITE, COLOR_BLUE, true, 0);
			set_colour(4, COLOR_WHITE, COLOR_BLUE, true, labels_attr);
			set_colour(5, COLOR_YELLOW, COLOR_CYAN, true, cursor_attr);
			set_colour(6, COLOR_YELLOW, COLOR_CYAN, true, cursor_attr);
			set_colour(7, COLOR_WHITE, COLOR_BLACK, false, 0);
			set_colour(8, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(9, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(10, COLOR_BLACK, COLOR_CYAN, false, cursor_attr);
			set_colour(11, COLOR_WHITE, COLOR_CYAN, false, 0);
			set_colour(12, COLOR_WHITE, COLOR_BLACK, true, 0);
			set_colour(13, COLOR_WHITE, COLOR_BLACK, true, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_YELLOW, COLOR_GREEN, true, 0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(17, COLOR_WHITE, COLOR_GREEN, false, 0);
			set_colour(18, COLOR_CYAN, COLOR_BLUE, false, 0);
			set_colour(19, COLOR_WHITE, COLOR_CYAN, true, 0);
			set_colour(20, COLOR_WHITE, COLOR_BLACK, false, 0);

			break;
		case 14:
			assume_default_colors(COLOR_WHITE, COLOR_BLUE);

			set_colour(2, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(3, COLOR_WHITE, COLOR_BLUE, true, 0);
			set_colour(4, COLOR_MAGENTA, COLOR_BLUE, true, labels_attr);
			set_colour(5, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(6, COLOR_BLACK, COLOR_CYAN, false, 0);
			set_colour(7, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(8, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(9, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(10, COLOR_BLACK, COLOR_CYAN, false, cursor_attr);
			set_colour(11, COLOR_WHITE, COLOR_CYAN, false, 0);
			set_colour(12, COLOR_WHITE, COLOR_BLACK, true, 0);
			set_colour(13, COLOR_WHITE, COLOR_BLACK, true, 0);
			set_colour(14, COLOR_WHITE, COLOR_RED, true, 0);
			set_colour(15, COLOR_YELLOW, COLOR_GREEN, true, 0);
			set_colour(16, COLOR_BLACK, COLOR_GREEN, false, 0);
			set_colour(17, COLOR_WHITE, COLOR_GREEN, false, 0);
			set_colour(18, COLOR_CYAN, COLOR_BLUE, false, 0);
			set_colour(19, COLOR_WHITE, COLOR_CYAN, true, 0);
			set_colour(20, COLOR_WHITE, COLOR_BLACK, false, 0);
			set_colour(21, COLOR_WHITE, COLOR_BLUE, false, 0);
			break;

		case 15:
			assume_default_colors(COLOR_BLACK, COLOR_WHITE);

			set_colour(2, COLOR_BLACK, COLOR_WHITE, false, 0);
			set_colour(3, COLOR_BLACK, COLOR_WHITE, false, 0);
			set_colour(4, COLOR_RED, COLOR_WHITE, false, A_DIM);
			set_colour(5, COLOR_WHITE, COLOR_RED, true, cursor_attr);
			set_colour(6, COLOR_WHITE, COLOR_RED, true, cursor_attr);
			set_colour(7, COLOR_BLACK, COLOR_WHITE, false, 0);
			set_colour(8, COLOR_WHITE, COLOR_BLUE, false, 0);
			set_colour(9, COLOR_BLACK, COLOR_WHITE, false, 0);
			set_colour(10, COLOR_WHITE, COLOR_RED, true, cursor_attr);
			set_colour(11, COLOR_BLACK, COLOR_RED, false, 0);
			set_colour(12, COLOR_WHITE, COLOR_BLACK, false, 0);
			set_colour(13, COLOR_WHITE, COLOR_BLACK, true, 0);
			set_colour(14, COLOR_YELLOW, COLOR_RED, true, A_REVERSE | A_BOLD);
			set_colour(15, COLOR_YELLOW, COLOR_BLACK, true, 0);
			set_colour(16, COLOR_WHITE, COLOR_BLACK, false, 0);
			set_colour(17, COLOR_WHITE, COLOR_BLACK, false, 0);
			set_colour(18, COLOR_CYAN, COLOR_BLUE, true, 0);
			set_colour(19, COLOR_WHITE, COLOR_CYAN, true, 0);
			set_colour(20, COLOR_WHITE, COLOR_BLACK, false, 0);
			break;

		case 16:
			use_default_colors();

			set_colour(2, -1, -1, false, 0);
			set_colour(3, -1, -1, false, 0);
			set_colour(4, -1, -1, true, A_ITALIC | labels_attr);
			set_colour(5, -1, -1, true, A_REVERSE | cursor_attr);
			set_colour(6, -1, -1, true, A_REVERSE | cursor_attr);
			set_colour(7, -1, -1, false, 0);
			set_colour(8, -1, -1, false, 0);
			set_colour(9, -1, -1, false, 0);
			set_colour(10, -1, -1, true, A_REVERSE | cursor_attr);
			set_colour(11, -1, -1, false, A_REVERSE);
			set_colour(12, -1, -1, false, 0);
			set_colour(13, -1, -1, true, 0);
			set_colour(14, -1, -1, false, A_UNDERLINE);
			set_colour(15, -1, -1, false, A_UNDERLINE);
			set_colour(16, -1, -1, false, 0);
			set_colour(17, -1, -1, false, 0);
			set_colour(18, -1, -1, false, A_UNDERLINE);
			set_colour(19, -1, -1, false, A_UNDERLINE | A_REVERSE | A_BOLD);
			set_colour(20, -1, -1, false, A_UNDERLINE | A_REVERSE | A_BOLD);
			set_colour(21, -1, -1, false, 0);
			break;

		case 17:
			init_color(235, 27, 212, 259);
			init_color(234, 0, 169, 212);
			init_color(240, 345, 431, 459);
			init_color(244, 557, 616, 624);
			init_color(245, 576, 631, 631);
			init_color(254, 933, 910, 835);
			init_color(136, 710, 537, 0);
			init_color(33, 149, 545, 824);
			init_color(160, 863, 196, 184);

			assume_default_colors(245, 234);

			init_pair(2, 245, 235);
			init_pair(3, 244, 234);
			init_pair(4, 33, 234);
			init_pair(5, 235, 136);
			init_pair(6, 235, 136);
			init_pair(7, 33, 235);
			init_pair(8, 33, 235);
			init_pair(9, 61, 234);
			init_pair(10, 235, 136);
			init_pair(11, 235, 136);
			init_pair(12, -1, -1);
			init_pair(13, -1, -1);
			init_pair(14, 230, 160);
			init_pair(15, 254, 235);
			init_pair(16, 245, 235);
			init_pair(17, 245, 235);
			init_pair(18, -1, -1);
			init_pair(19, -1, -1);
			init_pair(20, 254, 136);
			init_pair(21, 244, 235);

			theme_attrs[4] = labels_attr;
			theme_attrs[5] = cursor_attr;
			theme_attrs[6] = cursor_attr;
			theme_attrs[10] = cursor_attr;
			break;

		case 18:
			init_color(234, 13, 98, 119);
			init_color(235, 18, 141, 172);
			init_color(240, 110, 146, 200);
			init_color(245, 576, 631, 631);
			init_color(244, 557, 616, 624);
			init_color(136, 710, 537, 0);
			init_color(160, 863, 196, 184);

			assume_default_colors(234, 245);

			init_pair(2, 235, 244);
			init_pair(3, 234, 245);
			init_pair(4, 17, 245);
			init_pair(5, 235, 136);
			init_pair(6, 235, 136);
			init_pair(7, 17, 244);
			init_pair(8, 17, 235);
			init_pair(9, 17, 245);
			init_pair(10, 235, 136);
			init_pair(11, 235, 136);
			init_pair(12, -1, -1);
			init_pair(13, -1, -1);
			init_pair(14, 255, 160);
			init_pair(15, 255, 244);
			init_pair(16, 240, 244);
			init_pair(17, 240, 244);
			init_pair(18, -1, -1);
			init_pair(19, -1, -1);
			init_pair(20, 255, 136);
			init_pair(21, 235, 244);

			theme_attrs[4] = labels_attr;
			theme_attrs[5] = cursor_attr;
			theme_attrs[6] = cursor_attr;
			theme_attrs[10] = cursor_attr;
			break;

		case 19:
			init_color_rgb_ff(200, 0xff, 0xff, 0xd7); /* background */
			init_color_rgb_ff(201, 0x26, 0x26, 0x26); /* foreground */
			init_color_rgb_ff(202, 0xaf, 0xaf, 0x87); /* modeline bg */
			init_color_rgb_ff(203, 0x4e, 0x4e, 0x4e); /* modeline fg */
			init_color_rgb_ff(204, 0xd7, 0xd6, 0xaf); /* table decor */
			init_color_rgb_ff(205, 0xeb, 0xdb, 0xb2); /* cursor bg */
			init_color_rgb_ff(206, 0xaf, 0xaf, 0xaf); /* footer */
			init_color_rgb_ff(207, 0xff, 0xff, 0xaf); /* lineno bg */

			init_color_rgb_ff(210, 0x87, 0x00, 0x00); /* keyword - red */
			init_color_rgb_ff(211, 0Xd7, 0x5f, 0x5f); /* bookmark - faded red */
			init_color_rgb_ff(212, 0x00, 0x5f, 0x87); /* mark - faded blue */

			assume_default_colors(204, 200);

			init_pair(2, 203, 202);
			init_pair(3, 201, 200);
			init_pair(4, 210, 200);
			init_pair(5, 210, 205);
			init_pair(6, 203, 205);
			init_pair(7, 203, 202);
			init_pair(8, 17, 200);
			init_pair(9, 206, 200);
			init_pair(10, 203, 205);
			init_pair(11, 204, 205);
			init_pair(13, 203, 202);
			init_pair(14, COLOR_WHITE, 211);
			init_pair(15, 212, 204);
			init_pair(16, 201, 204);
			init_pair(17, 206, 204);
			init_pair(18, -1, -1);
			init_pair(19, -1, -1);
			init_pair(20, 212, 205);
			init_pair(21, 206, 207);

			theme_attrs[4] = labels_attr;
			theme_attrs[5] = cursor_attr;
			theme_attrs[6] = cursor_attr;
			theme_attrs[10] = cursor_attr;
			break;

		case 20:
			init_color_rgb_ff(200, 0xf1, 0xf1, 0xf1); /* background */
			init_color_rgb_ff(201, 0x61, 0x61, 0x61); /* foreground */
			init_color_rgb_ff(202, 0xfc, 0xfc, 0xfc); /* modeline bg */
			init_color_rgb_ff(203, 0x17, 0x17, 0x17); /* modeline fg */
			init_color_rgb_ff(204, 0x9e, 0x9e, 0x9e); /* table decor */
			init_color_rgb_ff(205, 0x4e, 0x4e, 0x4e); /* cursor bg */
			init_color_rgb_ff(213, 0xf6, 0xf6, 0xf6); /* cursor fg */
			init_color_rgb_ff(206, 0x9e, 0x9e, 0x9e); /* footer */
			init_color_rgb_ff(207, 0xf6, 0xf6, 0xf6); /* lineno bg */

			init_color_rgb_ff(210, 0x00, 0x00, 0x00); /* keyword - red */
			init_color_rgb_ff(211, 0Xd7, 0x5f, 0x5f); /* bookmark - faded red */
			init_color_rgb_ff(212, 0xff, 0xff, 0xff); /* mark fg - white */
			init_color_rgb_ff(215, 0xc3, 0xc3, 0xc3); /* mark bg */
			init_color_rgb_ff(214, 0xda, 0xda, 0xda); /* marked line bg */
			init_color_rgb_ff(216, 0x25, 0x25, 0x25);

			init_color(240, 40, 50, 200);

			assume_default_colors(204, 200);

			init_pair(2, 203, 202);
			init_pair(3, 201, 200);
			init_pair(4, 210, 200);
			init_pair(5, 213, 205);
			init_pair(6, 213, 205);
			init_pair(7, 203, 202);
			init_pair(8, 17, 200);
			init_pair(9, 206, 200);
			init_pair(10, 213, 205);
			init_pair(11, 204, 205);
			init_pair(13, 203, 202);
			init_pair(14, COLOR_WHITE, 211);
			init_pair(15, 216, 214);
			init_pair(16, 201, 214);
			init_pair(17, 206, 214);
			init_pair(18, -1, -1);
			init_pair(19, -1, -1);
			init_pair(20, 212, 205);
			init_pair(21, 204, 207);

			theme_attrs[4] = labels_attr;
			theme_attrs[5] = cursor_attr;
			theme_attrs[6] = cursor_attr;
			theme_attrs[10] = cursor_attr;
			break;
	}
}

#define _in			if_in_int
#define _notin		if_notin_int


void
initialize_theme(int theme, int window_identifier, bool is_tabular_fmt, bool no_highlight_lines, Theme *t)
{
	memset(t, 0, sizeof(Theme));

	switch (window_identifier)
	{
		case WINDOW_LUC:
		case WINDOW_FIX_ROWS:
			t->data_attr = theme_attr(4);
			break;

		case WINDOW_TOP_BAR:
			t->title_attr = theme_attr(7);
			break;

		case WINDOW_BOTTOM_BAR:
			t->prompt_attr = _in(theme, (int[]) {0, 1, -1}, theme_attr(2), theme_attr(13));
			t->bottom_attr = theme_attr(12);
			t->bottom_light_attr = A_BOLD | theme_attr(13);
			break;

		case WINDOW_FIX_COLS:
			t->data_attr = theme_attr(4);
			t->line_attr = 0;
			t->expi_attr = theme_attr(8);
			t->cursor_data_attr = theme_attr(5);
			t->cursor_line_attr = theme_attr(11);
			t->cursor_expi_attr = theme_attr(6);
			t->cursor_pattern_attr = theme_attr(20);
			t->bookmark_data_attr = theme_attr(14);
			t->bookmark_line_attr = theme_attr(14);
			t->cursor_bookmark_attr = theme_attr(14);
			t->found_str_attr = !no_highlight_lines ? theme_attr(15) : theme_attr(18);
			t->pattern_data_attr = theme_attr(16);
			t->pattern_line_attr = theme_attr(17);

			t->line_attr |= 0;
			t->expi_attr |= A_BOLD;
			t->bookmark_data_attr |= _in(theme, (int[]){15, -1}, A_REVERSE | A_BOLD, A_BOLD);
			t->bookmark_line_attr |= _in(theme, (int[]){15, -1}, A_REVERSE | A_BOLD, 0);
			t->cursor_bookmark_attr |= _in(theme, (int[]){15, -1}, A_BOLD, A_REVERSE | A_BOLD);
			t->found_str_attr |= no_highlight_lines ? (_in(theme, (int[]){0, -1}, A_REVERSE, A_BOLD)) : _in(theme, (int[]){0, 15,  -1}, A_REVERSE | A_BOLD, A_BOLD);
			t->pattern_data_attr |= _in(theme, (int[]) {15, -1}, A_BOLD, 0) | _in(theme, (int[]) {0, 15, -1}, A_REVERSE, 0);
			t->pattern_line_attr |= _in(theme, (int[]) {11, 7, 8, 15, -1}, A_BOLD, 0) | _in(theme, (int[]) {0, 15, -1}, A_REVERSE, 0);
			t->found_str_attr |= _in(theme, (int[]) {16, -1}, A_UNDERLINE | (no_highlight_lines ? A_ITALIC : 0), 0);
			break;

		case WINDOW_ROWS:
			t->data_attr = theme_attr(3);
			t->line_attr = 0;
			t->expi_attr = theme_attr(8);
			t->cursor_data_attr = theme_attr(6);
			t->cursor_line_attr = theme_attr(11);
			t->cursor_expi_attr = theme_attr(6);
			t->cursor_pattern_attr = theme_attr(19);
			t->bookmark_data_attr = theme_attr(14);
			t->bookmark_line_attr = theme_attr(14);
			t->cursor_bookmark_attr = theme_attr(14);
			t->found_str_attr = !no_highlight_lines ? theme_attr(15) : theme_attr(18);
			t->pattern_data_attr = theme_attr(16);
			t->pattern_line_attr = theme_attr(17);

			t->expi_attr |= A_BOLD;
			t->bookmark_data_attr |= _in(theme, (int[]){15, -1}, A_REVERSE | A_BOLD, A_BOLD);
			t->bookmark_line_attr |= _in(theme, (int[]){15, -1}, A_REVERSE | A_BOLD, 0);
			t->cursor_bookmark_attr |= _in(theme, (int[]){15, -1}, A_BOLD, A_REVERSE | A_BOLD);
			t->found_str_attr |= no_highlight_lines ? (_in(theme, (int[]){0, -1}, A_REVERSE, A_BOLD)) : _in(theme, (int[]){0, 15,  -1}, A_REVERSE | A_BOLD, A_BOLD);
			t->pattern_data_attr |= _in(theme, (int[]) {15, -1}, A_BOLD, 0) | _in(theme, (int[]) {0, 15, -1}, A_REVERSE, 0);
			t->pattern_line_attr |= _in(theme, (int[]) {11, 7, 8, 15, -1}, A_BOLD, 0) | _in(theme, (int[]) {0, 15, -1}, A_REVERSE, 0);
			t->found_str_attr |= _in(theme, (int[]) {16,  -1}, A_UNDERLINE, 0);
			break;

		case WINDOW_FOOTER:
			t->data_attr = is_tabular_fmt ? theme_attr(9) : theme_attr(3);
			t->line_attr = 0;
			t->expi_attr = 0;
			t->cursor_data_attr = theme_attr(10);
			t->cursor_line_attr = 0;
			t->cursor_expi_attr = 0;
			t->cursor_pattern_attr = theme_attr(19);
			t->bookmark_data_attr = theme_attr(14);
			t->bookmark_line_attr = theme_attr(14);
			t->cursor_bookmark_attr = theme_attr(14);
			t->found_str_attr = !no_highlight_lines ? theme_attr(15) : theme_attr(18);
			t->pattern_data_attr = theme_attr(16);
			t->pattern_line_attr = theme_attr(17);

			t->line_attr |= 0,
			t->expi_attr |= 0;
			t->cursor_line_attr |= 0;
			t->cursor_expi_attr |= 0;
			t->bookmark_line_attr |= 0;
			t->cursor_bookmark_attr |= A_BOLD | A_REVERSE;
			t->found_str_attr |= no_highlight_lines ? (_in(theme, (int[]){0, -1}, A_REVERSE, A_BOLD)) : A_BOLD;
			t->pattern_data_attr |= 0;
			t->pattern_line_attr |= 0;
			t->cursor_pattern_attr |= A_REVERSE;
			break;

		case WINDOW_ROWNUM:
		case WINDOW_ROWNUM_LUC:
			t->data_attr = theme_attr(21);
			t->cursor_data_attr = theme_attr(10);
			t->bookmark_data_attr = theme_attr(14);
			t->cursor_bookmark_attr = theme_attr(14);
			t->pattern_data_attr = theme_attr(16);
			t->cursor_bookmark_attr |= A_BOLD | A_REVERSE;

			break;
	}

	if (no_highlight_lines)
	{
		t->pattern_data_attr = t->data_attr;
		t->pattern_line_attr = t->line_attr;
	}
}
