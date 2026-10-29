#include "Text.h"
#include <cstring>
#include <ostream>
#include <iostream>
Text::Text() : data_(new char[1]{'\0'}) {
    std::clog << "[Text " << this << "] конструктор без параметров\n";
}
Text::Text(const char* value) : data_(nullptr) {
    if (!value) value = "";
    data_ = new char[std::strlen(value) + 1];
    std::strcpy(data_, value);
    std::clog << "[Text " << this << "] конструктор с параметрами\n";
}
Text::Text(const Text& other) : data_(new char[other.size() + 1]) {
    std::strcpy(data_, other.data_);
    std::clog << "[Text " << this << "] конструктор копирования\n";
}
Text& Text::operator=(const Text& other) {
    if (this != &other) {
        char* copy = new char[other.size() + 1];
        std::strcpy(copy, other.data_);
        delete[] data_;
        data_ = copy;
    }
    return *this;
}
Text::~Text() {
    delete[] data_;
    std::clog << "[Text " << this << "] деструктор\n";
}
const char* Text::c_str() const { return data_; }
bool Text::empty() const { return data_[0] == '\0'; }
std::size_t Text::size() const { return std::strlen(data_); }
bool Text::operator==(const Text& other) const {
    return std::strcmp(data_, other.data_) == 0;
}
std::ostream& operator<<(std::ostream& out, const Text& text) {
    return out << text.c_str();
}
