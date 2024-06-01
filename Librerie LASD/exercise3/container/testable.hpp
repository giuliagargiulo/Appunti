
#ifndef TESTABLE_HPP
#define TESTABLE_HPP

/* ************************************************************************** */

#include "container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class TestableContainer : virtual public Container {

private:

protected:

public:

  // Destructor
  virtual ~TestableContainer() = default; // ~TestableContainer() specifiers

  /* ************************************************************************ */

  // Copy assignment
  TestableContainer & operator =(const TestableContainer & other ) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  TestableContainer & operator = (TestableContainer && other) = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const TestableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator != (const TestableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member function

virtual bool Exists(const Data & val) const noexcept = 0;  // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

}

#endif
