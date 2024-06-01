
#ifndef HTCLSADR_HPP
#define HTCLSADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableClsAdr : public virtual HashTable<Data>{

private:

protected:

  using DictionaryContainer<Data>::size;
  
  using HashTable<Data>::tableSize;
  using HashTable<Data>::NextPow;
  using HashTable<Data>::HashKey;

  List<Data> * table = nullptr;


public:

  using DictionaryContainer<Data>::Exists;
  using DictionaryContainer<Data>::InsertAll;
  using DictionaryContainer<Data>::RemoveAll;

  // Default constructor
  HashTableClsAdr(){
    table = new List<Data>[tableSize]{};
  };

  /* ************************************************************************ */

  // Specific constructors
  HashTableClsAdr(const ulong newSize); // A hash table of a given size
  HashTableClsAdr(const TraversableContainer<Data> & trav_container); // A hash table obtained from a TraversableContainer
  HashTableClsAdr(const ulong newSize, const TraversableContainer<Data> & trav_container); // A hash table of a given size obtained from a TraversableContainer
  HashTableClsAdr(MappableContainer<Data> && map_container) noexcept; // A hash table obtained from a MappableContainer
  HashTableClsAdr(const ulong newSize, MappableContainer<Data> && map_container) noexcept; // A hash table of a given size obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableClsAdr(const HashTableClsAdr & other);

  // Move constructor
  HashTableClsAdr(HashTableClsAdr && other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~HashTableClsAdr(){ delete[] table; };

  /* ************************************************************************ */

  // Copy assignment
  HashTableClsAdr & operator =(const HashTableClsAdr & other);

  // Move assignment
  HashTableClsAdr & operator =(HashTableClsAdr && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator ==(const HashTableClsAdr & other) const noexcept;
  bool operator !=(const HashTableClsAdr & other) const noexcept{ return !(operator ==(other));}

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data & val) override;  // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data && val) noexcept override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data & val) override;  // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data & val) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from ResizableContainer)

  void Resize(const ulong newsize) override; // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from ClearableContainer)

  void Clear() noexcept override; // Override Container member

};

/* ************************************************************************** */

}

#include "htclsadr.cpp"

#endif
