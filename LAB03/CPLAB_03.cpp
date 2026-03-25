#include <iostream>
using namespace std;

struct Page {
	string url;
	string title;
	int accesTime[3]; // {hour, minute, second}

	Page* next;
	Page* prev;
};

// Global Pointers
Page* head = nullptr;
Page* current = nullptr;

// Function: Visit
void visit(string url, string title, int h, int m, int s)
{
	Page* new_page = new Page(url, title, { h, m, s });

	// If history empty
	if (!head) {
		head = new_page;
		current = new_page;
		return;
	}

	// If we are not at the end, we must delete forward history
	Page* temp = current->next;
	while (temp) { // Stop when temp == null
		Page* to_delete = temp;
		temp = temp->next;
		delete to_delete;
	}

	current->next = new_page;
	new_page->prev = current;
	current = new_page;
}

// Function: Back
void goBack()
{
	if (current && current->prev) {
		current = current->prev;
	}
	else {
		cout << "No previous page!!\n"; 
	}
}

// Function: Forward
void goForward()
{
	if (current && current->next) {
		current = current->next;
	}
	else {
		cout << "No forward page!!|n";
	}
}

// Function: Delete Current
void deleteCurrent()
{
	if (!current) return;

	Page* temp = current;

	// Case 1: Only One Node in the History
	if (!current->prev && !current->next) {
		head = nullptr;
		current = nullptr;
	}

	// Case 2: Head Node
	else if (!current->prev) {
		head = current->next;
		head->prev = nullptr;
		current = head;
	}

	// Case 3: Tail Node
	else if (!current->next) {
		current = current->prev;
		current->next = nullptr;
	}

	// Case 4: Middle Node
	else {
		current->prev->next = current->next;
		current->next->prev = current->prev;
		current = current->next;
	}

	delete temp;
}

// Function: Display History
void displayHistory()
{
	Page* temp = head;

	cout << "\n------- Browser History -------\n";
	while (temp) {
		if (temp == current) {
			cout << "You are on this site!"; // update!!!!
		}
		else {
			cout << "    ";
		}

		cout << temp->title << " (" << temp->url << ") - ";

		// Print Access Time Using Loop
		for (int i = 0; i < 3; i++) {
			cout << temp->accesTime[i];
			if (i < 2) cout << ":";
		}

		cout << endl;
		temp = temp->next;
	}

	cout << "--------------------------\n";
}

// Function: Clean Memory
void cleanMemory() {
	Page* temp = head;

	while (temp) {
		Page* next = temp->next;
		delete temp;
		temp = next;
	}

	head = nullptr;
	current = nullptr;
}

int main()
{
	int choice;

	while (true) {
		cout << "\n------- MENU -------\n";
		cout << "1. Visit a Page\n";
		cout << "2. Back\n";
		cout << "3. Forward\n";
		cout << "4. Delete Current Page\n";
		cout << "5. Show History\n";
		cout << "6. Exit\n";
		cout << "Select: ";
		cin >> choice;

		switch (choice) {
		case 1:
			string url, title;
			int h, m, s;

			cout << "Enter Url: ";
			cin >> url;
			cout << "Enter Title: ";
			cin >> title;
			cout << "Enter Time (hours, minutes, seconds): ";
			cin >> h >> m >> s;

			visit(url, title, h, m, s);
			break;

		case 2:
			goBack();
			break;

		case 3:
			goForward();
			break;

		case 4:
			deleteCurrent();
			break;

		case 5:
			displayHistory();
			break;

		case 6:
			cleanMemory();
			cout << "Memory Cleaned. Exiting!!";
			return 0;
		
		default:
			cout << "Invalid Choice!\n";
		}
	}
}
