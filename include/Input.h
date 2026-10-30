#pragma once
#include "Text.h"
#include <iosfwd>
namespace Input {
    constexpr int MAX_TEXT = 4096;
    Text line(std::istream& in);
    Text text(const char* prompt);
    int integer(const char* prompt, int low, int high);
    long long money(const char* prompt);
    long long parseInteger(const Text& value, long long low, long long high);
    long long parseMoney(const Text& value);
    void requireText(const Text& value);
    void writeText(std::ostream& out, const Text& value);
    Text readText(std::istream& in);
    long long readInteger(std::istream& in, long long low, long long high);
    void printMoney(std::ostream& out, long long cents);
}
