
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"
/* ************************************************************************** */

#define STARTING_SIZE 10
#define RESIZE_FACTOR 2
#define RESIZE_DIVISOR 4

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : virtual public Queue<Data>, virtual protected Vector<Data>{


private:

protected:

  using Vector<Data>::array;
  using Container::size;
  ulong head = 0;
  ulong tail = 0;

public:

  // Default constructor
  QueueVec();

  /* ************************************************************************ */

  // Specific constructor
  QueueVec(const TraversableContainer<Data> & trav_container); // A stack obtained from a TraversableContainer
  QueueVec(MappableContainer<Data> && map_container); // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueVec(const QueueVec<Data> & other);

  // Move constructor
  QueueVec(QueueVec<Data> && other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~QueueVec() = default;

  /* ************************************************************************ */

  // Copy assignment
  QueueVec<Data> & operator = (const QueueVec & other);

  // Move assignment
  QueueVec<Data> & operator = (QueueVec && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const QueueVec & other) const ;
  bool operator != (const QueueVec & other) const { return !(operator==(other)); };   // oppure !(*this == other)

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data & Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data & Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data & val) override; // Override Queue member (copy of the value)
  void Enqueue(Data && val) noexcept override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  bool Empty() const noexcept override{ return head == tail;};  // Override Container member

  inline ulong Size() const noexcept override { return (size == 0) ? 0 : ((tail+size-head)%size); };  // Override Container member 
  // Size conta il numero di elementi presenti nella coda

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override;  // Override ClearableContainer member


protected:

  void Reduce();    // Reduce the size of the queue
  void Expand();    // Expand the size of the queue
  void Resize(const ulong newsize) override; 
};

/* ************************************************************************** */

}

#include "queuevec.cpp"

#endif
