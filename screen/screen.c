#include "screen.h"

// ��ʼ��SCREENʵ��
void
init_screen(SCREEN *screen, HWND hwnd) {

	assert(screen != NULL);
	assert(hwnd != NULL);

	HDC hdcWindow = GetDC(hwnd);

	// Create a compatible DC which is used in a BitBlt from the window DC
	screen->hdcMemDC = CreateCompatibleDC(hdcWindow);

	if (!(screen->hdcMemDC))
	{
		MessageBox(hwnd, "CreateCompatibleDC has failed", "Failed", MB_OK);
	}

	(screen->screen_size).cx = GetSystemMetrics(SM_CXSCREEN);

	(screen->screen_size).cy = GetSystemMetrics(SM_CYSCREEN);

}


// ��Ļ��ȡ������ȡ��ͼ����� ȫ�ֱ���hdcMemDc ��
void 
screen_caption(HWND hWnd, SCREEN *screen){

	assert(hWnd != NULL);
	assert(screen != NULL);

	HDC hdcScreen;
	HDC hdcWindow;
	HBITMAP hbmScreen = NULL;

	// Retrieve the handle to a display device context for the client 
	// area of the window. 
	hdcScreen = GetDC(NULL); // GetDC(NULL)��ʾ������Ļ��dc
	hdcWindow = GetDC(hWnd); // ������ǰ���ڵ�hdc

	// Create a compatible bitmap from the Window DC
	hbmScreen = CreateCompatibleBitmap(hdcWindow, (screen->screen_size).cx, (screen->screen_size).cy);

	if (!hbmScreen)
	{
		MessageBox(hWnd, "CreateCompatibleBitmap Failed", "Failed", MB_OK);
		goto done;
	}

	// Select the compatible bitmap into the compatible memory DC.
	SelectObject(screen->hdcMemDC, hbmScreen);

	// Bit block transfer into our compatible memory DC.
	if (!BitBlt(screen->hdcMemDC,
		0, 0,
		(screen->screen_size).cx, (screen->screen_size).cy,
		hdcScreen,
		0, 0,
		SRCCOPY))
	{
		MessageBox(hWnd, "BitBlt has failed", "Failed", MB_OK);
		goto done;
	}

	//Clean up
done:
	DeleteObject(hbmScreen);
	ReleaseDC(NULL, hdcScreen);
	ReleaseDC(hWnd, hdcWindow);

}


// ���� ȫ�ֱ���hdcMemDc �д�ŵ���Ļͼ��
void
screen_draw(HDC hdc, SCREEN screen) {

	assert(hdc != NULL);

	BitBlt(hdc,
		0, 0,
		(screen.screen_size).cx, (screen.screen_size).cy,
		screen.hdcMemDC,
		0, 0,
		SRCCOPY);
}


