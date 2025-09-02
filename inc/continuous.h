#ifndef CONTINUOUS_H
#define CONTINUOUS_H


#include <cxxabi.h>
#include <iterator>
#include <memory>
#include <typeinfo>


template <typename T>
class ContainerCont
{
private:
    size_t m_size{0};
    size_t m_capacity{0};
    T* m_pMem{nullptr};
    void reallocate(std::size_t capacity);
public:
    ContainerCont() = default;
    ContainerCont(const ContainerCont& other); // copy ctor
    ContainerCont(ContainerCont&& other) noexcept; // move ctor
    ~ContainerCont();
    ContainerCont& operator=(const ContainerCont& other); // copy assignment
    ContainerCont& operator=(ContainerCont&& other) noexcept; // move assignment
    std::string getName() const;

    class Iterator
    {
    private:
        T* m_pData;
        size_t m_index;
        ContainerCont* m_pContainer;
    public:
        Iterator(T* pData, size_t index, ContainerCont* pCont);
        T& operator*() const;
        Iterator& operator++();
        Iterator operator++(int);
        T& operator[](std::ptrdiff_t index) const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;
        size_t getIndex() const;
        T& getValue();
        const T& getValue() const;
        std::ptrdiff_t operator-(const Iterator& other) const;
    };

    class IteratorConst
    {
    private:
        const T* m_pData;
        size_t m_index;
        const ContainerCont* m_pContainer;
    public:
        IteratorConst(const T* pData, size_t index, const ContainerCont* pCont);
        const T& operator*() const;
        IteratorConst& operator++();
        IteratorConst operator++(int);
        const T& operator[](std::ptrdiff_t index) const;
        bool operator==(const IteratorConst& other) const;
        bool operator!=(const IteratorConst& other) const;
        size_t getIndex() const;
        const T& getValue() const;
    };

    Iterator begin();
    Iterator end();
    IteratorConst begin() const;
    IteratorConst end() const;
    IteratorConst cbegin() const;
    IteratorConst cend() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    size_t size() const;
    size_t capacity() const;
    void reserve(std::size_t capacity);
    void push_back(const T& value);
    void push_back(const T&& value);
    void insert(size_t index, const T& value);
    void insert(size_t index, T&& value); // move semantics
    Iterator insert(Iterator pos, const T& value);
    Iterator insert(Iterator pos, T&& value);
    Iterator erase(Iterator pos);
    void clear();
    void erase(size_t index);
};


template <typename T>
ContainerCont<T>::ContainerCont(const ContainerCont& other)
    : m_size(other.m_size), m_capacity(other.m_capacity)
{
    m_pMem = new T[m_capacity];
    for(std::size_t i = 0; i < m_size; i++)
    {
        m_pMem[i] = other.m_pMem[i];
    }
}

template <typename T>
ContainerCont<T>::ContainerCont(ContainerCont&& other) noexcept
    : m_size(other.m_size), m_capacity(other.m_capacity), m_pMem(other.m_pMem)
{
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_pMem = nullptr;
}

template <typename T>
ContainerCont<T>::~ContainerCont()
{
    this->clear();
}

template <typename T>
ContainerCont<T>& ContainerCont<T>::operator=(const ContainerCont& other)
{
    if(this != &other)
    {
        delete[] m_pMem;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_pMem = new T[m_capacity];
        for(std::size_t i = 0; i < m_size; i++)
        {
            m_pMem[i] = other.m_pMem[i];
        }
    }
    return *this;
}

template <typename T>
ContainerCont<T>& ContainerCont<T>::operator=(ContainerCont&& other) noexcept
{
    if(this != &other)
    {
        delete[] m_pMem;
        m_pMem = other.m_pMem;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        other.m_pMem = nullptr;
        other.m_capacity = 0;
        other.m_size = 0;
    }
    return *this;
}

template <typename T>
std::string ContainerCont<T>::getName() const
{
    int status;
    char* pDemangled = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
    std::string result(pDemangled);
    free(pDemangled);
    return result;
}

/* Private member functions */
template <typename T>
void ContainerCont<T>::reallocate(std::size_t capacity)
{
    size_t newCapacity = std::max(capacity, static_cast<size_t>(m_capacity * 1.5));
    if(newCapacity <= m_capacity) // ensure we always grow
    {
        newCapacity = m_capacity + 1;
    }
    T* newMem = new T[newCapacity];
    for (size_t i = 0; i < m_size; ++i)
    {
        newMem[i] = std::move(m_pMem[i]);
    }
    delete[] m_pMem;
    m_pMem = newMem;
    m_capacity = newCapacity;    
}

template <typename T>
ContainerCont<T>::Iterator::Iterator(T* pData, size_t index, ContainerCont* pCont) 
    : m_pData(pData), m_index(index), m_pContainer(pCont)
{

}

template <typename T>
T& ContainerCont<T>::Iterator::operator*() const
{
    return *(m_pData);
}

template <typename T>
T& ContainerCont<T>::Iterator::operator[](std::ptrdiff_t index) const
{
    return m_pData[index];
}

template <typename T>
typename ContainerCont<T>::Iterator& ContainerCont<T>::Iterator::operator++()
{
    ++m_pData;
    ++m_index;
    return *(this);
}

template <typename T>
typename ContainerCont<T>::Iterator ContainerCont<T>::Iterator::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
bool ContainerCont<T>::Iterator::operator==(const ContainerCont::Iterator& other) const
{
    return m_pData == other.m_pData;
}

template <typename T>
bool ContainerCont<T>::Iterator::operator!=(const ContainerCont::Iterator& other) const
{
    return m_pData != other.m_pData;
}

template<typename T>
std::ptrdiff_t ContainerCont<T>::Iterator::operator-(const ContainerCont<T>::Iterator& other) const
{
    return m_index - other.m_index;
}

template <typename T>
ContainerCont<T>::IteratorConst::IteratorConst(const T* pData, size_t index, const ContainerCont* pCont) 
    : m_pData(pData), m_index(index), m_pContainer(pCont)
{
}

template <typename T>
const T& ContainerCont<T>::IteratorConst::operator*() const
{
    return *(m_pData);
}

template <typename T>
const T& ContainerCont<T>::IteratorConst::operator[](std::ptrdiff_t index) const
{
    return m_pData[index];
}

template <typename T>
typename ContainerCont<T>::IteratorConst& ContainerCont<T>::IteratorConst::operator++()
{
    ++m_pData;
    ++m_index;
    return *(this);
}

template <typename T>
typename ContainerCont<T>::IteratorConst ContainerCont<T>::IteratorConst::operator++(int)
{
    Iterator temp = *this;
    ++(*this);
    return temp;
}

template <typename T>
bool ContainerCont<T>::IteratorConst::operator==(const ContainerCont::IteratorConst& other) const
{
    return m_pData == other.m_pData;
}

template <typename T>
bool ContainerCont<T>::IteratorConst::operator!=(const ContainerCont::IteratorConst& other) const
{
    return m_pData != other.m_pData;
}

template <typename T>
typename ContainerCont<T>::Iterator ContainerCont<T>::begin()
{
    return Iterator(m_pMem, 0, this);
}

template <typename T>
typename ContainerCont<T>::Iterator ContainerCont<T>::end()
{
    return Iterator(m_pMem + m_size, m_size, this);
}

template <typename T>
size_t ContainerCont<T>::Iterator::getIndex() const
{
    return m_index;
}

template <typename T>
T& ContainerCont<T>::Iterator::getValue()
{
    return *m_pData;
}

template <typename T>
const T& ContainerCont<T>::Iterator::getValue() const
{
    return *m_pData;
}

template <typename T>
typename ContainerCont<T>::IteratorConst ContainerCont<T>::begin() const
{
    return IteratorConst(m_pMem, 0, this);
}

template <typename T>
typename ContainerCont<T>::IteratorConst ContainerCont<T>::end() const
{
    return IteratorConst(m_pMem + m_size, m_size, this);
}

template <typename T>
typename ContainerCont<T>::IteratorConst ContainerCont<T>::cbegin() const
{
    return IteratorConst(m_pMem, 0, this);
}

template <typename T>
typename ContainerCont<T>::IteratorConst ContainerCont<T>::cend() const
{
    return IteratorConst(m_pMem + m_size, m_size, this);
}

template <typename T>
size_t ContainerCont<T>::IteratorConst::getIndex() const
{
    return m_index;
}

template <typename T>
const T& ContainerCont<T>::IteratorConst::getValue() const
{
    return *m_pData;
}

template <typename T>
T& ContainerCont<T>::operator[](size_t index)
{
    return m_pMem[index];
}

template <typename T>
const T& ContainerCont<T>::operator[](size_t index) const
{
    return m_pMem[index];
}

template <typename T>
size_t ContainerCont<T>::size() const
{
    return m_size;
}

template <typename T>
size_t ContainerCont<T>::capacity() const
{
    return m_capacity;
}

template <typename T>
void ContainerCont<T>::reserve(std::size_t capacity)
{
    if(capacity > m_capacity)
    {
        reallocate(capacity);
    }
}

template <typename T>
void ContainerCont<T>::push_back(const T& value)
{
    if(m_size >= m_capacity)
    {
        reallocate(m_capacity + 1);
    }
    m_pMem[m_size++] = value;

    return;
}

template <typename T>
void ContainerCont<T>::push_back(const T&& value)
{
    if(m_size == m_capacity)
    {
        reallocate(m_capacity + 1);
    }
    m_pMem[m_size++] = std::move(value);

    return;
}

template <typename T>
void ContainerCont<T>::insert(size_t index, const T& value)
{
    if(index > m_size)
    {
        throw std::out_of_range("Index out of range");
    }

    if(m_size == m_capacity)
    {
        reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
    }

    for(size_t i = m_size; i > index; --i)
    {
        m_pMem[i] = std::move(m_pMem[i - 1]);
    }
    m_pMem[index] = value;
    ++m_size;
    
    return;
}

template <typename T>
void ContainerCont<T>::insert(size_t index, T&& value)
{
    if(index > m_size)
    {
        throw std::out_of_range("Index out of range");
    }

    if(m_size == m_capacity)
    {
        reallocate(m_capacity == 0 ? 1 : m_capacity * 2);
    }

    for(size_t i = m_size; i > index; --i)
    {
        m_pMem[i] = std::move(m_pMem[i - 1]);
    }
    m_pMem[index] = std::move(value);
    ++m_size;

    return;
}

template <typename T>
typename ContainerCont<T>::Iterator ContainerCont<T>::insert(Iterator pos, const T& value)
{
    size_t index = pos.getIndex();
    
    if(index > m_size)
    {
        throw std::out_of_range("Invalid Iterator position");
    }

    if(m_size == m_capacity)
    {
        reserve(m_capacity == 0 ? 1 : m_capacity);
    }

    for(size_t i = m_size; i > index; --i)
    {
        m_pMem[i] = std::move(m_pMem[i-1]);
    }

    m_pMem[index] = value;
    ++m_size;
    
    return Iterator(&m_pMem[index], index, this);
}

template <typename T>
typename ContainerCont<T>::Iterator ContainerCont<T>::insert(Iterator pos, T&& value)
{
    size_t index = pos.getIndex();
    if(index > m_size)
    {
        throw std::out_of_range("Invalid Iterator position");
    }

    if(m_size == m_capacity)
    {
        reserve(m_capacity == 0 ? 1 : m_capacity);
    }

    for(size_t i = m_size; i > index; --i)
    {
        m_pMem[i] = std::move(m_pMem[i-1]);
    }

    m_pMem[index] = std::move(value);
    ++m_size;

    return Iterator(&m_pMem[index], index, this);
}

template <typename T>
typename ContainerCont<T>::Iterator ContainerCont<T>::erase(Iterator pos)
{
    if (pos == end())
    {
        return end();
    }

    size_t index = pos - begin();
    for (size_t i = index; i < m_size - 1; ++i)
    {
        m_pMem[i] = std::move(m_pMem[i + 1]);
    }

    /*
        Decrement size
    */
    --m_size;

    if(index < m_size)
    {
        return Iterator(&m_pMem[index], index, this);
    }
    else
    {
        return end();
    }
}

template <typename T>
void ContainerCont<T>::clear()
{
    if(m_pMem != nullptr)
    {
        delete[] m_pMem;
        m_pMem = nullptr;
    }
    m_size = 0;
    m_capacity = 0;
    
    return;
}

template <typename T>
void ContainerCont<T>::erase(size_t index)
{
    if(index >= m_size)
        throw std::out_of_range("Index out of range");
    
    Iterator it(&m_pMem[index], index, this);
    erase(it);
}


#endif // CONTINUOUS_H