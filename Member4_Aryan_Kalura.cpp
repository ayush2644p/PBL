#include <iostream>
#include <string>
#include <cctype>
using namespace std;

const int MAX_RECORDS = 100;

class Validator {
public:
    static bool validId(int id) { return id > 0; }
    static bool validPrice(double price) { return price >= 0; }
    static bool validQuantity(int q) { return q > 0; }
    static bool validName(const string& name) {
        if (name.empty()) return false;
        for (char c : name)
            if (isdigit(static_cast<unsigned char>(c))) return false;
        return true;
    }
    static bool validEmail(const string& email) {
        size_t at = email.find('@'), dot = email.rfind('.');
        return at != string::npos && dot != string::npos &&
               at > 0 && dot > at + 1 && dot + 1 < email.length();
    }
};

class DataManager {
    string records[MAX_RECORDS];
    int count;
public:
    DataManager() : count(0) {}
    void add() {
        if (count == MAX_RECORDS) { cout << "Record storage full.\n"; return; }
        string text;
        cout << "Enter record (one word): "; cin >> text;
        if (text.empty()) { cout << "Record cannot be empty.\n"; return; }
        records[count++] = text; cout << "Record added.\n";
    }
    void display() const {
        if (!count) { cout << "No records.\n"; return; }
        for (int i = 0; i < count; i++) cout << i + 1 << ". " << records[i] << "\n";
    }
    void search() const {
        string key; cout << "Keyword: "; cin >> key;
        bool found = false;
        for (int i = 0; i < count; i++) {
            if (records[i].find(key) != string::npos) {
                cout << i + 1 << ". " << records[i] << "\n"; found = true;
            }
        }
        if (!found) cout << "No matching record.\n";
    }
    void removeRecord() {
        int n; cout << "Record number: "; cin >> n;
        if (n < 1 || n > count) { cout << "Invalid record number.\n"; return; }
        for (int i = n - 1; i < count - 1; i++) records[i] = records[i + 1];
        count--; cout << "Record deleted.\n";
    }
    void total() const { cout << "Total records: " << count << "\n"; }
};

int main() {
    DataManager manager; int ch;
    do {
        cout << "\n=== MEMBER 4: ARYAN KALURA ===\n"
             << "1 Validate ID\n2 Validate price\n3 Validate quantity\n"
             << "4 Validate name\n5 Validate email\n6 Add record\n"
             << "7 Display records\n8 Search record\n9 Delete record\n"
             << "10 Count records\n0 Exit\nChoice: ";
        cin >> ch;
        if (ch == 1) {
            int x; cout << "ID: "; cin >> x;
            cout << (Validator::validId(x) ? "Valid\n" : "Invalid\n");
        } else if (ch == 2) {
            double x; cout << "Price: "; cin >> x;
            cout << (Validator::validPrice(x) ? "Valid\n" : "Invalid\n");
        } else if (ch == 3) {
            int x; cout << "Quantity: "; cin >> x;
            cout << (Validator::validQuantity(x) ? "Valid\n" : "Invalid\n");
        } else if (ch == 4) {
            string x; cout << "Name: "; cin >> x;
            cout << (Validator::validName(x) ? "Valid\n" : "Invalid\n");
        } else if (ch == 5) {
            string x; cout << "Email: "; cin >> x;
            cout << (Validator::validEmail(x) ? "Valid\n" : "Invalid\n");
        } else if (ch == 6) manager.add();
        else if (ch == 7) manager.display();
        else if (ch == 8) manager.search();
        else if (ch == 9) manager.removeRecord();
        else if (ch == 10) manager.total();
    } while (ch != 0);
    return 0;
}
