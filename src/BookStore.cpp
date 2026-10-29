#include "BookStore.h"
#include "LabError.h"
#include <iostream>
BookStore::BookStore() : price_(0) {
    std::cout << "[BookStore " << this << "] конструктор без параметров\n";
}
BookStore::BookStore(long long price) : price_(0) {
    setPrice(price);
    std::cout << "[BookStore " << this << "] конструктор с параметрами\n";
}
BookStore::BookStore(const BookStore& other) : price_(other.price_) {
    std::cout << "[BookStore " << this << "] конструктор копирования\n";
}
BookStore& BookStore::operator=(const BookStore& other) {
    price_ = other.price_;
    return *this;
}
BookStore::~BookStore() {
    std::cout << "[BookStore " << this << "] виртуальный деструктор\n";
}
long long BookStore::getPrice() const { return price_; }
void BookStore::setPrice(long long price) {
    if (price < 0 || price > 1000000000LL)
        throw LabError("Стоимость вне диапазона 0..1000000000 копеек.");
    price_ = price;
}
std::ostream& operator<<(std::ostream& out, const BookStore& item) {
    item.print(out);
    return out;
}
