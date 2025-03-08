#include <iostream>
using namespace std;

class Product {
private:
    int productID;
    string name;
    double price;
    int stockQuantity;

public:
    Product(int id, string n, double p, int stock) : productID(id), name(n), price(p), stockQuantity(stock) {}

    int getID() { return productID; }
    string getName() { return name; }
    double getPrice() { return price; }
    int getStock() { return stockQuantity; }
    void reduceStock(int quantity) { if (stockQuantity >= quantity) stockQuantity -= quantity; }

    void getDetails() {
        cout << productID << "\t" << name << "\t" << "\u20B1" << price << endl;
    }
};

class ShoppingCart {
private:
    struct CartItem {
        Product *product;
        int quantity;
    };
    CartItem cart[10];
    int itemCount;
    static int orderID;

public:
    ShoppingCart() : itemCount(0) {}

    void addProduct(Product &product) {
        if (itemCount >= 10) {
            cout << "Cart is full! Cannot add more items." << endl;
            return;
        }
        if (product.getStock() > 0) {
            for (int i = 0; i < itemCount; i++) {
                if (cart[i].product->getID() == product.getID()) {
                    cart[i].quantity++;
                    product.reduceStock(1);
                    cout << "Product added successfully!" << endl;
                    return;
                }
            }
            cart[itemCount].product = &product;
            cart[itemCount].quantity = 1;
            itemCount++;
            product.reduceStock(1);
            cout << "Product added successfully!" << endl;
        } else {
            cout << "Product out of stock!" << endl;
        }
    }

    void viewCart() {
        if (itemCount == 0) {
            cout << "Shopping cart is empty." << endl;
            return;
        }
        cout << "ProductID\tName\tPrice\tQuantity" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout << cart[i].product->getID() << "\t"
                 << cart[i].product->getName() << "\t"
                 << "\u20B1" << cart[i].product->getPrice() << "\t"
                 << cart[i].quantity << endl;
        }
    }

    void checkout() {
        if (itemCount == 0) {
            cout << "Shopping cart is empty. Cannot checkout." << endl;
            return;
        }
        double totalAmount = 0;
        cout << "Order ID: " << orderID++ << endl;
        cout << "Total Amount: ";
        for (int i = 0; i < itemCount; i++) {
            totalAmount += cart[i].product->getPrice() * cart[i].quantity;
        }
        cout << totalAmount << endl;
        cout << "Order Details:" << endl;
        cout << "Product ID\tName\tPrice\tQuantity" << endl;
        for (int i = 0; i < itemCount; i++) {
            cout << cart[i].product->getID() << "\t"
                 << cart[i].product->getName() << "\t"
                 << cart[i].product->getPrice() << "\t"
                 << cart[i].quantity << endl;
        }
        itemCount = 0;
    }
};

int ShoppingCart::orderID = 1;

bool getValidInput(int &input) {
    string userInput;
    cin >> userInput;
    for (char c : userInput) {
        if (!isdigit(c)) {
            cout << "Invalid input. Please enter a number." << endl;
            return false;
        }
    }
    input = stoi(userInput);
    return true;
}

int main() {
    Product products[] = {
        Product(1, "Laptop", 999.99, 5),
        Product(2, "Mouse", 49.99, 10),
        Product(3, "Keyboard", 79.99, 7),
        Product(4, "Monitor", 199.99, 4),
        Product(5, "Headphones", 59.99, 6)
    };
    
    ShoppingCart cart;
    int choice;
    bool running = true;
    while (running) {
        cout << "\nMenu:\n1. View Products\n2. View Shopping Cart\n3. Checkout\n4. Exit\nEnter your choice: ";
        if (!getValidInput(choice)) continue;
        
        if (choice == 1) {
            cout << "ProductID\tName\tPrice" << endl;
            for (int i = 0; i < 5; i++) {
                products[i].getDetails();
            }
            
            int productID;
            bool addingProduct = true;
            while (addingProduct) {
                cout << "Enter the ID of the product to add to cart (or 0 to quit): ";
                if (!getValidInput(productID)) continue;
                if (productID == 0) {
                    addingProduct = false;
                    break;
                }
                
                bool found = false;
                for (int i = 0; i < 5; i++) {
                    if (products[i].getID() == productID) {
                        cart.addProduct(products[i]);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Invalid Product ID. Please try again." << endl;
                }
            }
        } else if (choice == 2) {
            cart.viewCart();
        } else if (choice == 3) {
            cart.checkout();
        } else if (choice == 4) {
            cout << "Exiting..." << endl;
            running = false;
        } else {
            cout << "Invalid choice, try again." << endl;
        }
    }
    return 0;
}
