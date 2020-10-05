#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <concepts>

template <typename T>
concept RequiredInputIterator = std::input_iterator<T>;


template<typename T>
class Vector
{
    T*               values;
    std::size_t      v_size;
    std::size_t      v_capacity;
    bool             ctor_initialized = false;



public:
    using iterator =                   T*;
    using const_iterator =             const T*;
    using reference =                  T&;
    using const_reference =            const T&;
    using reverse_iterator =           std::reverse_iterator<iterator>;
    using const_reverse_iterator =     std::reverse_iterator<const_iterator>;
    using size_type =                  std::size_t;
    using difference_type =            std::ptrdiff_t;

    Vector();
    explicit Vector(size_type sz);
    Vector(size_type sz, const_reference v );
    Vector(const std::initializer_list<T>& i_list );
    Vector(const Vector&);
    Vector(Vector&&) noexcept;
    Vector<T>& operator=(Vector<T>) noexcept;
//    Vector<T>& operator=(Vector<T>&&) noexcept;
    ~Vector();

    template<RequiredInputIterator InputInterator>//, typename = required_input_iterator<InputInterator> >
    Vector(InputInterator first, InputInterator last);

    // element access
    const_reference              front() const;
    reference                    front();
    const_reference              back() const;
    reference                    back();
    reference                    operator[ ](size_type n);
    const_reference              operator[ ](size_type n) const;
    reference                    at(size_type n);
    const_reference              at(size_type n) const;
    constexpr T*                 data() noexcept;
    constexpr const_iterator     data() const noexcept;

    // iterators
    iterator                     begin() noexcept;
    const_iterator               begin() const noexcept;
    iterator                     end() noexcept;
    const_iterator               end() const noexcept;
    const_iterator               cbegin() const noexcept;
    const_iterator               cend() const;
    reverse_iterator             rbegin() noexcept;
    const_reverse_iterator       crbegin() const noexcept;
    reverse_iterator             rend() noexcept;
    const_reverse_iterator       crend() const noexcept;

    // Modifiers
    template<typename... ARGS>
    reference emplace_back(ARGS&&... args); // since C++17 the std::vector::emplace_back() function type is a reference reference, why is that? what does this change brings to the table?
    template<typename... ARGS>
    iterator emplace(const_iterator pos, ARGS&&... args);
    iterator insert(iterator pos, const_reference v );
    template<RequiredInputIterator InputInterator> iterator insert(iterator pos, InputInterator first, InputInterator last );
    iterator insert(const_iterator pos, const_reference v );
    iterator insert(const_iterator pos, reference& v );
    void insert(iterator pos, size_type n, const_reference v );
    iterator insert(const_iterator pos, size_type n, const_reference v );
    void push_back(const_reference v);
    void push_back(reference& v);
    void pop_back();
    iterator erase( const_iterator pos );
    iterator erase( iterator first, iterator last);
    void clear() noexcept;
    void resize(size_type n);
    void resize(size_type n, const_reference v);
    void swap(Vector& other ) noexcept;

    // capacity
    size_type size() const noexcept;
    size_type capacity() const noexcept;
    constexpr bool empty() const noexcept;
    void reserve(size_type n);
    void shrink_to_fit();

    // Non-Member Functions
    template<typename H> friend bool operator==(const Vector<H>& lhs, const Vector<H>& rhs);
    template<typename H> friend bool operator!=(const Vector<H>& lhs, const Vector<H>& rhs);

    // see https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
    friend void swap(Vector<T>& first, Vector<T>& second);

private:
    void reallocate();
};

template<typename T>
Vector<T>::Vector() : v_size(0), v_capacity(0), values(nullptr) { }

template<typename T>
Vector<T>::Vector(size_type sz) : v_size(0), v_capacity(sz),
    values(static_cast<T*>(::operator new (sizeof(T) * sz))) { }

template<typename T>
Vector<T>::Vector(size_type sz, const_reference v) : v_size(sz), v_capacity(sz),
    values(static_cast<T*>(::operator new (sizeof(T) * v_capacity))), ctor_initialized(true)
{
    std::fill(begin(), end(), v);
}

template<typename T>
Vector<T>::Vector(const std::initializer_list<T>& i_list) : v_size(i_list.size()), v_capacity(i_list.size()),
    values(static_cast<T*>(::operator new (sizeof(T) * v_capacity))), ctor_initialized(true)
{
    std::copy(i_list.begin(), i_list.end(), begin());
}

template<typename T>
template<RequiredInputIterator InputInterator>//, typename SFINAE >
Vector<T>::Vector(InputInterator first, InputInterator last) : v_size(last - first), v_capacity(v_size),
    values(static_cast<T*>(::operator new (sizeof(T) * v_size)))
{
    std::copy(first, last, begin());
}

template<typename T>
Vector<T>::Vector(const Vector<T>& src) : v_size(src.v_size), v_capacity(src.v_size),
    values(static_cast<T*>(::operator new (sizeof(T) * v_size)))
{
    std::copy(src.begin(), src.end(), begin());
}

template<typename T>
Vector<T>::~Vector()
{
    for(size_type i = 0; i < v_size; ++i)
        values[ v_size - 1 - i ].~T();
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> src) noexcept
{
    swap(*this, src);

    return *this;
}

template<typename T>
Vector<T>::Vector(Vector<T>&& mv) noexcept : Vector()
{
    swap(*this, mv);
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::back() const
{
    return values[v_size - 1];
}

template<typename T>
typename Vector<T>::reference Vector<T>::back()
{
    return values[v_size - 1];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::front() const
{
    return values[0];
}

template<typename T>
typename Vector<T>::reference Vector<T>::front()
{
    return values[0];
}

template<typename T>
typename Vector<T>::iterator Vector<T>::begin() noexcept
{
    return values;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::begin() const noexcept
{
    return values;
}

template<typename T>
typename Vector<T>::iterator  Vector<T>::end() noexcept
{
    return values + v_size;
}

template<typename T>
typename Vector<T>::const_iterator  Vector<T>::end() const noexcept
{
    return values + v_size;
}

template<typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept
{
    return values;
}

template<typename T>
typename Vector<T>::const_iterator  Vector<T>::cend() const
{
    return values + v_size;
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept
{
    return reverse_iterator(end());
}

template<typename T>
typename Vector<T>::reverse_iterator Vector<T>::rend() noexcept
{
    return reverse_iterator(begin());
}

template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crbegin() const noexcept
{
    return rbegin();
}

template<typename T>
typename Vector<T>::const_reverse_iterator Vector<T>::crend() const noexcept
{
    return rend();
}

template<typename T>
typename Vector<T>::reference Vector<T>::operator[ ] (size_type i)
{
    return values[ i ];
}

template<typename T>
typename Vector<T>::reference Vector<T>::at (size_type n)
{
    if(n >= v_size)
        throw std::out_of_range("out of range: n (which is " +
                                std::to_string(n) + ") >= this->size()(which is " + std::to_string(this->size()) + ")");

    return values[ n ];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::operator[ ] (size_type n) const
{
    return values[ n ];
}

template<typename T>
typename Vector<T>::const_reference Vector<T>::at (size_type n) const
{
    if(n >= v_size)
        throw std::out_of_range("out of range: n (which is " +
                                std::to_string(n) + ") >= this->size()(which is " + std::to_string(this->size()) + ")");

    return values[ n ];
}

template<typename T>
constexpr T* Vector<T>::data() noexcept
{
    return values;
}

template<typename T>
constexpr typename Vector<T>::const_iterator Vector<T>::data() const noexcept
{
    return values;
}

template<typename T>
template<typename... ARGS>
typename Vector<T>::reference Vector<T>::emplace_back(ARGS&&... args)
{
    if(v_size == v_capacity)
    {
        if(ctor_initialized)
            v_capacity *= 2;
        else
        {
            if (v_size == 0)
                v_capacity = 1;
            else if(v_size < 8)
                v_capacity++;
            else if (v_size >= 8)
                v_capacity *= 2;
        }

        reallocate();
    }

    return values[v_size++] = T(std::forward<ARGS>(args)...);
}

template<typename T>
template<typename... ARGS>
typename Vector<T>::iterator Vector<T>::emplace(const_iterator pos, ARGS&&... args)
{
    // I found a lot of examples implementing this function but they were confusing so I came up with this, is this ok?

    const difference_type dist = pos - begin();

    if(dist == v_capacity)
    {
        emplace_back(T(std::forward<T>(args)...));
    }
    else
    {
        if(v_size == v_capacity)
        {
            v_capacity *= 2;

            reallocate();
        }

        std::move_backward(begin() + dist, end(), end() + 1);

        iterator iter = &values[dist];

        *iter = std::move(T(std::forward<ARGS>(args)...));

        ++v_size;

        return iter;
    }
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, const_reference v )
{
    emplace(pos, v);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, const_reference v )
{
    emplace(pos, v);
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, reference& v )
{
    emplace(pos, std::forward<T>(v));
}

template<typename T>
void Vector<T>::insert(iterator pos, size_type n, const_reference v )
{
    const difference_type dist = pos - begin();

    if( (v_size + n) > v_capacity)
    {
        v_capacity += n;

        reallocate();
    }

    std::move_backward(begin() + dist, end(), end() + n);

    std::fill(begin() + dist, begin() + dist + n, v);

    v_size += n;
}

template<typename T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator pos, size_type n, const_reference v )
{
    const difference_type dist = pos - begin();

    if(v_size + n > v_capacity)
    {
        v_capacity += n;

        reallocate();
    }

    T* iter = &values[dist];

    std::move_backward(begin() + dist, end(), end() + n);

    std::fill(iter, iter + n, v);

    v_size += n;

    return &values[dist];
}


template<typename T>
template<RequiredInputIterator InputInterator>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, InputInterator first, InputInterator last)
{
    difference_type dist = last - first;
    difference_type ps = pos - begin();

    if(dist == 0)
        return &values[0];

    if(v_size + dist > v_capacity)
    {
        v_capacity += dist + dist + dist;

        reallocate();

        v_size += dist;
    }

    pos = &values[ps];

    std::move_backward(pos, pos + dist, end());

    std::copy(first, last, pos);

    return &values[ps];
}

template<typename T>
void Vector<T>::push_back(const_reference v)
{
    emplace_back(v);
}

template<typename T>
void Vector<T>::push_back(reference& v)
{
    emplace_back(std::move(v));
}

template<typename T>
void Vector<T>::pop_back()
{
    --v_size;

    // what if I use this below, what would be happening and what would be the difference??
    /*   values[--v_size].~T(); */
}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase( const_iterator pos )
{
    /* I cloud use other implementation of this function that is
      pretty shorter than this but I chose this one that I camne up with, is this ok? */

    /*The reason why I chose this is because when I triy erasing on empty Vector and it doesn't
     crash like the std::vector, instead it just doesn't do anything and neither does it crach
     when you pass an iterator that is out of range. Not sure if this is good or bad. Any insight? */

    const difference_type dist = pos - begin();

    if(v_size != 0)
        --v_size;

    int inc;

    for(inc = 2; v_size > pow(2, inc); ++inc);

    if(v_size == 0)
        v_capacity = 0;
    else
        v_capacity = pow(2, inc);

    if(v_capacity != 0)
    {
        T* temp = new T[v_capacity];

        for(size_type i = 0, j = 0; j <= v_size; ++j)
        {
            if(j != dist)
                temp[ i++ ] = values[ j ];
        }

        delete [ ] values;
        values = temp;
    }

    return &values[ dist ];
}

template<typename T>
typename Vector<T>::iterator Vector<T>::erase(  iterator first, iterator last )
{
    const difference_type n = last - first;

    std::move(last, end(), first);

    v_size -= n;
}

template<typename T>
void  Vector<T>::clear() noexcept
{
    v_size = 0;
}

template<typename T>
void Vector<T>::shrink_to_fit()
{
    v_capacity = v_size;
    reallocate();
}

template<typename T>
void Vector<T>::reserve(size_type n)
{
    if (n > v_capacity)
    {
        v_capacity = n;
        reallocate();
    }
}

template<typename T>
void Vector<T>::resize(size_type n)
{
    if(n > v_capacity)
    {
        ctor_initialized = true;

        v_capacity = n;
        reallocate();
    }

    v_size = n;
}

template<typename T>
void Vector<T>::resize(size_type n, const_reference v)
{
    if(n > v_capacity)
    {
        ctor_initialized = true;

        v_capacity = n;
        reallocate();
    }

    if(n > v_size)
    {
        std::fill(begin() + v_size, begin() + n, v);
    }

    v_size = n;
}

template<typename T>
void Vector<T>::swap(Vector& other) noexcept
{
    using std::swap;

    swap(values, other.values);
    swap(v_size, other.v_size);
    swap(v_capacity, other.v_capacity);
}

template<typename T>
typename Vector<T>::size_type  Vector<T>::size() const noexcept
{
    return v_size;
}

template<typename T>
typename Vector<T>::size_type  Vector<T>::capacity() const noexcept
{
    return v_capacity;
}

template<typename T>
constexpr bool  Vector<T>:: empty() const noexcept
{
    return begin() == end();
}

template<typename T>
void Vector<T>::reallocate()
{
    T* temp =  new T [v_capacity];

    std::copy(begin(), end(), temp);

    delete[ ] values;
    values = temp;
}

template<typename H>
bool operator==(const Vector<H>& lhs, const Vector<H>& rhs)
{
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename H>
bool operator!=(const Vector<H>& lhs, const Vector<H>& rhs)
{
    return !(lhs == rhs);
}

template<typename T>
void swap(Vector<T>& first, Vector<T>& second)
{
    using std::swap;

    swap(first.v_size, second.v_size);
    swap(first.v_capacity, second.v_capacity);
    swap(first.values, second.values);
}

#endif // VECTOR_H_INCLUDED
