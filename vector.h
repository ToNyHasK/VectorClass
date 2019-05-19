#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
#include <cstring>
#include <utility>
#include <iterator>
#include <stdexcept>
#include <chrono>
#include <iostream>

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

    inline void reallocate();

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
    Vector() noexcept;//default
    explicit Vector(size_type sp);
    Vector(size_type s, const T &value);
    Vector(typename Vector<T>::iterator first, typename Vector<T>::iterator last);
    Vector(std::initializer_list<T>);
    Vector(const Vector<T> &);
    Vector(Vector<T> &&) noexcept;
    ~Vector() {delete[] elem;}//deconstruct
    //Iterators
    iterator begin() noexcept;
    const_iterator cbegin() const noexcept;
    iterator end()noexcept;
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
    ref operator[](size_type);//operator[]
    const_ref operator[](size_type) const;//operator[]
    ref at(size_type);
    const_ref at(size_type) const;
    ref front();
    const_ref front() const;
    ref back();
    const_ref back() const;
    T* data() noexcept;
    const T* data() const noexcept;
    //Capacity
    bool empty() const noexcept;
    size_type size() const noexcept {return sz;}
    size_type max_size() const noexcept;
    size_type capacity() const noexcept {return cap;}
    void reserve(size_type);
    void shrink_to_fit();
    //Modifiers
    void push_back(const T& v);
    void push_back(T&& v);
    void pop_back();
    void swap(Vector& other);
    void resize(size_type);
    void resize(size_type, const T&);
    template<class ...Args> void emplace_back(Args&& ... args);
    template<class ... Args> iterator emplace(const_iterator, Args && ...);
    iterator insert(const_iterator, const T &);
    iterator insert(const_iterator, T&&);
    iterator insert(const_iterator, size_type, const T&);
    template<class InputIt> iterator insert(const_iterator, InputIt, InputIt);
    iterator insert(const_iterator, std::initializer_list<T>);
    iterator erase(const_iterator);
    iterator erase(const_iterator, const_iterator);
    void clear() noexcept;
//Non-member functions
    bool operator==(const Vector<T>& v) const;//operator ==
    bool operator!=(const Vector<T>& v) const;//operator !=
    bool operator < (const Vector<T> &) const;
    bool operator <= (const Vector<T> &) const;
    bool operator > (const Vector<T> &) const;
    bool operator >= (const Vector<T> &) const;
};
template<typename T>
Vector<T>::Vector() noexcept {
    elem = new T[cap];
}
template<typename T>
Vector<T>::Vector(typename Vector<T>::size_type sp) {
    size_type i;
    cap = sp << 2;
    elem = new T[cap];
    for(i = 0; i < sp; ++i)
        elem[i] = T();
    sz = sp;
}
template<typename T>
Vector<T>::Vector(typename Vector<T>::size_type sp, const T &value) {
    size_type i;
    cap = sp << 2;
    elem = new T[cap];
    for (i = 0; i < sp; ++i)
        elem[i] = value;
    sz = sp;
}
template<typename T>
Vector<T>::Vector(typename Vector<T>::iterator first, typename Vector<T>::iterator last) {
    size_type i, count = last - first;
    cap = count << 2;
    elem = new T[cap];
    for (i = 0; i < count; ++i, ++first)
        elem[i] = *first;
    sz = count;
}
//Member type
    //iterators
template<typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept {
    return elem;
}
template<typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept {
    return elem;
}
template<typename T>
typename Vector<T>::iterator Vector<T>::end() noexcept {
    return elem + sz;
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
    //reallocation
template<typename T>
inline void Vector<T>::reallocate() {
    T *pT = new T[cap];
    memcpy(pT, elem, sz * sizeof(T));
    delete [] elem;
    elem = pT;
}
//Member functions
    //Constructors
template<typename T>
Vector<T>::Vector(std::initializer_list<T> il) {
    cap = il.size() << 2;
    elem = new T[cap];
    for(auto&new_i: il)
        elem[sz++] = new_i;
}

    //Operators
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& v) { //Move operator l-value
        size_type i;
        if (cap < v.vec_sz) {
            cap = v.sz << 2;
            reallocate();
        }
        for (i = 0; i < v.sz; ++i)
            elem[i] = v.elem[i];
        sz = v.sz;
}
template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T>&& v) noexcept {
    size_type i;
    if (cap < v.sz) {
        cap = v.sz << 2;
        reallocate();
    }
    for (i = 0; i < v.sz; ++i)
        elem[i] = std::move(v.elem[i]);
    sz = v.sz;
}
//Other stuff
template<typename T>
Vector<T>::Vector(const Vector<T>& v){
    size_type i;
    cap = v.cap;
    elem = new T[cap];
    for (i = 0; i < v.sz; ++i)
        elem[i] = v.elem[i];
    sz = v.sz;
}
template<typename T>
Vector<T>::Vector(Vector<T>&& v) noexcept {
    size_type i;
    cap = v.cap;
    elem = new T[cap];
    for (i = 0; i < v.sz; ++i)
        elem[i] = std::move(v.elem[i]);
    sz = v.sz;
}

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
typename Vector<T>::ref Vector<T>::operator[](typename Vector<T>::size_type i) {
    if (i < 0 || size() <= i) throw std::out_of_range {"Vector::operator[]"};
    return elem[i];
    }
template<typename T>
typename Vector<T>::const_ref Vector<T>::operator[](typename Vector<T>::size_type i) const {
    if (i < 0 || size() <= i) throw std::out_of_range {"Vector::operator[]"};
    return elem[i];
}
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
T& Vector<T>::back() {
    if(sz == 0)
        throw std::logic_error("Emty");
    return elem[sz - 1];
}
template<typename T>
const T& Vector<T>::back() const {
    if(sz == 0)
        throw std::logic_error("Emty");
    return elem[sz - 1];
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
void Vector<T>::reserve(typename Vector<T>::size_type size) {
    if (size > cap) {
        cap = size;
        reallocate();
    }
}
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
void Vector<T>::resize(typename Vector<T>::size_type size) {
    if(size > sz) {
        if (size > cap) {
            cap = size;
            reallocate();
        }
    }else {
        size_type i;
        for (i = sz; i < size; ++i)
            elem[i].~T();
    }
    sz = size;
}
template<typename T>
void Vector<T>::resize(typename Vector<T>::size_type size, const T &c) {
    if (size > sz) {
        if (size > cap) {
            cap = size;
            reallocate();
        }
        size_type i;
        for(i = sz; i < size; ++i)
            elem[i] = c;
    }else {
        size_type i;
        for (i = sz; i < size; ++i)
            elem[i].~T();
    }
    sz = size;
}
template<typename T>
void Vector<T>::push_back(const T& v) {
    if (sz == cap) {
        cap <<= 2;
    reallocate();
    }
    elem[sz] = v;
    ++sz;
}
template<typename T>
void Vector<T>::push_back(T &&val) {
    if (sz == cap) {
        cap <<= 2;
        reallocate();
    }
    elem[sz] = std::move(val);
    ++sz;
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
typename Vector<T>::iterator Vector<T>::erase(typename Vector<T>::const_iterator it) {
    iterator iit = &elem[it - elem];
    (*iit).~T();
    memmove(iit, iit + 1, (sz - (it - elem) - 1) * sizeof(T));
    --sz;
    return iit;
}
template<typename T>
typename Vector<T>::iterator Vector<T>::erase(typename Vector<T>::const_iterator first, typename Vector<T>::const_iterator last) {
    iterator f = &elem[first - elem];
    if (first == last) return f;
    for (; first != last; ++first)
        (*first).~T();
    memmove(f, last, (sz - (last - elem)) * sizeof(T));
    sz -= last - first;
    return f;
}
template<typename T>
void Vector<T>::clear() noexcept {
    size_type i;
    for (i = 0; i < sz; ++i)
        elem[i].~T();
    sz = 0;
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
