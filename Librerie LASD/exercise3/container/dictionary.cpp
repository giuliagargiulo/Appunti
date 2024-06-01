
namespace lasd {

/* ************************************************************************** */

// Specific member functions
//InsertAll copy of the value
template <typename Data>
bool DictionaryContainer<Data>::InsertAll(const TraversableContainer<Data> & container) {
  bool all_inserted = true;

  container.Traverse(
    [this, &all_inserted](const Data& val){
        all_inserted = all_inserted && (*this).Insert(val);
        }
    ); 
  return all_inserted;
}

//InsertAll move of the value
template <typename Data>
bool DictionaryContainer<Data>::InsertAll(TraversableContainer<Data> && container){
  bool all_inserted = true;

  container.Traverse(
    [this, &all_inserted](const Data& val){
        all_inserted = all_inserted && (*this).Insert(std::move(val));
        }
    ); 
  return all_inserted;
}

//RemoveAll
template <typename Data>
bool DictionaryContainer<Data>::RemoveAll(const TraversableContainer<Data> & container) {
  bool all_removed = true;

  container.Traverse(
    [this, &all_removed](const Data& val){
        all_removed = all_removed && (*this).Remove(val);
        }
    ); 
  return all_removed;
}

//InsertSome copy of the value
template <typename Data>
bool DictionaryContainer<Data>::InsertSome(const TraversableContainer<Data> & container){
  bool some_inserted = false;

  container.Traverse(
    [this, &some_inserted](const Data& val){
        some_inserted = some_inserted || (*this).Insert(val);
        }
    ); 
  return some_inserted;
}

//InsertSome move of the value
template <typename Data>
bool DictionaryContainer<Data>::InsertSome(TraversableContainer<Data> && container){
  bool some_inserted = false;

  container.Traverse(
    [this, &some_inserted](const Data& val){
        some_inserted = some_inserted || (*this).Insert(std::move(val));
        }
    ); 
  return some_inserted;
}

//RemoveSome
template <typename Data>
bool DictionaryContainer<Data>::RemoveSome(const TraversableContainer<Data> & container){
  bool some_removed = false;

  container.Traverse(
    [this, &some_removed](const Data& val){
        some_removed = some_removed || (*this).Remove(val);
        }
    ); 
  return some_removed;
}

/* ************************************************************************** */

}
