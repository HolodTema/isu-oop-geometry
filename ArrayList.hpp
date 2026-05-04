#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <iostream>

template<class T>
class ArrayList 
{
public:
    static constexpr size_t START_CAPACITY = 20;
    static constexpr float CAPACITY_INCREASE_COEFF = 2.0;

    ArrayList():
        capacity_(START_CAPACITY),
        size_(0)
    {
        head_ = new T[capacity_];
    }

    ArrayList(size_t capacity):
        capacity_(capacity),
        size_(0)
    {
        head_ = new T[capacity_];
    }

    ArrayList(const ArrayList& other):
        capacity_(other.capacity_),
        size_(other.size_)
    {
        head_ = new T[capacity_];
        for (size_t i = 0; i < size_; ++i)
        {
            head_[i] = other.head_[i];
        }
    }

    ArrayList(ArrayList&& other) noexcept:
        capacity_(other.capacity_),
        size_(other.size_),
        head_(other.head_)
    {
        other.head_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
    }
    
    ArrayList& operator=(const ArrayList& other)
    {
        if (this != &other)
        {
            ArrayList copy = ArrayList(other);
            swap(copy);
        }
        return *this;
    }

    ArrayList& operator=(ArrayList&& other) noexcept
    {
        if (this != &other)
        {
            delete[] head_;
            capacity_ = other.capacity_;
            size_ = other.size_;
            head_ = other.head_;
            other.head_ = nullptr;
            other.capacity_ = 0;
            other.size_ = 0;
        }
        return *this;
    }

    ~ArrayList()
    {
        delete[] head_;
        head_ = nullptr;
    }

    void add(const T& element)
    {
        if (size_ >= capacity_) {
            capacity_ = static_cast<size_t>(capacity_ * CAPACITY_INCREASE_COEFF);
            T* newHead = new T[capacity_];
            for (size_t i = 0; i < size_; ++i)
            {
                newHead[i] = head_[i];
            }
            std::swap(head_, newHead);
            delete[] newHead;
            newHead = nullptr;
        }
        head_[size_] = element;
        ++size_;
    }
    
    void replace(size_t index, const T& element)
    {
        head_[index] = element;
    }

    T pop(size_t index)
    {
        T result = head_[index];
        for (size_t i = index; i < size_-1; ++i)
        {
            head_[i] = head_[i+1];
        }
        --size_;
        return result;
    }

    void remove(size_t index)
    {
        for (size_t i = index; i < size_-1; ++i)
        {
            head_[i] = head_[i+1];
        }
        --size_;
    }

    bool contains(const T& value) const
    {
        for (size_t i = 0; i < size_; ++i)
        {
            if (head_[i] == value)
            {
                return true;
            }
        }
        return false;
    }

    T get(size_t index) const
    {
        return head_[index];
    }

    size_t getSize() const
    {
        return size_;
    }

    size_t getCapacity() const
    {
        return capacity_;
    }

    bool isEmpty() const
    {
        return size_ == 0;
    }

private:
    size_t capacity_ = 0;
    size_t size_ = 0;
    T* head_ = nullptr;

    void swap(ArrayList& other)
    {
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(head_, other.head_);
    }

};


template <class T1>
std::ostream& operator<<(std::ostream& out, const ArrayList<T1>& arrayList)
{
    std::ostream::sentry s(out);
    if (!s)
    {
        return out;
    }

    for (int i = 0; i < arrayList.getSize(); ++i)
    {
        out << arrayList.get(i) << " ";
    }
    out << "\n";
    return out;
}

#endif
