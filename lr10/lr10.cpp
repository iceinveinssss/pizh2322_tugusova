#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ������� ����� � �����
class Session {
protected:
    string date;
    string time;
    string movieTitle;

public:
    Session(string d = "", string t = "", string mt = "") : date(d), time(t), movieTitle(mt) {}
    virtual ~Session() {}

    virtual void output() const {
        cout << "�����: " << movieTitle << " | ����: " << date << " | �����: " << time << endl;
    }
};

// �����-��������� � ������������
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

// �����-��������� � ���������� ������
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

    // 2. �������� � ���������� ���������� (vector) �������� ������
    vector<int> numbers = { 10, 20, 30, 40, 50 };

    // 3. �������� ����������
    cout << "�������� ��������� (int):" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    // 4. ��������� ����������
    numbers.erase(remove(numbers.begin(), numbers.end(), 30), numbers.end());
    numbers[1] = 25;

    // 5. �������� � �������������� ����������
    cout << "\n���������� ��������� (int):" << endl;
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    // 6. ������ � ���������������� �����
    vector<Session*> sessions;
    sessions.push_back(new Session("2024-06-01", "18:00", "������������"));
    sessions.push_back(new Booking("2024-06-02", "19:30", "����", "������ �.�.", 5));
    sessions.push_back(new PaidTicket("2024-06-03", "21:00", "�������", 350.0, true));

    // �������� ��������� ����������
    cout << "\n�������� ��������� (Session*):" << endl;
    for (const auto& session : sessions) {
        session->output();
        cout << "-----" << endl;
    }

    // ��������� ����������
    delete sessions[1];
    sessions.erase(sessions.begin() + 1);
    sessions.push_back(new Booking("2024-06-04", "15:00", "������", "������ �.�.", 8));

    // �������� � �������������� ����������
    cout << "\n���������� ��������� (Session*):" << endl;
    for (auto it = sessions.begin(); it != sessions.end(); ++it) {
        (*it)->output();
        cout << "-----" << endl;
    }

    // ������������ ������
    for (auto session : sessions) {
        delete session;
    }

    return 0;
}