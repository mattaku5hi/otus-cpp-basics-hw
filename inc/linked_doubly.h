#ifndef LINKED_DOUBLY_H
#define LINKED_DOUBLY_H


#include <cxxabi.h>
#include <memory>
#include <stdexcept>


template <typename T>
class ContainerListDoubly
{
private:
    struct Node
    {
        Node* pNext;
        Node* pPrev;
        T data;
        Node(Node* next, Node* prev, const T& value) :
            pNext(next), pPrev(prev), data(value) {}
    };
    size_t m_size;
    Node* m_pHead;
    Node* m_pTail;
    void copyFrom(const ContainerListDoubly& other);

public:
    ContainerListDoubly();
    ContainerListDoubly(const ContainerListDoubly& other); // copy ctor
    ContainerListDoubly(ContainerListDoubly&& other) noexcept; // move ctor
    ~ContainerListDoubly();
    ContainerListDoubly& operator=(const ContainerListDoubly& other); // copy assignment
    ContainerListDoubly& operator=(ContainerListDoubly&& other) noexcept; // move assignment
    bool operator==(const ContainerListDoubly& other) const;
    std::string getName() const;

    class Iterator
    {
    private:
        Node* m_pNode;
    public:
        Iterator(Node* p) : m_pNode(p) {};
        ~Iterator()=default;
        T& operator*() const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        Iterator& operator++();
        Iterator operator++(int);
        Node* getNode() const;
        void setNode(Node* p);
        T getValue() const;
    };

    class IteratorConst
    {
    private:
        const Node* m_pNode;
    public:
        IteratorConst(const Node* p) : m_pNode(p) {};
        ~IteratorConst()=default;
        T& operator*() const;
        bool operator==(const IteratorConst& other) const;
        bool operator!=(const IteratorConst& other) const;
        Node* getNode() const;
        T getValue() const;
    };

    size_t size() const;
    T& operator[](const size_t& index);
    const T& operator[](const size_t& index) const;
    T& operator[](IteratorConst& it);
    const T& operator[](IteratorConst& it) const;
    Iterator begin();
    Iterator end();
    IteratorConst begin() const;
    IteratorConst end() const;
    IteratorConst cbegin() const;
    IteratorConst cend() const;
    void push_back(const T& value);
    void push_back(T&& value);
    void insert(const size_t position, const T& value);
    void insert(const size_t position, T&& value);
    Iterator insert(Iterator& position, const T& value);
    Iterator insert(Iterator& position, T&& value);
    void erase(const size_t position);
    Iterator erase(Iterator& position);
    void clear();
};


template <typename T>
ContainerListDoubly<T>::ContainerListDoubly() :
    m_pHead(nullptr), m_pTail(nullptr), m_size(0)
{

}

template <typename T>
ContainerListDoubly<T>::ContainerListDoubly(const ContainerListDoubly& other)
    : m_size(0), m_pHead(nullptr), m_pTail(nullptr)
{
    copyFrom(other);
}

template <typename T>
ContainerListDoubly<T>::ContainerListDoubly(ContainerListDoubly&& other) noexcept
    : m_size(other.m_size), m_pHead(other.m_pHead), m_pTail(other.m_pTail)
{
    /* Clear incoming object as we implement move semantics */
    other.m_size = 0;
    other.m_pHead = nullptr;
    other.m_pTail = nullptr;
}

template <typename T>
ContainerListDoubly<T>::~ContainerListDoubly()
{
    clear();
}

template<typename T>
ContainerListDoubly<T>& ContainerListDoubly<T>::operator=(const ContainerListDoubly& other)
{
    if(this != &other)
    {
        clear();
        copyFrom(other);
    }
    return *this;
}

template<typename T>
ContainerListDoubly<T>& ContainerListDoubly<T>::operator=(ContainerListDoubly&& other) noexcept
{
    if(this != &other)
    {
        clear();
        
        /* Transfer ownership */
        m_pHead = other.m_pHead;
        m_pTail = other.m_pTail;
        m_size = other.m_size;
        
        /* Reset other object */
        other.m_pHead = nullptr;
        other.m_pTail = nullptr;
        other.m_size = 0;
    }

    return *this;  
}

template <typename T>
bool ContainerListDoubly<T>::operator==(const ContainerListDoubly& other) const
{
    if(m_size != other.m_size)
    {
        return false;
    }

    Node* pNodeThis = m_pHead;
    Node* pNodeOther = other.m_pHead;

    while(pNodeThis != nullptr)
    {
        if(pNodeThis->data != pNodeOther->data)
        {
            return false;

            pNodeThis = pNodeThis->pNext;
            pNodeOther = pNodeOther->pNext;
        }
    }

    /* yep, they are equal */
    return true;
}

template <typename T>
std::string ContainerListDoubly<T>::getName() const
{
    int status;
    char* pDemangled = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
    std::string result(pDemangled);
    free(pDemangled);
    return result;
}

template <typename T>
void ContainerListDoubly<T>::copyFrom(const ContainerListDoubly& other)
{
    Node* pNodeCurrent = other.m_pHead;
    Node* pNodePrev = nullptr;
    while(pNodeCurrent)
    {
        Node* pNodeNew = new Node(pNodeCurrent->data);
        if(m_pHead == nullptr)
        {
            m_pHead = pNodeNew;
        }
        else
        {
            pNodePrev->pNext = pNodeNew;
            pNodeNew->pPrev = pNodePrev;
        }
        pNodePrev = pNodeNew;
        pNodeCurrent = pNodeCurrent->pNext;
        ++m_size;
    }
    m_pTail = pNodePrev;
    return;
}

template <typename T>
size_t ContainerListDoubly<T>::size() const
{
    return m_size;
}

template <typename T>
T& ContainerListDoubly<T>::operator[](const size_t& index)
{
    if (index >= m_size)
    {
        throw std::out_of_range("Invalid position for member access");
    }
    Node* pNodeCurrent = m_pHead;
    for(size_t i = 0; i < index; ++i)
    {
        pNodeCurrent = pNodeCurrent->pNext;
    }
    return pNodeCurrent->data;   
}

template <typename T>
const T& ContainerListDoubly<T>::operator[](const size_t& index) const
{
    if (index >= m_size)
    {
        throw std::out_of_range("Invalid position for member access");
    }
    Node* pNodeCurrent = m_pHead;
    for(size_t i = 0; i < index; ++i)
    {
        pNodeCurrent = pNodeCurrent->pNext;
    }
    return pNodeCurrent->data;
}

template <typename T>
T& ContainerListDoubly<T>::operator[](IteratorConst& it)
{
    return *it;
}

template <typename T>
const T& ContainerListDoubly<T>::operator[](IteratorConst& it) const
{
    return *it;
}

template <typename T>
T& ContainerListDoubly<T>::Iterator::operator*() const
{
    return m_pNode->data;
}

template <typename T>
bool ContainerListDoubly<T>::Iterator::operator==(const Iterator& other) const
{
    return m_pNode == other.m_pNode;
}

template <typename T>
bool ContainerListDoubly<T>::Iterator::operator!=(const Iterator& other) const
{
    return !(*this == other);
}

/* Pre-increment operator */
template <typename T>
typename ContainerListDoubly<T>::Iterator& ContainerListDoubly<T>::Iterator::operator++()
{
    if(m_pNode != nullptr)
    {
        m_pNode = m_pNode->pNext;
    }
    return *this;
}

/* Post-increment operator */
template <typename T>
typename ContainerListDoubly<T>::Iterator ContainerListDoubly<T>::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp; 
}

template <typename T>
typename ContainerListDoubly<T>::Node* ContainerListDoubly<T>::Iterator::getNode() const
{
    return m_pNode;
}

template <typename T>
void ContainerListDoubly<T>::Iterator::setNode(Node* pNode)
{
    m_pNode = pNode;
    return;
}

template <typename T>
T ContainerListDoubly<T>::Iterator::getValue() const
{
    if(m_pNode != nullptr)
    {
        return m_pNode->data;
    }
    throw std::out_of_range("Iterator is out of range");
}

template <typename T>
T& ContainerListDoubly<T>::IteratorConst::operator*() const
{
    return m_pNode->data;
}

template <typename T>
bool ContainerListDoubly<T>::IteratorConst::operator==(const IteratorConst& other) const
{
    return m_pNode == other.m_pNode;
}

template <typename T>
bool ContainerListDoubly<T>::IteratorConst::operator!=(const IteratorConst& other) const
{
    return !(*this == other);
}

template <typename T>
typename ContainerListDoubly<T>::Node* ContainerListDoubly<T>::IteratorConst::getNode() const
{
    return m_pNode;
}

template <typename T>
T ContainerListDoubly<T>::IteratorConst::getValue() const
{
    if(m_pNode != nullptr)
    {
        return m_pNode->data;
    }
    throw std::out_of_range("Iterator is out of range");
}

template <typename T>
typename ContainerListDoubly<T>::Iterator ContainerListDoubly<T>::begin()
{
    return Iterator(m_pHead);
}

template <typename T>
typename ContainerListDoubly<T>::Iterator ContainerListDoubly<T>::end()
{
    return Iterator(nullptr);
}

template <typename T>
typename ContainerListDoubly<T>::IteratorConst ContainerListDoubly<T>::begin() const
{
    return IteratorConst(m_pHead);
}

template <typename T>
typename ContainerListDoubly<T>::IteratorConst ContainerListDoubly<T>::end() const
{
    return IteratorConst(nullptr);
}

template <typename T>
typename ContainerListDoubly<T>::IteratorConst ContainerListDoubly<T>::cbegin() const
{
    return IteratorConst(m_pHead);
}

template <typename T>
typename ContainerListDoubly<T>::IteratorConst ContainerListDoubly<T>::cend() const
{
    return IteratorConst(nullptr);
}

template <typename T>
void ContainerListDoubly<T>::push_back(const T& value)
{
    Node* pNewNode = new Node{value, nullptr, nullptr};

    if(m_size == 0)
    {
        m_pHead = pNewNode;
        m_pTail = pNewNode;

    }
    else
    {
        pNewNode->pPrev = m_pTail;
        m_pTail->pNext = pNewNode;
        m_pTail = pNewNode;
    }
    m_size++;

    return;
}

template <typename T>
void ContainerListDoubly<T>::push_back(T&& value)
{
    Node* pNewNode = new Node(nullptr, nullptr, std::move(value));

    if(m_size == 0)
    {
        m_pHead = pNewNode;
        m_pTail = pNewNode;

    }
    else
    {
        pNewNode->pPrev = m_pTail;
        m_pTail->pNext = pNewNode;
        m_pTail = pNewNode;
    }
    m_size++;

    return;
}

template <typename T>
void ContainerListDoubly<T>::insert(const size_t position, const T& value)
{
    if(position > m_size)
    {
        throw std::out_of_range("Invalid position for insertion");
    }

    Node* pNodeNew = new Node(nullptr, nullptr, value);

    if(position == 0)
    {
        pNodeNew->pNext = m_pHead;
        m_pHead = pNodeNew;
    } 
    else
    {
        Node* pNodeCurrent = m_pHead;
        for(size_t i = 0; i < position - 1; i++)
        {
            pNodeCurrent = pNodeCurrent->pNext;
        }
        pNodeNew->pNext = pNodeCurrent->pNext;
        pNodeCurrent->pNext = pNodeNew;
    }

    m_size++;
    return;
}

template <typename T>
void ContainerListDoubly<T>::insert(const size_t position, T&& value)
{
    if(position > m_size)
    {
        throw std::out_of_range("Invalid position for insertion");
    }

    Node* pNodeNew = new Node(nullptr, nullptr, std::move(value));

    if(position == 0)
    {
        pNodeNew->pNext = m_pHead;
        m_pHead = pNodeNew;
    } 
    else
    {
        Node* pNodeCurrent = m_pHead;
        for(size_t i = 0; i < position - 1; i++)
        {
            pNodeCurrent = pNodeCurrent->pNext;
        }
        pNodeNew->pNext = pNodeCurrent->pNext;
        pNodeCurrent->pNext = pNodeNew;
    }

    m_size++;
    return;
}

template <typename T>
typename ContainerListDoubly<T>::Iterator ContainerListDoubly<T>::insert(Iterator& position, const T& value)
{
    Node* pNodeNew = new Node(nullptr, nullptr, value);

    if(position.getNode() == nullptr)
    {
        // Inserting at the end
        if(m_pTail == nullptr)
        {
            m_pHead = m_pTail = pNodeNew;
        }
        else
        {
            pNodeNew->pPrev = m_pTail;
            m_pTail->pNext = pNodeNew;
            m_pTail = pNodeNew;
        }
    }
    else
    {
        Node* pNodeCurrent = position.getNode();
        pNodeNew->pNext = pNodeCurrent;
        pNodeNew->pPrev = pNodeCurrent->pPrev;

        if(pNodeCurrent->pPrev != nullptr)
        {
            pNodeCurrent->pPrev->pNext = pNodeNew;
        }
        else
        {
            m_pHead = pNodeNew;
        }
        pNodeCurrent->pPrev = pNodeNew;
    }

    m_size++;
    return Iterator(pNodeNew);
}

template <typename T>
typename ContainerListDoubly<T>::Iterator ContainerListDoubly<T>::insert(Iterator& position, T&& value)
{
    Node* pNodeNew = new Node(nullptr, nullptr, std::move(value));

    if(position.getNode() == nullptr)
    {
        // Inserting at the end
        if(m_pTail == nullptr)
        {
            m_pHead = m_pTail = pNodeNew;
        }
        else
        {
            pNodeNew->pPrev = m_pTail;
            m_pTail->pNext = pNodeNew;
            m_pTail = pNodeNew;
        }
    }
    else
    {
        Node* pNodeCurrent = position.getNode();
        pNodeNew->pNext = pNodeCurrent;
        pNodeNew->pPrev = pNodeCurrent->pPrev;

        if(pNodeCurrent->pPrev != nullptr)
        {
            pNodeCurrent->pPrev->pNext = pNodeNew;
        }
        else
        {
            m_pHead = pNodeNew;
        }
        pNodeCurrent->pPrev = pNodeNew;
    }

    m_size++;
    return Iterator(pNodeNew);
}

template <typename T>
void ContainerListDoubly<T>::erase(const size_t position)
{
    
    if(position >= m_size)
    {
        throw std::out_of_range("Invalid position for erasure");
    }

    Node* pNodeToDelete;

    if(position == 0)
    {
        pNodeToDelete = m_pHead;
        m_pHead = m_pHead->pNext;
    } 
    else
    {
        Node* pNodeCurrent = m_pHead;
        for(size_t i = 0; i < position - 1; ++i)
        {
            pNodeCurrent = pNodeCurrent->pNext;
        }
        pNodeToDelete = pNodeCurrent->pNext;
        pNodeToDelete->pNext->pPrev = pNodeToDelete->pPrev;
        pNodeToDelete->pPrev->pNext = pNodeToDelete->pNext;
    }

    delete pNodeToDelete;
    m_size--;
    return;
}

template <typename T>
typename ContainerListDoubly<T>::Iterator ContainerListDoubly<T>::erase(Iterator& position)
{
    if(position == end())
    {
        throw std::out_of_range("Can't erase Iterator: it's out of range");
    }

    Node* pNodeToDelete = position.getNode();
    Iterator nextPos(pNodeToDelete->pNext);

    if(position == begin())
    {
        m_pHead = m_pHead->pNext;
        delete pNodeToDelete;
        m_size--;

    } 
    else
    {
        Node* pNodePrev = m_pHead;
        while(pNodePrev != nullptr && pNodePrev->pNext != pNodeToDelete)
        {
            pNodePrev = pNodePrev->pNext;
        }

        if(pNodePrev != nullptr)
        {
            pNodeToDelete->pNext->pPrev = pNodePrev;
            pNodePrev->pNext = pNodeToDelete->pNext;
            delete pNodeToDelete;
            m_size--;
        }
    }
    
    return nextPos;
}

template <typename T>
void ContainerListDoubly<T>::clear()
{
    Node* pCurrent = m_pHead;
    while(pCurrent != nullptr)
    {
        Node* pNext = pCurrent->pNext;
        delete pCurrent;
        pCurrent = pNext;
    }
}


#endif // LINKED_DOUBLY_H
