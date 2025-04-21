#include "Libib.h"


#include <iomanip>
#include <sstream>
#include "globalvars.h"

PUBLIC Libib::Libib()
{
    _itemType = "";
    _title = "";
    _creators = "";
    _firstName = "";
    _lastName = "";
    _EAN_ISBN13 = 0;
    _UPC_ISBN10 = 0;
    _description = "";
    _publisher = "";
    _publishDate = {};
    _group = "";
    _tags = "";
    _notes = "";
    _price = 0;
    _length = 0;
    _numberOfDiscs = 0;
    _numberOfPlayers = 0;
    _ageGroup = 0;
    _aspectRatio = "";
    _ensemble = "";
    _ESRB = "";
    _rating = 0;
    _review = "";
    _reviewDate = {};
    _status = "";
    _began = {};
    _completed = {};
    _added = {};
    _copies = 0;
}

PUBLIC void Libib::setItemType(std::string itemType) { _itemType = itemType; }
PUBLIC void Libib::setTitle(std::string title) { _title = title; }
PUBLIC void Libib::setCreators(std::string creators) { _creators = creators; }
PUBLIC void Libib::setFirstName(std::string firstName) { _firstName = firstName; }
PUBLIC void Libib::setLastName(std::string lastName) { _lastName = lastName; }
PUBLIC void Libib::setEAN_ISBN13(unsigned long long EAN_ISBN13) { _EAN_ISBN13 = EAN_ISBN13; }
PUBLIC void Libib::setUPC_ISBN10(unsigned long long UPC_ISBN10) { UPC_ISBN10 = UPC_ISBN10; }
PUBLIC void Libib::setDescription(std::string description) { _description = description; }
PUBLIC void Libib::setPublisher(std::string publisher) { _publisher = publisher; }

PUBLIC void Libib::setPublishDate(std::string publishDateStr)
{
    std::istringstream ss(publishDateStr);
    ss >> std::get_time(&_publishDate, dateformat);

    _added.tm_mon += 1;
    _added.tm_year += 1900;
}

PUBLIC void Libib::setGroup(std::string group) { _group = group; }
PUBLIC void Libib::setTags(std::string tags) { _tags = tags; }
PUBLIC void Libib::setNotes(std::string notes) { _notes = notes; }
PUBLIC void Libib::setPrice(unsigned long long price) { _price = price; }
PUBLIC void Libib::setLength(int length) { _length = length; }
PUBLIC void Libib::setNumberOfDiscs(int numberOfDiscs) { _numberOfDiscs = numberOfDiscs; }
PUBLIC void Libib::setNumberOfPlayers(int numberOfPlayers) { _numberOfPlayers = numberOfPlayers; }
PUBLIC void Libib::setAgeGroup(int ageGroup) { _ageGroup = ageGroup; }
PUBLIC void Libib::setAspectRatio(std::string aspectRatio) { _aspectRatio = aspectRatio; }
PUBLIC void Libib::setEnsemble(std::string ensemble) { _ensemble = ensemble; }
PUBLIC void Libib::setESRB(std::string ESRB) {_ESRB = ESRB;  }
PUBLIC void Libib::setRating(double rating) { _rating = rating; }
PUBLIC void Libib::setReview(std::string review) { _review = review; }

PUBLIC void Libib::setReviewDate(std::string reviewDateStr)
{
    std::istringstream ss(reviewDateStr);
    ss >> std::get_time(&_reviewDate, dateformat);

    _added.tm_mon += 1;
    _added.tm_year += 1900;
}

PUBLIC void Libib::setStatus(std::string status) { _status = status; }

PUBLIC void Libib::setBegan(std::string beganStr)
{
    std::istringstream ss(beganStr);
    ss >> std::get_time(&_began, dateformat);

    _added.tm_mon += 1;
    _added.tm_year += 1900;
}

PUBLIC void Libib::setCompleted(std::string completedStr)
{
    std::istringstream ss(completedStr);
    ss >> std::get_time(&_completed, dateformat);

    _added.tm_mon += 1;
    _added.tm_year += 1900;
}

PUBLIC void Libib::setAdded(std::string addedStr)
{
    std::istringstream ss(addedStr);
    ss >> std::get_time(&_added, dateformat);

    _added.tm_mon += 1;
    _added.tm_year += 1900;
}

PUBLIC void Libib::setCopies(int copies) { _copies = copies; }

PUBLIC std::string Libib::ItemType() const { return _itemType; }
PUBLIC std::string Libib::Title() const { return _title; }
PUBLIC std::string Libib::Creators() const { return _creators; }
PUBLIC std::string Libib::FirstName() const { return _firstName; }
PUBLIC std::string Libib::LastName() const { return _lastName; }
PUBLIC unsigned long long Libib::EAN_ISBN13() const { return _EAN_ISBN13; }
PUBLIC unsigned long long Libib::UPC_ISBN10() const { return _UPC_ISBN10; }
PUBLIC std::string Libib::Description() const { return _description; }
PUBLIC std::string Libib::Publisher() const { return _publisher; }
PUBLIC tm Libib::PublishDate() const { return _publishDate; }
PUBLIC std::string Libib::Group() const { return _group; }
PUBLIC std::string Libib::Tags() const { return _tags; }
PUBLIC std::string Libib::Notes() const { return _notes; }
PUBLIC unsigned long long Libib::Price() const { return _price; }
PUBLIC int Libib::Length() const { return _length; }
PUBLIC int Libib::NumberOfDiscs() const { return _numberOfDiscs; }
PUBLIC int Libib::NumberOfPlayers() const { return _numberOfPlayers; }
PUBLIC int Libib::AgeGroup() const { return _ageGroup; }
PUBLIC std::string Libib::AspectRatio() const { return _aspectRatio; }
PUBLIC std::string Libib::Ensemble() const { return _ensemble; }
PUBLIC std::string Libib::ESRB() const { return _ESRB; }
PUBLIC double Libib::Rating() const { return _rating; }
PUBLIC std::string Libib::Review() const { return _review; }
PUBLIC tm Libib::ReviewDate() const { return _reviewDate; }
PUBLIC std::string Libib::Status() const { return _status; }
PUBLIC tm Libib::Began() const { return _began; }
PUBLIC tm Libib::Completed() const { return _completed; }
PUBLIC tm Libib::Added() const { return _added; }
PUBLIC int Libib::Copies() const { return _copies; }
