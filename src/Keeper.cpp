#include "Keeper.h"
#include "Book.h"
#include "Textbook.h"
#include "Stationery.h"
#include "Input.h"
#include "LabError.h"
#include <iostream>
#include <fstream>
#include <utility>
Keeper::Keeper() : items_(nullptr), size_(0), capacity_(0) {
    std::cout << "[Keeper " << this << "] конструктор без параметров\n";
}
Keeper::Keeper(int capacity) : items_(nullptr), size_(0), capacity_(0) {
    reserve(capacity);
    std::cout << "[Keeper " << this << "] конструктор с параметрами\n";
}
Keeper::Keeper(const Keeper& other) : items_(nullptr), size_(0), capacity_(0) {
    try {
        reserve(other.size_);
        for (int i = 0; i < other.size_; ++i) add(*other.items_[i]);
    } catch (...) {
        clear();
        delete[] items_;
        throw;
    }
    std::cout << "[Keeper " << this << "] конструктор копирования\n";
}
Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        Keeper copy(other);
        swap(copy);
    }
    return *this;
}
Keeper::~Keeper() {
    clear();
    delete[] items_;
    std::cout << "[Keeper " << this << "] деструктор\n";
}
void Keeper::swap(Keeper& other) noexcept {
    std::swap(items_, other.items_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
}
void Keeper::reserve(int capacity) {
    if (capacity < 0 || capacity > MAX_ITEMS)
        throw LabError("Вместимость контейнера вне диапазона 0..10000.");
    if (capacity <= capacity_) return;
    BookStore** data = new BookStore*[capacity];
    for (int i = 0; i < size_; ++i) data[i] = items_[i];
    delete[] items_;
    items_ = data;
    capacity_ = capacity;
}
int Keeper::getSize() const { return size_; }
const BookStore& Keeper::operator[](int index) const {
    if (index < 0 || index >= size_) throw LabError("Товар с таким номером отсутствует.");
    return *items_[index];
}
void Keeper::add(const BookStore& item) {
    if (size_ == MAX_ITEMS) throw LabError("Достигнут предел 10000 товаров.");
    if (size_ == capacity_) {
        int next = capacity_ ? capacity_ * 2 : 4;
        reserve(next > MAX_ITEMS ? MAX_ITEMS : next);
    }
    items_[size_] = item.clone();
    ++size_;
}
Keeper& Keeper::operator+=(const BookStore& item) { add(item); return *this; }
void Keeper::remove(int index) {
    (void)(*this)[index];
    delete items_[index];
    for (int i = index; i + 1 < size_; ++i) items_[i] = items_[i + 1];
    --size_;
}
void Keeper::replace(int index, const BookStore& item) {
    (void)(*this)[index];
    BookStore* copy = item.clone(); // сначала копия, затем удаление
    delete items_[index];
    items_[index] = copy;
}
void Keeper::clear() {
    for (int i = 0; i < size_; ++i) delete items_[i];
    size_ = 0;
}
void Keeper::print(std::ostream& out, int type) const {
    int found = 0;
    for (int i = 0; i < size_; ++i) {
        if (type == 0 || items_[i]->type() == type) {
            out << "\nТовар №" << i + 1 << '\n' << *items_[i];
            ++found;
        }
    }
    if (!found) out << "Товары отсутствуют.\n";
    out << "Показано: " << found << ". Всего: " << size_ << '\n';
}
void Keeper::save(const Text& filename) const {
    Input::requireText(filename);
    std::ofstream out(filename.c_str(), std::ios::binary | std::ios::trunc);
    if (!out) throw LabError("Не удалось открыть файл для записи.");
    out << "BOOKSTORE_V1\n" << size_ << '\n';
    for (int i = 0; i < size_; ++i) {
        out << items_[i]->type() << '\n';
        items_[i]->write(out);
    }
    out.flush();
    if (!out) throw LabError("Не удалось записать файл полностью.");
    out.close();
    if (!out) throw LabError("Ошибка закрытия файла после записи.");
}
void Keeper::load(const Text& filename) {
    std::ifstream in(filename.c_str(), std::ios::binary);
    if (!in) throw LabError("Не удалось открыть файл для чтения.");
    if (!(Input::line(in) == Text("BOOKSTORE_V1")))
        throw LabError("Неверный формат или версия файла.");
    int count = static_cast<int>(Input::readInteger(in, 0, MAX_ITEMS));
    Keeper loaded(count);
    for (int i = 0; i < count; ++i) {
        int tag = static_cast<int>(Input::readInteger(in, 1, 3));
        BookStore* item = nullptr;
        if (tag == 1) item = new Book;
        else if (tag == 2) item = new Textbook;
        else item = new Stationery;
        try {
            item->read(in);
            loaded.add(*item);
        } catch (...) { delete item; throw; }
        delete item;
    }
    char ch;
    while (in.get(ch)) {
        if (ch != '\n' && ch != '\r' && ch != ' ' && ch != '\t')
            throw LabError("Лишние данные после последнего товара.");
    }
    if (in.bad()) throw LabError("Ошибка чтения файла.");
    swap(loaded); // текущее состояние заменяется только после полной проверки
}
std::ostream& operator<<(std::ostream& out, const Keeper& keeper) {
    keeper.print(out);
    return out;
}
