
#ifndef LINEAR_HPP
#define LINEAR_HPP

/* ************************************************************************** */

#include "mappable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class LinearContainer: virtual public PreOrderMappableContainer<Data>, virtual public PostOrderMappableContainer<Data> {

private:

protected:

  using Container::size;

public:

  // Destructor
  virtual ~LinearContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  LinearContainer & operator = (const LinearContainer & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  LinearContainer & operator = (LinearContainer &&  other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const LinearContainer & other) const noexcept;  // Comparison of abstract types is possible.
  inline bool operator != (const LinearContainer & other) const noexcept{ return !operator== (other); };  // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data & operator [] (ulong val) const = 0; // (non-mutable version; concrete function must throw std::out_of_range when out of range)
  virtual Data & operator [] (ulong val) = 0; // (mutable version; concrete function must throw std::out_of_range when out of range)

  virtual const Data & Front() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data & Front(); // (mutable version; concrete function must throw std::length_error when empty)

  virtual const Data & Back() const; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data & Back(); // (mutable version; concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  void Traverse(TraverseFun fun) const override; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  void PreOrderTraverse(TraverseFun fun) const override;  // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  void PostOrderTraverse(TraverseFun fun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

   using typename MappableContainer<Data>::MapFun;

  void Map(MapFun fun) override; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun fun) override;  // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun fun) override;  // Override PostOrderMappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class SortableLinearContainer: virtual public LinearContainer<Data> {

private:

protected:

  using Container::size;

public:

  // Destructor
  virtual ~SortableLinearContainer() = default; 

  /* ************************************************************************ */

  // Copy assignment
  SortableLinearContainer & operator = (const SortableLinearContainer & other) = delete;  // Copy assignment of abstract types is not possible.

  // Move assignment
  SortableLinearContainer & operator = (SortableLinearContainer && other) noexcept = delete;  // Move assignment of abstract types is not be possible.

  /* ************************************************************************ */

  // Comparison operators
  inline bool operator == (const SortableLinearContainer & other) const noexcept{ return LinearContainer<Data>::operator == (other);}; // Comparison of abstract types is possible.
  inline bool operator != (const SortableLinearContainer & other) const noexcept{ return LinearContainer<Data>::operator!=(other); }; // Comparison of abstract types is possible.

  /* ************************************************************************ */

  // Specific member function

  virtual void Sort() noexcept; 

protected:

  void QuickSort(ulong p, ulong r);
  ulong Partition(ulong p, ulong r); 

};

/* ************************************************************************** */

}

#include "linear.cpp"

#endif
