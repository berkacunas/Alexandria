#ifndef LIBIB_H
#define LIBIB_H

#include <string>
#include <ctime>

class Libib {
    std::string _itemType;
    std::string _title;
    std::string _creators;
    std::string _firstName;
    std::string _lastName;
    unsigned long long _EAN_ISBN13;
    unsigned long long _UPC_ISBN10;
    std::string _description;;
    std::string _publisher;
    tm _publishDate;
    std::string _group;
    std::string _tags;
    std::string _notes;
    unsigned long long _price;
    int _length;
    int _numberOfDiscs;
    int _numberOfPlayers;
    int _ageGroup;
    std::string _aspectRatio;
    std::string _ensemble;
    std::string _ESRB;
    double _rating;
    std::string _review;
    tm _reviewDate;
    std::string _status;
    tm _began;
    tm _completed;
    tm _added;
    int _copies;

public:
    explicit Libib();

    void setItemType(std::string itemType);
    void setTitle(std::string title);
    void setCreators(std::string creators);
    void setFirstName(std::string firstName);
    void setLastName(std::string lastName);
    void setEAN_ISBN13(unsigned long long EAN_ISBN13);
    void setUPC_ISBN10(unsigned long long UPC_ISBN10);
    void setDescription(std::string description);
    void setPublisher(std::string publisher);
    void setPublishDate(tm publishDate);
    void setGroup(std::string group);
    void setTags(std::string tags);
    void setNotes(std::string notes);
    void setPrice(unsigned long long price);
    void setLength(int length);
    void setNumberOfDiscs(int numberOfDiscs);
    void setNumberOfPlayers(int numberOfPlayers);
    void setAgeGroup(int ageGroup);
    void setAspectRatio(std::string aspectRatio);
    void setEnsemble(std::string ensemble);
    void setESRB(std::string ESRB);
    void setRating(double rating);
    void setReview(std::string review);
    void setReviewDate(tm reviewDate);
    void setStatus(std::string status);
    void setBegan(tm began);
    void setCompleted(tm completed);
    void setAdded(tm added);
    void setCopies(int copies);

    std::string ItemType() const ;
    std::string Title() const ;
    std::string Creators() const ;
    std::string FirstName() const ;
    std::string LastName() const ;
    unsigned long long EAN_ISBN13() const;
    unsigned long long UPC_ISBN10() const;
    std::string Description() const;
    std::string Publisher() const;
    tm PublishDate() const;
    std::string Group() const;
    std::string Tags() const;
    std::string Notes() const;
    unsigned long long Price() const;
    int Length() const;
    int NumberOfDiscs() const;
    int NumberOfPlayers() const;
    int AgeGroup() const;
    std::string AspectRatio() const;
    std::string Ensemble() const;
    std::string ESRB() const;
    double Rating() const;
    std::string Review() const;
    tm ReviewDate() const;
    std::string Status() const;
    tm Began() const;
    tm Completed() const;
    tm Added() const;
    int Copies() const;

    void normalize_tm();
 };

#endif // LIBIB_H

