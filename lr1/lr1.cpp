#include <iostream>
#include <string>
using namespace std;

// Класс Сеанс (дополнительный класс)
class Session {
private:
    string date;    // дата сеанса
    string time;    // время сеанса
    string movieTitle;  // название фильма

public:
    // Методы для установки значений (setters)
    void setDate(string d) { date = d; }
    void setTime(string t) { time = t; }
    void setMovieTitle(string mt) { movieTitle = mt; }

    // Методы для получения значений (getters)
    string getDate() { return date; }
    string getTime() { return time; }
    string getMovieTitle() { return movieTitle; }

    // Перегруженные методы (два метода с одним именем, но разными параметрами)
    void setProperties() {
        cout << "Введите дату: ";
        getline(cin, date);
        cout << "Введите время: ";
        getline(cin, time);
        cout << "Введите название фильма: ";
        getline(cin, movieTitle);
    }

    void setProperties(string d, string t, string mt) {
        date = d;
        time = t;
        movieTitle = mt;
    }
};

// Класс Кинотеатр (основной класс)
class Cinema {
private:
    string name;    // название кинотеатра
    string address; // адрес кинотеатра
    Session sessions[10]; // массив сеансов (максимум 10)
    int sessionCount = 0; // счетчик сеансов

public:
    // Методы для установки значений
    void setName(string n) { name = n; }
    void setAddress(string a) { address = a; }

    // Методы для получения значений
    string getName() { return name; }
    string getAddress() { return address; }

    // Метод для добавления сеанса
    void addSession(Session s) {
        if (sessionCount < 10) {
            sessions[sessionCount] = s;
            sessionCount++;
        }
        else {
            cout << "Достигнуто максимальное количество сеансов!" << endl;
        }
    }

    // Метод для получения сеанса по индексу
    Session getSession(int index) {
        if (index >= 0 && index < sessionCount) {
            return sessions[index];
        }
        else {
            cout << "Неверный индекс сеанса!" << endl;
            return Session(); // возвращаем пустой сеанс
        }
    }

    int getSessionCount() { return sessionCount; }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Cinema cinema;
    string input;

    // Ввод информации о кинотеатре
    cout << "Введите название кинотеатра: ";
    getline(cin, input);
    cinema.setName(input);

    cout << "Введите адрес кинотеатра: ";
    getline(cin, input);
    cinema.setAddress(input);

    // Добавление сеансов
    char choice;
    do {
        Session session;
        cout << "Добавить сеанс (1 - вручную, 2 - автоматически): ";
        cin >> choice;
        cin.ignore(); // очищаем буфер

        if (choice == '1') {
            session.setProperties(); // используем первый метод
        }
        else {
            session.setProperties("2023-12-01", "18:00", "Новый фильм"); // второй метод
        }

        cinema.addSession(session);

        cout << "Добавить еще один сеанс? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' && cinema.getSessionCount() < 10);

    // Вывод информации
    cout << "\nКинотеатр: " << cinema.getName() << endl;
    cout << "Адрес: " << cinema.getAddress() << endl;
    cout << "Сеансы:\n";

    for (int i = 0; i < cinema.getSessionCount(); i++) {
        Session s = cinema.getSession(i);
        cout << "Сеанс " << i + 1 << ": " << s.getMovieTitle()
            << " в " << s.getTime() << ", " << s.getDate() << endl;
    }

    return 0;
}