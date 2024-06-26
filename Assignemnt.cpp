#include <iostream>
#include <string>
#include <chrono>
#pragma warning(disable : 4996)
using namespace std;

class Post {
public:
    int autonum;
    string text;
    chrono::system_clock::time_point currentTime; // Define currentTime here
    int hours; // Store hours as an integer
    int minutes; // Store minutes as an integer
    int seconds; // Store seconds as an integer
    Post* next;

    Post(string txt) : text(txt) {
        autonum = rand() % 9000 + 1000;
        next = nullptr;
        currentTime = chrono::system_clock::now(); // Initialize currentTime here

        // Convert the time point to a time_t (C-style timestamp)
        std::time_t currentTime_t = std::chrono::system_clock::to_time_t(currentTime);

        // Convert the time_t to a more human-readable format
        struct std::tm* timeinfo = std::localtime(&currentTime_t);

        // Extract hours, minutes, and seconds and store them as integers
        hours = timeinfo->tm_hour;
        minutes = timeinfo->tm_min;
        seconds = timeinfo->tm_sec;
    }

};

class Feed {
public:
    Post* head;
    Feed()
    {
        head = nullptr;
    }

    void add_New_post(string txt)
    {
        //Add the post at start as in social media
        Post* newPost = new Post(txt);
        if (newPost == nullptr)
        {
            cout << "Post not uploaded" << endl;
        }
        else
        {
            newPost->next = head;
            head = newPost;
        }
    }

    void sort_By_time()
    {
        if (head == nullptr || head->next == nullptr) {
            // The list is empty or has only one element, it's already sorted
            return;
        }

        bool swapped;
        Post* lastNode = nullptr;
        Post* maxPrev = nullptr;
        do {
            swapped = false;
            Post* current = head;
            Post* prev = nullptr;
            Post* maxNode = head;

            while (current->next != lastNode) {
                if (current->seconds > maxNode->seconds) {
                    maxNode = current;
                    maxPrev = prev;
                }
                prev = current;
                current = current->next;
            }

            // Move the node with the maximum seconds to the front
            if (maxPrev != nullptr) {
                maxPrev->next = maxNode->next;
                maxNode->next = head;
                head = maxNode;
            }

            lastNode = head; // Mark the last sorted element
        } while (swapped);
    }

    void print_recursive(Post* current)
    {
        if (current == nullptr)
        {
            cout << "nullptr" << endl;
            return;
        }



        // Recursively call the function with the next node
        print_recursive(current->next);

        cout << current->hours << ":" << current->minutes << ":" << current->seconds << " -> ";
        cout << current->autonum << " -> ";
        cout << current->text << " -> ";
        cout << endl;
    }

    void print_forward()
    {
        print_recursive(head);
    }


    void edit_Post(string newcap)
    {
        int edit;
        Post* current = head;
        while (current != nullptr) {
            cout << current->autonum << " -> ";
            current = current->next;
        }
        cout << "nullptr";
        cout << endl;
        cout << "Enter the Number of post you want to edit" << endl;
        cin >> edit;
        current = head;
        while (current != nullptr)
        {
            if (current->autonum == edit)
            {
                current->text = newcap;
                current->currentTime = chrono::system_clock::now();
                time_t currentTime_t = std::chrono::system_clock::to_time_t(current->currentTime);
                struct tm* timeinfo = std::localtime(&currentTime_t);
                current->hours = timeinfo->tm_hour;
                current->minutes = timeinfo->tm_min;
                current->seconds = timeinfo->tm_sec;
                current = current->next;
            }
            current = current->next;
        }
        sort_By_time();
        print_reverse();
    }


    int count_Post()
    {
        if (head == nullptr)
            return 0;
        else if (head->next == nullptr)
            return 1;
        else
        {
            int count = 0;
            Post* current = head;
            while (current->next != nullptr)
            {
                count++;
                current = current->next;
            }
            return count;
        }
    }


    void delete_Post()
    {
        int delpost;
        cout << "Enter the number of post you want to delete" << endl;
        cin >> delpost;
        if (delpost<1 || delpost>count_Post())
            cout << "Invalid Post number" << endl;
        else
        {
            Post* last = head;
            Post* secondlast = head;
            for (int i = 1; i < delpost; i++)
            {
                secondlast = last;
                last = last->next;
            }
            Post* temp = last;
            secondlast->next = last->next;
            delete temp;
        }
    }

    void print_reverse()
    {
        Post* current = head;
        while (current != nullptr) {
            cout << current->hours << ":" << current->minutes << ":" << current->seconds << " -> ";
            cout << current->autonum << " -> ";
            cout << current->text << " -> ";
            cout << endl;
            current = current->next;
        }
        cout << "nullptr" << endl;
    }





    void search_post(const string& delstr)
    {
        Post* current = head;
     //   bool foundFlag = false; // Flag to indicate if the substring is found

        while (current != nullptr)
        {
            size_t found = current->text.find(delstr);
            if (found != string::npos)
            {
    //           foundFlag = true; // Set flag to true if substring found

                if (current == head)
                {
                    head = current->next;
                    delete current;
                    current = head;
                }
                else
                {
                    Post* last = head;
                    while (last->next != current)
                    {
                        last = last->next;
                    }
                    last->next = current->next;
                    delete current;
                    current = last->next;
                }
            }
            else
            {
                current = current->next;
            }
        }

         
        //if (foundFlag)
       // {
         //   cout << "Substring '" << delstr << "' found in at least one post." << endl;
        //}
       // else
        //{
          //  cout << "Substring '" << delstr << "' not found in any post." << endl;
        //}
    }


};
int main()
{
    Feed post;
    int choice = -1;
    while (choice != 0)
    {
        cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
        cout << "X  Social Media Account Menu:  X" << endl;
        cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;
        cout << "1. Count Nodes" << endl;
        cout << "2. Add Post" << endl;
        cout << "3. Delete Post" << endl;
        cout << "4. Edit Post" << endl;
        cout << "5. search Post by text" << endl;
        cout << "6. Display List in chronological order" << endl;
        cout << "7. Display List in reverse chronological order" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 1)
            cout << "Number of posts are " << post.count_Post() << endl;
        else if (choice == 2)
        {
            string text;
            cout << "Enter the text of the post" << endl;
            cin >> text;
            post.add_New_post(text);
        }   
        else if (choice == 3)
            post.delete_Post();
        else if (choice == 4)
        {
            string edittext;
            cout << "Enter the text your want to save " << endl;
            cin >> edittext;
            post.edit_Post(edittext);
        }
        else if (choice == 5)
        {
            string searchtext;
            cout << "Enter the text your want to save " << endl;
            cin >> searchtext;
            post.search_post(searchtext);
        }
        else if (choice == 6)
            post.print_reverse();
        else if (choice == 7)
            post.print_forward();
        else if (choice == 0)
            cout << "Exiting..." << endl;
        else
            cout << "Invalid choice! Please try again." << endl;
    }
}
 