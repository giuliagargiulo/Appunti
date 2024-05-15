
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : virtual public Queue<Data>, virtual protected List<Data> {

private:

protected:

  using Container::size;

public:

  // Default constructor
  QueueLst() = default;

  /* ************************************************************************ */

  // Specific constructor
  QueueLst(const TraversableContainer<Data> & new_queue): List<Data>::List(new_queue) { ; };  // A stack obtained from a TraversableContainer
  QueueLst(MappableContainer<Data> && new_queue): List<Data>:: List(std::move(new_queue)) { ; };  // A stack obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  QueueLst(const QueueLst & old_queue): List<Data>::List(old_queue) { ; }
  // Move constructor
  QueueLst(QueueLst && old_queue) noexcept : List<Data>::List(std::move(old_queue)) { ; }

  /* ************************************************************************ */

  // Destructor
  virtual ~QueueLst(){
    while(!(List<Data>::Empty()))
      List<Data>::RemoveFromFront();
  };

  /* ************************************************************************ */

  // Copy assignment
  QueueLst<Data> & operator = (const QueueLst & other);
  // Move assignment
  QueueLst<Data> & operator = (QueueLst && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueLst<Data>& other) const noexcept { return List<Data>::operator==(other); };
  bool operator!=(const QueueLst<Data>& other) const noexcept { return List<Data>::operator!=(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)

  const Data & Head() const override; // Override Queue member (non-mutable version; must throw std::length_error when empty)
  Data & Head() override; // Override Queue member (mutable version; must throw std::length_error when empty)
  void Dequeue() override; // Override Queue member (must throw std::length_error when empty)
  Data HeadNDequeue() override; // Override Queue member (must throw std::length_error when empty)
  void Enqueue(const Data & val) override; // Override Queue member (copy of the value)
  void Enqueue(Data && val) noexcept override; // Override Queue member (move of the value)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  using List<Data>::Clear;
  using List<Data>::Empty;


protected:


};

/* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
