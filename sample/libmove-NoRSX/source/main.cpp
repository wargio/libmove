/*
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.

 This program was created by Grazioli Giovanni Dante <wargio@libero.it>.
*/

#include <io/pad.h>

#include <NoRSX.h> //This is the new HEADER!!! Now it's a real new lib!!

#include <time.h>
#include <libmove/libmove.h>


msgType MSG_OK = (msgType)(MSG_DIALOG_NORMAL | MSG_DIALOG_BTN_TYPE_OK | MSG_DIALOG_DISABLE_CANCEL_ON);

s32 main(s32 argc, const char* argv[])
{
	padInfo padinfo;
	padData paddata;
	ioPadInit(7);

	initLibMove();

	setMoveLedColor(PLAYSTATION_MOVE_PAD_0, 0.5, 0, 0);

	NoRSX *GFX = new NoRSX(RESOLUTION_1920x1080); //set defined screen resolution You can change it to:
						      //RESOLUTION_720x480 | RESOLUTION_720x576 | RESOLUTION_1280x720 | RESOLUTION_1920x1080
	Image IMG(GFX);
	Background BG(GFX);
	Object OBJ(GFX);
	Bitmap BMap(GFX);
	MsgDialog Msg(GFX);

	NoRSX_Bitmap Precalculated_Layer;	
	
	BMap.GenerateBitmap(&Precalculated_Layer); //Initialize the Bitmap
	
	Font F1(LATIN2 ,GFX);   //Loaded from Memory
	BG.MonoBitmap(COLOR_BLACK,&Precalculated_Layer); //a green hex color (you can use hex colors insted of COLOR_XXXXXXX)

	F1.PrintfToBitmap(150,500,&Precalculated_Layer,COLOR_RED,"Screen %d x %d",GFX->width,GFX->height);
	F1.PrintfToBitmap(150,350,&Precalculated_Layer,COLOR_BLUE, 35,"Press X to exit! (joypad)");
	F1.PrintfToBitmap(150,400,&Precalculated_Layer,COLOR_YELLOW, 35,"Press start to exit! (move)");

	GFX->AppStart();
	float x=GFX->width*0.5,y=GFX->height*0.5,z=0;
	float x1=0,y1=0,z1=0;
	movePadData data;

	getGyroPosition(PLAYSTATION_MOVE_PAD_0,&x1,&y1,&z1);
	x=GFX->width*0.5-x1;
	y=GFX->height*0.5-y1;
	z=-z1;


	while(GFX->GetAppStatus()){
		BMap.DrawBitmap(&Precalculated_Layer);

		getMovePadData(PLAYSTATION_MOVE_PAD_0, &data);

		ioPadGetInfo(&padinfo);
		if(padinfo.status[0]){
			ioPadGetData(0, &paddata);
			if(paddata.BTN_CROSS){
				GFX->AppExit();
			}
		}
		
		if(data.BTN_ACTION){
			calibrateMove(PLAYSTATION_MOVE_PAD_0);
			setMoveLedColor(PLAYSTATION_MOVE_PAD_0, 0.5, 0, 0);
			getGyroPosition(PLAYSTATION_MOVE_PAD_0, &x1, &y1, &z1);
			x=GFX->width*0.5-x1;
			y=GFX->height*0.5-y1;
			z=-z1;
		}
		get3DPosition(PLAYSTATION_MOVE_PAD_0, &x1, &y1, &z1);
		F1.Printf(150,200,COLOR_WHITE,30,"3D: x %.2f, y %.2f, z %.2f",x1,y1,z1);
		
		getGyroPosition(PLAYSTATION_MOVE_PAD_0, &x1, &y1, &z1);
		F1.Printf(150,300,COLOR_WHITE,30,"Gyro: x %.2f, y %.2f, z %.2f",x1,y1,z1);


		if(abs(x1) > 2)
			x += x1;
		if(abs(y1) > 2)
			y += y1;
		if(abs(z1) > 2)
			z += z1;

		if(x>=GFX->width ) x = GFX->width ;
		else if(x<0) x = 0;
		if(y>=GFX->height) y = GFX->height;
		else if(y<0) y = 0;
		

		if(data.BTN_CROSS)
			F1.Printf(150,150,COLOR_RED,60,"BTN_CROSS");
		if(data.BTN_CIRCLE)
			F1.Printf(150,150,COLOR_RED,60,"BTN_CIRCLE");
		if(data.BTN_SQUARE)
			F1.Printf(150,150,COLOR_RED,60,"BTN_SQUARE");
		if(data.BTN_TRIANGLE)
			F1.Printf(150,150,COLOR_RED,60,"BTN_TRIANGLE");
		if(data.BTN_T)
			F1.Printf(150,150,COLOR_RED,60,"BTN_T");
		if(data.BTN_ACTION)
			F1.Printf(150,150,COLOR_RED,60,"BTN_ACTION");
		if(data.BTN_START){
			F1.Printf(150,150,COLOR_RED,60,"BTN_START");
			goto end;
		}
		if(data.BTN_SELECT)
			F1.Printf(150,150,COLOR_RED,60,"BTN_SELECT");
		


		F1.Printf(150,250,COLOR_WHITE,30,"Trigger T 0x%04x",data.ANA_T);
		OBJ.Rectangle(x-5, y-5 , 10, 10, COLOR_WHITE);
		GFX->Flip();
		moveSetRumble(PLAYSTATION_MOVE_PAD_0, (u8)data.ANA_T);
	}
end:
	//You need to clean the Bitmap before exit
	BMap.ClearBitmap(&Precalculated_Layer);
	endLibMove();
	GFX->NoRSX_Exit();
	ioPadEnd();
	return 0;
}

