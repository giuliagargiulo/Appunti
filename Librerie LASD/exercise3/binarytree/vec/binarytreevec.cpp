#include <stdexcept>

namespace lasd {

/* ************************************************************************** */

//NodeVec

//Copy constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(const Data & elem, ulong i, BinaryTreeVec<Data> * tree){
    element = elem;
    index = i;
    bt = tree;
}

//Move constructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Data && elem, ulong i, BinaryTreeVec<Data> * tree) noexcept{
    std::swap(element, elem);
    index = i;
    bt = tree;
}

//Destructor
template <typename Data>
BinaryTreeVec<Data>::NodeVec::~NodeVec(){
    if(!bt->vecNodes.Empty()){
        bt->vecNodes[Index()] = nullptr;
    }  
}

//Copy assignment
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::operator=(const NodeVec & other){
    element = other.element;
    index = other.index;
    bt = other.bt;
    return *this;
}

//Move assignment
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::operator=(NodeVec && other) noexcept{
    std::swap(element, other.element);
    std::swap(index,other.index);
    std::swap(bt,other.bt);
    return *this;
}

//HasLeftChild
template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept{
    return ((Index()*2 + 1) < (bt->vecNodes).Size() && bt->vecNodes[Index()*2 + 1] != nullptr);
}

//HasRightChild
template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept{
    return ((Index()*2 + 2) < (bt->vecNodes).Size() && bt->vecNodes[Index()*2 + 2] != nullptr);
}

template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::RightChild(){
    if(HasRightChild())
        return *bt->vecNodes.operator[](Index()*2 + 2);
    else
        throw std::out_of_range("LeftChild doe not exist");
}

template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::RightChild() const{
    if(HasRightChild())
        return *bt->vecNodes.operator[](Index()*2 + 2);
    else
        throw std::out_of_range("LeftChild doe not exist");
}

//LeftChild
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::LeftChild(){
    if(HasLeftChild())
        return *bt->vecNodes.operator[](Index()*2 + 1);
    else
        throw std::out_of_range("LeftChild doe not exist");
}

//LeftChild
template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::NodeVec::LeftChild() const{
    if(HasLeftChild())
        return *bt->vecNodes.operator[](Index()*2 + 1);
    else
        throw std::out_of_range("LeftChild doe not exist");
}

/* ************************************************************************** */

// BinaryTreeVec

// A binary tree obtained from a TraversableContainer
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const TraversableContainer<Data> & trav_container): vecNodes(trav_container.Size()){
    ulong i = 0;
    trav_container.Traverse([this, &i](const Data & elem){
        this->vecNodes[i] = new NodeVec(elem, i, this);
        i++;
    });
    this->size = trav_container.Size();
}

// A binary tree obtained from a MappableContainer
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(MappableContainer<Data> && map_container) : vecNodes(map_container.Size()) {
    ulong i = 0;
    map_container.Map([this, &i](Data & elem){
        this->vecNodes[i] = new NodeVec(std::move(elem), i, this);
        i++;
    });
    this->size = map_container.Size();
}

//Copy constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> & other): vecNodes(other.vecNodes.Size()){
    this->size = other.Size();
    for(ulong i = 0; i < this->Size(); i++)
        this->vecNodes[i] = new typename BinaryTreeVec<Data>::NodeVec(other.vecNodes[i]->Element(), i, this);
}

//Move constructor
template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data> && other) noexcept{
    std::swap(this->vecNodes, other.vecNodes);
    std::swap(this->size, other.size);
    for(ulong i = 0; i < this->Size(); i++)
        this->vecNodes[i]->bt = this;
    for(ulong i = 0; i < other.Size(); i++)
        other.vecNodes[i]->bt = &other;      
}

//Destructor
template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec(){
    Clear();
}

//Copy assignment
template <typename Data>
BinaryTreeVec<Data> & BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data> & other){
    Clear();
    vecNodes.Resize(other.Size());
    this->size = other.Size();
    for(ulong i = 0; i < this->Size(); i++)
        this->vecNodes[i] = new NodeVec(other.vecNodes[i]->Element(), i, this);
    return *this;
}

//Move assignment
template <typename Data>
BinaryTreeVec<Data> & BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data> && other) noexcept{
    std::swap(this->vecNodes, other.vecNodes);
    std::swap(this->size, other.size);
    for(ulong i = 0; i < this->Size(); i++)
        this->vecNodes[i]->bt = this;
    for(ulong i = 0; i < other.Size(); i++)
        other.vecNodes[i]->bt = &other;
    return *this;
}

//Root
template <typename Data>
typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::Root(){
    if(!vecNodes.Empty())
        return *vecNodes[0];
    else
        throw std::length_error("Empty tree in function Root");
}

template <typename Data>
const typename BinaryTreeVec<Data>::NodeVec & BinaryTreeVec<Data>::Root() const{
    if(!vecNodes.Empty())
        return *vecNodes[0];
    else
        throw std::length_error("Empty tree in function Root");
}

//Clear
template <typename Data>
void BinaryTreeVec<Data>::Clear() noexcept{
    for(ulong i = 0; i < this->Size(); i++){
        if(vecNodes[i] != nullptr){
            delete vecNodes[i];
            vecNodes[i] = nullptr;
        }
    }
    vecNodes.Clear();
    this->size = 0;
}

//BreadthTraverse
template <typename Data>
void BinaryTreeVec<Data>::BreadthTraverse(TraverseFun fun) const{
    for(ulong i = 0; i < this->Size(); i++){
        if (vecNodes[i] != nullptr)
            fun(vecNodes[i]->Element());
    }
}

//BreadthMap
template <typename Data>
 void BinaryTreeVec<Data>::BreadthMap(MapFun fun){
    for(ulong i = 0; i < this->Size(); i++){
        if (vecNodes[i] != nullptr)
            fun(vecNodes[i]->Element());
    }
 }

/* ************************************************************************** */

}
