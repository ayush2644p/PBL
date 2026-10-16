#include <iostream>
#include <string>
using namespace std;

const int MAX_PRODUCTS = 100;

class Product {
    int id;
    string name, category;
    double price;
    int stock;
public:
    Product() : id(0), name(""), category(""), price(0), stock(0) {}
    Product(int i, string n, string c, double p, int s)
        : id(i), name(n), category(c), price(p), stock(s) {}
    int getId() const { return id; }
    string getName() const { return name; }
    string getCategory() const { return category; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
    void setName(string n) { name = n; }
    void setCategory(string c) { category = c; }
    void setPrice(double p) { price = p; }
    void setStock(int s) { stock = s; }
    void display() const {
        cout << "\nID: " << id << "\nName: " << name
             << "\nCategory: " << category << "\nPrice: Rs. " << price
             << "\nStock: " << stock << "\n";
    }
};

class Inventory {
    Product products[MAX_PRODUCTS];
    int count;
    int findIndex(int id) const {
        for (int i = 0; i < count; i++)
            if (products[i].getId() == id) return i;
        return -1;
    }
public:
    Inventory() : count(0) {}
    void addProduct() {
        if (count == MAX_PRODUCTS) { cout << "Inventory full.\n"; return; }
        int id, stock; double price; string name, category;
        cout << "ID: "; cin >> id;
        cout << "Name (one word): "; cin >> name;
        cout << "Category (one word): "; cin >> category;
        cout << "Price: "; cin >> price;
        cout << "Stock: "; cin >> stock;
        if (id <= 0 || price < 0 || stock < 0) {
            cout << "Invalid ID, price, or stock.\n"; return;
        }
        if (findIndex(id) != -1) { cout << "Duplicate product ID.\n"; return; }
        products[count++] = Product(id, name, category, price, stock);
        cout << "Product added.\n";
    }
    void displayProducts() const {
        if (!count) { cout << "No products.\n"; return; }
        for (int i = 0; i < count; i++) products[i].display();
    }
    void searchProduct() const {
        int id; cout << "Product ID: "; cin >> id;
        int i = findIndex(id);
        if (i == -1) cout << "Product not found.\n";
        else products[i].display();
    }
    void updateProduct() {
        int id; cout << "Product ID: "; cin >> id;
        int i = findIndex(id);
        if (i == -1) { cout << "Product not found.\n"; return; }
        string n, c; double p; int s;
        cout << "New name: "; cin >> n;
        cout << "New category: "; cin >> c;
        cout << "New price: "; cin >> p;
        cout << "New stock: "; cin >> s;
        if (p < 0 || s < 0) { cout << "Invalid price/stock.\n"; return; }
        products[i].setName(n); products[i].setCategory(c);
        products[i].setPrice(p); products[i].setStock(s);
        cout << "Product updated.\n";
    }
    void deleteProduct() {
        int id; cout << "Product ID: "; cin >> id;
        int i = findIndex(id);
        if (i == -1) { cout << "Product not found.\n"; return; }
        for (int j = i; j < count - 1; j++) products[j] = products[j + 1];
        count--; cout << "Product deleted.\n";
    }
    void changeStock(bool increase) {
        int id, q; cout << "Product ID: "; cin >> id;
        cout << "Quantity: "; cin >> q;
        int i = findIndex(id);
        if (i == -1) { cout << "Product not found.\n"; return; }
        if (q <= 0 || (!increase && q > products[i].getStock())) {
            cout << "Invalid quantity or insufficient stock.\n"; return;
        }
        int stock = products[i].getStock();
        products[i].setStock(increase ? stock + q : stock - q);
        cout << "Stock updated.\n";
    }
};

int main() {
    Inventory inv; int ch;
    do {
        cout << "\n=== MEMBER 1: AYUSH SINGH KIRSALI ===\n"
             << "1 Add product\n2 Display products\n3 Search\n4 Update\n"
             << "5 Delete\n6 Increase stock\n7 Decrease stock\n0 Exit\nChoice: ";
        cin >> ch;
        if (ch == 1) inv.addProduct();
        else if (ch == 2) inv.displayProducts();
        else if (ch == 3) inv.searchProduct();
        else if (ch == 4) inv.updateProduct();
        else if (ch == 5) inv.deleteProduct();
        else if (ch == 6) inv.changeStock(true);
        else if (ch == 7) inv.changeStock(false);
    } while (ch != 0);
    return 0;
}
