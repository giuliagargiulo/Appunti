
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include <random>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : public virtual HashTable<Data> {

private:

  // ...

protected:
  using DictionaryContainer<Data>::size;

  using HashTable<Data>::tableSize;
  using HashTable<Data>::NextPow;
  using HashTable<Data>::HashKey;

  enum Flag {empty, deleted, occupied};

  Data * table = nullptr;
  Flag * flags = nullptr;  // Array of flags for each element in the table

  ulong deletedElem = 0;

  //using typename TraversableContainer<Data>::TraverseFun;
  //void Traverse(TraverseFun fun) const;

public:
  
  using DictionaryContainer<Data>::Exists;
  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::RemoveAll;


  // Default constructor
  HashTableOpnAdr(){
    table = new Data[tableSize]{};
    flags = new Flag[tableSize]{};
  }

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const ulong newSize); // A hash table of a given size
  HashTableOpnAdr(const TraversableContainer<Data> & trav_container); // A hash table obtained from a TraversableContainer
  HashTableOpnAdr(const ulong newSize, const TraversableContainer<Data> & trav_container); // A hash table of a given size obtained from a TraversableContainer
  HashTableOpnAdr(MappableContainer<Data> && map_container) noexcept;  // A hash table obtained from a MappableContainer
  HashTableOpnAdr(const ulong newSize, MappableContainer<Data> && map_container) noexcept;// A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr<Data> & other);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr<Data> && other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HashTableOpnAdr(){
    delete[] table;
    delete[] flags;
  }

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr & operator=(const HashTableOpnAdr & other);

  // Move assignment
  HashTableOpnAdr & operator=(HashTableOpnAdr && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const HashTableOpnAdr & other) const noexcept; 
  bool operator != (const HashTableOpnAdr & other) const noexcept{ return !(operator == (other));}

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data & val) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data && val) noexcept override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data & val) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data & val) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(const ulong size) override; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() noexcept override;  // Override Container member

protected:

  // Auxiliary member functions

  ulong QuadraticProbing(ulong & probing, const Data & key) const noexcept;
  bool Find(ulong & index, ulong & probing, const Data & key) const noexcept; 
  ulong FindEmpty(ulong & probing, const Data & key) noexcept;
  bool RemoveElem(ulong & probing, const Data & key);

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
