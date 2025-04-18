#include "libibcollection.h"


#include <iomanip>
#include <sstream>
#include <cstdlib>
#include "globalvars.h"

PUBLIC LibibCollection::LibibCollection()
{

}

PUBLIC Libib LibibCollection::parseLine(std::vector<std::string> line)
{
    Libib libib;
    const std::string dateStrFormat = "%YYYY-%mm-%dd";


    libib.ItemType = line[0];
    libib.Title = line[1];
    libib.Creators = line[2];
    libib.FirstName = line[3];
    libib.LastName = line[4];

    std::istringstream ss_EAN_ISBN13(line[5]);
    ss_EAN_ISBN13 >> libib.EAN_ISBN13;

    std::istringstream ss_UPC_ISBN10(line[6]);
    ss_UPC_ISBN10 >> libib.UPC_ISBN10;

    libib.Description = line[7];
    libib.Publisher = line[8];

    std::istringstream ss_publishDate(line[9]);
    ss_publishDate >> std::get_time(&libib.PublishDate, "%Y-%m-%d");

    libib.Group = line[10];
    libib.Tags = line[11];
    libib.Notes = line[12];

    std::istringstream ss_Price(line[13]);
    ss_Price >> libib.Price;

    libib.Length = atoi(line[14].c_str());
    libib.NumberOfDiscs = atoi(line[15].c_str());
    libib.NumberOfPlayers = atoi(line[16].c_str());
    libib.AgeGroup = atoi(line[17].c_str());
    libib.Ensemble = line[18];
    libib.AspectRatio = line[19];
    libib.ESRB = line[20];

    std::istringstream ss_Rating(line[21]);
    ss_Rating >> libib.Rating;

    libib.Review = line[22];

    std::istringstream ss_reviewDate(line[23]);
    ss_reviewDate >> std::get_time(&libib.ReviewDate, dateStrFormat.c_str());

    libib.Status = line[24];

    std::istringstream ss_Began(line[25]);
    ss_Began >> std::get_time(&libib.Began, dateStrFormat.c_str());

    std::istringstream ss_Completed(line[26]);
    ss_Completed >> std::get_time(&libib.Completed, dateStrFormat.c_str());

    std::istringstream ss_Added(line[27]);
    ss_Added >> std::get_time(&libib.Added, dateStrFormat.c_str());

    libib.Copies = atoi(line[28].c_str());

    return libib;
}

PUBLIC void LibibCollection::addItem(Libib &libib)
{
    _libibs.push_back(libib);
}
