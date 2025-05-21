#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
using namespace std;

// 1. Дополняем классы из ЛР7
class Session {
protected:
    string date;
    string time;
    string movieTitle;

public:
    Session(string d = "", string t = "", string mt = "") : date(d), time(t), movieTitle(mt) {}
    virtual ~Session() {}

    bool operator<(const Session& other) const { return movieTitle < other.movieTitle; }
    bool operator>(const Session& other) const { return movieTitle > other.movieTitle; }

    void riskyMethod() {
        // 2. Генерируем исключение int
        throw 42;
    }
};

// 5. Собственные классы исключений
class MyException1 : public std::exception {
public:
    const char* what() const noexcept override {
        return "My custom exception 1 occurred";
    }
};

class MyException2 : public std::runtime_error {
public:
    MyException2() : std::runtime_error("My custom exception 2 occurred") {}
};

void functionThatThrowsString() {
    // 2. Генерируем исключение string
    throw string("Something went wrong!");
}

void functionWithNestedExceptions() {
    try {
        // 6. Исключение во вложенном вызове
        Session s;
        s.riskyMethod();
    }
    catch (int e) {
        cout << "Caught int exception in nested call: " << e << endl;
        // 7. Локальная обработка без передачи выше
        return;
    }
}

int main() {
    // 2. Перехват int и string
    try {
        Session s;
        s.riskyMethod();
    }
    catch (int e) {
        cout << "Caught int exception: " << e << endl;
    }

    try {
        functionThatThrowsString();
    }
    catch (const string& e) {
        cout << "Caught string exception: " << e << endl;
    }

    // 3. Перехват любых исключений
    try {
        throw 3.14;
    }
    catch (...) {
        cout << "Caught unknown exception" << endl;
    }

    // 4. Стандартные исключения
    try {
        throw std::invalid_argument("Invalid argument");
    }
    catch (const std::invalid_argument& e) {
        cout << "Caught invalid_argument: " << e.what() << endl;
    }

    try {
        throw std::out_of_range("Out of range");
    }
    catch (const std::out_of_range& e) {
        cout << "Caught out_of_range: " << e.what() << endl;
    }

    // 5. Собственные исключения
    try {
        throw MyException1();
    }
    catch (const MyException1& e) {
        cout << "Caught MyException1: " << e.what() << endl;
    }

    try {
        throw MyException2();
    }
    catch (const MyException2& e) {
        cout << "Caught MyException2: " << e.what() << endl;
    }

    // 6. Обработка на верхнем уровне
    try {
        functionWithNestedExceptions();
    }
    catch (...) {
        cout << "This won't be called due to local handling" << endl;
    }

    // 7. Локальная обработка
    try {
        throw runtime_error("Local error");
    }
    catch (const runtime_error& e) {
        cout << "Locally handled: " << e.what() << endl;
    }

    cout << "Program completed successfully" << endl;
    return 0;
}