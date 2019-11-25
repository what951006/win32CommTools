#pragma once
#include <Windows.h>
#include <tchar.h>

#ifndef DELEGATE_FUNC_BEGIN
	#define DELEGATE_FUNC_BEGIN(ClassName)                     \
	public:                                                    \
		void SetDelegate(ClassName * class_name)               \
		{delegate_ = class_name;}                              \
		ClassName *  GetDelegate() {return delegate_;}         \
	private:                                                   \
		ClassName * delegate_ = nullptr;                       \
	public:                                                    \
		class ClassName{                                       \
		public:
#endif

#ifndef DELEGATE_FUNC_END
	#define DELEGATE_FUNC_END                                  \
	};
#endif

class StandardWindow
{
public:
	class Delegate;
	DELEGATE_FUNC_BEGIN(Delegate)
		virtual void OnDelegatePaint(StandardWindow *,HDC dc) {}
		virtual void OnDelegateResize(StandardWindow *,int width, int height) {}
		virtual bool OnDelegateClosed(StandardWindow *) { return true; }
		virtual void OnDelegateDestory(StandardWindow *) {}
		virtual void OnDelegateFinal(StandardWindow *) {}
	DELEGATE_FUNC_END
public:
	StandardWindow();
	virtual ~StandardWindow();
	
	static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	HWND CreateBaseWindow(HWND parent ,DWORD dwExStyle,int x=0 ,int y =0,int w=1,int h=1);

	void SetGeometry(int x ,int y ,int w ,int h);

	void Show();

	void Hide();

	HWND GetHwnd();

	void Update();

	bool IsLayeredWindow();
protected:
	void OnSysPaintEventPaint(HDC dc);
	void OnSysLayeredPaint(HDC dc);

	virtual void OnPaint(HDC dc);
	virtual void OnResize(int width, int height);
	virtual bool OnClosed();
	virtual void OnDestory();
	virtual void OnFinal();

	HWND hwnd_ = NULL;
private:
	void CreateMemDC(HDC &mem_dc,HBITMAP &mem_bitmap ,HDC dc,int cx,int cy);
	void DeleteMemDC(HDC mem_dc, HBITMAP mem_bitmap);
};