
#include "list.hpp"

namespace lasd {

/* ************************************************************************** */

// NODE

// Constructor Node() copy of the value
template <typename Data>
List<Data>::Node::Node(const Data & new_val){
    val = new_val;
}

// Constructor Node() move of the value
template <typename Data>
List<Data>::Node::Node(Data && new_val) noexcept{
    std::swap(val, new_val);
}

// Copy constructor
template <typename Data>
List<Data>::Node::Node(const Node & new_node){
    val = new_node.val;
    next = new_node.next;
}

// Move constructor 
template <typename Data>
List<Data>::Node::Node(Node && new_node) noexcept{
    std::swap(val, new_node.val);
    std::swap(next, new_node.next);
}

/* ************************************************************************** */

// LIST

//Constructor
// A list obtained from a TraversableContainer
template <typename Data>
List<Data>::List(const TraversableContainer<Data> & trav_container){
    trav_container.Traverse([this](const Data & val){
            InsertAtBack(val);
            }
    );
}

// A list obtained from a MappableContainer
template <typename Data>
List<Data>::List(MappableContainer<Data> && map_container){
    map_container.Map([this](Data & val){
            InsertAtBack(std::move(val));
            }
    );
}

// Copy constructor 
template <typename Data>
List<Data>::List(const List & other){
    for(ulong i = 0; i < other.size; i++)
        InsertAtBack(other[i]);
}

// Move constructor 
template <typename Data>
List<Data>::List(List && other) noexcept{
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
}


/* ************************************************************************** */

// Copy assignment 
template <typename Data>
List<Data> & List<Data>::operator = (const List & other) {
    Clear();    
    other.PostOrderTraverse(       
        [this](const Data & val){
        InsertAtFront(val); 
        }
    );
    return *this;
}

// Move assignment 
template <typename Data>
List<Data> & List<Data>::operator = (List && other) noexcept {
    std::swap(head, other.head);
    std::swap(tail, other.tail);
    std::swap(size, other.size);
    return *this;
}
/* ************************************************************************** */

// Comparison operator 
template <typename Data>
bool List<Data>::operator == (const List & other) const noexcept{
    if(size != other.size)
        return false;
    
    Node * tmp1 = head, * tmp2 = other.head;

    for(ulong i = 0; i < size; i++){
        if(tmp1->val != tmp2->val)
            return false;
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    return true;
}
/* ************************************************************************** */

// Specific member functions

// InsertAtFront() copy of the value
template <typename Data>
void List<Data>::InsertAtFront(const Data & new_element){

    Node * tmp = new Node(new_element);  
    tmp ->next = head;  
    head = tmp;
    size++; 

    if (tail == nullptr) // se la lista è vuota, e quindi sto inserendo il primo elemento tail = head
        tail = head;
    
}

// InsertAtFront() move of the value
template <typename Data>
void List<Data>::InsertAtFront(Data && new_element){

    Node * tmp = new Node(std::move(new_element));  
    tmp ->next = head;  
    head = tmp;
    size++; 

    if (tail == nullptr) // se la lista è vuota, e quindi sto inserendo il primo elemento tail = head
        tail = head;
}

// RemoveFromFront()
template <typename Data>
void List<Data>::RemoveFromFront(){
    if(size == 0)
        throw std::length_error("List is empty in function RemoveFromFront()");
    
    Node * tmp = head;
    if(head == tail)  // se la lista ha un solo nodo
        head = tail = nullptr;
    else{
        head = head->next;
        tmp->next = nullptr;
    }
    delete tmp;
    size--;
   
}

// FrontNRemove()
template <typename Data>
Data List<Data>::FrontNRemove(){
    if(Empty())
        throw std::length_error("List is empty in function FrontNRemove()");

    Data elem =  head->val;
    RemoveFromFront();
    return elem;
}

// RemoveFromBack()
template <typename Data>
void List<Data>::RemoveFromBack(){
    if(Empty())
        throw std::length_error("List is empty in function RemoveFromBack()");

    Node * tmp = head;
    Node * prev = nullptr;

    if(head == tail){      // se la lista contine un solo elemento
        RemoveFromFront();
        return;
    }

    while(tmp->next != nullptr){   // scorro la lista fino all'ultimo elemento
        prev = tmp;
        tmp = tmp->next;
    }

    prev->next = nullptr;
    tail = prev;
    delete tmp;
    size--;
}

// InsertAtBack() copy of the value
template <typename Data>
 void List<Data>::InsertAtBack(const Data & new_element){
    Node * tmp = new Node(new_element);

    if(tail == nullptr)  // se la lista è vuota
        head = tail = tmp;
    else{
        tail->next = tmp;
        tail = tmp;
    }
    size++;
    
}

// InsertAtBack() move of the value
template <typename Data>
 void List<Data>::InsertAtBack(Data && new_element){
    Node * tmp = new Node(std::move(new_element));

    if(tail == nullptr)  // se la lista è vuota
        head = tail = tmp;
    else{
        tail->next = tmp;
        tail = tmp;
    }
    size++;
}

// Specific member function (inherited from ClearableContainer)

// void Clear()
template <typename Data>
void List<Data>::Clear() noexcept {
    while(!Empty())
      RemoveFromFront();
};

/* ************************************************************************** */

// Specific member functions (inherited from DictionaryContainer)

// bool Insert() copy of the value
template <typename Data>
bool List<Data>::Insert(const Data & new_element){

    if(!(Exists(new_element))){
        InsertAtBack(new_element);
        return true;
    }
    return false;
}

// bool Insert() move of the value
template <typename Data>
bool List<Data>::Insert(Data && new_element){

    if(!(Exists(new_element))){
        InsertAtBack(std::move(new_element));
        return true;
    }
    return false;
}

// bool Remove() 
template <typename Data>
bool List<Data>::Remove(const Data & element){

    if(Empty())
        throw std::length_error("List is empty in function Remove()");

    if(!(Exists(element)))
        return false;
    
    if(head->val == element){     // se l'elemento da eliminare è in testa
        RemoveFromFront();
        return true;
    }
    
    if (tail->val == element){   // se l'elemento da eliminare è in coda
        RemoveFromBack();
        return true;
    }

    Node * tmp = head;
    Node * prev = nullptr;

    while(tmp!= nullptr && tmp->val != element){
        prev = tmp;
        tmp = tmp->next;
    }

    if (tmp != nullptr){
        prev->next = tmp->next;   // aggiorno i puntatori
        tmp->next = nullptr;  
        delete tmp;                 // elimino il nodo
        size--;
        return true;
    }
    return false;
}

/* ************************************************************************** */

// Specific member functions (inherited from LinearContainer)

// operator[] NonMutable
template <typename Data>
const Data & List<Data>::operator[](const ulong index) const{
    if (Empty())
        throw std::length_error("List is empty in operator[]");

    if (index < size){
        Node * tmp = head;
        for(ulong i = 0; i<index; i++)
            tmp = tmp->next;
        return tmp->val;
    }
    else
        throw std::out_of_range("List: Index out of range in operator[]");
    
}

// operator[] 
template <typename Data>
Data & List<Data>::operator[](const ulong index){
    if (Empty())
        throw std::length_error("List is empty in operator[]");
    
    if (index < size){
        Node * tmp = head;
        for(ulong i = 0; i<index; i++)
            tmp = tmp->next;
        return tmp->val;
    }
    else
    throw std::out_of_range("List: Index out of range in operator[]");
}

// Front() NonMutable
template <typename Data>
const Data & List<Data>::Front() const{
    if(Empty())
        throw std::length_error("List is empty in function Front()");
    return head->val;
}

// Front()
template <typename Data>
Data & List<Data>::Front(){
    if(Empty())
        throw std::length_error("List is empty in function Front()");
    return head->val;
}

// Back() NonMutable
template <typename Data>
const Data & List<Data>::Back() const{
    if(Empty())
        throw std::length_error("List is empty in function Back()");
    return tail->val;
}

// Back()
template <typename Data>
Data & List<Data>::Back(){
    if(Empty())
        throw std::length_error("List is empty in function Back()");
    return tail->val;
}

// Specific member function (inherited from PreOrderTraversableContainer)

// PreOrderTraverse()
template <typename Data>
void List<Data>::PreOrderTraverse(TraverseFun fun, Node * tmp) const {
    if(!tmp)
        return;

    fun(tmp->val);
    PreOrderTraverse(fun, tmp->next);
}

// PostOrderTraverse()
template <typename Data>
void List<Data>::PostOrderTraverse(TraverseFun fun, Node * tmp) const {
    if(!tmp)
        return;

    PostOrderTraverse(fun, tmp->next);
    fun(tmp->val);
}

/* ************************************************************************** */
// Specific member function (inherited from MappableContainer)  

// void PreOrderMap(MapFun fun)
template <typename Data>
void List<Data>::PreOrderMap(MapFun fun, Node * tmp) {
    if(!tmp)
        return;

    fun(tmp->val);
    PreOrderMap(fun, tmp->next);
}

// void PostOrderMap(MapFun fun)
template <typename Data>
void List<Data>::PostOrderMap(MapFun fun, Node * tmp) {
    if(!tmp)
        return;

    PostOrderMap(fun, tmp->next);    
    fun(tmp->val);
}

/* ************************************************************************** */
}
