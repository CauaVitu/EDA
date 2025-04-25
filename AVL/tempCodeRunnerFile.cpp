#include <iostream>
#include "Set.hpp"
#include "set_operations.hpp"
#include <random>
int main(){
    Set set1,set2;
    for (int i = 0; i < 30; i++){
       set1.insert(i);
    }
    set1.show();
    set1.predecessor(3);
    std::cout << std::endl;
    return 0;
}