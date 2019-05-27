#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <cstring>
#include <utility>
#include <iterator>
#include <stdexcept>
#include <chrono>
#include <iostream>
#include <cmath>

#define VECTOR_MAX_SIZE 1000000000

// paimta is https://github.com/objprog/paskaitos2019/wiki/Laiko-matavimas
//Timer class
class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
public:
    Timer() : start{std::chrono::high_resolution_clock::now()} {}
    void reset() {
        start = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const {
        return std::chrono::duration<double>
                (std::chrono::high_resolution_clock::now() - start).count();
    }
};
template<typename T>
class Vector {
private:
    unsigned int sz = 0;
    unsigned int cap = 4;
    T* elem;

    void reallocate(const unsigned int &szA, const unsigned int &capA) {
        sz = szA;
        cap = capA;
    }

public:
    //Member type
    typedef T value_type;
    typedef T& ref;
    typedef const T& const_ref;
    typedef T* ptr;
    typedef const T* const_ptr;
    typedef ptrdiff_t diff_type;
    typedef unsigned int size_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
//constructors
    //initializer
    Vector() : sz(0), cap(0), elem(new T[sz]) {};
    Vector(unsigned int size, T val) : sz(size), cap(size), elem(new T[size]) {std::fill_n(elem, sz, val);}
    Vector(std::initializer_list<T> list) : sz(list.size()), cap(list.size()), elem(new T[list.size()]) { std::copy(list.begin(), list.end(), elem);}
    explicit Vector(unsigned int sk) : sz(sk), cap(sk), elem(new T[sk]) {};
    Vector(const Vector<T>& v) : elem{new T[v.sz]}, sz{v.sz}, cap{v.cap} {
        std::copy(v.begin(), v.end(), (*this).begin());
    }
    Vector(Vector&& v) noexcept : sz{v.sz}, cap{v.cap}, elem{v.elem} {v.elem = nullptr; v.sz = 0; v.cap = 0;}
    ~Vector() {delete[] elem;}


    //Iterators
    const_iterator cbegin() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator crbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator crend() const noexcept;
//Member functions
    //Operators
    Vector& operator=(const Vector<T>& v);//move operator l-value
    Vector& operator=(Vector<T>&& v) noexcept;//move operator r-value
    //Other stuff
    void assign(size_type, const T& value);//assign
    void assign(typename Vector<T>::iterator, typename Vector<T>::iterator);
    void assign(std::initializer_list<T>);
    //Element access
    T& operator[](int i) {
        if (i < 0 || i >= sz)
            throw std::out_of_range {"vector::operator[]"};
        return elem[i];
    }
    ref at(size_type);
    const_ref at(size_type) const;
    ref front();
    const_ref front() const;
    T* data() noexcept;
    const T* data() const noexcept;
    //Capacity
    bool empty() const noexcept;
    size_type size() const noexcept {return sz;}
    size_type max_size() const noexcept;
    size_type capacity() const noexcept {return cap;}
    void shrink_to_fit();
    //Modifiers
    void push_back(const T& v);
    //void push_back(T&& v);
    void pop_back();
    void swap(Vector& other);
    template<class ...Args> void emplace_back(Args&& ... args);
    template<class ... Args> iterator emplace(const_iterator, Args && ...);
    iterator insert(const_iterator, const T &);
    iterator insert(const_iterator, T&&);
    iterator insert(const_iterator, size_type, const T&);
    template<class InputIt> iterator insert(const_iterator, InputIt, InputIt);
    iterator insert(const_iterator, std::initializer_list<T>);
    iterator erase(const_iterator);
    iterator erase(const_iterator, const_iterator);
//Non-member functions
    bool operator==(const Vector<T>& v) const;//operator ==
    bool operator!=(const Vector<T>& v) const;//operator !=
    bool operator < (const Vector<T> &) const;
    bool operator <= (const Vector<T> &) const;
    bool operator > (const Vector<T> &) const;
    bool operator >= (const Vector<T> &) const;

    T * begin() const {
        return &elem[0];
    };
    T back() const {
        return elem[sz-1];
    };
    T * end() const {
        return &elem[sz];
    };
    void clear() {
        delete[] elem;
        elem = new T[0];
        reallocate(0, 0);
    }
    void reserve(int n) {
        if (n > cap) {
            T* temp = elem;
            elem = new T[n];
            std::copy(&temp[0], &temp[sz], &elem[0]);
            reallocate(sz, n);
        }
    }
    void resize(unsigned int n) {
        T* temp;
        if(n < sz) {
            temp = new T[n];
            std::copy(&elem[0], &elem[n], &temp[0]);

            delete[] elem;
            elem = temp;
            reallocate(n, n);
        }
        if (n > sz) {
            if (n > cap) {
                reserve(n);
                std::fill(&elem[sz], &elem[n], 0);
                reallocate(n, n);
            }else {
                temp = elem;
                elem = new T[n];

                std::copy(&temp[0], &temp[sz], &elem[0]);
                std::fill(&elem[sz], &elem[n], 0);

                reallocate(n, cap);
            }
        }
    }
};
//Member type
    //iterators

template<typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept {
    return elem;
}
template<typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept {
    return elem + sz;
}
template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept {
    return reverse_iterator(elem + sz);
}
template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const noexcept {
    return reverse_iterator(elem + sz);
}
template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() noexcept {
    return reverse_iterator(elem);
}
template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crend() const noexcept {
    return reverse_iterator(elem);
}
//Member functions
    //Constructors

    //Operators
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) { //Move operator l-value
        if (&v == this) return *this;

        T* newElem = new T[v.sz];
        std::copy(v.begin(), v.end(), &newElem[0]);

        delete[] elem;
        elem = v.elem;
        sz = v.sz;
        cap = v.cap;
        return *this;
}
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v) noexcept {
   if (&v == this)
       return *this;
   delete[] elem;
   elem = v.elem;
   sz = v.sz;
   cap = v.cap;
   v.elem = nullptr;
   v.sz = 0;
   v.cap = 0;
   return *this;
}
//Other stuff
template<typename T>
void Vector<T>::assign(typename Vector<T>::size_type count, const T& value) {
    size_type i;
    if (count > cap) {
        cap = count << 2;
        reallocate();
    }
    for (i = 0; i < count; ++i)
        elem[i] = value;
    sz = count;
}
template<typename T>
void Vector<T>::assign(typename Vector<T>::iterator first, typename Vector<T>::iterator last) {
    size_type i, count = last - first;
    if (count > cap) {
        cap = count << 2;
        reallocate();
    }
    for (i = 0; i < count; ++i, ++first)
        elem[i] = *first;
    sz = count;
}
template<typename T>
void Vector<T>::assign(std::initializer_list<T> il) {
    size_type i, count = il.size();
    if (count > cap) {
        cap = count << 2;
        reallocate();
    }
    i = 0;
    for (auto &item: il)
        elem[i++] = item;
}

    //Element access
template<typename T>
T& Vector<T>::front() {
    if(sz > 0)
        return elem[0];
    else
        throw  std::logic_error("Emty container");
}
template<typename T>
const T& Vector<T>::front() const{
    if (sz > 0)
        return elem[0];
    else
        throw std::logic_error("Emty container");
}
template<typename T>
typename Vector<T>::ref Vector<T>::at(size_type pos) {
    if (pos < sz)
        return elem[pos];
    else
        throw std::out_of_range("accessed position is out of range");
}
template<typename T>
typename Vector<T>::const_ref Vector<T>::at(size_type pos) const {
    if (pos < sz)
        return elem[pos];
    else
        throw std::out_of_range("accessed position is out of range");
}
template<typename T>
T* Vector<T>::data() noexcept {
    return elem;
}
template<typename T>
const T* Vector<T>::data() const noexcept {
    return elem;
}
//Capacity

template<typename T>
bool Vector<T>::empty() const noexcept {
    return sz = 0;
}
template<typename T>
typename Vector<T>::size_type Vector<T>::max_size() const noexcept {
    return VECTOR_MAX_SIZE;
}
template<typename T>
void Vector<T>::shrink_to_fit() {
    cap = sz;
    reallocate();
}
//Modifiers
template<typename T>
void Vector<T>::push_back(const T& v) {
  if (sz+1 <= cap) {
      elem[sz] = v;
      sz++;
  }else{
      this->reserve(std::round(1+cap*1.5));
      elem[sz] = v;
      sz++;
  }
}
template<typename T>
void Vector<T>::pop_back() {
   --sz;
   elem[sz].~T();
}
template<typename T>
void Vector<T>::swap(Vector<T> &other) {
  size_t tsz = sz,
    tcap = cap;
  T *telem = elem;

  sz = other.sz;
  cap = other.cap;
  elem = other.elem;

  other.sz = tsz;
  other.cap = tcap;
  other.elem = telem;
}
template<typename T>
template<class ... Args>
void Vector<T>::emplace_back(Args &&... args) {
    if (sz == cap) {
        cap <<= 2;
        reallocate();
    }
    elem[sz] = std::move(T(std::forward<Args>(args) ... ));
    ++sz;
}
template<typename T>
template<class ... Args>
typename Vector<T>::iterator Vector<T>::emplace(typename Vector<T>::const_iterator it, Args && ... args) {
    iterator iit = &elem[it - elem];
    if(sz == cap) {
        cap <<= 2;
        reallocate();
    }
    memmove(iit + 1, iit, (sz - (it - elem)) * sizeof(T));
    (*iit) = std::move(T(std::forward<Args>(args) ... ) );
    ++sz;
    return iit;
}
template<typename T>
typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::const_iterator it, const T& val) {
    iterator iit = &elem[it - elem];
    if (sz == cap) {
        cap <<=2;
        reallocate();
    }
    memmove(iit + 1, iit, (sz - (it - elem)) * sizeof(T));
    (*iit) = val;
    ++sz;
    return iit;
}
template<typename T>
typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::const_iterator it, T &&val) {
    iterator iit = &elem[it - elem];
    if(sz == cap) {
        cap <<= 2;
        reallocate();
    }
    memmove(iit + 1, iit, (sz - (it - elem)) * sizeof(T));
    (*iit) = std::move(val);
    ++sz;
    return iit;
}
template<typename T>
typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::const_iterator it, typename Vector<T>::size_type cnt, const T &val) {
    iterator f = &elem[it - elem];
    if(!cnt) return f;
    if(sz + cnt > cap) {
        cap = (sz + cnt) << 2;
        reallocate();
    }
    memmove(f + cnt, f, (sz - (it - elem)) * sizeof(T));
    sz += cnt;
    for (iterator it = f; cnt--; ++it)
        (*it) = val;
    return f;
}
template<typename T>
template<class InputIt>
typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::const_iterator it, InputIt first, InputIt last) {
    iterator f = &elem[it - elem];
    size_type cnt = last - first;
    if (!cnt) return f;
    if (sz + cnt > cap) {
        cap = (sz + cnt) << 2;
        reallocate();
    }
    memmove(f + cnt, f, (sz - (it - elem)) * sizeof(T));
    for (iterator it = f; first != last; ++it, ++first)
        (*it) = *first;
    sz += cnt;
    return f;
}
template<typename T>
typename Vector<T>::iterator Vector<T>::insert(typename Vector<T>::const_iterator it, std::initializer_list<T> lst) {
    size_type cnt = lst.size();
    iterator f = &elem[it - elem];
    if (!cnt) return f;
    if (sz + cnt > cap) {
        cap = (sz + cnt) << 2;
        reallocate();
    }
    memmove(f + cnt, f, (sz - (it - elem)) * sizeof(T));
    iterator iit = f;
    for (auto &item: lst) {
        (*iit) = item;
        ++iit;
    }
    sz += cnt;
    return f;
}
template<typename T>
typename Vector<T>::iterator Vector<T>::erase(typename Vector<T>::const_iterator first, typename Vector<T>::const_iterator last) {
    if ((first < this->begin() || first >= this->end())
    || (last < this->begin() || last > this ->end()))
        throw std::out_of_range {"Vector::erase, possesion of invalid memory"};
    int tin = first - this->begin();
    int tist = last - first;
    T* temp = new T[cap];

    int newSz = 0;
    if (first != &elem[0]) {
        std::copy(&elem[0], first, &temp[0]);
        newSz += tin;
    }
    if (last != &elem[sz]) {
        std::copy(last, &elem[sz], &temp[newSz]);
        newSz += sz - tist - tin;
    }
    delete[] elem;
    elem = temp;
    reallocate(newSz, cap);
    return &elem[tin];
}
//Non-member functions
template<typename T>
bool Vector<T>::operator==(const Vector<T>& v) const { //operator ==
    if (sz != v.sz) return false;
    size_type i;
    for (i = 0; i < sz; ++i)
        if (elem[i] != v.elem[i])
            return false;
        return true;
}
template<typename T>
bool Vector<T>::operator!=(const Vector<T> &v) const {
    return !operator==(v);
}
template<typename T>
bool Vector<T>::operator<(const Vector<T> &v) const {
    size_type i, j, k = sz < v.sz ? sz : v.sz;
    for (i = 0; i < k; ++i)
        if(elem[i] != v.elem[i])
            return elem[i] < v.elem[i];
        return sz < v.sz;
}
template<typename T>
bool Vector<T>::operator<=(const Vector<T> &v) const {
    size_type i, j, k = sz < v.sz ? sz : v.sz;
    for (i = 0; i < k; ++i)
        if(elem[i] != v.elem[i])
            return elem[i] < v.elem[i];
        return sz <= v.sz;
}
template<typename T>
bool Vector<T>::operator>(const Vector<T> &v) const {
    size_type i, j, k = sz < v.sz ? sz : v.sz;
    for (i = 0; i < k; ++i)
        if(elem[i] != v.elem[i])
            return elem[i] > v.elem[i];
        return sz > v.sz;
}
template<typename T>
bool Vector<T>::operator>=(const Vector<T> &v) const {
    size_type i, j, k = sz < v.sz ? sz : v.sz;
    for (i = 0; i < k; ++i)
        if(elem[i] != v.elem[i])
            return elem[i] > v.elem[i];
        return sz >= v.sz;
}
#endif //VECTOR_H
