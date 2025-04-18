#include "libibparser.h"

#include <fstream>
#include <sstream>

LibibParser::LibibParser(std::string &csvFile)
{
    _csvFile = csvFile;
}

void LibibParser::setCsvFile(std::string &csvFile) { _csvFile = csvFile; }
std::string LibibParser::CsvFile() { return _csvFile; }

std::vector<std::vector<std::string>> LibibParser::parse(char delimeter, void (*callback)(std::vector<std::string>))
{
    std::vector<std::vector<std::string>> wordLists;
    std::ifstream ifs;
    std::string line;

    try {
        ifs.open(_csvFile);

        while (getline(ifs, line)) {
            std::stringstream ss(line);
            std::string word;
            char del = delimeter;

            std::vector<std::string> wordList;
            while (getline(ss, word, del))
                wordList.push_back(word);

            if (callback != NULL)
                callback(wordList);

            wordLists.push_back(wordList);
        }

        ifs.close();
    }
    catch(std::exception &r) {
        throw r;
    }

    return wordLists;
}

LibibParser::~LibibParser()
{

}
