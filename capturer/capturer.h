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
	POINT	pos;	// ���ʱ�������
	HDC		memDc;	// �洢��ͼ��Ϣ��memDc
}CAPTURE;

void
init_capture(CAPTURE *);		// ��ʼ�� capture ʵ��

void
capture_image(CAPTURE *, HWND);				// �ӿں���������һ������н�ͼ��Ϣ��memhdc

static void
select_image(CAPTURE *);					// ��̬������ѡ��ͼƬ

static void
store_image(CAPTURE *, HWND);				// ��̬����������ͼƬ

#ifdef __cplusplus
}
#endif
#endif
