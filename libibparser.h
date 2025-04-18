#ifndef LIBIBPARSER_H
#define LIBIBPARSER_H

#include <string>
#include <vector>

class LibibParser
{
    std::string _csvFile;

public:
    LibibParser(std::string &csvFile);

    void setCsvFile(std::string &csvFile);
    std::string CsvFile();
    std::vector<std::vector<std::string>> parse(char delimeter = ',', void (*callback)(std::vector<std::string>) = NULL);

    ~LibibParser();
};

#endif // LIBIBPARSER_H
