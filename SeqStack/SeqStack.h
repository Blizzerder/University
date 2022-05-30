#ifndef SEQ_STACK_
#define SEQ_STACK_

template <class T,int MaxSize>
class SeqStack
{
	T data[MaxSize];
	int top;
public:
	SeqStack();
	void Push(T x);
	T Pop();
	T Top();
	bool IsEmpty();
	bool IsFull();
	void Print();
};

#endif 