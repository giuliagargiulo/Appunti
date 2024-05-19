
#ifndef MYTEST_CPP
#define MYTEST_CPP

/* ************************************************************************** */

/* ************************************************************************** */

#include <iostream>
#include <random>

using namespace std;
#define dim 10

#include "test.hpp"
default_random_engine gen(random_device{}());
uniform_int_distribution<int> RandomNumber(0, 100);
uniform_int_distribution<int> RandomChar(32, 126);
uniform_int_distribution<int> RandomChar2(128, 255);
uniform_real_distribution<double> RandomDouble(0,100);

/* ************************************************************************** */

void mytest(){
    mytest1();
    mytest2();
}

// -------------- TEST COSTRUTTORI --------------

bool TestCostruttori(){

  bool TestPassed = true;
  ulong numTest = 0;
  ulong errors = 0;
  cout << "BEGIN OF CONSTRUCTOR TEST" << endl;

  cout<< "("<< ++numTest<< ")"<< " Test Copy constructor Vector<int>: ";
  lasd::Vector<int> vec(dim);
  for(ulong i=0; i<vec.Size(); i++) vec[i] = RandomNumber(gen);
  lasd::Vector<int> vec2(vec);
  
  if(vec == vec2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }
 
  cout<< "("<< ++numTest<< ")"<< " Test Move constructor Vector<int>: ";
  lasd::Vector<int> vec3(std::move(vec2));

 if(vec2.Empty())
   cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }
  
  cout<< "("<< ++numTest<< ")"<< " Test Copy constructor List<int>: ";
  lasd::List<int> list;
  for(ulong i=0; i<dim; i++) list.InsertAtBack(RandomNumber(gen));
  lasd::List<int> list2(list);

  if (list == list2)
    cout << "Correct!" << endl;
  else{ 
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<  "("<< ++numTest<< ")"<< " Test Move constructor List<int>: ";
  lasd::List<int> list3(std::move(list2));

  if (list2.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<  "("<< ++numTest<< ")"<< " Test copy constructor QueueVec<int>: ";
  lasd::QueueVec<int> queueVec;
  for(ulong i=0; i<dim; i++) queueVec.Enqueue(RandomNumber(gen));
  lasd::QueueVec<int> queueVec2(queueVec);

  if(queueVec == queueVec2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test Move constructor QueueVec<int>: ";
  lasd::QueueVec<int> queueVec3(std::move(queueVec2));

  if(queueVec2.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }


  cout<<  "("<< ++numTest<< ")"<< " Test Copy constructor StackVec<int>: ";
  lasd::StackVec<int> stackVec;
  for(ulong i=0; i<stackVec.Size(); i++) stackVec.Push(RandomNumber(gen));
  lasd::StackVec<int> stackVec2(stackVec);

  if(stackVec == stackVec2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test move constructor StackVec<int>: ";
  lasd::StackVec<int> stackVec3(std::move(stackVec2));

  if(stackVec2.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout << "("<< ++numTest<< ")"<<  " Test copy constructor QueueLst<int>";
  lasd::QueueLst<int> queueLst;
  for(ulong i=0; i<dim; i++) queueLst.Enqueue(RandomNumber(gen));
  lasd::QueueLst<int> queueLst2(queueLst);
  if(queueLst == queueLst2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout <<  "("<< ++numTest<< ")"<< " Test move constructor QueueLst<int>";
  lasd::QueueLst<int> queueLst3(std::move(queueLst2));

  if(queueLst2.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout << "("<< ++numTest<< ")"<<  " Test copy constructor StackLst<int>";
  lasd::StackLst<int> stackLst;
  for(ulong i=0; i<dim; i++) stackLst.Push(RandomNumber(gen));
  lasd::StackLst<int> stackLst2(stackLst);

  if(stackLst == stackLst2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout << "("<< ++numTest<< ")"<<  " Test move constructor StackLst<int>";
  lasd::StackLst<int> stackLst3(std::move(stackLst2));

  if(stackLst2.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }


  cout<< "("<< ++numTest<< ")"<< " Test copy constructor List<int> from Vector<int>: ";
  lasd::Vector<int> vec4(dim);
  for(ulong i=0; i<dim; i++) vec4[i] = RandomNumber(gen);
  lasd::List<int> list4(vec4);
 
  for(ulong i=0; i<list.Size(); i++){
    if(vec4[i] != list4[i]){
      cout << "Error!" << endl; errors++; TestPassed &= false;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<< " Test move constructor List<int> from Vector<int>: ";
  lasd::List<int> vec5(vec4);
  lasd::List<int> list5(std::move(vec4));

  for(ulong i=0; i<dim; i++){
    if(vec5[i] != list5[i]){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<< " Test copy constructor Vector<int> from List<int>: ";
  lasd::List<int> list6;
  for(ulong i=0; i<dim; i++) list6.InsertAtBack(RandomNumber(gen));
  lasd::Vector<int> vec6(list6);

  for(ulong i=0; i<dim; i++){
    if(vec6[i] != list6[i]){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<< " Test move constructor Vector<int> from List<int>: ";
  lasd::List<int> list7(list6);
  lasd::Vector<int> vec7(std::move(list6));

  for(ulong i=0; i<dim; i++){
    if(vec7[i] != list7[i]){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test copy constructor StackLst<int> from Vector<int>: ";
  lasd::Vector<int> vec8(dim);
  for(ulong i=0; i<vec.Size(); i++) vec8[i] = RandomNumber(gen);
  lasd::StackLst<int> stackLst4(vec8);

  for(ulong i=0; i<dim; i++){
    if(vec8[i] != stackLst4.TopNPop()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  } 
  
  cout<< "("<< ++numTest<< ")"<<  " Test move constructor StackLst<int> from Vector<int>: ";
  lasd::Vector<int> vec9(vec8);
  lasd::StackLst<int> stackLst5(std::move(vec8));

  
  for(ulong i=0; i<dim; i++){
    if(vec9[i] != stackLst5.TopNPop()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test copy constructor StackVec<int> from Vector<int>: ";
  lasd::Vector<int> vec14(dim);
  for(ulong i=0; i<dim; i++) vec14[i] = RandomNumber(gen);
  lasd::StackVec<int> stackVec4(vec14);

  for(long i=dim-1; i >= 0; i--){
   if(vec14[i] != stackVec4.TopNPop()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
   if(i == 0)
     cout << "Correct!" << endl;
  }


  cout<< "("<< ++numTest<< ")"<<  " Test move constructor StackVec<int> from Vector<int>: ";
  lasd::Vector<int> vec15(vec14);
  lasd::StackVec<int> stackVec5(std::move(vec14));
 
  for(long i=dim-1; i>=0; i--){
    if(vec15[i] != stackVec5.TopNPop()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == 0)
      cout << "Correct!" << endl;
    
  }

  cout<< "("<< ++numTest<< ")"<<  " Test copy constructor QueueLst<int> from Vector<int>: ";
  lasd::Vector<int> vec10(dim);
  for(ulong i=0; i<dim; i++) vec10[i] = RandomNumber(gen);
  lasd::QueueLst<int> queueLst4(vec10);

  for(ulong i=0; i<dim; i++){
    if(vec10[i] != queueLst4.HeadNDequeue()){ 
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test move constructor QueueLst<int> from Vector<int>: ";
  lasd::Vector<int> vec11(vec10);
  lasd::QueueLst<int> queueLst5(std::move(vec10));

  for(ulong i=0; i<dim; i++){
    if(vec11[i] != queueLst5.HeadNDequeue()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }
  
  cout<< "("<< ++numTest<< ")"<<  " Test copy constructor QueueVec<int> from Vector<int>: ";
  lasd::Vector<int> vec12(dim);
  for(ulong i=0; i<vec.Size(); i++) vec12[i] = RandomNumber(gen);
  lasd::QueueVec<int> queueVec4(vec12);

  for(ulong i=0; i<dim; i++){
    if(vec12[i] != queueVec4.HeadNDequeue()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test move constructor QueueVec<int> from Vector<int>: ";
  lasd::Vector<int> vec13(vec12);
  lasd::QueueVec<int> queueVec5(std::move(vec12));

  for(ulong i=0; i<dim; i++){
    if(vec13[i] != queueVec5.HeadNDequeue()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test copy constructor StackLst<int> from List<int>: ";
  lasd::List<int> list8;
  for(ulong i=0; i<dim; i++) list8.InsertAtBack(RandomNumber(gen));
  lasd::StackLst<int> stackLst6(list8);

  for(ulong i=0; i<dim; i++){
    if(list8[i] != stackLst6.TopNPop()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test move constructor StackLst<int> from List<int>: ";
  lasd::List<int> list9(list8);
  lasd::StackLst<int> stackLst7(std::move(list8));
  
  for(ulong i=0; i<dim; i++){
    if(list9[i] != stackLst7.TopNPop()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test copy constructor StackVec<int> from List<int>: ";
  lasd::List<int> list10;
  for(ulong i=0; i<dim; i++) list10.InsertAtBack(RandomNumber(gen));
  lasd::StackVec<int> stackVec6(list10);
  
  for(long i=dim-1; i>=0; i--){
    if(list10[i] != stackVec6.TopNPop()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == 0)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test move constructor StackVec<int> from List<int>: ";
  lasd::List<int> list11(list10);
  lasd::StackVec<int> stackVec7(std::move(list10));

  for(long i=dim-1; i>=0; i--){
    if(list11[i] != stackVec7.TopNPop()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == 0)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test copy constructor QueueLst<int> from List<int>: ";
  lasd::List<int> list12;
  for(ulong i=0; i<dim; i++) list12.InsertAtBack(RandomNumber(gen));
  lasd::QueueLst<int> queueLst6(list12);

  for(ulong i=0; i<dim; i++){
    if(list12[i] != queueLst6.HeadNDequeue()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test move constructor QueueLst<int> from List<int>: ";
  lasd::List<int> list13(list12);
  lasd::QueueLst<int> queueLst7(std::move(list12));

  for(ulong i=0; i<dim; i++){
    if(list13[i] != queueLst7.HeadNDequeue()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test copy constructor QueueVec<int> from List<int>: ";
  lasd::List<int> list14;
  for(ulong i=0; i<dim; i++) list14.InsertAtBack(RandomNumber(gen));
  lasd::QueueVec<int> queueVec6(list14);
  
  for(ulong i=0; i<dim; i++){
    if(list14[i] != queueVec6.HeadNDequeue()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest<< ")"<<  " Test move constructor QueueVec<int> from List<int>: ";
  lasd::List<int> list15(list14);
  lasd::QueueVec<int> queueVec7(std::move(list14));

  for(ulong i=0; i<dim; i++){
    if(list15[i] != queueVec7.HeadNDequeue()){
      cout << "Error!" << endl; errors++; TestPassed &= false; break;
    }
    if(i == dim-1)
      cout << "Correct!" << endl;
  }

// forse devo mettere clear in tutti i move constructor????
cout << "END OF CONSTRUCTOR TEST: ("<< errors << "/" << numTest  << ") " ;
return TestPassed;
}

// -------------- TEST ASSEGNAMENTI --------------

// Copy assignment Vector
bool TestAssignment(){

  bool TestPassed = true;
  ulong numTest = 0;
  ulong errors = 0;
  cout << "BEGIN OF ASSIGNMENT TEST" << endl;
  
  cout<< "("<< ++numTest<< ")"<< " Test Copy assignment from Vector<int> to Vector<int>: ";
  lasd::Vector<int> vec(dim);
  for(ulong i=0; i<vec.Size(); i++) vec[i]=RandomNumber(gen);    
  lasd::Vector<int> vec2; 
  vec2 = vec; 

  if(vec == vec2) 
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout << "("<< ++numTest<< ")"<< " Test Move assignment from Vector<int> to Vector<int>: ";
  lasd::Vector<int> vec3;
  vec3 = std::move(vec2);
  
  if((vec3==vec) && (vec2.Empty()))
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<< "("<< ++numTest<< ")"<< " Test Copy assignment from List<int> to List<int>: ";
  lasd::List<int> list;
  for(ulong i=0; i<dim; i++) list.InsertAtBack(RandomNumber(gen));
  lasd::List<int> list2;
  list2 = list;

  if(list == list2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<< "("<< ++numTest<< ")"<< " Test Move assignment from List<int> to List<int>: ";
  lasd::List<int> list3;
  list3 = std::move(list2);

  if((list3==list) && (list2.Empty()))
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<< "("<< ++numTest<< ")"<< " Test Copy assignment from QueueVec<int> to QueueVec<int>: ";
  lasd::QueueVec<int> queueVec;
  for(ulong i=0; i<dim; i++) queueVec.Enqueue(RandomNumber(gen));
  lasd::QueueVec<int> queueVec2;
  queueVec2 = queueVec;

  if(queueVec == queueVec2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<< "("<< ++numTest<< ")"<< " Test Move assignment from QueueVec<int> to QueueVec<int>: ";
  lasd::QueueVec<int> queueVec3;
  queueVec3 = std::move(queueVec2);

  if((queueVec3==queueVec) && (queueVec2.Empty()))
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }


  cout<< "("<< ++numTest<< ")"<< " Test Copy assignment from QueueLst<int> to QueueLst<int>: ";
  lasd::QueueLst<int> queueLst;
  for(ulong i=0; i<dim; i++) queueLst.Enqueue(RandomNumber(gen));
  lasd::QueueLst<int> queueLst2;
  queueLst2 = queueLst;

  if(queueLst == queueLst2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<< "("<< ++numTest<< ")"<< " Test Move assignment from QueueLst<int> to QueueLst<int>: ";
  lasd::QueueLst<int> queueLst3;
  queueLst3 = std::move(queueLst2);

  if((queueLst3==queueLst) && (queueLst2.Empty()))
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<< "("<< ++numTest<< ")"<< " Test Copy assignment from StackVec<int> to StackVec<int>: ";
  lasd::StackVec<int> stackVec;
  for(ulong i=0; i<dim; i++) stackVec.Push(RandomNumber(gen));
  lasd::StackVec<int> stackVec2;
  stackVec2 = stackVec;
  
  if(stackVec == stackVec2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<< "("<< ++numTest<< ")"<< " Test Move assignment from StackVec<int> to StackVec<int>: ";
  lasd::StackVec<int> stackVec3;
  stackVec3 = std::move(stackVec2);

  if((stackVec3==stackVec) && (stackVec2.Empty()))
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<< "("<< ++numTest<< ")"<< " Test Copy assignment from StackLst<int> to StackLst<int>: ";
  lasd::StackLst<int> stackLst;
  for(ulong i=0; i<dim; i++) stackLst.Push(RandomNumber(gen));
  lasd::StackLst<int> stackLst2;
  stackLst2 = stackLst;

  if(stackLst == stackLst2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<< "("<< ++numTest<< ")"<< " Test Move assignment from StackLst<int> to StackLst<int>: ";
  lasd::StackLst<int> stackLst3;
  stackLst3 = std::move(stackLst2);

  if((stackLst3==stackLst) && (stackLst2.Empty()))
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout << "END OF ASSIGNMENT TEST: ("<< errors << "/" << numTest  << ") " ;
  return TestPassed;
}

bool VectorFunctionsTest(){

bool TestPassed = true;
ulong numTest = 0;
ulong errors = 0;

cout << "BEGIN OF VECTOR FUNCTIONS TEST" << endl;

  // Resize DA RIVEDERE!
  cout << "("<< ++numTest<< ")"<< " Test Resize(): ";
  lasd::Vector<int> vec(dim);

  vec.Resize(dim*2);
  if(vec.Size() == dim*2){
    vec.Resize(dim/4);
    if(vec.Size() == dim/4)
      cout << "Correct!" << endl;
  }
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Clear(): ";
  vec.Clear();
  if(vec.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test ~Vector(): ";
  lasd::Vector<int> vec1(dim);
  vec1.~Vector();
  if(vec1.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Front(): ";
  lasd::Vector<int> vec2(dim);
  for(ulong i=0; i<dim; i++) vec2[i] = RandomNumber(gen);
  if(vec2.Front() == vec2[0])
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Back(): ";
  if(vec2.Back() == vec2[dim-1])
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout<< "("<< ++numTest << ")"<< " Test Sort() SortableVector<int>: ";
  lasd::SortableVector<int> vec3(dim);
  for(ulong i=0; i<dim; i++) vec3[i] = RandomNumber(gen);
  vec3.Sort();

  for(ulong i=0; i<dim-1; i++){
    if(vec3[i] > vec3[i+1]){
      cout << "Error!" << endl; errors++; TestPassed &= false;
    }
    if(i == dim-2)
      cout << "Correct!" << endl;
  }

  cout<< "("<< ++numTest << ")"<< " Test Sort() SortableVector<double>: ";
  lasd::SortableVector<double> vec4(dim);
  for(ulong i=0; i<dim; i++) vec4[i] = RandomDouble(gen);
  vec4.Sort();

  for(ulong i=0; i<dim-1; i++){
    if(vec4[i] > vec4[i+1]){
      cout << "Error!" << endl; errors++; TestPassed &= false;
    }
    if(i == dim-2)
      cout << "Correct!" << endl;
  }

  cout<<"("<< ++numTest << ")"<< " Test Sort() SortableVector<string>: ";
  lasd::SortableVector<string> vec5(dim);
  for(ulong i=0; i<dim/2; i++) vec5[i] = RandomChar(gen);
  for(ulong i=dim/2; i<dim; i++) vec5[i] = RandomChar2(gen);
  vec5.Sort();

  for(ulong i=0; i<dim-1; i++){
    if(vec5[i] > vec5[i+1]){
      cout << "Error!" << endl; errors++; TestPassed &= false;
    }
    if(i == dim-2)
      cout << "Correct!" << endl;
  }

  cout << "END OF VECTOR FUNCTIONS TEST: ("<< errors << "/" << numTest  << ") " ;
  return TestPassed;
}

bool ListFunctionsTest(){

  bool TestPassed = true;
  ulong numTest = 0;
  ulong errors = 0;

  cout << "BEGIN OF LIST FUNCTIONS TEST" << endl;

  cout << "("<< ++numTest<< ")"<<  " Test Clear(): ";
  lasd::List<int> list;
  for(ulong i=0; i<dim; i++) list.InsertAtBack(RandomNumber(gen));
  list.Clear();
  if(list.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Front(): ";
  lasd::List<int> list2;
  for(ulong i=0; i<dim; i++) list2.InsertAtBack(RandomNumber(gen));
  if(list2.Front() == list2[0])
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Back(): ";
  if(list2.Back() == list2[dim-1])
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test RemoveFromBack(): ";
  lasd::List<int> list3;  
  for(ulong i=0; i<dim; i++) list3.InsertAtBack(i);
  cout<< "List Back = "<< list3.Back();
  list3.RemoveFromBack();
  if(list3.Size() == dim-1 && list3.Back() == list3[dim-2])
    cout << " Correct!" << endl;
  else{
    cout << " Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test RemoveFromBack(): ";
  lasd::List<int> list4;
  for(ulong i=0; i<2; i++) list4.InsertAtBack(i);
  cout<< "List Back = "<< list4.Back();
  list4.RemoveFromBack();

  if(list4.Size() == 1 && list4.Back() == 0)
    cout << " Correct!" << endl;
  else{
    cout << " Error!" << endl; TestPassed &= false; errors++;
  }

 cout << "("<< ++numTest<< ")"<<  " Test RemoveFromBack(): ";
  list4.RemoveFromBack();
  if(list4.Empty())
    cout << "Removed element 0 from back, Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test RemoveFromFront(): ";
  lasd::List<int> list5;
  for(ulong i=0; i<dim; i++) list5.InsertAtBack(i);
  cout<< "List Front = "<< list5.Front();
  list5.RemoveFromFront();

  if((list5.Size()== dim-1) && (list5.Front() == 1))
    cout << " Removed element 0 from front, Correct!" << endl;
  else{
    cout << " Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test RemoveFromFront(): ";
  lasd::List<int> list6;
  for(ulong i=0; i<2; i++) list6.InsertAtBack(i);
  cout<< "List Front = "<< list6.Front();
  list6.RemoveFromFront();

  if((list6.Size()== 1) && (list6.Front() == 1))
    cout << " Removed element 0 from front, Correct!" << endl;
  else{
    cout << " Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test RemoveFromFront(): ";
  if((list6.Size()== 1) && (list6.Front() == 1))
    cout << " Removed element 0 from front, Correct!" << endl;
  else{
   cout << " Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test RemoveFromFront(): ";
  list6.RemoveFromFront();
  if(list6.Empty())
    cout << "Removed element 1 from front, Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Remove(): ";
  lasd::List<int> list7;
  for(ulong i=0; i<dim; i++) list7.InsertAtBack(i);
  list7.Remove(0);
  if(list7.Size() == dim-1 && list7.Front() == 1)
    cout << "Removed element 0, Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Remove(): ";
  list7.Remove(9);
  if(list7.Size() == dim-2 && list7.Back() == 8)
    cout << "Removed element 9, Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Remove(): ";
  list7.Remove(6);
  if(list7.Size() == dim-3 && list7[5] == 7)
    cout << "Removed element 6, Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Remove(): ";
  list7.Remove(8);
  if(list7.Size() == dim-4 && list7.Back() == 7)
    cout << "Removed element 8, Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Remove(): ";
  list7.Remove(7);
  if(list7.Size() == dim-5 && list7.Back() == 5)
    cout << "Removed element 7, Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Remove(): ";
  bool test = list7.Remove(6);
  if(list7.Size() == dim-5 && test == false)
    cout << "Element 6 not in list , Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Remove(): ";
  test = list7.Remove(0);
  if(list7.Size() == dim-5 && test == false)
    cout << "Element 0 not in list , Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Remove(): ";
  lasd::List<int> list8;
  list8.InsertAtBack(0);
  list8.Remove(0);
  if(list8.Empty())
    cout << "Removed element 0, Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Remove(): ";
  lasd::List<int> list9;
  list9.InsertAtBack(1);
  list9.InsertAtBack(2);

  list9.Remove(1);
  if(list9.Size() == 1 && list9.Front() == 2)
    cout << "Removed element 1, Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Remove(): ";
  list9.Remove(2);
  if(list9.Empty())
    cout << "Removed element 2, Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Remove(): ";
  lasd::List<int> list10;
  list10.Insert(2);
  list10.Insert(1);
  list10.Insert(0);

  list10.Remove(1);
  if(list10.Size() == 2 && list10[0] == 2)
    cout << "Removed element 1, Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "("<< ++numTest<< ")"<<  " Test Remove(): ";
  list10.Remove(0);
  if(list10.Size() == 1 && list10.Front() == 2)
    cout << "Removed element 0, Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "END OF LIST FUNCTIONS TEST: ("<< errors << "/" << numTest  << ") " ;
  return TestPassed;
}


bool QueueVecFunctionsTest(){

  cout<< "BEGIN OF QueueVec FUNCTIONS TEST" << endl;
  bool TestPassed = true;
  ulong numTest = 0;
  ulong errors = 0;

  cout<< "("<< ++numTest << ")"<< " Test Clear(): ";
  lasd::QueueVec<int> queueVec;
  for(ulong i=0; i<dim; i++) queueVec.Enqueue(RandomNumber(gen));
  queueVec.Clear();
  if(queueVec.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "END OF QueueVec FUNCTIONS TEST: ("<< errors << "/" << numTest  << ") " ;
  return TestPassed;
}

bool StackVecFunctionsTest(){

  cout<< "BEGIN OF StackVec FUNCTIONS TEST" << endl;
  bool TestPassed = true;
  ulong numTest = 0;
  ulong errors = 0;

  cout<< "("<< ++numTest << ")"<< " Test Clear(): ";
  lasd::QueueVec<int> stackVec;
  for(ulong i=0; i<dim; i++) stackVec.Enqueue(RandomNumber(gen));
  stackVec.Clear();
  if(stackVec.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; TestPassed &= false; errors++;
  }

  cout << "END OF StackVec FUNCTIONS TEST: ("<< errors << "/" << numTest  << ") " ;
  return TestPassed;
}

/* ************************************************************************** */

void mytest1() {
  cout<< " ~ BEGIN MYTEST 1 ~ " << endl<<endl;
  cout<< (TestCostruttori() ? "All Passed!" : "Error!" )<< endl<<endl;
  cout<< (TestAssignment() ? "All Passed!" : "Error!" )<< endl<<endl;
  cout<< (VectorFunctionsTest() ? "All Passed!" : "Error!" )<< endl<<endl; 
  cout<< (ListFunctionsTest() ? "All Passed!" : "Error!" )<< endl<<endl;
  cout<< (QueueVecFunctionsTest() ? "All Passed!" : "Error!" )<< endl<<endl;
  cout<< (StackVecFunctionsTest() ? "All Passed!" : "Error!" )<< endl<<endl;
  cout<< " ~ END MYTEST 1 ~ " << endl;
}

/* ************************************************************************** */

bool TestBinaryTreeLink(){

  bool TestPassed = true;
  ulong numTest = 0;
  ulong errors = 0;
  cout << "BEGIN OF BINARY TREE LINK TEST" << endl;

  cout<<"("<< ++numTest<< ")"<< " Test Copy constructor Empty BinaryTreeLnk<int>: ";
  lasd::BinaryTreeLnk<int> btlnk12;
  lasd::BinaryTreeLnk<int> btlnk13(btlnk12);

  if (btlnk12 == btlnk13)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test Move constructor Empty BinaryTreeLnk<int>: ";
  lasd::BinaryTreeLnk<int> btlnk14(std::move(btlnk12));

  if(btlnk12.Empty() && btlnk13 == btlnk14)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test Copy constructor BinaryTreeLnk<int>: ";
  lasd::BinaryTreeLnk<int> btlnk;
  lasd::Vector<int> vec(dim);
  for(ulong i=0; i<dim; i++) vec[i] = RandomNumber(gen);
  btlnk = vec;
  lasd::BinaryTreeLnk<int> btlnk2(btlnk);

  if (btlnk == btlnk2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test Move constructor BinaryTreeLnk<int>: ";
  lasd::BinaryTreeLnk<int> btlnk3(std::move(btlnk2));

  if(btlnk == btlnk3 && btlnk2.Empty()){
    cout << "Correct!" << endl;
  }
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test Copy assingment BinaryTreeLnk<int>: ";
  btlnk3.Clear();
  btlnk3 = btlnk;

  if(btlnk == btlnk3)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test Move assingment BinaryTreeLnk<int>: ";
  btlnk3.Clear();
  btlnk2 = btlnk;
  btlnk3 = std::move(btlnk);
  if(btlnk2 == btlnk3 && btlnk.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test Clear() BinaryTreeLnk<int>: ";
  btlnk.Clear();
  btlnk2.Clear();
  if(btlnk.Empty() && btlnk2.Empty() && btlnk == btlnk2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  
  
  cout<<"("<< ++numTest<< ")"<< " Test BinaryTreeLnk<int> from List<int>: ";
  lasd::List<int> list;
  for(ulong i=0; i<dim; i++) list.InsertAtBack(RandomNumber(gen));
  lasd::BinaryTreeLnk<int> btlnk4(list);
  lasd:: BinaryTreeLnk<int> btlnk5(std::move(list));
  if(btlnk4 == btlnk5 && !btlnk4.Empty() && !btlnk5.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test BinaryTreeLnk<int> from Vector<int>: ";
  lasd::Vector<int> vec1(dim);
  for(ulong i=0; i<dim; i++) vec1[i] = RandomNumber(gen);
  lasd::BinaryTreeLnk<int> btlnk6(vec1);
  lasd:: BinaryTreeLnk<int> btlnk7(std::move(vec1));

  if(btlnk6 == btlnk7 && !btlnk6.Empty() && !btlnk7.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  
  cout<<"("<< ++numTest<< ")"<< " Test BinaryTreeLnk<int> from BinaryTreeVec<int>: ";
  lasd::BinaryTreeVec<int> btvec(vec1);
  lasd::BinaryTreeLnk<int> btlnk10(btvec);

  if(btlnk10 == btvec)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  //Root()
  cout<<"("<< ++numTest<< ")"<< " Test Root() BinaryTreeLnk<int>: ";
  lasd::List<int> list2;
  lasd::BinaryTreeLnk<int> btlnk8;
  btlnk8 = list2;
  try{
    btlnk8.Root();
  } catch (std::length_error) {
    cout<<"length_error: btlnk is Empty, does not have root: Correct!"<<endl; 
  } catch (std::exception) {
    cout<<"Wrong exception called: Error!"<<endl; 
    TestPassed &= false;    
  }


  cout<<"("<< ++numTest<< ")"<< " Test Root() BinaryTreeLnk<int>: ";
  for(ulong i=0; i<dim; i++) list2.InsertAtBack(i);
  btlnk8 = list2;

  if(btlnk8.Root().Element() == 0)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  //Clear()
  cout<<"("<< ++numTest<< ")"<< " Test Clear() BinaryTreeLnk<int>: ";
  btlnk8.Clear();
  lasd::BinaryTreeLnk<int> btlnk9;

  if(btlnk8 == btlnk9 && btlnk8.Empty()){
    try{
      btlnk8.Root();
    } catch (std::length_error) {
      cout<<"length_error: btlnk is Empty, does not have root: Correct!"<<endl; 
    } catch (std::exception) {
      cout<<"Wrong exception called: Error!"<<endl; 
      TestPassed &= false; errors++;
    }
  }
  else{
      cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  
  cout << "END OF BINARY TREE LINK TEST: ("<< errors << "/" << numTest  << ") " ;
  return TestPassed;
}

bool TestBinaryTreeVec(){

  cout<< "BEGIN OF BINARY TREE VEC TEST" << endl;
  bool TestPassed = true;
  ulong numTest = 0;
  ulong errors = 0;

  cout<<(++numTest)<< " Test Copy constructor Empty BinaryTreeVec<int>: ";
  lasd::BinaryTreeVec<int> btvec4;
  lasd::BinaryTreeVec<int> btvec5(btvec4);

  if(btvec4 == btvec5)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test Move constructor Empty BinaryTreeVec<int>: ";
  lasd::BinaryTreeVec<int> btvec6(std::move(btvec5));
  
  if(btvec4 == btvec6 && btvec5.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }


  cout<<"("<< ++numTest<< ")"<< " Test Copy constructor BinaryTreeVec<int>: ";
  lasd::Vector<int> vec(dim);
  for(ulong i=0; i<dim; i++) vec[i] = RandomNumber(gen);
  lasd::BinaryTreeVec<int> btvec(vec);
  lasd::BinaryTreeVec<int> btvec2(btvec);

  if (btvec == btvec2 && !btvec.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test Move constructor BinaryTreeVec<int>: ";
  lasd::BinaryTreeVec<int> btvec3(std::move(btvec2));

  if(btvec == btvec3 && btvec2.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test Copy assingment BinaryTreeVec<int>: ";
  btvec3.Clear();
  btvec3 = btvec;

  if(btvec == btvec3)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test Move assingment BinaryTreeVec<int>: ";
  btvec3.Clear(); btvec2.Clear();
  btvec2 = btvec;
  btvec3 = std::move(btvec);
  if(btvec2 == btvec3 && btvec.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test Clear() BinaryTreeVec<int>: ";
  btvec.Clear();
  btvec2.Clear();
  if(btvec.Empty() && btvec2.Empty() && btvec == btvec2)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test BinaryTreeVec<int> from List<int>: ";
  lasd::List<int> list;
  for(ulong i=0; i<dim; i++) list.InsertAtBack(RandomNumber(gen));
  lasd::BinaryTreeVec<int> btvec7(list);
  lasd:: BinaryTreeVec<int> btvec8(std::move(list));
  if(btvec7 == btvec8 && !btvec7.Empty() && !btvec8.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test BinaryTreeVec<int> from Vector<int>: ";
  lasd::Vector<int> vec1(dim);
  for(ulong i=0; i<dim; i++) vec1[i] = RandomNumber(gen);
  lasd::BinaryTreeVec<int> btvec9(vec1);
  lasd:: BinaryTreeVec<int> btvec10(std::move(vec1));

  if(btvec9 == btvec10 && !btvec9.Empty() && !btvec10.Empty())
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  cout<<"("<< ++numTest<< ")"<< " Test BinaryTreeVec<int> from BinaryTreeLnk<int>: ";
  lasd::BinaryTreeLnk<int> btlnk;
  lasd::BinaryTreeVec<int> btvec11(btlnk);

  if(btvec11 == btlnk)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  //Root()
  cout<<"("<< ++numTest<< ")"<< " Test Root() BinaryTreeVec<int>: ";
  lasd::List<int> list2;
  for(ulong i=0; i<dim; i++) list2.InsertAtBack(i);
  lasd::BinaryTreeVec<int> btvec12;
  btvec12 = list2;

  if(btvec12.Root().Element() == 0)
    cout << "Correct!" << endl;
  else{
    cout << "Error!" << endl; errors++; TestPassed &= false;
  }

  

  cout << "END OF BINARY TREE VEC TEST: ("<< errors << "/" << numTest  << ") " ;
  return TestPassed;

}

void mytest2() {
  cout<<endl;
  cout<< " ~ BEGIN MYTEST 2 ~ " << endl<<endl;
  cout<< (TestBinaryTreeLink() ? "All Passed!" : "Error!" )<< endl<<endl;
  cout<<(TestBinaryTreeVec() ? "All Passed!" : "Error!" )<< endl<<endl;
  cout<< " ~ END MYTEST 2 ~ " << endl;
}


#endif



  


