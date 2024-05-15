
namespace lasd {

/* ************************************************************************** */

// Specific constructors
template <typename Data>
BST<Data>::BST(const TraversableContainer<Data> & trav_container){
    trav_container.Traverse([this](const Data & data){
        Insert(data);
    });
}

template <typename Data>
BST<Data>::BST(MappableContainer<Data> && map_container){
    map_container.Map([this](Data && data){
        Insert(std::move(data));
    });
}

// Copy assignment
template <typename Data>
BST<Data> & BST<Data>::operator = (const BST & other){
    if(this != &other){
        Clear();
        other.PreOrderTraverse([this](const Data & data){
            Insert(data);
        });
    }
    return *this;
}

// Move assignment
template <typename Data>
BST<Data> & BST<Data>::operator = (BST && other) noexcept{
  if(this != &other){
        Clear();
        other.PreOrderTraverse([this](const Data & data){
            Insert(std::move(data));
        });
    }
    return *this;
}

// Comparison operator
template <typename Data>
bool BST<Data>::operator == (const BST & other) const noexcept{
    if(Size() != other.Size())
        return false;

    bool equal = true;
    this->PreOrderTraverse([&other, &equal](const Data & data){
        if(!other.Exists(data)){
            equal = false;
            return;
        }
    });
    return equal;
}

// Specific member functions

// Min()
template <typename Data>
const Data & BST<Data>::Min() const{
    if(root == nullptr)
        throw std::length_error("BST is empty in function Min()");
    return FindPointerToMin(root)->Element();
}

template <typename Data>
const typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerToMin(const typename BST<Data>::NodeLnk* const & node) const noexcept {
    const typename BST<Data>:: NodeLnk * const * ret = &node;
    if(node->left == nullptr)
        return *ret;
    else
        return FindPointerToMin(node->left);
}

template <typename Data>
typename BST<Data>::NodeLnk* & BST<Data>::FindPointerToMin(typename BST<Data>::NodeLnk *& node) noexcept {
    typename BST<Data>::NodeLnk ** ret = &node;
    if(node->left == nullptr)
        return *ret;
    else
        return FindPointerToMin(node->left);
}


//MinNRemove();
template <typename Data>
Data BST<Data>::MinNRemove(){
    Data min = Min();
    if(Size() == 0)
        throw std::length_error("BST is empty in function MinNRemove()");
    RemoveMin();
    return min;
}

//RemoveMin();
template <typename Data>
void BST<Data>::RemoveMin(){
    if(Size() == 0)
        throw std::length_error("BST is empty in function RemoveMin()");
    delete DetachMin(root->left, root);
    size--;
}

template <typename Data>
typename BST<Data>::NodeLnk * BST<Data>::DetachMin(typename BST<Data>::NodeLnk *& node, typename BST<Data>::NodeLnk *& parent) noexcept{
   typename BST<Data>::NodeLnk * ret = node;
   if(node != nullptr){
        if (node->left != nullptr)
            ret = DetachMin(node->left, node);

        else{
           ret = node;
           if (parent != nullptr){
                if(parent->left == node){
                    parent->left = node->right;
                    ret->right = nullptr;
                }
                else{
                    parent->right = node->right;
                    ret->right = nullptr;
                }
            }
        }  
   }
    return ret;
}



//Max()
template <typename Data>
const Data & BST<Data>::Max() const{
    if(Size() == 0)
        throw std::length_error("BST is em ty in function Max()");
    return FindPointerToMax(root)->element;
}

// FindPointerToMax()
template <typename Data>
const typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerToMax(const typename BST<Data>::NodeLnk* const & node) const noexcept {
    const typename BST<Data>::NodeLnk * const * ret = &node;
    if(node->right == nullptr)
        return *ret;
    else
        return FindPointerToMax(node->right);
}

template <typename Data>
typename BST<Data>::NodeLnk* & BST<Data>::FindPointerToMax(typename BST<Data>::NodeLnk* & node) noexcept {
    typename BST<Data>::NodeLnk ** ret = &node;
    if(node->right == nullptr)
        return *ret;
    else
        return FindPointerToMax(node->right);
}

//MaxNRemove();
template <typename Data>
Data BST<Data>::MaxNRemove(){
    Data max = Max();
    if(Size() == 0)
        throw std::length_error("BST is empty in function MaxNRemove()");
    RemoveMax();
    return max;
}

//RemoveMax();
template <typename Data>
void BST<Data>::RemoveMax(){
    if(Size() == 0)
        throw std::length_error("BST is empty in function RemoveMax()");
    delete DetachMax(root->right, root);
    size--;
}

// DetachMax()
template <typename Data>
typename BST<Data>::NodeLnk * BST<Data>::DetachMax(typename BST<Data>::NodeLnk *& node, typename BST<Data>::NodeLnk *& parent) noexcept{
    typename BST<Data>::NodeLnk * ret = node;
    if(node != nullptr){
        if (node->right != nullptr)
            ret = DetachMax(node->right, node);

        else{
           ret = node;
           if (parent != nullptr){
                if(parent->right == node){
                    parent->right = node->left;
                    ret->left = nullptr;
                }
                else{
                    parent->left = node->left;
                    ret->left = nullptr;
                }
            }
        }  
   }
    return ret;
}

//Predecessor();
template <typename Data>
const Data & BST<Data>::Predecessor(const Data & elem) const{
    if(Size() == 0)
        throw std::length_error("BST is empty in function Predecessor()");
    if(!Exists(elem))
        throw std::length_error("Element not found in function Predecessor()");
    const typename BST<Data>::NodeLnk * pred = FindPointerToPredecessor(root, elem);
    if(pred == nullptr)
        throw std::length_error("No predecessor found in function Predecessor()");
    return pred->element;
}

template <typename Data>
const typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerToPredecessor(const typename BST<Data>::NodeLnk * const & node, const Data & elem) const noexcept{
    if(node != nullptr){
        if(node->element == elem)
            return FindPointerToMax(node->left);
        else if(node->element < elem)
            return FindPointerToPredecessor(node->right, elem);
        else
            return FindPointerToPredecessor(node->left, elem);
    }
    return nullptr;
}

template <typename Data>
typename BST<Data>::NodeLnk* & BST<Data>::FindPointerToPredecessor(typename BST<Data>::NodeLnk *& node, const Data & elem) noexcept{
    if(node != nullptr){
        if(node->element == elem)
            return Max(node->left);
        else if(node->element < elem)
            return FindPointerToPredecessor(node->right, elem);
        else
            return FindPointerToPredecessor(node->left, elem);
    }
    return nullptr;
}

//PredecessorNRemove();
template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data & elem){
    Data pred = Predecessor(elem);
    Remove(pred);
    return pred;
}

//RemovePredecessor();
template <typename Data>
void BST<Data>::RemovePredecessor(const Data & elem){
    Remove(Predecessor(elem));
}

// Successor()
template <typename Data>
const Data & BST<Data>::Successor(const Data & elem) const{
    if(Size() == 0)
        throw std::length_error("BST is empty in function Successor()");
    if(!Exists(elem))
        throw std::length_error("Element not found in function Successor()");
    const NodeLnk * succ = FindPointerToSuccessor(root, elem);
    if(succ == nullptr)
        throw std::length_error("No successor found in function Successor()");
    return succ->element;
}

// TODO: DA RIVEDERE 
template <typename Data>
const typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerToSuccessor(const typename BST<Data>::NodeLnk * const & node, const Data & elem) const noexcept{
    const typename BST<Data>::NodeLnk * const * ret = nullptr;
    if (node != nullptr){
        if (node->element == elem)
            ret = &FindPointerToMin(node->right);
        else if(node->element < elem)
            ret = &FindPointerToSuccessor(node->right, elem);
        else{
            ret = &FindPointerToSuccessor(node->left, elem);
            if (ret == nullptr)
                ret = &node;
        }
    }
    return *ret;
}

template <typename Data>
typename BST<Data>::NodeLnk* & BST<Data>::FindPointerToSuccessor(typename BST<Data>::NodeLnk *& node, const Data & elem) noexcept{
    typename BST<Data>::NodeLnk ** ret = nullptr;
    if (node != nullptr){
        if (node->element == elem)
            ret = &FindPointerToMin(node->right);
        else if(node->element < elem)
            ret = &FindPointerToSuccessor(node->right, elem);
        else{
            ret = &FindPointerToSuccessor(node->left, elem);
            if (ret == nullptr)
                ret = &node;
        }
    }
    return *ret;
}

// SuccessorNRemove()
template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data & elem){
    Data succ = Successor(elem);
    Remove(succ);
    return succ;
}

// RemoveSuccessor()
template <typename Data>
void BST<Data>::RemoveSuccessor(const Data & elem){
    Remove(Successor(elem));
}

// Specific member functions (inherited from DictionaryContainer)

// Insert() copy of the value
template <typename Data>
bool BST<Data>::Insert(const Data & elem){
    typename BST<Data>::NodeLnk *& pointer = FindPointerTo(root, elem);
    if(pointer == nullptr){ // se il nodo non esiste, allora inserisco il nuovo elemento, altrimenti ritorno false
        pointer = new typename BST<Data>::NodeLnk(elem);
        ++size;
        return true;
    }
    return false;
}

// Insert() move of the value
template <typename Data>
bool BST<Data>::Insert(Data && elem){
    typename BST<Data>::NodeLnk *& pointer = FindPointerTo(root, elem);
    if(pointer == nullptr){ // se il nodo non esiste, allora inserisco il nuovo elemento, altrimenti ritorno false
        pointer = new typename BST<Data>::NodeLnk(std::move(elem));
        ++size;
        return true;
    }
    return false;
}

//FindPointerTo()
template <typename Data>
const typename BST<Data>::NodeLnk* const & BST<Data>::FindPointerTo(const typename BST<Data>::NodeLnk * const & node, const Data & elem) const noexcept {
    const typename BST<Data>::NodeLnk * const * ret = &node;
    if(node == nullptr || node->element == elem)
        return *ret;
    if (node->element < elem)
        return FindPointerTo(node->right, elem);
    else
        return FindPointerTo(node->left, elem);
}

template <typename Data>
typename BST<Data>::NodeLnk* & BST<Data>::FindPointerTo(typename BST<Data>::NodeLnk *& node, const Data & elem) noexcept {
    typename BST<Data>::NodeLnk ** ret = &node;
    if(node == nullptr || node->element == elem)
        return *ret;
    if (node->element < elem)
        return FindPointerTo(node->right, elem);
    else
        return FindPointerTo(node->left, elem);
}

// Remove()
template <typename Data>
bool BST<Data>::Remove(const Data & elem){
    typename BST<Data>::NodeLnk *& pointer = FindPointerTo(root, elem);
    if(pointer != nullptr){ // se il nodo esiste allora lo elimino, altrimenti ritorno false
        root = Delete(root, elem);
        --size;
        return true;
    }
    return false;
}


//// Remove()
//template <typename Data>
//bool BST<Data>::Remove(const Data & elem){
//    if(root != nullptr){
//        root = Delete(root, elem);
//        if(!Exists(elem))
//            return true;
//    }
//    return false;
//}


// Detach()
template <typename Data>
typename BST<Data>::NodeLnk * BST<Data>::Detach(typename BST<Data>::NodeLnk *& node) noexcept{
    typename BST<Data>::NodeLnk ** ret = &node;

    if (node != nullptr){
        typename BST<Data>::NodeLnk * tmp = node;
        if(node->left == nullptr)
            ret = &(node->right);
        
        else if (node->right == nullptr)
            ret = &(node->left);
        else{
            tmp = DetachMin(node->right, node);
            node->element = tmp->element;
        }
        delete tmp;
    }
    return *ret; 
}


// Exists()
template <typename Data>
bool BST<Data>::Exists(const Data & val) const noexcept{
    return FindPointerTo(root, val) != nullptr;
}

// Delete()
template <typename Data>
typename BST<Data>::NodeLnk * BST<Data>::Delete(typename BST<Data>::NodeLnk *& node, const Data & elem) noexcept{
   
    if (node != nullptr){
        if(node->Element() < elem)
            node->right = Delete(node->right, elem);
        else if(node->Element() > elem)
            node->left = Delete(node->left, elem);
        else
            node = Detach(root);        
    }
    return node;
}
    
    


/* ************************************************************************** */

}
