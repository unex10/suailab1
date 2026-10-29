#include "LabError.h"
#include <iostream>
LabError::LabError() : message_("Ошибка приложения.") {
    std::clog << "[LabError " << this << "] конструктор без параметров\n";
}
LabError::LabError(const char* message) : message_(message) {
    std::clog << "[LabError " << this << "] конструктор с параметрами\n";
}
LabError::LabError(const LabError& other)
    : std::exception(other), message_(other.message_) {
    std::clog << "[LabError " << this << "] конструктор копирования\n";
}
LabError& LabError::operator=(const LabError& other) {
    if (this != &other) {
        std::exception::operator=(other);
        message_ = other.message_;
    }
    return *this;
}
LabError::~LabError() {
    std::clog << "[LabError " << this << "] деструктор\n";
}
const char* LabError::what() const noexcept { return message_.c_str(); }
