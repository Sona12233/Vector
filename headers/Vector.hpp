#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

#include <iostream>

template <typename T> class Vector;
template <typename T> std::ostream& operator<<(std::ostream& out, const Vector<T>& vector);

template <typename T>
class Vector
{
public:
    typedef T value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef value_type* pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;

    class const_iterator
    {
        friend class Vector<T>;
    public:
        const_iterator();
        const_iterator(const const_iterator& rhv);
        ~const_iterator();

        const const_iterator& operator=(const const_iterator& rhv);
        const_reference operator*() const;
        const value_type* operator->() const;
        const const_iterator& operator++();
        const const_iterator operator++(int);
        const const_iterator& operator--();
        const const_iterator operator--(int);
        const const_iterator& operator+=(const int rhv);
        const const_iterator& operator-=(const int rhv);
        const const_iterator& operator+(const int rhv);
        const const_iterator& operator-(const int rhv);
        difference_type operator-(const const_iterator& rhv) const;
        bool operator==(const const_iterator& rhv) const;
        bool operator!=(const const_iterator& rhv) const;
        bool operator<(const const_iterator& rhv) const;
        bool operator<=(const const_iterator& rhv) const;
        bool operator>(const const_iterator& rhv) const;
        bool operator>=(const const_iterator& rhv) const;
        const_reference operator[](const size_type size) const;

    protected:
        const_iterator(pointer rhv);
        pointer getPtr() const;
        pointer getPtr();
        void setPtr(const pointer ptr);

    private:
        pointer ptr_;
    };

    class iterator : public const_iterator
    {
        friend class Vector<T>;
    public:
        iterator();
        iterator(const iterator& rhv);
        ~iterator();
        difference_type operator-(iterator& rhv) const;
        reference operator*();
        iterator& operator++();
        iterator operator++(int);
        iterator& operator--();
        iterator operator--(int);
        iterator& operator+(const int rhv);
        iterator& operator-(const int rhv);
        const_reference operator->();
        reference operator[](const size_type size);
        iterator& operator=(const const_iterator& rhv);
        bool operator==(const iterator& rhv);
        bool operator!=(const iterator& rhv);
    protected:
        iterator(pointer rhv);
    };

    class const_reverse_iterator
    {
        friend class Vector<T>;
    public:
        const_reverse_iterator();
        const_reverse_iterator(const const_reverse_iterator& rhv);
        ~const_reverse_iterator();

        const const_reverse_iterator& operator=(const const_reverse_iterator& rhv);
        const_reference operator*() const;
        const value_type* operator->() const;
        const const_reverse_iterator& operator++();
        const const_reverse_iterator operator++(int);
        const const_reverse_iterator& operator--();
        const const_reverse_iterator operator--(int);
        const const_reverse_iterator& operator+=(const int rhv);
        const const_reverse_iterator& operator-=(const int rhv);
        const const_reverse_iterator& operator+(const int rhv);
        const const_reverse_iterator& operator-(const int rhv);
        bool operator==(const const_reverse_iterator& rhv);
        bool operator!=(const const_reverse_iterator& rhv);
        const_reference operator[](const size_type size) const;

    protected:
        const_reverse_iterator(pointer rhv);
        pointer getPtr() const;
        void setPtr(const pointer ptr);

    private:
        pointer ptr_;
    };

    class reverse_iterator : public const_reverse_iterator
    {
        friend class Vector<T>;
    public:
        reverse_iterator();
        reverse_iterator(const reverse_iterator& rhv);
        ~reverse_iterator();
        reference operator*();
        const_reference operator->();
        reference operator[](const size_type size);
        reverse_iterator& operator=(const const_reverse_iterator& rhv);
        bool operator==(const reverse_iterator& rhv);
        bool operator!=(const reverse_iterator& rhv);

    protected:
        reverse_iterator(pointer rhv);
    };

    Vector();
    Vector(const size_type size);
    Vector(const size_type n, const_reference t);
    Vector(const int n, const_reference t);
    template <typename InputIterator> Vector(InputIterator f, InputIterator l);
    ~Vector();
    size_type size() const;
    size_type max_size() const;
    void resize(const size_type n, const T& init = T());
    void push_back(const const_reference element);
    void pop_back();
    void clear();
    size_type capacity() const;
    void reserve(const size_type n);
    const_reference operator[](const size_type index) const ;
    bool operator==(const Vector<T>& rhv) const;
    bool operator!=(const Vector<T>& rhv) const;
    bool operator<(const Vector<T>& rhv) const;
    bool operator<=(const Vector<T>& rhv) const;
    bool operator>(const Vector<T>& rhv) const;
    bool operator>=(const Vector<T>& rhv) const;
    const_iterator begin() const;
    iterator begin();
    const_iterator end() const;
    iterator end();
    const_reverse_iterator rbegin() const;
    reverse_iterator rbegin();
    const_reverse_iterator rend() const;
    reverse_iterator rend();
    iterator insert(iterator pos, const_reference x);
    void insert(iterator pos, const size_type n, const_reference x);
    void insert(iterator pos, const int n, const_reference x);
    template <typename InputIterator>
    void insert(iterator pos, InputIterator f, InputIterator l);
    iterator erase(iterator pos);
    iterator erase(iterator f, iterator l);

private:
    T* begin_;
    T* end_;
    T* bufferEnd_;
};

#include "../templates/Vector.cpp"

#endif /// __VECTOR_HPP__
