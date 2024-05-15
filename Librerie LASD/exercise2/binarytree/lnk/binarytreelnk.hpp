
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public MutableBinaryTree<Data> {

private:

  // ...

protected:

  // using BinaryTree<Data>::???;

  using Container::size;

  // ...

  struct NodeLnk : public virtual MutableBinaryTree<Data>::MutableNode { // serve public?? 
  
  friend class BinaryTreeLnk<Data>;

  private:

  protected:
    
  public:

    Data element {};
    NodeLnk * left = nullptr;
    NodeLnk * right = nullptr;

    // TODO: costruttori e medoti override (Element, IsLeaf, HasLeftChild.....)
  
    // Constructors
    NodeLnk(const Data & newElement){ element = newElement;};
    NodeLnk(Data && newElement) noexcept{std::swap(element, newElement);};


    // Copy constructor
    NodeLnk(const NodeLnk & other);
  
    // Move constructor
    NodeLnk(NodeLnk && other) noexcept;
  
    //Destructor
    ~NodeLnk();

    // Specific member functions
    virtual const Data & Element() const noexcept override{ return element;};
    virtual Data & Element() noexcept override{ return element;};

    virtual bool HasLeftChild() const noexcept override{ return left!= nullptr;};
    virtual bool HasRightChild() const noexcept override{ return right!= nullptr;};

    virtual const NodeLnk & LeftChild() const override;
    virtual NodeLnk & LeftChild() override;

    virtual const NodeLnk & RightChild() const override;
    virtual NodeLnk & RightChild() override;

  };

  NodeLnk * root = nullptr;


public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const TraversableContainer<Data> & trav_container); // A binary tree obtained from a TraversableContainer
  BinaryTreeLnk(MappableContainer<Data> && map_container); // A binary tree obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data> & other);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data> && other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk(); 

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk & operator=(const BinaryTreeLnk & other);

  // Move assignment
  BinaryTreeLnk & operator=(BinaryTreeLnk && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk & other) const noexcept{ return BinaryTree<Data>::operator==(other);}
  bool operator!=(const BinaryTreeLnk & other) const noexcept{ return BinaryTree<Data>::operator!=(other);};

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  const NodeLnk & Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MutableBinaryTree)

  NodeLnk & Root() override; // Override MutableBinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member


  // Auxiliar functions
  NodeLnk * Copy(NodeLnk *& currentNode, const NodeLnk & other);
};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
