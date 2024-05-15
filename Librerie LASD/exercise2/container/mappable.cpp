
namespace lasd {

/* ************************************************************************** */
// MAPPABLE CONTAINER
// ...

// PREORDER MAPPABLE CONTAINER
// Map()
template <typename Data>
void PreOrderMappableContainer<Data>::Map(MapFun fun) {
  PreOrderMap(fun);
}

// POSTORDER MAPPABLE CONTAINER
// Map()
template <typename Data>
void PostOrderMappableContainer<Data>::Map(MapFun fun) {
  PostOrderMap(fun);
}

// INORDER MAPPABLE CONTAINER
// Map()
template <typename Data>
void InOrderMappableContainer<Data>::Map(MapFun fun) {
  InOrderMap(fun);
}

// INORDER MAPPABLE CONTAINER
// Map()
template <typename Data>
void BreadthMappableContainer<Data>::Map(MapFun fun) {
  BreadthMap(fun);
}

/* ************************************************************************** */

}
