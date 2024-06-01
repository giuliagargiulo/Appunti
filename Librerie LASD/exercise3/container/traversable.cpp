
namespace lasd {

/* ************************************************************************** */
// TRAVERSABLE CONTAINER

 // Specific member function
 // Fold
template <typename Data, typename Accumulator>
using FoldFun = std::function<Accumulator(const Data &, const Accumulator &)>;

template <typename Data>
template <typename Accumulator>
Accumulator TraversableContainer<Data>::Fold(FoldFun<Accumulator> fun , Accumulator acc) const{
  Traverse([fun, &acc](const Data & currData){
    acc = fun(currData, acc);
  });
  return acc;
}

/* ************************************************************************** */

// Specific member function (inherited from TestableContainer)
//Exists()

template <typename Data>
bool TraversableContainer<Data>::Exists(const Data & val) const noexcept{
    bool exists = false;
    Traverse(
        [&val, &exists](const Data & currData){
        if(currData == val)
        exists = true;
     }
    );
    return exists;
}

/* ************************************************************************** */
//PREORDER TRAVERSABLE CONTAINER

// Specific member function
// PreOrderFold
template <typename Data>
template <typename Accumulator>
Accumulator PreOrderTraversableContainer<Data>::PreOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    PreOrderTraverse([&acc, fun](const Data & currData){
        acc = fun(currData, acc);
    });
    return acc;
}

// Specific member function (inherited from TraversableContainer)
template <typename Data>
void PreOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
    PreOrderTraverse(fun);
}

/* ************************************************************************** */

//POSTORDER TRAVERSABLE CONTAINER

// Specific member function
// PostOrderFold
template <typename Data>
template <typename Accumulator>
Accumulator PostOrderTraversableContainer<Data>::PostOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    PostOrderTraverse([&acc, fun](const Data & currData){
        acc = fun(currData, acc);
    });
    return acc;
}

// Specific member function (inherited from TraversableContainer)
template <typename Data>
void PostOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
    PostOrderTraverse(fun);
}

/* ************************************************************************** */

//INORDER TRAVERSABLE CONTAINER

// Specific member function
// InOrderFold
template <typename Data>
template <typename Accumulator>
Accumulator InOrderTraversableContainer<Data>::InOrderFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    InOrderTraverse([fun, &acc](const Data & currData){
        acc = fun(currData, acc);
    });
    return acc;
}

// Specific member function (inherited from TraversableContainer)
template <typename Data>
void InOrderTraversableContainer<Data>::Traverse(TraverseFun fun) const {
    InOrderTraverse(fun);
}

/* ************************************************************************** */

// BREADTH TRAVERSABLE CONTAINER

// Specific member function
// BreadthFold
template <typename Data>
template <typename Accumulator>
Accumulator BreadthTraversableContainer<Data>::BreadthFold(FoldFun<Accumulator> fun, Accumulator acc) const{
    BreadthTraverse([fun, &acc](const Data & currData){
        acc = fun(currData, acc);
    });
    return acc;
}

// Specific member function (inherited from TraversableContainer)
template <typename Data>
void BreadthTraversableContainer<Data>::Traverse(TraverseFun fun) const  {
    BreadthTraverse(fun);
}

/* ************************************************************************** */

}
