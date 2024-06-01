
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

#define STARTING_SIZE 10
#define RESIZE_FACTOR 2
#define RESIZE_DIVISOR 4
/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : virtual public Stack<Data>, virtual protected Vector<Data> {

private:

protected:

  using Vector<Data>::array;
  using Container::size;
  ulong counter = 0; // conta gli elementi inseriti nello stack (viene incrementato ad ogni push e decrementato ad ogni pop)
 
public:

  // Default constructor
  StackVec();

  /* ************************************************************************ */

  // Specific constructor
  StackVec(const TraversableContainer<Data> & trav_container); // A stack obtained from a TraversableContainer
  StackVec(MappableContainer<Data> && map_container); // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  StackVec(const StackVec<Data> & old_stack);
  // Move constructor
  StackVec(StackVec<Data> && old_stack);

  /* ************************************************************************ */

  // Destructor
  ~StackVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  StackVec & operator = (const StackVec & other);

  // Move assignment
  StackVec & operator = (StackVec && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const StackVec & other) const noexcept;
  bool operator != (const StackVec & other) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)

  const Data & Top() const override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  Data & Top() override; // Override Stack member (non-mutable version; must throw std::length_error when empty)
  void Pop() override; // Override Stack member (must throw std::length_error when empty)
  Data TopNPop() override; // Override Stack member (must throw std::length_error when empty)
  void Push(const Data & val) override; // Override Stack member (copy of the value)
  void Push(Data && val) override; // Override Stack member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  inline bool Empty() const noexcept override{ return counter == 0; } // Override Container member
  // Controlla quanti elementi sono stati inseriti nello stack (ritorna TRUE se non ci sono elementi)

  inline ulong Size() const noexcept override{ return counter; } // Override Container member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member

  // Specific member function (inherited from ResizableContainer)

  void Resize(const ulong new_size) override; // Override ResizableContainer member

protected:

  // ...
};

/* ************************************************************************** */

}

#include "stackvec.cpp"

#endif
