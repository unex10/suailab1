#include "Stationery.h"
#include "Input.h"
#include "LabError.h"
#include <iostream>
Stationery::Stationery() : BookStore(), kind_("Не задано"), color_("Не задано"), purpose_("Не задано") {
    std::cout << "[Stationery " << this << "] конструктор без параметров\n";
}
Stationery::Stationery(const Text& kind, const Text& color, const Text& purpose, long long price) : BookStore(price), kind_("Не задано"), color_("Не задано"), purpose_("Не задано") {
    setKind(kind);
    setColor(color);
    setPurpose(purpose);
    std::cout << "[Stationery " << this << "] конструктор с параметрами\n";
}
Stationery::Stationery(const Stationery& other) : BookStore(other), kind_(other.kind_), color_(other.color_), purpose_(other.purpose_) {
    std::cout << "[Stationery " << this << "] конструктор копирования\n";
}
Stationery& Stationery::operator=(const Stationery& other) {
    if (this != &other) {
        BookStore::operator=(other);
        kind_ = other.kind_;
        color_ = other.color_;
        purpose_ = other.purpose_;
    }
    return *this;
}
Stationery::~Stationery() {
    std::cout << "[Stationery " << this << "] деструктор\n";
}
const Text& Stationery::getKind() const { return kind_; }
void Stationery::setKind(const Text& value) {
    Input::requireText(value);
    kind_ = value;
}
const Text& Stationery::getColor() const { return color_; }
void Stationery::setColor(const Text& value) {
    Input::requireText(value);
    color_ = value;
}
const Text& Stationery::getPurpose() const { return purpose_; }
void Stationery::setPurpose(const Text& value) {
    Input::requireText(value);
    purpose_ = value;
}
int Stationery::type() const { return 3; }
BookStore* Stationery::clone() const { return new Stationery(*this); }
void Stationery::input() {
    setKind(Input::text("Тип канцелярии: "));
    setColor(Input::text("Цвет: "));
    setPurpose(Input::text("Назначение: "));
    setPrice(Input::money("Стоимость в рублях: "));
}
void Stationery::print(std::ostream& out) const {
    out << "Канцелярия\n";
    out << "  Тип канцелярии: " << kind_ << '\n';
    out << "  Цвет: " << color_ << '\n';
    out << "  Назначение: " << purpose_ << '\n';
    out << "  Стоимость: ";
    Input::printMoney(out, getPrice());
    out << " руб.\n";
}
