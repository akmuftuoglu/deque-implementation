//
//  main.cpp
//  HW3 PIC10C
//

#include <iostream>
#include <functional>
#include <algorithm>
#include <cassert>
#include <memory>

#include "Safedeque.h"

using namespace std;

int main()
{
    cout << "********** print empty deque *********" << endl;
    Safedeque<int> sd;
    sd.print();
    cout << "********** add elements *********" << endl;
    // add elements
    sd.push_front(1);
    sd.push_front(2);
    sd.pop_back();
    sd.push_front(3);
    sd.push_back(4);
    sd.push_back(5);
    sd.push_front(6);
    sd.push_back(7);
    sd.print();
    cout << "********* real array elements**********" << endl;
    sd.real_print();
    cout << "********** element squares *********" << endl;
    
    Iterator<int> iter1 = sd.begin();
    Iterator<int> iter2 = sd.end();
    
    //cout << *iter1 << endl;
    
    return 0;
    
}
