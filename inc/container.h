#ifndef CONTAINER_H
#define CONTAINER_H


#include <cxxabi.h>
#include <memory>


/* Base class implementation */
template <typename T>
class ContainerBase
{
private:
    size_t m_size;

public:
    class IteratorBase 
    {
    public:
        virtual IteratorBase() = default;
        virtual ~IteratorBase() = default;
        virtual T& operator*() const = 0;
        virtual T& operator[](std::ptrdiff_t index) const = 0;
        virtual bool operator==(const IteratorBase& other) const = 0;
        virtual bool operator!=(const IteratorBase& other) const = 0;
        virtual IteratorBase& operator++() = 0;
        virtual IteratorBase operator++(int) = 0;
        virtual size_t getIndex() const = 0;
        virtual T& getValue() = 0;
        virtual const T& getValue() const = 0;

        virtual IteratorBase* clone() const = 0;  // For polymorphic copying
    };

    class IteratorConstBase 
    {
    public:
        virtual IteratorConstBase() = default;
        virtual ~IteratorConstBase() = default;
        virtual T& operator*() const = 0;
        virtual T& operator[](std::ptrdiff_t index) const = 0;
        virtual bool operator==(const IteratorConstBase& other) const = 0;
        virtual bool operator!=(const IteratorConstBase& other) const = 0;
        virtual size_t getIndex() const = 0;
        virtual T& getValue() = 0;
        virtual const T& getValue() const = 0;

        virtual IteratorConstBase* clone() const = 0;  // For polymorphic copying
    };
    
    virtual ContainerBase() = default;
    virtual ~ContainerBase() = default;
    virtual std::string getName() const;
    virtual bool operator==(const ContainerBase& other) const = 0;

    virtual IteratorBase begin() = 0;
    virtual IteratorBase end();
    virtual IteratorConstBase begin() const = 0;
    virtual IteratorConstBase end() const;
    virtual IteratorConstBase cbegin() const = 0;
    virtual IteratorConstBase cend() const;

    virtual size_t size() const;
    virtual T& operator[](const size_t& index) = 0;
    virtual const T& operator[](const size_t& index) const = 0;
    virtual T& operator[](IteratorBase& it) const = 0;
    virtual const T& operator[](IteratorConstBase& it) const = 0;
    virtual void push_back(const T& value) = 0;
    virtual void push_back(T&& value) = 0;
    virtual void insert(const size_t position, const T& value) = 0;
    virtual void insert(const size_t position, T&& value) = 0;
    virtual IteratorBase insert(IteratorBase& position, const T& value) = 0;
    virtual IteratorBase insert(IteratorBase& position, T&& value) = 0;
    virtual void erase(const size_t position) = 0;
    virtual IteratorBase erase(IteratorBase& position) = 0;
};


template <typename T>
std::string ContainerBase<T>::getName() const
{
    int status;
    char* pDemangled = abi::__cxa_demangle(typeid(*this).name(), 0, 0, &status);
    std::string result(pDemangled);
    free(pDemangled);
    return result;
}

template <typename T>
typename ContainerBase<T>::IteratorBase ContainerBase<T>::end()
{
    return IteratorBase(nullptr);
}

template <typename T>
typename ContainerBase<T>::IteratorConstBase ContainerBase<T>::end() const
{
    return IteratorConstBase(nullptr);
}

template <typename T>
typename ContainerBase<T>::IteratorConstBase ContainerBase<T>::cend() const
{
    return IteratorConstBase(nullptr);
}

template <typename T>
size_t ContainerBase<T>::size() const
{
    return m_size;
}


#endif // CONTAINER_H