#pragma once
template <class T>
inline void swap(T &a, T &b)
{
    T t = a;
    a = b;
    b = t;
}
template <class T>
inline int partition(T s[], int l, int r)
{
    T v = s[l];
    int j = l;
    for (int i = l + 1; i <= r; i++)
    {
        if (s[i] < v)
        {
            swap(s[++j], s[i]);
        }
    }
    swap(s[l], s[j]);
    return j;
}
template <class T>
inline void quickSort(T s[], int l, int r)
{
    if (l >= r)
        return;
    int p = partition(s, l, r);
    quickSort(s, l, p - 1);
    quickSort(s, p + 1, r);
}
template <class T>
inline void quick_sort(T s[], int n)
{
    quickSort(s, 0, n - 1);
}
template <class T>
inline void adjust(T s[], int i, int n)
{
    // i为待调整的节点，n为s数组元素的个数，从上往下调整
    int j = 2 * i + 1; // 左子节点
    while (j < n)
    {
        if (j + 1 < n && s[j + 1] > s[j])
            j++; // 比较左右孩子谁更大
        if (s[j] < s[i])
            break; // 都比父节点小就停止
        else
        {
            swap(s[i], s[j]);
            i = j; // 继续往下调整
            j = 2 * i + 1;
        }
    }
}
template <class T>
inline void heap_sort(T s[], int len)
{
    int n = len;
    for (int i = n / 2 - 1; i >= 0; i--)
    { // 从第一个非叶子节点开始（从下往上看第一个）
        adjust(s, i, n);
    }
    for (int i = n - 1; i >= 1; i--)
    {
        swap(s[0], s[i]); // 交换堆顶和最末一个元素
        adjust(s, 0, i);  // 将最末一个元素去除，再进行调整
    }
}
template <class T>
inline void bubble_sort(T s[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - 1 - i; j++)
        {
            if (s[j] > s[j + 1])
            {
                swap(s[j], s[j + 1]);
            }
        }
    }
}