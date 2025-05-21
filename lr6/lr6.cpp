#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ��������������� ���������� ������ Cinema ��� ������������� �������
class Cinema;

// ����������� ������� ����� � �����
class Session {
private:
    static int objectCount;  // �������� ����������� ������� ��������

protected:
    string date;   // ���� ������
    string time;   // ����� ������
    string movieTitle;   // �������� ������

public:
    // ����������� �� ���������
    Session() : date("No date"), time("No time"), movieTitle("No title") {
        objectCount++;
        cout << "Session: Default constructor" << endl;
    }

    // ����������� � �����������
    Session(string d, string t, string mt) : date(d), time(t), movieTitle(mt) {
        objectCount++;
        cout << "Session: Constructor with parameters" << endl;
    }

    // ����������� �����������
    Session(const Session& s) : date(s.date), time(s.time), movieTitle(s.movieTitle) {
        objectCount++;
        cout << "Session: Copy constructor" << endl;
    }

    // ����������� ����������
    virtual ~Session() {
        objectCount--;
        cout << "Session: Destructor" << endl;
    }

    // ����� ��� ����� ������
    virtual void input() {
        cout << "������� ����: ";
        getline(cin, date);
        cout << "������� �����: ";
        getline(cin, time);
        cout << "������� �������� ������: ";
        getline(cin, movieTitle);
    }

    // ����� ��� ������ ������
    virtual void output() const {
        cout << "�����: " << movieTitle << " | ����: " << date << " | �����: " << time << endl;
    }

    // ����� ����������� ������� ��� ������� ������
    virtual void fullOutput() const = 0;

    // ����������� ����� ��� ��������� ���������� ��������
    static int getObjectCount() {
        return objectCount;
    }
};

// ������������� ������������ ��������
int Session::objectCount = 0;

// �����-��������� � ������������
class Booking : public Session {
private:
    string customerName;  // ��� �������
    int seatNumber;  // ����� �����

public:
    // ����������� �� ���������
    Booking() : Session(), customerName("Unknown"), seatNumber(0) {
        cout << "Booking: Default constructor" << endl;
    }

    // ����������� � �����������
    Booking(string d, string t, string mt, string name, int seat)
        : Session(d, t, mt), customerName(name), seatNumber(seat) {
        cout << "Booking: Constructor with parameters" << endl;
    }

    // ����������
    ~Booking() override {
        cout << "Booking: Destructor" << endl;
    }

    // ���������������� ����� ����� ������
    void input() override {
        Session::input();  // ���� ������ ��� �������� ������
        cout << "������� ��� �������: ";
        getline(cin, customerName);
        cout << "������� ����� �����: ";
        cin >> seatNumber;
        cin.ignore();  // ������� �����
    }

    // ���������������� ����� ������ ������
    void output() const override {
        Session::output();  // ����� ������ ��� �������� ������
        cout << "����������� ���: " << customerName << ", �����: " << seatNumber << endl;
    }

    // ���������������� ����� ������� ������
    void fullOutput() const override {
        output();  // ������� ��� ������
    }
};

// �����-��������� � ���������� ������
class PaidTicket : public Session {
private:
    double price;  // ���� ������
    bool isPaid;  // ������ ������

public:
    // ����������� �� ���������
    PaidTicket() : Session(), price(0.0), isPaid(false) {
        cout << "PaidTicket: Default constructor" << endl;
    }

    // ����������� � �����������
    PaidTicket(string d, string t, string mt, double p, bool paid)
        : Session(d, t, mt), price(p), isPaid(paid) {
        cout << "PaidTicket: Constructor with parameters" << endl;
    }

    // ����������
    ~PaidTicket() override {
        cout << "PaidTicket: Destructor" << endl;
    }

    // ���������������� ����� ����� ������
    void input() override {
        Session::input();  // ���� ������ ��� �������� ������
        cout << "������� ���� ������: ";
        cin >> price;
        cout << "��������? (1 - ��, 0 - ���): ";
        cin >> isPaid;
        cin.ignore();  // ������� �����
    }

    // ���������������� ����� ������ ������
    void output() const override {
        Session::output();  // ����� ������ ��� �������� ������
        cout << "����: " << price << ", ��������: " << (isPaid ? "��" : "���") << endl;
    }

    // ���������������� ����� ������� ������
    void fullOutput() const override {
        output();  // ������� ��� ������
    }
};

// ���������� �������� ������ ��� Session
ostream& operator<<(ostream& os, const Session& session) {
    session.output();
    return os;
}

// �������� ����� � ���������
class Cinema {
private:
    string name;  // �������� ����������
    string address;  // ����� ����������
    vector<Session*> sessions;  // ������ ��� �������� ���������� �� ������
    static int arrayObjectCount;  // �������� ����������� ������� �������� � �������

public:
    Cinema() = default;  // ����������� �� ���������

    // ����������
    ~Cinema() {
        for (auto s : sessions) {
            delete s;  // ������������ ������
        }
        sessions.clear();  // ������� �������
    }

    // ��������� � ��������� �������� ����������
    void setName(const string& n) { name = n; }
    string getName() const { return name; }

    // ��������� � ��������� ������ ����������
    void setAddress(const string& a) { address = a; }
    string getAddress() const { return address; }

    // ���������� ������ � ������
    void addSession(Session* s) {
        sessions.push_back(s);
        arrayObjectCount++;
    }

    // ����� ���� ���������� � ���������� � �������
    void outputAll() const {
        cout << "\n���������: " << name << "\n�����: " << address << "\n������:\n";
        for (size_t i = 0; i < sessions.size(); ++i) {
            cout << "\n����� " << i + 1 << ":\n";
            sessions[i]->fullOutput();  // ����� ������ ������� ������
        }
    }

    // ����������� ����� ��� ��������� ���������� �������� � �������
    static int getArrayObjectCount() {
        return arrayObjectCount;
    }

    // �������� + ��� ���������� ������� (����� 2 �������)
    Cinema& operator+(Session* newSession) {
        this->addSession(newSession);
        return *this;
    }

    // ���������� �������� ++ (����� 3 �������)
    Cinema& operator++() {
        this->addSession(new Booking());  // ��������� ������ �� ���������
        return *this;
    }

    // ����������� �������� ++ (����� 3 �������)
    Cinema operator++(int) {
        Cinema temp = *this;
        this->addSession(new PaidTicket());  // ��������� ������ �� ���������
        return temp;
    }

    // �������� [] ��� ������� � ��������� ������� (����� 4 �������)
    Session* operator[](size_t index) {
        if (index >= sessions.size()) {
            throw out_of_range("������ ������� �� ������� �������");
        }
        return sessions[index];
    }

    // ������������� ������� ��� ��������� ������
    friend ostream& operator<<(ostream& os, const Cinema& cinema);
};

// ���������� �������� ������ ��� Cinema (����� 5 �������)
ostream& operator<<(ostream& os, const Cinema& cinema) {
    os << "���������: " << cinema.name << "\n�����: " << cinema.address
        << "\n���������� �������: " << cinema.sessions.size() << "\n";
    return os;
}

// ������������� ������������ �������� �������� � �������
int Cinema::arrayObjectCount = 0;

// �������� main
int main() {
    setlocale(LC_ALL, "Russian");  // ��������� �����������

    cout << "========= ������������ ������ ���������� =========\n";

    Cinema cinema;
    cinema.setName("������");
    cinema.setAddress("��. �����������, 15");

    // ������������ ��������� + (����� 6 �������)
    cinema + new Booking("2025-05-01", "15:00", "������", "������� �.�.", 12);
    cinema + new PaidTicket("2025-05-01", "18:00", "������", 350.0, true);

    // ������������ ����������� ++ (����� 6 �������)
    ++cinema;

    // ������������ ������������ ++ (����� 6 �������)
    cinema++;

    // ������������ ��������� ������ (����� 6 �������)
    cout << cinema;

    // ������������ ��������� [] (����� 6 �������)
    try {
        cout << "\n���������� � ������ ������:\n";
        cout << *cinema[0];  // ���������� ���������� �������� << ��� Session
    }
    catch (const out_of_range& e) {
        cerr << "������: " << e.what() << endl;
    }

    // ����� ���� ���������� � ����������
    cout << "\n������ ���������� � ����������:\n";
    cinema.outputAll();

    cout << "\n========= ����� ��������� =========\n";
    return 0;
}