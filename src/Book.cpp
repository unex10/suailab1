#include "Book.h"
#include "Input.h"
#include "LabError.h"
#include <iostream>
Book::Book() : BookStore(), title_("Не задано"), author_("Не задано"), year_(2000), annotation_("Не задано"), genre_("Не задано"), pages_(1) {
    std::cout << "[Book " << this << "] конструктор без параметров\n";
}
Book::Book(const Text& title, const Text& author, int year, const Text& annotation, const Text& genre, int pages, long long price) : BookStore(price), title_("Не задано"), author_("Не задано"), year_(2000), annotation_("Не задано"), genre_("Не задано"), pages_(1) {
    setTitle(title);
    setAuthor(author);
    setYear(year);
    setAnnotation(annotation);
    setGenre(genre);
    setPages(pages);
    std::cout << "[Book " << this << "] конструктор с параметрами\n";
}
Book::Book(const Book& other) : BookStore(other), title_(other.title_), author_(other.author_), year_(other.year_), annotation_(other.annotation_), genre_(other.genre_), pages_(other.pages_) {
    std::cout << "[Book " << this << "] конструктор копирования\n";
}
Book& Book::operator=(const Book& other) {
    if (this != &other) {
        BookStore::operator=(other);
        title_ = other.title_;
        author_ = other.author_;
        year_ = other.year_;
        annotation_ = other.annotation_;
        genre_ = other.genre_;
        pages_ = other.pages_;
    }
    return *this;
}
Book::~Book() {
    std::cout << "[Book " << this << "] деструктор\n";
}
const Text& Book::getTitle() const { return title_; }
void Book::setTitle(const Text& value) {
    Input::requireText(value);
    title_ = value;
}
const Text& Book::getAuthor() const { return author_; }
void Book::setAuthor(const Text& value) {
    Input::requireText(value);
    author_ = value;
}
int Book::getYear() const { return year_; }
void Book::setYear(int value) {
    if (value < 1 || value > 9999)
        throw LabError("Год выпуска: допустимо от 1 до 9999.");
    year_ = value;
}
const Text& Book::getAnnotation() const { return annotation_; }
void Book::setAnnotation(const Text& value) {
    Input::requireText(value);
    annotation_ = value;
}
const Text& Book::getGenre() const { return genre_; }
void Book::setGenre(const Text& value) {
    Input::requireText(value);
    genre_ = value;
}
int Book::getPages() const { return pages_; }
void Book::setPages(int value) {
    if (value < 1 || value > 1000000)
        throw LabError("Количество страниц: допустимо от 1 до 1000000.");
    pages_ = value;
}
int Book::type() const { return 1; }
BookStore* Book::clone() const { return new Book(*this); }
void Book::input() {
    setTitle(Input::text("Название: "));
    setAuthor(Input::text("Автор: "));
    setYear(Input::integer("Год выпуска", 1, 9999));
    setAnnotation(Input::text("Аннотация: "));
    setGenre(Input::text("Жанр: "));
    setPages(Input::integer("Количество страниц", 1, 1000000));
    setPrice(Input::money("Стоимость в рублях: "));
}
void Book::print(std::ostream& out) const {
    out << "Книга\n";
    out << "  Название: " << title_ << '\n';
    out << "  Автор: " << author_ << '\n';
    out << "  Год выпуска: " << year_ << '\n';
    out << "  Аннотация: " << annotation_ << '\n';
    out << "  Жанр: " << genre_ << '\n';
    out << "  Количество страниц: " << pages_ << '\n';
    out << "  Стоимость: ";
    Input::printMoney(out, getPrice());
    out << " руб.\n";
}
