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

template <class currClass>
class Deque
{
private:
    currClass * elements, *buf;
    size_t elementsBegin, elementsEnd, elementsSize, memorySize;
    void copyArrayToBuf()
    {
        for (size_t index = elementsBegin; index < elementsEnd; index++)
            buf[index - elementsBegin] = elements[index];
    }
    void copyBufToArray()
    {
        for (size_t index = 0u; index < elementsSize; index++)
            elements[index + elementsBegin] = buf[index];
    }
    void changeMemorySize(bool flag)
    {
        buf = new currClass[elementsSize];
        copyArrayToBuf();
        if (flag)
            memorySize *= 3u;
        else
            memorySize /= 2u;
        elements = new currClass[memorySize];
        elementsBegin = memorySize / 3u;
        elementsEnd = elementsBegin + elementsSize;
        copyBufToArray();
        buf = new currClass[1u];
    }
    void push()
    {
        if (elementsBegin <= 0u || elementsEnd >= memorySize)
            changeMemorySize(true);
        elementsSize++;
    }
    void pop()
    {
        elementsSize--;
        if (elementsSize * 6u <= memorySize)
            changeMemorySize(false);
    }
public:
    Deque()
    {
        elements = new currClass[1];
        elementsBegin = 0u;
        elementsEnd = 1u;
        elementsSize = 0u;
        memorySize = 1u;
    }
    void pushFront(currClass key)
    {
        push();
        elementsBegin--;
        elements[elementsBegin] = key;
    }
    void pushBack(currClass key)
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
    currClass &operator[](size_t index)
    {
        if (index < elementsSize)
            return elements[elementsBegin + index];
        throw InvalidIndex(index);
    }
    const currClass &operator[](size_t index) const
    {
        return elements[index];
    }
    currClass &back()
    {
        return elements[elementsEnd - 1u];
    }
    const currClass &back() const
    {
        return elements[elementsEnd - 1u];
    }
    currClass &front()
    {
        return elements[elementsBegin];
    }
    const currClass &front() const
    {
        return elements[elementsBegin];
    }
    bool empty() const
    {
        return elementsSize == 0u;
    }
    size_t size() const
    {
        return elementsSize;
    }

    typedef currClass* iterator;
    typedef const currClass* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef const std::reverse_iterator<iterator> const_reverse_iterator;

    iterator begin()
    {
        return elements + elementsBegin;
    }
    iterator begin() const
    {
        return elements + elementsBegin;
    }
    iterator cbegin() const
    {
        return elements + elementsBegin;
    }

    iterator end()
    {
        return elements + elementsEnd;
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
