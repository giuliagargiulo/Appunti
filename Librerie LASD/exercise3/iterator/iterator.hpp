
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Iterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  Iterator & operator=(const Iterator & other) = delete; // Copy assignment of abstract is not possible.

  // Move assignment
  Iterator & operator=(Iterator && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const Iterator & other) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator != (const Iterator & other) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data & operator*() const  = 0; // (non-mutable version; concrete function must throw std::out_of_range when terminated)

  virtual inline bool Terminated() const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class MutableIterator: virtual public Iterator<Data>{

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~MutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableIterator & operator=(const MutableIterator & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableIterator & operator=(MutableIterator && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator ==(const MutableIterator & other) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator !=(const MutableIterator & other) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions
  using Iterator<Data>::operator*;
  virtual Data & operator*() = 0; // (mutable version; concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator : virtual public Iterator<Data>{
 
private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ForwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  ForwardIterator & operator = (const ForwardIterator & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ForwardIterator & operator = (ForwardIterator && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const ForwardIterator & other) const noexcept = delete;  // Comparison of abstract types is not possible.
  bool operator != (const ForwardIterator & other) const noexcept = delete;  // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual ForwardIterator & operator++() = 0; // (concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class ResettableIterator : virtual public Iterator<Data>{

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ResettableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  ResettableIterator & operator =(const ResettableIterator & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  ResettableIterator & operator =(ResettableIterator && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator ==(const ResettableIterator & other) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator !=(const ResettableIterator & other) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Reset() noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

}

#endif
