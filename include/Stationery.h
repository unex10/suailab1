#pragma once
#include "BookStore.h"
#include "Text.h"
class Stationery : public BookStore {
    Text kind_;
    Text color_;
    Text purpose_;
public:
    Stationery();
    Stationery(const Text& kind, const Text& color, const Text& purpose, long long price);
    Stationery(const Stationery& other);
    Stationery& operator=(const Stationery& other);
    ~Stationery() override;
    const Text& getKind() const;
    void setKind(const Text& value);
    const Text& getColor() const;
    void setColor(const Text& value);
    const Text& getPurpose() const;
    void setPurpose(const Text& value);
    int type() const override;
    BookStore* clone() const override;
    void input() override;
    void print(std::ostream& out) const override;
    void write(std::ostream& out) const override;
    void read(std::istream& in) override;
};
