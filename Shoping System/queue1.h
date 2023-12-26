
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <cstdlib>
#include <stdexcept>
#include<fstream>
using namespace std;

// Structure of Node.
struct Node
{
    string cname;

    Node* link;
};

Node* front = NULL;
Node* rear = NULL;

//Function to check if queue is empty or not
bool isempty()
{
    if (front == NULL && rear == NULL)
        return true;
    else
        return false;
}

//function to enter elements in queue
void enqueue(string name)
{
    Node* ptr = new Node();
    ptr->cname = name;
    ptr->link = NULL;

    //If inserting the first element/node
    if (front == NULL)
    {
        front = ptr;
        rear = ptr;
    }
    else
    {
        rear->link = ptr;
        rear = ptr;
    }

    // Open the file in append mode
    ofstream file("customers.txt", ios::app);

    // Write the customer name to the file
    file << name << "\n";

    // Close the file
    file.close();
}

//function to delete/remove element from queue
void dequeue()
{
    if (isempty())
        cout << "Queue is empty\n";
    else
    {
        //only one element/node in queue.
        if (front == rear)
        {
            free(front);
            front = rear = NULL;
        }
        else
        {
            Node* ptr = front;
            front = front->link;
            free(ptr);
        }

        // Open the file in read mode
        ifstream fileIn("customers.txt");

        // Check if the file is open
        if (!fileIn.is_open()) {
            cout << "Unable to open file";
            return;
        }

        // Vector to hold all customer names
        vector<string> customers;

        string line;
        // Skip the first line
        getline(fileIn, line);
        while (getline(fileIn, line)) {
            // Read the customer name from the file
            customers.push_back(line);
        }

        // Close the file
        fileIn.close();

        // Open the file in write mode
        ofstream fileOut("customers.txt");

        // Write all the customer names back to the file
        for (const string& customer : customers) {
            fileOut << customer << "\n";
        }

        // Close the file
        fileOut.close();
    }
}

//function to show the element at front
void showfront()
{
    if (isempty())
        cout << "Queue is empty\n";
    else
        cout << "element at front is:" << front->cname << "\n";
}

//function to display queue
void displayQueue()
{
    // Open the file in read mode
    ifstream file("customers.txt");

    // Check if the file is open
    if (!file.is_open()) {
        cout << "Unable to open file";
        return;
    }

    cout << "Customers:\n";

    string line;
    while (getline(file, line)) {
        // Read the customer name from the file
        cout << line << "\n";
    }

    // Close the file
    file.close();
}

