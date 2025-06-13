#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

class Book {
    string author;
    string title;
    int year;

public:
    Book(string a = "", string t = "", int y = 0) :
        author(a), title(t), year(y) {
    }

    string getAuthor() const { return author; }
    string getTitle() const { return title; }
    int getYear() const { return year; }

    friend bool operator < (const Book& b1, const Book& b2) {
        if (b1.author != b2.author)
            return b1.author < b2.author;
        if (b1.year != b2.year)
            return b1.year < b2.year;
        return b1.title < b2.title;
    }

    friend ostream& operator << (ostream& os, const Book& b) {
        os << "Автор: " << b.author << "\tНазва: " << b.title
            << "\tРік: " << b.year;
        return os;
    }
};

void removeBooksOlderThan(multimap<string, Book>& library, int year) {
    auto it = library.begin();
    while (it != library.end()) {
        if (it->second.getYear() < year) {
            it = library.erase(it);
        }
        else {
            ++it;
        }
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    multimap<string, Book> library;

    int choice;
    string author, title;
    int year;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Додати книгу\n";
        cout << "2. Видалити книгу\n";
        cout << "3. Пошук книг за автором\n";
        cout << "4. Пошук книг за роком видання\n";
        cout << "5. Вивести всі книги\n";
        cout << "6. Видалити книги старші за вказаний рік\n";
        cout << "7. Вихід\n";
        cout << "Виберіть опцію: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            cout << "Введіть автора: ";
            getline(cin, author);
            cout << "Введіть назву книги: ";
            getline(cin, title);
            cout << "Введіть рік видання: ";
            cin >> year;

            Book newBook(author, title, year);
            library.insert(make_pair(author, newBook));
            cout << "Книгу додано!\n";
            break;
        }

        case 2: {
            cout << "Введіть автора книги для видалення: ";
            getline(cin, author);
            cout << "Введіть назву книги: ";
            getline(cin, title);
            cout << "Введіть рік видання: ";
            cin >> year;

            bool found = false;
            auto range = library.equal_range(author);
            for (auto it = range.first; it != range.second; ++it) {
                if (it->second.getTitle() == title && it->second.getYear() == year) {
                    library.erase(it);
                    found = true;
                    cout << "Книгу видалено!\n";
                    break;
                }
            }

            if (!found) {
                cout << "Книгу не знайдено!\n";
            }
            break;
        }

        case 3: {
            cout << "Введіть автора для пошуку: ";
            getline(cin, author);

            auto range = library.equal_range(author);
            if (range.first == range.second) {
                cout << "Книг цього автора не знайдено.\n";
            }
            else {
                cout << "Знайдені книги:\n";
                for (auto it = range.first; it != range.second; ++it) {
                    cout << it->second << endl;
                }
            }
            break;
        }

        case 4: {
            cout << "Введіть рік видання для пошуку: ";
            cin >> year;

            bool found = false;
            cout << "Знайдені книги:\n";
            for (const auto& entry : library) {
                if (entry.second.getYear() == year) {
                    cout << entry.second << endl;
                    found = true;
                }
            }

            if (!found) {
                cout << "Книг цього року видання не знайдено.\n";
            }
            break;
        }

        case 5: {
            if (library.empty()) {
                cout << "Бібліотека порожня.\n";
            }
            else {
                cout << "Всі книги в бібліотеці:\n";
                for (const auto& entry : library) {
                    cout << entry.second << endl;
                }
            }
            break;
        }

        case 6: {
            cout << "Введіть рік: книги старші за цей рік будуть видалені: ";
            cin >> year;
            removeBooksOlderThan(library, year);
            cout << "Книги старші за " << year << " рік видалено!\n";
            break;
        }

        case 7:
            return 0;

        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
        }
    }

    return 0;
}