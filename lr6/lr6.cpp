#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Предварительное объявление класса Cinema для дружественной функции
class Cinema;

// Абстрактный базовый класс — Сеанс
class Session {
private:
    static int objectCount;  // Закрытый статический счетчик объектов

protected:
    string date;   // Дата сеанса
    string time;   // Время сеанса
    string movieTitle;   // Название фильма

public:
    // Конструктор по умолчанию
    Session() : date("No date"), time("No time"), movieTitle("No title") {
        objectCount++;
        cout << "Session: Default constructor" << endl;
    }

    // Конструктор с параметрами
    Session(string d, string t, string mt) : date(d), time(t), movieTitle(mt) {
        objectCount++;
        cout << "Session: Constructor with parameters" << endl;
    }

    // Конструктор копирования
    Session(const Session& s) : date(s.date), time(s.time), movieTitle(s.movieTitle) {
        objectCount++;
        cout << "Session: Copy constructor" << endl;
    }

    // Виртуальный деструктор
    virtual ~Session() {
        objectCount--;
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

    // Статический метод для получения количества объектов
    static int getObjectCount() {
        return objectCount;
    }
};

// Инициализация статического счетчика
int Session::objectCount = 0;

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

// Глобальный оператор вывода для Session
ostream& operator<<(ostream& os, const Session& session) {
    session.output();
    return os;
}

// Основной класс — Кинотеатр
class Cinema {
private:
    string name;  // Название кинотеатра
    string address;  // Адрес кинотеатра
    vector<Session*> sessions;  // Вектор для хранения указателей на сеансы
    static int arrayObjectCount;  // Закрытый статический счетчик объектов в массиве

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
        arrayObjectCount++;
    }

    // Вывод всей информации о кинотеатре и сеансах
    void outputAll() const {
        cout << "\nКинотеатр: " << name << "\nАдрес: " << address << "\nСеансы:\n";
        for (size_t i = 0; i < sessions.size(); ++i) {
            cout << "\nСеанс " << i + 1 << ":\n";
            sessions[i]->fullOutput();  // Вызов метода полного вывода
        }
    }

    // Статический метод для получения количества объектов в массиве
    static int getArrayObjectCount() {
        return arrayObjectCount;
    }

    // Оператор + для добавления объекта (пункт 2 задания)
    Cinema& operator+(Session* newSession) {
        this->addSession(newSession);
        return *this;
    }

    // Префиксный оператор ++ (пункт 3 задания)
    Cinema& operator++() {
        this->addSession(new Booking());  // Добавляем объект по умолчанию
        return *this;
    }

    // Постфиксный оператор ++ (пункт 3 задания)
    Cinema operator++(int) {
        Cinema temp = *this;
        this->addSession(new PaidTicket());  // Добавляем объект по умолчанию
        return temp;
    }

    // Оператор [] для доступа к элементам массива (пункт 4 задания)
    Session* operator[](size_t index) {
        if (index >= sessions.size()) {
            throw out_of_range("Индекс выходит за границы массива");
        }
        return sessions[index];
    }

    // Дружественная функция для оператора вывода
    friend ostream& operator<<(ostream& os, const Cinema& cinema);
};

// Глобальный оператор вывода для Cinema (пункт 5 задания)
ostream& operator<<(ostream& os, const Cinema& cinema) {
    os << "Кинотеатр: " << cinema.name << "\nАдрес: " << cinema.address
        << "\nКоличество сеансов: " << cinema.sessions.size() << "\n";
    return os;
}

// Инициализация статического счетчика объектов в массиве
int Cinema::arrayObjectCount = 0;

// Основной main
int main() {
    setlocale(LC_ALL, "Russian");  // Установка локализации

    cout << "========= Демонстрация работы операторов =========\n";

    Cinema cinema;
    cinema.setName("Звезда");
    cinema.setAddress("ул. Космонавтов, 15");

    // Демонстрация оператора + (пункт 6 задания)
    cinema + new Booking("2025-05-01", "15:00", "Аватар", "Смирнов А.А.", 12);
    cinema + new PaidTicket("2025-05-01", "18:00", "Аватар", 350.0, true);

    // Демонстрация префиксного ++ (пункт 6 задания)
    ++cinema;

    // Демонстрация постфиксного ++ (пункт 6 задания)
    cinema++;

    // Демонстрация оператора вывода (пункт 6 задания)
    cout << cinema;

    // Демонстрация оператора [] (пункт 6 задания)
    try {
        cout << "\nИнформация о первом сеансе:\n";
        cout << *cinema[0];  // Используем глобальный оператор << для Session
    }
    catch (const out_of_range& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }

    // Вывод всей информации о кинотеатре
    cout << "\nПолная информация о кинотеатре:\n";
    cinema.outputAll();

    cout << "\n========= Конец программы =========\n";
    return 0;
}