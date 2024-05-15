
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

typedef unsigned long int ulong;
/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

class Container {

private:

protected:

  ulong size = 0;

  /* ************************************************************************ */

   // Default constructor
  Container() = default;

public:

  // Destructor
  virtual ~Container() = default;

  /* ************************************************************************ */

  // Copy assignment
  Container &  operator = (const Container & other) = delete; // Copy assignment of abstract types is not possible.
  
  // Move assignment
  Container &  operator = (Container && other) = delete; // Move assignment of abstract types is not possible.
  
  /* ************************************************************************ */

  // Comparison operators
  bool operator ==(const Container & other) const noexcept = delete; // Comparison of abstract types is not possible.
  
  bool operator !=(const Container & other) const noexcept = delete; // Comparison of abstract types is not possible.
  
  /* ************************************************************************ */

  // Specific member functions

  inline virtual bool Empty() const noexcept{ return size == 0; } // (concrete function should not throw exceptions)
  inline virtual ulong Size() const noexcept{ return size; }  // (concrete function should not throw exceptions)
};

/* ************************************************************************** */

class ClearableContainer: virtual public Container {

private:

protected:

public:

  // Destructor
  virtual ~ClearableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  ClearableContainer &  operator = (const ClearableContainer & other) = delete;  // Copy assignment of abstract types is not possible.

  // Move assignment
  ClearableContainer &  operator = (ClearableContainer && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator ==(const ClearableContainer & other) const noexcept = delete;// Comparison of abstract types is not possible.
  bool operator !=(const ClearableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Clear() noexcept = 0;

};

/* ************************************************************************** */

class ResizableContainer: virtual public ClearableContainer{

private:

protected:

public:

  // Destructor
  virtual ~ResizableContainer() = default; 
  /* ************************************************************************ */

  // Copy assignment
  ResizableContainer &  operator = (const ResizableContainer & other) = delete;  // Copy assignment of abstract types is not possible.

  // Move assignment
  ResizableContainer &  operator = (ResizableContainer && other) = delete; // Move assignment of abstract types is not possible.
  

  /* ************************************************************************ */

  // Comparison operators
  bool operator ==(const ResizableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.
  bool operator !=(const ResizableContainer & other) const noexcept = delete; // Comparison of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual void Resize(const ulong size) = 0;

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() noexcept override { Resize(0); }; // Override ClearableContainer member
  // imposto la dimensione a 0 cosi svuoto tutto.
};

/* ************************************************************************** */

}

#endif
