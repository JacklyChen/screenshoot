/*
+
-             ���ߣ�Joezeo < joezeo@outlook.com >
+
-             ����ʱ�䣺2017.12.23 / 21��52
+
-             �޸�ʱ�䣺2017.12.23 / 21��52
+
-             �ļ����ƣ�save.h
+
-             ���ܣ�saveģ���ͷ�ļ������������ļ����궨�壬saveģ�麯����ǰ��������
+                  saveģ�����Ҫ�������ڽ�ͼ��ϣ���ˢ��ͼ��Ϻ󣬱���ͼƬ��
-
+
*/
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
