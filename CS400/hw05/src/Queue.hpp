#ifndef QUEUE__HPP
#define QUEUE__HPP
#include <iostream>
#include <utility>
#include "List.hpp"
template <typename T>
class Queue {
public:
    Queue();// Default Constructor
    Queue(T d);// Parameterized Constructor
    Queue(const Queue<T> &d);// Copy Constructor
    Queue(Queue<T> &&d);// Move Constructor
    ~Queue();// Destructor
    bool empty()const;// function empty; does not throw exceptions
    size_t size() const noexcept;// function size; does not throw exceptions
    T& front();// function front, l-value, throws underflow is queue is empty
    const T& front()const;// function front, read-only, throws underflow if queue is empty
    T& back();// function back, l-value, throws underflow
    const T& back()const;// function back, read-only, throws underflow
    void push (const T& d);// function push, does not throw exceptions
    template<typename ...Args>
    void emplace(Args&&... args);// function emplace, does not throw exceptions
    void pop();// function pop, throws underflow
    Queue<T>& operator=(const Queue<T> &other);// Copy assignment operator overload
    Queue<T>& operator=(Queue<T> &&other);// Move assignment operator overload
private:
    List<T> Queuelist;// Private data / underlying container
};

// QUEUE IMPLEMENTATION
template <typename T>
Queue<T>::Queue()  //default constructor
{
    
}

template <typename T>
Queue<T>::Queue(T d) //paramenterized constructor
{
    Queuelist.push_back(d);
}

template<typename T>
Queue<T>::Queue(const Queue<T> &d):Queuelist(d.Queuelist)  //copies data from one queue to another
{

}

template<typename T>
Queue<T>::Queue(Queue<T> &&d) :Queuelist(std::move(d.Queuelist))//moves one queue to another
{

}

template<typename T>
Queue<T>::~Queue()// destructor
{
    
}

template<typename T>
bool Queue<T>::empty() const //checks if queue is empty
{
    return Queuelist.empty();
}

template<typename T>
size_t Queue<T>::size() const noexcept
{
    return Queuelist.size(); //returns queue's size
}

template<typename T>
T& Queue<T>:: front()// function front, l-value, throws underflow is queue is empty
{
    if(Queuelist.empty()==true)
  {
    throw std::underflow_error("no element in Queue");
  }
    return Queuelist.front();//return data pointed by front pointer
}

template<typename T>
const T& Queue<T>::front()const// function front, read-only, throws underflow if queue is empty
{
   if(Queuelist.empty()==true)
  {
    throw std::underflow_error("no element in Queue");
  }
    return Queuelist.front();//front pointer
}

template<typename T>
T& Queue<T>:: back()// function back, l-value, throws underflow
{
    if(Queuelist.empty()==true)
  {
    throw std::underflow_error("no element in Queue");
  }
    return Queuelist.back();//return data pointed by back pointer
}

template<typename T>
const T& Queue<T> :: back()const 
{
    if(Queuelist.empty()==true)
  {
    throw std::underflow_error("no element in Queue");
  }
    return Queuelist.back();//back pointer

}

template <typename T>
void Queue<T>::push(const T& d)
{
    Queuelist.push_back(d);//inserts new node at the back of the queue
}

template <typename T>
template<typename ...Args>
void Queue<T>::emplace(Args&&... args)
{
    Queuelist.emplace_back(args...);//constucts and inserts new node at the back of the queue
}


template <typename T>
void Queue<T>::pop()  //dequeue operation at the back of the queue
{   if(Queuelist.empty()==true)
    {
        throw std::underflow_error("no elements to delete");
    }
   T topdata= Queuelist.front();
   Queuelist.erase(topdata);   

}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T> &other)// Copy assignment operator overload
{
     Queuelist=other.Queuelist;
     return *this;
}

template<typename T>
Queue<T>& Queue<T>::operator=( Queue<T> &&other) // move assignment operator overload
{
    Queuelist=std::move(other.Queuelist);
    return *this;
}



#endif