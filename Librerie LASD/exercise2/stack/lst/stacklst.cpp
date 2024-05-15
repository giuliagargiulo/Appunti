
namespace lasd {

/* ************************************************************************** */


// Copy assignment
template <typename Data>
StackLst<Data> & StackLst<Data>::operator = (const StackLst & other){
    List<Data>::operator=(other);
    return *this;
}

// Move assignment
template <typename Data>
StackLst<Data> & StackLst<Data>::operator = (StackLst && other) noexcept{
    List<Data>::operator=(std::move(other));
    return *this;
}

/* ************************************************************************** */
// Specific member functions (inherited from Stack)

// const Data & Top() const NonMutable
template <typename Data>
const Data & StackLst<Data>::Top() const{
  if (Empty()) 
    throw std::length_error("Stack is empty in function Top()");
  return List<Data>::Front();
}

// Data & Top() Mutable
template <typename Data>
Data & StackLst<Data>::Top(){
  if (Empty()) 
    throw std::length_error("Stack is empty in function Top()");
  return List<Data>::Front();
}

//void Pop() 
template <typename Data>
void StackLst<Data>::Pop(){
  if (Empty()) 
    throw std::length_error("Stack is empty in function Pop()");
  List<Data>::RemoveFromFront();
}

// void Data & TopNPop()
template <typename Data>
Data StackLst<Data>::TopNPop(){
  if (Empty()) 
    throw std::length_error("Stack is empty in function TopNPop()");
  return List<Data>::FrontNRemove();
}

// void Push(const Data & val)
template <typename Data>
void StackLst<Data>::Push(const Data & val){
  List<Data>::InsertAtFront(val);
}
//void Push(Data && val)
template <typename Data>
void StackLst<Data>::Push(Data && val){
  List<Data>::InsertAtFront(std::move(val));
}

/* ************************************************************************** */

}
