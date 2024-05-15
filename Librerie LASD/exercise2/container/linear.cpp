
#include <stdexcept>
namespace lasd {

/* ************************************************************************** */

// LINEAR CONTAINER
// Comparison operators
template <typename Data>
bool LinearContainer<Data>::operator== (const LinearContainer<Data> & other) const noexcept{
  if(size != other.size)
    return false;

  for(ulong i = 0; i < size; i++)
    if(operator[](i) != other[i])
      return false;
  return true;
}

 // Specific member functions
// Front() NonMutable
template <typename Data>
const Data & LinearContainer<Data>::Front() const{
  if(this->Empty())
    throw std::length_error("Linear Container is empty in function Front()");
  return (*this)[0];
}

// Front()
template <typename Data>
Data & LinearContainer<Data>::Front(){
  if(this->Empty())
    throw std::length_error("Linear Container is empty in function Front()");
  return (*this)[0];
}

// Back() NonMutable
template <typename Data>
const Data & LinearContainer<Data>::Back() const{
  if(this->Empty())
    throw std::length_error("Linear Container is empty in function Back()");
  return (*this)[size-1];
}

// Back()
template <typename Data>
Data & LinearContainer<Data>::Back(){
  if(this->Empty())
    throw std::length_error("Linear Container is empty in function Back()");
  return (*this)[size-1];
}

// Specific member function (inherited from TraversableContainer)
// Traverse
template <typename Data>
void LinearContainer<Data>::Traverse(TraverseFun fun) const{
    PreOrderTraverse(fun);
}

// PreOrderTraverse
template <typename Data>
void LinearContainer<Data>::PreOrderTraverse(TraverseFun fun) const{
  for(ulong i = 0; i < size; ++i)
    fun((*this)[i]);
}

// PostOrderTraverse
template <typename Data>
void LinearContainer<Data>::PostOrderTraverse(TraverseFun fun)const{
  ulong i = size;
  while(i > 0)
    fun(operator[](--i));
}


/* ************************************************************************** */

// Specific member function (inherited from MappableContainer)
// Map
template <typename Data>
void LinearContainer<Data>::Map(MapFun fun) {
    PreOrderMap(fun);
}

// PreOrderMap
template <typename Data>
void LinearContainer<Data>::PreOrderMap(MapFun fun) {
  for(ulong i = 0; i < size; ++i)
    fun((*this)[i]);
}

// PostOrderMap
template <typename Data>
void LinearContainer<Data>::PostOrderMap(MapFun fun) {
  ulong i = size;
  while(i > 0)
    fun(operator[](--i));
}

/* ************************************************************************** */

// SORTABLE LINEAR CONTAINER
// Sort()
template <typename Data>
void SortableLinearContainer<Data>::Sort() noexcept{
  if(size > 1)
    QuickSort(0, size-1);
}

// QuickSort
template <typename Data>
void SortableLinearContainer<Data>::QuickSort(ulong p, ulong r){
  if(p < r){
    ulong q = Partition(p, r);
    QuickSort(p, q);
    QuickSort(q+1, r);
  }
}

// Partition
template <typename Data>
ulong SortableLinearContainer<Data>::Partition(ulong p, ulong r){
  Data x = (*this)[p];
  ulong i = p - 1;
  ulong j = r + 1;
  do{
    do{
      j--;
      }while((*this)[j] > x);

    do{
      i++;
      }while((*this)[i] < x);

    if(i < j)
      std::swap((*this)[i], (*this)[j]);
      
    }while(i < j);
    return j;
}

/* ************************************************************************** */

}
