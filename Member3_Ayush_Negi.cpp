#include <iostream>
#include <string>
using namespace std;

const int MAX_ORDERS = 100;

class Order {
    int id, priority;
    string customer, status;
    double amount;
public:
    Order()
     { id=0;
       priority=0;
       customer=" ";
       status="Pending";
       amount=0;
    
    
    }

    Order(int i, string c, double a, int p)
     {
       id=i;
       priority=p;
       customer=c;
       amount=a;
       status="Pending";



     }
    int getId() const
     { return id; }

    int getPriority() const
     { return priority; }

    void display() const {
        cout << "Order ID: " << id << " | Customer: " << customer
             << " | Amount: Rs. " << amount << " | Status: " << status
             << " | Priority: " << priority << "\n";
    }
};


class NormalQueue {
    Order data[MAX_ORDERS];
    int frontIndex, rearIndex, count;
public:
    NormalQueue() 
     {
       frontIndex=0;
       rearIndex=-1;
       count =0;
      }


    bool enqueue(Order o) {
        if (count == MAX_ORDERS) { cout << "Normal queue full.\n"; return false; }
        rearIndex = (rearIndex + 1) % MAX_ORDERS;
        data[rearIndex] = o; count++; return true;
    }
    bool dequeue() {
        if (count == 0) { cout << "No normal orders.\n"; return false; }
        cout << "Processing normal order: "; data[frontIndex].display();
        frontIndex = (frontIndex + 1) % MAX_ORDERS; count--; return true;
    }
    void display() const {
        if (!count) { cout << "No normal orders.\n"; return; }
        for (int i = 0; i < count; i++)
            data[(frontIndex + i) % MAX_ORDERS].display();
    }
};


class PriorityQueue {
    Order data[MAX_ORDERS];
    int count;

public:
    PriorityQueue() : count(0) {}

    bool enqueue(Order o) {
        if (count == MAX_ORDERS) {
            cout << "Priority queue full.\n";
            return false;
        }

        int i = count - 1;

        // Shift lower-priority orders to the right.
        while (i >= 0 &&
               data[i].getPriority() < o.getPriority()) {
            data[i + 1] = data[i];
            i--;
        }

        // Insert the new order at its correct position.
        data[i + 1] = o;
        count++;

        return true;
    }

    bool process() {
        if (count == 0) {
            cout << "No priority orders.\n";
            return false;
        }

        // Highest-priority order is always at index 0.
        cout << "Processing highest-priority order: ";
        data[0].display();

        // Shift remaining orders one position left.
        for (int i = 0; i < count - 1; i++) {
            data[i] = data[i + 1];
        }

        count--;
        return true;
    }

    void display() const {
        if (count == 0) {
            cout << "No priority orders.\n";
            return;
        }

        cout << "Priority orders (highest to lowest):\n";

        for (int i = 0; i < count; i++) {
            data[i].display();
        }
    }
};


int main() {
    NormalQueue normal;
    PriorityQueue priority;
    int ch;

    do {
        cout << "\n"
             << "1 Add normal order\n"
             << "2 Add priority order\n"
             << "3 Display normal orders\n"
             << "4 Display priority orders\n"
             << "5 Process next normal order\n"
             << "6 Process highest-priority order\n"
             << "0 Exit\nChoice: ";
        cin >> ch;

        if (ch == 1 || ch == 2) {
            int id, p = 0;
            string customer;
            double amount;

            cout << "Order ID: ";
            cin >> id;
            cout << "Customer ";
            cin >> customer;
            cout << "Total amount: ";
            cin >> amount;

            if (id <= 0 || amount < 0) {
                cout << "Invalid order data.\n";
                continue;
            }

            if (ch == 2) {
                cout << "Priority  ";
                cin >> p;
                if (p < 1 || p > 10) {
                    cout << "Priority must be 1-10.\n";
                    continue;
                }
                priority.enqueue(Order(id, customer, amount, p));
            } 
            else {
                normal.enqueue(Order(id, customer, amount, 0));
            }
        } else if (ch == 3) {
            normal.display();
        } else if (ch == 4) {
            priority.display();
        } else if (ch == 5) {
            normal.dequeue();
        } else if (ch == 6) {
            priority.process();
        } else if (ch != 0) {
            cout << "Invalid choice.\n";
        }
    } while (ch != 0);

    return 0;
}
