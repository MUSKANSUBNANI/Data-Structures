#ifndef STACK_CLASS_HPP
#define STACK_CLASS_HPP

#include "List.hpp"

template <typename T>
class Stack {
public:
    Stack();// default constructor
    Stack(T d);// parameterized constructor that takes first item
    Stack(const Stack<T> &d);  // Copy constructor 
    Stack(Stack<T> &&d); // move constructor
    ~Stack();// Destructor
    bool empty()const;// function empty; does not throw exceptions
    size_t size() const noexcept;// function size; does not throw exceptions
    const T& top()const; // function top; read-only; throws underflow if stack is empty
    T& top();// function top; l-value; throws underflow if stack is empty
    void push (const T& d);// function push_back;// function push; does not throw exceptions
    template<typename ...Args>
    void emplace(Args&&... args);// function emplace; does not throw exceptions
    void pop();// function pop; throws underflow if stack is empty
    Stack<T>& operator=(const Stack<T> &other);// Copy assignment operator overload 
    Stack<T>& operator=( Stack<T> &&other); // move assignment operator overload
   
private:
    // Private data
    List<T> stacklist;
};
template <typename T>
Stack<T>::Stack()
{
    
}
template <typename T>
Stack<T>::Stack(T d)
{
    stacklist.push_back(d);
}
template<typename T>
Stack<T>::Stack(const Stack<T> &d)
{
   stacklist=d.stacklist;

}
template<typename T>
Stack<T>::Stack(Stack<T> &&d)
{
    stacklist= std::move(d.stacklist);
}
template<typename T>
Stack<T>::~Stack()
{
    
}
template<typename T>
bool Stack<T>::empty() const
{
    return stacklist.empty();
}
template<typename T>
size_t Stack<T>::size() const noexcept
{
    return stacklist.size();
}
template <typename T>
const T& Stack<T>::top() const
{
  if(stacklist.empty()==true)
  {
    throw std::underflow_error("no element in stack");
  }
    return stacklist.front();
}
template <typename T>
T& Stack<T>::top()
{
   if(stacklist.empty()==true)
  {
    throw std::underflow_error("no element in stack");
  }
    return stacklist.front();
}

template <typename T>
void Stack<T>::push(const T& d)
{
    stacklist.push_front(d);
}
// STACK FUNCTIONS

template <typename T>
template<typename ...Args>
void Stack<T>::emplace(Args&&... args)
{
    stacklist.emplace_front(args...);
}
template <typename T>
void Stack<T>::pop()
{   if(stacklist.empty()==true)
    {
        throw std::underflow_error("no elements to delete");
    }
   T topdata= stacklist.front();
   stacklist.erase(topdata);

}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T> &other)// Copy assignment operator overload
{
     stacklist=other.stacklist;
     return *this;
}
template<typename T>
Stack<T>& Stack<T>::operator=( Stack<T> &&other) // move assignment operator overload
{
    stacklist=std::move(other.stacklist);
    return *this;
}



#endif