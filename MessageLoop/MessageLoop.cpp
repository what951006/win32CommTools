#include "MessageLoop.h"
#include <windows.h>

MessageLoop::MessageLoop()
{
	
}

MessageLoop::~MessageLoop()
{

}

int MessageLoop::Run()
{
    thread_id_ = GetCurrentThreadId();
	while (true)
	{
		if (queue_list_.GetLength() > 0)
		{
			queue_list_.pop_front()();
		}

		MSG msg = { 0 };
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return msg.wParam;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//TODO������������Σ���Ȼ�ܽ���CPU������������
		std::this_thread::sleep_for(std::chrono::nanoseconds(1));
	}
	return -1;
}

void MessageLoop::Quit(int quit_code)
{
	PostTask([&, quit_code] {
		PostQuitMessage(quit_code);
	});
}

bool MessageLoop::CheckRunUIThread()
{
	return GetCurrentThreadId() == thread_id_;
}