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
}BRUSH;

void
init_brush(BRUSH *);                                 // �ӿں�������ʼ�� BRUSH ʵ��

void
change_menu_checked(BRUSH *, PENCOLOR, UINT, HMENU); // �ӿں������ı�˵����� check ���Ե�״̬

void
brush_picture(POINT, CAPTURE);                       // �ӿں������ж����λ�ã����ʻ�ͼ

static BOOL
check_mouse_pos(POINT, CAPTURE);					 // ��̬�������ж����λ���Ƿ���ͼƬ��

#ifdef __cplusplus
}
#endif
#endif
