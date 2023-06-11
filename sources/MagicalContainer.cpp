#include "MagicalContainer.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

namespace ariel
{
    MagicalContainer::MagicalContainer() 
    {

    }

    vector<int> MagicalContainer::elements() const
    { 
        return _elements;
    } 

    vector<int*> MagicalContainer::primeElements() const 
    { 
        return _prime_elements;
    } 

    //check if num is prime
    bool prime(int n) {
        if (n <2) return false;
        for (int i = 2; i <= sqrt(n); ++i) {
            if (n % i == 0) return false;
        }
        return true;
    }

    void MagicalContainer::addElement(int element)
    {
        size_t i = 0;
        _prime_elements.clear();
        auto iterOn = find(_elements.begin(), _elements.end(), element); 
        if (iterOn != _elements.end()) throw runtime_error("there is already this element"); 
        _elements.push_back(element); 
        sort(_elements.begin(), _elements.end()); 
        //now, update _prime_elements :
        while(i <= _elements.size()-1){
            if(prime(_elements.at(i)))
                _prime_elements.push_back(&_elements.at(i));
            ++i;
        }    
        sort(_prime_elements.begin(), _prime_elements.end()); //just in case
    }

    void MagicalContainer::removeElement(int element)
    {
        auto elementIter = find(_elements.begin(), _elements.end(), element); // check if the element exists in _elements vector
        if (elementIter == _elements.end()) throw std::runtime_error("Element does not exist in the container");
            _elements.erase(elementIter); // remove the element from _elements for AscendingIterator and SideCrossIterator
        auto primeElementIter = find(_prime_elements.begin(), _prime_elements.end(), &(*elementIter)); // Check if the element exists in _prime_elements vector 
        if (primeElementIter != _prime_elements.end())
            _prime_elements.erase(primeElementIter); // remove the element from _prime_elements for PrimeIterator
    }

    size_t MagicalContainer::size() const 
    { 
        return _elements.size();
    } 

    //Iterator :
    MagicalContainer::Iterator::Iterator( MagicalContainer &mc) 
    : container(mc), idx(0) 
    {

    }

    MagicalContainer::Iterator::Iterator(MagicalContainer &mc, size_t i)
    : container(mc), idx(i)
    {

    }

    MagicalContainer::Iterator::Iterator(const Iterator &other)
    : container(other.container), idx(other.idx)
    {

    }

    MagicalContainer::Iterator::~Iterator() 
    {

    }

    MagicalContainer &MagicalContainer::Iterator::getCont() const
    {
        return container;
    }

    size_t MagicalContainer::Iterator::getIdx() const
    {
        return idx;
    }

    void MagicalContainer::Iterator::incIdx()
    { 
        ++idx;
    }


    MagicalContainer::Iterator &MagicalContainer::Iterator::operator=(const Iterator &other) {
        if(&container != &other.container) throw runtime_error("different containers");
        if (this != &other) {
            container = other.container;
            idx = other.idx;
        }
        return *this;
    }

    bool MagicalContainer::Iterator::operator==(const Iterator &other) const
    {
        if (typeid(*this) != typeid(other)) throw runtime_error("different types of Iterators");
        return idx == other.idx &&
               &container == &other.container;
    } 
    
    bool MagicalContainer::Iterator::operator!=(const Iterator &other) const
    {
        if (*this == other) return false; //for operator "!="
        return true;
    }   
    
    bool MagicalContainer::Iterator::operator>(const Iterator &other) const
    {
        return idx > other.idx;
    }  
    
    bool MagicalContainer::Iterator::operator<(const Iterator &other) const
    {
        return idx < other.idx;
    }   
    
    int MagicalContainer::Iterator::operator*() const 
    {
        return container._elements.at(idx);
    }

    //AscendingIterator :
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &cont, size_t idx)
    : Iterator(cont, idx)
    {

    }

    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer& cont)
        : Iterator(cont)
    {

    } 

    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
    :Iterator(other.getCont(), other.getIdx())
    {

    }

    MagicalContainer::AscendingIterator::~AscendingIterator()
    {

    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++() 
    {
        if(getIdx() == getCont().elements().size()) throw runtime_error("it can not increment after the end");
        incIdx(); 
        return *this;
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    {
        size_t beginIdx= 0;
        return AscendingIterator(getCont(), beginIdx); 
    }

    MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end() 
    {
        size_t endIdx= getCont().size();
        return AscendingIterator(getCont(), endIdx);
    }

    //SideCrossIterator :
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &cont, size_t idx)
    : Iterator(cont, idx)
    {

    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &cont) 
    : Iterator(cont, 0)
    {

    }

    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator& other) 
    : Iterator(other.getCont(), other.getIdx())
    {

    }
        
    MagicalContainer::SideCrossIterator::~SideCrossIterator() 
    {

    }

    int MagicalContainer::SideCrossIterator::operator*() const
    { 
        size_t len = getCont().size() - 1;
        size_t forEven = getIdx() / 2;
        size_t forOdd = len - (getIdx() - 1 ) / 2;
        return (getIdx() % 2 == 0) ? getCont()._elements.at(forEven) : getCont()._elements.at(forOdd);
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++() {
        if(getIdx() == getCont().elements().size()) throw runtime_error("it can not increment after the end");
        incIdx(); 
        return *this;
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    {
        size_t beginIdx= 0;
        return SideCrossIterator(getCont(), beginIdx); 
    }

    MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
    {
        size_t endIdx= getCont().size();
        return SideCrossIterator(getCont(), endIdx);
    }

    //PrimeIterator :
    MagicalContainer::PrimeIterator::PrimeIterator( MagicalContainer &cont, size_t idx) 
    : Iterator(cont, idx)
    {

    }

    MagicalContainer::PrimeIterator::PrimeIterator( MagicalContainer &cont) 
    : Iterator(cont, 0)
    {

    }

    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) 
    : Iterator(other.getCont(), other.getIdx())
    {

    }
    
    MagicalContainer::PrimeIterator::~PrimeIterator() 
    {

    }

    int MagicalContainer::PrimeIterator::operator*() const 
    { 
        int forPointer= *getCont().primeElements().at(getIdx());
        return forPointer;
    }

    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++() {
        if(getIdx() == getCont().primeElements().size()) throw runtime_error("it can not increment after the end");
        incIdx();
        return *this;
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    {
        size_t beginIdx= 0;
        return PrimeIterator(getCont(), beginIdx);
    }

    MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
    {
        size_t endIdx= getCont().primeElements().size();
        return PrimeIterator(getCont(), endIdx);
    }
}

