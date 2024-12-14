#include "functions.h" // directive to include the Node and Browser class definitions and function declarations from our header file. 
using namespace std;  

// Browser constructor referencing the Browser class from the header file.  head, tail and current are assigned nullptr special constants. using a nullptr vs null for many reasons; dangling pointer prevention, avoids ambiguity in overloads and provides better type checking because we are stating it is a type-safe vs NULL = 0 ... 
 
Browser::Browser() : head(nullptr), tail(nullptr), current(nullptr)
{}

// Destructor to clear dynamic memory
Browser::~Browser()
{
    while (head) // while loop, while head is not nullptr this loop will keep iterating through the list deallocating memory deleting each node until nullptr.
        // concise version of while ( head != nullptr). The compiler knows head is a pointer. When head is evaluated in a boolean context, the system performs an implicit conversion.. 
    {
        head = head->next; // head is reassigned to point to the next node in the list until nullptr is reached  and the previous node is released if no other references exist.  
    }
}

// Add a single website function member referencing from the Browser class.  url is the parameter we work around here being the parameter. 
void Browser::addWebsite(const string& url) 
{
    auto newNode = make_shared<Node>(url); /* auto deduced variable by the compiler based on the return type of the expression on the right-hand side.
               make_shared<Node> allocates a single contiguous block of memory which contains the control block and node object.
                        make_shared calls the Node constructor and wraps the object in a shared_ptr. Then initializes the Node object with the given url 
                        argument.  The entire statement initializes newNode with a memory-managed instance of Node */
        if (!head) // if statement to check if head is null(that the list is empty)/ false..
        {
        head = tail = newNode; // Both head and tail are assignend to newNode since the list is empty. 
       
        }
        else // else statement if  the if statement is not-null.
        {
        tail->next = newNode; // here we establish a forward link where newNode is assigned to next node. 
        newNode->prev = tail; // tail is assigned to the previous pointer of the newNode creating the backward link
        tail = newNode; // newNode pointer now points to tail node.
        }
        current = tail; // updates current pointer to tail.  
        cout << "Website added: " << url << endl; // string output message to user with the url that the user input.
}

// Overloaded function to add multiple websites with a vector string referance assigning the parameter named urls as the container for user website inputs. Using a vector container helps us pass a batch of websites in one sitting rather than one by one manually. We avoid repetative calls using this simplified process of adding multiple nodes by delegating to the single url add function. 
void Browser::addWebsite(const vector<string>& urls)
{
    for (const auto& url : urls)  /* Range-based for loop that iterates through each element in the urls vector. url contstant string reference connecting 
       url to the urls vector with the range seaparator. On each iteration the current URL is stored in url... */

    {
        this->addWebsite(url); // Explicitly calls the member function from above and adds the url to the doubly linked list.
    }
    cout << "Batch of websites added." << endl; // output print to let the user know the add was successful. 
}

// Delete a website function.. assigning a constant string reference parameter named url
void Browser::deleteWebsite(const string& url) 
{
    auto temp = head; // temp is a deduced shared pointer created with auto and it is temporarily shares ownership of the head node. It is used as a helper pointer for traversing and manipulating the nodes in the list.
    while (temp) // while loop will continue under the condition that temp is not null/ true. 
    {
        if (temp->url == url) // if statement checks if the url stored in the node that temp points to matches the url passed as the argument to the function. If a match is found it is prepared for deletion in the steps that follow.
        {
            if (temp->prev) temp->prev->next = temp->next; // if condition, forward skipping; checking if temp has a previous node. If true, then the next pointer of the previous node is updated so that next points to the node after temp removing it from the list. 
            if (temp->next) temp->next->prev = temp->prev; // if condition, backward skipping; if temp has a node next of it then temp points to the previous pointer of the node and it is updated to point to the previous node before temp essentially removing temp node from the doubly linked list.
            if (temp == head) head = temp->next; // if temp is the current head node then heads pointer is updated so that it can access the next node after temp
            if (temp == tail) tail = temp->prev; // if temp is the current tail then the pointer of the tail gets updated so that it can access the node before temp
            cout << "Website deleted: " << url << endl; // output indicating website deleted and the name of the url.
            return; // exit the function and return to the caller.  the menu in this case...
        }

        temp = temp->next; // temp is updated to the next node if the url argument doesn't match and will continue to iterate until the list is over.
    }
    cout << "Website not found: " << url << endl; // output if nothing matches along with the search the user typed in.
}

// Display all websites in the list function
void Browser::displayList() const // reference to a constant function to display the list of urls

{
    auto temp = head; // shared_ptr is initialized and updated as head node 
    if (!temp) // if condition testing to see if temp is nullptr/ false
    {
        cout << "The list is empty." << endl; // output to indicate an empty list.
        return; // exit function 
    }
    cout << "Website List:" << endl;  // if false then the list of websites message will print to console. 
    while (temp) // while loop with the condition of temp not null/ true the following will iterate. 
    {
        cout << temp->url << endl; // out to console with the url starting from the head, then ends here and starts a new line. 
        temp = temp->next; // temp is updated to point to the next node in the list iterating until the website list is completely displayed.
    }
}

// Navigate forward function is called 
void Browser::goForward()
{
    if (!current) // if current is nullptr/ false conditional
    {
        cout << "No websites in the list." << endl; // output indicating that, there isn't anything further in the list.  We are at nullptr.
        return; // exits the function
    }
    if (current->next) // if current has a pointer it can access.  Technically checks if the currents next pointer is not null/ true. 
    {
        current = current->next; // current now points to the next pointer of the node next is pointing to. 
        cout << "Current website: " << current->url << endl; // output of the updated current website message with the url that is stored.  
    }
    else // else statement when we have reached nullptr
    {
        cout << "You are at the end of the list." << endl; 
    }
}

// Navigate backward function with the same concept as the goForward function..
void Browser::goBackward()
{
    if (!current) 
    {
        cout << "No websites in the list." << endl;
        return;
    }
    if (current->prev)
    {
        current = current->prev;
        cout << "Current website: " << current->url << endl;
    }
    else
    {
        cout << "You are at the beginning of the list." << endl;
    }
}

// Find a specific website function (exact match)
void Browser::findWebsite(const string& url) const
{
    auto temp = head; // Temporary smart pointer is initialized to head. So we can start at the top and traverse down the linked list to find the requested search
    while (temp) // While loop continues as long as the temp pointer is not null/ true
    {
        if (temp->url == url) // if statement with a condition if url that the pointer is pointing to matches the url requested by the user then, the following block executes.
        {
            cout << "Website found: " << url << endl; // print message along with the url that the searched url was found...
            return;
        }
        temp = temp->next; // temp will point to the next nodes pointer iterating through the linked list. 
    }
    cout << "Website not found: " << url << endl; // not found output message..
}

// Overloaded to find a specific website (partial match) (2 new parameters here: string and boolean)
void Browser::findWebsite(const string& keyword, bool partialMatch) const 
{
    if (!partialMatch) // if the partial match is false and then, the findWebsite exact match function is called passing keyword argument 
    {
        findWebsite(keyword); // Call the exact match version function which preceeds this function. 
        return;
    }

    auto temp = head;  //here we declare the pointer to head deduced by temp.  Sets pointer to head so that it can traverse the linked list. 
    bool found = false; // here bool found is initialized to false.  Will shift to true if a match is found.  
     
    while (temp) // While loop assigns temp pointer as not-nullptr/ true and will iterate while the if statement is false
    {
        if (temp->url.find(keyword) != string::npos) // if statement searches the nodes url for the keyword by calling .find...npos ensures safe handling when a match isn't found
        { 
            cout << "Partial match found: " << temp->url << endl; // output message if found..
            found = true; // boolean flag found is now is set to true indicating a match was found..
        }
        temp = temp->next; // temp is assigned to point to the next nodes pointer iterating the while loop until nullptr. No more logic to execute if we had matches therefore the function implicitly "returns". 
    }                    
    if (!found) // if statement with a false found condition.  
    {
        cout << "No partial matches found for keyword: " << keyword << endl; // output message with users input.  the program exits the function here naturlly as well. 
    }
}

// Menu function defined for the browser class from the header file. Here we have our user options which will run through the linked list upon request.
void Browser::menu()
{
    int choice; // variables int, string vector of strings, and a boolean declared 
    string url;
    vector<string> urls; // Container to hold multiple URLs for batch operations
    bool running = true; // running set to true

    while (running) // while loop iterates while as long as the program doesn't encounter errors or as long as the user doesn't select 9 and allow the menu to exit. 
    {
        cout << "\nBrowser Menu:\n";  // output to console for the user to read their options.
        cout << "1. Add a website\n";                
        cout << "2. Add multiple websites\n";        
        cout << "3. Delete a website\n";             
        cout << "4. Display the list\n";             
        cout << "5. Go forward\n";                   
        cout << "6. Go backward\n";                  
        cout << "7. Find a website (exact match)\n"; 
        cout << "8. Find a website (partial match)\n";
        cout << "9. Exit\n";                        
        cout << "Enter your choice: ";

        if (!(cin >> choice)) // if statement with a condition checking input validation 
        {
            cin.clear(); // Resets error flags so that the programm doesn't jam up
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // this skips characters in the input buffer to prevent infinite loops. It removes letters after the number if the user were to do something like 4abc...
            cout << "Invalid input. Please enter a number between 1 and 9.\n"; // message to user of the error
            continue; //  continues the program to the beginning of the loop 
        }

         cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer for valid input for robuts input handling..

        switch (choice) // Switch statement named choice with 9 cases for the program to execute depending on the users selection
        {
        case 1: // Case for adding a single website
            cout << "Enter website URL to add: ";
            getline(cin, url); //  input for the URL
            addWebsite(url);   // Calls the original addWebsite function
            break; // exits the current case and returns control to the top of the loop.. otherwise the program would fall through and go onto the next function executing all subsequent cases...

        case 2: // Case for adding multiple websites
            cout << "Enter multiple URLs (type 'done' to finish): ";
            while (true) // loop to continue while true however we have an exit condition available for the user when finished.
            {
                getline(cin, url); // user input
                if (url == "done") break; // Stops loop if the user inputs "done"
                urls.push_back(url);     // Add each URL to the vector
            }
            addWebsite(urls); // Calls the overloaded addWebsite function
            break;

        case 3: // Case for deleting a website
            cout << "Enter website URL to delete: ";
            getline(cin, url); // Get input for the URL to delete
            deleteWebsite(url); // Calls the deleteWebsite function
            break;

        case 4: // Case for displaying the list of websites
            displayList(); // Calls the displayList function
            break;

        case 5: // Case for navigating forward
            goForward(); // Calls the goForward function
            break;

        case 6: // Case for navigating backward
            goBackward(); // Calls the goBackward function
            break;

        case 7: // Case for finding a website (exact match)
            cout << "Enter website URL to find (exact match): ";
            getline(cin, url); // Get input for the exact match URL
            findWebsite(url);  // Calls the findWebsite (exact match) function
            break;

        case 8: // Case for finding a website (partial match)
            cout << "Enter keyword to search for (partial match): ";
            getline(cin, url); // Get input for the partial match keyword
            findWebsite(url, true); // Calls the overloaded findWebsite function for partial match
            break;

        case 9: // Case to exit the program
            cout << "Exiting the browser.\n";
            running = false; // Stops the loop
            break;

        default: // Default case for invalid input by the user..
            cout << "Invalid choice. Enter a number between 1 and 9.\n";
        }
    }
}

