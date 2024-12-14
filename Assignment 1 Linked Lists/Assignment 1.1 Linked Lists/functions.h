#pragma once // pragmatic information directive as an inclusion guard (to prevent multiple inclusions), which is used for compiler-specific instructions. It prevents multiple inclusions of a header file.
#include <iostream> 
#include <string>
#include <memory> // pointer directive.. used for our smart pointers to share ownership of the same object via shared_ptr.
#include <vector> 
#include <limits> // for our input buffer 

using namespace std; // This allows us to omit the std:: prefix for standard library components.

class Node // class created to represent a node in a doubly linked list
{
public: // the class encapsulation for these members is public and accessible from outside of the class.
    string url; // string variable named url where website addresses will be stored.
    shared_ptr<Node> next; // smart pointer declared named next that will manage the memory for a Node object and link to the next node.
    shared_ptr<Node> prev; // smart pointer declared named prev that will manage the previous node in the doubly linked list.

    // Node constructor with a constant string referance named website with an initializer list to initialize the URL and set the next and previous pointers to nullptr.
    Node(const string& website) : url(website), next(nullptr), prev(nullptr)
    {}
};

class Browser // Represents the browser functionality using a doubly linked list
{
private: // the encapsulation for these members is private and accessible only within the Browser class.
    shared_ptr<Node> head; // points to the first node in the doubly linked list.
    shared_ptr<Node> tail; // points to the last node in the doubly linked list.
    shared_ptr<Node> current; // points to the current node in the list for navigation.

public:
    Browser(); // Default constructor for the Browser class.
    ~Browser(); // Destructor to clear memory when the Browser object is destroyed.

    void addWebsite(const string& url); // Adds a single website to the list.
    void addWebsite(const vector<string>& urls); // Overloaded method to add multiple websites to the list. 
    void deleteWebsite(const string& url); // Deletes a specific website from the list by its URL.
    void displayList() const; // Displays all the websites currently in the list.
    void goForward(); // Moves the pointer to the next node in the list.
    void goBackward(); // Moves the pointer to the previous node in the list.
    void findWebsite(const string& url) const; // Searches for a website in the list by exact match.
    void findWebsite(const string& keyword, bool partialMatch) const; // Overloaded method to search for a website by partial match. 
    void menu(); // Displays a menu for interacting with the Browser functionality.
};
