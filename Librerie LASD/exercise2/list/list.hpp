
#ifndef LIST_HPP
#define LIST_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class List: virtual public ClearableContainer, virtual public LinearContainer<Data>, virtual public DictionaryContainer<Data> {

private:

protected:

  using Container::size;


  struct Node { 

    Data val {};
    Node * next = nullptr;

    /* ********************************************************************** */

    // Specific constructors
    Node(const Data & new_val);
    Node(Data && new_val) noexcept;

    /* ********************************************************************** */

    // Copy constructor
    Node(const Node & new_node);

    // Move constructor
    Node(Node && new_node) noexcept;

    /* ********************************************************************** */

    // Destructor
    virtual ~Node() { delete next; };

    /* ********************************************************************** */

    // Comparison operators
    inline bool operator == (const Node & other){ return other.val == val; };
    inline bool operator != (const Node & other){ return other.val != val; };

    /* ********************************************************************** */

    // Specific member functions

};

  Node * head = nullptr;
  Node * tail = nullptr;

public:

  // Default constructor
  List() = default;
  /* ************************************************************************ */

  // Specific constructor
  List(const TraversableContainer<Data> & trav_container); // A list obtained from a TraversableContainer
  List(MappableContainer<Data> && map_container); // A list obtained from a MappableContainer

  /* ************************************************************************ */

  // Copy constructor
  List(const List & other);

  // Move constructor
  List(List && other) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~List() { Clear(); };

  /* ************************************************************************ */

  // Copy assignment 
  List<Data> & operator=(const List & other);

  // Move assignment
  List<Data> & operator = (List && other) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator == (const List & other) const noexcept;
  bool operator != (const List & other) const noexcept{ return !operator ==(other);};

  /* ************************************************************************ */

  // Specific member functions 

  void InsertAtFront(const Data & new_element); // Copy of the value
  void InsertAtFront(Data && new_element); // Move of the value
  void RemoveFromFront(); // (must throw std::length_error when empty)
  Data FrontNRemove(); // (must throw std::length_error when empty)

  void InsertAtBack(const Data & new_element); // Copy of the value
  void InsertAtBack(Data && new_element);  // Move of the value

  // Aggiunta io
  void RemoveFromBack();  // Remove the last element of a list (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from ClearableContainer)

  void Clear() noexcept override; // Override ClearableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data & new_element) override; // Copy of the value
  bool Insert(Data && new_element) override; // Move of the value
  bool Remove(const Data & element) override;

  /* ************************************************************************ */

  // Specific member functions (inherited from LinearContainer)

  const Data & operator [] (const ulong index) const override;  // Override (NonMutable) LinearContainer member (must throw std::out_of_range when out of range)
  Data & operator [] (const ulong index)  override;  // Override (Mutable) LinearContainer member (must throw std::out_of_range when out of range)

  const Data & Front() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data & Front() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  const Data & Back() const override; // Override (NonMutable) LinearContainer member (must throw std::length_error when empty)
  Data & Back() override; // Override (Mutable) LinearContainer member (must throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member function (inherited from TraversableContainer)

  using typename TraversableContainer<Data>::TraverseFun;

  inline void Traverse(TraverseFun fun) const override{    // Override TraversableContainer member
    PreOrderTraverse(fun, head); 
  }

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderTraversableContainer)

  inline void PreOrderTraverse(TraverseFun fun) const override{   // Override PreOrderTraversableContainer member
    PreOrderTraverse(fun, head); 
  } 

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderTraversableContainer)

  inline void PostOrderTraverse(TraverseFun fun) const override{  // Override PostOrderTraversableContainer member
    PostOrderTraverse(fun, head); 
  }
  /* ************************************************************************ */

  // Specific member function (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFun;

  void Map(MapFun fun) override{   // Override MappableContainer member
    PreOrderMap(fun, head);
  } 

  /* ************************************************************************ */

  // Specific member function (inherited from PreOrderMappableContainer)

  void PreOrderMap(MapFun fun) override{  // Override PreOrderMappableContainer member
    PreOrderMap(fun, head);
  } 

  /* ************************************************************************ */

  // Specific member function (inherited from PostOrderMappableContainer)

  void PostOrderMap(MapFun fun) override{  // Override PostOrderMappableContainer member
    PostOrderMap(fun, head);
  } 

protected:

  void PreOrderTraverse(TraverseFun fun, Node * tmp) const;
  void PostOrderTraverse(TraverseFun fun, Node * tmp) const;
  void PreOrderMap(MapFun fun, Node * tmp);
  void PostOrderMap(MapFun fun, Node * tmp);
  using LinearContainer<Data>::Exists;
};

/* ************************************************************************** */

}

#include "list.cpp"

#endif
