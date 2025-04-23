#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Абстрактный базовый класс — Сеанс
class Session {
protected:
    string date;   // Дата сеанса
    string time;   // Время сеанса
    string movieTitle;   // Название фильма

public:
    // Конструктор по умолчанию
    Session() : date("No date"), time("No time"), movieTitle("No title") {
        cout << "Session: Default constructor" << endl;
    }

    // Конструктор с параметрами
    Session(string d, string t, string mt) : date(d), time(t), movieTitle(mt) {
        cout << "Session: Constructor with parameters" << endl;
    }

    // Конструктор копирования
    Session(const Session& s) : date(s.date), time(s.time), movieTitle(s.movieTitle) {
        cout << "Session: Copy constructor" << endl;
    }

    // Виртуальный деструктор
    virtual ~Session() {
        cout << "Session: Destructor" << endl;
    }

    // Метод для ввода данных
    virtual void input() {
        cout << "Введите дату: ";
        getline(cin, date);
        cout << "Введите время: ";
        getline(cin, time);
        cout << "Введите название фильма: ";
        getline(cin, movieTitle);
    }

    // Метод для вывода данных
    virtual void output() const {
        cout << "Фильм: " << movieTitle << " | Дата: " << date << " | Время: " << time << endl;
    }

    // Чисто виртуальная функция для полного вывода
    virtual void fullOutput() const = 0;
};

// Класс-наследник — Бронирование
class Booking : public Session {
private:
    string customerName;  // Имя клиента
    int seatNumber;  // Номер места

public:
    // Конструктор по умолчанию
    Booking() : Session(), customerName("Unknown"), seatNumber(0) {
        cout << "Booking: Default constructor" << endl;
    }

    // Конструктор с параметрами
    Booking(string d, string t, string mt, string name, int seat)
            : Session(d, t, mt), customerName(name), seatNumber(seat) {
        cout << "Booking: Constructor with parameters" << endl;
    }

    // Деструктор
    ~Booking() override {
        cout << "Booking: Destructor" << endl;
    }

    // Переопределенный метод ввода данных
    void input() override {
        Session::input();  // Ввод данных для базового класса
        cout << "Введите имя клиента: ";
        getline(cin, customerName);
        cout << "Введите номер места: ";
        cin >> seatNumber;
        cin.ignore();  // Очищаем буфер
    }

    // Переопределенный метод вывода данных
    void output() const override {
        Session::output();  // Вывод данных для базового класса
        cout << "Бронировано для: " << customerName << ", Место: " << seatNumber << endl;
    }

    // Переопределенный метод полного вывода
    void fullOutput() const override {
        output();  // Выводим все данные
    }
};

// Класс-наследник — Оплаченные билеты
class PaidTicket : public Session {
private:
    double price;  // Цена билета
    bool isPaid;  // Статус оплаты

public:
    // Конструктор по умолчанию
    PaidTicket() : Session(), price(0.0), isPaid(false) {
        cout << "PaidTicket: Default constructor" << endl;
    }

    // Конструктор с параметрами
    PaidTicket(string d, string t, string mt, double p, bool paid)
            : Session(d, t, mt), price(p), isPaid(paid) {
        cout << "PaidTicket: Constructor with parameters" << endl;
    }

    // Деструктор
    ~PaidTicket() override {
        cout << "PaidTicket: Destructor" << endl;
    }

    // Переопределенный метод ввода данных
    void input() override {
        Session::input();  // Ввод данных для базового класса
        cout << "Введите цену билета: ";
        cin >> price;
        cout << "Оплачено? (1 - да, 0 - нет): ";
        cin >> isPaid;
        cin.ignore();  // Очищаем буфер
    }

    // Переопределенный метод вывода данных
    void output() const override {
        Session::output();  // Вывод данных для базового класса
        cout << "Цена: " << price << ", Оплачено: " << (isPaid ? "Да" : "Нет") << endl;
    }

    // Переопределенный метод полного вывода
    void fullOutput() const override {
        output();  // Выводим все данные
    }
};

// Основной класс — Кинотеатр
class Cinema {
private:
    string name;  // Название кинотеатра
    string address;  // Адрес кинотеатра
    vector<Session*> sessions;  // Вектор для хранения указателей на сеансы

public:
    Cinema() = default;  // Конструктор по умолчанию

    // Деструктор
    ~Cinema() {
        for (auto s : sessions) {
            delete s;  // Освобождение памяти
        }
        sessions.clear();  // Очистка вектора
    }

    // Установка и получение названия кинотеатра
    void setName(const string& n) { name = n; }
    string getName() const { return name; }

    // Установка и получение адреса кинотеатра
    void setAddress(const string& a) { address = a; }
    string getAddress() const { return address; }

    // Добавление сеанса в вектор
    void addSession(Session* s) {
        sessions.push_back(s);
    }

    // Вывод всей информации о кинотеатре и сеансах
    void outputAll() const {
        cout << "\nКинотеатр: " << name << "\nАдрес: " << address << "\nСеансы:\n";
        for (size_t i = 0; i < sessions.size(); ++i) {
            cout << "\nСеанс " << i + 1 << ":\n";
            sessions[i]->fullOutput();  // Вызов метода полного вывода
        }
    }
};

// Основной main
int main() {
    setlocale(LC_ALL, "Russian");  // Установка локализации

    cout << "========= Часть 1: Массив объектов (указатели на Session) =========\n";
    Session* sessionArray[3];  // Массив указателей на базовый класс
    sessionArray[0] = new Booking("2025-04-24", "17:00", "Интерстеллар", "Иванов И.И.", 4);
    sessionArray[1] = new PaidTicket("2025-04-24", "19:00", "Интерстеллар", 450.0, true);
    sessionArray[2] = new Booking("2025-04-25", "21:00", "Тенет", "Петров П.П.", 9);

    // Вывод всех сеансов в массиве
    for (int i = 0; i < 3; i++) {
        sessionArray[i]->fullOutput();
        cout << "--------------------------------\n";
    }

    cout << "\n========= Часть 2: Работа с Cinema =========\n";
    Cinema myCinema;  // Создание объекта Cinema
    myCinema.setName("Космос");
    myCinema.setAddress("ул. Гагарина, 1");

    // Добавление сеансов в кинотеатр
    myCinema.addSession(new Booking("2025-04-26", "18:00", "Дюна", "Сидоров С.С.", 6));
    myCinema.addSession(new PaidTicket("2025-04-26", "20:00", "Дюна", 400.0, false));

    // Вывод информации о кинотеатре
    myCinema.outputAll();

    // Освобождение памяти, если осталось что-то из sessionArray
    for (int i = 0; i < 3; i++) {
        delete sessionArray[i];  // Освобождение памяти
    }

    cout << "\n========= Конец программы =========\n";
    return 0;
}
