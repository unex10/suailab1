#pragma once
#include "BookStore.h"
#include "Text.h"
class Book : public BookStore {
    Text title_;
    Text author_;
    int year_;
    Text annotation_;
    Text genre_;
    int pages_;
public:
    Book();
    Book(const Text& title, const Text& author, int year, const Text& annotation, const Text& genre, int pages, long long price);
    Book(const Book& other);
    Book& operator=(const Book& other);
    ~Book() override;
    const Text& getTitle() const;
    void setTitle(const Text& value);
    const Text& getAuthor() const;
    void setAuthor(const Text& value);
    int getYear() const;
    void setYear(int value);
    const Text& getAnnotation() const;
    void setAnnotation(const Text& value);
    const Text& getGenre() const;
    void setGenre(const Text& value);
    int getPages() const;
    void setPages(int value);
    int type() const override;
    BookStore* clone() const override;
    void input() override;
    void print(std::ostream& out) const override;
    void write(std::ostream& out) const override;
    void read(std::istream& in) override;
};
