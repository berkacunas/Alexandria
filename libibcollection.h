#ifndef LIBIBCOLLECTION_H
#define LIBIBCOLLECTION_H

#include <string>
#include <vector>

#include "Libib.h"

std::string listToStr(std::vector<std::string> list);

class LibibCollection
{
    std::vector<Libib> _libibs;

public:
    LibibCollection();

    std::vector<Libib> Libibs() { return _libibs; }

    Libib readLine(const std::vector<std::string> &line);
    void addItem(Libib libib);
};

#endif // LIBIBCOLLECTION_H
