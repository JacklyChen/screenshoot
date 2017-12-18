#ifndef __SAVE_H__
#define __SAVE_H__

#include <windows.h>
#include <assert.h>
#include "../capturer/capturer.h"

#ifdef __cplusplus
extern "C" {
#endif

void
init_save_file(OPENFILENAME *, HWND, HINSTANCE);                 // ��ʼ�������ļ��Ի���

HBITMAP
GetSrcBit(HDC hDC, DWORD BitWidth, DWORD BitHeight);             // ��captureʵ����memDc��ȡ��HBITMAP

void
save_bmp_file(HBITMAP, LPSTR, HDC);                              // ���� bmp ͼƬ

#ifdef __cplusplus
}
#endif
#endif
