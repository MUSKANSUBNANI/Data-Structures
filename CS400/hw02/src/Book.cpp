#include "Book.hpp"

Book::Book(std::string lastName,std::string firstName, std::string title, int y)
:lastName(lastName),
firstName(firstName),
bookTitle(title),
publishedYear(y)
{

}

std::string Book::title()const
{
    return bookTitle;
}
int Book::year()const
{
    return publishedYear;
}
std::ostream& operator<< (std::ostream &sout, const Book &abook)
{
    abook.print(sout);
    return sout;
}

bool operator <(const Book& left, const Book& right)
 { 
     if(left.lastName<right.lastName)
    {
        return true;
    }
    else if(left.lastName>right.lastName)
    {
        return false;
    }
    else
    {
        if(left.firstName<right.firstName)
        {
            return true;
        }
        else if (left.firstName>right.firstName)
        {
            return false;
        }
        else
        {
            if(left.bookTitle<right.bookTitle)
            {
                return true;
            }
            else 
            {
                return false;
            }
        }
        
    }
  

 }
  bool operator==(const Book& left,const Book& right)
  {
      if((left.firstName==right.firstName) &&( left.lastName==right.lastName) &&
      (left.bookTitle==right.bookTitle) &&(left.publishedYear==right.publishedYear))
      {
      return true;
      }
      else{
          return false;
      }
  }

