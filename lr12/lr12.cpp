#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;

class Session {
protected:
    string date;
    string time;
    string movieTitle;

public:
    Session(string d = "", string t = "", string mt = "") : date(d), time(t), movieTitle(mt) {}

    bool operator<(const Session& other) const {
        return movieTitle < other.movieTitle;
    }

    bool operator>(const Session& other) const {
        return movieTitle > other.movieTitle;
    }

    virtual void output() const {
        cout << "Фильм: " << movieTitle << " | Дата: " << date << " | Время: " << time << endl;
    }

    string getMovieTitle() const { return movieTitle; }
    string getDate() const { return date; }
    string getTime() const { return time; }
};

class Booking : public Session {
private:
    string customerName;
    int seatNumber;

public:
    Booking(string d = "", string t = "", string mt = "", string name = "", int seat = 0)
        : Session(d, t, mt), customerName(name), seatNumber(seat) {
    }

    void output() const override {
        Session::output();
        cout << "Бронировано для: " << customerName << ", Место: " << seatNumber << endl;
    }
};

class PaidTicket : public Session {
private:
    double price;
    bool isPaid;

public:
    PaidTicket(string d = "", string t = "", string mt = "", double p = 0.0, bool paid = false)
        : Session(d, t, mt), price(p), isPaid(paid) {
    }

    void output() const override {
        Session::output();
        cout << "Цена: " << price << ", Оплачено: " << (isPaid ? "Да" : "Нет") << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    // 1. Создание контейнера vector с объектами пользовательского типа
    vector<Session*> sessions = {
        new Session("2024-06-01", "18:00", "Интерстеллар"),
        new Booking("2024-06-02", "19:30", "Дюна", "Иванов И.И.", 5),
        new PaidTicket("2024-06-03", "21:00", "Матрица", 350.0, true),
        new Session("2024-06-04", "15:00", "Начало"),
        new Booking("2024-06-05", "20:00", "Звёздные войны", "Петров П.П.", 8)
    };

    // 2. Замена глобальных функций на лямбда-выражения

    // Сортировка по убыванию времени сеанса
    sort(sessions.begin(), sessions.end(), [](Session* a, Session* b) {
        return a->getTime() > b->getTime();
        });

    cout << "Сеансы, отсортированные по убыванию времени:\n";
    for_each(sessions.begin(), sessions.end(), [](Session* s) {
        s->output();
        cout << "-----\n";
        });

    // Поиск всех сеансов на "Дюну"
    list<Session*> duneSessions;
    copy_if(sessions.begin(), sessions.end(), back_inserter(duneSessions), [](Session* s) {
        return s->getMovieTitle() == "Дюна";
        });

    cout << "\nВсе сеансы на 'Дюну':\n";
    for_each(duneSessions.begin(), duneSessions.end(), [](Session* s) {
        s->output();
        cout << "-----\n";
        });

    // Удаление всех сеансов до 2024-06-03
    sessions.erase(remove_if(sessions.begin(), sessions.end(), [](Session* s) {
        return s->getDate() < "2024-06-03";
        }), sessions.end());

    cout << "\nСеансы после 2024-06-03:\n";
    for_each(sessions.begin(), sessions.end(), [](Session* s) {
        s->output();
        cout << "-----\n";
        });

    // Освобождение памяти
    for_each(sessions.begin(), sessions.end(), [](Session* s) { delete s; });
    for_each(duneSessions.begin(), duneSessions.end(), [](Session* s) { delete s; });

    return 0;
}