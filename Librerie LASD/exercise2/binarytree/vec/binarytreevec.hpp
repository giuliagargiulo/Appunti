
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public MutableBinaryTree<Data>{

private:

protected:

  struct NodeVec: public virtual MutableBinaryTree<Data>::MutableNode {

  private:

  protected:

    const ulong Index() const { return index; }

  public:

    BinaryTreeVec<Data> * bt;
    ulong index;
    Data element {};

    // TODO: costruttori e medoti override (Element, IsLeaf, HasLeftChild.....)
    NodeVec(const Data & elem, ulong i, BinaryTreeVec<Data> * tree);
    NodeVec(Data && elem, ulong i, BinaryTreeVec<Data> * tree) noexcept;
    ~NodeVec();

    NodeVec & operator=(const NodeVec & other);
    NodeVec & operator=(NodeVec && other) noexcept;

    virtual inline const Data & Element() const noexcept override{ return element; }
    virtual inline  Data & Element() noexcept override{ return element; }

    virtual bool HasLeftChild() const noexcept override;
    virtual bool HasRightChild() const noexcept override;

    virtual NodeVec & RightChild() override;
    virtual const NodeVec & RightChild() const override;

    virtual NodeVec& LeftChild() override;
    virtual const NodeVec& LeftChild() const override;

  };
  // un vettore di puntatori a nodi non è la scelta ideale perchè richiede piu memoria, ed è piu difficile da gestire
  // posso fare un vettore di nodi, con all'interno un flag booleano che mi dice se il nodo è presente o no
  Vector<NodeVec*> vecNodes;

public:

  // Default constructor
  BinaryTreeVec(): vecNodes(0){;};

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeVec(const TraversableContainer<Data> & trav_container); // A binary tree obtained from a TraversableContainer
  BinaryTreeVec(MappableContainer<Data> && map_container); // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data> & other);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data> && other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec & operator=(const BinaryTreeVec & other);

  // Move assignment
  BinaryTreeVec & operator=(BinaryTreeVec && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeVec & other) const noexcept{ return BinaryTree<Data>::operator==(other); };
  bool operator!=(const BinaryTreeVec & other) const noexcept{ return BinaryTree<Data>::operator!=(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  virtual const NodeVec & Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  virtual NodeVec & Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  virtual void Clear() noexcept override;// type Clear() specifiers; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  using typename BreadthTraversableContainer<Data>::TraverseFun;
  void BreadthTraverse(TraverseFun fun) const override; // Override BreadthTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)

  using typename BreadthMappableContainer<Data>::MapFun;
  void BreadthMap(MapFun fun) override; // Override BreadthMappableContainer member

protected:

  // Auxiliary functions, if necessary!

};

/* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
