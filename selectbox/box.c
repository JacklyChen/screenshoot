#include "box.h"

/*
			�ӿں���
*/

// �ӿں�������ʼ�� SELECTBOX ʵ��
void
init_selectbox(SELECTBOX * selectbox) {

	assert(selectbox != NULL);

	(selectbox->sta_pos).x = 0;
	(selectbox->sta_pos).y = 0;

	selectbox->set_sta = FALSE;

	selectbox->cnt = 0;

}


// �ӿں�������ѡ��������ƺ���
void
draw_selectbox(SELECTBOX * selectbox, HWND hwnd, POINT mPos, SCREEN screen) {

	assert(selectbox != NULL);
	assert(hwnd != NULL);

	if ((selectbox->cnt) == 1) {

		selectbox->sta_pos = mPos;

		selectbox->set_sta = TRUE;

		selectbox->cnt++;

		return;

	}

	if (selectbox->set_sta) {

		redraw_image(hwnd, screen);

		draw_box(selectbox, hwnd, mPos);

	}

}


/*
			��̬����
*/

// ÿ�λ�����ѡ���֮ǰ���ػ�����ͼ��
static void
redraw_image(HWND hwnd, SCREEN screen) {

	HDC						hdc;

	hdc = GetDC(hwnd);

	BitBlt(hdc, 0, 0,
		screen.screen_size.cx, screen.screen_size.cy,
		screen.hdcMemDC,
		0, 0, SRCCOPY);

	ReleaseDC(hwnd, hdc);

}


// ��̬����������ѡ���
static void
draw_box(SELECTBOX *selectbox, HWND hwnd, POINT mPos) {

	HDC						hdc;
	SIZE					box_size;
	POINT					right_top;
	POINT					left_bottom;
	POINT					points[4];

	hdc = GetDC(hwnd);

	box_size.cx = mPos.x - (selectbox->sta_pos).x;
	box_size.cy = mPos.y - (selectbox->sta_pos).y;

	right_top.x = (selectbox->sta_pos).x + box_size.cx;
	right_top.y = (selectbox->sta_pos).y;

	left_bottom.x = (selectbox->sta_pos).x;
	left_bottom.y = (selectbox->sta_pos).y + box_size.cy;

	points[0] = selectbox->sta_pos;
	points[1] = right_top;
	points[2] = mPos;
	points[3] = left_bottom;

	//SetROP2(hdc, R2_XORPEN);

	//SelectObject(hdc, GetStockObject(WHITE_PEN));

	HPEN hpen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));

	SelectObject(hdc, hpen);

	for (int i = 0; i < 4; i++) {

		MoveToEx(hdc, points[i].x, points[i].y, NULL);

		LineTo(hdc, points[i + 1].x, points[i + 1].y);

	}

	MoveToEx(hdc, points[3].x, points[3].y, NULL);

	LineTo(hdc, points[0].x, points[0].y);

	ReleaseDC(hwnd, hdc);

}