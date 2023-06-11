#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <iterator>
#include <algorithm>
#include <set>
using namespace std;
namespace ariel
{
    class MagicalContainer
    {
    private:
        vector<int> elements;
        vector<int *> Prime_vec;

    public:
        bool isPrime(int num);
        MagicalContainer();
        ~MagicalContainer();
        MagicalContainer(const MagicalContainer &) = delete;            
        MagicalContainer &operator=(const MagicalContainer &) = delete; 
        MagicalContainer(MagicalContainer &&) = delete;                 
        MagicalContainer &operator=(MagicalContainer &&) = delete;      
        void addElement(int element);
        void removeElement(int element);
        int size();
        void setSize(int newSize);

        class AscendingIterator
        {
        private:
            const MagicalContainer *container;
            size_t index;

        public:
            AscendingIterator();
            AscendingIterator(const AscendingIterator &other);
            AscendingIterator(const MagicalContainer &other);
            ~AscendingIterator();
            AscendingIterator(AscendingIterator &&other) = default;            // Move constructor
            AscendingIterator &operator=(AscendingIterator &&other) = default; // Move assignment operator
            AscendingIterator &operator=(const AscendingIterator &other);
            AscendingIterator &operator++();
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            int operator*();
            AscendingIterator begin() const;
            AscendingIterator end() const;
        };

        class SideCrossIterator
        {
        private:
            const MagicalContainer *container;
            size_t index;
            bool isForward = true;

        public:
            SideCrossIterator();
            SideCrossIterator(const SideCrossIterator &other);
            SideCrossIterator(const MagicalContainer &other);
            ~SideCrossIterator();
            SideCrossIterator(SideCrossIterator &&other) = default;            // Move constructor
            SideCrossIterator &operator=(SideCrossIterator &&other) = default; // Move assignment operator
            SideCrossIterator &operator++();
            SideCrossIterator &operator=(const SideCrossIterator &other);
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            int operator*() const;
            SideCrossIterator begin() const;
            SideCrossIterator end() const;
        };

        class PrimeIterator
        {
        private:
            const MagicalContainer *container;
            size_t index;

        public:
            PrimeIterator();
            PrimeIterator(const PrimeIterator &other);
            PrimeIterator(const MagicalContainer &other);
            ~PrimeIterator();
            PrimeIterator(PrimeIterator &&other) = default;            // Move constructor
            PrimeIterator &operator=(PrimeIterator &&other) = default; // Move assignment operator
            PrimeIterator &operator++();
            PrimeIterator &operator=(const PrimeIterator &other);
            bool operator>(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            int operator*() const;
            PrimeIterator begin() const;
            PrimeIterator end() const;
        };
    };

}