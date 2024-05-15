#include <stdexcept>

namespace lasd {

/* ************************************************************************** */

// BINARY TREE

// Comparison operators
template <typename Data>
bool BinaryTree<Data>::operator == (const BinaryTree & other) const noexcept{
    if(size != other.size)
        return false;
    
    BTPreOrderIterator i(*this);
    BTPreOrderIterator j(other);
    while(!i.Terminated()){
        if((*i) != (*j))
            return false;
        ++i; ++j;
    }
    return true;
}

// PreOrderTraverse()
template <typename Data>
void BinaryTree<Data>::PreOrderTraverse(TraverseFun fun) const{
    if (!this->Empty())
        PreOrderTraverseAux(fun, Root());
}

template <typename Data>
void BinaryTree<Data>::PreOrderTraverseAux(TraverseFun fun, const Node & node) const{
    fun(node.Element());
    if(node.HasLeftChild())
        PreOrderTraverseAux(fun, node.LeftChild());
    if(node.HasRightChild())
        PreOrderTraverseAux(fun, node.RightChild());
}

// PostOrderTraverse()
template <typename Data>
void BinaryTree<Data>::PostOrderTraverse(TraverseFun fun) const{
    if (!this->Empty())
        PostOrderTraverseAux(fun, Root());
}

template <typename Data>
void BinaryTree<Data>::PostOrderTraverseAux(TraverseFun fun, const Node & node) const{
    if(node.HasLeftChild())
        PostOrderTraverseAux(fun, node.LeftChild());
    if(node.HasRightChild())
        PostOrderTraverseAux(fun, node.RightChild());
    fun(node.Element());
}

// InOrderTraverse()
template <typename Data>
void BinaryTree<Data>::InOrderTraverse(TraverseFun fun) const{
    if (!this->Empty())
        InOrderTraverseAux(fun, Root());
}

template <typename Data>
void BinaryTree<Data>::InOrderTraverseAux(TraverseFun fun, const Node & node) const{
    if(node.HasLeftChild())
        InOrderTraverseAux(fun, node.LeftChild());
    fun(node.Element());
    if(node.HasRightChild())
        InOrderTraverseAux(fun, node.RightChild());
}


//BreadthTraverse()
template <typename Data>
void BinaryTree<Data>::BreadthTraverse(TraverseFun fun) const{
    for(BTBreadthIterator i(*this); !(i.Terminated()); ++i) 
        fun(*i);
}

/* ************************************************************************** */

// MUTABLE BINARY TREE

// PreOrderMap()
template <typename Data>
void MutableBinaryTree<Data>::PreOrderMap(MapFun fun){
    if (!this->Empty())
        PreOrderMapAux(fun, Root());
}

template <typename Data>
void MutableBinaryTree<Data>::PreOrderMapAux(MapFun fun, MutableNode & node){
    fun(node.Element());
    if(node.HasLeftChild())
        PreOrderMapAux(fun, node.LeftChild());
    if(node.HasRightChild())
        PreOrderMapAux(fun, node.RightChild());
}

// PostOrderMap()
template <typename Data>
void MutableBinaryTree<Data>::PostOrderMap(MapFun fun){
    if (!this->Empty())
        PostOrderMapAux(fun, Root());
}

template <typename Data>
void MutableBinaryTree<Data>::PostOrderMapAux(MapFun fun, MutableNode & node){
    if(node.HasLeftChild())
        PostOrderMapAux(fun, node.LeftChild());
    if(node.HasRightChild())
        PostOrderMapAux(fun, node.RightChild());
    fun(node.Element());
}

// InOrderMap()
template <typename Data>
void MutableBinaryTree<Data>::InOrderMap(MapFun fun){
    if (!this->Empty())
        InOrderMapAux(fun, Root());
}

template <typename Data>
void MutableBinaryTree<Data>::InOrderMapAux(MapFun fun, MutableNode & node){
    if(node.HasLeftChild())
        InOrderMapAux(fun, node.LeftChild());
    fun(node.Element());
    if(node.HasRightChild())
        InOrderMapAux(fun, node.RightChild());
}

// BreadthMap()
template <typename Data>
void MutableBinaryTree<Data>::BreadthMap(MapFun fun){
    for(BTBreadthMutableIterator i(*this); !(i.Terminated()); ++i) 
        fun(*i);
}

/* ************************************************************************** */

//BTPreOrderIterator

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> & bt){
   if(!bt.Empty())
        root = current = &bt.Root();
}

// Copy Constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator & other) : stack(other.stack){
    root = other.root;
    current = other.current;
}
// Move Constructor
template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator && other) noexcept : stack(std::move(other.stack)){
    std::swap(root, other.root);
    std::swap(current, other.current);
}

//Copy Assignment
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator = (const BTPreOrderIterator & other){
    root = other.root;
    current = other.current;
    stack = other.stack;
    return *this;
}
//Move Assignment
template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator = (BTPreOrderIterator && other) noexcept{
    root = std::move(other.root);
    stack = std::move(other.stack);
    current = std::move(other.current);
    return *this;
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator == (const BTPreOrderIterator & other) const noexcept{
    return (current == other.current && root == other.root);
}

template <typename Data>
const Data & BTPreOrderIterator<Data>::operator * () const{
    if(Terminated())
        throw std::out_of_range("operator*: Iterator is terminated");
    return current->Element();
}


template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept{
    return current == nullptr;
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator ++ (){
    if(Terminated())
        throw std::out_of_range("operator++: Iterator is terminated");
    if (current->HasLeftChild()){  //se c'e un sottoalbero sinistro
        if(current->HasRightChild())  // se c'e anche un sottoalbero destro
            stack.Push(&current->RightChild()); //inserisco il sottoalbero destro nello stack
        current = &(current->LeftChild()); //vado al sottoalbero sinistro
    }
    else if(current->HasRightChild()) //se c'e solo il sottoalbero destro
        current = &(current->RightChild()); //vado al sottoalbero destro
    else if(!stack.Empty()) //se non ci sono sottoalberi
        current = stack.TopNPop(); //prendo il primo elemento nello stack
    else
        current = nullptr; //se non ci sono piu elementi
    return *this;
}

template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept{
    stack.Clear();
    this->current = root;
}

/* ************************************************************************** */

//BTPreOrderMutableIterator

//Copy Assignment
template <typename Data>
BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator = (const BTPreOrderMutableIterator & other){
    this->current = other.current;
    this->root = other.root;
    this->stack = other.stack;
    return *this;
}

//Move Assignment
template <typename Data>
BTPreOrderMutableIterator<Data>& BTPreOrderMutableIterator<Data>::operator = (BTPreOrderMutableIterator && other) noexcept{
    this->current = std::move(other.current);
    this->root = std::move(other.root);
    this->stack = std::move(other.stack);
    return *this;
}

// operator*
template <typename Data>
Data& BTPreOrderMutableIterator<Data>::operator*(){
    if(this->Terminated())
        throw std::out_of_range("operator*: Iterator is terminated");
    return const_cast<Data&>(this->current->Element()); // forse serve const_cast<Data&> prima di current per togliere const dalla funzione Element()
}

/* ************************************************************************** */
//BTPostOrderIterator
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data> & bt){
    if(!bt.Empty())
        root = &bt.Root();
        current = FindDeepestLeft(root);
}

//Copy Constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator & other){
    stack = other.stack;
    root = other.root;
    current = other.current;
}

//Move Constructor
template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator && other) noexcept{
    std::swap(stack, other.stack);
    std::swap(root, other.root);
    std::swap(current, other.current);
}

//Copy Assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator = (const BTPostOrderIterator & other){
    stack = other.stack;
    root = other.root;
    current = other.current;
    return *this;
}

//Move Assignment
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator = (BTPostOrderIterator && other) noexcept{
    std::swap(stack, other.stack);
    std::swap(root, other.root);
    std::swap(current, other.current);
    return *this;
}

//Comparison operator
template <typename Data>
bool BTPostOrderIterator<Data>::operator == (const BTPostOrderIterator & other) const noexcept{
    return (current == other.current && root == other.root);
}

//operator*
template <typename Data>
const Data & BTPostOrderIterator<Data>::operator * () const{
    if(Terminated())
        throw std::out_of_range("operator*: Iterator is terminated");
    return current->Element();
}

//Terminated()
template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept{
    return current == nullptr;
}

//operator++
template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator ++ (){
    if(Terminated())
        throw std::out_of_range("operator++: Iterator is terminated");
    if(!(stack.Empty())){
        if(stack.Top()-> HasRightChild() && !(&(stack.Top()->RightChild()) == current)){
            current = &(stack.Top()->RightChild());
            current = FindDeepestLeft(current);
        }
        else
            current = stack.TopNPop();
    }
    else
        current = nullptr;
    return *this;
}

//FindDeepestLeft()
template <typename Data>
const typename BinaryTree<Data>::Node* BTPostOrderIterator<Data>::FindDeepestLeft(const typename BinaryTree<Data>::Node * node){
    if(node != nullptr){  
        while(node->HasLeftChild()){
            stack.Push(node);
            node = &node->LeftChild();
        }
        if(node->HasRightChild()){
            stack.Push(node);
            node = &node->RightChild();
            node = FindDeepestLeft(node);
        }
    }
    return node;
}

//Reset()
template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept{
    stack.Clear();
    current = root;
    current = FindDeepestLeft(root);
}

/* ************************************************************************** */

//BTPostOrderMutableIterator

//Copy Assignment
template <typename Data>
BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator = (const BTPostOrderMutableIterator & other){
    this->current = other.current;
    this->root = other.root;
    this->stack = other.stack;
    return *this;
}

//Move Assignment
template <typename Data>
BTPostOrderMutableIterator<Data>& BTPostOrderMutableIterator<Data>::operator = (BTPostOrderMutableIterator && other) noexcept{
    std::swap(this->current, other.current);
    std::swap(this->root, other.root);
    std::swap(this->stack, other.stack);
    return *this;
}

//operator*
template <typename Data>
Data& BTPostOrderMutableIterator<Data>::operator*(){
    if(this->Terminated())
        throw std::out_of_range("operator*: Iterator is terminated");
    return const_cast<Data&>(this->current->Element());
}

/* ************************************************************************** */

//BTInOrderIterator

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> & bt){
    if(!bt.Empty())
        root = current = &bt.Root();
        current = FindDeepestLeftInOrder(root);
}

//FindDeepestLeftInOrder()
template <typename Data>
const typename BinaryTree<Data>::Node* BTInOrderIterator<Data>::FindDeepestLeftInOrder(const typename BinaryTree<Data>::Node * node){ 
    while(node != nullptr && node->HasLeftChild()){
        stack.Push(node);
        node = &node->LeftChild();
    }
    return node;
}

//Copy Constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator & other){
    stack = other.stack;
    root = other.root;
    current = other.current;
}

//Move Constructor
template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator && other) noexcept{
    std::swap(stack, other.stack);
    std::swap(root, other.root);
    std::swap(current, other.current);
}

//Copy Assignment
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator = (const BTInOrderIterator & other){
    stack = other.stack;
    root = other.root;
    current = other.current;
    return *this;
}

//Move Assignment
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator = (BTInOrderIterator && other) noexcept{
    std::swap(stack, other.stack);
    std::swap(root, other.root);
    std::swap(current, other.current);
    return *this;
}

//Comparison operator
template <typename Data>
bool BTInOrderIterator<Data>::operator == (const BTInOrderIterator & other) const noexcept{
    return (current == other.current && root == other.root);
}

//operator*
template <typename Data>
const Data & BTInOrderIterator<Data>::operator * () const{
    if(Terminated())
        throw std::out_of_range("operator*: Iterator is terminated");
    return current->Element();
}

//Terminated()
template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept{
    return current == nullptr;
}

//operator++
template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator ++ (){
    if(Terminated())
        throw std::out_of_range("operator++: Iterator is terminated");
    if(stack.Empty() && !(current->HasRightChild()))
        current = nullptr;
    else {
        if(current->HasRightChild())
            current = FindDeepestLeftInOrder(&current->RightChild());
        else
            current = stack.TopNPop();
    }
    return *this;
}

//Reset()
template <typename Data>
void BTInOrderIterator<Data>::Reset() noexcept{
    stack.Clear();
    current = FindDeepestLeftInOrder(root);
}

/* ************************************************************************** */

//BTInOrderMutableIterator

//Copy Assignment
template <typename Data>
BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator = (const BTInOrderMutableIterator & other){
    this->current = other.current;
    this->root = other.root;
    this->stack = other.stack;
    return *this;
}

//Move Assignment
template <typename Data>
BTInOrderMutableIterator<Data>& BTInOrderMutableIterator<Data>::operator = (BTInOrderMutableIterator && other) noexcept{
    std::swap(this->current, other.current);
    std::swap(this->root, other.root);
    std::swap(this->stack, other.stack);
    return *this;
}

//operator*
template <typename Data>
Data& BTInOrderMutableIterator<Data>::operator*(){
    if(this->Terminated())
        throw std::out_of_range("operator*: Iterator is terminated");
    return const_cast<Data&>(this->current->Element());
}

/* ************************************************************************** */

//BTBreadthIterator

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data> & bt){
    if(!bt.Empty())
        root = current = &bt.Root();
}

//Copy Constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator & other){
    queue = other.queue;
    root = other.root; // fprse root = other.current
    current = other.current;
}

//Move Constructor
template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator && other) noexcept{
    std::swap(queue, other.queue);
    std::swap(root, other.root);
    std::swap(current, other.current);
}

//Copy Assignment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator = (const BTBreadthIterator & other){
    queue = other.queue;
    root = other.root;
    current = other.current;
    return *this;
}

//Move Assignment
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator = (BTBreadthIterator && other) noexcept{
    std::swap(queue, other.queue);
    std::swap(root, other.root);
    std::swap(current, other.current);
    return *this;
}

//Comparison operator
template <typename Data>
bool BTBreadthIterator<Data>::operator == (const BTBreadthIterator & other) const noexcept{
    return (current == other.current && root == other.root);
}

//operator*
template <typename Data>
const Data & BTBreadthIterator<Data>::operator * () const{
    if(Terminated())
        throw std::out_of_range("operator*: Iterator is terminated");
    return current->Element();
}

//Terminated()
template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept{
    return current == nullptr;
}

//operator++
template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator ++ (){
    if(Terminated())
        throw std::out_of_range("operator++: Iterator is terminated");
    if(current->HasLeftChild())
        queue.Enqueue(&current->LeftChild());
    if(current->HasRightChild())
        queue.Enqueue(&current->RightChild());
    if(queue.Empty())
        current = nullptr;
    else
        current = queue.HeadNDequeue();
    return *this;
}

//Reset()
template <typename Data>
void BTBreadthIterator<Data>::Reset() noexcept{
    queue.Clear();
    current = root;
}

/* ************************************************************************** */

//BTBreadthMutableIterator

//Copy Assignment
template <typename Data>
BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator = (const BTBreadthMutableIterator & other){
    this->current = other.current;
    this->root = other.root;
    this->queue = other.queue;
    return *this;
}

//Move Assignment
template <typename Data>
BTBreadthMutableIterator<Data>& BTBreadthMutableIterator<Data>::operator = (BTBreadthMutableIterator && other) noexcept{
    std::swap(this->current, other.current);
    std::swap(this->root, other.root);
    std::swap(this->queue, other.queue);
    return *this;
}

//operator*
template <typename Data>
Data& BTBreadthMutableIterator<Data>::operator*(){
    if(this->Terminated())
        throw std::out_of_range("operator*: Iterator is terminated");
    return const_cast<Data&>(this->current->Element());
}

/* ************************************************************************** */

}
