#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <stdexcept>
#include <queue>
template <typename T>
class BST {
public:

    class Node;
    BST();// Default Ctor
    BST(T r);//parameterized ctor
    BST(const BST &source);// Copy Ctor
    BST (BST<T> &&source);// Move Ctor
    ~BST();/// Dtor

    class preorder_iterator;
    class inorder_iterator;
    class postorder_iterator;
    preorder_iterator prbegin();// function prbegin; pr = preorder
    preorder_iterator prend();// function prend
    inorder_iterator begin();
    inorder_iterator end();
    postorder_iterator pobegin();// function pobegin; po = postorder
    postorder_iterator poend();// function poend

    bool empty()const; // function empty; does not throw exceptions
    const T& min() const; // function min; l-value, throws underflow if empty
    T& min();// function min; read-only, throws underflow if empty
    const T& max() const;// function max; l-value, throws underflow if empty
    T& max();// function max; read-only, throws underflow if empty

    void insert( T data);// function insert; does not throw exceptions
    template<typename ...Args>
    void emplace(Args&&... args); // function emplace; does not throw exceptions
    void erase(const T d); // function erase; takes a type T, throws invalid_argument if empty or cannot be found
    void clear();// function clear; does not throw exceptions

    BST<T>& operator=(const BST<T> &other);// Copy assignment operator overload 
    BST<T>& operator=( BST<T> &&other);// Move assignment operator overload// copy assignment operator overload
   
private:
    Node* _root;
    Node* remove( const T data , Node* root);
    void inserthelper(Node* n, T data);
    void copyTree(Node* sourceRoot);
    void DestroyRecursive(Node* root);
    Node* findMin(Node* root) const;
    Node* findMax(Node* root) const;
    void assign(Node* c);
    // Private data and helper functions go here
};

// NODE CLASS
template <typename T>
class BST<T>::Node {
public:
    Node();
    Node(T d);
    T& key ();
    const T key() const;
    Node* getparent() const;
    Node* getleft() const;
    Node* getright() const;
    void setkey(T d);//sets data in the node
    void setparent(Node *n);//set node passed in the parameter as the next node
    void setleft(Node *n);
    void setright(Node *n);
    // Public Node Functions
private:
    T data;
    Node* parent;
    Node* left;
    Node* right;
    // Private data and helper functions for BST<T>::Node
};

// PREORDER_ITERATOR CLASS
template <typename T>
class BST<T>::preorder_iterator {
public:
    preorder_iterator(Node *curr);
    T& operator*();
    preorder_iterator& operator++();
    preorder_iterator operator++(int);
     friend bool operator==(const typename BST<T>::preorder_iterator &lhs,  const typename BST<T>::preorder_iterator &rhs)
    {
        return lhs.PreQ == rhs.PreQ ;
    }
    friend bool operator!=(const typename BST<T>::preorder_iterator &lhs,  const typename BST<T>::preorder_iterator &rhs)
    {
        return !(lhs == rhs);
    }

private:
    std::queue<Node*> PreQ;
    void preorder(Node* curr);
};

// INORDER_ITERATOR CLASS
template <typename T>
class BST<T>::inorder_iterator {
public:
    inorder_iterator(Node *curr);
    T& operator*();
    inorder_iterator& operator++();
    inorder_iterator operator++(int);
    friend bool operator==(const typename BST<T>::inorder_iterator &lhs,  const typename BST<T>::inorder_iterator &rhs)
    {
        return lhs.InQ == rhs.InQ ;
    }
    friend bool operator!=(const typename BST<T>::inorder_iterator &lhs,  const typename BST<T>::inorder_iterator &rhs)
    {
        return !(lhs == rhs);
    }
private:
    std::queue<Node*> InQ;
    void inorder(Node* curr);
};

// POSTORDER_ITERATOR CLASS
template <typename T>
class BST<T>::postorder_iterator {
public:
    postorder_iterator(Node *curr);
    T& operator*();
    postorder_iterator& operator++();
    postorder_iterator operator++(int);
    friend bool operator==(const typename BST<T>::postorder_iterator &lhs,  const typename BST<T>::postorder_iterator &rhs)
    {
        return lhs.PoQ== rhs.PoQ ;
    }
    friend bool operator!=(const typename BST<T>::postorder_iterator &lhs,  const typename BST<T>::postorder_iterator &rhs)
    {
        return !(lhs == rhs);
    }

private:
    
    std::queue<Node*> PoQ; //post order queue
    void postorder(Node* curr);
};


// BST FINCTOPMS
template<typename T>
BST<T>::BST() : _root(nullptr) 
{

}// Default Ctor

template<typename T>
BST<T>::BST(T r):_root(new Node(r)) //parameterized constructor
{
}


template <typename T>
BST<T>::BST(const BST &source) : _root(nullptr)  //copy constructor
{
    if(source._root != nullptr)
        copyTree( source._root);
}


template<typename T>
BST<T>::BST(BST &&source):_root(source._root)
{
    source._root=nullptr;
}

template<typename T>
void BST<T>::copyTree(Node* sourceRoot)
{
    if(sourceRoot!=nullptr)
    {
        insert(sourceRoot->key());
         if(sourceRoot->getleft()!=nullptr)
             copyTree(sourceRoot->getleft());
         if(sourceRoot->getright()!=nullptr)
             copyTree(sourceRoot->getright());
    }

}

template<typename T>
BST<T>::~BST()
{
    DestroyRecursive(_root);
}

template<typename T>
void BST<T>::DestroyRecursive(Node* root)
{
    if (root!=nullptr)
    {
        DestroyRecursive(root->getleft());
        DestroyRecursive(root->getright());
        delete root;
    }

}

template<typename T>
typename BST<T>::preorder_iterator BST<T>::prbegin()// function prbegin; pr = preorder
{
    return(preorder_iterator(_root));
}

template <typename T>
typename BST<T>::preorder_iterator BST<T>::prend()// function prend
{
    return (preorder_iterator(nullptr));
}
    
template<typename T>
typename BST<T>::inorder_iterator BST<T>::begin()
{ 

    return(inorder_iterator(_root));
}

template <typename T>
typename BST<T>::inorder_iterator BST<T>::end()
{
    return(inorder_iterator(nullptr));
} 

template<typename T>
typename BST<T>::postorder_iterator BST<T>::pobegin()// function pobegin; po = postorder
{ 
   return(postorder_iterator(_root));
}

template <typename T>
typename BST<T>::postorder_iterator BST<T>::poend()
{
    return postorder_iterator(nullptr);

}

template<typename T>
bool BST<T>::empty()const// function empty; does not throw exceptions
{
    if(_root==nullptr)
        return true;
    return false;
}

template<typename T>
const T& BST<T>::min() const // function min; l-value, throws underflow if empty
{
    Node* minnode=findMin(_root);
    if(minnode==nullptr)
    {
         throw std::underflow_error("No elements");
    }
    return minnode->key();
}

template<typename T>
T& BST<T>::min()// function min; read-only, throws underflow if 
{
    Node* minnode=findMin(_root);
    if(minnode==nullptr)
    {
        throw std::underflow_error("No elements");
    }
    return minnode->key();

}

template<typename T>
const T& BST<T>::max() const// function max; l-value, throws underflow if empty
{
    Node* maxnode=findMax(_root);
    if(maxnode==nullptr)
    {
        throw std::underflow_error("No elements");
    }
    return maxnode->key();
}

template<typename T>
T& BST<T>::max()
{
    Node* maxnode=findMax(_root);
    if(maxnode==nullptr)
    {
        throw std::underflow_error("No elements");
    }
    return maxnode->key();
}

template<typename T>
void BST<T>::insert(T data)
{   if(_root==nullptr)
    {
        _root = new Node(data);
    }
    else
    {
        inserthelper(_root, data);
    }
}  

template<typename T>
void BST<T>::erase(const T data)
{   if(_root==nullptr)
    {    
        throw std::invalid_argument( "empty tree" );
        
    }
    remove(data,_root);
}

template<typename T>
typename BST<T>::Node* BST<T>::remove(const T data,Node* root) //erase helper
{
    Node* temp =new Node();
    if(root == nullptr)
        return nullptr;
    else if(data < root->key())
        root->setleft( remove(data, root->getleft()));
    else if(data > root->key())
        root->setright( remove(data, root->getright()));
    else if(root->getleft()!=nullptr && root->getright()!=nullptr)
    {
        temp = findMin(root->getright());
        root->setkey(temp->key());
        root->setright(remove(root->key(), root->getright()));
    }
    else
    {
        temp = root;
        if(root->getleft() == nullptr)
            root = root->getright();
        else if(root->getright() == nullptr)
            root = root->getleft();
        delete temp;
    }
    return root;
}

template<typename T>
template<typename ...Args>
void BST<T>::emplace(Args&&... args)// function emplace_front; takes item constructor parameters
{   T* newT=new T(std::forward<Args>(args)...);//construct item 
    insert(*newT);//call to emplace
}

template<typename T>
typename BST<T>::Node* BST<T>::findMin(Node* root) const
{
    if(root == nullptr)
        return nullptr;
    else if(root->getleft() == nullptr)
        return root;
    else
        return findMin(root->getleft());
}

template<typename T>
typename BST<T>::Node* BST<T>::findMax(Node* root) const
{
    if(root == nullptr)
        return nullptr;
    else if(root->getright() == nullptr)
        return root;
    else
        return findMax(root->getright());
}


template<typename T>
void BST<T>::inserthelper(Node* n, T data) //isert helper to insert data
{
    {
        if (data < n->key())  //left insertion
        {

            if (n->getleft()==nullptr)
            {
                Node *treeTemp = new Node(data);
                n->setleft(treeTemp);
                treeTemp->setparent(n);
            }
            else
                inserthelper(n->getleft(), data);
        }
        else
        {
            if (n->getright()==nullptr)  //right insertion
            {                   
                n->setright(new Node(data));
                n->getright()->setparent(n);
            }
            else
                inserthelper(n->getright(), data);
        }
    }
}

template<typename T>
void BST<T>::clear()
{
    DestroyRecursive(_root); //recursively deletes all nodes
    _root=nullptr;
}

template<typename T>
BST<T>& BST<T>::operator=(const BST& other) //assignment operator
{
    if(this != &other)
    {
        this->clear();
        Node *c = other._root;
        assign(c);
        other->clear();
    }
    
    return *this;
}

template<typename T>
void BST<T>::assign(Node *c) //assign helper
{
    if (c != nullptr)
    {
        this->insert(c->key());
        assign(c->getleft());
        assign(c->getright());
    }
}

// NODE FUNCTIONS
template<typename T>
BST<T>::Node::Node():parent(nullptr),left(nullptr),right(nullptr)//default constructor
{
}

template<typename T>
BST<T>::Node::Node(T d):data(d),parent(nullptr),left(nullptr),right(nullptr)//constructor that makes a node with data n
{
}


template <typename T>
T& BST<T>::Node::key()//return data in the node
{
    return data;
}

template <typename T>
const T BST<T>::Node::key() const  //return data in the node read only
{
    return data;
}

template<typename T>
typename BST<T>::Node* BST<T>::Node::getparent() const //get the node in front of the current node
{
    return parent;
}

template<typename T>
typename BST<T>::Node* BST<T>::Node::getleft() const//gets the node previous to the current node
{
    return left;
}

template<typename T>
typename BST<T>::Node* BST<T>::Node::getright() const
{
    return right;
}

template<typename T>
void BST<T>::Node::setkey(T d)//sets data in the node
{
    data=d;
}

template<typename T>
void BST<T>::Node::setparent(Node *n)//set node passed in the parameter as the next node
{
    parent=n;//assigning parent
}

template<typename T>
void BST<T>::Node::setleft(Node *n)
{
    left=n;//assigning left
}

template<typename T>
void BST<T>::Node::setright(Node *n)
{
    right=n; //assigning right
}

// PREORDER_ITERATOR FUNCTIONS
template<typename T>
BST<T>::preorder_iterator::preorder_iterator(Node *curr):PreQ()
{   if(curr!=nullptr)
    {
         preorder(curr); //preorder queue
    }
}

template<typename T>
T& BST<T>::preorder_iterator::operator*()
{
   return PreQ.front()->key();
}

template<typename T>
void BST<T>::preorder_iterator::preorder(Node* node) {
    if (node == nullptr) 
    {
        return; 
    }
    PreQ.push(node);    // first print data of node 
    preorder(node->getleft());  // now recur on the left subtree
    preorder(node->getright());   // now recur on right subtree 
}

template<typename T>
typename BST<T>::preorder_iterator& BST<T>::preorder_iterator::operator++()
{       
    if(PreQ.empty()!=true)
    {      
       PreQ.pop(); //poping off the node  
    }
   
    return *this;
}

template <typename T>
typename BST<T>::preorder_iterator BST<T>::preorder_iterator::operator++(int)
{
    preorder_iterator tmp = *this;
    ++(*this);
    return tmp;
}

// INORDER_ITERATOR FUNCTIONS
template<typename T>
BST<T>::inorder_iterator::inorder_iterator(Node *curr):InQ()
{   if(curr!=nullptr)
    {
        inorder(curr);//inorder walk
    }
}

template <typename T>
T& BST<T>::inorder_iterator::operator*()
{
   return InQ.front()->key();
}

template<typename T>
void BST<T>::inorder_iterator::inorder(Node* node)
{
    if (node == nullptr) 
        return; 
    inorder(node->getleft()); /* then recur on left sutree */
    InQ.push(node); //push the node
    inorder(node->getright()); /* now recur on right subtree */

}

template<typename T>
typename BST<T>::inorder_iterator& BST<T>::inorder_iterator::operator++()
{       
    if(InQ.empty()!=true)
    {      
       InQ.pop();//popping off he elements
    }
   
    return *this;
}

template <typename T>
typename BST<T>::inorder_iterator BST<T>::inorder_iterator::operator++(int)
{
    inorder_iterator tmp = *this;
    ++(*this);

    return tmp;
}
// POSTORDER_ITERATOR FUNCTIONS
template<typename T>
BST<T>::postorder_iterator::postorder_iterator(Node *curr):PoQ()
{   if(curr!=nullptr)
    {
        postorder(curr);
    }
}

template<typename T>
T& BST<T>::postorder_iterator::operator*()
{
   return PoQ.front()->key();//front of the queue is the first element
}

template<typename T>
void BST<T>::postorder_iterator::postorder(Node* node) {
    if (node == nullptr) 
        return; 
    postorder(node->getleft());  // first recur on left subtree 
    postorder(node->getright());     // then recur on right subtree 
    PoQ.push (node) ;// now deal with the node 
}

template<typename T>
typename BST<T>::postorder_iterator& BST<T>::postorder_iterator::operator++()
{       
    if(PoQ.empty()!=true)
    {    //using std::queue
        
        PoQ.pop();
    }
    return *this;
}

template <typename T>
typename BST<T>::postorder_iterator BST<T>::postorder_iterator::operator++(int)
{
    postorder_iterator tmp = *this;
    ++(*this);
    return tmp;
}

#endif