
namespace lasd {

/* ************************************************************************** */

// Copy assignment
template <typename Data>
QueueLst<Data> & QueueLst<Data>::operator = (const QueueLst & other){
    List<Data>::operator=(other);
    return *this;
}

// Move assignment
template <typename Data>
QueueLst<Data> & QueueLst<Data>::operator = (QueueLst&& other) noexcept{
    List<Data>::operator=(std::move(other));
    return *this;
}
/* ************************************************************************** */

// Specific member functions (inherited from Queue)

// Head() NotMutable
template <typename Data>
const Data & QueueLst<Data>::Head() const{
  if (Empty()) 
    throw std::length_error("Queue is empty in function Head()");
  return List<Data>::Front();
}

// Head()
template <typename Data>
Data & QueueLst<Data>::Head(){
  if (Empty()) 
    throw std::length_error("Queue is empty in function Head()");
  return List<Data>::Front();
}

// Dequeue()
template <typename Data>
void QueueLst<Data>::Dequeue(){
  if (Empty()) 
    throw std::length_error("Queue is empty in function Dequeue()");
  List<Data>::RemoveFromFront();
}

// HeadNDequeue()
template <typename Data>
Data QueueLst<Data>::HeadNDequeue(){
  if (Empty()) 
    throw std::length_error("Queue is empty in function HeadNDequeue()");
  return List<Data>::FrontNRemove();
}

// Enqueue() copy of the value
template <typename Data>
void QueueLst<Data>::Enqueue(const Data & val){
  List<Data>::InsertAtBack(val);
}

// Enqueue() move of the value
template <typename Data>
void QueueLst<Data>::Enqueue(Data && val) noexcept{
  List<Data>::InsertAtBack(std::move(val));
}

/* ************************************************************************** */

}
