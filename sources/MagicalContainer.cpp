#include <iterator>
#include <cmath>
#include "MagicalContainer.hpp"

namespace ariel
{

    MagicalContainer::MagicalContainer() : elements() {}

    MagicalContainer::~MagicalContainer()
    {
        // Delete the objects pointed to by the pointers in Prime_vec
        for (int* ptr : Prime_vec)
        {
            delete ptr;
        }
    }

    bool MagicalContainer::isPrime(int num)
    {
        if (num < 2)
        {
            return false;
        }
        for (int i = 2; i <= sqrt(num); ++i)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    void MagicalContainer::addElement(int element)
    {
        elements.push_back(element);                 // Add element at the end
        std::sort(elements.begin(), elements.end()); // Sort in ascending order

        if (isPrime(element))
        {
            int *prime_element = new int(element);   // Dynamically allocate memory for the prime element
            Prime_vec.push_back(prime_element);      // Add the pointer to Prime_vec
        }
    }

    void MagicalContainer::removeElement(int element)
    {
        auto iter = std::find(elements.begin(), elements.end(), element);
        if (iter != elements.end())
        {
            elements.erase(iter);                     // Remove element from elements vector
        }
        else
        {
            throw std::runtime_error("The element is not in the container");
        }

        auto primeIter = std::find_if(Prime_vec.begin(), Prime_vec.end(),
                                      [element](int *ptr)
                                      { return (*ptr) == element; });
        if (primeIter != Prime_vec.end())
        {
            delete (*primeIter);                        // Delete the object pointed to by the pointer
            Prime_vec.erase(primeIter);                  // Remove the pointer from Prime_vec
        }
    }

    int MagicalContainer::size()
    {
        return elements.size();
    }

    void MagicalContainer::setSize(int newSize)
    {
        this->setSize(newSize);  // This is an infinite recursion, it should be modified to set the size of the container
    }

    //************AscendingIterator***********

    MagicalContainer::AscendingIterator::AscendingIterator() : container(nullptr), index(0) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
        : container(other.container), index(other.index) {}

    MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &other)
        : container(&other), index(0) {}

    MagicalContainer::AscendingIterator::~AscendingIterator() {}

    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if (this->container != other.container)
        {
            throw std::runtime_error("this pointers not associated with the same container");
        }
        if (this != &other)
        {
            container = other.container;
            index = other.index;
        }
        return *this;
    }


// AscendingIterator
bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
{
    return (container == other.container) && (index == other.index);
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    return !operator==(other);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
{
    // Less-than comparison operator
    if (container != other.container)
    {
        throw std::runtime_error("Comparison of iterators from different containers is not allowed");
    }
    return index > other.index;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
{
    // Less-than comparison operator
    if (container != other.container)
    {
        throw std::runtime_error("Comparison of iterators from different containers is not allowed");
    }
    return index < other.index;
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (container && index < container->elements.size())
    {
        ++index;
        return *this;
    }
    throw std::runtime_error("Iterator is already at the end or not associated with a container");
}

int MagicalContainer::AscendingIterator::operator*()
{
    return container->elements[index];
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin() const
{
    // begin() function
    if (container)
    {
        AscendingIterator it(*this);
        it.index = 0;
        return it;
    }
    throw std::runtime_error("Iterator is not associated with a container");
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() const
{
    AscendingIterator iter(*container);
    iter.index = container->elements.size();
    return iter;
}

//*********SideCrossIterator**********
MagicalContainer::SideCrossIterator::SideCrossIterator()
    : container(nullptr), index(0), isForward(true) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other)
    : container(other.container), index(other.index), isForward(other.isForward) {}

MagicalContainer::SideCrossIterator::SideCrossIterator(const MagicalContainer &container)
    : container(&container), index(0), isForward(true) {}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
{
    if (this->container != other.container)
    {
        throw runtime_error("this two iterator not associated with the same container");
    }

    if (this != &other)
    {
        container = other.container;
        index = other.index;
        isForward = other.isForward;
    }
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &other) const
{
    return (container == other.container) && (index == other.index);
}

bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &other) const
{
    return !(*this == other); // Reuse the implemented operator==
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
{
    if (container != other.container)
    {
        throw std::runtime_error("Comparison of iterators from different containers is not allowed");
    }
    return index < other.index;
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
{
    if (container != other.container)
    {
        throw std::runtime_error("Comparison of iterators from different containers is not allowed");
    }
    return index > other.index;
}

MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
{
    if (this->index == container->elements.size())
    {
        throw std::runtime_error("*****");
    }

    if (index == (container->elements.size() / 2))
    {
        index = container->elements.size();
        return *this;
    }

    if (isForward)
    {
        if (index < container->elements.size() / 2)
        {
            index = container->elements.size() - index - 1;
        }
        else
        {
            index = container->elements.size() - index;
            isForward = false;
        }
    }
    else
    {
        if (index > container->elements.size() / 2)
        {
            index = container->elements.size() - index;
        }
        else
        {
            index = container->elements.size() - index - 1;
            isForward = true;
        }
    }

    return *this;
}

int MagicalContainer::SideCrossIterator::operator*() const
{
    if (container != nullptr && index < container->elements.size())
    {
        return container->elements[index];
    }
    throw std::out_of_range("Iterator out of range");
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin() const
{
    return SideCrossIterator(*container);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end() const
{
    SideCrossIterator iter(*container);
    iter.index = container->elements.size();
    return iter;
}

//*********primeIterator*********

MagicalContainer::PrimeIterator::PrimeIterator()
    : container(nullptr), index(0) {}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
    : container(other.container), index(other.index) {}

MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container)
    : container(&container), index(0) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (index == this->end().index)
    {
        throw std::runtime_error("you cant promote the last index");
    }
    ++index;
    return *this;
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (this->container != other.container)
    {
        throw runtime_error("this two iterator not associated with the same container");
    }

    if (this != &other)
    {
        container = other.container;
        index = other.index;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
{
    return index > other.index;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
{
    return index < other.index;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    return (container == other.container) && (index == other.index);
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    return !(*this == other);
}

int MagicalContainer::PrimeIterator::operator*() const
{
    if (container && index < container->Prime_vec.size())
    {
        return *(container->Prime_vec[index]);
    }
    throw std::runtime_error("Iterator is already at the end or not associated with a container");
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin() const
{
    PrimeIterator it(*this);
    it.index = 0;
    if (it.container && it.container->Prime_vec.size() > 0 && it.index % 2 == 0)
    {
        ++it;
    }
    return it;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end() const
{
    PrimeIterator it(*this);
    it.index = container ? container->Prime_vec.size() : 0;
    return it;
}
}