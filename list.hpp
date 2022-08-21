#pragma once
template <class T>
struct node
{
	T date;
	node *pNext;
};

template <class T>
class List
{
public:
	List();
	List(const List<T> &List);
	List<T> &operator=(const List<T> &rhs);
	~List();
	T front() const;
	T back() const;
	void push_front(const T &date);			  //在头结点插入
	void push_back(const T &date);			  //在尾节点插入
	T pop_front();							  //删除头结点
	T pop_back();							  //删除尾节点
	int size() const;						  //返回链表长度
	bool empty() const;						  //判断是否为空
	T get_element(int n) const;				  //返回链表第n个节点值
	bool insert(int n, const T &data);		  //将元素插入在链表的第pos位置上
	bool del(int n);						  //删除第n个节点
	bool reset_element(int n, const T &date); //修改n位置的元素值为x
	int find(const T &date);				  //查找x第一次出现的位置，若没有，返回-1
	void sort();							  //对链表元素进行升序排序
	void destroy();							  //销毁链表，将链表成为空链表

private:
	node<T> *header;
	int length;
};
template <class T>
T List<T>::front() const
{
	get_element(0);
}
template <class T>
T List<T>::back() const
{
	get_element(length - 1);
}
template <class T>
List<T>::List() : header(NULL), length(0){};

template <class T>
List<T>::List(const List<T> &List) : header(NULL), length(0)
{
	int i = 0;
	while (i < List.size())
	{
		push_back(List.get_element(i));
		i++;
	}
}

template <class T>
List<T> &List<T>::operator=(const List<T> &rhs)
{
	if (this == &rhs)
	{
		return *this;
	}
	destroy();
	for (int i = 0; i < rhs.size(); i++)
	{
		push_back(rhs.get_element(i));
	}
	return *this;
}

template <class T>
List<T>::~List()
{
	destroy();
}

template <class T>
void List<T>::push_front(const T &date)
{
	node<T> *pnode = new node<T>;
	pnode->date = date;
	pnode->pNext = NULL;
	if (header == NULL)
	{
		header = pnode;
	}
	else
	{
		pnode->pNext = header;
		header = pnode;
	}
	length++;
}

template <class T>
void List<T>::push_back(const T &date)
{
	node<T> *pnode = new node<T>;
	pnode->date = date;
	pnode->pNext = NULL;
	if (header == NULL)
	{
		header = pnode;
	}
	else
	{
		node<T> *rear = header;
		while (rear->pNext != NULL)
		{
			rear = rear->pNext;
		}
		rear->pNext = pnode;
	}
	length++;
}
template <class T>
T List<T>::pop_back()
{
	T t = get_element(length - 1);
	del(length - 1);
	return t;
}
template <class T>
T List<T>::pop_front()
{
	T t = get_element(0);
	del(0);
	return t;
}
template <class T>
int List<T>::size() const
{
	return length;
}

template <class T>
bool List<T>::empty() const
{
	return header == NULL;
}

template <class T>
T List<T>::get_element(int n) const
{

	if (n < 0 || n > length - 1)
	{
		return header->date;
	}
	else
	{
		int i = 0;
		node<T> *ptemp = header;
		while (i++ < n)
		{
			ptemp = ptemp->pNext;
		}
		return ptemp->date;
	}
}

template <class T>
bool List<T>::insert(int n, const T &date)
{
	if (n < 0 || n > length - 1)
	{
		return false;
	}
	else
	{
		if (n == 0)
		{
			node<T> *ptemp = new node<T>;
			ptemp->date = date;
			ptemp->pNext = header;
			header = ptemp;
		}
		else
		{
			int i = 0;
			node<T> *ptemp = header;
			while (++i < n)
			{
				ptemp = ptemp->pNext;
			}
			node<T> *pinsert = new node<T>;
			pinsert->date = date;
			pinsert->pNext = ptemp->pNext;
			ptemp->pNext = pinsert;
		}
		length++;
	}
	return true;
}

template <class T>
bool List<T>::del(int n)
{
	if (n < 0 || n > length - 1)
	{
		return false;
	}
	else
	{
		node<T> *deleteElement;
		if (n == 0)
		{
			deleteElement = header;
			header = header->pNext;
		}
		else
		{
			int i = 0;
			node<T> *ptemp = header;
			while (++i < n)
			{
				ptemp = ptemp->pNext;
			}
			deleteElement = ptemp->pNext;
			ptemp->pNext = deleteElement->pNext;
		}
		delete deleteElement;
		length--;
	}
	return true;
}

template <class T>
bool List<T>::reset_element(int n, const T &date)
{
	if (n < 0 || n > length - 1)
	{
		return false;
	}
	else
	{
		if (n == 0)
		{
			header->date = date;
		}
		else
		{
			node<T> *ptemp = header;
			int i = 0;
			while (i++ < n)
			{
				ptemp = ptemp->pNext;
			}
			ptemp->date = date;
		}
	}
	return true;
}

template <class T>
int List<T>::find(const T &date)
{
	int i = 0;
	int re = -1;
	node<T> *ptemp = header;
	while (!ptemp)
	{
		if (ptemp->date == date)
		{
			re = i;
			break;
		}
		i++;
		ptemp = ptemp->pNext;
	}
	return re;
}

template <class T>
void List<T>::sort()
{
	if (length > 1)
	{
		for (int i = length - 1; i >= 0; --i)
		{
			for (int j = 0; j < i; j++)
			{
				T lift = get_element(j);
				T right = get_element(j + 1);
				if (lift > right)
				{
					reset_element(j, right);
					reset_element(j + 1, lift);
				}
			}
		}
	}
}

template <class T>
void List<T>::destroy()
{
	while (header != NULL)
	{
		node<T> *ptemp = header;
		header = header->pNext;
		delete ptemp;
	}
	length = 0;
}