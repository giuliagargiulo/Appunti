
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Stack : virtual public ClearableContainer {

private:

protected:

public:

  // Destructor
  virtual ~Stack() = default;

  /* ************************************************************************ */

  // Copy assignment
  Stack & operator =(const Stack & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  Stack & operator =(Stack && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator ==(const Stack & other) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator !=(const Stack & other) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Data & Top() const = 0; // (non-mutable version; concrete function must throw std::length_error when empty)
  virtual Data & Top() = 0;  // (mutable version; concrete function must throw std::length_error when empty)
  virtual void Pop() = 0; // (concrete function must throw std::length_error when empty)
  virtual Data TopNPop() = 0;  // (concrete function must throw std::length_error when empty)
  virtual void Push(const Data & val) = 0;  // Copy of the value
  virtual void Push(Data && val) = 0; // Move of the value

};

/* ************************************************************************** */

}

#endif
