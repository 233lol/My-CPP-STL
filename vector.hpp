template <class T>
class Vector
{
public:
    Vector(); //构造函数
    Vector(int n);

    void push_back(T ele);
    T pop_back();

    T &operator[](int i)
    { //下标运算符
        return data[i];
    }

    int size()
    {
        return size_l;
    }
    bool empty()
    {
        return size_l == 0;
    }
    ~Vector()
    {
        delete[] data;
    }

private:
    T *data;
    int size_l;                   //当前数组的元素个数
    int capacity;                 //当前数组最大的容量
    bool resize(int newcapacity); //重新分配大小
};

template <class T>
Vector<T>::Vector()
{
    data = new T[10];
    size_l = 0;
    capacity = 10;
}

template <class T>
Vector<T>::Vector(int n)
{
    data = new T[n * 2];
    size_l = n;
    capacity = n * 2;
}

template <class T>
bool Vector<T>::resize(int newcapacity)
{
    if (newcapacity < size_l)
        return false;
    T *newdata = new T[newcapacity];
    for (int i = 0; i < size_l; i++)
    {
        newdata[i] = data[i];
    }
    delete[] data;
    data = newdata;
    capacity = newcapacity;
    return true;
}

template <class T>
void Vector<T>::push_back(T ele)
{
    if (size_l == capacity && !resize(capacity * 2))
        return;
    data[size_l++] = ele;
}

template <class T>
T Vector<T>::pop_back()
{
    return data[--size_l];
}
