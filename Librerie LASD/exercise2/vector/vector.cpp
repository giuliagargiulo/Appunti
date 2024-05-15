
namespace lasd {

/* ************************************************************************** */
// VECTOR

//Constructor Vector(const ulong lenght)
template <typename Data>
Vector<Data>::Vector(const ulong lenght){
  size = lenght;
  array = new Data[size] {};
}

// A Vector obtained from a TraversableContainer
template <typename Data>
Vector<Data>::Vector(const TraversableContainer<Data> & trav_container) :  Vector(trav_container.Size()) {
  ulong i = 0;
  trav_container.Traverse(
    [this, &i](const Data & data){
      array[i++] = data;
      }
  );
}

// A Vector obtained from a MappableContainer
template <typename Data>
Vector<Data>::Vector(MappableContainer<Data> && map_container) :  Vector(map_container.Size()) {
  ulong i = 0;
  map_container.Map(
    [this, &i](Data & data){
      std::swap(array[i++], data);
      }
  );
}

// Copy constructor 
template <typename Data>
Vector<Data>::Vector(const Vector<Data> & other){
  size = other.size;
  array = new Data[size];
  std::copy(other.array, other.array + size, array);
}

// Move constructor 
template <typename Data>
Vector<Data>::Vector(Vector<Data> && other) noexcept{
  std::swap(size, other.size);
  std::swap(array, other.array);
}

 // Destructor
template <typename Data>
Vector<Data>::~Vector(){
  Clear();
}

/* ************************************************************************** */

// Copy assignment 
template <typename Data>
Vector<Data> & Vector<Data>::operator = (const Vector & other){ 
    delete [] array;
    size = other.size;
    array = new Data[other.size];
    std::copy(other.array, other.array + size, array); 
  
  return *this;
}

// Move assignment
template <typename Data>
Vector<Data> & Vector<Data>::operator = (Vector && other) noexcept{
  std::swap(size, other.size);
  std::swap(array, other.array);
  return *this;
}
/* ************************************************************************** */


// Comparison operators
template <typename Data>
bool Vector<Data>::operator == (const Vector & other) const noexcept{
  if(size != other.size)
    return false;

  for(ulong i = 0; i < size; ++i){
    if(array[i] != other[i])
      return false;
  }
  return true;
}

/* ************************************************************************** */

// Specific member function (inherited from ClearableContainer)
// void Clear()
template <typename Data>
void Vector<Data>::Clear() noexcept{
  delete[] array;  
  array = nullptr; 
  size = 0;
}

/* ************************************************************************** */

// Specific member function (inherited from ResizableContainer)
//void Resize(const ulong size)
template <typename Data>
void Vector<Data>::Resize(const ulong new_size){
  if(new_size == 0) 
    Clear();
  else if (size != new_size){
    Data * new_array = new Data[new_size]{}; 
    ulong min_size = (size < new_size) ? size : new_size;  

    for(ulong i = 0; i < min_size; i++){  
      new_array[i] = array[i];
    }

    delete[] array;     
    array = new_array;  
    size = new_size;    
  }
}
/* ************************************************************************** */

// Specific member functions (inherited from LinearContainer)

// operator[] NonMutable
template <typename Data>
const Data & Vector<Data>::operator[] (const ulong index) const{
  if(index < size)
    return array[index];
  else
    throw std::out_of_range("Vector :Index out of range in function operator[]");
}

// operator[]
template <typename Data>
 Data & Vector<Data>::operator[] (const ulong index){
  if(index < size)
    return array[index];  
  else
    throw std::out_of_range("Vector :Index out of range in function operator[]"); 
 }


// Front() NonMutable
template <typename Data>
 const Data & Vector<Data>::Front() const{
  if(size == 0){
    throw std::length_error("Vector is empty in function Front()");
  }
  return array[0];
 }

// Front()
template <typename Data>
Data & Vector<Data>::Front(){
  if(size == 0){
    throw std::length_error("Vector is empty in function Front()");
  }
  return array[0];
 }

// Back() NonMutable
template <typename Data>
const Data & Vector<Data>::Back() const {
 if(size == 0){
    throw std::length_error("Vector is empty in function Front()");
  }
  return array[size-1];
}

// Back()
template <typename Data>
Data & Vector<Data>::Back(){
 if(size == 0){
    throw std::length_error("Vector is empty in function Front()");
  }
  return array[size-1];
}

/* ************************************************************************** */

// SORTABLE VECTOR

// Destructor
template <typename Data>
SortableVector<Data>::~SortableVector(){
  Vector<Data>::Clear();
}

 // Copy assignment
template <typename Data>
SortableVector<Data> & SortableVector<Data>::operator =(const SortableVector & other){
    Vector<Data>::operator =(other);
    return *this;
  }

// Move assignment
template <typename Data>
SortableVector<Data> & SortableVector<Data>::operator =(SortableVector<Data> && other) noexcept {
    Vector<Data>::operator =(std::move(other));
    return *this;
  }

/* ************************************************************************** */

}
