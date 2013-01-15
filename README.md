libmove for PSL1GHT V2
======================

This lib will be installed inside the PORTLIBS

Authors
-------
* deroad - libmove.cpp/.h movebuttons.h
* José Ramos Márquez (bigboss) - moveutil.cpp/.h spursutil.cpp/.h
* Youness Alaoui (KaKaRoTo) - moveutil.cpp/.h spursutil.cpp/.h

Changelog:
----------
* 0.1
	initial release
	
Linking
-------

Add these libs on your makefile to compile your homebrew.
	-lmove -lgem -lcamera -lspurs
	
License
-------

This lib is released under BSD License.

Example
-------

	#include <libmove/libmove.h>
	int main(s32 argc, const char* argv[]){
		movePadData data;
		init_move();
		while(1){
			getMovePadData(&data);
			if(data.BTN_ACTION)
				calibrate_move();
			}else if(data.BTN_T){
				goto end;
			}
		}
	end:
		end_move();	
	}
