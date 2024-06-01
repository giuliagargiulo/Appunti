
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize) : HashTable<Data>() {
  tableSize = NextPow(newSize);
  table = new Data[tableSize]{};
  flags = new Flag[tableSize]{};
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const TraversableContainer<Data> & trav_container): HashTableOpnAdr(trav_container.Size()*2) {
  InsertAll(trav_container);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, const TraversableContainer<Data> & trav_container): HashTableOpnAdr(newSize) {
  InsertAll(trav_container);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(MappableContainer<Data> && map_container) noexcept: HashTableOpnAdr(map_container.Size()*2) {
  InsertAll(std::move(map_container));
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong newSize, MappableContainer<Data> && map_container) noexcept: HashTableOpnAdr(newSize) {
  InsertAll(std::move(map_container));
}

// Copy Constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data> & other) : HashTable<Data>(other) {    
  table = new Data[tableSize]{};
  flags = new Flag[tableSize]{};
  for(ulong i = 0; i < tableSize; i++) {
    table[i] = other.table[i];
    flags[i] = other.flags[i];
  }
}

// Move Constructor
template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr && other) noexcept : HashTable<Data>(std::move(other)) {
  std::swap(table, other.table);
  std::swap(flags, other.flags);
}

// Copy Assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr & other) {
  HashTable<Data>::operator=(other);
  delete[] table;
  delete[] flags;
  table = new Data[tableSize]{};
  flags = new Flag[tableSize]{};
  for(ulong i = 0; i < tableSize; i++) {
    table[i] = other.table[i];
    flags[i] = other.flags[i];
  }
  return *this;
}

//Move Assignment
template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr && other) noexcept {
  HashTable<Data>::operator=(std::move(other));
  std::swap(table, other.table);
  std::swap(flags, other.flags);
  return *this;
}

// Comparison operators
template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr & other) const noexcept {
    if (size != other.Size()) 
        return false;
    for(ulong i=0; i<tableSize; i++){
        if(flags[i] == occupied){ 
            if(!other.Exists(table[i]))
                return false;
        }
    }
  return true;
}

/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

// Insert (Copy of the value)
template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data & val) {
  ulong probing = 0;
  if((size*2) >= tableSize)
    Resize(tableSize*2);
  ulong index = FindEmpty(probing, val);
  if(flags[index] != occupied){
    table[index] = val;
    size++;
    if(flags[index] == deleted) 
        deletedElem--;
    flags[index] = occupied;
    return !RemoveElem(++probing, table[index]);   
  }
    probing = 0;
    return false;
}

// Insert (Move of the value)
template <typename Data>
bool HashTableOpnAdr<Data>::Insert(Data && val) noexcept {
  ulong probing = 0;
  if(size*2 >= tableSize)
    Resize(tableSize*2);
  ulong index = FindEmpty(probing, val);
  if(flags[index] != occupied){
    table[index] = std::move(val);
    size++;
    if(flags[index] == deleted) // se l'elemento è stato cancellato
        deletedElem--;
    flags[index] = occupied;
    return !RemoveElem(++probing, table[index]);   
  }
    probing = 0;
    return false;
}

// Remove
template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data & val) {
  ulong probing = 0;
  return RemoveElem(probing, val);
}

// Exists
template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data & val) const noexcept {
  ulong probing = 0;
  ulong index = HashKey(Hashable<Data>()(val));
  return Find(index, probing, val);
}

// Resize
template <typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong newSize) {
  if(newSize == 0){
    Clear();
    return;
  }

  ulong nextSize;
  if(newSize < size)
    nextSize = NextPow(size * 2);
  else
    nextSize = NextPow(newSize);

  Data* newTable = new Data[nextSize]{};
  Flag * newFlags = new Flag[nextSize]{};

  std::swap(tableSize, nextSize);
  std::swap(newTable, table);
  std::swap(flags, newFlags);

  size = 0;
  deletedElem = 0;

  for(ulong i = 0; i < nextSize; i++){
      if(newFlags[i] == occupied)
          Insert(newTable[i]);
  }
  delete[] newTable;
  delete[] newFlags;
}


/* ************************************************************************** */

// Auxiliary member functions

// QuadraticProbing
template <typename Data>
ulong HashTableOpnAdr<Data>::QuadraticProbing(ulong & probing, const Data & key) const noexcept {
    ulong index = HashKey(Hashable<Data>()(key));
    return (index + (((probing*probing) + probing)/2) + tableSize) % tableSize;
}


// Find
template <typename Data>
bool HashTableOpnAdr<Data>::Find(ulong & index, ulong & probing, const Data & key) const noexcept {
    ulong jumps = 0;
    ulong indexSwap = 0;
    bool found = true;
    ulong tmpIndex = QuadraticProbing(probing, key);
    do{
        if(jumps == (tableSize-1))
            return false;
        if((table[tmpIndex] == key) && (flags[tmpIndex] == occupied)){
            index = tmpIndex;
            if(!found){
                table[indexSwap] = table[index];
                std::swap(flags[indexSwap], flags[tmpIndex]);
                index = indexSwap;
            }
            else
                index = tmpIndex;
            return true;
        }
        if(flags[tmpIndex] != occupied && found){
            indexSwap = tmpIndex;
            found = false;
        }
        tmpIndex = QuadraticProbing(++probing, key);
        jumps++;
    }while(!flags[tmpIndex] == empty);
    return false;
}

// FindEmpty
template <typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(ulong & probing, const Data & key) noexcept {
    ulong tmpIndex = QuadraticProbing(probing, key);

    while((flags[tmpIndex] == occupied) && (table[tmpIndex] != key)){
        tmpIndex = QuadraticProbing(++probing, key);
    }
    return tmpIndex;
}

// Remove
template <typename Data>
bool HashTableOpnAdr<Data>::RemoveElem(ulong & probing, const Data & key) {
    ulong tmpIndex = 0;
    if(Find(tmpIndex, probing, key)){
        flags[tmpIndex] = deleted;
        size--;
        deletedElem++;
        probing = 0;
        if(size < tableSize/5 && tableSize > 16)
            Resize(tableSize/2);
        if(deletedElem > (tableSize/4))
            Resize(tableSize);
        return true;
    }
    probing = 0;
    return false;
}
 
/* ************************************************************************** */

}
