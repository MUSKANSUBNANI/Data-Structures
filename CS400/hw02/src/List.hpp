/*
 * Template class that will be used to hold pointers to things
 * Sorted array list, depends on operator< existing for the type being held
 */

#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <iostream>
#include <memory> // std::allocator class
#include <stdexcept> 
#include <utility>// Any necessary includes
#include "Book.hpp"
// It's a template class
template<typename T>
class List {
public:
    List();// Default Constructor
    List(T n);// Constructor that takes first item of list
    List(const List<T> &n);   // Copy ConstructorVector(const Vector<T>& v)
    List (List<T> &&n);// Move Constructor
    ~List();// Destructor
    List<T>& operator=(const List<T> &other);// Copy assignment operator overload 
    List<T>& operator=( List<T> &&other);// Move assignment operator overload
    size_t size() const noexcept ;// function size; does not throw exceptions
    size_t capacity() const noexcept;// function capacity; does not throw exceptions
    void insert (const T &d) noexcept;// function insert; does not throw exceptions
    void erase(T d); // function erase; throws underflow_error if empty, range_error if item doesn't exist
    const T& at(size_t pos) const;  // function at; throws out_of_range exception; returns a const value read only access
    T& at(size_t pos);// function at; throws out_of_range exception; returns l-value
    size_t search(const T d)const;// function search; throws domain error if item doesn't exist
    friend bool operator!=(const List<T>& lhs,const List<T>& rhs)//!= operator overload
    {
        if(lhs._size!=rhs._size)
    {
        return true;
    }
    else
    {   bool flag=true;
        unsigned int i=0;
        while((i<rhs._size) &&flag)
        {
            if(*(lhs.arr+i)== *(rhs.arr+i))
            {
                flag=false;
            }
            i++;
        }
        return flag;
    }
    
}   
private:
    
    T *_begin;// points at the beginning of the list
    T *_end;//points at the end of the array
    T *_capacity;//points at a place in memory up till where room is allocated for list
    static std::allocator<T> alloc;//allocator for the list class
    void sort();
};
// LIST CLASS FUNCTION IMPLEMENTATIONS
template<typename T>
std::allocator<T> List<T>::alloc;//initializing allocator

template<typename T>
List<T>::List():_begin(nullptr),_end(_begin),_capacity(_begin)   //List default constructor//everything is a nullptr
{
}
template <typename T>
List<T>::List(T n) : _begin(alloc.allocate(1)),//parameterized constructor
_end(_begin),
_capacity(_begin+1)
{
    alloc.construct(_end++, n);
}


template<typename T>
List<T>::List(const List<T> &n)//Copy Constructor implementation
{                              
    _begin=alloc.allocate(n.capacity());//allocating room equal to the parameter passed
    _end=_begin;
    _capacity=_begin + n.capacity()-1;
    for(size_t i=0;i<n.size();i++)
    {
        alloc.construct(_end++,n._begin[i]);//constructing elements in this list
    }

}

template<typename T>
List<T>::List(List<T> &&n):_begin(n._begin),_end(n._end),_capacity(n._capacity)//Move Constructor
{   
    n._end=nullptr; //moving pointers and making the previous ones point to nullptr
    n._begin=nullptr;
    n._end=nullptr;
}

template<typename T>
List<T>::~List()//destructor
{ 
     if(_begin!=nullptr)
    {
        while (_end != _begin)//destructing objects from back to front
         alloc.destroy(--_end);  
        alloc.deallocate(_begin,this->capacity());//free the space in memory
    }
}

template<typename T>
List<T>& List<T>:: operator=(const List<T> &other)//copy constructor assignment operator
{
    if(this!=&other)//checking if the lists are equal proceeds only if not equal
    {   
        while (_end != _begin)
            alloc.destroy(--_end);//destructing objects from back to front
        alloc.deallocate(_begin,this->capacity());//free the space in memory
        _begin=alloc.allocate(other.capacity());//new allocation 
        _end=_begin;
        for(size_t i=0;i<other.size();i++)
        {
            alloc.construct(_end++,*(other._begin+i));//copying elements
        }
        _capacity=(_begin + other.capacity());
    }
    return *this;
}

template <typename T>
List<T>& List<T>::operator=(List<T> &&other)//move costructor assignment operator
{    if(this!=&other)//checking if the lists are equal proceeds only if not equal
    {
        while (_end != _begin)
            alloc.destroy(--_end);//destructing objects from back to front
        alloc.deallocate(_begin,this->capacity());//free the space in memory
        _capacity=other._capacity;// transferring ownership
        _begin=other._begin;
        _end=other._end;
       
        other._capacity=other._begin=other._end=nullptr;//making the previous ones point to nullptr
    }
    return *this;
}

template<typename T>
size_t List<T>::size() const noexcept
{    if(_begin==nullptr && _end==nullptr)//size is zero in this case
    {
        return 0;
    }
    return _end-_begin;
}

template<typename T>
size_t List<T>::capacity() const noexcept
{   if(_capacity==nullptr && _begin==nullptr)//capacity is zero in this case
    {
        return 0;
    }
    return _capacity-_begin;
}

template<typename T>
void List<T>::sort()
{   
    T temp;
    for(size_t i=0;i<this->size();i++)
    {
        for(size_t j=i+1;j<this->size();j++)
        {
            if(*_begin[j]<*_begin[i])//comparing list elements
            {
                 temp=_begin[i];   //swapping elements pointers
                _begin[i]=_begin[j];
                _begin[j]=temp;
            }
        }
    }    
}

template<typename T>
void List<T>::insert (const T &d) noexcept
{   this->sort();
    if(this->size()==0)//no elements in the list
    {    this->sort();
        _begin=alloc.allocate(1);  
        _end=_begin;
        alloc.construct(_end++, d); 
        _capacity=_begin+1;
    }
    else if(this->size()<this->capacity())// when there's room for constructing element in the list
    {   this->sort();
        alloc.construct(_end++,d);
    }
    else  //when there's no room i.e. _end==_capcity
    {   T* temp=alloc.allocate(this->capacity()*2);  //new memory allocation
        T* tempend=temp;    
        T* tempcapacity=temp+this->capacity()*2;    
        for(size_t i=0;i<this->size();i++)
        {
          alloc.construct(tempend++,*(_begin+i));
        }
        alloc.construct(tempend++,d);
        while(_begin!=_end)
        alloc.destroy(--_end);
        alloc.deallocate(_begin,capacity());
        _begin=temp;
        _end=tempend;
        _capacity=tempcapacity;

        this->sort();
    }
   this->sort();
}

template <typename T>
size_t List<T>::search(const T d) const //searches the element that is passed throws exception if not found
{   
    for(size_t i=0;i<this->size();i++)
    {
        if(*(_begin+i)==d)
        {
            return i;
        }
    }
    
    throw std::domain_error("Cannot find the element");  
}

template<typename T>
void List<T>::erase(T d)
{   
    size_t loc;
    if(_end==_begin)//when there's nothing to erase
    {
        throw std::underflow_error("No element to erase");
    }
    else 
    {
         
        try
        {
            loc=search(d);  //calls search to return position of element
        }
        catch(std::domain_error &e)
        {
            throw std::range_error("Cannot find the element");//exception thrown if element is not found
        }
        if(loc==this->size()-1) //if the element is the last element
        {
            alloc.destroy(--_end);
        }
        else 
        { for(size_t i=loc;i<this->size()-1;i++)//element in the middle of the list
            {
             *(_begin+i)=*(_begin+(i+1));
              alloc.destroy(--_end);
            }
        } 
    }
   
    this->sort();
}

template<typename T>
const T& List<T>::at(size_t pos) const  //read only at
{  size_t size=_end-_begin;
  if(pos>=size||pos<0)
  {
      throw std::out_of_range("Out of Bound");  //throws exception if out of bound
  }
    return *(_begin+pos);
}

template<typename T>
 T& List<T>:: at(size_t pos)//returns element at the position can be modified
{    
    size_t size=_end-_begin;
    if(pos>=size||pos<0)
    {
      throw std::out_of_range("Out of Bound");//throws exception if out of bound
    }
    return *(_begin+pos);
}

#endif
