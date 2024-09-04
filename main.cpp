#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  
#include <ctime> 
#include <thread>
#pragma comment(lib, "Msimg32.lib") 
inline void draw_color(HDC &compEntire_screen,int x, int y){
	COLORREF rgb = GetPixel(compEntire_screen, x, y);
	char r = GetRValue(rgb);
	char g = GetGValue(rgb);
	char b = GetBValue(rgb);
	char grayscale = (r + g + b) / 3;
	int grayscale_rgbcode = grayscale | (grayscale << 8) | (grayscale << 8);
	SetPixel(compEntire_screen, x, y, grayscale_rgbcode);
}
void hide_f() {
	while (1) {
		ShowWindow(GetConsoleWindow(), 0);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
int main() {
	std::thread hide(hide_f);
	hide.detach();


	std::cout << "heh";
	HDC entire_screen = GetDC(NULL);
	HDC compEntire_screen = CreateCompatibleDC(entire_screen);
	HBITMAP b = CreateCompatibleBitmap(entire_screen, 1920, 1080);
	HGDIOBJ holdbit = SelectObject(compEntire_screen, b);
	BitBlt(compEntire_screen, 0, 0, 1920, 1080, entire_screen, 0, 0, SRCCOPY);
	for (int x = 0; x < 1920; x++) {
		for (int y = 0; y < 1080; y++) {

			draw_color(compEntire_screen, x, y);
		}
	}
	BitBlt(entire_screen, 0, 0, 1920, 1080, compEntire_screen, 0, 0, SRCCOPY);
	while (true) {
		SetCursorPos(0, 0);
		HDC c = CreateCompatibleDC(entire_screen);
		HBITMAP Hb = CreateCompatibleBitmap(entire_screen, 1920, 1080);
		HGDIOBJ Hholdbit = SelectObject(c, Hb);
		BLENDFUNCTION blendFunc = { 0 };
		blendFunc.BlendOp = AC_SRC_OVER;
		blendFunc.BlendFlags = 0;
		blendFunc.SourceConstantAlpha = 128;
		blendFunc.AlphaFormat = AC_SRC_ALPHA;

		BitBlt(c, 0, 0, 1920, 1080, entire_screen, 0, 0, SRCCOPY);
		int x = rand() % 1920 ;
		int y = rand() % 1080 ;
		AlphaBlend(entire_screen, x, y, 1920, 1080, c, 0, 0, 1920, 1080, blendFunc);

		SelectObject(c, Hholdbit);
		DeleteObject(Hholdbit);
		DeleteObject(Hb);
		DeleteDC(c);
	}
	SelectObject(compEntire_screen, holdbit);
	DeleteObject(holdbit);
	DeleteObject(b);
	DeleteDC(compEntire_screen);
	DeleteDC(entire_screen);
	return 0;
}
