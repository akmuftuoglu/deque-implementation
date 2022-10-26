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
        const Iterator<T> begin();
        const Iterator<T> end();
        void print();
        void real_print();
        T& operator[](int);
            
        // helper functions
        T* endOfData();
        T* startOfData();
        void printData();
        T* afterEndOfData();
        int frontIndex();
        int backIndex();

    
        
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
            T* afterBack = container->back;
            afterBack++;
            
            assert(position != afterBack);
            
            if (position == container->endOfData())
            {
                position = container->startOfData();
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
            
            if (position == container->endOfData())
            {
                position = container->startOfData();
            }
            else
            {
                position++;
            }
        }
        void operator--()       //prefix --
        {
            //assert(position != container->startOfData());
            position--;
        }
        void operator--(int)    //postfix --
        {
            //assert(position != container->startOfData());
            position--;
        }
        T& operator*()
        {
            return *position;
        };
        void operator=(Iterator<T> const &rhs)
        {
            this->position = rhs.position;
            this->container = rhs.container;
        };
        bool operator!=(Iterator<T> const &rhs) const
        {
            if (this->position != rhs.position)
            {
                return true;
            }
            else
            {
                return false;
            }
        };

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
        front = &data[cap-1];
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
    
    if (back == &data[0])
    {
        back = &data[cap-1];
        return;
    }
    back--;
    sz--;
}

template<typename T>
void Safedeque<T>::pop_front() {
    
    if (front == &data[cap-1])
    {
        front = &data[0];
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
    
    iter.position = afterBack++;;
    iter.container = this;
    return iter;
}

template<typename T>
void Safedeque<T>::print() {
    
    T* printer = front;
    T* afterLastElement = back;
    afterLastElement++;
    int printedCount = 0;
    
    while(printer != &data[cap] && printer != afterLastElement && printedCount != sz)
    {
        std::cout << *printer << " ";
        printedCount++;
        printer++;
    }
    
    if (printedCount == sz)
    {
        std::cout << std::endl;
        return;
    }
    
    if (printer == &data[cap])
    {
        printer = &data[0];
        
        while (printer != afterLastElement && printedCount != sz)
        {
            std::cout << *printer << " ";
            printedCount++;
            printer++;
        }
    }
    
    std::cout << std::endl;
}


template<typename T>
void Safedeque<T>::real_print() {
    
    if (frontIndex() > backIndex())
    {
        for (int i = 0; i < backIndex()+1; i++)
        {
            std::cout << data[i] << " ";
        }
        
        for (int i = backIndex()+1; i < frontIndex(); i++)
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
        
        for (int i = frontIndex(); i < backIndex()+1; i++)
        {
            std::cout << data[i] << " ";
        }
        
        for (int i = backIndex(); i < cap-1; i++)
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
        
        for (int i = frontIndex()+1; i < cap; i++)
        {
            std::cout << '*' << " ";
        }
        
        std::cout << std::endl;
        return;
    }
}

template<typename T>
T& Safedeque<T>::operator[](int x)
{
    assert(x < cap);
    T* index = &data[x];
    return *index;
}


// helper functions

template<typename T>
T* Safedeque<T>::endOfData() {
    
    return &data[cap-1];
}


template<typename T>
T* Safedeque<T>::startOfData() {
    
    return &data[0];
}

template<typename T>
void Safedeque<T>::printData() {
    
    for (int i = 0; i < cap; i++)
    {
        std::cout << data[i] << " ";
    }
    
    std::cout << std::endl;
}


template<typename T>
T* Safedeque<T>::afterEndOfData() {
    
    return &data[cap];
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

/* START OF ITERATOR IMPLEMENTATIONS */

template<typename T>
Iterator<T>::Iterator() {
    
    container = nullptr;
    position = nullptr;

}


/* END OF ITERATOR IMPLEMENTATIONS */

#endif /* Safedeque_h */
