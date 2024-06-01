
#ifndef VECTOR_HPP
#define VECTOR_HPP

typedef unsigned long int ulong;
/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Vector: virtual public ResizableContainer, virtual public LinearContainer<Data> {

private:

protected:

  using Container::size;
  Data * array = nullptr;

public:

  // Default constructor
  Vector() = default; 
  
  /* ************************************************************************ */

  // Specific constructors
  Vector(const ulong lenght);   // A vector with a given initial dimension
  Vector(const TraversableContainer<Data> & trav_container); // A vector obtained from a TraversableContainer
  Vector(MappableContainer<Data> && map_container); // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  Vector(const Vector & other);

  // Move constructor
  Vector(Vector &&  other) noexcept;
  /* ************************************************************************ */

  // Destructor
  virtual ~Vector();

  /* ************************************************************************ */

  // Copy assignment
  Vector & operator = (const Vector & other);

  // Move assignment
  Vector & operator = (Vector && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator == (const Vector & other) const noexcept;
  inline bool operator != (const Vector & other) const noexcept{ return !operator==(other); };

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member
  
  /* ************************************************************************ */

  // Specific member function (inherited from ResizableContainer)
  void Resize(const ulong new_size) override;  // Override ResizableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)
     
  const Data & operator [] (const ulong index) const override; // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data & operator [] (const ulong index) override;  // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  const Data & Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data & Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  const Data & Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data & Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

protected:

  using TraversableContainer<Data>::Exists;

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

template <typename Data>
class SortableVector: virtual public Vector<Data>, virtual public SortableLinearContainer<Data> {

private:

protected:

  using Container::size;
  using Vector<Data>::array;

public:

  // Default constructor
  SortableVector() = default;

  /* ************************************************************************ */

  // Specific constructors
  SortableVector(const ulong size) : Vector<Data>(size){}; // A vector with a given initial dimension
  SortableVector(const TraversableContainer<Data> & trav_container) : Vector<Data>::Vector(trav_container){};  // A vector obtained from a TraversableContainer
  SortableVector(MappableContainer<Data> && map_container) : Vector<Data>::Vector(std::move(map_container)){};  // A vector obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  SortableVector(const SortableVector & other) : Vector<Data>::Vector(other){};

  // Move constructor
  SortableVector(SortableVector && other) noexcept : Vector<Data>::Vector(std::move(other)){};

  /* ************************************************************************ */

  // Destructor
  virtual ~SortableVector();
  /* ************************************************************************ */

  // Copy assignment
  SortableVector<Data> & operator =(const SortableVector & other);

  // Move assignment
  SortableVector<Data> & operator =(SortableVector && other) noexcept;

protected:

};

/* ************************************************************************** */

}

#include "vector.cpp"

#endif
