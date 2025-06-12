#include <iostream>
#include <vector>
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

    void searchByTitle(const string& title)
    {
        // find(books.begin(), books.end(), title);
        bool valid = false;
        size_t idx;
        for (idx = 0; idx < books.size(); idx++)
        {
            if (books[idx].title == title)
            {
                valid = true;
                break;
            }
        }
        if (valid)
        {
            cout << "������ ã�ҽ��ϴ�." << endl;
            cout << "- " << books[idx].title << " by " << books[idx].author << endl;
        }
        else
        {
            cout << "��ġ�ϴ� ����� �����ϴ�." << endl;
        }
    }

    void searchByAuthor(const string& author)
    {
        // find(books.begin(), books.end(), author);
        bool valid = false;
        size_t idx;
        for (idx = 0; idx < books.size(); idx++)
        {
            if (books[idx].author == author)
            {
                valid = true;
                break;
            }
        }
        if (valid)
        {
            cout << "������ ã�ҽ��ϴ�." << endl;
            cout << "- " << books[idx].title << " by " << books[idx].author << endl;
        }
        else
        {
            cout << "��ġ�ϴ� ����� �����ϴ�." << endl;
        }
    }
};

int main() 
{
    BookManager manager;

    // ������ ���� ���α׷��� �⺻ �޴��� �ݺ������� ����Ͽ� ����� �Է��� ó���մϴ�.
    // ���α׷� ���Ḧ �����ϱ� ������ ��� �����մϴ�.
    while (true) 
    {
        cout << "\n������ ���� ���α׷�" << endl;
        cout << "1. å �߰�" << endl; // å ������ �Է¹޾� å ��Ͽ� �߰�
        cout << "2. ��� å ���" << endl; // ���� å ��Ͽ� �ִ� ��� å ���
        cout << "3. ���� �˻�" << endl; // ���� �˻� �б���
        cout << "4. ����" << endl; // ���α׷� ����
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
                manager.searchByTitle(temp);
            }
            else if (choice == 2)
            {
                cout << "�۰��� �Է�: ";
                cin.ignore();
                getline(cin, temp);
                manager.searchByAuthor(temp);
            }
            else
            {
                cout << "�߸��� �Է��Դϴ�. �������� ���ư��ϴ�." << endl;
            }
        }
        else if (choice == 4) 
        {
            // 3�� ����: ����
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