#include <bits/stdc++.h>
using namespace std;

//a class for representing a single browser page as a DLL
class Node
{   
    public:
    string url;     // Webpage URL
    int index ;     // The index position  of the webpage
    Node* back;     // Pointer to the previous page
    Node* next;     // Pointer to the next page
};


class BrowserHistory 
{
    Node* head;        // It points to the homepage
    Node* tail;        // It points to the very last page
    Node* current;     // It points to the current page

    public:
    Node* NewNode(string url, int index) //Function for creating a new browser node
    {
        Node* page= new Node();
        page->url = url;
        page->index = index;
        page->back = nullptr;
        page->next = nullptr;

        return page; 
    }

    BrowserHistory(string homepage)  //Constructor: initializes the home page
    {
        Node* start= NewNode(homepage,0);
        head= start;
        tail= start;
        current= start;
    }
    
    void visit(string url) //for visiting a new page
    {
        if(current==tail) //if at the tail, just add the new page
        {
            Node* page = NewNode(url,(tail->index)+1);
            tail->next = page;
            page->back = tail;
            tail= page;
            current= page;
        }
        else     // otherwise the forward pages are discarded & add the new page
        {
            Node* page = NewNode(url,(current->index)+1);
            current->next = page;
            page->back = current;
            tail= page;
            current= page;
        }
    }
    
    string back(int steps) //for moving back the given number of steps
    {
        int i = current->index - steps;
        if(i<=0)  // if the given steps go before start
        {
            current = head;
            return current->url;  //return the first page
        }

        while(steps>0) //otherwise
        {
            current = current->back;
            steps--;
        }
        return current->url;
    }
    
    string forward(int steps) //for moving forward given number of steps
    {
        int i = current->index + steps;
        if(i>= tail->index)  //if the given steps go past end
        {
            current = tail;
            return current->url; //return the last page
        }

        while(steps>0) //otherwise
        {
            current = current->next;
            steps--;
        }
        return current->url;
    }
};


int main() {
    string homepage;
    cout<<"Enter homepage URL: ";
    getline(cin, homepage);
    BrowserHistory* browser= new BrowserHistory(homepage);
    
    int choice;
    while(true)
    {
        cout<< "\n==============================\n";
        cout << "Current Page: "<< browser->forward(0)<<endl;
        cout<< "==============================\n";
        cout << "1. Visit new site\n";
        cout<< "2. Go back\n";
        cout<< "3. Go forward\n";
        cout << "4. Exit\n";
        cout<< "Enter your choice: ";
        cin>> choice;

        if(choice==1) 
        {
            cin.ignore(); //for clearing newline from input buffer b4 using getline
            string url;
            cout << "Enter URL to visit: ";
            getline(cin, url);
            browser->visit(url);
            cout << "Visited: " << url << endl;
        } 
        else if(choice==2) 
        {
            int steps;
            cout<< "How many steps back ? ";
            cin>>steps;
            string url= browser->back(steps);
            cout << "Moved back to: " << url << endl;
        } 
        else if(choice==3) 
        {
            int steps;
            cout<< "How many steps forward ? ";
            cin>> steps;
            string url = browser->forward(steps);
            cout<< "Moved forward to: "<<url<<endl;
        } 
        else if(choice==4) 
        {
            cout<< "Exiting.\n";
            break;
        } 
        else 
        {
            cout<< "Invalid choice. Please try again.\n";
        }
    }
    delete browser; //Clean up dynamically allocated memory
    return 0;
}