#include<assert.h>
template <class T>
class Queue
{
public:
    Queue(int sz = 50);
    bool push(const T &x);
    bool pop();
    T get_front(); //获取队头元素
    bool empty() const
    {
        return (front == rear) ? true : false;
    }
    bool full() const
    {
        return ((rear + 1) % maxsize == front) ? true : false;
    }
    int size() const
    {
        return (rear - front + maxsize) % maxsize;
    } //获取队列元素个数
private:
    int front, rear;
    T *element;
    int maxsize;
};
template <class T>
Queue<T>::Queue(int sz)
{
    maxsize=sz;
    front=0;rear=0;
    element = new T[maxsize];
    assert(element != NULL);
}

template <class T>
bool Queue<T>::push(const T &x)
{
    if (full() == true)
        return false;
    element[rear] = x;
    rear = (rear + 1) % maxsize;
    return true;
}

template <class T>
bool Queue<T>::pop()
{
    if (empty() == true)
        return false;
    T x = element[front];
    front = (front + 1) % maxsize;
    return true;
}

template <class T>
T Queue<T>::get_front()
{
    if (empty() == true)
        return -1;
    return element[front];
}