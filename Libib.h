#ifndef LIBIB_H
#define LIBIB_H

#include <string>

class Libib {

public:

    std::string ItemType;
    std::string Title ;
    std::string Creators;
    std::string FirstName;
    std::string LastName;
    std::string EAN_ISBN13;
    std::string UPC_ISBN10;
    std::string Description;
    std::string Publisher;
    struct tm PublishDate;
    std::string Group;
    std::string Tags;
    std::string Notes;
    long long int Price;
    int Length;
    std::string Ensemble;
    std::string ESRB;
    long long int Rating;
    std::string Review;
    std::string ReviewDate;
    std::string Status ;
    std::string Began;
    std::string Completed;
    std::string Added;
    int Copies;
 };

#endif // LIBIB_H

