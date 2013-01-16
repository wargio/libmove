/*
 * Copyright (C) 2013, Giovanni Dante Grazioli (deroad)
 */

#ifndef __LIBMOVE_H__
#define __LIBMOVE_H__

#include <sysmodule/sysmodule.h>
#include <libmove/moveutil.h>
#include <libmove/movebuttons.h>

#define LIBMOVE_OK			(0)
#define LIBMOVE_ERROR			(-1)

#define	PLAYSTATION_MOVE_PAD_0 		0
#define	PLAYSTATION_MOVE_PAD_1 		1
#define	PLAYSTATION_MOVE_PAD_2 		2

/*
 * This function initialize lib move. to use this, you need an EyeToy or a PS Eye, and a PS Move.
 * Return LIBMOVE_OK if nothing went wrong.
 */
int  init_move();

/*
 * This function terminate lib move.
 * Return LIBMOVE_OK if nothing went wrong.
 */
int  end_move();

/*
 * This function return the camera status.
 * Return LIBMOVE_OK if everything is fine.
 */
int  camera_is_loaded();

/*
 * This function return the gem status.
 * Return LIBMOVE_OK if everything is fine.
 */
int  move_is_loaded();

/*
 * This function get the PS Move 3D Position value
 * an example: 
 *        float x ,y ,z;
 *        get_3d_position( PLAYSTATION_MOVE_PAD_0 , &x, &y, &z );
 */

void get_3d_position(int pad_number, float *x, float *y, float *z);

/*
 * This function get the PS Move Gyroscopic value
 * an example: 
 *        float x ,y ,z;
 *        get_gyro_position( PLAYSTATION_MOVE_PAD_0 , &x, &y, &z );
 */

void get_gyro_position(int pad_number, float *x, float *y, float *z);

/*
 * This function get the PS Move Buttons
 * see $(PORTLIBS)/libmove/movebuttons.h for more details
 */

void getMovePadData(int pad_number, movePadData *data);

/*
 * This function force the ball color of the PS Move
 * an example: set_move_led_color( PLAYSTATION_MOVE_PAD_0 , 0.5, 0.5, 0.5 );
 */
 
void set_move_led_color(int pad_number, f32 red, f32 green, f32 blue);

/*
 * This function should reset the PS Move
 */
int  move_reset(int pad_number);

/*
 * This function recalibrate the PS Move
 */
void calibrate_move(int pad_number);

/*
 * These functions set and get the Rumble intensity of the PS Move
 */
void move_set_rumble(int pad_number, u8 intensity);
u8   move_get_rumble(int pad_number);

#endif

