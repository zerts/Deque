#define _SCL_SECURE_NO_WARNINGS

#include <cstdlib>
#include <iterator>
#include <cassert>
#include <string>

class InvalidIndex : public  std::exception
{
    std::string message;
public:
    explicit InvalidIndex(size_t index)
    {
        message = "Index is out of range: " + std::to_string(index) + "\n";
    }
    virtual const char* what() const throw()
    {
        return message.c_str();
    }
};

template <class CurrClass>
class Deque
{
private:
    CurrClass * elements, *buf;
    size_t elementsBegin, elementsEnd, memorySize;
public:
    typedef CurrClass* iterator;
    typedef const CurrClass* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef const std::reverse_iterator<iterator> const_reverse_iterator;

    iterator begin()
    {
        return elements + elementsBegin;
    }
    iterator end()
    {
        return elements + elementsEnd;
    }
private:
    void copyArrayToBuf()
    {
        std::copy(begin(), end(), buf);
    }
    void copyBufToArray()
    {
        std::copy(buf, buf + (end() - begin()), begin());
    }
    void changeMemorySize(bool makeDequeBigger)
    {
        delete[] buf;
        buf = new CurrClass[(end() - begin())];
        copyArrayToBuf();
        if (makeDequeBigger)
            memorySize *= 3u;
        else
            memorySize /= 2u;
        delete[] elements;
        elements = new CurrClass[memorySize];
        size_t currElementsSize = (end() - begin());
        elementsBegin = memorySize / 3u;
        elementsEnd = elementsBegin + currElementsSize;
        copyBufToArray();
            delete[] buf;
        buf = new CurrClass[1u];
    }
    void push()
    {
        if (elementsBegin <= 0u || elementsEnd >= memorySize)
            changeMemorySize(true);
    }
    void pop()
    {
        if ((end() - begin()) * 6u <= memorySize)
            changeMemorySize(false);
    }
public:
    Deque()
    {
        elements = new CurrClass[1];
        elementsBegin = 0u;
        elementsEnd = 0u;
        memorySize = 1u;
    }
    ~Deque()
    {
        delete[] buf;
        delete[] elements;
    }
    void pushFront(CurrClass key)
    {
        push();
        elementsBegin--;
        elements[elementsBegin] = key;
    }
    void pushBack(CurrClass key)
    {
        push();
        elements[elementsEnd] = key;
        elementsEnd++;
    }
    void popFront()
    {
        elementsBegin++;
        pop();
    }
    void popBack()
    {
        elementsEnd--;
        pop();
    }
    CurrClass &operator[](size_t index)
    {
        if (index < (end() - begin()))
            return elements[elementsBegin + index];
        throw InvalidIndex(index);
    }
    const CurrClass &operator[](size_t index) const
    {
        return elements[index];
    }
    CurrClass &back()
    {
        return elements[elementsEnd - 1u];
    }
    const CurrClass &back() const
    {
        return elements[elementsEnd - 1u];
    }
    CurrClass &front()
    {
        return elements[elementsBegin];
    }
    const CurrClass &front() const
    {
        return elements[elementsBegin];
    }
    bool empty() const
    {
        return (end() - begin()) == 0u;
    }
    size_t size() const
    {
        return (end() - begin());
    }

    iterator begin() const
    {
        return elements + elementsBegin;
    }
    iterator cbegin() const
    {
        return elements + elementsBegin;
    }

    iterator end() const
    {
        return elements + elementsEnd;
    }
    iterator cend() const
    {
        return elements + elementsEnd;
    }
    reverse_iterator rbegin()
    {
        return reverse_iterator(elements + elementsEnd);
    }

    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(elements + elementsEnd);
    }

    const_reverse_iterator crbegin() const
    {
        return const_reverse_iterator(elements + elementsEnd);
    }

    reverse_iterator rend()
    {
        return reverse_iterator(elements + elementsBegin);
    }

    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(elements + elementsBegin);
    }

    const_reverse_iterator crend() const
    {
        return const_reverse_iterator(elements + elementsBegin);
    }
    void print()
    {
        for (size_t i = elementsBegin; i != elementsEnd; i++)
            std::cout << elements[i] << ' ';
        std::cout << std::endl;
    }
};
