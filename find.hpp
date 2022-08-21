#pragma once
template <class T>
inline int seq_find(T s[], T target, int len)
{
    if (len == 0)
        return -1;
    for (int i = 0; i < len; i++)
    {
        if (target == s[i])
        {
            return i;
        }
    }
    return -1;
}
template <class T>
inline int binarySearch(T s[], int target, int len)
{
    if (len == 0)
        return -1;

    int left = 0, right = len - 1;
    while (left + 1 < right)
    {
        int mid = left + (right - left) / 2;
        if (s[mid] == target)
        {
            return mid;
        }
        else if (s[mid] < target)
        {
            left = mid;
        }
        else
        {
            right = mid;
        }
    }
    if (s[left] == target)
        return left;
    if (s[right] == target)
        return right;
    return -1;
}