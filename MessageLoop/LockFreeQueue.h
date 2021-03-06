#ifndef __GLOBAL_LOCK_FREE_QUEUE_H__
#define __GLOBAL_LOCK_FREE_QUEUE_H__

#include <atomic>
#include <list>

#ifdef _WINDOWS
#include <windows.h>
//PVOID __cdecl InterlockedCompareExchangePointer(
//    _Inout_ PVOID volatile *Destination,
//    _In_    PVOID          Exchange,
//    _In_    PVOID          Comparand
//    );
//
//Parameters
//    Destination [in, out]
//A pointer to a pointer to the destination value.
//    Exchange [in]
//The exchange value.
//    Comparand [in]
//The value to compare to Destination.
//    Return value
//    The function returns the initial value of the Destination parameter.
//    Remarks
//    The function compares the Destination value with the Comparand value. If the Destination value is equal to the Comparand value, the Exchange value is stored in the address specified by Destination. Otherwise, no operation is performed.
//    On a 64-bit system, the parameters are 64 bits and must be aligned on 64-bit boundaries; otherwise, the function will behave unpredictably. On a 32-bit system, the parameters are 32 bits and must be aligned on 32-bit boundaries.
//    The interlocked functions provide a simple mechanism for synchronizing access to a variable that is shared by multiple threads. This function is atomic with respect to calls to other interlocked functions.
#define __sync_bool_compare_and_swap(a,b,c) (InterlockedCompareExchangePointer((void*volatile*)a,c,b), (*a)==(c))
#endif

namespace DataCache
{

    template <typename T>
    class LinkList
    {
    public:
        T data;
        LinkList<T> *next;
    };// class LinkeList<T>

    template <typename T>
    class LockFreeQueue
    {
    public:
        LockFreeQueue();

        void Push(T t);

        T Pop(void);

        bool Empty();

        int Length();

    private:
        LinkList<T> *head_;
        LinkList<T> *tail_;
        std::atomic_int count_;
    }; // class LockFreeQueue

    template <typename T>
    LockFreeQueue<T>::LockFreeQueue()
        :head_(NULL),
        tail_(new LinkList<T>),
        count_(0)
    {
        head_ = tail_;
        tail_->next = NULL;
    }

    template <typename T>
    void LockFreeQueue<T>::Push(T t)
    {
        auto newVal = new LinkList<T>;
        newVal->data = t;
        newVal->next = NULL;

        LinkList<T> *p;
        do
        {
            p = tail_;
        } while (!__sync_bool_compare_and_swap(&tail_->next, NULL, newVal));

        //move tail_
        __sync_bool_compare_and_swap(&tail_, tail_, newVal);
        count_++;
    }

    template <typename T>
    T LockFreeQueue<T>::Pop()
    {
        LinkList<T> *p;

        do
        {
            //record the first node.
            p = head_->next;
            if (!p)
            {
                return 0;
            }
        } while (!__sync_bool_compare_and_swap(&head_->next, p, p->next));

        if (count_ > 0) count_--;
        if (count_ == 0)
        {
            // if the queue is empty then the tail to header.
            do
            {

            } while (!__sync_bool_compare_and_swap(&tail_, p, head_));
        }

        return p->data;
    }

    template <typename T>
    bool LockFreeQueue<T>::Empty()
    {
        if (count_ == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename T>
    int LockFreeQueue<T>::Length()
    {
        return count_;
    }

}// namespace DataCache

#endif