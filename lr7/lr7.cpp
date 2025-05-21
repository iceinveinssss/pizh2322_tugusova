#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Session {
protected:
    string date;
    string time;
    string movieTitle;

public:
    Session(string d = "", string t = "", string mt = "") : date(d), time(t), movieTitle(mt) {}
    virtual ~Session() {}

    bool operator<(const Session& other) const { return movieTitle < other.movieTitle; }
    bool operator>(const Session& other) const { return movieTitle > other.movieTitle; }
};

class Booking : public Session {
private:
    string customerName;
    int seatNumber;

public:
    Booking(string d = "", string t = "", string mt = "", string name = "", int seat = 0)
        : Session(d, t, mt), customerName(name), seatNumber(seat) {
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
};

template <typename T>
class MyArray {
private:
    T* arr;
    int size;
    int capacity;

public:
    MyArray(int n) : size(0), capacity(n) {
        arr = new T[capacity];
    }

    ~MyArray() {
        delete[] arr;
    }

    void add(const T& element) {
        if (size < capacity) {
            arr[size++] = element;
        }
    }

    T get(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return arr[index];
    }

    T min() const {
        if (size == 0) throw runtime_error("Array is empty");
        T min_val = arr[0];
        for (int i = 1; i < size; ++i) {
            if (arr[i] < min_val) {
                min_val = arr[i];
            }
        }
        return min_val;
    }

    T max() const {
        if (size == 0) throw runtime_error("Array is empty");
        T max_val = arr[0];
        for (int i = 1; i < size; ++i) {
            if (arr[i] > max_val) {
                max_val = arr[i];
            }
        }
        return max_val;
    }
};

int main() {
    // Для int
    MyArray<int> intArr(5);
    intArr.add(10);
    intArr.add(5);
    intArr.add(20);
    cout << "Min int: " << intArr.min() << endl;
    cout << "Max int: " << intArr.max() << endl;

    // Для char
    MyArray<char> charArr(3);
    charArr.add('z');
    charArr.add('a');
    charArr.add('m');
    cout << "Min char: " << charArr.min() << endl;
    cout << "Max char: " << charArr.max() << endl;

    // Для указателей на Session
    MyArray<Session*> sessionArr(3);
    Session s1("2023-01-01", "10:00", "Movie A");
    Session s2("2023-01-02", "12:00", "Movie B");
    Session s3("2023-01-03", "14:00", "Movie C");
    sessionArr.add(&s1);
    sessionArr.add(&s2);
    sessionArr.add(&s3);
    cout << "Min session: " << sessionArr.min()->movieTitle << endl;
    cout << "Max session: " << sessionArr.max()->movieTitle << endl;

    // Для наследников
    MyArray<Session*> derivedArr(2);
    Booking b1("2023-01-01", "10:00", "Movie X", "Ivan", 5);
    PaidTicket p1("2023-01-02", "12:00", "Movie Y", 300.0, true);
    derivedArr.add(&b1);
    derivedArr.add(&p1);
    cout << "Min derived: " << derivedArr.min()->movieTitle << endl;
    cout << "Max derived: " << derivedArr.max()->movieTitle << endl;

    return 0;
}