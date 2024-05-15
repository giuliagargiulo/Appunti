
namespace lasd {

/* ************************** */
// Constructor
template <typename Data>
QueueVec<Data>::QueueVec() : Vector<Data>(STARTING_SIZE){}

// Specific constructor 
// A stack obtained from a TraversableContainer
template <typename Data>
QueueVec<Data>::QueueVec(const TraversableContainer<Data> & trav_container) : Vector<Data>(trav_container), tail(trav_container.Size()){
    Vector<Data>::Resize(trav_container.Size() * RESIZE_FACTOR);
}

// A stack obtained from a MappableContainer
template <typename Data>
QueueVec<Data>::QueueVec(MappableContainer<Data> && map_container) : Vector<Data>(std::move(map_container)), tail(map_container.Size()){
    Vector<Data>::Resize(map_container.Size() * RESIZE_FACTOR);
}


// Copy constructor
template <typename Data>
QueueVec<Data>::QueueVec(const QueueVec & other) : Vector<Data>(other) {
    head=other.head;
    tail=other.tail;
}

// Move constructor
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec && other) noexcept : Vector<Data>(std::move(other)) {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
}

// Copy assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data> & other) {
    Vector<Data>::operator=(other);
    head = other.head;
    tail = other.tail;
    return *this;
}

// Move assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& other) noexcept {
    Vector<Data>::operator=(std::move(other));
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    return *this;
}

 // Comparison operators
template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec & other) const {

    if(Size()!=other.Size())
        return false;

    for(ulong i=0; i<Size(); i++){
        if(array[(i+head)%size] != other[(i+other.head)%other.size])
            return false;
    }
    return true;
}

/* ************************** */

// Specific member functions (inherited from Queue)
// Head() NonMutable
template <typename Data>
const Data & QueueVec<Data>::Head() const {
    if (head == tail)
        throw std::length_error("Queue is empty in function Head()");
    return array[head];
}

// Head ()
template <typename Data>
Data & QueueVec<Data>::Head() {
    if (head == tail)
        throw std::length_error("Queue is empty in function Head()");
    return array[head];
}

// Dequeue()
template <typename Data>
void QueueVec<Data>::Dequeue() {
    if (head == tail)
        throw std::length_error("Queue is empty in function Dequeue()");
    Reduce();
    head = (head+1)%size;
}

// HeadNDequeue()
template <typename Data>
Data QueueVec<Data>::HeadNDequeue() {
    if (head == tail)
        throw std::length_error("Queue is empty in function HeadNDequeue()");
    Reduce();
    head = (head+1)%size;
    return array[((head-1+size)%size)];
}

// Enqueue() copy of the value
template <typename Data>
void QueueVec<Data>::Enqueue(const Data & val){
    Expand();
    array[tail] = val;
    tail = (tail+1)%size;
}

// Enqueue() move of the value
template <typename Data>
void QueueVec<Data>::Enqueue(Data && val) noexcept {
    Expand();
    array[tail] = std::move(val);
    tail = (tail+1)%size;
}

// Specific member function (inherited from ClearableContainer)
// Clear()
template <typename Data>
void QueueVec<Data>::Clear() noexcept {
    head = tail = 0;
    Vector<Data>::Resize(STARTING_SIZE);
}

// Auxiliary member functions

// Reduce()
template <typename Data>
void QueueVec<Data>::Reduce(){
    if (Size()< STARTING_SIZE)
        return;
    if (Size() == size/ RESIZE_DIVISOR)
        Resize(size/RESIZE_FACTOR);
}

// Expand()
template <typename Data>
void QueueVec<Data>::Expand(){
    if (Size() == size-1)
        Resize(size*RESIZE_FACTOR);
}

// Resize()
template <typename Data>
void QueueVec<Data>::Resize(const ulong newsize){
    Data * new_array = new Data[newsize]{};

    ulong max_size = (Size() <= newsize) ? Size() : newsize;
    
    for(ulong i = 0; i<max_size; i++)
        new_array[i] = array[(head+i)%size];
    
    delete [] array;
    array = new_array;
    tail = Size();
    head = 0;
    size = newsize;
}

/* ************************** */

}