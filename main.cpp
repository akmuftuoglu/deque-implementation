

//main

#include <iostream>
#include <functional>
#include <algorithm>
#include "Safedeque.h"

using namespace std;

int main()
{
    Safedeque<char> sd;
   
    cout << "********** add elements *********" << endl;
    // add elements
    sd.push_front('5');
    sd.push_front('4');
    sd.push_front('3');
    sd.push_back('6');
    sd.push_back('7');
    sd.push_front('2');
    sd.push_front('1');
    sd.push_back('8');
    sd.push_back('9');
    sd.push_front('0');
    sd.push_front('-');
    sd.push_back('A');
    sd.push_back('B');
    
    cout << "********** Test Iterators (must appear in this order) *********" <<
endl;
    auto iter1 = sd.end();
    iter1--;
    iter1--;
    auto iter2 = sd.begin();
    iter2++;
    iter2++;
    ++iter2;
    ++iter2;
    for_each(iter2, iter1, [](char &x){cout<< x << " "; x = '!';});
    cout << "\n********* deque (must appear in this order) **********" << endl;
    sd.print();
    cout << "********* real array **********" << endl;
    sd.real_print();
     
    return 0;
}
