#include <iostream>
#include <string>
using namespace std;

const int MAX_ACTIONS = 100;

class User {
protected:
    int id;
    string name, email;
public:
    User(int i, string n, string e) : id(i), name(n), email(e) {}
    virtual void displayProfile() const = 0;
    virtual ~User() {}
};
class Customer : public User {
    string phone;
public:
    Customer(int i, string n, string e, string p) : User(i, n, e), phone(p) {}
    void displayProfile() const override {
        cout << "\nCustomer ID: " << id << "\nName: " << name
             << "\nEmail: " << email << "\nPhone: " << phone << "\n";
    }
};

struct Action {
    int type, id, quantity;
    string name;
    double price;
    Action() : type(0), id(0), quantity(0), name(""), price(0) {}
    Action(int t, int i, string n, double p, int q)
        : type(t), id(i), quantity(q), name(n), price(p) {}
};

// Custom stack implemented using an array, not STL stack.
class ActionStack {
    Action data[MAX_ACTIONS];
    int topIndex;
public:
    ActionStack() : topIndex(-1) {}
    bool push(Action a) {
        if (topIndex == MAX_ACTIONS - 1) {
            cout << "Undo history full; action will not be saved.\n"; return false;
        }
        data[++topIndex] = a; return true;
    }
    bool pop(Action& a) {
        if (topIndex == -1) return false;
        a = data[topIndex--]; return true;
    }
};

struct Node {
    int id, quantity;
    string name;
    double price;
    Node* next;
    Node(int i, string n, double p, int q)
        : id(i), quantity(q), name(n), price(p), next(nullptr) {}
};

class Cart {
    Node* head;
    ActionStack history;
    Node* find(int id) const {
        Node* cur = head;
        while (cur) { if (cur->id == id) return cur; cur = cur->next; }
        return nullptr;
    }
public:
    Cart() : head(nullptr) {}
    ~Cart() {
        while (head) { Node* t = head; head = head->next; delete t; }
    }
    void add(int id, string name, double price, int qty) {
        if (id <= 0 || price < 0 || qty <= 0) {
            cout << "Invalid ID, price, or quantity.\n"; return;
        }
        Node* n = find(id);
        if (n) {
            n->quantity += qty;
            history.push(Action(1, id, n->name, n->price, qty));
        } else {
            Node* fresh = new Node(id, name, price, qty);
            if (!head) head = fresh;
            else {
                Node* cur = head;
                while (cur->next) cur = cur->next;
                cur->next = fresh;
            }
            history.push(Action(1, id, name, price, qty));
        }
        cout << "Added to cart.\n";
    }
    void remove(int id) {
        Node *cur = head, *prev = nullptr;
        while (cur && cur->id != id) { prev = cur; cur = cur->next; }
        if (!cur) { cout << "Item not found.\n"; return; }
        history.push(Action(2, cur->id, cur->name, cur->price, cur->quantity));
        if (!prev) head = cur->next; else prev->next = cur->next;
        delete cur; cout << "Removed from cart.\n";
    }
    void display() const {
        if (!head) { cout << "Cart is empty.\n"; return; }
        double total = 0; Node* cur = head;
        while (cur) {
            double sub = cur->price * cur->quantity; total += sub;
            cout << "ID " << cur->id << " | " << cur->name
                 << " | Rs. " << cur->price << " x " << cur->quantity
                 << " = Rs. " << sub << "\n";
            cur = cur->next;
        }
        cout << "Cart total: Rs. " << total << "\n";
    }
    void undo() {
        Action a;
        if (!history.pop(a)) { cout << "Nothing to undo.\n"; return; }
        if (a.type == 1) {
            Node *cur = head, *prev = nullptr;
            while (cur && cur->id != a.id) { prev = cur; cur = cur->next; }
            if (cur) {
                cur->quantity -= a.quantity;
                if (cur->quantity <= 0) {
                    if (!prev) head = cur->next; else prev->next = cur->next;
                    delete cur;
                }
            }
            cout << "Last add undone.\n";
        } else {
            Node* fresh = new Node(a.id, a.name, a.price, a.quantity);
            fresh->next = head; head = fresh;
            cout << "Last remove undone (item restored at cart start).\n";
        }
    }
};

int main() {
    Customer customer(102, "Harsh", "harsh@example.com", "9999999999");
    Cart cart; int ch;
    do {
        cout << "\n=== MEMBER 2: HARSH VARDHAN ===\n"
             << "1 View profile\n2 Add cart item\n3 Remove cart item\n"
             << "4 Display cart/total\n5 Undo last action\n0 Exit\nChoice: ";
        cin >> ch;
        if (ch == 1) customer.displayProfile();
        else if (ch == 2) {
            int id, qty; string name; double price;
            cout << "Product ID: "; cin >> id;
            cout << "Name (one word): "; cin >> name;
            cout << "Price: "; cin >> price;
            cout << "Quantity: "; cin >> qty;
            cart.add(id, name, price, qty);
        } else if (ch == 3) {
            int id; cout << "Product ID: "; cin >> id; cart.remove(id);
        } else if (ch == 4) cart.display();
        else if (ch == 5) cart.undo();
    } while (ch != 0);
    return 0;
}
