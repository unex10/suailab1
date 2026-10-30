#include "Keeper.h"
#include "Book.h"
#include "Textbook.h"
#include "Stationery.h"
#include "Input.h"
#include "LabError.h"
#include <iostream>
#include <new>
namespace {
BookStore* createItem(int type) {
    if (type == 1) return new Book;
    if (type == 2) return new Textbook;
    return new Stationery;
}
int chooseIndex(const Keeper& keeper) {
    if (!keeper.getSize()) throw LabError("Магазин пуст. Сначала добавьте товар.");
    return Input::integer("Номер товара", 1, keeper.getSize()) - 1;
}

}
int main() {
    try {
        Keeper keeper;
        bool running = true;
        while (running) {
            std::cout << "\nКНИЖНЫЙ МАГАЗИН\n"
                "1. Добавить товар\n2. Показать все товары\n"
                "3. Изменить товар\n4. Удалить товар\n"
                "5. Сохранить в файл\n6. Загрузить из файла\n"
                "7. Показать товары выбранного вида\n"
                "8. Очистить магазин\n0. Выход\n";
            try {
                int command = Input::integer("Команда", 0, 8);
                switch (command) {
                case 0: running = false; break;
                case 1: {
                    int type = Input::integer("Вид: 1-книга, 2-учебник, 3-канцелярия", 1, 3);
                    BookStore* item = createItem(type);
                    try { item->input(); keeper += *item; }
                    catch (...) { delete item; throw; }
                    delete item;
                    std::cout << "Товар добавлен.\n";
                    break;
                }
                case 2: std::cout << keeper; break;
                case 3: {
                    int index = chooseIndex(keeper);
                    BookStore* edited = keeper[index].clone();
                    try { edited->input(); keeper.replace(index, *edited); }
                    catch (...) { delete edited; throw; }
                    delete edited;
                    std::cout << "Товар изменён.\n";
                    break;
                }
                case 4: keeper.remove(chooseIndex(keeper));
                    std::cout << "Товар удалён.\n"; break;
                case 5: {
                    Text path = Input::text("Имя файла (существующий будет перезаписан): ");
                    keeper.save(path);
                    std::cout << "Сохранено товаров: " << keeper.getSize() << '\n';
                    break;
                }
                case 6: {
                    Text path = Input::text("Имя файла: ");
                    int yes = Input::integer("Загрузка заменит список. 1-продолжить, 0-отмена", 0, 1);
                    if (yes) {
                        keeper.load(path);
                        std::cout << "Загружено товаров: " << keeper.getSize() << '\n';
                    }
                    break;
                }
                case 7: keeper.print(std::cout, Input::integer(
                    "Вид: 1-книга, 2-учебник, 3-канцелярия", 1, 3)); break;
                case 8:
                    if (Input::integer("Удалить все товары? 1-да, 0-нет", 0, 1)) {
                        keeper.clear(); std::cout << "Магазин очищен.\n";
                    }
                    break;
                }
            } catch (const LabError& e) {
                std::cout << "Ошибка: " << e.what() << '\n';
                if (std::cin.eof() || std::cin.bad()) running = false;
            } catch (const std::bad_alloc&) {
                std::cout << "Ошибка: недостаточно оперативной памяти.\n";
            }
        }
        std::cout << "Работа завершена. Не забудьте сохранить данные перед выходом.\n";
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
