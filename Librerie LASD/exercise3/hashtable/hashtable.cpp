
namespace lasd {

/* ************************************************************************** */


// HASHABLE

// Metodo di moltiplicazione: h(k) = kA - floor(kA) (per i double, poichè per gli int non è necessario)

template<>
class Hashable<int> {
    public:
        ulong operator()(const int val) const noexcept{
            return (val+1)*val;
            //return val;
        }
};

template<>
class Hashable<std::string> {
    public:
        ulong operator()(const std::string val) const noexcept{
            ulong hashVal = 0;
            for(ulong i = 0; i < val.size(); i++)
                hashVal += (i* val[i]);
            return hashVal;
        }
};

template<>
class Hashable<double> {
    public:
        ulong operator()(const double val) const noexcept{
            ulong intPart = floor(val);
            return ((intPart * intPart + ((val-intPart) *(val-intPart))) - intPart);
        }
        //return val+1;
};

/* ************************************************************************** */

// HASHTABLE

// Copy Constructor
  template <typename Data>
  HashTable<Data>::HashTable(const HashTable & other){
    size = other.size;
    tableSize = other.tableSize;
    A = other.A;
    B = other.B;
  }

// Move Constructor
template <typename Data>
HashTable<Data>::HashTable(HashTable && other) noexcept{
    std::swap(this->size, other.size);
    std::swap(tableSize, other.tableSize);
    std::swap(A, other.A);
    std::swap(B, other.B);
}

// Copy Assignment
template <typename Data>
HashTable<Data> & HashTable<Data>::operator= (const HashTable & other){
    size = other.size;
    tableSize = other.tableSize;
    A = other.A;
    B = other.B;
    return *this;
}

// Move Assignment
template <typename Data>
HashTable<Data> & HashTable<Data>::operator= (HashTable && other) noexcept{
    std::swap(this->size, other.size);
    std::swap(tableSize, other.tableSize);
    std::swap(A, other.A);
    std::swap(B, other.B);
    return *this;
}
/* ************************************************************************** */

// Auxiliary member functions
template <typename Data>
ulong HashTable<Data>::HashKey(const ulong key) const noexcept{
    return ((A * key + B) % tableSize);
}


template <typename Data>
ulong HashTable<Data>::NextPow(ulong newSize){
    if(newSize < HASH_TABLE_SIZE)
        return HASH_TABLE_SIZE;
    return std::pow(2, ceil(log2(newSize)));
}

/* ************************************************************************** */

}
