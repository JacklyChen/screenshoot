/*
+
-             ���ߣ�Joezeo < joezeo@outlook.com >
+
-             ����ʱ�䣺2017.12.23 / 21��47
+
-             �޸�ʱ�䣺2017.12.23 / 21��47
+
-             �ļ����ƣ�brush.h
+
-             ���ܣ�brushģ���ͷ�ļ������������ļ����궨�壬brushģ�麯����ǰ��������
+                  brushģ�����Ҫ����Ϊ��ˢ��ѡ�񻭱ʣ�������ͼ��
-
+
*/
#ifndef __BRUSH_H__
#define __BRUSH_H__

#include <windows.h>
#include <assert.h>
#include "../capturer/capturer.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum {
	nocolor = 0,
	red,
	blue,
	green,
}PENCOLOR;

typedef struct {
	PENCOLOR pen_color; // ������ɫ
	POINT    pre_point; // ǰһ��������
}BRUSH;

void
init_brush(BRUSH *);                                 // �ӿں�������ʼ�� BRUSH ʵ��

void
change_menu_checked(BRUSH *, PENCOLOR, UINT, HMENU); // �ӿں������ı�˵����� check ���Ե�״̬

void
brush_picture(POINT, CAPTURE *, BRUSH *, HWND);		 // �ӿں������ж����λ�ã����ʻ�ͼ

static BOOL
check_mouse_pos(POINT, CAPTURE);					 // ��̬�������ж����λ���Ƿ���ͼƬ��

static BOOL
check_brush_color(BRUSH);                            // ��̬��������黭�ʵ���ɫ�Ƿ�Ϊ nocolor

static BOOL
check_brush_prePoint(BRUSH *, POINT);                // ��̬��������黭�ʵ� pre_point ����

static void
draw_brush_picture(HWND, BRUSH *, POINT);            // ��̬���������ʻ�ͼ

static void
change_capture_memdc(CAPTURE *, HWND);               // ��̬���������ʻ�ͼ��ͬʱ�ı� capture ʵ���е�memdc


#ifdef __cplusplus
}
#endif
#endif
