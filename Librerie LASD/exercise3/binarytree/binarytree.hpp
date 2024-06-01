
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/mappable.hpp"

#include "../iterator/iterator.hpp"

#include "../stack/vec/stackvec.hpp"
// #include "../stack/lst/stacklst.hpp"
#include "../queue/vec/queuevec.hpp"
// #include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : public virtual PreOrderTraversableContainer<Data>, public virtual PostOrderTraversableContainer<Data>,
                   public virtual InOrderTraversableContainer<Data>, public virtual BreadthTraversableContainer<Data>{

private:

  // ...

protected:

  using Container::size;

public:

  struct Node {

  protected:

    // Comparison operators
    bool operator==(const Node& other) const noexcept { return (this->Element()==other.Element()); }; // Comparison of abstract types is possible, but is not visible.
    inline bool operator!=(const Node& other) const noexcept { return (!(this->operator==(other))); }; // Comparison of abstract types is possible, but is not visible.

  public:

    friend class BinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() = default;

    /* ********************************************************************** */

    // Copy assignment
    Node & operator = (const Node & other) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    Node & operator = (Node && other) noexcept = delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions

    virtual const Data & Element() const noexcept = 0; // Immutable access to the element (concrete function should not throw exceptions)

    virtual bool IsLeaf() const noexcept { return (!HasLeftChild() && !HasRightChild());}; // (concrete function should not throw exceptions)
    virtual bool HasLeftChild() const noexcept = 0; // (concrete function should not throw exceptions)
    virtual bool HasRightChild() const noexcept = 0; // (concrete function should not throw exceptions)

    virtual const Node & LeftChild() const = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual const Node & RightChild() const = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree & operator = (const BinaryTree & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  BinaryTree & operator = (BinaryTree && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BinaryTree & other) const noexcept; // Comparison of abstract binary tree is possible.
  bool operator != (const BinaryTree & other) const noexcept{ return !operator ==(other); }; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual const Node & Root() const = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  virtual inline void Traverse(TraverseFun fun) const override{ return PreOrderTraverse(fun); }; // Override TraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  virtual void PreOrderTraverse(TraverseFun fun) const override;  // Override PreOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  virtual void PostOrderTraverse(TraverseFun fun) const override; // Override PostOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderTraversableContainer)

  virtual void InOrderTraverse(TraverseFun fun) const override; // Override InOrderTraversableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthTraversableContainer)

  virtual void BreadthTraverse(TraverseFun fun) const override; // Override BreadthTraversableContainer member

protected:

  void PreOrderTraverseAux(TraverseFun fun, const Node & root) const;
  void PostOrderTraverseAux(TraverseFun fun, const Node & root) const;
  void InOrderTraverseAux(TraverseFun fun, const Node & root) const;

};

/* ************************************************************************** */

template <typename Data>
class MutableBinaryTree: public virtual ClearableContainer, public virtual BinaryTree<Data>,
                         public virtual PreOrderMappableContainer<Data>, public virtual PostOrderMappableContainer<Data>,
                         public virtual InOrderMappableContainer<Data>, public virtual BreadthMappableContainer<Data>{

private:

  // ...

protected:

  // ...

public:

  struct MutableNode : public virtual BinaryTree<Data>::Node{

    friend class MutableBinaryTree<Data>;

    /* ********************************************************************** */

    // Destructor
     ~MutableNode() = default;

    /* ********************************************************************** */

    // Copy assignment
    MutableNode & operator =(const MutableNode & other) = delete; // Copy assignment of abstract types is not possible.

    // Move assignment
    MutableNode & operator =(MutableNode && other) noexcept = delete; // Move assignment of abstract types is not possible.

    /* ********************************************************************** */

    // Specific member functions
    using BinaryTree<Data>::Node::Element;
    virtual Data & Element() noexcept = 0; // Mutable access to the element (concrete function should not throw exceptions)

    using BinaryTree<Data>::Node::LeftChild;
    using BinaryTree<Data>::Node::RightChild;
    virtual MutableNode & LeftChild() = 0; // (concrete function must throw std::out_of_range when not existent)
    virtual MutableNode & RightChild() = 0; // (concrete function must throw std::out_of_range when not existent)

  };

  /* ************************************************************************ */

  // Destructor
   virtual ~MutableBinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  MutableBinaryTree & operator = (const MutableBinaryTree & other) = delete; // Copy assignment of abstract types is not possible.

  // Move assignment
  MutableBinaryTree & operator = (MutableBinaryTree && other) noexcept = delete; // Move assignment of abstract types is not possible.

  /* ************************************************************************ */

  // Specific member functions

  using BinaryTree<Data>::Root;
  virtual MutableNode & Root() = 0; // (concrete function must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  virtual void Map(MapFun fun) override { return PreOrderMap(fun); }; // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  virtual void PreOrderMap(MapFun fun) override; // Override PreOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  virtual void PostOrderMap(MapFun fun) override; // Override PostOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from InOrderMappableContainer)

  virtual void InOrderMap(MapFun fun) override; // Override InOrderMappableContainer member

  /* ************************************************************************ */

  // Specific member function (inherited from BreadthMappableContainer)
  virtual void BreadthMap(MapFun fun) override; // Override BreadthMappableContainer member

protected:

  void PreOrderMapAux(MapFun fun, MutableNode & root);
  void PostOrderMapAux(MapFun fun, MutableNode & root);
  void InOrderMapAux(MapFun fun, MutableNode & root);

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderIterator : public virtual ForwardIterator<Data>, public virtual ResettableIterator<Data>{

private:

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * current = nullptr;
  StackVec<const typename BinaryTree<Data>::Node *> stack;

public:

  // Specific constructors
  BTPreOrderIterator(const BinaryTree<Data> & bt); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderIterator(const BTPreOrderIterator & other);

  // Move constructor
  BTPreOrderIterator(BTPreOrderIterator && other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTPreOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderIterator & operator = (const BTPreOrderIterator & other);

  // Move assignment
  BTPreOrderIterator & operator = (BTPreOrderIterator && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTPreOrderIterator & other) const noexcept;
  bool operator != (const BTPreOrderIterator & other) const noexcept { return !operator ==(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data& operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPreOrderIterator<Data> & operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override;  // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPreOrderMutableIterator: public virtual MutableIterator<Data>, public virtual  BTPreOrderIterator<Data>{

private:

protected:

public:

  // Specific constructors
  BTPreOrderMutableIterator(MutableBinaryTree<Data> & mbt) : BTPreOrderIterator<Data>(mbt){;}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPreOrderMutableIterator(const BTPreOrderMutableIterator & other) : BTPreOrderIterator<Data>(other){;};

  // Move constructor
  BTPreOrderMutableIterator(BTPreOrderMutableIterator && other) noexcept: BTPreOrderIterator<Data>(std::move(other)){;};

  /* ************************************************************************ */

  // Destructor
   virtual ~BTPreOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPreOrderMutableIterator & operator=(const BTPreOrderMutableIterator & other);

  // Move assignment
  BTPreOrderMutableIterator & operator=(BTPreOrderMutableIterator && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool  operator == (const BTPreOrderMutableIterator & other) const noexcept{ return BTPreOrderIterator<Data>::operator ==(other);}
  bool  operator != (const BTPreOrderMutableIterator & other) const noexcept{ return !operator ==(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data  & operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderIterator : public virtual ForwardIterator<Data>, public virtual ResettableIterator<Data>{

private:

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * current = nullptr;
  StackVec<const typename BinaryTree<Data>::Node *> stack;

 const typename BinaryTree<Data>::Node * FindDeepestLeft(const typename BinaryTree<Data>::Node * node);

public:

  // Specific constructors
  BTPostOrderIterator(const BinaryTree<Data> & bt); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderIterator(const BTPostOrderIterator & other);

  // Move constructor
  BTPostOrderIterator(BTPostOrderIterator && other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTPostOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderIterator & operator = (const BTPostOrderIterator & other);

  // Move assignment
  BTPostOrderIterator & operator = (BTPostOrderIterator && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTPostOrderIterator & other) const noexcept;
  bool operator != (const BTPostOrderIterator & other) const noexcept { return !operator ==(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override;  // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override;  // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTPostOrderIterator<Data> & operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTPostOrderMutableIterator : public virtual MutableIterator<Data>, public virtual BTPostOrderIterator<Data>{

private:

protected:

public:

  // Specific constructors
  BTPostOrderMutableIterator(const MutableBinaryTree<Data> & mbt) : BTPostOrderIterator<Data>(mbt){;}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTPostOrderMutableIterator(const BTPostOrderMutableIterator<Data> & other): BTPostOrderIterator<Data>(other){;}

  // Move constructor
  BTPostOrderMutableIterator(BTPostOrderMutableIterator<Data> && other) noexcept : BTPostOrderIterator<Data>(std::move(other)){;};

  /* ************************************************************************ */

  // Destructor
   ~BTPostOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTPostOrderMutableIterator & operator = (const BTPostOrderMutableIterator & other);

  // Move assignment
  BTPostOrderMutableIterator & operator = (BTPostOrderMutableIterator && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTPostOrderMutableIterator & other) const noexcept { return BTPostOrderIterator<Data>::operator ==(other);};
  bool operator != (const BTPostOrderMutableIterator & other) const noexcept { return !operator ==(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data & operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderIterator : public virtual ForwardIterator<Data>, public virtual ResettableIterator<Data>{

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * current = nullptr;
  StackVec<const typename BinaryTree<Data>::Node *> stack;

  const typename BinaryTree<Data>::Node * FindDeepestLeftInOrder(const typename BinaryTree<Data>::Node * node);

public:

  // Specific constructors
  BTInOrderIterator(const BinaryTree<Data> & bt); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderIterator(const BTInOrderIterator & other);

  // Move constructor
  BTInOrderIterator(BTInOrderIterator && other) noexcept;

  /* ************************************************************************ */

  // Destructor
   ~BTInOrderIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderIterator & operator = (const BTInOrderIterator & other);

  // Move assignment
  BTInOrderIterator & operator = (BTInOrderIterator && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTInOrderIterator & other) const noexcept;
  bool operator != (const BTInOrderIterator & other) const noexcept { return !operator ==(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override; // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTInOrderIterator<Data> & operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override; // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTInOrderMutableIterator : public virtual MutableIterator<Data>, public virtual BTInOrderIterator<Data>{

private:

  // ...

protected:

  

public:

  // Specific constructors
  BTInOrderMutableIterator(const MutableBinaryTree<Data> & mbt) : BTInOrderIterator<Data>(mbt){;}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTInOrderMutableIterator(const BTInOrderMutableIterator & other) : BTInOrderIterator<Data>(other){;}

  // Move constructor
  BTInOrderMutableIterator(BTInOrderMutableIterator && other) noexcept : BTInOrderIterator<Data>(std::move(other)){;}

  /* ************************************************************************ */

  // Destructor
  ~BTInOrderMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTInOrderMutableIterator & operator = (const BTInOrderMutableIterator & other);

  // Move assignment
  BTInOrderMutableIterator & operator = (BTInOrderMutableIterator && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTInOrderMutableIterator & other) const noexcept { return BTInOrderIterator<Data>::operator ==(other);};
  bool operator != (const BTInOrderMutableIterator & other) const noexcept { return !operator ==(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data & operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthIterator: public virtual ForwardIterator<Data>, public virtual ResettableIterator<Data>{

private:

  // ...

protected:

  const typename BinaryTree<Data>::Node * root = nullptr;
  const typename BinaryTree<Data>::Node * current = nullptr;
  QueueVec<const typename BinaryTree<Data>::Node *> queue;

public:

  // Specific constructors
  BTBreadthIterator(const BinaryTree<Data> & bt); // An iterator over a given binary tree

  /* ************************************************************************ */

  // Copy constructor
  BTBreadthIterator(const BTBreadthIterator & other);

  // Move constructor
  BTBreadthIterator(BTBreadthIterator && other) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthIterator & operator = (const BTBreadthIterator & other);

  // Move assignment
  BTBreadthIterator & operator = (BTBreadthIterator && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTBreadthIterator & other) const noexcept;
  bool operator != (const BTBreadthIterator & other) const noexcept { return !operator ==(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from Iterator)

  const Data & operator*() const override; // (throw std::out_of_range when terminated)

  bool Terminated() const noexcept override;  // (should not throw exceptions)

  /* ************************************************************************ */

  // Specific member functions (inherited from ForwardIterator)

  BTBreadthIterator<Data> & operator++() override; // (throw std::out_of_range when terminated)

  /* ************************************************************************ */

  // Specific member functions (inherited from ResettableIterator)

  void Reset() noexcept override;  // (should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class BTBreadthMutableIterator : public virtual MutableIterator<Data>, public virtual BTBreadthIterator<Data>{

private:

  // ...

protected:

  // ...

public:

  // Specific constructors
  BTBreadthMutableIterator(const MutableBinaryTree<Data> & mbt) : BTBreadthIterator<Data>(mbt){;}; // An iterator over a given mutable binary tree

  /* ************************************************************************ */
  // Copy constructor
  BTBreadthMutableIterator(const BTBreadthMutableIterator & other): BTBreadthIterator<Data>(other){;}

  // Move constructor
  BTBreadthMutableIterator(BTBreadthMutableIterator && other) noexcept : BTBreadthIterator<Data>(std::move(other)){;}

  /* ************************************************************************ */

  // Destructor
  ~BTBreadthMutableIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  BTBreadthMutableIterator & operator = (const BTBreadthMutableIterator & other);

  // Move assignment
  BTBreadthMutableIterator & operator = (BTBreadthMutableIterator && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const BTBreadthMutableIterator & other) const noexcept { return BTBreadthIterator<Data>::operator ==(other);};
  bool operator != (const BTBreadthMutableIterator & other) const noexcept { return !operator ==(other); };

  /* ************************************************************************ */

  // Specific member functions (inherited from MutableIterator)

  Data & operator*() override; // (throw std::out_of_range when terminated)

};

/* ************************************************************************** */

}

#include "binarytree.cpp"

#endif
