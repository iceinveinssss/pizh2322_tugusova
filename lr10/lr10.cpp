#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// Базовый класс — Сеанс
class Session {
protected:
    string date;
    string time;
    string movieTitle;

public:
    Session(string d = "", string t = "", string mt = "") : date(d), time(t), movieTitle(mt) {}
    virtual ~Session() {}

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
    Booking(string d = "", string t = "", string mt = "", string name = "", int seat = 0)
        : Session(d, t, mt), customerName(name), seatNumber(seat) {
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

    // 2. Создание и заполнение контейнера (vector) базовыми типами
    vector<int> numbers = { 10, 20, 30, 40, 50 };

    // 3. Просмотр контейнера
    cout << "Исходный контейнер (int):" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // 4. Изменение контейнера
    numbers.erase(remove(numbers.begin(), numbers.end(), 30), numbers.end());
    numbers[1] = 25;

    // 5. Просмотр с использованием итераторов
    cout << "\nИзмененный контейнер (int):" << endl;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 6. Работа с пользовательским типом
    vector<Session*> sessions;
    sessions.push_back(new Session("2024-06-01", "18:00", "Интерстеллар"));
    sessions.push_back(new Booking("2024-06-02", "19:30", "Дюна", "Иванов И.И.", 5));
    sessions.push_back(new PaidTicket("2024-06-03", "21:00", "Матрица", 350.0, true));

    // Просмотр исходного контейнера
    cout << "\nИсходный контейнер (Session*):" << endl;
    for (const auto& session : sessions) {
        session->output();
        cout << "-----" << endl;
    }

    // Изменение контейнера
    delete sessions[1];
    sessions.erase(sessions.begin() + 1);
    sessions.push_back(new Booking("2024-06-04", "15:00", "Начало", "Петров П.П.", 8));

    // Просмотр с использованием итераторов
    cout << "\nИзмененный контейнер (Session*):" << endl;
    for (auto it = sessions.begin(); it != sessions.end(); ++it) {
        (*it)->output();
        cout << "-----" << endl;
    }

    // Освобождение памяти
    for (auto session : sessions) {
        delete session;
    }

    return 0;
}