#include "Movie.h"

Movie::Movie(int id, const std::string& title) : id(id), title(title)
{
}

int Movie::getId()
{
    return id;
}

std::string Movie::getTitle()
{
    return title;
}
