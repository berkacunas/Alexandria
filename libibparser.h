#ifndef LIBIBPARSER_H
#define LIBIBPARSER_H

#include <string>
#include <vector>

#include "Libib.h"
#include "globalvars.h"

class LibibParser
{
    std::string _csvFile;

public:
    LibibParser(std::string csvFile);

    void setCsvFile(std::string csvFile);
    std::string CsvFile();
    std::vector<std::vector<std::string>> parse(char delimeter = ',', void (*ParseCallback)(std::vector<std::string>) = nullptr);
    Libib readLine(const std::vector<std::string> &line, void (*LibibCallback)(Libib) = nullptr);

    ~LibibParser();
};

#endif // LIBIBPARSER_H
