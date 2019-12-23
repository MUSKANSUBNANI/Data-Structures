#ifndef GRAPHIC_NOVEL_HPP
#define GRAPHIC_NOVEL_HPP


#include <iostream>
#include "Book.hpp"
class GraphicNovel : public Book
{
public:
    GraphicNovel(std::string firstName,std::string lastName, std::string ill, std::string title, int y);
    std::string author() const override;

    void print(std::ostream &sout) const override;
private:
    std::string illustrator;

};

#endif
