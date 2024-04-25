// Библиотека.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <locale> // Для setlocale
#include <algorithm> // Для std::find_if
#include <Windows.h>
using namespace std;

class Book {

public:
    string title;
    string author;
    Book(string title, string author)
        : title(title), author(author) {}
};

class Human {
public:
    string name;
    vector<Book> reservedBooks;

    Human(string name) : name(name) {}

    void reserveBook(const Book& book) {
        reservedBooks.push_back(book);
    }

    void removeReservation(const string& title) {
        auto it = find_if(reservedBooks.begin(), reservedBooks.end(), [&title](const Book& book) {
            return book.title == title;
            });
        if (it != reservedBooks.end()) {
            reservedBooks.erase(it);
        }
    }

    void listReservedBooks() {
        for (const auto& book : reservedBooks) {
            cout << book.title << " " << book.author << endl;
        }
    }
};
class Library {
private:
    vector<Book> books;
public:
    void addBook(const Book& book) {
        books.push_back(book);
    }
    void listBooks() {
        for (const auto& book : books) {
            cout << book.title << " " << book.author << endl;
        }
    }
    Book findBookByTitle(const string& title) {
        auto it = find_if(books.begin(), books.end(), [&title](const Book& book) {
            return book.title == title;
            });
        if (it != books.end()) {
            return *it;
        }
        // Возвращаем пустую книгу, если книга не найдена
        return Book("", "");
    }
    Book selectBookByIndex(int index) {
        if (index >= 0 && index < books.size()) {
            return books[index];
        }
        // Возвращаем пустую книгу, если индекс недействителен
        return Book("", "");
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); // Установка кодовой страницы вывода
    setlocale(LC_ALL, "Russian_Russia.1251");
    Library library; // Создаем один объект Library
    cout << "Введите имя\n";
    string name;
    cin >> name;
    Human user(name);

    while (true) {
        cout << "Добро пожаловать в библиотечный каталог!\n Выберите действие:\n 1. Отменить резервацию\n 2. Добавить резервацию\n 3. Выбрать книгу \n 4. Список книг\n 5. Добавить книгу в список\n 6. Выход\n";
        int opt;
        cin >> opt;

        if (opt == 6) {
            break; // Выход из цикла
        }

        if (opt == 1) {
            cout << "Введите название книги для удаления резервации: " << endl;
            string titleToRemove;
            cin >> titleToRemove;
            auto it = find_if(user.reservedBooks.begin(), user.reservedBooks.end(), [&titleToRemove](const Book& book) {
                return book.title == titleToRemove;
                });
            if (it != user.reservedBooks.end()) {
                user.reservedBooks.erase(it);
                cout << "Резервация успешно удалена.\n";
            }
            else {
                cout << "Резервация не найдена.\n";
            }
        }
        else if (opt == 2)
        {
            cout << "Введите название книги для резервации: " << endl;
            string title;
            cin >> title;
            Book bookToReserve = library.findBookByTitle(title);
            if (bookToReserve.title.empty()) {
                cout << "Книга не найдена.\n";
            }
            else {
                user.reserveBook(bookToReserve);
                cout << "Книга успешно зарезервирована.\n";
            }

        }
        
        else if (opt == 3) {
            cout << "Выберите номер книги из списка: " << endl;
            library.listBooks();
            int index;
            cin >> index;
            Book selectedBook = library.selectBookByIndex(index);
            if (selectedBook.title.empty()) {
                cout << "Книга не найдена.\n";
            }
            else {
                cout << "Выбрана книга: " << selectedBook.title << " " << selectedBook.author << endl;
            }
        }
        else if (opt == 4) {
            cout << "Книги:\n" << endl;
            library.listBooks();
        }
        else if (opt == 5) {
            cout << "Введите название и автора книги для добавления в библиотеку: " << endl;
            string title, author;
            cin >> title >> author;
            library.addBook(Book(title, author));
        }
        else {
            cout << "Неверный выбор.\n";
        }
    }
}