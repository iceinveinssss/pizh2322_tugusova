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
    // Конструктор без параметров
    Session() {
        date = "No date";
        time = "No time";
        movieTitle = "No title";
        cout << "Session: Default constructor" << endl;
    }

    // Конструктор с параметрами
    Session(string d, string t, string mt) {
        date = d;
        time = t;
        movieTitle = mt;
        cout << "Session: Constructor with parameters" << endl;
    }

    // Конструктор копирования
    Session(const Session& s) {
        date = s.date;
        time = s.time;
        movieTitle = s.movieTitle;
        cout << "Session: Copy constructor" << endl;
    }

    // Деструктор
    ~Session() {
        cout << "Session: Destructor" << endl;
    }

    // Методы для установки значений (setters)
    void setDate(string d) { date = d; }
    void setTime(string t) { time = t; }
    void setMovieTitle(string mt) { movieTitle = mt; }

    // Методы для получения значений (getters)
    string getDate() { return date; }
    string getTime() { return time; }
    string getMovieTitle() { return movieTitle; }

    // Перегруженные методы
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
    // Конструктор без параметров
    Cinema() {
        name = "No name";
        address = "No address";
        cout << "Cinema: Default constructor" << endl;
    }

    // Конструктор с параметрами
    Cinema(string n, string a) {
        name = n;
        address = a;
        cout << "Cinema: Constructor with parameters" << endl;
    }

    // Конструктор копирования
    Cinema(const Cinema& c) {
        name = c.name;
        address = c.address;
        sessionCount = c.sessionCount;
        for (int i = 0; i < sessionCount; i++) {
            sessions[i] = c.sessions[i];
        }
        cout << "Cinema: Copy constructor" << endl;
    }

    // Деструктор
    ~Cinema() {
        cout << "Cinema: Destructor" << endl;
    }

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

    // Новый метод (пункт 5 задания) - создает объект Session с параметрами и добавляет в массив
    void addNewSession(string date, string time, string title) {
        if (sessionCount < 10) {
            Session newSession(date, time, title); // создание объекта конструктором с параметрами
            sessions[sessionCount] = newSession;
            sessionCount++;
        }
        else {
            cout << "Достигнуто максимальное количество сеансов!" << endl;
        }
    }

    // Новый метод (пункт 6 задания) - создает копии объекта и добавляет в массив
    void addCopiesOfSession(const Session& session, int count) {
        for (int i = 0; i < count && sessionCount < 10; i++) {
            Session newSession(session); // создание копии конструктором копирования
            sessions[sessionCount] = newSession;
            sessionCount++;
        }
        if (sessionCount >= 10) {
            cout << "Достигнуто максимальное количество сеансов!" << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    cout << "============= Step 1: Cinema constructors" << endl;
    Cinema cinema1; // конструктор без параметров
    Cinema cinema2("Киномакс", "ул. Ленина, 10"); // конструктор с параметрами
    Cinema cinema3(cinema2); // конструктор копирования

    cout << "============= Step 2: Session constructors" << endl;
    Session session1; // конструктор без параметров
    Session session2("2023-12-15", "18:00", "Аватар"); // конструктор с параметрами

    cout << "============= Step 3: Using new methods" << endl;
    // Использование нового метода (пункт 5)
    cinema1.addNewSession("2023-12-20", "20:00", "Интерстеллар");

    // Использование нового метода (пункт 6)
    cinema2.addCopiesOfSession(session2, 3);

    cout << "============= Step 4: Display information" << endl;
    // Вывод информации о кинотеатре и сеансах
    cout << "Кинотеатр 1: " << cinema1.getName() << endl;
    cout << "Сеансы в кинотеатре 1:" << endl;
    for (int i = 0; i < cinema1.getSessionCount(); i++) {
        Session s = cinema1.getSession(i);
        cout << "  " << s.getMovieTitle() << " в " << s.getTime() << ", " << s.getDate() << endl;
    }

    cout << "\nКинотеатр 2: " << cinema2.getName() << endl;
    cout << "Сеансы в кинотеатре 2:" << endl;
    for (int i = 0; i < cinema2.getSessionCount(); i++) {
        Session s = cinema2.getSession(i);
        cout << "  " << s.getMovieTitle() << " в " << s.getTime() << ", " << s.getDate() << endl;
    }

    cout << "============= End of program" << endl;
    return 0;
}