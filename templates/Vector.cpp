#ifndef __VECTOR_CPP__
#define __VECTOR_CPP__

#include "../headers/Vector.hpp"

#include <cassert>
#include <limits>
#include <cmath>
#include <cstring>

const double RESERVE_COEFF = 2;

template <typename T>
std::ostream&
operator<<(std::ostream& out, const Vector<T>& vector)
{
    for (size_t i = 0; i < vector.size(); ++i) {
        out << vector[i] << " ";
    }
    return out;
}

template <typename T>
Vector<T>::Vector()
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{}

template <typename T>
Vector<T>::Vector(const size_type size)
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{
    resize(size);
}

template <typename T>
Vector<T>::Vector(const size_type n, const_reference t)
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{
    resize(n, t);
}

template <typename T>
Vector<T>::Vector(const int n, const_reference t)
        : begin_(NULL)
        , end_(NULL)
        , bufferEnd_(NULL)
{
    resize(n, t);
}

template <typename T>
template <typename InputIterator>
Vector<T>::Vector(InputIterator f, InputIterator l)
    : begin_(NULL)
    , end_(NULL)
    , bufferEnd_(NULL)
{
    while (f != l) {
        push_back(*(f));
        ++f;
    }
}

template <typename T>
Vector<T>::~Vector()
{
    if (begin_ != NULL) {
        for (size_type i = 1 ; i < size(); ++i) {
            (end_ - i)->~T();
        }
        ::operator delete[](begin_);
        begin_ = NULL;
        end_ = NULL;
        bufferEnd_ = NULL;
    }
}

template <typename T>
typename Vector<T>::size_type
Vector<T>::size() const
{
    return end_ - begin_;
}

template <typename T>
typename Vector<T>::size_type
Vector<T>::max_size() const
{
    return std::numeric_limits<size_type>::max();
}

template <typename T>
void
Vector<T>::resize(const Vector::size_type n, const T& init)
{
    if (n > capacity()) {
        reserve(n);
    }
    const size_type oldSize = size();
    for (size_type i = n; i < oldSize; ++i) {
        (end_--)->~T();
    }

    end_ = begin_ + n;
    for (size_type i = oldSize; i < n; ++i) {
        new (begin_ + i) T(init);
    }
}

template <typename T>
void
Vector<T>::push_back(const_reference element)
{
    const size_type oldCapacity = capacity();
    const size_type oldSize = size();
    if (oldSize == oldCapacity) {
        reserve((0 == oldCapacity) ? 1 : std::ceil(RESERVE_COEFF * capacity()));
    }
    *(end_++) = element;
}

template <typename T>
void
Vector<T>::pop_back()
{
    (end_--)->~T();
}

template <typename T>
void
Vector<T>::clear()
{
    for (size_type i = 1 ; i < size(); ++i) {
        (end_ - i)->~T();
    }
    end_ = begin_;
}

template <typename T>
typename Vector<T>::size_type
Vector<T>::capacity() const
{
    return bufferEnd_ - begin_;
}

template <typename T>
void
Vector<T>::reserve(const Vector::size_type n)
{
    if (n <= capacity()) {
        return;
    }
    T* temp = reinterpret_cast<T*>(::operator new[](n * sizeof(T)));
    ::memcpy(reinterpret_cast<void*>(temp), reinterpret_cast<void*>(begin_), sizeof(T) * size());
    size_type sizeTemp = size();

    if (begin_ != NULL) {
        delete[] begin_;
        begin_ = NULL;
    }
    begin_ = temp;
    end_ = begin_ + sizeTemp;
    bufferEnd_ = begin_ + n;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::operator[](const typename Vector<T>::size_type index) const
{
    //assert(index < size() && begin_ != NULL);
    return begin_[index];
}

template <typename T>
bool
Vector<T>::operator==(const Vector<T>& rhv) const
{
    if (size() != rhv.size()) {
        return false;
    }
    for (size_type i = 0; i < size(); ++i) {
        if (this->operator[](i) != rhv[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool
Vector<T>::operator!=(const Vector<T>& rhv) const
{
    return !(this->operator==(rhv));
}

template <typename T>
bool
Vector<T>::operator<(const Vector<T>& rhv) const
{
    if (this->operator==(rhv)) return false;
    if (this->size() > rhv.size()) return false;
    if (this->size() < rhv.size()) return true;
    for (size_type i = 0; i < size(); ++i) {
        if (begin_[i] > rhv.begin_[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
bool
Vector<T>::operator<=(const Vector<T>& rhv) const
{
    return !(rhv < *this);
}

template <typename T>
bool
Vector<T>::operator>(const Vector<T>& rhv) const
{
    return rhv < *this;
}

template <typename T>
bool
Vector<T>::operator>=(const Vector<T>& rhv) const
{
    return !(*this < rhv);
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::begin() const
{
    return const_iterator(begin_);
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::begin()
{
    return iterator(begin_);
}

template <typename T>
typename Vector<T>::const_iterator
Vector<T>::end() const
{
    return const_iterator(end_);
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::end()
{
    return iterator(end_);
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::rbegin() const
{
    return const_reverse_iterator(end_ - 1);
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::rbegin()
{
    return reverse_iterator(end_ - 1);
}

template <typename T>
typename Vector<T>::const_reverse_iterator
Vector<T>::rend() const
{
    return const_reverse_iterator(begin_ - 1);
}

template <typename T>
typename Vector<T>::reverse_iterator
Vector<T>::rend()
{
    return reverse_iterator(begin_ - 1);
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::insert(iterator pos, const_reference x)
{
    assert(pos >= begin_ && pos < end_);
    const size_type index = pos.getPtr() - begin_;
    resize(size() + 1);

    for (size_type i = size() - 1; i > index; --i) {
        begin_[i] = begin_[i - 1];
    }
    *(begin_ + index) = x;
    return begin_ + index;
}

template <typename T>
void
Vector<T>::insert(iterator pos, const size_type n, const_reference x)
{
    //assert(pos >= begin_ && pos + n < end_);
    const size_type index = pos - begin_;
    resize(size() + n);

    for (size_type i = size() - 1; i > index; --i) {
        begin_[i] = begin_[i - n];
    }
    for (size_type i = 0; i < n; ++i) {
        *(begin_ + index + i) = x;
    }
}

template <typename T>
void
Vector<T>::insert(iterator pos, const int n, const_reference x)
{
//    assert(pos >= begin_ && pos + n < end_);
    size_type index = pos.getPtr() - begin_;
    resize(size() + n);

    for (size_type i = size() - 1; i > index; --i) {
        begin_[i] = begin_[i - n];
    }
    for (int i = 0; i < n; ++i) {
        *(begin_ + index + i) = x;
    }
}

template <typename T>
template <typename InputIterator>
void
Vector<T>::insert(iterator pos, InputIterator f, InputIterator l)
{
    while (f != l) {
        pos = insert(pos, *(f));
        ++f;
        ++pos;
    }
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::erase(iterator pos)
{
    size_type index = pos.getPtr() - begin_;
    for (size_type i = index; i < size() - 1; ++i) {
        begin_[i] = begin_[i + 1];
    }
    resize(size() - 1);
    return pos;
}

template<typename T>
typename Vector<T>::iterator
Vector<T>::erase(iterator f, iterator l)
{
    const size_type distance = l - f;
    const size_type index = end_ - l.getPtr() - 1;
    const size_type tempSize = size();
    for (size_type i = tempSize - index - 1; i < tempSize; ++i) {
        begin_[i - distance] = begin_[i];
    }
    resize(tempSize - distance);
    return l;
}

template <typename T>
Vector<T>::const_iterator::const_iterator()
    : ptr_(NULL)
{
}

template <typename T>
Vector<T>::const_iterator::const_iterator(const const_iterator& rhv)
    : ptr_(rhv.ptr_)
{
}

template <typename T>
Vector<T>::const_iterator::const_iterator(pointer rhv)
    : ptr_(rhv)
{}

template <typename T>
Vector<T>::const_iterator::~const_iterator()
{
    if (ptr_ != NULL) {
        ptr_ = NULL;
    }
}

template <typename T>
typename Vector<T>::pointer
Vector<T>::const_iterator::getPtr() const
{
    return ptr_;
}

template <typename T>
typename Vector<T>::pointer
Vector<T>::const_iterator::getPtr()
{
    return ptr_;
}

template <typename T>
void
Vector<T>::const_iterator::setPtr(const pointer ptr)
{
    if (NULL == ptr) return;
    ptr_ = ptr;
}

template <typename T>
const typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator=(const const_iterator& rhv)
{
    ptr_ = rhv.ptr_;
    return *this;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::const_iterator::operator*() const
{
    return *ptr_;
}

template <typename T>
const typename Vector<T>::value_type*
Vector<T>::const_iterator::operator->() const
{
    return ptr_;
}

template <typename T>
const typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator++()
{
    ++ptr_;
    return *this;
}

template <typename T>
const typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator++(int)
{
    const_iterator temp = *this;
    ++ptr_;
    return temp;
}

template <typename T>
const typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator--()
{
    --ptr_;
    return *this;
}

template <typename T>
const typename Vector<T>::const_iterator
Vector<T>::const_iterator::operator--(int)
{
    const_iterator temp = *this;
    --ptr_;
    return temp;
}

template <typename T>
const typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator+=(const int rhv)
{
    ptr_ += rhv;
    return *this;
}

template <typename T>
const typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator-=(const int rhv)
{
    ptr_ -= rhv;
    return *this;
}

template <typename T>
const typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator+(const int rhv)
{
    ptr_ = ptr_ + rhv;
    return *this;
}

template <typename T>
const typename Vector<T>::const_iterator&
Vector<T>::const_iterator::operator-(const int rhv)
{
    ptr_ = ptr_ - rhv;
    return *this;
}

template <typename T>
typename Vector<T>::difference_type
Vector<T>::const_iterator::operator-(const const_iterator& rhv) const
{
    return ptr_ - rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_iterator::operator==(const Vector::const_iterator& rhv) const
{
    return getPtr() == rhv.getPtr();
}

template <typename T>
bool
Vector<T>::const_iterator::operator!=(const Vector::const_iterator& rhv) const
{
    return !(*this == rhv);
}

template <typename T>
bool
Vector<T>::const_iterator::operator<(const Vector::const_iterator& rhv) const
{
    return ptr_ < rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_iterator::operator<=(const Vector::const_iterator& rhv) const
{
    return ptr_ <= rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_iterator::operator>(const Vector::const_iterator& rhv) const
{
    return ptr_ > rhv.ptr_;
}

template <typename T>
bool
Vector<T>::const_iterator::operator>=(const Vector::const_iterator& rhv) const
{
    return ptr_ >= rhv.ptr_;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::const_iterator::operator[](const size_type size) const
{
    return *(ptr_ + size);
}

template <typename T>
Vector<T>::iterator::iterator()
        : const_iterator()
{
}

template <typename T>
Vector<T>::iterator::iterator(const iterator& rhv)
    : const_iterator(rhv)
{
}

template <typename T>
Vector<T>::iterator::iterator(pointer rhv)
    : const_iterator(rhv)
{
}

template <typename T>
Vector<T>::iterator::~iterator()
{
}

template<typename T>
typename Vector<T>::difference_type
Vector<T>::iterator::operator-(iterator& rhv) const
{
    return const_iterator::getPtr() - rhv.getPtr();
}

template <typename T>
typename Vector<T>::reference
Vector<T>::iterator::operator*()
{
    return *(::Vector<T>::const_iterator::getPtr());
}

template <typename T>
typename Vector<T>::iterator&
Vector<T>::iterator::operator++()
{
    pointer ptr = const_iterator::getPtr();
    ++ptr;
    const_iterator::setPtr(ptr);
    return *this;
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::iterator::operator++(int)
{
    iterator temp = *this;
    pointer ptr = const_iterator::getPtr();
    ++ptr;
    const_iterator::setPtr(ptr);
    return temp;
}

template <typename T>
typename Vector<T>::iterator&
Vector<T>::iterator::operator--()
{
    pointer ptr = const_iterator::getPtr();
    --ptr;
    const_iterator::setPtr(ptr);
    return *this;
}

template <typename T>
typename Vector<T>::iterator
Vector<T>::iterator::operator--(int)
{
    iterator temp = *this;
    pointer ptr = const_iterator::getPtr();
    --ptr;
    const_iterator::setPtr(ptr);
    return temp;
}

template <typename T>
typename Vector<T>::iterator&
Vector<T>::iterator::operator+(const int rhv)
{
    const_iterator::setPtr(const_iterator::getPtr() + rhv);
    return *this;
}

template <typename T>
typename Vector<T>::iterator&
Vector<T>::iterator::operator-(const int rhv)
{
    const_iterator::setPtr(const_iterator::getPtr() - rhv);
    return *this;
}


template <typename T>
typename Vector<T>::const_reference
Vector<T>::iterator::operator->()
{
    return const_iterator::getPtr();
}

template <typename T>
typename Vector<T>::reference
Vector<T>::iterator::operator[](const size_type size)
{
    return *(const_iterator::getPtr() + size);
}

template <typename T>
typename Vector<T>::iterator&
Vector<T>::iterator::operator=(const const_iterator& rhv)
{
    const_iterator::setPtr(rhv.getPtr());
    return *this;
}

template <typename T>
bool
Vector<T>::iterator::operator==(const Vector::iterator& rhv)
{
    return const_iterator::getPtr() == rhv.getPtr();
}

template <typename T>
bool
Vector<T>::iterator::operator!=(const Vector::iterator& rhv)
{
    return !(*this == rhv);
}

template <typename T>
Vector<T>::const_reverse_iterator::const_reverse_iterator()
    :ptr_(NULL)
{}

template <typename T>
Vector<T>::const_reverse_iterator::const_reverse_iterator(const Vector::const_reverse_iterator&rhv)
{
    ptr_ = rhv.ptr_;
}

template <typename T>
Vector<T>::const_reverse_iterator::const_reverse_iterator(pointer rhv)
    : ptr_(rhv)
{}

template <typename T>
Vector<T>::const_reverse_iterator::~const_reverse_iterator()
{
    if (ptr_ != NULL) {
        ptr_ = NULL;
    }
}

template <typename T>
typename Vector<T>::pointer
Vector<T>::const_reverse_iterator::getPtr() const
{
    return ptr_;
}

template <typename T>
void
Vector<T>::const_reverse_iterator::setPtr(const typename Vector<T>::pointer ptr)
{
    if (ptr == NULL) return;
    ptr_ = ptr;
}

template <typename T>
const typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator=(const const_reverse_iterator& rhv)
{
    ptr_ = rhv.ptr_;
    return *this;
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::const_reverse_iterator::operator*() const
{
    return *ptr_;
}

template <typename T>
const typename Vector<T>::value_type*
Vector<T>::const_reverse_iterator::operator->() const
{
    return ptr_;
}

template <typename T>
const typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator++()
{
    --ptr_;
    return *this;
}

template <typename T>
const typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator++(int)
{
    const_reverse_iterator temp = *this;
    --ptr_;
    return temp;
}

template <typename T>
const typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator--()
{
    ++ptr_;
    return *this;
}

template <typename T>
const typename Vector<T>::const_reverse_iterator
Vector<T>::const_reverse_iterator::operator--(int)
{
    const_reverse_iterator temp = *this;
    ++ptr_;
    return temp;
}

template <typename T>
const typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator+=(const int rhv)
{
    ptr_ -= rhv;
    return *this;
}

template <typename T>
const typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator-=(const int rhv)
{
    ptr_ += rhv;
    return *this;
}

template <typename T>
const typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator+(const int rhv)
{
    ptr_ = ptr_ - rhv;
    return *this;
}

template <typename T>
const typename Vector<T>::const_reverse_iterator&
Vector<T>::const_reverse_iterator::operator-(const int rhv)
{
    ptr_ = ptr_ + rhv;
    return *this;
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator==(const Vector::const_reverse_iterator& rhv)
{
    return getPtr() == rhv.getPtr();
}

template <typename T>
bool
Vector<T>::const_reverse_iterator::operator!=(const Vector::const_reverse_iterator& rhv)
{
    return !(*this == rhv);
}


template <typename T>
typename Vector<T>::const_reference
Vector<T>::const_reverse_iterator::operator[](const size_type size) const
{
    return *(ptr_ + size);
}

template <typename T>
Vector<T>::reverse_iterator::reverse_iterator()
    : const_reverse_iterator()
{}

template <typename T>
Vector<T>::reverse_iterator::reverse_iterator(const reverse_iterator& rhv)
    : const_reverse_iterator(rhv)
{}

template <typename T>
Vector<T>::reverse_iterator::reverse_iterator(pointer rhv)
    : const_reverse_iterator(rhv)
{}

template <typename T>
Vector<T>::reverse_iterator::~reverse_iterator()
{}

template <typename T>
typename Vector<T>::reference
Vector<T>::reverse_iterator::operator*()
{
    return *(::Vector<T>::const_reverse_iterator::getPtr());
}

template <typename T>
typename Vector<T>::const_reference
Vector<T>::reverse_iterator::operator->()
{
    return const_reverse_iterator::getPtr();
}

template <typename T>
typename Vector<T>::reference
Vector<T>::reverse_iterator::operator[](const size_type size)
{
    return *(const_reverse_iterator::getPtr() + size);
}

template <typename T>
typename Vector<T>::reverse_iterator&
Vector<T>::reverse_iterator::operator=(const const_reverse_iterator& rhv)
{
    const_reverse_iterator::setPtr(rhv.getPtr());
    return *this;
}

template <typename T>
bool
Vector<T>::reverse_iterator::operator==(const Vector::reverse_iterator& rhv)
{
    return const_reverse_iterator::getPtr() == rhv.getPtr();
}

template <typename T>
bool
Vector<T>::reverse_iterator::operator!=(const Vector::reverse_iterator& rhv)
{
    return !(*this == rhv);
}

#endif
