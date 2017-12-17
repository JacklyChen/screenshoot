#ifndef __BOX_H__
#define __BOX_H__

#include <windows.h>
#include <assert.h>
#include "../screen/screen.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	POINT sta_pos; // ѡ�����ʼ��
	BOOL  set_sta; // �Ƿ����ó�ʼ��
	UINT  cnt;	   // ���������
}SELECTBOX;


void
init_selectbox(SELECTBOX *);                              // �ӿں�������ʼ�� SELECTBOX ʵ��

void
draw_selectbox(SELECTBOX *, HWND, POINT, SCREEN);         // �ӿں�������ѡ��������ƺ���

static void
redraw_image(HWND, SCREEN);                               // ÿ�λ�����ѡ���֮ǰ���ػ�����ͼ��

static void
draw_box(SELECTBOX *, HWND, POINT);                       // ��̬����������ѡ���

#ifdef __cplusplus
}
#endif

#endif
