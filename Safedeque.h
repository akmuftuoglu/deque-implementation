#pragma once

/*
PIC 10C Homework 1, Safedeque.h
Purpose:
Author: Aral Muftuoglu
Date: 10/25/2021
*/

#ifndef Safedeque_h
#define Safedeque_h

#include <iostream>
#include <iomanip>
#include <cassert>

template<typename T>
class Iterator;

template<typename T>
class Safedeque {

public:
    Safedeque();
    T& get_front();
    T& get_back();
    void push_front(T input);
    void push_back(T input);
    void pop_front();
    void pop_back();
    const Iterator<T> begin();
    const Iterator<T> end();
    int size();
    int capacity();
    void print();
    void real_print();
    T& operator[](int) const;

    // helper functions
    T* endOfDataArray();    // to help move iterator position
    T* startOfDataArray();  // to help move iterator position
    void printData();       // used to keep track of the raw array of data
    int frontIndex();       // to help with print functions
    int backIndex();        // to help with print functions

private:
    T* data;
    int cap;
    int sz;
    T* front;
    T* back;
    Iterator<T> iter;
    template<typename U>
    friend class Iterator;

};

template<typename T>
class Iterator {

    // function implementations are put here because they are shorter and easier to locate
public:
    Iterator()
    {
        container = nullptr;
        position = nullptr;
    };
    void operator++()       //prefix ++
    {
        T* afterBack = container->back;
        afterBack++;

        assert(position != afterBack);

        if (position == container->endOfDataArray())
        {
            position = container->startOfDataArray();
        }
        else
        {
            position++;
        }

    }
    void operator++(int)    //postfix ++
    {
        T* afterBack = container->back;
        afterBack++;
        assert(position != afterBack);

        if (position == container->endOfDataArray())
        {
            position = container->startOfDataArray();
        }
        else
        {
            position++;
        }
    }
    void operator--()       //prefix --
    {
        T* afterBack = container->back;
        afterBack++;

        // cannot point to beginning of data array and then go backwards

        assert(position != container->front);
        if (position == container->startOfDataArray())
        {
            position = afterBack;
        }
        else
        {
            position--;
        }
    }
    void operator--(int)    //postfix --
    {
        T* afterBack = container->back;
        afterBack++;


        // cannot point to beginning of data array and then go backwards

        assert(position != container->front);

        if (position == container->startOfDataArray())
        {
            position = afterBack;
        }
        else
        {
            position--;
        }
    }
    T& operator*()
    {
        T* afterBack = container->back;
        afterBack++;
        assert(position != afterBack);
        return *position;
    }
    void operator=(Iterator<T> const& rhs)
    {
        this->position = rhs.position;
        this->container = rhs.container;
    }
    bool operator!=(Iterator<T> const& rhs) const
    {
        if (this->position != rhs.position)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

private:
    T* position;
    Safedeque<T>* container;
    template<typename U>
    friend class Safedeque;
};

/* START OF SAFEDEQUE IMPLEMENTATIONS */

template<typename T>
Safedeque<T>::Safedeque() {
    
    back = nullptr;
    front = nullptr;
    sz = 0;
    cap = 0;
}

template<typename T>
T& Safedeque<T>::get_front() {

    assert(sz != 0);
    return *front;  
}

template<typename T>
T& Safedeque<T>::get_back() {

    assert(sz != 0);
    return *back;  
}

template<typename T>
void Safedeque<T>::push_front(T input) {


    if (cap == 0)
    {
        cap++;
        data = new T[cap];
        data[0] = input;
        sz++;

        front = &data[0];
        back = &data[0];

        std::cout << "One spot added. Current capacity: " << cap << std::endl;
        return;
    }

    if (cap == sz)
    {
        cap = cap * 2;

        T* temp = new T[cap];
        T* frontMark = front;
        T* restOfData = &data[0];
        temp[0] = input;

        int i = 1;

        // put data into temp
        while (frontMark != &data[sz])
        {
            temp[i] = *frontMark;
            i++;
            frontMark++;
        }

        while (i < sz + 1)
        {
            temp[i] = *restOfData;
            i++;
            restOfData++;
        }

        // assigned data to new array
        data = temp;

        // assign back and front and increase size
        back = &data[sz];
        front = &data[0];
        sz++;

        std::cout << "Capacity doubled. Current capacity: " << cap << std::endl;

        return;

    }

    // if size of deque does not equal capacity:
    if (front == &data[0])
    {
        front = &data[cap - 1];
        *front = input;
        sz++;
        return;
    }

    // if size of deque does not equal capacity:

    front--;
    *front = input;
    sz++;


}

template<typename T>
void Safedeque<T>::push_back(T input) {

    if (cap == 0)
    {
        cap++;

        data = new T[cap];

        data[0] = input;
        sz++;

        front = &data[0];
        back = &data[0];

        std::cout << "One spot added. Current capacity: " << cap << std::endl;

        return;
    }

    if (cap == sz)
    {
        cap = cap * 2;

        T* temp = new T[cap];
        T* frontMark = front;
        T* restOfData = &data[0];
        temp[sz] = input;

        int i = 0;

        // put data elements to temp 
        while (frontMark != &data[sz])
        {
            temp[i] = *frontMark;
            i++;
            frontMark++;
        }

        while (i < sz)
        {
            temp[i] = *restOfData;
            i++;
            restOfData++;
        }

        // assign temp to data

        data = temp;
        back = &data[sz];
        front = &data[0];
        sz++;

        std::cout << "Capacity doubled. Current capacity: " << cap << std::endl;

        return;

    }


    // if size of deque does not equal capacity:

    back++;
    *back = input;
    sz++;


}

template<typename T>
void Safedeque<T>::pop_back() {

    assert(sz != 0);

    // if the back is at the front of the array, move back to the index at the end of the data array 
    // you cannot just delete the element to remove it, you have to manipulate the back tracker
    
    // since a deque can be viewed as a circular array you need to check this condition 
    // to move it from the "front" of the array to the "back" of the array

    if (back == &data[0])
    {
        back = &data[cap - 1];
        sz--;
        return;
    }

    back--;
    sz--;
}

template<typename T>
void Safedeque<T>::pop_front() {

    assert(sz != 0);

    // if the front is at the back of the array, move front to the index at the front of the data array (which is decrementing it)
    // you cannot just delete the element to remove it, so you have to manipulate the front marker

    // since a deque can be viewed as a circular array you need to check this condition 
    // to move it from the "back" of the array to the "front" of the array

    if (front == &data[cap - 1])
    {
        front = &data[0];
        sz--;
        return;
    }

    front++;
    sz--;
}

template<typename T>
const Iterator<T> Safedeque<T>::begin() {

    iter.position = front;
    iter.container = this;
    return iter;
}

template<typename T>
const Iterator<T> Safedeque<T>::end() {

    T* afterBack = back;
    afterBack++;

    iter.position = afterBack;
    iter.container = this;
    return iter;
}

template<typename T>
int Safedeque<T>::size() {
    return sz;
}

template<typename T>
int Safedeque<T>::capacity() {
    return cap;
}

template<typename T>
void Safedeque<T>::print() {

    // follows similar logic to real_print() except you wont print *

    if (cap == 0)
    {
        std::cout << std::endl;
        return;
    }

    if (frontIndex() > backIndex())
    {
        for (int i = frontIndex(); i < cap; i++)
        {
            std::cout << data[i] << " ";
        }

        for (int i = 0; i < backIndex() + 1; i++)
        {
            std::cout << data[i] << " ";
        }

        std::cout << std::endl;
        return;
    }
    else if (frontIndex() < backIndex())
    {
        for (int i = frontIndex(); i < backIndex() + 1; i++)
        {
            std::cout << data[i] << " ";
        }

        std::cout << std::endl;
        return;
    }
    else // size is 1
    {
        std::cout << data[frontIndex()] << " ";
        std::cout << std::endl;
        return;
    }

}

template<typename T>
void Safedeque<T>::real_print() {

    // there are three main cases when printing the array
    
    // if the front index is after the back index, then that means the first elements of data must be elements
    // then there MAY be * between the back and the front
    // it would look like this: X X X B * * F X (the * could be elements too but then that would mean the B and F are next to each other)
    // if the the B and F are neighbors -> then the data array is full and you can just print from front to back
    // if there are *, you start from index 0 then print to B then print * until F then print F until the end


    // if the front index is before the back index, then that means from front to back, they will be in order (bc of how i implemented push functions)
    // it could look like this -> F X X X X X X X B or  * F X X X X X B * or other variations
    // so you have to print * up to front (if there are *), then print front to back then print * until the end (if there are *)


    // if the front index and back index are the same: 
    // the size is 1 and all you have to do is print * up to that index (if there are *) and then print the index (if not printed)
    // and then print * after (if there are *)


    if (frontIndex() > backIndex())
    {
        for (int i = 0; i < backIndex() + 1; i++)
        {
            std::cout << data[i] << " ";
        }

        for (int i = backIndex() + 1; i < frontIndex(); i++)
        {
            std::cout << '*' << " ";
        }

        for (int i = frontIndex(); i < cap; i++)
        {
            std::cout << data[i] << " ";
        }

        std::cout << std::endl;
        return;
    }
    else if (frontIndex() < backIndex())
    {
        for (int i = 0; i < frontIndex(); i++)
        {
            std::cout << '*' << " ";
        }

        for (int i = frontIndex(); i < backIndex() + 1; i++)
        {
            std::cout << data[i] << " ";
        }

        for (int i = backIndex(); i < cap - 1; i++)
        {
            std::cout << '*' << " ";
        }

        std::cout << std::endl;
        return;
    }
    else
    {
        for (int i = 0; i < frontIndex(); i++)
        {
            std::cout << '*' << " ";
        }

        std::cout << data[frontIndex()] << " ";

        for (int i = frontIndex() + 1; i < cap; i++)
        {
            std::cout << '*' << " ";
        }

        std::cout << std::endl;
        return;
    }
}

template<typename T>
T& Safedeque<T>::operator[](int x) const
{
    assert(x < cap);
    T* index = &data[x];
    return *index;
}


// helper functions

template<typename T>
T* Safedeque<T>::endOfDataArray() {

    return &data[cap - 1];
}


template<typename T>
T* Safedeque<T>::startOfDataArray() {

    return &data[0];
}


// im just going to keep this here because I was using it to see the raw contents of the data array
template<typename T>
void Safedeque<T>::printData() {

    for (int i = 0; i < cap; i++)
    {
        std::cout << data[i] << " ";
    }

    std::cout << std::endl;
}

template<typename T>
int Safedeque<T>::frontIndex() {

    int index = 0;

    for (T* ptr = &data[0]; ptr != front; ptr++)
    {
        index++;
    }
    return index;
}

template<typename T>
int Safedeque<T>::backIndex()
{
    int index = 0;

    for (T* ptr = &data[0]; ptr != back; ptr++)
    {
        index++;
    }
    return index;
}

/* END OF SAFEDEQUE IMPLEMENTATIONS */


#endif /* Safedeque_h */
