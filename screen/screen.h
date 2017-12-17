#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <windows.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	HDC  hdcMemDC;
	SIZE screen_size;
}SCREEN;

void
init_screen(SCREEN *, HWND);          // ��ʼ��SCREENʵ��

void
screen_caption(HWND, SCREEN *);      // ��Ļ��ȡ������ȡ��ͼ����� ȫ�ֱ���hdcMemDc ��

void
screen_draw(HDC, SCREEN);            // ���� ȫ�ֱ���hdcMemDc �д�ŵ���Ļͼ��

#ifdef __cplusplus
}
#endif
#endif
