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
        cout << "�����: " << movieTitle << " | ����: " << date << " | �����: " << time << endl;
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
        cout << "����������� ���: " << customerName << ", �����: " << seatNumber << endl;
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
        cout << "����: " << price << ", ��������: " << (isPaid ? "��" : "���") << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    // 1. �������� ���������� vector � ��������� ����������������� ����
    vector<Session*> sessions = {
        new Session("2024-06-01", "18:00", "������������"),
        new Booking("2024-06-02", "19:30", "����", "������ �.�.", 5),
        new PaidTicket("2024-06-03", "21:00", "�������", 350.0, true),
        new Session("2024-06-04", "15:00", "������"),
        new Booking("2024-06-05", "20:00", "������� �����", "������ �.�.", 8)
    };

    // 2. ������ ���������� ������� �� ������-���������

    // ���������� �� �������� ������� ������
    sort(sessions.begin(), sessions.end(), [](Session* a, Session* b) {
        return a->getTime() > b->getTime();
        });

    cout << "������, ��������������� �� �������� �������:\n";
    for_each(sessions.begin(), sessions.end(), [](Session* s) {
        s->output();
        cout << "-----\n";
        });

    // ����� ���� ������� �� "����"
    list<Session*> duneSessions;
    copy_if(sessions.begin(), sessions.end(), back_inserter(duneSessions), [](Session* s) {
        return s->getMovieTitle() == "����";
        });

    cout << "\n��� ������ �� '����':\n";
    for_each(duneSessions.begin(), duneSessions.end(), [](Session* s) {
        s->output();
        cout << "-----\n";
        });

    // �������� ���� ������� �� 2024-06-03
    sessions.erase(remove_if(sessions.begin(), sessions.end(), [](Session* s) {
        return s->getDate() < "2024-06-03";
        }), sessions.end());

    cout << "\n������ ����� 2024-06-03:\n";
    for_each(sessions.begin(), sessions.end(), [](Session* s) {
        s->output();
        cout << "-----\n";
        });

    // ������������ ������
    for_each(sessions.begin(), sessions.end(), [](Session* s) { delete s; });
    for_each(duneSessions.begin(), duneSessions.end(), [](Session* s) { delete s; });

    return 0;
}