#ifndef LIBIB_H
#define LIBIB_H

#include <string>
#include <ctime>

class Libib {

public:

    std::string ItemType;
    std::string Title;
    std::string Creators;
    std::string FirstName;
    std::string LastName;
    std::string EAN_ISBN13;
    std::string UPC_ISBN10;
    std::string Description;
    std::string Publisher;
    tm PublishDate;
    std::string Group;
    std::string Tags;
    std::string Notes;
    unsigned long int Price;
    int Length;
    int NumberOfDiscs;
    int NumberOfPlayers;
    int AgeGroup;
    std::string AspectRatio;
    std::string Ensemble;
    std::string ESRB;
    unsigned long int Rating;
    std::string Review;
    tm ReviewDate;
    std::string Status ;
    tm Began;
    tm Completed;
    tm Added;
    int Copies;
 };

#endif // LIBIB_H

