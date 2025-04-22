#include "libibcollection.h"

#include <cstdlib>
#include "globalvars.h"

std::string listToStr(std::vector<std::string> list)
{
    std::string s = "";
    int size = list.size();

    for (int i = 0; i < size; ++i) {
        if (i == size - 1)
            s = s.substr(0 , size - 2);
        s += list[i] + " ";
    }

    return s;
}

PUBLIC LibibCollection::LibibCollection()
{

}



PUBLIC void LibibCollection::addItem(Libib libib)
{
    _libibs.push_back(libib);
}

PUBLIC int LibibCollection::size()
{
    return _libibs.size();
}
