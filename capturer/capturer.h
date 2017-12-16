#ifndef __CAPTURER_H__
#define __CAPTURER_H__

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {

	UINT	bCnt;	// �������������
	BOOL	status;	// �Ƿ��ͼ�ɹ�
	RECT	rect;	// ��ȡͼ��ľ�������
	POINT	pos;	// ���ʱ������꣬�Լ���ͼ��ͼƬ�ڿͻ���������
	HDC		memDc;	// �洢��ͼ��Ϣ��memDc
	SIZE	picSize;// ��ȡͼƬ�Ĵ�С

}CAPTURE;

void
init_capture(CAPTURE *);					// �ӿں�������ʼ�� CAPTURE ʵ��

void
capture_image(CAPTURE *, HWND, HWND);		// �ӿں�����ѡ��ͼƬ������ͼƬ�� CAPTURE ʵ����memDc��

void
draw_image(CAPTURE *, HDC, HWND);			// �ӿں��������� capture ʵ�� memDc �д�ŵ�ͼ��

static void
select_image(CAPTURE *);					// ��̬������ѡ��ͼƬ

static void
store_image(CAPTURE *, HWND, HWND);			// ��̬����������ͼƬ�� CAPTURE ʵ����memDc��

#ifdef __cplusplus
}
#endif
#endif
