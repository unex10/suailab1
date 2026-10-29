#pragma once
#include "BookStore.h"
#include "Text.h"
class Textbook : public BookStore {
    Text title_;
    Text author_;
    int year_;
    Text institution_;
    int studyYear_;
    int pages_;
public:
    Textbook();
    Textbook(const Text& title, const Text& author, int year, const Text& institution, int studyYear, int pages, long long price);
    Textbook(const Textbook& other);
    Textbook& operator=(const Textbook& other);
    ~Textbook() override;
    const Text& getTitle() const;
    void setTitle(const Text& value);
    const Text& getAuthor() const;
    void setAuthor(const Text& value);
    int getYear() const;
    void setYear(int value);
    const Text& getInstitution() const;
    void setInstitution(const Text& value);
    int getStudyYear() const;
    void setStudyYear(int value);
    int getPages() const;
    void setPages(int value);
    int type() const override;
    BookStore* clone() const override;
    void input() override;
    void print(std::ostream& out) const override;
};
