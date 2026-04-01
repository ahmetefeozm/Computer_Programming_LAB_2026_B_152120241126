#include <iostream>
#include <string>

using namespace std;

class BankSystem {
private:
    // -----------Data Structure-----------

    // MoneyBundle
    struct MoneyBundle {
        string serialNumber;
        string currencyType;
        int billCounts[3]; // [0]=100, [1]=50, [2]=
    };

    // LinkedList Node
    struct MoneyNode {
        MoneyBundle bundle;
        MoneyNode* next;
    };

    // Customer Struct
    struct Customer {
        string customerName;
        string transactionType;
    };

    // Stack (Case) Variable
    MoneyNode* top;

    //Circular Queue (Customer) Variables
    static const int MAX_QUEUE_SIZE = 5;
    Customer customerQueue[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int currentSize;

public:
    BankSystem() {
        top = nullptr;
        front = 0;
        rear = -1;
        currentSize = 0;
    }

    ~BankSystem() {
        while (top != nullptr) {
            MoneyNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    // -----------Operations-----------
    void receiveMoney(string serial, string currency, int count100, int count50, int count20) {
        MoneyNode* newNode = new MoneyNode();
        newNode->bundle.serialNumber = serial;
        newNode->bundle.currencyType = currency;
        newNode->bundle.billCounts[0] = count100;
        newNode->bundle.billCounts[1] = count50;
        newNode->bundle.billCounts[2] = count20;

        newNode->next = top;
        top = newNode;

        cout << "[+] Kasa: Para destesi eklendi (" << serial << " - " << currency << ").\n";
    }

    void newCustomer(string name, string transaction) {
        if (currentSize == MAX_QUEUE_SIZE) {
            cout << "[-] Hata: Kuyruk dolu! " << name << " siraya eklenemedi.\n";
            return;
        }

        rear = (rear + 1) % MAX_QUEUE_SIZE;
        customerQueue[rear].customerName = name;
        customerQueue[rear].transactionType = transaction;
        currentSize++;

        cout << "[+] Sira: Müşteri eklendi (" << name << " - " << transaction << ").\n";
    }

    void processTransaction() {
        if (currentSize == 0) {
            cout << "[-] Hata: Sırada bekleyen müşteri yok!\n";
            return;
        }
        if (top == nullptr) {
            cout << "[-] Hata: Kasada para destesi kalmadı! İşlem gerçekleştirilemiyor.\n";
            return;
        }

        Customer servedCustomer = customerQueue[front];
        front = (front + 1) % MAX_QUEUE_SIZE;
        currentSize--;

        MoneyNode* temp = top;
        MoneyBundle usedBundle = temp->bundle;
        top = top->next;
        delete temp;

        cout << "\n>>> ISLEM GERCEKLESTIRILIYOR <<<\n";
        cout << "Müsteri: " << servedCustomer.customerName << " (" << servedCustomer.transactionType << ")\n";
        cout << "Kullanilan Para Destesi: " << usedBundle.serialNumber << " [" << usedBundle.currencyType << "]\n";
        cout << "(100'lük: " << usedBundle.billCounts[0] << ", 50'lik: " << usedBundle.billCounts[1] << ", 20'lik: " << usedBundle.billCounts[2] << ")\n";
        cout << "Islem tamamlandi.\n";
    }

    void display() {
        cout << "\n================= BANKA DURUMU =================\n";

        cout << "--- MÜSTERI SIRASI ---\n";
        if (currentSize == 0) {
            cout << "  Sira bos.\n";
        }
        else {
            int index = front;
            for (int i = 0; i < currentSize; i++) {
                cout << "  " << i + 1 << ". " << customerQueue[index].customerName
                    << " (" << customerQueue[index].transactionType << ")\n";
                index = (index + 1) % MAX_QUEUE_SIZE;
            }
        }

        cout << "\n--- KASA (PARA DESTELERI) ---\n";
        if (top == nullptr) {
            cout << "  Kasa bos.\n";
        }
        else {
            MoneyNode* current = top;
            int counter = 1;
            while (current != nullptr) {
                cout << "  " << counter++ << ". Deste: " << current->bundle.serialNumber
                    << " [" << current->bundle.currencyType << "] "
                    << "=> (100x" << current->bundle.billCounts[0]
                    << ", 50x" << current->bundle.billCounts[1]
                    << ", 20x" << current->bundle.billCounts[2] << ")\n";
                current = current->next;
            }
        }
        cout << "================================================\n";
    }
};

int main() {
    BankSystem branch;
    int choice;

    while (true) {
        cout << "\n--- BANKA SUBE YONETIM SISTEMI ---\n";
        cout << "1. Kasaya Para Ekle (Push)\n";
        cout << "2. Yeni Musteri Ekle (Enqueue)\n";
        cout << "3. Islem Gerceklestir (Pop & Dequeue)\n";
        cout << "4. Durumu Goster\n";
        cout << "5. Cikis\n";
        cout << "Seciminiz: ";

        if (!(cin >> choice)) {
            cout << "Hatalı giris! Lutfen bir sayi girin.\n";
            break;
        }

        if (choice == 1) {
            string serial, currency;
            int c100, c50, c20;

            cout << "Deste Seri No (orn. SN-100): ";
            cin >> serial;
            cout << "Para Birimi (orn. TL, USD): ";
            cin >> currency;
            cout << "100'luk banknot adedi: ";
            cin >> c100;
            cout << "50'lik banknot adedi: ";
            cin >> c50;
            cout << "20'lik banknot adedi: ";
            cin >> c20;

            branch.receiveMoney(serial, currency, c100, c50, c20);
        }
        else if (choice == 2) {
            string name, type;

            cout << "Musteri Adi ve Soyadi: ";
            cin.ignore(); // Newline Clean
            getline(cin, name); // Get name with spaces "EFE OZMEN"

            cout << "Islem Tipi (Withdraw/Deposit): ";
            cin >> type;

            branch.newCustomer(name, type);
        }
        else if (choice == 3) {
            branch.processTransaction();
        }
        else if (choice == 4) {
            branch.display();
        }
        else if (choice == 5) {
            cout << "Sistemden cikiliyor...\n";
            break;
        }
        else {
            cout << "Gecersiz secim! Lutfen 1 ile 5 arasinda bir deger giriniz.\n";
        }
    }

    return 0;
}