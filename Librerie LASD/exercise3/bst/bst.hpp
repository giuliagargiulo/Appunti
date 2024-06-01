
#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : public virtual ClearableContainer, public virtual DictionaryContainer<Data>, 
            public virtual BinaryTree<Data>, public virtual BinaryTreeLnk<Data>{

private:

  // ...

protected:

  using Container::size;
  using BinaryTreeLnk<Data>::root;
  using typename BinaryTreeLnk<Data>::NodeLnk;

public:

  // Default constructor
  BST() = default;

  /* ************************************************************************ */

  // Specific constructors
  BST(const TraversableContainer<Data> & trav_container); // A bst obtained from a TraversableContainer
  BST(MappableContainer<Data> && map_container); // A bst obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BST(const BST & other): BinaryTreeLnk<Data>(other){;};

  // Move constructor
  BST(BST && other) noexcept: BinaryTreeLnk<Data>(std::move(other)){;};

  /* ************************************************************************ */

  // Destructor
  ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST & operator=(const BST & other);

  // Move assignment
  BST & operator=(BST && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST & other) const noexcept;
  bool operator!=(const BST & other) const noexcept{ return !operator==(other);}

  /* ************************************************************************ */

  // Specific member functions

  const Data & Min() const; // (concrete function must throw std::length_error when empty)
  Data MinNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMin();  // (concrete function must throw std::length_error when empty)

  const Data & Max() const; // (concrete function must throw std::length_error when empty)
  Data MaxNRemove(); // (concrete function must throw std::length_error when empty)
  void RemoveMax(); // (concrete function must throw std::length_error when empty)

  const Data & Predecessor(const Data & elem) const; // (concrete function must throw std::length_error when not found)
  Data PredecessorNRemove(const Data & elem); // (concrete function must throw std::length_error when not found)
  void RemovePredecessor(const Data & elem); // (concrete function must throw std::length_error when not found)

  const Data & Successor(const Data & elem) const; // (concrete function must throw std::length_error when not found)
  Data SuccessorNRemove(const Data & elem); // (concrete function must throw std::length_error when not found)
  void RemoveSuccessor(const Data & elem); // (concrete function must throw std::length_error when not found)

  /* ************************************************************************ */

  // Specific member function (inherited from BinaryTree)

  const NodeLnk & Root() const override { return *root; }; // Override BinaryTree member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data & elem) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data && elem) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data & elem) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data & val) const noexcept override; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  inline void Clear() noexcept override{ BinaryTreeLnk<Data>:: Clear(); }; // Override ClearableContainer member

protected:

  // Auxiliary functions, if necessary!

  // type DataNDelete(argument) specifiers;
  NodeLnk * Delete(NodeLnk *& node, const Data & elem) noexcept;

  NodeLnk * Detach(NodeLnk *& node) noexcept;

  NodeLnk * DetachMin(NodeLnk *& node, NodeLnk *& parent) noexcept;
  NodeLnk * DetachMax(NodeLnk *& node, NodeLnk *& parent) noexcept;

  // type Skip2Left(argument) specifiers;
  // type Skip2Right(argument) specifiers;

  const NodeLnk* const & FindPointerToMin(const NodeLnk * const & node) const noexcept; // Both mutable & unmutable versions
  NodeLnk* & FindPointerToMin(NodeLnk *& node) noexcept;

  const NodeLnk* const & FindPointerToMax(const NodeLnk* const & node) const noexcept; // Both mutable & unmutable versions
  NodeLnk* & FindPointerToMax(NodeLnk* & node) noexcept;

  const NodeLnk * const & FindPointerTo(const NodeLnk * const & node, const Data & elem) const noexcept; // Both mutable & unmutable versions
  NodeLnk *& FindPointerTo(NodeLnk *& node, const Data & elem) noexcept;

  const NodeLnk * const & FindPointerToPredecessor(const NodeLnk * const & node, const Data & elem) const noexcept; // Both mutable & unmutable versions
  NodeLnk* & FindPointerToPredecessor(NodeLnk* & node, const Data & elem) noexcept; 

  const NodeLnk* const & FindPointerToSuccessor(const NodeLnk * const & node, const Data & elem) const noexcept; // Both mutable & unmutable versions
  NodeLnk* & FindPointerToSuccessor(NodeLnk* & node, const Data & elem) noexcept;
   
};

/* ************************************************************************** */

}

#include "bst.cpp"

#endif
