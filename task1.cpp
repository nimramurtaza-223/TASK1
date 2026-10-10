#include <iostream>
#include <string>
using namespace std;

struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

class PriorityQueue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:
    PriorityQueue()
    {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    void Add(BookRequestNode* request)
    {
        request->next = nullptr;

        if (front == nullptr)
        {
            front = request;
            rear = request;
        }
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        else
        {
            BookRequestNode* current = front;

            while (current->next != nullptr &&
                   current->next->priority <= request->priority)
            {
                current = current->next;
            }

            request->next = current->next;
            current->next = request;

            if (request->next == nullptr)
                rear = request;
        }

        count++;
    }

    BookRequestNode* Remove()
    {
        if (front == nullptr)
            return nullptr;

        BookRequestNode* request = front;
        front = front->next;

        if (front == nullptr)
            rear = nullptr;

        request->next = nullptr;
        count--;

        return request;
    }

    bool IsEmpty()
    {
        return front == nullptr;
    }

    bool IsNotEmpty()
    {
        return front != nullptr;
    }

    void PrintQueue()
    {
        BookRequestNode* current = front;

        while (current != nullptr)
        {
            cout << "Student ID: " << current->studentID << endl;
            cout << "Student Name: " << current->studentName << endl;
            cout << "Book ID: " << current->bookID << endl;
            cout << "Book Title: " << current->bookTitle << endl;
            cout << "Priority: " << current->priority << endl;
            cout << "------------------------" << endl;

            current = current->next;
        }
    }

    ~PriorityQueue()
    {
        while (front != nullptr)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = nullptr;
    }
};

int main()
{
    PriorityQueue requests;
    int choice;

    do
    {
        cout << "\nLibrary Book Request System\n";
        cout << "1. Add Book Request\n";
        cout << "2. Process Highest Priority Request\n";
        cout << "3. Display All Requests\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            BookRequestNode* request = new BookRequestNode;

            cout << "Enter Student ID: ";
            cin >> request->studentID;

            cin.ignore(10000, '\n');

            cout << "Enter Student Name: ";
            getline(cin, request->studentName);

            cout << "Enter Book ID: ";
            cin >> request->bookID;

            cin.ignore(10000, '\n');

            cout << "Enter Book Title: ";
            getline(cin, request->bookTitle);

            cout << "Enter Priority (1-3): ";
            cin >> request->priority;

            if (request->priority < 1 || request->priority > 3)
            {
                cout << "Invalid priority.\n";
                delete request;
            }
            else
            {
                requests.Add(request);
                cout << "Request added successfully.\n";
            }
        }
        else if (choice == 2)
        {
            BookRequestNode* request = requests.Remove();

            if (request == nullptr)
            {
                cout << "Queue is empty.\n";
            }
            else
            {
                cout << "Processing Request\n";
                cout << "Student: " << request->studentName << endl;
                cout << "Book: " << request->bookTitle << endl;
                cout << "Priority: " << request->priority << endl;

                delete request;
            }
        }
        else if (choice == 3)
        {
            if (requests.IsEmpty())
                cout << "No pending requests.\n";
            else
                requests.PrintQueue();
        }
        else if (choice == 4)
        {
            if (requests.IsEmpty())
                cout << "Queue is empty.\n";
            else
                cout << "Queue is not empty.\n";
        }
        else if (choice == 5)
        {
            cout << "Program ended.\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}