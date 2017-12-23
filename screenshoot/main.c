/*
+
-             ���ߣ�Joezeo < joezeo@outlook.com >
+
-             ����ʱ�䣺2017.12.23 / 21��35
+
-             �޸�ʱ�䣺2017.12.23 / 21��35
+
-             �ļ����ƣ�main.c
+
-             ���ܣ�mainģ���Դ�ļ���mainģ�麯��������
+                  mainģ����Ҫ�������������ڣ��Լ������߼����ƣ���Ϣ���д���ȡ�
-
+
*/
#include "main.h"


CAPTURE				cap;
HINSTANCE			hInst;
TCHAR				szWndClassName[]	= "FrameWin";
TCHAR				szScreenClassName[]	= "ScreenWin";
TCHAR				szSaveClassName[]	= "SaveWin";
extern TCHAR		strFilename[MAX_PATH];


int WINAPI 
WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance, 
	LPSTR	  lpCmdLine,
	int		  nShowCmd) {

	HWND                    hwnd;

	MSG                     msg;

	WNDCLASS                wndclass;

	hInst = hInstance;

	wndclass.style              = CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc        = WndProc;

	wndclass.cbClsExtra         = 0;

	wndclass.cbWndExtra         = 0;

	wndclass.hInstance          = hInstance;

	wndclass.hIcon              = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BIGICON));

	wndclass.hCursor            = LoadCursor(NULL, IDC_ARROW);

	wndclass.hbrBackground      = (HBRUSH)GetStockObject(WHITE_BRUSH);

	wndclass.lpszMenuName       = "MyMenu";

	wndclass.lpszClassName      = szWndClassName;


	if (!RegisterClass(&wndclass)) {
		MessageBox(NULL, "ע��ʧ��", "����", MB_ICONERROR);
		return 0;
	}


	registe_sreenshoot_window(hInstance);

	registe_save_window(hInstance);


	HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU));


	hwnd = CreateWindow(
		szWndClassName,                         // windows class name
		"��ͼ����",                              // windows caption	
		WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX
		^ WS_THICKFRAME,                        // windows style
		CW_USEDEFAULT,                          // intial x position
		CW_USEDEFAULT,                          // intial y position
		WNDWIDTH,                               // intial x size
		WNDHEIGHT,                              // intial y size
		NULL,                                   // parent wnidow handle
		hMenu,                                  // window menu handle
		hInstance,                              // program instance handle
		NULL);                                  // creation paramenter


	ShowWindow(hwnd, nShowCmd); // ȫ������ SW_MAXIMIZE

	UpdateWindow(hwnd);


	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}

	return msg.wParam;
}


void
registe_sreenshoot_window(HINSTANCE hInstance) {

	WNDCLASS			wndclass;

	wndclass.style              = CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc        = ScreenProc;

	wndclass.cbClsExtra         = 0;

	wndclass.cbWndExtra         = sizeof(HANDLE);

	wndclass.hInstance          = hInstance;

	wndclass.hIcon              = LoadIcon(NULL, IDI_APPLICATION);

	wndclass.hCursor            = LoadCursor(NULL, IDC_ARROW);

	wndclass.hbrBackground      = (HBRUSH)GetStockObject(WHITE_BRUSH);

	wndclass.lpszMenuName       = NULL;

	wndclass.lpszClassName      = szScreenClassName;


	if (!RegisterClass(&wndclass)) {

		MessageBox(NULL, "ע��ʧ��", "����", MB_ICONERROR);

		return;
	}

}


void
registe_save_window(HINSTANCE hInstance) {

	WNDCLASS			wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	wndclass.lpfnWndProc = SaveProc;

	wndclass.cbClsExtra = 0;

	wndclass.cbWndExtra = sizeof(HANDLE);

	wndclass.hInstance = hInstance;

	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SAVEICON));

	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	wndclass.lpszMenuName = "SaveMenu";

	wndclass.lpszClassName = szSaveClassName;


	if (!RegisterClass(&wndclass)) {

		MessageBox(NULL, "ע��ʧ��", "����", MB_ICONERROR);

		return;
	}

}


void
create_screenshot_window(HWND *hwnd, HWND phwnd) {

	*hwnd = CreateWindow(szScreenClassName, TEXT("Child Demo"),
		WS_POPUP,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		phwnd, NULL, hInst, NULL);

}


void
create_save_window(HWND *hwnd) {

	HMENU hmenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENUSAVE));

	*hwnd = CreateWindow(szSaveClassName, TEXT("�����ͼ"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, SAVEWIDTH, SAVEHEIGHT,
		NULL, hmenu, hInst, NULL);

}


void
show_screenshot_window(HWND hwnd) {

	ShowWindow(hwnd, SW_MAXIMIZE);

	UpdateWindow(hwnd);

}


void
show_save_window(HWND hwnd, CAPTURE cap) {

	RECT				rect;
	SIZE				client_size;

	GetClientRect(hwnd, &rect);

	client_size.cx = rect.right - rect.left;
	client_size.cy = rect.bottom - rect.top;

	if (((cap.picSize).cx >= client_size.cx - 200) || ((cap.picSize).cy >= client_size.cy - 200)) {

		ShowWindow(hwnd, SW_MAXIMIZE);

	} else {

		ShowWindow(hwnd, SW_SHOWNORMAL);

	}

	UpdateWindow(hwnd);

}


LRESULT CALLBACK 
WndProc(HWND hwnd, UINT message, WPARAM wparam,LPARAM lparam) {

	HDC                         hdc;

	PAINTSTRUCT                 ps;

	RECT                        rect;

	static HWND                 ChildWnd;

	switch (message) {
	case WM_CREATE: 

		create_screenshot_window(&ChildWnd, hwnd);

		return 0;
	

	case WM_MENUSELECT: 

		switch (LOWORD(wparam)) {

		case IDABORT:

			ShowWindow(hwnd, SW_HIDE);

			// �������"�½�"��ť����ScreenShot���ڴ���WM_CAPTION��Ϣ����ȡ����ͼ�񣬱�����hdcMemDc��
			SendMessage(ChildWnd, WM_CAPTION, 0, 0);

			show_screenshot_window(ChildWnd);

			break;

		case ID_40001:

			SendMessage(hwnd, WM_CLOSE, 0, 0);

			break;

		}
		return 0;


	case WM_SHOW:

		ShowWindow(hwnd, SW_SHOWNORMAL);

		return 0;
	

	case WM_PAINT: 

		hdc = BeginPaint(hwnd, &ps);

		GetClientRect(hwnd, &rect);

		SelectObject(hdc, GetStockObject(DEFAULT_GUI_FONT));

		DrawText(hdc, "����½���ʼ��ͼ~����ͼ�����а�ESCȡ����ͼ��", -1, &rect, DT_LEFT);

		EndPaint(hwnd, &ps);

		return 0;
	

	case WM_DESTROY: 

		PostQuitMessage(0);

		return 0;
	
	}


	return DefWindowProc(hwnd, message, wparam, lparam);
}


LRESULT CALLBACK
ScreenProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {

	HDC                             hdc;
	HWND							fhwnd;
	POINT							mPos;
	PAINTSTRUCT                     ps;
	static HWND						phwnd;
	static HWND						SaveWnd;
	static SELECTBOX				selectbox;
	static SCREEN					screen;

	switch (message) {

	case WM_CREATE:

		phwnd = GetParent(hwnd);

		init_screen(&screen, hwnd);

		init_capture(&cap);

		init_selectbox(&selectbox);

		create_save_window(&SaveWnd);

		return 0;


	case WM_CAPTION:

		screen_caption(hwnd, &screen);

		return 0;


	case WM_LBUTTONDOWN:

		mPos.x = LOWORD(lparam);

		mPos.y = HIWORD(lparam);

		(cap.pos).x = LOWORD(lparam);

		(cap.pos).y = HIWORD(lparam);

		capture_image(&cap, hwnd, SaveWnd);

		(selectbox.cnt)++;

		draw_selectbox(&selectbox, hwnd, mPos, screen);

		if (cap.status) {

			cap.status = FALSE;

			ShowWindow(hwnd, SW_HIDE);

			// ��capture_image��ͼ��ϣ���ʾSaveWin����
			show_save_window(SaveWnd, cap);

		}
		return 0;


	case WM_MOUSEMOVE:

		mPos.x = LOWORD(lparam);

		mPos.y = HIWORD(lparam);

		draw_selectbox(&selectbox, hwnd, mPos, screen);

		return 0;


	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);

		screen_draw(hdc, screen);

		EndPaint(hwnd, &ps);

		return 0;


	case WM_KEYDOWN:

		switch (wparam) {

		case VK_ESCAPE:

			// ����û��ڽ�ͼ���滹û��ʼ��ͼ�����ESC�˳���ͼ
			if (selectbox.set_sta == FALSE) {

				init_capture(&cap);

				init_selectbox(&selectbox);

				ShowWindow(hwnd, SW_HIDE);

				SendMessage(phwnd, WM_SHOW, 0, 0);

			} 
			// ����û��ڽ�ͼ�����Ѿ���ʼ��ʼ��ͼ�����ESC����ѡ��
			else {

				init_capture(&cap);

				init_selectbox(&selectbox);

				hdc = GetDC(hwnd);

				BitBlt(hdc, 0, 0,
					screen.screen_size.cx, screen.screen_size.cy,
					screen.hdcMemDC,
					0, 0, SRCCOPY);

				ReleaseDC(hwnd, hdc);

			}

			

			break;

		}

		return 0;


	case WM_RECAP:

		init_selectbox(&selectbox);

		init_capture(&cap);

		fhwnd = FindWindow(szWndClassName, NULL);

		ShowWindow(fhwnd, SW_SHOWNORMAL);

		return 0;


	case WM_DESTROY:

		PostQuitMessage(0);

		return 0;


	}

	return DefWindowProc(hwnd, message, wparam, lparam);

}


LRESULT CALLBACK
SaveProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {

	HDC							hdc;
	HWND						phwnd;	
	POINT						mPos;
	PAINTSTRUCT					ps;
	static HMENU				hMenu;
	static HMENU				subMenu;
	static BRUSH				brush;
	static OPENFILENAME			sFile;

	switch (message) {

	case WM_CREATE:

		hMenu = GetMenu(hwnd);

		subMenu = GetSubMenu(hMenu, 4);

		init_brush(&brush);

		return 0;
		

	case WM_PAINT:

		hdc = BeginPaint(hwnd, &ps);

		draw_image(&cap, hdc, hwnd);

		EndPaint(hwnd, &ps);

		return 0;


	case WM_LBUTTONDOWN:

		mPos.x = LOWORD(lparam);
		mPos.y = HIWORD(lparam);

		brush_picture(mPos, &cap, &brush, hwnd);

		return 0;


	case WM_LBUTTONUP:

		brush.pre_point.x = 0;
		brush.pre_point.y = 0;

		return 0;


	case WM_MOUSEMOVE:

		//�������������������
		if (MK_LBUTTON & wparam) {

			mPos.x = LOWORD(lparam);
			mPos.y = HIWORD(lparam);

			brush_picture(mPos, &cap, &brush, hwnd);

		}


	case WM_COMMAND:

		if (lparam == 0) {

			switch (LOWORD(wparam)) {

			case ID_SAVE:

				init_save_file(&sFile, hwnd, hInst);

				/*����û�ָ�����ļ�����������ȷ����ť������ֵ��Ϊ�㡣
				ָ��� OPENFILENAME �ṹ�� lpstrFile ��Ա�ڻ������а���������·�����ļ����ơ�*/
				if (GetSaveFileName(&sFile)) { 

					MessageBox(NULL, sFile.lpstrFile, TEXT("���浽"), 0);

					HBITMAP hbmp;

					hdc = GetDC(hwnd);

					hbmp = GetSrcBit(cap.memDc, cap.picSize.cx, cap.picSize.cy);

					save_bmp_file(hbmp, sFile.lpstrFile, hdc);

					ReleaseDC(hwnd, hdc);

					DeleteObject(hbmp);

				}

				break;


			case ID_RECAP:

				change_menu_checked(&brush, nocolor, 0, subMenu);

				phwnd = FindWindow(szScreenClassName, NULL);

				SendMessage(phwnd, WM_RECAP, 0, 0);

				ShowWindow(hwnd, SW_HIDE);

				break;

			case ID_REDPEN:

				change_menu_checked(&brush, red, ID_REDPEN, subMenu);

				break;

			case ID_BLUEPEN:

				change_menu_checked(&brush, blue, ID_BLUEPEN, subMenu);

				break;

			case ID_GREENPEN:

				change_menu_checked(&brush, green, ID_GREENPEN, subMenu);

				break;

			}

		}

		return 0;
		
	case WM_DESTROY:

		PostQuitMessage(0);

		return 0;

	}

	return DefWindowProc(hwnd, message, wparam, lparam);

}
