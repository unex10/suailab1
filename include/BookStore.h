#pragma once
#include <iosfwd>
// Абстрактная сущность товара книжного магазина.
class BookStore {
    long long price_; // копейки, чтобы избежать ошибок double
protected:
    void writePrice(std::ostream& out) const;
    void readPrice(std::istream& in);
public:
    BookStore();
    explicit BookStore(long long price);
    BookStore(const BookStore& other);
    BookStore& operator=(const BookStore& other);
    virtual ~BookStore();
    long long getPrice() const;
    void setPrice(long long price);
    virtual int type() const = 0;
    virtual BookStore* clone() const = 0;
    virtual void input() = 0;
    virtual void print(std::ostream& out) const = 0;
    virtual void write(std::ostream& out) const = 0;
    virtual void read(std::istream& in) = 0;
};
std::ostream& operator<<(std::ostream& out, const BookStore& item);
