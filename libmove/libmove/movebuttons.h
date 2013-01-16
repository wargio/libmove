/*
 * Copyright (C) 2013, Giovanni Dante Grazioli (deroad)
 */

#ifndef __LIBMOVE_BUTTONS_H__
#define __LIBMOVE_BUTTONS_H__

typedef struct {
	/* Button information */
	/* 0: UP, 1: DOWN     */
	u16 BTN_SELECT;
	u16 BTN_T;
	u16 BTN_ACTION;
	u16 BTN_START;
	u16 BTN_TRIANGLE;
	u16 BTN_CIRCLE;
	u16 BTN_CROSS;
	u16 BTN_SQUARE;
	/* Analog nub information */
	/* 0x0000 - 0x00FF        */
	u16 ANA_T;
} movePadData;

#endif

