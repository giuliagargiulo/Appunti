
#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

/* ************************************************************************** */

#include <functional>

/* ************************************************************************** */

#include "traversable.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class MappableContainer : virtual public TraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~MappableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  MappableContainer & operator = (const MappableContainer & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MappableContainer & operator = (MappableContainer && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const MappableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator != (const MappableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using MapFun = std::function<void(Data &)>;
  virtual void Map(MapFun) = 0; 

};

/* ************************************************************************** */

template <typename Data>
class PreOrderMappableContainer: virtual public MappableContainer<Data>, virtual public PreOrderTraversableContainer<Data> {

private:

protected:

public:

  // Destructor
  virtual ~PreOrderMappableContainer() = default; 

  /* ************************************************************************ */

  // Copy assignment
  PreOrderMappableContainer & operator = (const PreOrderMappableContainer & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PreOrderMappableContainer & operator = (PreOrderMappableContainer && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const PreOrderMappableContainer & other) const noexcept = delete;  // Comparison of abstract types is not possible.
  bool operator != (const PreOrderMappableContainer & other) const noexcept = delete;  // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;
  virtual void PreOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  void Map(MapFun fun) override; // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class PostOrderMappableContainer: virtual public MappableContainer<Data>, virtual public PostOrderTraversableContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~PostOrderMappableContainer() = default; 

  /* ************************************************************************ */

  // Copy assignment
  PostOrderMappableContainer & operator = (const PostOrderMappableContainer & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  PostOrderMappableContainer & operator = (PostOrderMappableContainer && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const PostOrderMappableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator != (const PostOrderMappableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;

  virtual void PostOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  void Map(MapFun) override; // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class InOrderMappableContainer: virtual public MappableContainer<Data>, virtual public InOrderTraversableContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~InOrderMappableContainer() = default; // ~InOrderMappableContainer() specifiers

  /* ************************************************************************ */

  // Copy assignment
  InOrderMappableContainer & operator = (const InOrderMappableContainer & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  InOrderMappableContainer & operator = (InOrderMappableContainer && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const InOrderMappableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator != (const InOrderMappableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;
  
  virtual void InOrderMap(MapFun) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  void Map(MapFun) override; // Override MappableContainer member

};

/* ************************************************************************** */

template <typename Data>
class BreadthMappableContainer: virtual public MappableContainer<Data>, virtual public BreadthTraversableContainer<Data>{

private:

protected:

public:

  // Destructor
  virtual ~BreadthMappableContainer() = default; // ~BreadthMappableContainer() specifiers

  /* ************************************************************************ */

  // Copy assignment
  BreadthMappableContainer & operator = (const BreadthMappableContainer & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BreadthMappableContainer & operator = (BreadthMappableContainer && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BreadthMappableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator != (const BreadthMappableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

  using typename MappableContainer<Data>::MapFun;
  
  virtual void BreadthMap(MapFun)  = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  void Map(MapFun) override; // Override MappableContainer member

};

/* ************************************************************************** */

}

#include "mappable.cpp"

#endif
