#pragma once
#include <cstddef>
#include <iosfwd>
// Собственная строка на динамической памяти. STL-контейнеры не используются.
class Text {
    char* data_;
public:
    Text();
    Text(const char* value);
    Text(const Text& other);
    Text& operator=(const Text& other);
    ~Text();
    const char* c_str() const;
    bool empty() const;
    std::size_t size() const;
    bool operator==(const Text& other) const;
};
std::ostream& operator<<(std::ostream& out, const Text& text);
