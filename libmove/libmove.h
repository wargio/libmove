/*
 * Copyright (C) 2013, Giovanni Dante Grazioli (deroad)
 */

#ifndef __LIBMOVE_H__
#define __LIBMOVE_H__

#include <sysmodule/sysmodule.h>
#include <libmove/moveutil.h>
#include <libmove/movebuttons.h>

int  init_move();
int  end_move();
void getMovePadData(movePadData *data);
void calibrate_move();
void get_3d_position(float *x, float *y, float *z);
void get_gyro_position(float *x, float *y, float *z);

#endif

