#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std; // namespace std ���

class Book 
{
public:
    string title;
    string author;

    Book(const string& title, const string& author) : title(title), author(author) {}
};

class BookManager 
{
private:
    vector<Book> books; // å ��� ����

public:
    Book* findBookByTitle(string title)
    {
        size_t idx = 0;
        for (; idx < books.size(); idx++)
        {
            if (books[idx].title == title)
            {
                return &books[idx];
            }
        }
        return nullptr; 
    }

    Book* findBookByAuthor(string author)
    {
        size_t idx = 0;
        for (; idx < books.size(); idx++)
        {
            if (books[idx].author == author)
            {
                return &books[idx];
            }
        }
        return nullptr;
    }

    // å �߰� �޼���
    void addBook(const string& title, const string& author) 
    {
        bool valid = false;
        for (size_t i = 0; i < books.size(); i++)
        {
            if (books[i].title == title)
            {
                valid = true;
                break;
            }
        }
        if (valid)
        {
            cout << "�ߺ��� �������Դϴ�. �߰��� �� �����ϴ�." << endl;
        }
        else
        {
            books.push_back(Book(title, author)); // push_back ���
            cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
        }
    }

    // ��� å ��� �޼���
    void displayAllBooks() const 
    {
        if (books.empty()) 
        {
            cout << "���� ��ϵ� å�� �����ϴ�." << endl;
            return;
        }

        cout << "���� ���� ���:" << endl;
        for (size_t i = 0; i < books.size(); i++) // �Ϲ����� for�� ���
        {   // size_t == unsigned integer ��ȣ ���� ����
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }
};

class BorrowManager
{
private:
    unordered_map<string, int> stock; // �ߺ�X ������, �Ǽ�

public:
    void initializeStock(string book, int quantity = 3)
    {
        stock[book] = quantity;
    }

    void borrowBook(string title)
    {
        if (stock.find(title) != stock.end() && stock[title] != 0)
        {
            stock[title] -= 1;
            cout << title << " ���� �Ϸ�" << endl;
        }
        else
        {
            cout << "���� ���� ����" << endl;
        }
    }

    void returnBook(string title)
    {
        if (stock.find(title) != stock.end() && stock[title] != 3)
        {
            stock[title] += 1;
            cout << title << " �ݳ� �Ϸ�" << endl;
        }
        else
        {
            cout << "���� �ݳ� ����" << endl;
        }
    }

    void displayStock()
    {
        for (auto it : stock)
        {
            cout << "'" << it.first << "'�� �ܿ��� : ";
            cout << it.second << "/3" << endl;
        }
    }
};

int main() 
{
    BookManager manager;
    BorrowManager borrow;

    // ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
    // ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
    while (true) 
    {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
        cout << "2. ��� å ���" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "3. ���� �˻�" << endl; // ���� �˻� �б���
        cout << "4. ���� ���� ��Ȳ" << endl;
        cout << "5. ���� ���� / �ݳ�" << endl;
        cout << "6. ����" << endl; // ���α׷� ����
        cout << "����: ";

        int choice; // ������� �޴� ������ ����
        cin >> choice;

        if (choice == 1) 
        {
            // 1�� ����: å �߰�
            // ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
            string title, author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ���� = ���� ���� ����
            getline(cin, title); // ���� �Է� (���� ����)
            cout << "å ����: ";
            getline(cin, author); // ���ڸ� �Է� (���� ����)
            manager.addBook(title, author); // �Է¹��� å ������ �߰�
            borrow.initializeStock(title);
        }
        else if (choice == 2) 
        {
            // 2�� ����: ��� å ���
            // ���� BookManager�� ����� å ����� ����մϴ�.
            manager.displayAllBooks();
        }
        else if (choice == 3)
        {
            // 3�� ����: ���� �˻� �б���
            cout << "1. ������ �˻�" << endl;
            cout << "2. �۰��� �˻�" << endl;
            cout << "����: ";
            string temp;
            cin >> choice;
            if (choice == 1)
            {
                cout << "������ �Է�: ";
                cin.ignore();
                getline(cin, temp);
                if (manager.findBookByTitle(temp) != nullptr)
                {
                    cout << manager.findBookByTitle(temp)->title << " by ";
                    cout << manager.findBookByTitle(temp)->author << endl;
                }
                else
                {
                    cout << "�˻� ����. �������� ���ư��ϴ�." << endl;
                }

            }
            else if (choice == 2)
            {
                cout << "�۰��� �Է�: ";
                cin.ignore();
                getline(cin, temp);
                if (manager.findBookByAuthor(temp) != nullptr)
                {
                    cout << manager.findBookByAuthor(temp)->title << " by ";
                    cout << manager.findBookByAuthor(temp)->author << endl;
                }
                else
                {
                    cout << "�˻� ����. �������� ���ư��ϴ�." << endl;
                }
            }
            else
            {
                cout << "�߸��� �Է��Դϴ�. �������� ���ư��ϴ�." << endl;
            }
        }
        else if (choice == 4) // ���� ���� ��Ȳ
        {
            borrow.displayStock();
        }
        else if (choice == 5) // ���� ����/�ݳ�
        {
            cout << "1. ���� ����" << endl;
            cout << "2. ���� �ݳ�" << endl;
            cout << "����: ";
            cin >> choice;
            string title;
            if (choice == 1)
            {
                cout << "������ ������ �Է�: ";
                cin.ignore();
                getline(cin, title);
                borrow.borrowBook(title);
            }
            else if (choice == 2)
            {
                cout << "�ݳ��� ������ �Է�: ";
                cin.ignore();
                getline(cin, title);
                borrow.returnBook(title);
            }
            else
            {
                cout << "�߸��� �Է��Դϴ�. �������� ���ư��ϴ�." << endl;
            }
        }
        else if (choice == 6)
        {
            // ���α׷��� �����ϰ� ����ڿ��� �޽����� ����մϴ�.
            cout << "���α׷��� �����մϴ�." << endl;
            break; // while ���� ����
        }
        else 
        {
            // �߸��� �Է� ó��
            // �޴��� ���� ��ȣ�� �Է����� ��� ��� �޽����� ����մϴ�.
            cout << "�߸��� �Է��Դϴ�. �ٽ� �õ��ϼ���." << endl;
        }
    }

    return 0; // ���α׷� ���� ����
}