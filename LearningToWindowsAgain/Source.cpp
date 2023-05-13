#include <Windows.h> 
#include "Window.h"
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	Window test_window = Window(hInstance, L"CRINGE");
	test_window.Initialise();
	test_window.RunMessageLoop();


	return 0;
}