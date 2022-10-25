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
        T get_front();
        T get_back();
        void push_front(T input);
        void push_back(T input);
        void pop_front();
        void pop_back();
        Iterator<T> begin();
        Iterator<T> end();
        void print();
        void real_print();
        
    

    
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
    

    public:
        Iterator();
        void operator++()       //prefix ++
        {
            position++;
        }
        void operator++(int)    //postfix ++
        {
            position++;
        }
        void operator--()       //prefix --
        {
            position--;
        }
        void operator--(int)    //postfix --
        {
            position--;
        }
        T& operator*(size_t)
        {
            return position;
        };
        void operator=(Iterator<T> const &rhs)
        {
            this->position = rhs.position;
            this->container = rhs.container;
        };
        bool operator!=(Iterator<T> const &rhs) const;
    
    private:
        T* position;
        Safedeque<T>* container;
        template<typename U>
        friend class Safedeque;
    
};

/* START OF SAFEDEQUE IMPLEMENTATIONS */

template<typename T>
Safedeque<T>::Safedeque() {
    
    sz = 0;
    cap = 0;
}

template<typename T>
T Safedeque<T>::get_front() {
    return *front;
}

template<typename T>
T Safedeque<T>::get_back() {
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
        cap = cap*2;
        
        T* temp = new T[cap];
        T* frontMark = front;
        T* restOfData = &data[0];
        temp[0] = input;
        
        int i = 1;
        
        while(frontMark != &data[sz])
        {
            temp[i] = *frontMark;
            i++;
            frontMark++;
        }
        
        
        while(i < sz+1)
        {
            temp[i] = *restOfData;
            i++;
            restOfData++;
        }
        
        data = temp;
            
        back = &data[sz];
        front = &data[0];
        sz++;
        
        std::cout << "Capacity doubled. Current capacity: " << cap << std::endl;
    
        return;
        
    }
    
    // if size of deque does not equal capacity:
    if (front == &data[0])
    {
        front = &data[sz];
        *front = input;
        sz++;
        return;
    }

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
        cap = cap*2;
        
        T* temp = new T[cap];
        T* frontMark = front;
        T* restOfData = &data[0];
        temp[sz] = input;
        
        //T* endpoint = &data[sz];
        int i = 0;
        
        while(frontMark != &data[sz])
        {
            temp[i] = *frontMark;
            i++;
            frontMark++;
        }
        
        
        while(i < sz)
        {
            temp[i] = *restOfData;
            i++;
            restOfData++;
        }
        
        
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
    
    back--;
    sz--;
}


template<typename T>
Iterator<T> Safedeque<T>::begin() {
    
    iter.position = &data[0];
    iter.container = this;
    
    return iter;
    
}


template<typename T>
Iterator<T> Safedeque<T>::end() {
    
    iter.position = &data[cap];
    iter.container = this;
    
    return iter;
    
}

template<typename T>
void Safedeque<T>::print() {
    
    T* frontMark = front;
    T* untilEnd = &data[0];
    T* afterBack = back;
    afterBack++;
    
    int counter = 0;
    

    while(frontMark != &data[sz] && counter < sz)
    {
        std::cout << *frontMark << " ";
        frontMark++;
        counter++;
    }
    
    if (untilEnd == back)
    {
        std::cout << *untilEnd << " ";
        untilEnd++;
        counter++;
    }
    
    while (untilEnd != afterBack && counter < sz)
    {
        std::cout << *untilEnd << " ";
        untilEnd++;
        counter++;

    }
    
    std::cout << std::endl;
    
}

template<typename T>
void Safedeque<T>::real_print() {
    
    for (int i = 0; i < cap; i++)
    {
        std::cout << data[i] << " ";
    }
}

/* END OF SAFEDEQUE IMPLEMENTATIONS */

/* START OF ITERATOR IMPLEMENTATIONS */

template<typename T>
Iterator<T>::Iterator() {
    
    container = nullptr;
    position = nullptr;

}


/* END OF ITERATOR IMPLEMENTATIONS */

#endif /* Safedeque_h */
