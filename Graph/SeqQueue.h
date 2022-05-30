#ifndef SEQ_QUEUE_
#define SEQ_QUEUE_

template <class T,int MaxSize>

class SeqQueue
{
	T data[MaxSize];
	int front,rear;
public:
	SeqQueue();
	void EnQueue(T x);
	T DeQueue();
	T GetQueue();
	bool Empty();
};



#endif