/*
 * Template class that will be used to hold pointers to things
 * Sorted array list, depends on operator< existing for the type being held
 */

#ifndef ARRAY_LIST_HPP
#define ARRAY_LIST_HPP

#include <iostream>
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
    int size() noexcept;// function size; does not throw exceptions
    int capacity() noexcept;// function capacity; does not throw exceptions
    void insert (const T &d) noexcept;// function insert; does not throw exceptions
    void erase(T d); // function erase; throws underflow_error if empty, range_error if item doesn't exist
    const T& at(unsigned int pos) const;  // function at; throws out_of_range exception; returns a const value read only access
    T& at(unsigned int pos);// function at; throws out_of_range exception; returns l-value
    int search(const T d);// function search; throws domain error if item doesn't exist
    friend bool operator!=(const List<T>& lhs,const List<T>& rhs)
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
        //!= operator overload
    
private:
    void sort();
    T *data;// variable that gives us our dynamic array
    unsigned int _size;
    unsigned int _capacity;
};


// LIST CLASS FUNCTION IMPLEMENTATIONS
template<typename T>
List<T>::List():_size(0),_capacity(0)   //List default constructor
{
    data=nullptr;
}
template<typename T>
List<T>::List(T n) //parametirzed constructor
{
   _size=1;
   _capacity=_size;
   data=new T[_size];
   *data=n;

}
template<typename T>
List<T>::List(const List<T> &n)//Copy Constructor
{
  _size=n._size;
  _capacity=n._size;
   data= new T[_size];
    for(unsigned int i=0;i<_size;i++)
    {
        *(data+i)=*(n.data+i);
    }

}

template<typename T>
List<T>::List(List<T> &&n)//Move Constructor
{   _size=n._size;
    _capacity=n._capacity;
        data=n.data;
        if(n.data!=nullptr){
        n.data=nullptr;
        n._size=0;
        n._capacity=0;
        }
}
template<typename T>
List<T>::~List()//destructor
{  if(data!=nullptr)
{
    delete [] data;
    data=nullptr;
    _size=_capacity=0;
}
}

template<typename T>
List<T>& List<T>:: operator=(const List<T> &other)
{
    if(this!=&other)
    {
        delete [] data;
        _size=other._size;
        _capacity=other._size;
        data=new T[_size];
        for(unsigned int i=0;i<_size;i++)
        {
            *(data+i)=*(other.data+i);
        }

    }
    return *this;
}
template <typename T>
List<T>& List<T>::operator=(List<T> &&other)
{
    if(this!=&other)
    {
        delete [] data;
        _size=other._size;
        _capacity=other._size;

        data=other.data;
        other._size=other._capacity=0;
        other.data=nullptr;

    }
    return *this;
}
template<typename T>
int List<T>::size() noexcept
{
    return _size;
}
template<typename T>
int List<T>::capacity() noexcept
{
    return _capacity;
}
template<typename T>
void List<T>::sort()
{
    T temp;
    for(unsigned int i=0;i<this->_size;i++)
    {
        for(unsigned int j=i+1;j<this->_size;j++)
        {
            if(*data[j]<*data[i])
            {
                temp=data[i];
                data[i]=data[j];
                data[j]=temp;
            }
        }

    }

    
}
template<typename T>
void List<T>::insert (const T &d) noexcept
{   this->sort();
    if(_capacity==0)
    { this->sort();
        _size++;
        _capacity=_size;
        data=new T[_size];
        *data=d;
    }
    else if(_size<_capacity)
    { this->sort();
        _size++;
        *(data+(_size-1))=d;
        this->sort();
    }
    else
    {  
          T *temp=new T[_size*2];
        for(unsigned int i=0;i<_size;i++)
        {
          temp[i]= *(data+i);
        }
        temp[_size]=d;
        delete [] data;
        data=nullptr;
        _capacity=_size*2;
        _size=_size+1;
        data=temp;

        this->sort();
    }
   this->sort();
}

template <typename T>
int List<T>::search(const T d)
{
    for(unsigned int i=0;i<_size;i++)
    {
        if(*(data+i)==d)
        {
            return i;
        }
    }
    
        throw std::domain_error("Cannot find the element");  
}
template<typename T>
void List<T>::erase(T d)
{
    unsigned int loc;
    if(_size==0)
    {
        throw std::underflow_error("No element to erase");
    }
    else {
         
          try
          {
              loc=search(d);
          }
          catch(std::domain_error &e)
          {
              throw std::range_error("Cannot find the element");
          }
        if(loc==_size-1)
        {
            _size--;

        }
        else 
        { for(unsigned int i=loc;i<_size-1;i++)
        {
           *(data+i)=*(data+(i+1));
           _size--;
        }
        
        }
        
       
    }
   
    this->sort();
}
template<typename T>
const T& List<T>::at(unsigned int pos) const
{

  if(pos>=_size ||pos<0)
  {
      throw std::out_of_range("Out of Bound");
  }
  
      return *(data+pos);
  
}
template<typename T>
 T& List<T>:: at(unsigned int pos)
 {
      if(pos>=_size ||pos<0)
  {
      throw std::out_of_range("Out of Bound");
  }
      return *(data+pos);
 }


#endif
