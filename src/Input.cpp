#include "Input.h"
#include "LabError.h"
#include <iostream>
#include <iomanip>
#include <cstring>
namespace Input {
Text line(std::istream& in) {
    // Ограниченный буфер исключает бесконтрольное выделение памяти.
    char buffer[MAX_TEXT + 1];
    int length = 0;
    bool tooLong = false;
    char ch;
    while (in.get(ch)) {
        if (ch == '\n') break;
        if (ch == '\0') throw LabError("Нулевой байт в строке.");
        if (length < MAX_TEXT) buffer[length++] = ch;
        else tooLong = true;
    }
    if (in.bad()) throw LabError("Ошибка чтения потока.");
    if (in.eof() && length == 0 && !tooLong)
        throw LabError("Ввод завершён или файл неожиданно закончился.");
    if (tooLong) throw LabError("Строка длиннее 4096 байт.");
    if (length && buffer[length - 1] == '\r') --length;
    buffer[length] = '\0';
    return Text(buffer);
}
void requireText(const Text& value) {
    if (value.empty() || value.size() > MAX_TEXT)
        throw LabError("Текст должен содержать от 1 до 4096 байт.");
    bool visible = false;
    for (const char* s = value.c_str(); *s; ++s) {
        if (*s == '\n' || *s == '\r')
            throw LabError("Перенос строки внутри поля запрещён.");
        if (*s != ' ' && *s != '\t') visible = true;
    }
    if (!visible) throw LabError("Поле не может состоять из пробелов.");
}
long long parseInteger(const Text& value, long long low, long long high) {
    const char* s = value.c_str();
    while (*s == ' ' || *s == '\t') ++s;
    if (*s < '0' || *s > '9')
        throw LabError("Введите целое неотрицательное число.");
    long long result = 0;
    while (*s >= '0' && *s <= '9') {
        int digit = *s++ - '0';
        if (result > high / 10 ||
            (result == high / 10 && digit > high % 10))
            throw LabError("Число превышает допустимый предел.");
        result = result * 10 + digit;
    }
    while (*s == ' ' || *s == '\t') ++s;
    if (*s || result < low || result > high)
        throw LabError("Недопустимое число или выход за диапазон.");
    return result;
}
long long parseMoney(const Text& value) {
    const char* s = value.c_str();
    while (*s == ' ' || *s == '\t') ++s;
    if (*s < '0' || *s > '9')
        throw LabError("Стоимость должна быть неотрицательным числом.");
    long long rubles = 0;
    while (*s >= '0' && *s <= '9') {
        int digit = *s++ - '0';
        if (rubles > 1000000 || (rubles == 1000000 && digit > 0))
            throw LabError("Максимальная стоимость 10000000 рублей.");
        rubles = rubles * 10 + digit;
    }
    int cents = 0;
    if (*s == '.' || *s == ',') {
        ++s;
        if (*s < '0' || *s > '9') throw LabError("Нет цифр после разделителя.");
        cents = (*s++ - '0') * 10;
        if (*s >= '0' && *s <= '9') cents += *s++ - '0';
    }
    while (*s == ' ' || *s == '\t') ++s;
    if (*s || rubles * 100 + cents > 1000000000LL)
        throw LabError("Стоимость: до 10000000 руб., не более 2 знаков после запятой.");
    return rubles * 100 + cents;
}
Text text(const char* prompt) {
    for (;;) {
        std::cout << prompt;
        try { Text value = line(std::cin); requireText(value); return value; }
        catch (const LabError& e) {
            if (std::cin.eof() || std::cin.bad()) throw;
            std::cout << "Ошибка: " << e.what() << '\n';
        }
    }
}
int integer(const char* prompt, int low, int high) {
    for (;;) {
        std::cout << prompt << " [" << low << ".." << high << "]: ";
        try { return static_cast<int>(parseInteger(line(std::cin), low, high)); }
        catch (const LabError& e) {
            if (std::cin.eof() || std::cin.bad()) throw;
            std::cout << "Ошибка: " << e.what() << '\n';
        }
    }
}
long long money(const char* prompt) {
    for (;;) {
        std::cout << prompt;
        try { return parseMoney(line(std::cin)); }
        catch (const LabError& e) {
            if (std::cin.eof() || std::cin.bad()) throw;
            std::cout << "Ошибка: " << e.what() << '\n';
        }
    }
}
void writeText(std::ostream& out, const Text& value) { out << value << '\n'; }
Text readText(std::istream& in) { Text value = line(in); requireText(value); return value; }
long long readInteger(std::istream& in, long long low, long long high) {
    return parseInteger(line(in), low, high);
}
void printMoney(std::ostream& out, long long cents) {
    char old = out.fill('0');
    out << cents / 100 << '.' << std::setw(2) << cents % 100;
    out.fill(old);
}
}
