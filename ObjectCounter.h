#ifndef _OBJECTCOUNTER_H
#define _OBJECTCOUNTER_H

template <typename T>
class ObjectCounter {
public:
	ObjectCounter() { ++objectAmount; }
	virtual ~ObjectCounter() { --objectAmount; }

	static unsigned long GetAmount() { return objectAmount; }

private:
	static unsigned long objectAmount;
};

template<typename T>
unsigned long ObjectCount<T>::objectAmount = 0;

#endif // !_OBJECTCOUNTER_H
