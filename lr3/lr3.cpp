#include <iostream>
#include <string>
using namespace std;

// Базовый класс — Сеанс
class Session {
protected:
    string date;
    string time;
    string movieTitle;

public:
    Session() {
        date = "No date";
        time = "No time";
        movieTitle = "No title";
        cout << "Session: Default constructor" << endl;
    }

    Session(string d, string t, string mt) : date(d), time(t), movieTitle(mt) {
        cout << "Session: Constructor with parameters" << endl;
    }

    Session(const Session& s) {
        date = s.date;
        time = s.time;
        movieTitle = s.movieTitle;
        cout << "Session: Copy constructor" << endl;
    }

    virtual ~Session() {
        cout << "Session: Destructor" << endl;
    }

    virtual void input() {
        cout << "Введите дату: ";
        getline(cin, date);
        cout << "Введите время: ";
        getline(cin, time);
        cout << "Введите название фильма: ";
        getline(cin, movieTitle);
    }

    virtual void output() const {
        cout << "Фильм: " << movieTitle << " | Дата: " << date << " | Время: " << time << endl;
    }
};

// Класс-наследник — Бронирование
class Booking : public Session {
private:
    string customerName;
    int seatNumber;

public:
    Booking() : Session(), customerName("Unknown"), seatNumber(0) {
        cout << "Booking: Default constructor" << endl;
    }

    Booking(string d, string t, string mt, string name, int seat)
            : Session(d, t, mt), customerName(name), seatNumber(seat) {
        cout << "Booking: Constructor with parameters" << endl;
    }

    ~Booking() override {
        cout << "Booking: Destructor" << endl;
    }

    void input() override {
        Session::input();
        cout << "Введите имя клиента: ";
        getline(cin, customerName);
        cout << "Введите номер места: ";
        cin >> seatNumber;
        cin.ignore();
    }

    void output() const override {
        Session::output();
        cout << "Бронировано для: " << customerName << ", Место: " << seatNumber << endl;
    }
};

// Класс-наследник — Оплаченные билеты
class PaidTicket : public Session {
private:
    double price;
    bool isPaid;

public:
    PaidTicket() : Session(), price(0.0), isPaid(false) {
        cout << "PaidTicket: Default constructor" << endl;
    }

    PaidTicket(string d, string t, string mt, double p, bool paid)
            : Session(d, t, mt), price(p), isPaid(paid) {
        cout << "PaidTicket: Constructor with parameters" << endl;
    }

    ~PaidTicket() override {
        cout << "PaidTicket: Destructor" << endl;
    }

    void input() override {
        Session::input();
        cout << "Введите цену билета: ";
        cin >> price;
        cout << "Оплачено? (1 - да, 0 - нет): ";
        cin >> isPaid;
        cin.ignore();
    }

    void output() const override {
        Session::output();
        cout << "Цена: " << price << ", Оплачено: " << (isPaid ? "Да" : "Нет") << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "========= Часть 1: Отдельные объекты =========" << endl;
    Session baseSession("2024-05-01", "18:00", "Флэшбек");
    Booking booking("2024-05-01", "18:00", "Флэшбек", "Иванов И.И.", 7);
    PaidTicket ticket("2024-05-01", "18:00", "Флэшбек", 350.0, true);

    cout << "\nВывод информации:" << endl;
    baseSession.output();
    booking.output();
    ticket.output();

    cout << "\n========= Часть 2: Массив указателей на базовый класс =========" << endl;
    Session* sessionArray[5];
    sessionArray[0] = new Session("2024-05-02", "15:00", "Матрица");
    sessionArray[1] = new Booking("2024-05-02", "15:00", "Матрица", "Петров П.П.", 12);
    sessionArray[2] = new PaidTicket("2024-05-02", "15:00", "Матрица", 450.0, true);
    sessionArray[3] = new Booking("2024-05-02", "17:00", "Начало", "Сидоров С.С.", 5);
    sessionArray[4] = new PaidTicket("2024-05-02", "17:00", "Начало", 300.0, false);

    for (int i = 0; i < 5; i++) {
        cout << "Объект " << i + 1 << ": ";
        sessionArray[i]->output();
    }

    // Освобождение памяти
    for (int i = 0; i < 5; i++) {
        delete sessionArray[i];
    }

    cout << "\n========= Часть 3: Массив объектов класса Booking =========" << endl;
    Booking bookings[2] = {
            Booking("2024-05-03", "20:00", "Дюна", "Александров А.А.", 3),
            Booking("2024-05-03", "22:00", "Бегущий по лезвию", "Смирнова А.А.", 9)
    };

    for (int i = 0; i < 2; i++) {
        cout << "Бронирование " << i + 1 << ": ";
        bookings[i].output();
    }

    cout << "\n========= Конец программы =========" << endl;
    return 0;
}
