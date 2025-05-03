#include "libibparser.h"

#include <fstream>
#include <sstream>

#include "globalvars.h"

LibibParser::LibibParser(std::string csvFile)
{
    _csvFile = csvFile;
}

PUBLIC_SETTER void LibibParser::setCsvFile(std::string csvFile)
{
    _csvFile = csvFile;
}

PUBLIC_GETTER std::string LibibParser::CsvFile()
{
    return _csvFile;
}

PUBLIC std::vector<std::vector<std::string>> LibibParser::parse(char delimeter, void (*ParseCallback)(std::vector<std::string>))
{
    std::vector<std::vector<std::string>> wordLists;
    std::ifstream ifs;
    std::string line;

    try {
        ifs.open(_csvFile);

        for (int i = 0; getline(ifs, line); ++i) {
            if (i == 0)
                continue;

            bool inQuotes = false;

            std::stringstream ss(line);
            std::string word;
            char del = delimeter;

            std::vector<std::string> wordList;
            // while (getline(ss, word, del))
            //    wordList.push_back(word);

            for (int k = 0; k < line.size(); ++k) {
                if (!inQuotes && line[k] == del) {
                    wordList.push_back(word);
                    word.clear();
                }
                else if (line[k] == '"')
                    inQuotes = !inQuotes;
                else
                    word += line[k];
            }

             wordList.push_back(word); // for last word.

            if (ParseCallback != NULL)
                ParseCallback(wordList);

            wordLists.push_back(wordList);
        }

        ifs.close();
    }
    catch(std::exception &r) {
        throw r;
    }

    return wordLists;
}

PUBLIC Libib LibibParser::readLine(const std::vector<std::string> &line, void (*LibibCallback)(Libib))
{
    Libib libib;
    const std::string dateStrFormat = "%Y-%m-%d";
    int size = line.size();
    int step = 0;

    if (step++ < size)
        libib.setItemType(line[0]);
    if (step++ < size)
        libib.setTitle(line[1]);
    if (step++ < size)
        libib.setCreators(line[2]);
    if (step++ < size)
        libib.setFirstName(line[3]);
    if (step++ < size)
        libib.setLastName(line[4]);

    if (step++ < size) {
        try {
            if (line[5] != "")
                libib.setEAN_ISBN13(std::stoull(line[5], nullptr, 0));
        }
        catch (std::exception &r) {
            std::string msg = "Cannot convert to EAN_ISBN13 in LibibParser::readLine() ";
            msg.append(r.what());
            throw std::exception(msg.c_str());
        }
    }

    if (step++ < size) {
        try {
            if (line[6] != "")
                libib.setUPC_ISBN10(std::stoull(line[6], nullptr, 0));
        }
        catch (std::exception &r) {
            std::string msg = "Cannot convert to UPC_ISBN10 in LibibParser::readLine() ";
            msg.append(r.what());
            throw std::exception(msg.c_str());
        }
    }

    if (step++ < size)
        libib.setDescription(line[7]);
    if (step++ < size)
        libib.setPublisher(line[8]);
    if (step++ < size)
        libib.setPublishDate(line[9]);

    if (step++ < size)
        libib.setGroup(line[10]);
    if (step++ < size)
        libib.setTags(line[11]);
    if (step++ < size)
        libib.setNotes(line[12]);

    if (step++ < size)
        try {
            if (line[13] != "")
                libib.setPrice(std::stod(line[13], nullptr));
        }
        catch (std::exception &r) {
            std::string msg = "Cannot convert to Price in LibibParser::readLine() ";
            msg.append(r.what());
            throw std::exception(msg.c_str());
        }

    if (step++ < size && line[14] != "")
        libib.setLength(atoi(line[14].c_str()));

    if (step++ < size && line[15] != "")
        libib.setNumberOfDiscs(atoi(line[15].c_str()));

    if (step++ < size && line[16] != "")
        libib.setNumberOfPlayers(atoi(line[16].c_str()));

    if (step++ < size && line[17] != "")
        libib.setAgeGroup(atoi(line[17].c_str()));

    if (step++ < size)
        libib.setEnsemble(line[18]);
    if (step++ < size)
        libib.setAspectRatio(line[19]);
    if (step++ < size)
        libib.setESRB(line[20]);

    if (step++ < size)
        try {
            if (line[21] != "")
                libib.setRating(std::stod(line[21], nullptr));
        }
        catch (std::exception &r) {
            std::string msg = "Cannot convert to Rating in LibibParser::readLine() ";
            msg.append(r.what());
            throw std::exception(msg.c_str());
        }

    if (step++ < size)
        libib.setReview(line[22]);
    if (step++ < size)
        libib.setPublishDate(line[23]);
    if (step++ < size)
        libib.setStatus(line[24]);
    if (step++ < size)
        libib.setBegan(line[25]);
    if (step++ < size)
        libib.setCompleted(line[26]);
    if (step++ < size)
        libib.setAdded(line[27]);

    if (step++ < size && line[28] != "")
        libib.setCopies(atoi(line[28].c_str()));

    if (LibibCallback != nullptr)
        LibibCallback(libib);

    return libib;
}

LibibParser::~LibibParser()
{

}
