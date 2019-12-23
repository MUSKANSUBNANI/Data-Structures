#ifndef DOUBLE_LINK_LIST_HPP
#define DOUBLE_LINK_LISH_HPP
// Necessary includes
#include <iostream>
#include<stdexcept>

// CLASS DECLARATIONS
template<typename T>
class List {
public:
    List();// Default constructor
    List(T d);// Constructor that takes first item
    ~List();// Destructor
    List(const List<T> &d);  // Copy constructor 
    List (List<T> &&d);// Move constructor
    const T& front ()const; // function front; l-value
    T& front();// function front; return by value
    const T& back()const;// function back; l-value
    T& back();// function back; return by value
    class iterator;
    class reverse_iterator;
    class const_iterator;
    class const_reverse_iterator;
    iterator begin() noexcept;// function begin
    const_iterator begin() const noexcept;// function begn; const_iterator overload
    iterator end();// function end
    const_iterator end() const noexcept;// function end; const_iterator overload
    reverse_iterator rbegin() noexcept;// function rbegin
    const_reverse_iterator rbegin() const noexcept;// function rbegin; const_reverse_iterator overload
    reverse_iterator rend();// function rend
    const_reverse_iterator rend() const ; // function rend; const_reverse_iterator overload
    const_iterator cbegin() const noexcept;// function cbegin
    const_iterator cend() const noexcept;// function cend
    const_reverse_iterator crbegin() const noexcept;// function crbegin
    const_reverse_iterator crend() const noexcept;// function crend
    iterator search(const T d);// function search; returns iterator            // throws std::invalid_argument
    const_iterator search(const T d) const;// function search; returns const_iterator      // throws std::invalid_argument
    iterator erase(const T d); // function erase; returns iterator to one after what was erased    // throws std::invalid_argument
    iterator erase (const_iterator position);// function erase; overload that takes an iterator to what should be erased // throws std::invalid_argument
    iterator insert (const_iterator position, const T& d);// function insert; takes an iterator to position where insertion occurs as well as item to insert, returns iterator to inserted item
    void push_back (const T& d);// function push_back; //no r value overload??
    void push_front (const T& d);// function push_front;
    iterator emplace(const_iterator position, T &d);// function emplace; takes an iterator to position where insertion occurs as well as item constructor parameters, returns iterator to inserted item
    void emplace_back(T &d);// function emplace_back; takes item constructor parameters
    void emplace_front(T &d);// function emplace_front; takes item constructor parameters
    size_t size() const noexcept;// function size();
    bool empty()const;// function empty();
    List<T>& operator=(const List<T> &other);// Copy assignment operator overload 
    List<T>& operator=( List<T> &&other);// Move assignment operator overload
    
private:
    class Node;
    Node *_front;   //private data of the List
    Node *_back;
    size_t _size;

};   // Whatever data or helper functions you deem necessary

template <typename T>
class List<T>::Node  {   //Node class declaration
    public:
        Node();  //default constructor
        Node(T n);  //constructor that makes a node with data n
        T& getData();//return data in the node
        const T getData() const;  //return data in the node
        Node* getNext() const;  //get the node in front of the current node
        Node* getPrev() const;//gets the node previous to the current node
        void setData(T d);//sets data in the node
        void setNext(Node *n);//set node passed in the parameter as the next node
        void setPrev(Node *n);//set node passed in the parameter as the previous node
    private:  //private data of node class
        T data;
        Node *next;
        Node *prev;
};

template <typename T>
class List<T>::const_iterator {
public:
    const_iterator(Node* n); // Only need one constructor
    const_iterator& operator++(); // function prefix increment operator overload
    const_iterator operator++(int);// function postfix increment operator overload
    const_iterator& operator--();// function prefix decrement operator overload
    const_iterator& operator--(int);// function postfix decrement operator overload
    const T& operator*() const;// function de-reference operator overload; l-value
    T& getresource() const;
    Node* getNode(); //get node pointer
  
    friend bool operator==(const List<T>::const_iterator &lhs, const List<T>::const_iterator &rhs)// Overloaded equality operator
    {
        return lhs.resource == rhs.resource;
    }// function equivalency operator overload
     friend bool operator!=(const List<T>::const_iterator &lhs, const List<T>::const_iterator &rhs)// Overloaded inequality operator
    {
        return lhs.resource != rhs.resource;
    }// function inequivalency operator overload
private:
   const Node *resource;// Node pointer (resource being managed by the iterator) // Resource that iterator manages
 
};

template <typename T>
class List<T>::iterator
{
public:
    iterator(Node* n); // Only need one constructor
    iterator& operator++(); // function prefix increment operator overload
    iterator operator++(int);// function postfix increment operator overload
    iterator& operator--();// function prefix decrement operator overload
    iterator operator--(int);// function postfix decrement operator overload
    T& operator*();// function de-reference operator overload; l-value
    const T& operator*()const;
    Node* getNode();// get node pointer
  
    friend bool operator==(const List<T>::iterator &lhs, const List<T>::iterator &rhs)// Overloaded equality operator
    {
        return lhs.resource == rhs.resource;
    }// function equivalency operator overload
    friend bool operator!=(const List<T>::iterator &lhs, const List<T>::iterator &rhs)// Overloaded inequality operator
    {
        return lhs.resource != rhs.resource;
    }// function inequivalency operator overload
    private:
    Node *resource;
};

template <typename T>
class List<T>::const_reverse_iterator
{
public:
    const_reverse_iterator(Node* n); // Only need one constructor
    const_reverse_iterator& operator++(); // function prefix increment operator overload
    const_reverse_iterator operator++(int);// function postfix increment operator overload
    const_reverse_iterator& operator--();// function prefix decrement operator overload
    const_reverse_iterator operator--(int);// function postfix decrement operator overload
    //T& operator*();// function de-reference operator overload; l-value
    const T& operator*() const;
     //Node* getNode(); get node pointer
  
    friend bool operator==(const List<T>::const_reverse_iterator &lhs, const List<T>::const_reverse_iterator &rhs)// Overloaded equality operator
    {
        return lhs.resource == rhs.resource;
    }// function equivalency operator overload
    friend bool operator!=(const List<T>::const_reverse_iterator &lhs, const List<T>::const_reverse_iterator &rhs)// Overloaded inequality operator
    {
        return lhs.resource != rhs.resource;
    }// function inequivalency operator overload
    private:
    const Node* resource;
};

template <typename T>
class List<T>::reverse_iterator
{
public:
    reverse_iterator(Node* n); // Only need one constructor
    reverse_iterator& operator++(); // function prefix increment operator overload
    reverse_iterator operator++(int);// function postfix increment operator overload
    reverse_iterator& operator--();// function prefix decrement operator overload
    reverse_iterator operator--(int);// function postfix decrement operator overload
    T& operator*();// function de-reference operator overload; l-value
    const T& operator*()const;

     //Node* getNode(); get node pointer
  
    friend bool operator==(const List<T>::reverse_iterator &lhs, const List<T>::reverse_iterator &rhs)// Overloaded equality operator
    {
        return lhs.resource == rhs.resource;
    }// function equivalency operator overload
     friend bool operator!=(const List<T>::reverse_iterator &lhs, const List<T>::reverse_iterator &rhs)// Overloaded inequality operator
    {
        return lhs.resource != rhs.resource;
    }// function inequivalency operator overload
    Node* resource;
};
// CLASS IMPLEMENTATIONS BELOW
//Node class implementation
template<typename T>
List<T>::Node::Node():next(nullptr),prev(nullptr) //default constructor
{
} 
template<typename T>
List<T>::Node::Node(T n):next(nullptr),prev(nullptr) //constructor that makes a node with data n
{
    data=n;
}

template <typename T>
T& List<T>::Node::getData()//return data in the node
{
    return data;
}

template <typename T>
const T List<T>::Node::getData() const  //return data in the node read only
{
    return data;
}

template<typename T>
typename List<T>::Node* List<T>::Node::getNext() const //get the node in front of the current node
{
    return next;
}

template<typename T>
typename List<T>::Node* List<T>::Node::getPrev() const//gets the node previous to the current node
{
    return prev;
}

template<typename T>
void List<T>::Node::setData(T d)//sets data in the node
{
    data=d;
}

template<typename T>
void List<T>::Node::setNext(Node *n)//set node passed in the parameter as the next node
{
    next=n;
}

template<typename T>
void List<T>::Node::setPrev(Node *n)
{
    prev=n;
}

//const_iterator implementation
template<typename T>
T& List<T>::const_iterator::getresource() const
{
    return resource->getData();
}

template<typename T>
List<T>::const_iterator::const_iterator(Node* n):resource(n) // Only need one constructor
{
}

template <typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator++() // function prefix increment operator overload
{
    if(resource!=nullptr)
    {
        resource=resource->getNext();
    }
    return *this;
}

template<typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int)// function postfix increment operator overload
{
    const_iterator temp(resource);
    ++(*this);
    return temp;
}
    
template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--()// function prefix decrement operator overload
{
     if(resource!=nullptr)
    {
        resource=resource->getPrev();
    }
    return *this;
}

template<typename T>
typename List<T>::const_iterator& List<T>::const_iterator::operator--(int)// function postfix decrement operator overload
{
    const_iterator temp(resource);
    --(*this);
    return temp;
}

template<typename T>
const T& List<T>::const_iterator::operator*() const// function de-reference operator overload; l-value
{
    return getresource();
}

template <typename T>
typename List<T>::Node* List<T>::const_iterator::getNode()//gets node pointer associated with iterator
{
    return resource;

}

// iterator implementation
template<typename T>
List<T>::iterator::iterator(Node *n):resource(n)
{
}

template<typename T>
typename List<T>::iterator& List<T>::iterator::operator++() // function prefix increment operator overload
{   if(resource!=nullptr)
    {
        resource=resource->getNext();
    }
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator++(int)// function postfix increment operator overload
{
    iterator temp=*this;
    ++(*this);
    return temp;
}

template<typename T>
typename List<T>::iterator& List<T>::iterator::operator--()// function prefix decrement operator overload
{
    resource=resource->getPrev();
    return *this;
}

template<typename T>
typename List<T>::iterator List<T>::iterator::operator--(int)// function postfix decrement operator overload
{
    iterator temp=*this;
    --(*this);
    return temp;
}

template<typename T>
T& List<T>::iterator:: operator*() // function de-reference operator overload; l-value
{
    return const_iterator::getresource();
}

template<typename T>
const T& List<T>::iterator::operator*() const
{
    return const_iterator::operator*();
}

template <typename T>
typename List<T>::Node* List<T>::iterator::getNode()//gets node pointer associated with iterator
{
    return resource;
}
//const_reverse_iterator implementation
template<typename T>
List<T>::const_reverse_iterator::const_reverse_iterator(Node *n):resource(n)
{
}
template<typename T>
const T& List<T>::const_reverse_iterator::operator*() const
{ 
    return const_iterator::getresource(); 
}

template<typename T>
typename List<T>::const_reverse_iterator& List<T>::const_reverse_iterator::operator++() // function prefix increment operator overload
{   if(resource!=nullptr)
    {
        resource=resource->getPrev();
    }
    return *this;
}

template<typename T>
typename List<T>::const_reverse_iterator List<T>::const_reverse_iterator::operator++(int)// function postfix increment operator overload
{
    iterator temp(resource);
    ++(*this);
    return temp;
}
template<typename T>
typename List<T>::const_reverse_iterator& List<T>::const_reverse_iterator::operator--()// function prefix decrement operator overload
{
    if(resource!=nullptr)
    {
        resource=resource->getNext();
    }
    return *this;
}

template<typename T>
typename List<T>::const_reverse_iterator List<T>::const_reverse_iterator::operator--(int)// function postfix decrement operator overload
{
    iterator temp(resource);
    --(*this);
    return temp;
}
//reverse_iterator implementation
template<typename T>
List<T>::reverse_iterator::reverse_iterator(Node *n):const_reverse_iterator(n)
{
}

template<typename T>
T& List<T>::reverse_iterator::operator*() // function de-reference operator overload; l-value
{
    return const_iterator::getresource();
}

template<typename T>
const T& List<T>::reverse_iterator::operator* () const
{
     return const_reverse_iterator::operator*();
}

template<typename T>
typename List<T>::reverse_iterator& List<T>::reverse_iterator::operator++() // function prefix increment operator overload
{   if(resource!=nullptr)//should you be doing this check
    {
        resource=resource->getPrev();
    }
    return *this;
}

template<typename T>
typename List<T>::reverse_iterator List<T>::reverse_iterator::operator++(int)// function postfix increment operator overload
{
    iterator temp(resource);
    ++(*this);
    return temp;
}

template<typename T>
typename List<T>::reverse_iterator& List<T>::reverse_iterator::operator--()// function prefix decrement operator overload
{
     if(resource!=nullptr)
    {
        resource=resource->getNext();
    }
    return *this;
}

template<typename T>
typename List<T>::reverse_iterator List<T>::reverse_iterator::operator--(int)// function postfix decrement operator overload
{
    iterator temp(resource);
    --(*this);
    return temp;
}

//List Implementation
template<typename T>
List<T>::List():_front(nullptr),_back(nullptr),_size(0)// Default constructor
{
}

template<typename T>
List<T>::List(T d):_front(new Node(d)),_back(_front),_size(1)// Constructor that takes first item
{
}

template<typename T>
List<T>::~List()// Destructor
{
    while (_front != _back)
    {
        Node* temp = _front;
        _front = _front->getNext();
        delete temp;
    }
    delete _front;
    _front = nullptr;
    _back = nullptr;
    _size = 0;
}

template<typename T>
List<T>::List(const List<T> &d):_front(nullptr),_back(nullptr),_size(0)// Copy constructor
{ 
    Node* temp= d._front;
    while(temp!=nullptr)
    {
        this.push_back(temp->getData());
        temp= temp->getNext();
    }
    _size=d._size;
}

template<typename T>
List<T>::List (List<T> &&d):_front(d._front),_back(d._back),_size(d._size)// Move constructor
{
    d._size=0;
    d._front=nullptr;
    d._back=nullptr;
}

template<typename T>
const T& List<T>::front ()const // function front; l-value
{
    return _front->getData();
}

template<typename T>
 T& List<T>::front()// function front; return by value
{
    return _front->getData();
}

template<typename T>
const T& List<T>::back()const// function back; l-value
{
    return _back->getData();
}

template<typename T>
T& List<T>::back()// function back; return by value
{
    return _back->getData();
}

template<typename T>
typename List<T>::iterator List<T>::begin() // function begin
{
    return iterator(_front->getNext());
}

template<typename T>
typename List<T>::const_iterator List<T>::begin() const // function begn; const_iterator overload
{
    return const_iterator(_front->getNext());
}

template<typename T>
typename List<T>::iterator List<T>::end()// function end
{
    return iterator(_back);
}

template<typename T>
typename List<T>::const_iterator List<T>::end() const noexcept// function end; const_iterator overload
{
    return const_iterator(_back);
}

template<typename T>
typename List<T>::reverse_iterator List<T>::rbegin() noexcept// function rbegin
{
    return reverse_iterator(_back->getPrev());
}

template<typename T>
typename List<T>::const_reverse_iterator List<T>::rbegin() const noexcept// function rbegin; const_reverse_iterator overload
{
    return const_reverse_iterator(_back->getPrev());
}

template<typename T>
typename List<T>::reverse_iterator List<T>::rend() // function rend
{
    return iterator(_front);
}

template<typename T>
typename List<T>::const_reverse_iterator List<T>::rend() const // function rend; const_reverse_iterator overload
{
    return const_reverse_iterator(_front);
}

template<typename T>
typename List<T>::const_iterator List<T>::cbegin() const noexcept// function cbegin
{
    return const_iterator(_front->getNext());
}

template<typename T>
typename List<T>::const_iterator List<T>::cend() const noexcept// function cend
{
    return const_iterator(_back);
}

template<typename T>
typename List<T>::const_reverse_iterator List<T>::crbegin() const noexcept// function crbegin
{
    return const_reverse_iterator(_back->getPrev());
}

template<typename T>
typename List<T>::const_reverse_iterator List<T>::crend() const noexcept// function crend
{
    return const_reverse_iterator(_front);
}
template<typename T>
typename List<T>::iterator List<T>::search(const T d)// function search; returns iterator  // throws std::invalid_argument
{
    Node* temp=_front;
    while(_temp->getData()!=d && temp!=nullptr )
    {
        if(_temp->getData()==d)
        {
           break;
        }
        else
        {
            temp=temp->getNext();
        }
        if(temp==nullptr)
        {
            throw std::invalid_argument("Element not found");
        }
        return iterator(temp);
    }
}

template<typename T>
typename List<T>::const_iterator List<T>::search(const T d) const// function search; returns const_iterator// throws std::invalid_argument
{
    Node* temp=_front;
    while(_temp->getData()!=d && temp!=nullptr )
    {
        if(_temp->getData()==d)
        {
           break;
        }
        else
        {
            temp=temp->getNext();
        }
        if(temp==nullptr)
        {
            throw std::invalid_argument("Element not found");
        }
        return const_iterator(temp);
    }
}

template<typename T>
typename List<T>::iterator List<T>::erase(const T d)// function erase; returns iterator to one after what was erased// throws std::invalid_argument
{   try
    {
    iterator it= search(Node(d));
    }
    catch(std::invalid_argument)
    {
        throw std::invalid_argument("element to be erased not found");
    }
    if(_front==it)
    {
         Node* temp=_front;
        _front=_front->getNext();
        delete temp;
        _size=_size-1;
        return iterator(_front);
    }
    else if(_back==it)
    {
        Node* temp=_back;
        _back=_back->getPrev();
        delete temp;
        _size--;
        _back->setNext(nullptr);
        return iterator(nullptr);
    }
    else
    {
        Node *temp=it.getNode();//can also be Node(d)
        Node* previous=temp->getPrev();
        Node* nextnode=temp->getNext();
        previous->setNext(nextnode);
        nextnode->setPrev(previous);
        delete temp;
        _size=_size-1;
        return  iterator(nextnode);
    }
}

template <typename T>
typename List<T>::iterator List<T>::erase (const_iterator position)// function erase; overload that takes an iterator to what should be erased // throws std::invalid_argument
{
     if(_front==position)
    {
         Node* temp=_front;
        _front=_front->getNext();
        delete temp;
        _size=_size-1;
        return iterator(_front);
    }
    else if(_back==position)
    {
        Node* temp=_back;
        _back=_back->getPrev();
        delete temp;
        _size=_size-1;
        _back->setNext(nullptr);
        return  iterator(nullptr);
    }
    else
    {
        Node *temp=it.getNode();//can also be Node(d)
        Node* previous=temp->getPrev();
        Node* nextnode=temp->getNext();
        previous->setNext(nextnode);
        nextnode->setPrev(previous);
        delete temp;
        _size=_size-1;
        return iterator(nextnode);
    }
}

template<typename T>
typename List<T>::iterator List<T>::insert(const_iterator position, const T& d)// function insert; takes an iterator to position where insertion occurs as well as item to insert, returns iterator to inserted item
{   
    Node* newnode=new Node(d);
 
    if(_front==nullptr)
    {
        _front=newnode;
       _front->setPrev(nullptr);
        _back=_front;
        _size++;
    }
    else if(size()==1)//_front and _back point at the same place)
    {
        _front=newnode;
        _front->setNext(_back);
        _back->setPrev(_front);
        _size++;
    }
    else
    {
        Node* posnode= position.getNode();
        Node* posprevnode=posnode->getPrev();
        posnode->setPrev(newnode);
        newnode->setNext(posnode);
        posprevnode->setNext(newnode);
        newnode->setNext(posprevnode);
        _size++;
    }
    return iterator(newnode);
}

template <typename T>
void List<T>::push_back (const T& d)// function push_back; //no r value overload??
{
    insert(end(),d);
}

template<typename T>
void List<T>::push_front (const T& d)// function push_front;
{
    insert(begin(),d);
}

template<typename T>
typename List<T>::iterator List<T>::emplace(const_iterator position, T &d)// function emplace; takes an iterator to position where insertion occurs as well as item constructor parameters, returns iterator to inserted item
{
    iterator it=insert(position,d);
    return it;
}

template<typename T>
void List<T>::emplace_back(T &d)// function emplace_back; takes item constructor parameters
{
    insert(end(),d);
}

template<typename T>
void List<T>::emplace_front(T &d)// function emplace_front; takes item constructor parameters
{
    insert(begin(),d);
}

template<typename T>
size_t List<T>::size() const noexcept// function size();
{
    return _size;
}

template<typename T>
bool List<T>::empty()const// function empty();
{
    return (size()==0);
}

template<typename T>
List<T>& List<T>::operator=(const List<T> &other)// Copy assignment operator overload 
{
 Node* temp= other._front;
    while(temp!=nullptr)
    {
        this.push_back(temp->getData());
        temp= temp->getNext();
    }
    _size=d._size;
    return *this;
}
template<typename T>
List<T>& List<T>::operator=( List<T> &&other)// Move assignment operator overload
{
    if(this!=&other)//delete the stuffs that 
    {                           
        _front=other._front;
        _back=other._back;
        _size=other._size;
        other._front=other._back=nullptr;
        other._size=0;
    }
    return *this;
}

#endif