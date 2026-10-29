#pragma once
#include "Text.h"
#include <exception>
class LabError : public std::exception {
    Text message_;
public:
    LabError();
    LabError(const LabError& other);
    LabError& operator=(const LabError& other);
    ~LabError() override;
    explicit LabError(const char* message);
    const char* what() const noexcept override;
};
