#include "GraphicNovel.hpp"


GraphicNovel::GraphicNovel(std::string lastName,std::string firstName,std::string ill, std::string title, int y):
    Book(lastName,firstName,title, y),illustrator(ill)
    {

    }
    std::string GraphicNovel::author() const
    {
        std::string fullname=firstName;
       fullname+=" ";
       fullname+=lastName;
       return fullname;

    }
    void GraphicNovel::print(std::ostream &sout) const
    {   std::string author=this->author();
        sout << "Author: " << author << "\n"
         << "Illustrator: " << illustrator << "\n"
         << "Title: " << bookTitle << "\n"
         << "Year: " << publishedYear << "\n";

    }
