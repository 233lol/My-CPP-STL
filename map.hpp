template <class K, class V>
class AVLNode
{
public:
    AVLNode(K key, V value)
    {
        this->key = key;
        this->value = value;
        height = 1;
        left = NULL;
        right = NULL;
    }

public:
    K key;
    V value;
    int height;
    AVLNode<K, V> *left;
    AVLNode<K, V> *right;
};

template <class K, class V>
class Map
{
public:
    Map()
    {
        root = NULL;
        m_size = 0;
    }
    int size()
    {
        return m_size;
    }
    bool empty()
    {
        return m_size == 0;
    }
    //增加操作
    void insert(K key, V value);
    //删除操作
    void remove(K key);
    //查找操作
    bool in(K key);
    V get(K key);
    V del(K key)
    {
        V res = get(key);
        remove(key);
        return res;
    }

private:
    AVLNode<K, V> *insert(AVLNode<K, V> *node, K key, V value);
    AVLNode<K, V> *remove(AVLNode<K, V> *node, K key);
    bool in(AVLNode<K, V> *node, K key);
    int getHeight(AVLNode<K, V> *node);
    int max(int a, int b) { return a > b ? a : b; }
    int getBalanceFactor(AVLNode<K, V> *node);
    AVLNode<K, V> *rightRotate(AVLNode<K, V> *node);
    AVLNode<K, V> *leftRotate(AVLNode<K, V> *node);

private:
    AVLNode<K, V> *root;
    int m_size;
};

template <class K, class V>
void Map<K, V>::insert(K key, V value)
{
    root = insert(root, key, value);
}
template <class K, class V>
AVLNode<K, V> *Map<K, V>::insert(AVLNode<K, V> *node, K key, V value)
{
    if (node == NULL)
    {
        m_size++;
        return new AVLNode<K, V>(key, value);
    }
    else if (key < node->key)
    {
        node->left = insert(node->left, key, value);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key, value);
    }
    else if (key == node->key)
    {
        node->value = value;
        return node;
    }
    //计算平衡因子
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    int balanceFactor = getBalanceFactor(node);
    //平衡维护
    if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
    {
        return rightRotate(node);
    }
    else if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
    {
        return leftRotate(node);
    }
    else if (balanceFactor > 1 && getBalanceFactor(node->left) < 0)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    else if (balanceFactor < -1 && getBalanceFactor(node->right) > 0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

template <class K, class V>
void Map<K, V>::remove(K key)
{
    root = remove(root, key);
}
template <class K, class V>
AVLNode<K, V> *Map<K, V>::remove(AVLNode<K, V> *node, K key)
{
    if (node == NULL)
    {
        return node;
    }
    AVLNode<K, V> *resNode = node;
    if (key < node->key)
    {
        node->left = remove(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = remove(node->right, key);
    }
    else if (key == node->key)
    {
        if (node->left == NULL)
        {
            AVLNode<K, V> *rightNode = node->right;
            delete node;
            m_size--;
            resNode = rightNode;
        }
        else if (node->right == NULL)
        {
            AVLNode<K, V> *leftNode = node->left;
            delete node;
            m_size--;
            resNode = leftNode;
        }
        else
        {
            AVLNode<K, V> *minNode = node->right;
            for (; minNode->left; minNode = minNode->left)
                ;
            minNode->right = remove(node->right, minNode->key);
            minNode->left = node->left;
            node->left = node->right = NULL;
            resNode = minNode;
        }
    }
    if (resNode == NULL)
    {
        return NULL;
    }
    //计算平衡因子
    resNode->height = max(getHeight(resNode->left), getHeight(resNode->right)) + 1;
    int balanceFactor = getBalanceFactor(resNode);
    //平衡维护
    if (balanceFactor > 1 && getBalanceFactor(resNode->left) >= 0)
    {
        return rightRotate(resNode);
    }
    else if (balanceFactor < -1 && getBalanceFactor(resNode->right) <= 0)
    {
        return leftRotate(resNode);
    }
    else if (balanceFactor > 1 && getBalanceFactor(resNode->left) < 0)
    {
        resNode->left = leftRotate(resNode->left);
        return rightRotate(resNode);
    }
    else if (balanceFactor < -1 && getBalanceFactor(resNode->right) > 0)
    {
        resNode->right = rightRotate(resNode->right);
        return leftRotate(resNode);
    }
    return resNode;
}

template <class K, class V>
bool Map<K, V>::in(K key)
{
    return in(root, key);
}
template <class K, class V>
bool Map<K, V>::in(AVLNode<K, V> *node, K key)
{
    if (node == NULL)
    {
        return false;
    }
    if (key == node->key)
    {
        return true;
    }
    else if (key < node->key)
    {
        return in(node->left, key);
    }
    else
    {
        return in(node->right, key);
    }
}
template <class K, class V>
V Map<K, V>::get(K key)
{
    AVLNode<K, V> *node = root;
    while (node != NULL)
    {
        if (key == node->key)
        {
            return node->value;
        }
        else if (key < node->key)
        {
            node = node->left;
        }
        else if (key > node->key)
        {
            node = node->right;
        }
    }
    return NULL;
}

template <class K, class V>
int Map<K, V>::getHeight(AVLNode<K, V> *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}
template <class K, class V>
int Map<K, V>::getBalanceFactor(AVLNode<K, V> *node)
{
    int lHeight = 0, rHeight = 0;
    if (node == NULL)
    {
        return 0;
    }
    if (node->left != NULL)
    {
        lHeight = node->left->height;
    }
    if (node->right != NULL)
    {
        rHeight = node->right->height;
    }
    return lHeight - rHeight;
}
template <class K, class V>
AVLNode<K, V> *Map<K, V>::rightRotate(AVLNode<K, V> *node)
{
    AVLNode<K, V> *res = node->left;
    AVLNode<K, V> *p = res->right;
    res->right = node;
    node->left = p;
    //维护平衡
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    res->height = max(getHeight(res->left), getHeight(res->right)) + 1;
    return res;
}
template <class K, class V>
AVLNode<K, V> *Map<K, V>::leftRotate(AVLNode<K, V> *node)
{
    AVLNode<K, V> *res = node->right;
    AVLNode<K, V> *p = res->left;
    res->left = node;
    node->right = p;
    //维护平衡
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    res->height = max(getHeight(res->left), getHeight(res->right)) + 1;
    return res;
}