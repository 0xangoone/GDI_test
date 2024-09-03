#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  
#include <ctime> 
#pragma comment(lib, "Msimg32.lib") 
int main() {

	while (true) {
		HDC entire_screen = GetDC(NULL);
		HDC compEntire_screen = CreateCompatibleDC(entire_screen);
		HBITMAP b = CreateCompatibleBitmap(entire_screen, 1920, 1080);
		HGDIOBJ holdbit = SelectObject(compEntire_screen, b);
		BLENDFUNCTION blendFunc = { 0 };
		blendFunc.BlendOp = AC_SRC_OVER;
		blendFunc.BlendFlags = 0;
		blendFunc.SourceConstantAlpha = 128;
		blendFunc.AlphaFormat = AC_SRC_ALPHA;
		srand(static_cast<unsigned>(time(0)));

		BitBlt(compEntire_screen, 0, 0, 1920, 1080, entire_screen, 0, 0, SRCCOPY);
		int x = rand() % 1920 - 0; 
		int y = rand() % 1080 - 0;
		AlphaBlend(entire_screen,x, y, 1920, 1080, compEntire_screen, 0, 0, 1920, 1080, blendFunc);
		
		SelectObject(compEntire_screen, holdbit);
		DeleteObject(holdbit);
		DeleteObject(b);
		DeleteDC(compEntire_screen);
		DeleteDC( entire_screen);

		Sleep(50);
	}

	return 0;

}
