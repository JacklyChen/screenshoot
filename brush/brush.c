/*
+
-             ���ߣ�Joezeo < joezeo@outlook.com >
+
-             ����ʱ�䣺2017.12.23 / 21��48
+
-             �޸�ʱ�䣺2017.12.23 / 21��48
+
-             �ļ����ƣ�brush.c
+
-             ���ܣ�brushģ���Դ�ļ�������brushģ�麯���Ķ��塣
+                  brushģ�����Ҫ����Ϊ��ˢ��ѡ�񻭱ʣ�������ͼ��
-
+
*/
#include "brush.h"

/* 
			�ӿں���
*/

// �ӿں�������ʼ�� BRUSH ʵ��
void
init_brush(BRUSH *brush) {

	assert(brush != NULL);

	brush->pen_color = nocolor;

	(brush->pre_point).x = 0;
	(brush->pre_point).y = 0;

}


// �ӿں������ı�˵����� check ���Ե�״̬
void
change_menu_checked(BRUSH *brush, PENCOLOR color, UINT menu_id, HMENU hmenu) {

	assert(brush != NULL);
	assert(hmenu != NULL);

	if (brush->pen_color == nocolor) {

		brush->pen_color = color;

		CheckMenuItem(hmenu, menu_id, MF_CHECKED);

		return;

	}

	if (color == brush->pen_color) {

		brush->pen_color = nocolor;

		CheckMenuItem(hmenu, menu_id, MF_UNCHECKED);

		return;

	}

	int tmp_id;

	switch (brush->pen_color) {
	case red:

		tmp_id = 40013;

		break;

	case blue:

		tmp_id = 40014;

		break;

	case green:

		tmp_id = 40015;

		break;

	}

	if (color == nocolor) {

		CheckMenuItem(hmenu, tmp_id, MF_UNCHECKED);

		brush->pen_color = nocolor;

		return;

	}

	CheckMenuItem(hmenu, tmp_id, MF_UNCHECKED);

	CheckMenuItem(hmenu, menu_id, MF_CHECKED);

	brush->pen_color = color;

}


// �ӿں������ж����λ�ã����ʻ�ͼ������ capture ʵ���� memDc
void
brush_picture(POINT mPos, CAPTURE *cap, BRUSH *brush, HWND hwnd) {

	assert(cap != NULL);
	assert(brush != NULL);

	if (!check_mouse_pos(mPos, *cap)) {

		return;

	}

	if (check_brush_color(*brush)) {

		return;

	}

	if (check_brush_prePoint(brush, mPos)) {

		return;

	}

	draw_brush_picture(hwnd, brush, mPos);

	change_capture_memdc(cap, hwnd);

}



/* 
			��̬���� 
*/

// ��̬�������ж����λ���Ƿ���ͼƬ��
static BOOL
check_mouse_pos(POINT mPos, CAPTURE cap) {

	RECT rect;

	rect.left = cap.pos.x;

	rect.top = cap.pos.y;

	rect.right = rect.left + cap.picSize.cx;

	rect.bottom = rect.top + cap.picSize.cy;

	return PtInRect(&rect, mPos);

}


// ��̬��������黭�ʵ���ɫ�Ƿ�Ϊ nocolor
static BOOL
check_brush_color(BRUSH brush) {

	if (brush.pen_color == nocolor) {

		return TRUE;

	}

	return FALSE;

}


// ��̬��������黭�ʵ� pre_point ����
static BOOL
check_brush_prePoint(BRUSH *brush, POINT mPos) {

	if (((brush->pre_point).x == 0) || ((brush->pre_point).y) == 0) {

		(brush->pre_point).x = mPos.x;
		(brush->pre_point).y = mPos.y;

		return TRUE;

	}

	return FALSE;

}


// ��̬���������ʻ�ͼ
static void
draw_brush_picture(HWND hwnd, BRUSH *brush, POINT mPos) {

	COLORREF color;
	HDC      hdc;

	hdc = GetDC(hwnd);

	switch (brush->pen_color) {

	case red:
		color = RGB(255, 0, 0);
		break;

	case green:
		color = RGB(0, 255, 0);
		break;

	case blue:
		color = RGB(0, 0, 255);
		break;

	}

	HPEN hpen = CreatePen(PS_SOLID, 5, color);

	SelectObject(hdc, hpen);

	MoveToEx(hdc, (brush->pre_point).x, (brush->pre_point).y, NULL);

	LineTo(hdc, mPos.x, mPos.y);

	brush->pre_point = mPos;

	ReleaseDC(hwnd, hdc);

}


// ��̬���������ʻ�ͼ��ͬʱ�ı� capture ʵ���е�memdc
static void
change_capture_memdc(CAPTURE *cap, HWND hwnd) {

	HDC windowDc = GetDC(hwnd);

	HBITMAP hBmp = CreateCompatibleBitmap(windowDc, (cap->picSize).cx, (cap->picSize).cy);

	SelectObject((cap->memDc), hBmp);

	if (!BitBlt(cap->memDc, 0, 0,
		(cap->picSize).cx, (cap->picSize).cy,
		windowDc,
		(cap->pos).x, (cap->pos).y,
		SRCCOPY)) {

		MessageBox(NULL, "��ͼʧ��", "����", MB_OK);

	}

}
