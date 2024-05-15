
#include "zmytest/test.hpp"

#include "zlasdtest/test.hpp"

#include "zlasdtest/test.hpp"


/* ************************************************************************** */

#include <iostream>
using namespace std;

/* ************************************************************************** */

int main() {

  int choose;
  bool exit = false;

  cout << " ~ Lasd Libraries 2024 ~ " <<endl<<endl;
  while(!exit){
    cout<< "Scegliere il test da eseguire: " << endl<< "1) Eseguire mytest()"<< endl<< "2) Eseguire lasdtest()"<< endl<< "3) Esci"<<endl << "Inserire la scelta: ";
    cin>>choose;
    cout<<endl;
    switch(choose){
      case 1: mytest(); break;
      case 2: lasdtest(); break;
      case 3: exit = true; break;
      default:
        std::cout << "Scelta non valida" << std::endl; break;
    }
    cout<<endl<<endl;
    
  }
  cout<<"Goodbye!"<<endl;

  return 0;

}


