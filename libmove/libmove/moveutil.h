/*
 * Copyright (C) Antonio José Ramos Márquez (bigboss)
 * Copyright (C) Youness Alaoui (KaKaRoTo)
 * Copyright (C) 2013, Giovanni Dante Grazioli (deroad)
 */

#ifndef __LIBMOVE_MOVEUTIL_H__
#define __LIBMOVE_MOVEUTIL_H__

#include <ppu-types.h>
#include <spurs/spurs.h>
#include <io/camera.h>
#include <io/move.h>

typedef struct{
	gemState state;
	cameraInfoEx camInfo;
	cameraReadInfo camRead;
	Spurs *spurs;
}moveContext;

static inline float vec_array(vec_float4 vec, unsigned int idx)
{
   union {
      vec_float4 vec;
      float      array[4];
   } v;

   v.vec = vec;

   if (idx > 3)
     return -1;
   return v.array[idx];
}
/*
 pad numbers goes starts from 0 to 7? ; where 0 is the first ps move controller connected to the ps3.
*/
moveContext *initMove();
void         endMove(moveContext *context);
int          processMove(moveContext *context, int pad_number, f32 red, f32 green, f32 blue);
int          processMove(moveContext *context, int pad_number);
void         moveGet3DPosition(moveContext *context, float *x, float *y, float *z);

#endif /* __MOVEUTIL_H__ */
