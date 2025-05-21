#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
using namespace std;

class Session {
protected:
    string date;
    string time;
    string movieTitle;

public:
    Session(string d = "", string t = "", string mt = "") : date(d), time(t), movieTitle(mt) {}
    virtual ~Session() {}

    friend ostream& operator<<(ostream& os, const Session& session);
    friend istream& operator>>(istream& is, Session& session);
};

// 2. Глобальный оператор вывода
ostream& operator<<(ostream& os, const Session& session) {
    os << "Date: " << session.date << "\nTime: " << session.time
        << "\nMovie: " << session.movieTitle << endl;
    return os;
}

// 3. Глобальный оператор ввода
istream& operator>>(istream& is, Session& session) {
    cout << "Enter date: ";
    getline(is, session.date);
    cout << "Enter time: ";
    getline(is, session.time);
    cout << "Enter movie title: ";
    getline(is, session.movieTitle);
    return is;
}

class Cinema {
private:
    vector<Session> sessions;

public:
    void addSession(const Session& session) {
        sessions.push_back(session);
    }

    // 4. Сохранение в файл
    void saveToFile(const string& filename) {
        ofstream outFile(filename);
        if (!outFile) {
            throw runtime_error("Cannot open file for writing");
        }

        for (const auto& session : sessions) {
            outFile << session.date << '\n'
                << session.time << '\n'
                << session.movieTitle << '\n';
        }
    }

    // 5. Чтение из файла
    void loadFromFile(const string& filename) {
        ifstream inFile(filename);
        if (!inFile) {
            throw runtime_error("Cannot open file for reading");
        }

        sessions.clear();
        string date, time, title;
        while (getline(inFile, date) {
            getline(inFile, time);
            getline(inFile, title);
            sessions.emplace_back(date, time, title);
        }
    }

    void displayAll() const {
        for (const auto& session : sessions) {
            cout << session << "\n-----\n";
        }
    }
};

int main() {
    try {
        Cinema cinema;

        // Создаем и добавляем сеансы
        Session s1;
        cin >> s1;  // Вводим данные через оператор >>
        cinema.addSession(s1);

        Session s2("2023-12-25", "19:30", "Home Alone");
        cinema.addSession(s2);

        // Выводим данные через оператор <<
        cout << "\nAll sessions:\n";
        cinema.displayAll();

        // 4. Сохраняем в файл
        cinema.saveToFile("sessions.txt");
        cout << "\nSessions saved to file\n";

        // 5. Читаем из файла в новый объект
        Cinema cinema2;
        cinema2.loadFromFile("sessions.txt");
        cout << "\nSessions loaded from file:\n";
        cinema2.displayAll();

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}