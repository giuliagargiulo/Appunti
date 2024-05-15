
namespace lasd {

/* ************************************************************************** */

// Default constructor
template <typename Data>
StackVec<Data>::StackVec() : Vector<Data>::Vector(STARTING_SIZE){}


// Contructor StackVec(const ulong lenght)
template <typename Data>
StackVec<Data>::StackVec(const TraversableContainer<Data> & trav_container) : Vector<Data>::Vector(trav_container), counter(trav_container.Size()){
    
    if (size < STARTING_SIZE)
        Resize(STARTING_SIZE);
}

// Constructor StackVec( MappableContainer<Data> && map_container)
template <typename Data>
StackVec<Data>::StackVec(MappableContainer<Data> && map_container): Vector<Data>::Vector(std::move(map_container)), counter(map_container.Size()){
   if (size < STARTING_SIZE)
        Resize(STARTING_SIZE);
}

// Copy constructor
template <typename Data>
StackVec<Data>::StackVec(const StackVec<Data> & old_stack): Vector<Data>::Vector(old_stack){
    counter = old_stack.counter;
}

// Move constructor
template <typename Data>
StackVec<Data>::StackVec(StackVec<Data> && old_stack) : Vector<Data>(std::move(old_stack)){
    std::swap(counter, old_stack.counter);
    old_stack.Clear();
}

/* ************************************************************************** */

// Copy assignment

template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data> & other){
    Vector<Data>::operator=(other);
    counter = other.counter;
    return *this;
}

// Move assignment
template <typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec<Data> && other) noexcept{
    Vector<Data>::operator=(std::move(other));
    std::swap(counter, other.counter);
    return *this;
}

template <typename Data>    
bool StackVec<Data>::operator == (const StackVec & other) const noexcept{
    if (counter != other.counter)
        return false;
    
    for (ulong i = 0; i < counter; i++){
        if (array[i] != other.array[i])
            return false;
    }
    return true;
}

template <typename Data>
bool StackVec<Data>::operator != (const StackVec & other) const noexcept{
    return !(*this == other);
}

/* ************************************************************************** */

// Specific member functions (inherited from Stack)

// Top NonMutable
template <typename Data>
 const Data & StackVec<Data>::Top() const{
    if (counter == 0)
        throw std::length_error("Stack is empty in  function Top()");
    return array[counter - 1];
}

// Top 
template <typename Data>
Data & StackVec<Data>::Top(){
    if (counter == 0)
        throw std::length_error("Stack is empty in  function Top()");
    return array[counter - 1];
}

//Pop
template <typename Data>
void StackVec<Data>::Pop(){
    if (counter == 0)
        throw std::length_error("Stack is empty in  function Pop()");
    
    --counter;  // decremento di 1 gli elementi nello stack
    if(counter < (size / RESIZE_DIVISOR))  // se il numero di elementi nello stack è inferiore ad un quarto della dimensione dello stack, ridimensiono lo stack
        Resize(size / RESIZE_FACTOR);      // ridimensiono lo stack (divido la dimensione dello stack per 2)
}

// TopNPop
template <typename Data>
Data StackVec<Data>::TopNPop(){
    if (counter == 0)
        throw std::length_error("Stack is empty in  function TopNPop()");

    Data & topElem = array[counter - 1];
    Pop(); 
    return topElem;
}

// Push copy of the value
template <typename Data>
void StackVec<Data>::Push(const Data & val){
    if (counter == size)
        Resize(size * RESIZE_FACTOR);
    
    array[counter++] = val;
}

// Push move of the value
template <typename Data>
void StackVec<Data>::Push(Data && val){
    if (counter == size)
        Resize(size * RESIZE_FACTOR);
    
    array[counter++] = std::move(val);
}

// Specific member function (inherited from ClearableContainer)
template <typename Data>
void StackVec<Data>::Clear() noexcept{
    counter = 0;
    Resize(STARTING_SIZE);
}

// Specific member function (inherited from ResizableContainer)
template <typename Data>
void StackVec<Data>::Resize(const ulong new_size){
    if(new_size >= STARTING_SIZE)
        Vector<Data>::Resize(new_size);
}

/* ************************************************************************** */

}