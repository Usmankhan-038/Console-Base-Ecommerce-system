#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include"queue1.h"
#include"animation.h"
#include"stackme.h"

using namespace std;

int search(int);
int display();
string check(int);       //   for checking quantity
int main();
void administator();
////////////////////////////////////////////////////////////////////
struct node
{
    int ID;
    string proName;
    double prePrice;
    int quantity;
    struct    node* next;
};
//////////////////////////////////////////////////////////
struct node* head = NULL;
///////////////////////////////////////////////////////////////////
class UserAuth {
private:
    string username;
    string password;
public:
    void signUp() {
        while (true)
        {
            bool flag = false;
            cout << "Enter username: ";
            cin >> username;

            if (username.length()<4)
            {
                
                for (int i = 0; i < username.length(); i++)
                {
                    if (username[i] == '$' || username[i] == '#' || username[i] == '%' || username[i] == '&' || username[i] == '(' || username[i] == ')' || username[i] == '*' || username[i] == '^' || username[i] == '!' || username[i] == '~' || username[i] == '/' || username[i] == '<' || username[i] == ';' || username[i] == '+' || username[i] == '/' || username[i] == '"' || username[i] == '\'')
                        flag = true;
                }
                cout << "Your Username should be atleast 4 character..." << endl;
                if (flag)
                    cout << "Your Username Should Not Contain Special Symbole except ( @ OR _ ) " << endl;
                system("pause");
                continue;
            }
            break;
        }
       
        
        while (true)
        {
            
            cout << "Enter password: ";
            password = getPassword1();

            if (password.length() < 5)
            {
                cout << "Your Username should be atleast 5 character..." << endl;
                system("pause");
                continue;
            }
            break;
        }
        

        // Write the credentials to a file
        ofstream file("user_credentials.txt");
        file << username << "\n";
        file << password << "\n";
        file.close();

        cout << "Sign up successful.\n";

        cout << "\n\nPlease Enter Username and Password To Login" << endl;
        login();
    }

    bool login() {
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        password = getPassword1();

        // Check the credentials against the ones in the file
        ifstream file("user_credentials.txt");
        string fileUsername, filePassword;
        if (file.is_open()) {
            getline(file, fileUsername);
            getline(file, filePassword);
        }
        file.close();

        if (username == fileUsername && password == filePassword) {
            cout << "Login successful.\n";
            return true;
        }
        else {
            cout << "Login failed.\n";
            return false;
        }
    }

    string getPassword1() {
        string password;
        char ch;
        while ((ch = _getch()) != '\r') { // '\r' is the Enter key
            if (ch == '\b') { // '\b' is the Backspace key
                if (!password.empty()) {
                    cout << "\b \b"; // erase the last '*'
                    password.pop_back();
                }
            }
            else {
                cout << '*';
                password.push_back(ch);
            }
        }
        cout << endl;
        return password;
    }
};
//////////////////////////////////////////////////////////////////
class Login {
private:
    string username;
    string password;
public:
    //  method to check admin login
    bool checkAdminLogin(string username, string password) {
        ifstream file("admin_credentials.txt");
        string fileUsername, filePassword;
        if (file.is_open()) {
            getline(file, fileUsername);
            getline(file, filePassword);
        }
        file.close();
        return (username == fileUsername && password == filePassword);
    }
    string getPassword() {
        string password;
        char ch;
        while ((ch = _getch()) != '\r') { // '\r' is the Enter key
            if (ch == '\b') { // '\b' is the Backspace key
                if (!password.empty()) {
                    cout << "\b \b"; // erase the last '*'
                    password.pop_back();
                }
            }
            else {
                cout << '*';
                password.push_back(ch);
            }
        }
        cout << endl;
        return password;
    }
};
///////////////////////////////////////////////////////////////////
class Cart {
private:
    node** items; // Pointer to the dynamic array
    int capacity; // Capacity of the dynamic array
    int size; // Current size of the dynamic array

public:
    Cart() : capacity(10), size(0) {
        items = new node * [capacity];
    }

    ~Cart() {
        delete[] items;
    }

    void addToCart(node* product) {
        if (size == capacity) {
            // The dynamic array is full, so we need to resize it
            capacity *= 2;
            node** newItems = new node * [capacity];
            for (int i = 0; i < size; i++) {
                newItems[i] = items[i];
            }
            delete[] items;
            items = newItems;
        }
        items[size] = product;
        size++;
        cout << "Product added to cart.\n";
    }

    void checkout() {
        double total = 0;
        cout << "Checking out...\n";
        for (int i = 0; i < size; i++) {
            total += items[i]->prePrice;
        }
        cout << "Total bill: " << total << "\n";
        size = 0; // Clear the cart
        cout << "Cart cleared.\n";
    }
};
////////////////////////////////////////////////////////////////////
void beg()
{
    system("cls");
    int id, quant;           //  quant    for quantity
    string name;
    double pre;            //  pre for price
    struct node* t = new node;
    struct node* p = head;
    char option;
    while (true)
    {
        system("cls");
        while (true) {
            cout << "\t\t\tEnter product ID (integer only):-";
            cin >> id;
            if (cin.fail()) {
                cin.clear();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.ignore();
                cout << "Invalid input. Please enter a valid product ID.\n";
            }
            else {
                // Check if the product already exists
                if (search(id) != -1) {
                    cout << "A product with this ID already exists. Please enter a different ID.\n";
                    continue;
                }
                break;
            }
        }
        t->ID = id;

        while (true) {
            cout << "\t\t\tEnter product Name (no numbers or special characters allowed):-";
            cin >> name;
            if (!all_of(name.begin(), name.end(), ::isalnum)) {
                cout << "Invalid input. Please enter a valid product name without numbers or special characters.\n";
            }
            else {
                break;
            }
        }
        t->proName = name;

        while (true) {
            cout << "\t\t\tEnter product price (number only):-";
            cin >> pre;
            if (cin.fail()) {
                cin.clear();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.ignore();
                cout << "Invalid input. Please enter a valid product price.\n";
            }
            else {
                break;
            }
        }
        t->prePrice = pre;

        while (true) {
            cout << "\t\t\tEnter product quantity (integer only):-";
            cin >> quant;
            if (cin.fail()) {
                cin.clear();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.ignore();
                cout << "Invalid input. Please enter a valid product quantity.\n";
            }
            else {
                break;
            }
        }

        t->quantity = quant;

        if (head == NULL)
        {
            t->next = head;
            head = t;
        }
        else
        {
            while (p->next != NULL)
            {
                p = p->next;
            }
            p->next = t;
            t->next = NULL;
        }
        system("cls");
        cout << "\n\n\t\t\t\tThis product is Inserted!\n\n\n";

        // Open the file in append mode
        ofstream file("products.txt", ios::app);

        // Write the product details to the file
        file << "Product ID: " << id << "\n";
        file << "Product Name: " << name << "\n";
        file << "Product Price: " << pre << "\n";
        file << "Product Quantity: " << quant << "\n";
        file << "------------------------\n";

        // Close the file
        file.close();

        cout << "\n\n\t\t\t\tDo you Want add another Product[Y/N]: ";
        cin >> option;

        if (option == 'Y' || option == 'y')
            continue;
        else if (option == 'N' || option == 'n')
            administator();
           
    }
    
}
///////////////////////////////////////////////////////////////////////////////////////////
int search(int id) {
    int count = 1;
    struct node* p = head;
    while (p != NULL) {
        if (p->ID == id)
            break;
        else
            count++;
        p = p->next;
    }
    if (p == NULL)
        return -1; // Return -1 if the ID does not exist in the list
    else
        return count;
}
///////////////////////////////////////////////////////////////////////
int hash(int x, int mod)
{
    return x % mod;

}

////////////////////////////////////////////////////////////////////////
void delPro()
{
    system("cls");
    display();
    int id;
    struct node* cur = head;
    struct node* pre = head;
    char option;
    while (true)
    {
        system("cls");
        cout << "\n\nEnter ID to delete that product:\n\n";
        while (true) {
            cin >> id;
            if (cin.fail()) {
                cin.clear();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.ignore();
                cout << "Invalid input. Please enter a valid product ID.\n";
            }
            else {
                break;
            }
        }
        if (head == NULL)
        {
            system("cls");
            cout << "List is empty" << endl;
            return; // Return if the list is empty
        }
        int pos = 0;
        int count = display();               //   for load no of nodes
        pos = search(id);                        //   for check weather desire node is exist or not
        if (pos <= count) {

            while (cur->ID != id) {                //  for delete middle area products
                pre = cur;
                cur = cur->next;
            }
            pre->next = cur->next;
            system("cls");
            cout << "\n<<item is deleted>>\n";
            // Open the file in read mode
            ifstream file("products.txt");

            // Check if the file is open
            if (!file.is_open()) {
                cout << "Unable to open file";
                return;
            }
            // Vector to hold all products
            vector<string> products;
            string line;
            while (getline(file, line)) {
                // Read the product details from the file
                string idStr = line.substr(12); // Get the ID
                if (stoi(idStr) == cur->ID) {
                    // This is the product we want to delete
                    // Skip the product details in the file
                    for (int i = 0; i < 4; i++) {
                        getline(file, line);
                    }
                }
                else {
                    // This is not the product we want to delete
                    // Store the product details in the vector as is
                    products.push_back(line);
                    for (int i = 0; i < 4; i++) {
                        getline(file, line);
                        products.push_back(line);
                    }
                }
            }

            // Close the file
            file.close();

            // Open the file in write mode
            ofstream fileOut("products.txt");

            // Write all the products back to the file
            for (const string& product : products) {
                fileOut << product << "\n";
            }

            // Close the file
            fileOut.close();

            // Delete the node from the linked list
            delete cur;
        }
        else {
            cout << "\n<<<Not found>>\n\n";
        }
        cout << "\n\nDo you Want Delete another Product[Y/N]: ";
        cin >> option;

        if (option == 'Y' || option == 'y')
            continue;
        else if (option == 'N' || option == 'n')
            administator();
    }
   
}
//////////////////////////////////////////////////////////////////////////////////
void modify()
{
    char option;
    while (true)
    {
        display();
        cout << "\n\nEnter ID to modify product Name and its price:\n";
        int id;
        cin >> id;
        struct node* cur = head;
        int pos = search(id); // Check if the ID exists in the list
        if (pos != -1)
        {
            while (cur->ID != id)
            {
                cur = cur->next;
            }
            cout << "\nOld ID : " << cur->ID << endl;
            cout << "\nOld Name : " << cur->proName << endl;
            cout << "\nOld Price : " << cur->prePrice << endl;
            cout << "\nOld Quantity : " << cur->quantity << endl;

            cout << endl << endl;
            int nid;
            while (true) {
                cout << "Enter new ID:";
                cin >> nid;
                if (cin.fail()) {
                    cin.clear();
                    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.ignore();
                    cout << "Invalid input. Please enter a valid product ID.\n";
                }
                else {
                    break;
                }
            }
            string pName;
            while (true) {
                cout << "Enter new Name:";
                cin >> pName;
                if (!all_of(pName.begin(), pName.end(), ::isalnum)) {
                    cout << "Invalid input. Please enter a valid product name without numbers or special characters.\n";
                }
                else {
                    break;
                }
            }
            double pre;
            while (true) {
                cout << "Enter new Price:";
                cin >> pre;
                if (cin.fail()) {
                    cin.clear();
                    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.ignore();
                    cout << "Invalid input. Please enter a valid product price.\n";
                }
                else {
                    break;
                }
            }
            int nq;
            while (true) {
                cout << "Enter new Quantity:";
                cin >> nq;
                if (cin.fail()) {
                    cin.clear();
                    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.ignore();
                    cout << "Invalid input. Please enter a valid product quantity.\n";
                }
                else {
                    break;
                }
            }
            // Open the file in read mode
            ifstream file("products.txt");

            // Check if the file is open
            if (!file.is_open()) {
                cout << "Unable to open file";
                return;
            }

            // Vector to hold all products
            vector<string> products;

            string line;
            while (getline(file, line)) {
                // Read the product details from the file
                string idStr = line.substr(12); // Get the ID
                if (stoi(idStr) == cur->ID) {
                    // This is the product we want to modify
                    // Store the new product details in the vector
                    products.push_back("Product ID: " + to_string(nid));
                    products.push_back("Product Name: " + pName);
                    products.push_back("Product Price: " + to_string(pre));
                    products.push_back("Product Quantity: " + to_string(nq));
                    products.push_back("------------------------");
                    // Skip the old product details in the file
                    for (int i = 0; i < 4; i++) {
                        getline(file, line);
                    }
                }
                else {
                    // This is not the product we want to modify
                    // Store the product details in the vector as is
                    products.push_back(line);
                    for (int i = 0; i < 4; i++) {
                        getline(file, line);
                        products.push_back(line);
                    }
                }
            }

            // Close the file
            file.close();

            // Open the file in write mode
            ofstream fileOut("products.txt");

            // Write all the products back to the file
            for (const string& product : products) {
                fileOut << product << "\n";
            }

            // Close the file
            fileOut.close();

            // Update the product details in the linked list
            cur->ID = nid;
            cur->proName = pName;
            cur->prePrice = pre;
            cur->quantity = nq;
        }
        else
        {
            cout << id << " is <<<Not found>>\n\n";
        }
        while (true)
        {
            cout << "\n\n\Do you Want Modify another Product[Y/N]: ";
            cin >> option;

            
            if (option == 'Y' || option == 'y')
                break;
            else if (option == 'N' || option == 'n')
                administator();
            else
                continue;

            
        }
        if (option == 'Y' || option == 'y')
            continue;
       
    }
}
//////////////////////////////////////////////////////////////////////////////////////
void loadProducts() {
    ifstream file("products.txt");
    string line;
    while (getline(file, line)) {
        struct node* t = new node;
        t->ID = stoi(line.substr(12));
        getline(file, line);
        t->proName = line.substr(14);
        getline(file, line);
        try {
            string priceStr = line.substr(15); // Get the price
            try {
                t->prePrice = stod(priceStr);
            }
            catch (std::invalid_argument& e) {
                cout << "Invalid argument: " << e.what() << '\n';
                continue;
            }
        }
        catch (std::invalid_argument& e) {
            cout << "Invalid argument: " << e.what() << '\n';
            continue;
        }
        getline(file, line);
        t->quantity = stoi(line.substr(18));
        getline(file, line); // Skip the separator line

        // Add the new node to the end of the linked list
        if (head == NULL) {
            t->next = NULL;
            head = t;
        }
        else {
            struct node* p = head;
            while (p->next != NULL) {
                p = p->next;
            }
            p->next = t;
            t->next = NULL;
        }
    }
    file.close();
}
int display()
{
    system("cls");
    int c = 0; // c for count products

    // Open the file
    ifstream file("products.txt");

    // Check if the file is open
    if (!file.is_open()) {
        cout << "Unable to open file";
        return 0;
    }

    cout << "Existing products are:\n";
    cout << "ID\t\tProduct Name\t\t\Price\t\tQuantity\n";
    cout << "=================================================================|\n";

    string line;
    while (getline(file, line)) {
        // Read the product details from the file
        string id = line.substr(12); // Get the ID
        getline(file, line);
        string name = line.substr(14); // Get the name
        getline(file, line);
        string price = line.substr(15); // Get the price
        getline(file, line);
        string quantity;
        if (line.length() > 18) {
            quantity = line.substr(18); // Get the quantity
        }
        else {
            cout << "Invalid line format in products.txt" << endl;
        }
        getline(file, line); // Skip the separator line

        if (!quantity.empty() && all_of(quantity.begin(), quantity.end(), ::isdigit)) {
            cout << id << "\t\t" << name << "\t\t\t" << price << "\t\t\t" << check(stoi(quantity)) << "\n"; // call check func and pass quantity
        }
        else {
            cout << "Invalid quantity format in products.txt" << endl;
        }
        c = c + 1;
    }

    file.close();

    cout << "\nTotal products in our store is : " << c << "\n\n\n";
    system("pause");
    return c;
}

////////////////////////////////////////////////////////////////////////////////////////
string check(int quant)

{              //        check function
    int a = quant;
    stringstream ss;
    ss << a;
    string quantity = ss.str();

    if (quant <= 0)
        return "out of stock!";
    else
        return quantity;
}

///////////////////////////////////////////////////////////////////////
void buy(Cart& cart)
{
    char option;
    int cho;
    while (true)
    {
        system("cls");
        cout << "[1] For Buy Product" << endl;
        cout << "[2] Logout" << endl;
        cout << "\nEnter your Choice: ";
        cin >> cho;
        switch (cho)
        {
        case 1:
        {
            fstream file("products.txt");
            system("cls");
            display();
            string products[20];
            int pay = 0, no, c = 0, price, id, i = 1;
            struct node* cur = head;

            if (head == NULL)
            {
                cout << "\n<<<<There is no items to buy>>>>\n\n";
                return;
            }
            cout << "How many products you want to buy : ";
            while (!(cin >> no) || no < 1) {
                cin.clear();
                //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cin.ignore();
                cout << "Invalid input. Please enter a positive integer.\n";
            }


            display();

            while (i <= no) {
                while (true) {
                    cout << "\n\nEnter ID of product " << i << " : ";
                    cin >> id;
                    if (cin.fail()) {
                        cin.clear();
                        //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cin.ignore();
                        cout << "Invalid input. Please enter a valid product ID.\n";
                    }
                    else {
                        break;
                    }
                }



                if (id == -1) {
                    system("cls");
                    return;
                }

                string line, des, predata;
                int data;
                int pos = search(id);
                if (pos != -1) {
                    cur = head;
                    while (cur != NULL && cur->ID != id) {
                        cur = cur->next;
                    }
                    if (cur != NULL) {
                        cur->quantity -= 1; // Decrease the quantity of the product
                    }

                    products[c] = cur->proName;
                    c++;
                    pay = pay + (cur->prePrice);
                    i++;
                    int data;
                    string line;
                    vector<string> products;
                    products.clear();
                    ifstream file("products.txt"); // Open the file in read mode
                    if (!file) {
                        cout << "Unable to open file";
                        return; // terminate with error
                    }
                    int reverse = 5;
                    while (getline(file, line)) {
                        // Read the product details from the file
                        string pre = line.substr(12); // Get the ID
                        string line1 = line; // Store the line in a variable
                        getline(file, line);
                        string name = line.substr(14); // Get the name
                        string line2 = line; // Store the line in a variable
                        getline(file, line);
                        string price = line.substr(15); // Get the price
                        string line3 = line; // Store the line in a variable
                        getline(file, line);
                        string quantity;
                        if (line.length() > 18) {
                            quantity = line.substr(18); // Get the quantity
                        }
                        else {
                            cout << "Invalid line format in products.txt" << endl;
                        }
                        string line4 = line; // Store the line in a variable

                        // Skip the separator line
                        data = stoi(pre);
                        int nq = stoi(quantity);
                        nq -= 1;

                        if (data == id)
                        {
                            // This is the product we want to modify
                            // Store the new product details in the vector
                            products.push_back("Product ID: " + to_string(data));
                            products.push_back("Product Name: " + name);
                            products.push_back("Product Price: " + price);
                            products.push_back("Product Quantity: " + to_string(nq));
                            products.push_back("------------------------");
                            getline(file, line);
                            // Skip the old product details in the file
                            /*file.seekg(reverse - 5);
                            file.clear();
                            for (int i = 0; i < 5; i++) {
                                getline(file, line);
                                reverse++;
                            }*/
                        }
                        else {
                            // This is not the product we want to modify
                            // Store the product details in the vector as is
                            products.push_back(line1);
                            products.push_back(line2);
                            products.push_back(line3);
                            products.push_back(line4);
                            products.push_back("------------------------");
                            getline(file, line);
                            reverse = reverse + 5;
                        }

                        c = c + 1;
                    }

                    file.close(); // Close the file after reading

                    ofstream file_out("products.txt"); // Open the file in write mode
                    for (int i = 0; i < products.size(); i++)
                        file_out << products[i] << "\n"; // Write the product details back to the file
                    file_out.close(); // Close the file after writing

                    // Add the product to the cart
                    cart.addToCart(cur);
                }
                else
                {
                    cout << "\n<<<<<<<<<This item is not available in our store at this time>>>>\n\n";
                    continue;
                }
            }

            string customer;
            while (true) {
                cout << "Enter your name: ";
                cin >> customer;
                if (!all_of(customer.begin(), customer.end(), ::isalpha)) {
                    cout << "Invalid input. Please enter a valid name without numbers or special characters.\n";
                }
                else {
                    break;
                }
            }
            enqueue(customer);

            system("cls");
            cout << "\n\n\n\n\t\t\tYou have bought : ";
            for (int i = 0; i < no; i++)
            {
                cout << products[i] << ",";
            }
            price = pay * (0.90);
            cout << "\n\nOriginal price : " << pay;
            cout << "\n with 10% discount: " << price << "\nThank you! for the shopping\n\n";

            // Checkout and calculate the total bill
            cart.checkout();

            cout << "\n\nDo you Want Buy another Product[Y/N]: ";
            cin >> option;

            if (option == 'Y' || option == 'y')
                continue;
            else if (option == 'N' || option == 'n')
                administator();
        }
        break;
        case 2:
            main();
        }
        }
        
    
}
/////////////////////////////////////////////////////////////////////////
void hashAndShowProducts() {
    // Hash the products
    
    fstream file("products.txt");

    // Check if the file is open
    if (!file.is_open()) {
        cout << "Unable to open file";
        return;
    }

    // Vector to hold all hashed products
    vector<string> hashedProducts;

    string line;
    while (getline(file, line)) {
        // Read the product details from the file
        string idStr = line.substr(12); // Get the ID
        int id = stoi(idStr);
        // Apply the hash function to the ID
        int hashedId = ::hash(id, 100); // Assuming 100 as the modulus value
        // Store the hashed ID in the vector
        hashedProducts.push_back("Product ID: " + to_string(hashedId));
        // Skip the rest of the product details in the file
        for (int i = 0; i < 4; i++) {
            getline(file, line);
        }
    }

    // Close the file
    file.close();

    // Open the file in write mode
    ofstream fileOut("hashed_products.txt");

    // Write all the hashed products back to the file
    for (const string& hashedProduct : hashedProducts) {
        fileOut << hashedProduct << "\n";
    }

    // Close the file
    fileOut.close();

    cout << "Hashed product IDs have been written to hashed_products.txt\n";

    // Show the hashed products
    ifstream fileIn("hashed_products.txt");

    // Check if the file is open
    if (!fileIn.is_open()) {
        cout << "Unable to open file";
        return;
    }

    cout << "Hashed product IDs:\n";

    while (getline(fileIn, line)) {
        // Read the hashed product ID from the file
        cout << line << "\n";
    }

    // Close the file
    fileIn.close();
}
void administator();
void adminLogin()
{
    Login admin;
    system("cls");
    
    string username, password;
    int loginAttempts = 0;
    bool loginSuccess = false;
    do {
        system("pause");
        system("cls");
        cout << "\n<< Administrator Login >>" << endl;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        password = admin.getPassword();
        if (admin.checkAdminLogin(username, password)) {
            cout << "Access granted." << endl;
            loginSuccess = true;
            administator();
            break;
        }
        else {
            cout << "Access denied." << endl;
            loginAttempts++;
            if (loginAttempts >= 3) {
                cout << "Maximum login attempts reached." << endl;
                break;
            }
        }
    } while (true);
    if (!loginSuccess) {
        cout << "Exiting due to failed login attempts." << endl;
        system("pause");
        return;
    }
}
/////////////////////////////////////////////////////////////////////////////////////////
void administator()
{
    int ch;
    do {
       
        system("cls");
        cout << "\t\t============================================" << endl;
        cout << "\t\t|          Administator Portal              |" << endl;
        cout << "\t\t============================================" << endl;

        cout << "\t\t     Enter 1 for ADD a new product    " << endl;
        cout << "\t\t     Enter 2 to display all products   " << endl;
        cout << "\t\t     Enter 3 for MODIFY Existing product" << endl;
        cout << "\t\t     Enter 4 for Delete a particular product item" << endl;
        cout << "\t\t     Enter 5 for Customers List " << endl;
        cout << "\t\t     Enter 6 for Dequeue customer" << endl;
        cout << "\t\t     Enter 7 for Generate hash" << endl;
        cout << "\t\t     Enter 8 for showing Hash Products" << endl;
        cout << "\t\t     Enter 0 for Main Menu" << endl;
        cout << "\nEnter Your choice >>>";
        cin >> ch;

        if (cin.fail() || ch < 0 || ch > 8) {
            cin.clear();
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.ignore();
            cout << "Invalid input. Please enter a number between 0 and 8.\n";
            continue;
        }

        switch (ch) {
        case 0:
            system("cls");
            main();
        case 1:
            beg();
            break;
        case 2:
            system("cls");
            display();
            break;
        case 3:
            while (true) {
                modify();
                if (cin.fail()) {
                    cin.clear();
                    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.ignore();
                    cout << "Invalid input. Please enter a valid product ID.\n";
                }
                else {
                    break;
                }
            }
            break;
        case 4:
            delPro();
            cout << "\n-------Product is Deleted-------\n";
            break;
        case 5:
            system("cls");
            cout << "|============CUSTOMERS NAMES LIST==============|" << endl;
            displayQueue();
            cout << "\n\n";
            system("pause");
            break;
        case 6:
            system("cls");
            cout << "|============CUSTOMERS NAMES LIST==============|" << endl;
            dequeue();
            displayQueue();
            cout << "\n\n";
            system("pause");

            break;
        case 7:
            int x, n;
            while (true) {
                cout << "Enter element to generate hash = ";
                cin >> x;
                if (cin.fail()) {
                    cin.clear();
                    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.ignore();
                    cout << "Invalid input. Please enter a valid integer.\n";
                }
                else {
                    break;
                } 
            }
            while (true) {
                cout << "Of total list number : ";
                cin >> n;
                if (cin.fail()) {
                    cin.clear();
                    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin.ignore();
                    cout << "Invalid input. Please enter a valid integer.\n";
                }
                else {
                    break;
                }
            }
            cout << "Hash of " << x << " is = " << ::hash(x, n);
            cout << "\n\n";
            system("pause");
            break;
        case 8:
            hashAndShowProducts();
            system("pause");
            break;
        default: system("cls");
        }
    } while (true);
}
//////////////////////////////////////////////
int main()
{
    system("cls");
    loadProducts();
    Cart cart;
    for (int i = 0; i <= 51; i++)
    {

        push(i);
    }
    system("color F1");     //  for console color
    gotoxy(17, 5);
    cout << "--------------------------------------------------" << endl;
    gotoxy(17, 7);
    cout << "||            Shopping Club System                ||" << endl;
    gotoxy(17, 9);
    cout << "--------------------------------------------------" << endl;
    gotoxy(17, 11);
    cout << "|Subject Teacher ->> Sir Amir <<-- |\n" << endl;
    gotoxy(17, 13);
    cout << ">>>----Project Implemented By-----<<<" << endl;
    gotoxy(22, 15);
    cout << "Abdur Rafay" << endl;
    gotoxy(22, 16);
    system("pause");
    system("cls");
    system("color Fc");
    int ch;
    do {
        cout << "\n\t\t|--------<Main Menu>-----------|";
        cout << "\n\n";
        cout << "\t\t 1)Administator of Market\n";
        cout << "\t\t 2)Customer               \n";
        cout << "\t\t 3)Exit                    \n";

        cout << "\nEnter Your choice >>>";
        cin >> ch;

        if (cin.fail() || ch < 1 || ch > 3) {
            cin.clear();
            //cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.ignore();
            cout << "Invalid input. Please enter a number between 1 and 3.\n";
        }
        else {
            break;
        }
    } while (true);

    switch (ch) {
    case 1:
    {
       
       adminLogin();
    }
        
        break;
    case 2:
    {
        UserAuth user;
        int userChoice;
        system("cls");
        while (true)
        {
            cout << "1) Log in\n";
            cout << "2) Sign up\n";
            cout << "Enter your choice: ";
            cin >> userChoice;
            if (userChoice != 1 && userChoice != 2)
            {
                cout << "Invalid Choice";
                system("pause");
                continue;
            }
            break;
            
        }
        if (userChoice == 1) {
            if (user.login()) {
                cout << endl << endl;
                bpop();
                system("pause");
                buy(cart);
            }
        }
        else if (userChoice == 2) {
            user.signUp();
            // After sign up, show the shopping trolley
            cout << endl << endl;
            bpop();
            system("pause");
            buy(cart);
        }
 
        break;
    }
    case 3:
        cout << "\n\n\t\t\t\t\tThank You\t\t\t\t";
        break;
    }
    return 0;
}






