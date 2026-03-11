#include <iostream>
#include <string>
using namespace std;

// Singly-Linked-List Struct
struct Node {
    string song_title;
    Node* next;
};

// Function Declarations 
void menuText();
void addSong(Node*& head, string title);
void listSongs(Node* head);
void searchSong(Node* head, string title);

int main()
{
    Node* head = NULL;
    int choice;
    string title;

    do {
        menuText();
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            cout << "Enter song title: ";
            getline(cin, title);
            addSong(head, title);
            break;

        case 2:
            cout << "Enter song title to search: ";
            getline(cin, title);
            searchSong(head, title);
            break;

        case 3:
            listSongs(head);
            break;

        case 4:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 4);
}

// Function: Display Menu
void menuText()
{
    cout << "\n---Music Menu---\n";
    cout << "1-) Add Song\n";
    cout << "2-) Search Song\n";
    cout << "3-) List Songs\n";
    cout << "4-) Exit\n";
    cout << "Enter choice: ";
}

// Function: Add song to list
void addSong(Node*& head, string title)
{
    Node* new_song = new Node;
    new_song->song_title = title;
    new_song->next = head;
    head = new_song;
    cout << title << " add succesfully!";
}

// Function: Display song list
void listSongs(Node* head)
{
    if (head == NULL)
    {
        cout << "Playlist is a empty! \n";
        return;
    }

    Node* temp = head;
    int index = 1;

    while (temp != NULL)
    {
        cout << index << ". " << temp->song_title << endl;
        temp = temp->next;
        index++;
    }
}

// Function: Search any song in the list
void searchSong(Node* head, string title)
{
    Node* temp = head;

    while (temp != NULL)
    {
        if (temp->song_title == title)
        {
            cout << "Soung found in the List!";
            return;
        }
        temp = temp->next;
    }
}


