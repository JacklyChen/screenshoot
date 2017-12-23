/*
+
-             ���ߣ�Joezeo < joezeo@outlook.com >
+
-             ����ʱ�䣺2017.12.23 / 21��41
+
-             �޸�ʱ�䣺2017.12.23 / 21��41
+
-             �ļ����ƣ�capture.c
+
-             ���ܣ�captureģ���Դ�ļ�������captureģ�麯���Ķ��塣
+                  captureģ�����Ҫ����Ϊ���Ѿ���ȡ������ͼ���У��û���ȡͼ��ͼ������CAPTURE�ṹ���memDC�С�
-
+
*/
#include "capturer.h"

/*
			�ӿں���
*/

// �ӿں�������ʼ�� CAPTURE ʵ��
void
init_capture(CAPTURE *cap) {

	assert(cap != NULL);

	cap->bCnt = 0;

	cap->status = FALSE;

	(cap->pos).x = 0;
	(cap->pos).y = 0;

	(cap->rect).left	= 0;
	(cap->rect).bottom	= 0;
	(cap->rect).right	= 0;
	(cap->rect).top		= 0;

	cap->memDc = NULL;

	(cap->picSize).cx = 0;
	(cap->picSize).cy = 0;

}


// �ӿں�����ѡ��ͼƬ������ͼƬ�� CAPTURE ʵ����memDc��
void
capture_image(CAPTURE *cap, HWND sHwnd, HWND wHwnd) {

	assert(cap != NULL);
	assert(sHwnd != NULL);
	assert(wHwnd != NULL);

	select_image(cap);

	if (cap->bCnt == 2) {

		store_image(cap, sHwnd, wHwnd);

	}
		
}


// �ӿں��������� capture ʵ�� memDc �д�ŵ�ͼ��
void
draw_image(CAPTURE *cap, HDC hdc, HWND hwnd) {

	assert(cap != NULL);
	assert(hdc != NULL);
	assert(hwnd != NULL);

	SIZE				client_size;
	RECT				clRect;

	GetClientRect(hwnd, &clRect);

	client_size.cx = clRect.right - clRect.left;
	client_size.cy = clRect.bottom - clRect.top;

	(cap->pos).x = (client_size.cx - (cap->picSize).cx) / 2;
	(cap->pos).y = (client_size.cy - (cap->picSize).cy) / 2;

	BitBlt(hdc,
		(cap->pos).x, (cap->pos).y,
		(cap->picSize).cx, (cap->picSize).cy,
		cap->memDc,
		0, 0,
		SRCCOPY);

}



/*
			��̬����
*/

// ��̬������ѡ��ͼƬ
static void
select_image(CAPTURE *cap) {

	(cap->bCnt)++;

	switch (cap->bCnt) {

	case 1:

		(cap->rect).left = (cap->pos).x;

		(cap->rect).top = (cap->pos).y;

		break;


	case 2:

		if (((cap->pos).x >= (cap->rect).left) &&
			((cap->pos).y >= (cap->rect).top)) {

			(cap->rect).right = (cap->pos).x;

			(cap->rect).bottom = (cap->pos).y;

		}
		else if (((cap->pos).x < (cap->rect).left) &&
			((cap->pos).y >= (cap->rect).top)) {

			int tmp = (cap->rect).left - (cap->pos).x;

			(cap->rect).left -= tmp;

			(cap->rect).right = (cap->pos).x + tmp;

			(cap->rect).bottom = (cap->pos).y;

		}
		else if (((cap->pos).x < (cap->rect).left) &&
			((cap->pos).y < (cap->rect).top)) {

			int a, b;

			(cap->rect).right = (cap->pos).x;

			(cap->rect).bottom = (cap->pos).y;

			a = (cap->rect).right;
			b = (cap->rect).bottom;

			(cap->rect).right = (cap->rect).left;
			(cap->rect).bottom = (cap->rect).top;

			(cap->rect).left = a;
			(cap->rect).top = b;

		}
		else if (((cap->pos).x >= (cap->rect).left) &&
			((cap->pos).y < (cap->rect).top)) {

			int tmp = (cap->rect).top - (cap->pos).y;

			(cap->rect).top -= tmp;

			(cap->rect).bottom = (cap->pos).y + tmp;

			(cap->rect).right = (cap->pos).x;

		}

		break;

	}

}


// ��̬����������ͼƬ�� CAPTURE ʵ����memDc��
static void
store_image(CAPTURE *cap, HWND sHwnd, HWND wHwnd) {

	cap->bCnt = 0;

	HDC					screen_dc;
	HDC					window_dc;
	HBITMAP				window_hbmp;

	(cap->picSize).cx = (cap->rect).right - (cap->rect).left;
	(cap->picSize).cy = (cap->rect).bottom - (cap->rect).top;

	screen_dc = GetDC(sHwnd);
	window_dc = GetDC(wHwnd);

	cap->memDc = CreateCompatibleDC(window_dc);

	window_hbmp = CreateCompatibleBitmap(window_dc, (cap->picSize).cx, (cap->picSize).cy);

	SelectObject(cap->memDc, window_hbmp);

	if (BitBlt(cap->memDc, 
		0, 0, 
		(cap->picSize).cx, (cap->picSize).cy,
		screen_dc, (cap->rect).left, (cap->rect).top, SRCCOPY)) {

		cap->status = TRUE;

	}

	DeleteObject(window_hbmp);
	ReleaseDC(sHwnd, screen_dc);
	ReleaseDC(wHwnd, window_dc);

}
