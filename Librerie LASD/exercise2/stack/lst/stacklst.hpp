
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : virtual public Stack<Data>, virtual protected List<Data> {

private:

protected:

  using List<Data>::List;
  using Container::size;

public:

  // Default constructor
  StackLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  StackLst(const TraversableContainer<Data> & trav_container) : List<Data>::List(trav_container) { ; }; // A stack obtained from a TraversableContainer
  StackLst(MappableContainer<Data> && map_container): List<Data>::List(std::move(map_container)) { ; };  // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackLst(const StackLst & old_stack) : List<Data>::List(old_stack) { ; }

  // Move constructor
  StackLst(StackLst && old_stack) noexcept : List<Data>::List(std::move(old_stack)) { ; }

  /* ************************************************************************ */

  // Destructor
  virtual ~StackLst(){
    Clear();
  };

  /* ************************************************************************ */

  // Copy assignment
  StackLst<Data> & operator = (const StackLst & other);

  // Move assignment
  StackLst<Data> & operator = (StackLst && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const StackLst & other) const noexcept{ return List<Data>::operator==(other); };
  bool operator != (const StackLst & other) const noexcept{ return List<Data>::operator!=(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  inline const Data & Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  inline Data & Top() override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  inline void Pop() override;  // Override Stack member (must throw std::length_error when empty)
  inline Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  inline void Push(const Data & val) override; // Override Stack member (copy of the value)
  inline void Push(Data && val) override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;
  using List<Data>::Empty;

protected:

};

/* ************************************************************************** */

}

#include "stacklst.cpp"

#endif
