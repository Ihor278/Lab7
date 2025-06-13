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
        os << "�����: " << b.author << "\t�����: " << b.title
            << "\tг�: " << b.year;
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
        cout << "\n����:\n";
        cout << "1. ������ �����\n";
        cout << "2. �������� �����\n";
        cout << "3. ����� ���� �� �������\n";
        cout << "4. ����� ���� �� ����� �������\n";
        cout << "5. ������� �� �����\n";
        cout << "6. �������� ����� ������ �� �������� ��\n";
        cout << "7. �����\n";
        cout << "������� �����: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            cout << "������ ������: ";
            getline(cin, author);
            cout << "������ ����� �����: ";
            getline(cin, title);
            cout << "������ �� �������: ";
            cin >> year;

            Book newBook(author, title, year);
            library.insert(make_pair(author, newBook));
            cout << "����� ������!\n";
            break;
        }

        case 2: {
            cout << "������ ������ ����� ��� ���������: ";
            getline(cin, author);
            cout << "������ ����� �����: ";
            getline(cin, title);
            cout << "������ �� �������: ";
            cin >> year;

            bool found = false;
            auto range = library.equal_range(author);
            for (auto it = range.first; it != range.second; ++it) {
                if (it->second.getTitle() == title && it->second.getYear() == year) {
                    library.erase(it);
                    found = true;
                    cout << "����� ��������!\n";
                    break;
                }
            }

            if (!found) {
                cout << "����� �� ��������!\n";
            }
            break;
        }

        case 3: {
            cout << "������ ������ ��� ������: ";
            getline(cin, author);

            auto range = library.equal_range(author);
            if (range.first == range.second) {
                cout << "���� ����� ������ �� ��������.\n";
            }
            else {
                cout << "������� �����:\n";
                for (auto it = range.first; it != range.second; ++it) {
                    cout << it->second << endl;
                }
            }
            break;
        }

        case 4: {
            cout << "������ �� ������� ��� ������: ";
            cin >> year;

            bool found = false;
            cout << "������� �����:\n";
            for (const auto& entry : library) {
                if (entry.second.getYear() == year) {
                    cout << entry.second << endl;
                    found = true;
                }
            }

            if (!found) {
                cout << "���� ����� ���� ������� �� ��������.\n";
            }
            break;
        }

        case 5: {
            if (library.empty()) {
                cout << "��������� �������.\n";
            }
            else {
                cout << "�� ����� � ��������:\n";
                for (const auto& entry : library) {
                    cout << entry.second << endl;
                }
            }
            break;
        }

        case 6: {
            cout << "������ ��: ����� ������ �� ��� �� ������ �������: ";
            cin >> year;
            removeBooksOlderThan(library, year);
            cout << "����� ������ �� " << year << " �� ��������!\n";
            break;
        }

        case 7:
            return 0;

        default:
            cout << "������� ����. ��������� �� ���.\n";
        }
    }

    return 0;
}