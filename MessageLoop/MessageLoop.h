#pragma once
#include <functional>
#include <atomic>
#include <mutex>
#include <queue>
#include <list>

#include "LockFreeQueue.h"

//�̰߳�ȫ����Ϣѭ��
class MessageLoop
{
public:
	MessageLoop();
	~MessageLoop();

	virtual int Run();

	virtual void Quit(int value= 0);
	
	template<typename Func, typename... ArgsType>
	void PostTask(Func func, ArgsType...args)
	{
		queue_list_.push_back(std::bind(func, args...));
	}

	bool CheckRunUIThread();

private:
	DataCache::LockFreeQueue<std::function<void(void)>> queue_list_;
	int thread_id_ = 0 ;
};
