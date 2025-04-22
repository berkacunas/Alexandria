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

PUBLIC Libib LibibCollection::readLine(const std::vector<std::string> &line)
{
    Libib libib;
    const std::string dateStrFormat = "%Y-%m-%d";

    libib.setItemType(line[0]);
    libib.setTitle(line[1]);
    libib.setCreators(line[2]);
    libib.setFirstName(line[3]);
    libib.setLastName(line[4]);

    try {
        if (line[5] != "")
            libib.setEAN_ISBN13(std::stoull(line[5], nullptr, 0));
    }
    catch (std::exception &r) {
        std::string msg = "Cannot convert to EAN_ISBN13 in LibibCollection::readLine() ";
        msg.append(r.what());
        throw std::exception(msg.c_str());
    }

    try {
        if (line[6] != "")
            libib.setUPC_ISBN10(std::stoull(line[6], nullptr, 0));
    }
    catch (std::exception &r) {
        std::string msg = "Cannot convert to UPC_ISBN10 in LibibCollection::readLine() ";
        msg.append(r.what());
        throw std::exception(msg.c_str());
    }

    libib.setDescription(line[7]);
    libib.setPublisher(line[8]);
    libib.setPublishDate(line[9]);

    libib.setGroup(line[10]);
    libib.setTags(line[11]);
    libib.setNotes(line[12]);

    try {
        if (line[13] != "")
            libib.setPrice(std::stod(line[13], nullptr));
    }
    catch (std::exception &r) {
        std::string msg = "Cannot convert to Price in LibibCollection::readLine() ";
        msg.append(r.what());
        throw std::exception(msg.c_str());
    }

    if (line[14] != "")
        libib.setLength(atoi(line[14].c_str()));

    if (line[15] != "")
        libib.setNumberOfDiscs(atoi(line[15].c_str()));

    if (line[16] != "")
        libib.setNumberOfPlayers(atoi(line[16].c_str()));

    if (line[17] != "")
        libib.setAgeGroup(atoi(line[17].c_str()));

    libib.setEnsemble(line[18]);
    libib.setAspectRatio(line[19]);
    libib.setESRB(line[20]);

    try {
        if (line[21] != "")
            libib.setRating(std::stod(line[21], nullptr));
    }
    catch (std::exception &r) {
        std::string msg = "Cannot convert to Rating in LibibCollection::readLine() ";
        msg.append(r.what());
        throw std::exception(msg.c_str());
    }

    libib.setReview(line[22]);
    libib.setPublishDate(line[23]);
    libib.setStatus(line[24]);
    libib.setBegan(line[25]);
    libib.setCompleted(line[26]);
    libib.setAdded(line[27]);

    if (line[28] != "")
        libib.setCopies(atoi(line[28].c_str()));

    return libib;
}

PUBLIC void LibibCollection::addItem(Libib libib)
{
    _libibs.push_back(libib);
}

PUBLIC int LibibCollection::size()
{
    return _libibs.size();
}
