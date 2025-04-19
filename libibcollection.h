#ifndef LIBIBCOLLECTION_H
#define LIBIBCOLLECTION_H

#include <string>
#include <vector>

#include "Libib.h"

class LibibCollection
{
    std::vector<Libib> _libibs;

public:
    LibibCollection();

    Libib readLine(const std::vector<std::string> &line);
    void addItem(Libib &libib);
};

#endif // LIBIBCOLLECTION_H
