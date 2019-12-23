#ifndef BOOK_HPP
#define BOOK_HPP
#include<iostream>
#include<string>
class Book{
public:
    Book(std::string lastName,std::string firstName,std::string title, int y); //constructor
    virtual std::string author() const = 0;//pure virtual function gets the author
    std::string title() const;//getter for title
    int year() const;//getter for year
    virtual void print(std::ostream &sout) const = 0;//pure virtual print function because (friend) insertion operator cannot be virtual
    friend std::ostream& operator<< (std::ostream &sout, const Book &abook);//friend insertion operator
    friend bool operator <(const Book& left, const Book& right);//< operator overload;
    friend bool operator==(const Book& left,const Book& right);//==operator overload
protected:
    std::string lastName;
    std::string firstName;
    std::string bookTitle;
    int publishedYear;
   
};


#endif
