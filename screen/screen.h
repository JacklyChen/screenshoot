#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <windows.h>
#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

void
screen_caption(HWND);                // ��Ļ��ȡ������ȡ��ͼ����� ȫ�ֱ���hdcMemDc ��

void
screen_draw(HDC);                    // ���� ȫ�ֱ���hdcMemDc �д�ŵ���Ļͼ��

#ifdef __cplusplus
}
#endif
#endif
