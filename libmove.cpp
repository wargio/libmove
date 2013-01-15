#include <libmove/libmove.h>

static int _camera_loaded = 0;
static int _gem_loaded = 0;

static moveContext *move_context = NULL;


int init_move(){
	int ret;
	_camera_loaded = !sysModuleIsLoaded (SYSMODULE_CAMERA);
	if (!_camera_loaded)
		ret = sysModuleLoad (SYSMODULE_CAMERA);
	else
		ret = 0;
	if (ret == 0){
		_gem_loaded = !sysModuleIsLoaded (SYSMODULE_GEM);
		if (!_gem_loaded)
			ret = sysModuleLoad (SYSMODULE_GEM);
		if (ret == 0){
			move_context = initMove();
		}
		else {
			if(_gem_loaded)
				sysModuleUnload (SYSMODULE_CAMERA);
		}
	}
	return ret;
}

int end_move(){
	if (move_context){
	        endMove (move_context);
	        move_context = NULL;
	        sysModuleUnload (SYSMODULE_CAMERA);
		sysModuleUnload (SYSMODULE_GEM);
		return 1;
	}
	return 0;
}

void get_3d_position(float *x, float *y, float *z){
	processMove(move_context);
	moveGet3DPosition(move_context, x, y, z);
}

void get_gyro_position(float *x, float *y, float *z){
	/* Check move events */
	processMove (move_context);
	float x1, y1, z1;
	gemInertialState gem_inert;
        gemGetInertialState (0, 0, 0, &gem_inert);
        z1 = -vec_array (gem_inert.gyro, 2) * 25;
        x1 = -vec_array (gem_inert.gyro, 1) * 25;
        y1 = -vec_array (gem_inert.gyro, 0) * 25;
        
	if(abs(x1) > 2)
		*x=x1;
	if(abs(y1) > 2)
		*y=y1;
	if(abs(z1) > 2)
		*z=z1;
}

void getMovePadData(movePadData *data){
	processMove (move_context);
	data->BTN_SELECT   = (move_context->state.paddata.buttons & 0x1);
	data->BTN_T        = (move_context->state.paddata.buttons & 0x2);
	data->BTN_ACTION   = (move_context->state.paddata.buttons & 0x4);
	data->BTN_START    = (move_context->state.paddata.buttons & 0x8);
	data->BTN_TRIANGLE = (move_context->state.paddata.buttons & 0x10);
	data->BTN_CIRCLE   = (move_context->state.paddata.buttons & 0x20);
	data->BTN_CROSS    = (move_context->state.paddata.buttons & 0x40);
	data->BTN_SQUARE   = (move_context->state.paddata.buttons & 0x80);
	data->ANA_T        =  move_context->state.paddata.ANA_T;
}

void calibrate_move(){
	gemCalibrate (0);
}
