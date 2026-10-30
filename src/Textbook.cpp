#include "Textbook.h"
#include "Input.h"
#include "LabError.h"
#include <iostream>
Textbook::Textbook() : BookStore(), title_("Не задано"), author_("Не задано"), year_(2000), institution_("Не задано"), studyYear_(1), pages_(1) {
    std::cout << "[Textbook " << this << "] конструктор без параметров\n";
}
Textbook::Textbook(const Text& title, const Text& author, int year, const Text& institution, int studyYear, int pages, long long price) : BookStore(price), title_("Не задано"), author_("Не задано"), year_(2000), institution_("Не задано"), studyYear_(1), pages_(1) {
    setTitle(title);
    setAuthor(author);
    setYear(year);
    setInstitution(institution);
    setStudyYear(studyYear);
    setPages(pages);
    std::cout << "[Textbook " << this << "] конструктор с параметрами\n";
}
Textbook::Textbook(const Textbook& other) : BookStore(other), title_(other.title_), author_(other.author_), year_(other.year_), institution_(other.institution_), studyYear_(other.studyYear_), pages_(other.pages_) {
    std::cout << "[Textbook " << this << "] конструктор копирования\n";
}
Textbook& Textbook::operator=(const Textbook& other) {
    if (this != &other) {
        BookStore::operator=(other);
        title_ = other.title_;
        author_ = other.author_;
        year_ = other.year_;
        institution_ = other.institution_;
        studyYear_ = other.studyYear_;
        pages_ = other.pages_;
    }
    return *this;
}
Textbook::~Textbook() {
    std::cout << "[Textbook " << this << "] деструктор\n";
}
const Text& Textbook::getTitle() const { return title_; }
void Textbook::setTitle(const Text& value) {
    Input::requireText(value);
    title_ = value;
}
const Text& Textbook::getAuthor() const { return author_; }
void Textbook::setAuthor(const Text& value) {
    Input::requireText(value);
    author_ = value;
}
int Textbook::getYear() const { return year_; }
void Textbook::setYear(int value) {
    if (value < 1 || value > 9999)
        throw LabError("Год выпуска: допустимо от 1 до 9999.");
    year_ = value;
}
const Text& Textbook::getInstitution() const { return institution_; }
void Textbook::setInstitution(const Text& value) {
    Input::requireText(value);
    institution_ = value;
}
int Textbook::getStudyYear() const { return studyYear_; }
void Textbook::setStudyYear(int value) {
    if (value < 1 || value > 30)
        throw LabError("Год обучения: допустимо от 1 до 30.");
    studyYear_ = value;
}
int Textbook::getPages() const { return pages_; }
void Textbook::setPages(int value) {
    if (value < 1 || value > 1000000)
        throw LabError("Количество страниц: допустимо от 1 до 1000000.");
    pages_ = value;
}
int Textbook::type() const { return 2; }
BookStore* Textbook::clone() const { return new Textbook(*this); }
void Textbook::input() {
    setTitle(Input::text("Название: "));
    setAuthor(Input::text("Автор: "));
    setYear(Input::integer("Год выпуска", 1, 9999));
    setInstitution(Input::text("Учебное заведение: "));
    setStudyYear(Input::integer("Год обучения", 1, 30));
    setPages(Input::integer("Количество страниц", 1, 1000000));
    setPrice(Input::money("Стоимость в рублях: "));
}
void Textbook::print(std::ostream& out) const {
    out << "Учебник\n";
    out << "  Название: " << title_ << '\n';
    out << "  Автор: " << author_ << '\n';
    out << "  Год выпуска: " << year_ << '\n';
    out << "  Учебное заведение: " << institution_ << '\n';
    out << "  Год обучения: " << studyYear_ << '\n';
    out << "  Количество страниц: " << pages_ << '\n';
    out << "  Стоимость: ";
    Input::printMoney(out, getPrice());
    out << " руб.\n";
}
void Textbook::write(std::ostream& out) const {
    Input::writeText(out, title_);
    Input::writeText(out, author_);
    out << year_ << '\n';
    Input::writeText(out, institution_);
    out << studyYear_ << '\n';
    out << pages_ << '\n';
    writePrice(out);
}
void Textbook::read(std::istream& in) {
    setTitle(Input::readText(in));
    setAuthor(Input::readText(in));
    setYear(static_cast<int>(Input::readInteger(in, 1, 9999)));
    setInstitution(Input::readText(in));
    setStudyYear(static_cast<int>(Input::readInteger(in, 1, 30)));
    setPages(static_cast<int>(Input::readInteger(in, 1, 1000000)));
    readPrice(in);
}
