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
    void reduceStock() { if (stockQuantity > 0) stockQuantity--; }

    void getDetails() {
        cout << productID << "\t" << name << "\t" << "₱" << price << endl;
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

public:
    ShoppingCart() : itemCount(0) {}

    void addProduct(Product &product) {
        if (product.getStock() > 0) {
            for (int i = 0; i < itemCount; i++) {
                if (cart[i].product->getID() == product.getID()) {
                    cart[i].quantity++;
                    product.reduceStock();
                    cout << "Product added successfully!" << endl;
                    return;
                }
            }
            cart[itemCount].product = &product;
            cart[itemCount].quantity = 1;
            itemCount++;
            product.reduceStock();
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
                 << "₱" << cart[i].product->getPrice() << "\t"
                 << cart[i].quantity << endl;
        }
    }

    double calculateTotal() {
        double total = 0;
        for (int i = 0; i < itemCount; i++) {
            total += cart[i].product->getPrice() * cart[i].quantity;
        }
        return total;
    }
};

class Order {
private:
    int orderID;
    ShoppingCart cart;
    double totalAmount;

public:
    Order(int id, ShoppingCart &c) : orderID(id), cart(c) {
        totalAmount = cart.calculateTotal();
    }

    void getOrderDetails() {
        cout << "Order ID: " << orderID << endl;
        cart.viewCart();
        cout << "Total Amount: ₱" << totalAmount << endl;
    }
};

int main() {
    Product products[] = {
        Product(1, "Laptop", 999.99, 5),
        Product(2, "Mouse", 49.99, 10),
        Product(3, "Keyboard", 79.99, 7),
        Product(4, "Monitor", 199.99, 4),
        Product(5, "Headphones", 59.99, 6)
    };
    ShoppingCart cart;
    Order *orders[10];
    int orderCount = 0;
    int orderID = 1;
    
    bool running = true;
    while (running) {
        cout << "\nMenu:\n1. View Products\n2. View Shopping Cart\n3. View Orders\n4. Exit\nEnter your choice: ";
        int choice;
        cin >> choice;
        
        if (choice == 1) {
            cout << "ProductID\tName\tPrice" << endl;
            for (int i = 0; i < 5; i++) {
                products[i].getDetails();
            }
            bool adding = true;
            while (adding) {
                cout << "Enter the ID of the product to add to cart (or 0 to quit): ";
                int productID;
                cin >> productID;
                if (productID == 0) break;
                bool found = false;
                for (int i = 0; i < 5; i++) {
                    if (products[i].getID() == productID) {
                        cart.addProduct(products[i]);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Invalid Product ID." << endl;
                }
            }
        }
        else if (choice == 2) {
            cart.viewCart();
            cout << "Do you want to checkout? (1 for Yes, 0 for No): ";
            int checkout;
            cin >> checkout;
            if (checkout == 1) {
                orders[orderCount++] = new Order(orderID++, cart);
                cout << "You have successfully checked out!" << endl;
                for (int i = 0; i < orderCount; i++) {
                    orders[i]->getOrderDetails();
                }
                cart = ShoppingCart();
            }
        }
        else if (choice == 3) {
            if (orderCount == 0) {
                cout << "No orders placed yet." << endl;
            } else {
                for (int i = 0; i < orderCount; i++) {
                    orders[i]->getOrderDetails();
                }
            }
        }
        else if (choice == 4) {
            cout << "Exiting..." << endl;
            running = false;
        }
        else {
            cout << "Invalid choice, try again." << endl;
        }
    }
    return 0;
}