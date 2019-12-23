#ifndef NOVEL_HPP
#define NOVEL_HPP
#include <iostream>
#include "Book.hpp"

class Novel : public Book
{ public:
    Novel(std::string lastName,std::string firstName,std::string title, int y);
    std::string author() const override;
    void print(std::ostream &sout) const override;
private:
};

#endif
