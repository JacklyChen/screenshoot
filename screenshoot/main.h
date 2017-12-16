#ifndef __MAIN_H__
#define __MAIN_H__

#include "resource.h"
#include "../screen/screen.h"
#include "../capturer/capturer.h"
#include "../brush/brush.h"
#pragma comment(lib,"msimg32.lib")
#pragma comment(lib,"winmm.lib")

#ifdef __cplusplus
extern "C"{
#endif

#define		WNDWIDTH				555				// �����ڿ�
#define		WNDHEIGHT				100				// �����ڸ�
#define		SAVEWIDTH				1000			// Save���ڿ�
#define		SAVEHEIGHT				750				// Save���ڸ�

#define		WM_CAPTION				(WM_USER + 1)	// CAPTION �¼������û�������½���ʱ����
#define		WM_SHOW					(WM_USER + 2)	// SHOW    �¼������û��ڽ�ͼ�����ESCʱ����
#define		WM_RECAP				(WM_USER + 3)	// RECAP   �¼�����������������½�ͼ��ʱ���� ScreenProc �д���

void
registe_sreenshoot_window(HINSTANCE);

void
registe_save_window(HINSTANCE);

void
create_screenshot_window(HWND *, HWND);

void
create_save_window(HWND *);

void
show_screenshot_window(HWND);

void
show_save_window(HWND, CAPTURE);

LRESULT CALLBACK
WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK
ScreenProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK
SaveProc(HWND, UINT, WPARAM, LPARAM);


#ifdef __cplusplus
}
#endif
#endif