#include <iostream>
#include "Novel.hpp"

Novel::Novel(std::string lastName,std::string firstName,std::string title, int y)
    : Book(lastName,firstName, title, y)
{
}

std::string Novel::author() const
{
    std::string fullname=firstName;
    fullname+=" ";
   fullname+=lastName;
   return fullname;
}

void Novel::print(std::ostream &sout) const
{    std::string author=this->author();

     sout << "Author: "<<author<< "\n"
         << "Title: " <<bookTitle<< "\n"
         << "Year: " <<publishedYear<< "\n";

}

