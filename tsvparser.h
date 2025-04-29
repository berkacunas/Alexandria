#ifndef TSVPARSER_H
#define TSVPARSER_H

#include <string>
#include <vector>

#include "libib.h"

class TsvParser {

    std::string _dbFile;
    std::string _tsvFile;
    std::string _tableName;
    std::vector<std::string> _columns;

    std::vector<std::string> getWordList(std::string, char del);

public:
    TsvParser();

    void setDbFile(std::string);
    void setTsvFile(std::string);

    std::string dbFile();
    std::string tsvFile();
    std::string tableName();
    std::vector<std::string> columns();

    std::vector<std::vector<std::string>> parse(char delimeter = '|', bool dropTableIfExists = false, void (*ParseCallback)(std::vector<std::string>) = nullptr);
    Libib readLine(const std::vector<std::string> &line, void (*LibibCallback)(Libib) = nullptr);
};

#endif
