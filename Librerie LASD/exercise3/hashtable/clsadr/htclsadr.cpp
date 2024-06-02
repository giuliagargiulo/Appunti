
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize){
    tableSize = NextPow(newSize);
    table = new List<Data>[tableSize]{};
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const TraversableContainer<Data> & trav_container) : HashTableClsAdr(trav_container.Size()){
    InsertAll(trav_container);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, const TraversableContainer<Data> & trav_container) : HashTableClsAdr(newSize){
    InsertAll(trav_container);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(MappableContainer<Data> && map_container) noexcept : HashTableClsAdr(map_container.Size()){
    InsertAll(std::move(map_container));
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong newSize, MappableContainer<Data> && map_container) noexcept : HashTableClsAdr(newSize){
    InsertAll(std::move(map_container));
}

/* ************************************************************************** */

// Copy Constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr & other): HashTable<Data>(other){
    table = new List<Data>[tableSize] {};
    std::copy(other.table, other.table + tableSize, table);
}

// Move Constructor
template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr && other) noexcept: HashTable<Data>(std::move(other)){
    std::swap(table, other.table);
}

// Copy Assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr & other){
    HashTable<Data>::operator=(other);
    delete[] table;
    table = new List<Data>[other.tableSize] {};
    for(ulong i = 0; i < tableSize; i++)
        table[i] = other.table[i];
    return *this;
}

//Move Assignment
template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr && other) noexcept{
    HashTable<Data>::operator=(std::move(other));
    std::swap(table, other.table);
    return *this;
}

// Comparison operators
template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr & other) const noexcept{
    if(this->size != other.size)
        return false;
    bool result = true;
    for(ulong i = 0; i < tableSize; i++){
        table[i].Traverse([&other, &result](const Data & data){
            if(!other.Exists(data))
                result = false;
        });
        if(!result)
            return false;
    }
    return true;
}

/* ************************************************************************** */
//Specific member functions

//Insert (Copy of the value)
//template <typename Data>
//bool HashTableClsAdr<Data>::Insert(const Data & val){
//    ulong index = this->HashKey(Hashable<Data> ()(val));
//    if(table[index].Insert(val)){
//        size++;
//        // calcolo il fattore di carico (alfa) della lista in cui inserisco il nuovo elemento e verifico se è superiore a 0.8
//        // oppure controllo che l'indice dove ho inserito il nuovo valore sia superiore alla radice quadrata della tableSize,
//        // in caso positivo, ridimensiono l' HashTable
//        if(((float)size/tableSize) > 0.8 || table[index].Size() > (floor(sqrt(tableSize)))) 
//            Resize(tableSize*2);
//        return true;
//    }
//    return false;
//}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data & val) {
    bool result = false;
    //calcolo l'indice in cui l'elemento dat dovrebbe essere inserito nella tabella hash chiamando la funzione HasKey
    ulong index = HashKey(Hashable<Data>()(val));       
    result = table[index].Insert(val);
    if(result)
        size++;
    return result;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data && val) noexcept {
    bool result = false;
    ulong index = HashKey(Hashable<Data>()(val));
    result = table[index].Insert(std::move(val));
    if(result)
        size++;
    return result;
}

////Insert (Move of the value)
//template <typename Data>
//bool HashTableClsAdr<Data>::Insert(Data && val) noexcept{
//    ulong index = this->HashKey(Hashable<Data> ()(val));
//    if(table[index].Insert(std::move(val))){
//        size++;
//        // calcolo il fattore di carico (alfa) della lista in cui inserisco il nuovo elemento e verifico se è superiore a 0.8
//        // oppure controllo che l'indice dove ho inserito il nuovo valore sia superiore alla radice quadrata della tableSize,
//        // in caso positivo, ridimensiono l' HashTable
//        if(((float)size/tableSize) > 0.8 || table[index].Size() > (floor(sqrt(tableSize)))) 
//            Resize(tableSize*2);
//        return true;
//    }
//    return false;
//}

//Remove
template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data & val){
    ulong index = this->HashKey(Hashable<Data>()(val));
    if(table[index].List<Data>::Remove(val)){
        size--;
        if(size<(tableSize/5) && tableSize != 16)
            Resize(tableSize/2);
        return true;
    }
    return false;
}

//Exists
template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data & val) const noexcept{
    ulong index = HashKey(Hashable<Data>()(val));
    return table[index].Exists(val);
}

//Resize
template <typename Data>
void HashTableClsAdr<Data>::Resize(const ulong newsize){
    if(newsize == 0){
        Clear();
        Resize(16);
        return;
    }
    ulong tmpSize = NextPow(newsize);
    size = 0;
    List<Data>* tmpTable = new List<Data>[tmpSize]{};
    std::swap(table, tmpTable);
    std::swap(tmpSize, tableSize);
    for(ulong i = 0; i < tmpSize; i++)
        InsertAll(tmpTable[i]);
    delete[] tmpTable;
}


template <typename Data>
void HashTableClsAdr<Data>::Clear() noexcept{
    delete[] table;
    table = new List<Data>[tableSize]{};
    size = 0;
}

/* ************************************************************************** */

}
