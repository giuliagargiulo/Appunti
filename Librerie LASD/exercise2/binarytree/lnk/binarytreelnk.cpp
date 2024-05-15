
#include <stdexcept>

namespace lasd {

/* ************************************************************************** */

//NodeLnk

//Specific Constructors

//Copy constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const NodeLnk & other): element(other.element){
    if(other.HasLeftChild())
        left = new NodeLnk(*other.left);
    if(other.HasRightChild())
        right = new NodeLnk(*other.right);
}

// Move constructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(NodeLnk && other) noexcept{
    std::swap(element, other.element);
    std::swap(left, other.left);
    std::swap(right, other.right);
}

//Specific member functions

//LeftChild()
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::LeftChild() const{
    if(HasLeftChild())
        return *left;
    else
        throw std::out_of_range("Left child does not exist in function LeftChild()");
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::LeftChild(){
    if(HasLeftChild())
        return *left;
    else
        throw std::out_of_range("Left child does not exist in function LeftChild()");
}

//RightChild()
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::RightChild() const{
    if(HasRightChild())
        return *right;
    else
        throw std::out_of_range("Right child does not exist in function RightChild()");
}

template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::NodeLnk::RightChild(){
    if(HasRightChild())
        return *right;
    else
        throw std::out_of_range("Right child does not exist in function RightChild()");
}

//Destructor
template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk(){
    delete left;
    delete right;
}

/* ************************************************************************** */

// BINARY TREE LNK

// A BinaryTreeLnk obtained from a TraversableContainer
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const TraversableContainer<Data> & trav_container){    // come una BFS sul container
    size = trav_container.Size();
    QueueVec<NodeLnk**> queue;  // Creo una coda di puntatori a puntatori a NodeLnk
    queue.Enqueue(&root); // Accodo il puntatore alla radice
    trav_container.Traverse([&queue](const Data & data){  // Per ogni elemento del contenainer creo un nuovo nodo e accodo i suoi figli
        NodeLnk *&  currentNode = *queue.Head();  // creo un puntatore che punta al nodo in testa alla coda
        currentNode = new NodeLnk(data);  // riempio il nodo con il dato
        queue.Enqueue(&currentNode->left); // accodo i figli (attualmente vuoti)
        queue.Enqueue(&currentNode->right);
        queue.Dequeue(); // deaccodo il nodo appena riempito
    });
}

// A BinaryTreeLnk obtained from a MappableContainer
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(MappableContainer<Data> && map_container){    // come una BFS sul container
    size = map_container.Size();
    QueueVec<NodeLnk**> queue;  // Creo una coda di puntatori a puntatori a NodeLnk
    queue.Enqueue(&root); // Accodo il puntatore alla radice
    map_container.Map([&queue](Data & data){  // Per ogni elemento del contenainer creo un nuovo nodo e accodo i suoi figli
        NodeLnk *&  currentNode = *queue.Head();  // creo un puntatore che punta al nodo in testa alla coda
        currentNode = new NodeLnk(std::move(data));  // riempio il nodo con il dato
        queue.Enqueue(&currentNode->left); // accodo i figli (attualmente vuoti)
        queue.Enqueue(&currentNode->right);
        queue.Dequeue(); // deaccodo il nodo appena riempito
    });
}

//// Copy constructor
//template <typename Data>
//BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data> & other){
//    size = other.Size();
//    QueueVec<NodeLnk**> queue; // BFS sull'albero da copiare (other)
//    queue.Enqueue(&root);
//    other.Traverse([&queue](const Data & data){
//        NodeLnk *&  currentNode = *queue.Head();  
//        currentNode = new NodeLnk(data); 
//        queue.Enqueue(&currentNode->left);
//        queue.Enqueue(&currentNode->right);
//        queue.Dequeue(); 
//    });
//}

// Copy Constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data> & other){
    Clear();
    size = other.Size();
    if(other.root != nullptr)
        root = Copy(root, other.Root());
}

// Copy()
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk * BinaryTreeLnk<Data>::Copy(typename BinaryTreeLnk<Data>::NodeLnk *& currentNode, const typename BinaryTreeLnk<Data>::NodeLnk & other){
    // visita in PreOrder
    currentNode = new NodeLnk(other.Element());
    if(other.HasLeftChild())
        currentNode->left = Copy(currentNode->left, other.LeftChild());
    if(other.HasRightChild())
        currentNode->right = Copy(currentNode->right, other.RightChild());
    return currentNode;
}

// Move constructor
template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data> && other) noexcept{
    std::swap(root, other.root);
    std::swap(size, other.size);
}

// Copy assignment
template <typename Data>
BinaryTreeLnk<Data> & BinaryTreeLnk<Data>::operator = (const BinaryTreeLnk<Data> & other){
    Clear();
    size = other.Size();
    if(other.root != nullptr)
        root = Copy(root, other.Root());
    return *this;
}

// Move assignment
template <typename Data>
BinaryTreeLnk<Data> & BinaryTreeLnk<Data>::operator = (BinaryTreeLnk<Data> && other) noexcept{
    std::swap(root, other.root);
    std::swap(size, other.size);
    return *this;
}

// Specific member functions (inherited from BinaryTree)
template <typename Data>
const typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::Root() const {
    if(size == 0)
        throw std::length_error("Empty tree in function Root()");
    return *root;
}

// Specific member function (inherited from MutableBinaryTree)
template <typename Data>
typename BinaryTreeLnk<Data>::NodeLnk & BinaryTreeLnk<Data>::Root(){
    if(size == 0)
        throw std::length_error("Empty tree in function Root()");
    return *root;
}

// Specific member function (inherited from ClearableContainer)
template <typename Data>
void BinaryTreeLnk<Data>::Clear() noexcept{
    if(root != nullptr){
        delete root;
        root = nullptr;
    }
    size = 0;
}

// Destructor
template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk(){
    delete root;
}

/* ************************************************************************** */

}
