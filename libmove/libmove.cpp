#include <libmove/libmove.h>

static int _camera_loaded = LIBMOVE_ERROR;
static int _gem_loaded    = LIBMOVE_ERROR;

static moveContext *move_context = NULL;

int initLibMove(){
	int ret;
	_camera_loaded = !sysModuleIsLoaded (SYSMODULE_CAMERA);
	if (!_camera_loaded)
		ret = sysModuleLoad (SYSMODULE_CAMERA);
	else
		ret = LIBMOVE_OK;
	if (ret == LIBMOVE_OK){
		_gem_loaded = !sysModuleIsLoaded (SYSMODULE_GEM);
		if (!_gem_loaded)
			ret = sysModuleLoad (SYSMODULE_GEM);
		if (ret == LIBMOVE_OK){
			move_context = initMove();
		}
		else {
			if(_gem_loaded)
				sysModuleUnload (SYSMODULE_CAMERA);
		}
	}
	
	if(move_context == NULL)
		return LIBMOVE_ERROR;
	
	return ret;
}

int endLibMove(){
	if (move_context){
	        endMove (move_context);
	        move_context = NULL;
	        sysModuleUnload (SYSMODULE_CAMERA);
		sysModuleUnload (SYSMODULE_GEM);
		return LIBMOVE_OK;
	}
	return LIBMOVE_ERROR;
}

int cameraIsLoaded(){
	return _camera_loaded;
}

int moveIsLoaded(){
	return _gem_loaded;
}

void get3DPosition(int pad_number, float *x, float *y, float *z){
	processMove(move_context, pad_number);
	moveGet3DPosition(move_context, x, y, z);
}

void getGyroPosition(int pad_number, float *x, float *y, float *z){
	processMove (move_context, pad_number);
	gemInertialState gem_inert;
        gemGetInertialState (0, 0, 0, &gem_inert);
        *z = -vec_array (gem_inert.gyro, 2) *25;
        *x = -vec_array (gem_inert.gyro, 1) *25;
        *y = -vec_array (gem_inert.gyro, 0) *25;
}

void getMovePadData(int pad_number, movePadData *data){
	processMove (move_context, pad_number);
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

void setMoveLedColor(int pad_number, f32 red, f32 green, f32 blue){
	gemReset(pad_number);
	processMove(move_context, pad_number, red, green, blue);
}

int moveReset(int pad_number){
	return gemReset(pad_number);
}

void calibrateMove(int pad_number){
	gemCalibrate(pad_number);
}

void moveSetRumble(int pad_number, u8 intensity){
	gemSetRumble(pad_number,  intensity);
}

u8 moveGetRumble(int pad_number){
	u8 intensity;
	gemGetRumble(pad_number, &intensity);
	return intensity;
}
