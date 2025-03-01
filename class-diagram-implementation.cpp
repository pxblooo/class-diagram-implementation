#include <iostream>
using namespace std;

class Product {
    public:
        int productID;
        string name;
        int price;
        int stockQuantity;
    
        Product() {}
        Product(int id, string n, int p, int stock) : productID(id), name(n), price(p), stockQuantity(stock) {}
    };
    
    class ShoppingCart {
    public:
        Product products[10];
        int quantities[10];
        int totalAmount = 0;
        int count = 0;


int main(){
    cout<< "hello world";

    return 0;
}