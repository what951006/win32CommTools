#include "StandardWindow.h"

#define STTANDARD_CLASS_NAME _T("StandardWnd")

StandardWindow::StandardWindow()
{
}


StandardWindow::~StandardWindow()
{
	if (hwnd_)
		DestroyWindow(hwnd_);
}

LRESULT CALLBACK StandardWindow::WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	StandardWindow *  target_obj = (StandardWindow *)GetWindowLongPtr(hwnd, GWLP_USERDATA);
	switch (message)                  /* handle the messages */
	{
	case WM_NCCREATE:
	{
		StandardWindow* remote = (StandardWindow*)((CREATESTRUCT*)lParam)->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)remote);
		remote->hwnd_ = hwnd;
	}
	break;
	case WM_NCDESTROY:
	{
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)NULL);
		target_obj->hwnd_ = NULL;
		target_obj->OnFinal();
	}
	break;
	case WM_CLOSE:
	{
		if (target_obj->OnClosed())
		{
			DestroyWindow(hwnd);
		}
		else
		{
			return true;
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT pt;
		HDC hdc = BeginPaint(hwnd, &pt);

		target_obj->OnSysPaintEventPaint(hdc);

		EndPaint(hwnd, &pt);
	}
	break;
	case WM_DESTROY:
	{
		target_obj->OnDestory();
	}
	break;
	case WM_SIZE:
	{
		target_obj->OnResize(LOWORD(lParam), HIWORD(lParam));
	}
	break;
	default:
		break;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

HWND StandardWindow::CreateBaseWindow(DWORD dwExStyle, HWND parent_hwnd)
{
	WNDCLASSEX wincl;        /* Data structure for the window class */

   /* The Window structure */
	wincl.hInstance = GetModuleHandle(NULL);
	wincl.lpszClassName = STTANDARD_CLASS_NAME;//+-69+
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
	/* Use Windows's default colour as the background of the window */
	wincl.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	/* Register the window class, and if it fails quit the program */
	RegisterClassEx(&wincl);

	hwnd_ = CreateWindowEx(
		dwExStyle,             /* Extended possibilites for variation */
		STTANDARD_CLASS_NAME,         /* class name */
		STTANDARD_CLASS_NAME,       /* Title Text */
		WS_POPUP, /* default window */
		0,       /* Windows decides the position */
		0,       /* where the window ends up on the screen */
		1,                 /* The programs width */
		1,                 /* and height in pixels */
		parent_hwnd,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		GetModuleHandle(NULL),       /* Program Instance handler */
		this                 /* No Window Creation data */
	);
	return hwnd_;
}

void StandardWindow::SetGeometry(int x, int y, int w, int h)
{
	MoveWindow(hwnd_, x, y, w, h, true);
}

void StandardWindow::Show()
{
	ShowWindow(hwnd_, SW_SHOW);
}

void StandardWindow::Hide()
{
	ShowWindow(hwnd_, SW_HIDE);
}

HWND StandardWindow::GetHwnd()
{
	return hwnd_;
}

void StandardWindow::Update()
{

}

bool StandardWindow::IsLayeredWindow()
{
	return GetWindowLong(hwnd_, GWL_EXSTYLE) & WS_EX_LAYERED;
}

void StandardWindow::OnSysPaintEventPaint(HDC dc)
{
	HDC mem_dc;
	HBITMAP mem_bitmap;
	RECT re;
	GetClientRect(hwnd_, &re);

	CreateMemDC(mem_dc, mem_bitmap,dc, re.right, re.bottom);
	
	OnPaint(mem_dc);

	BitBlt(dc, 0, 0, re.right, re.bottom, mem_dc, 0, 0, SRCCOPY);

	DeleteMemDC(mem_dc, mem_bitmap);
}

void StandardWindow::OnSysLayeredPaint(HDC dc)
{
	HDC mem_dc;
	HBITMAP mem_bitmap;
	RECT client_rect;
	GetClientRect(hwnd_, &client_rect);

	CreateMemDC(mem_dc, mem_bitmap, dc, client_rect.right, client_rect.bottom);

	OnPaint(mem_dc);

	BitBlt(dc, 0, 0, client_rect.right, client_rect.bottom, mem_dc, 0, 0, SRCCOPY);

	
	POINT ptsrc{ 0, 0 };
	POINT ptDest{ 0, 0};
	SIZE wnd_size{ client_rect.right,client_rect.bottom };
	BLENDFUNCTION blend = { AC_SRC_OVER, 0, (BYTE)(255.0), AC_SRC_ALPHA };
	UpdateLayeredWindow(hwnd_, dc, &ptDest, &wnd_size, mem_dc, &ptsrc, 0, &blend, ULW_ALPHA);

	DeleteMemDC(mem_dc, mem_bitmap);
}

void StandardWindow::OnPaint(HDC dc)
{
	auto delegate = GetDelegate();
	if (delegate)
	{
		delegate->OnDelegatePaint(this,dc);
	}
}

void StandardWindow::OnResize(int width, int height)
{
	auto delegate = GetDelegate();
	if (delegate)
	{
		delegate->OnDelegateResize(this,width, height);
	}

	if (IsLayeredWindow())
	{
		HDC dc = GetDC(hwnd_);
		OnSysLayeredPaint(dc);
		ReleaseDC(hwnd_,dc);
	}
	
}

bool StandardWindow::OnClosed()
{
	auto delegate = GetDelegate();
	if (delegate)
	{
		return delegate->OnDelegateClosed(this);
	}
	return true;
}

void StandardWindow::OnDestory()
{
	auto delegate = GetDelegate();
	if (delegate)
	{
		delegate->OnDelegateDestory(this);
	}
}

void StandardWindow::OnFinal()
{
	auto delegate = GetDelegate();
	if (delegate)
	{
		delegate->OnDelegateFinal(this);
	}
}

void StandardWindow::CreateMemDC(HDC &mem_dc, HBITMAP &mem_bitmap,HDC dc, int cx, int cy)
{
	mem_dc = ::CreateCompatibleDC(dc);

	BITMAPINFO bitmapinfo;
	bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfo.bmiHeader.biBitCount = 32;
	bitmapinfo.bmiHeader.biHeight = cy;
	bitmapinfo.bmiHeader.biWidth = cx;
	bitmapinfo.bmiHeader.biPlanes = 1;
	bitmapinfo.bmiHeader.biCompression = BI_RGB;
	bitmapinfo.bmiHeader.biXPelsPerMeter = 0;
	bitmapinfo.bmiHeader.biYPelsPerMeter = 0;
	bitmapinfo.bmiHeader.biClrUsed = 0;
	bitmapinfo.bmiHeader.biClrImportant = 0;
	bitmapinfo.bmiHeader.biSizeImage =
		bitmapinfo.bmiHeader.biWidth * bitmapinfo.bmiHeader.biHeight *
		bitmapinfo.bmiHeader.biBitCount / 8;
	mem_bitmap = ::CreateDIBSection(mem_dc, &bitmapinfo, 0, NULL, 0, 0);
	SelectObject(mem_dc, mem_bitmap);
}

void StandardWindow::DeleteMemDC(HDC mem_dc, HBITMAP mem_bitmap)
{
	if (mem_dc)
	{
		::DeleteDC(mem_dc);
	}
	if (mem_bitmap)
	{
		::DeleteObject(mem_bitmap);
	}
}
