#pragma once
template <class T>
class Stack
{
protected:
    T *data;
    int count;
    int max=1000;

public:
    Stack()
    {
        data = new T[1000];
        count = 0;
    }
    Stack(int n)
    {
        data = new T[n];
        count = 0;
        max=n;
    }
    ~Stack()
    {
        delete[] data;
    }

    int size()
    {
        return count;
    }
    bool push(T a)
    {
        if(count==max){
            return false;
        }
        data[count++] = a;
        return true;
    }
    bool pop()
    {
        if (count == 0)
            return false;
        T a = data[--count];
        return true;
    }
    bool s_top(T &a){
        if(empty())
        {
            return false;
        }
        a=data[count-1];
        return true;
    }
    T top()
    {
        T a = data[count - 1];
        return a;
    }
    bool empty()
    {
        if (count == 0)
            return true;
        return false;
    }
};