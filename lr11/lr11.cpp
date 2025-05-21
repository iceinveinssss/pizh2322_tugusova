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

    // 2. Создание контейнера vector с объектами пользовательского типа
    vector<Session*> sessions;
    sessions.push_back(new Session("2024-06-01", "18:00", "Интерстеллар"));
    sessions.push_back(new Booking("2024-06-02", "19:30", "Дюна", "Иванов И.И.", 5));
    sessions.push_back(new PaidTicket("2024-06-03", "21:00", "Матрица", 350.0, true));
    sessions.push_back(new Session("2024-06-04", "15:00", "Начало"));
    sessions.push_back(new Booking("2024-06-05", "20:00", "Звёздные войны", "Петров П.П.", 8));

    // 3. Сортировка по убыванию (по названию фильма)
    sort(sessions.begin(), sessions.end(), [](Session* a, Session* b) {
        return *a > *b;
        });

    // 4. Просмотр отсортированного контейнера
    cout << "Контейнер после сортировки по убыванию:" << endl;
    for (const auto& session : sessions) {
        session->output();
        cout << "-----" << endl;
    }

    // 5. Поиск элементов по условию (фильмы после 2024-06-02)
    auto it = find_if(sessions.begin(), sessions.end(), [](Session* s) {
        return s->getDate() > "2024-06-02";
        });

    // 6. Перемещение в другой контейнер (list)
    list<Session*> filteredSessions;
    while (it != sessions.end()) {
        if ((*it)->getDate() > "2024-06-02") {
            filteredSessions.push_back(*it);
            it = sessions.erase(it);
        }
        else {
            ++it;
        }
    }

    // 7. Просмотр второго контейнера
    cout << "\nФильтрованный контейнер (фильмы после 2024-06-02):" << endl;
    for (const auto& session : filteredSessions) {
        session->output();
        cout << "-----" << endl;
    }

    // 8. Сортировка обоих контейнеров по возрастанию
    sort(sessions.begin(), sessions.end(), [](Session* a, Session* b) {
        return *a < *b;
        });

    filteredSessions.sort([](Session* a, Session* b) {
        return *a < *b;
        });

    // 9. Просмотр отсортированных контейнеров
    cout << "\nПервый контейнер после сортировки по возрастанию:" << endl;
    for (const auto& session : sessions) {
        session->output();
        cout << "-----" << endl;
    }

    cout << "\nВторой контейнер после сортировки по возрастанию:" << endl;
    for (const auto& session : filteredSessions) {
        session->output();
        cout << "-----" << endl;
    }

    // Освобождение памяти
    for (auto session : sessions) {
        delete session;
    }
    for (auto session : filteredSessions) {
        delete session;
    }

    return 0;
}