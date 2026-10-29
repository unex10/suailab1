#pragma once
#include "BookStore.h"
#include <iosfwd>
class Keeper {
    BookStore** items_;
    int size_;
    int capacity_;
    void reserve(int capacity);
public:
    static constexpr int MAX_ITEMS = 10000;
    Keeper();
    explicit Keeper(int capacity);
    Keeper(const Keeper& other);
    Keeper& operator=(const Keeper& other);
    ~Keeper();
    void swap(Keeper& other) noexcept;
    int getSize() const;
    const BookStore& operator[](int index) const;
    void add(const BookStore& item); // глубокая копия
    Keeper& operator+=(const BookStore& item);
    void remove(int index);
    void replace(int index, const BookStore& item);
    void clear();
    void print(std::ostream& out, int type = 0) const;
};
std::ostream& operator<<(std::ostream& out, const Keeper& keeper);
