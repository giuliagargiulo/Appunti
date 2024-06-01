
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#define HASH_TABLE_SIZE 16

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hashable {

public:

  ulong operator()(const Data val) const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable : public virtual DictionaryContainer<Data>, public virtual ResizableContainer{

private:

  // ...

protected:

  using DictionaryContainer<Data>::size;

  ulong tableSize = HASH_TABLE_SIZE;
  ulong A = 1;
  ulong B = 0;
  static const ulong prime = 109345121;

  std::default_random_engine seed = std::default_random_engine(std::random_device{}());
  std::uniform_int_distribution<ulong> genA = std::uniform_int_distribution<ulong>(1, prime-1);
  std::uniform_int_distribution<ulong> genB = std::uniform_int_distribution<ulong>(0, prime-1);

  /* ************************************************************************ */

  // Default Constructor
  HashTable(){
    A = genA(seed)*2 + 1;
    B = NextPow(genB(seed));
  }

  // Copy Constructor
  HashTable(const HashTable & other);

  // Move Constructor
  HashTable(HashTable && other) noexcept;

public:

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTable & operator = (const HashTable & other); // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable & operator = (HashTable && other) noexcept; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  // NOTA: non si devono implementare per forza
  bool operator == (const HashTable & other) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.
  bool operator != (const HashTable & other) const noexcept = delete; // Comparison of abstract hashtable is possible but not required.
 
protected:

  // Auxiliary member functions
  ulong HashKey(const ulong key) const noexcept;  //  TODO:serve per risolvere le collisioni nelle OpnAdr HashTable? forse ne serve un'altra
  ulong NextPow(ulong newSize); // calcola la successiva potenza di 2

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
