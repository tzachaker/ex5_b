#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP
#include "MagicalContainer.hpp"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

namespace ariel
{
    class MagicalContainer
    {
        private:
            vector <int> _elements; 
            vector <int*> _prime_elements;
            
        public:
            MagicalContainer(); 
            vector<int> elements() const; //for _elements
            vector<int*> primeElements() const; //for _prime_elements
            void addElement(int element); 
            void removeElement(int element); 
            size_t size() const;  

            class Iterator
            {
                private:
                    size_t idx;
                    MagicalContainer &container;

                public:
                    Iterator(Iterator &&other) = delete; // for tidy
                    Iterator &operator=(Iterator &&other) = delete; // for tidy  
                    Iterator(MagicalContainer &magicCont);
                    Iterator(MagicalContainer &magicCont, size_t idx);
                    Iterator(const Iterator& other); 
                    virtual ~Iterator();
                    Iterator &operator=(const Iterator &other);
                    virtual Iterator &operator++() = 0;
                    virtual bool operator==(const Iterator &other) const;
                    virtual bool operator!=(const Iterator &other) const;
                    virtual bool operator>(const Iterator &other) const; 
                    virtual bool operator<(const Iterator &other) const; 
                    virtual int operator*() const; 
                    MagicalContainer &getCont() const; 
                    size_t getIdx() const;
                    void incIdx(); 
            };

            class AscendingIterator: public Iterator
            {
                private:

                public:
                    AscendingIterator(AscendingIterator &&other) = delete; // for tidy
                    AscendingIterator& operator=(AscendingIterator &&other) = delete; // for tidy
                    AscendingIterator(MagicalContainer &magicCont, size_t idx);
                    AscendingIterator(MagicalContainer &magicCont);
                    AscendingIterator(const AscendingIterator &other);
                    ~AscendingIterator() override; 
                    AscendingIterator &operator=(const AscendingIterator &other) = default; 
                    AscendingIterator &operator++() override; 
                    AscendingIterator begin();
                    AscendingIterator end();
            };

            class SideCrossIterator : public Iterator
            {
                private:

                public:
                    SideCrossIterator(SideCrossIterator &&other) = delete; // for tidy
                    SideCrossIterator& operator=(SideCrossIterator && other) = delete; // for tidy
                    SideCrossIterator(MagicalContainer &magicCont, size_t idx);
                    SideCrossIterator(MagicalContainer &magicCont) ;                
                    SideCrossIterator(const SideCrossIterator &other);
                    ~SideCrossIterator() override;  
                    SideCrossIterator &operator=(const SideCrossIterator &other) = default;    
                    int operator*() const override;                
                    SideCrossIterator &operator++() override; 
                    SideCrossIterator begin();
                    SideCrossIterator end();
            };

            class PrimeIterator : public Iterator
            {
                private:

                public:
                    PrimeIterator(PrimeIterator &&other) = delete; // for tidy
                    PrimeIterator& operator=(PrimeIterator &&other) = delete; // for tidy
                    PrimeIterator(MagicalContainer &magicCont, size_t idx);
                    PrimeIterator(MagicalContainer &magicCont);
                    PrimeIterator(const PrimeIterator &other);
                    ~PrimeIterator() override;
                    PrimeIterator &operator=(const PrimeIterator &other) = default;
                    int operator*() const override;
                    PrimeIterator &operator++() override;
                    PrimeIterator begin();
                    PrimeIterator end();
            };
    };
}
#endif