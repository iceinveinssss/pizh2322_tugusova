#include <iostream>
#include <string>
#include <vector>
using namespace std;

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
};

// ������������� ������������ �������� �������� � �������
int Cinema::arrayObjectCount = 0;

// �������� main
int main() {
    setlocale(LC_ALL, "Russian");  // ��������� �����������

    // ����� ���������� �������� �� �������� (����� 6 �������)
    cout << "���������� �������� Session �� ��������: " << Session::getObjectCount() << endl;
    cout << "���������� �������� � ������� Cinema �� ��������: " << Cinema::getArrayObjectCount() << endl << endl;

    cout << "========= ����� 1: ������ �������� (��������� �� Session) =========\n";
    Session* sessionArray[3];  // ������ ���������� �� ������� �����
    sessionArray[0] = new Booking("2025-04-24", "17:00", "������������", "������ �.�.", 4);
    sessionArray[1] = new PaidTicket("2025-04-24", "19:00", "������������", 450.0, true);
    sessionArray[2] = new Booking("2025-04-25", "21:00", "�����", "������ �.�.", 9);

    // ����� ���� ������� � �������
    for (int i = 0; i < 3; i++) {
        sessionArray[i]->fullOutput();
        cout << "--------------------------------\n";
    }

    cout << "\n========= ����� 2: ������ � Cinema =========\n";
    Cinema myCinema;  // �������� ������� Cinema
    myCinema.setName("������");
    myCinema.setAddress("��. ��������, 1");

    // ���������� ������� � ��������� (����� 7 �������)
    myCinema.addSession(new Booking("2025-04-26", "18:00", "����", "������� �.�.", 6));
    myCinema.addSession(new PaidTicket("2025-04-26", "20:00", "����", 400.0, false));

    // ����� ���������� � ����������
    myCinema.outputAll();

    // ����� ���������� �������� ����� �������� (����� 8 �������)
    cout << "\n���������� �������� Session ����� ��������: " << Session::getObjectCount() << endl;
    cout << "���������� �������� � ������� Cinema: " << Cinema::getArrayObjectCount() << endl << endl;

    // ������������ ������, ���� �������� ���-�� �� sessionArray
    for (int i = 0; i < 3; i++) {
        delete sessionArray[i];  // ������������ ������
    }

    cout << "\n========= ����� ��������� =========\n";
    return 0;
}