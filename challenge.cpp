#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

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
        books.push_back(Book(title, author)); // push_back ���
        cout << "å�� �߰��Ǿ����ϴ�: " << title << " by " << author << endl;
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
        for (size_t i = 0; i < books.size(); i++) 
        { // �Ϲ����� for�� ���
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    void searchByTitle(string& title)
    {
        for (Book& book : books)
        {
            if (book.title == title)
            {
                cout << "������: " << title << "��(��) ã�ҽ��ϴ�." << endl;
                return;
            }
        }

        cout << title << "��� å�� ã�� ���߽��ϴ�." << endl;
    }

    void searchByAuthor(string& author)
    {
        for (Book& book : books)
        {
            if (book.author == author)
            {
                cout << "����: " << author << "��(��) ã�ҽ��ϴ�." << endl;
                return;
            }
        }

        cout << "���� '" << author << "'�� å�� ã�� ���߽��ϴ�." << endl;
    }

    Book* findBookByTitle(const string& title)
    {
        for (Book& book : books)
        {
            if (book.title == title)
            {
                return &book;
            }
        }

        return nullptr;
    }

    Book* findBookByAuthor(const string& author)
    {
        for (Book& book : books)
        {
            if (book.author == author)
            {
                return &book;
            }
        }

        return nullptr;
    }

};

class BorrowManager
{
private:
    unordered_map<string, int> stock;

public:
    void initializeStock(const Book* book, int quantity = 3)
    {
        if (nullptr == book)
        {
            return;
        }

        stock[book->title] = quantity;
        cout << "å�� �߰��Ǿ����ϴ�." << endl;
    }

    void borrowBook(const string& title)
    {
        if (stock.end() != stock.find(title))
        {
            if (stock[title] > 0)
            {
                --stock[title];
                cout << title << "��(��) �뿩�߽��ϴ�." << endl;
            }
            else
            {
                cout << "��� ���� / �뿩 ����" << endl;
            }
        }
        else
        {
            cout << "��ġ�ϴ� å�� �����ϴ�." << endl;
        }
    }

    void returnBook(const string& title)
    {
        if (stock.end() != stock.find(title))
        {
            if (stock[title] < 3)
            {
                ++stock[title];
                cout << title << "��(��) �ݳ��߽��ϴ�." << endl;
            }
            else
            {
                cout << "�ݳ� ����" << endl;
            }
        }
        else
        {
            cout << "��ġ�ϴ� å�� �����ϴ�." << endl;
        }
    }

    void displayStock()
    {
        for (pair<const string, int> e : stock)
        {
            cout << "å ����: " << e.first << " / ���: " << e.second << endl;
        }
        for (auto it : stock)
        {
            cout << it.first << " " << it.second << endl;
            cout << &it.first;
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
        cout << "3. �˻�" << endl;
        cout << "4. �뿩/�ݳ�" << endl;
        cout << "5. ����" << endl; // ���α׷� ����
        cout << "����: ";

        int choice; // ������� �޴� ������ ����
        cin >> choice;

        if (choice == 1) 
        {
            // 1�� ����: å �߰�
            // ����ڷκ��� å ����� ���ڸ��� �Է¹޾� BookManager�� �߰��մϴ�.
            string title, author;
            cout << "å ����: ";
            cin.ignore(); // ���� �Է��� �ܿ� ���۸� ����
            getline(cin, title); // ���� �Է� (���� ����)
            cout << "å ����: ";
            getline(cin, author); // ���ڸ� �Է� (���� ����)
            manager.addBook(title, author); // �Է¹��� å ������ �߰�
            borrow.initializeStock(manager.findBookByTitle(title));
        }
        else if (choice == 2) 
        {
            // 2�� ����: ��� å ���
            // ���� BookManager�� ����� å ����� ����մϴ�.
            manager.displayAllBooks();
            borrow.displayStock();
        }
        else if (choice == 3)
        {
            cout << "1. ������ / 2. ���ڸ�" << endl;
            cin >> choice;
            string title, author;
            if (choice == 1)
            {
                cin.ignore();
                getline(cin, title);
                manager.searchByTitle(title);
            }
            else if (choice == 2)
            {
                cin.ignore();
                getline(cin, author);
                manager.searchByAuthor(author);
            }
            else
            {
                cout << "�������� ���ư��ϴ�." << endl;
            }
        }
        else if (choice == 4)
        {
            cout << "1. ���� / 2. �ݳ�" << endl;
            cin >> choice;
            string temp;
            if (choice == 1)
            {
                cout << "������ �Ǵ� ���ڸ��� �Է��ϼ���." << endl;
                cin.ignore();
                getline(cin, temp);
                Book* book = manager.findBookByTitle(temp);
                if (book)
                {
                    borrow.borrowBook(book->title);
                }
                else
                {
                    book = manager.findBookByAuthor(temp);
                    if (book)
                    {
                        borrow.borrowBook(book->title);
                    }
                    else
                    {
                        cout << "��ġ�ϴ� å�� �����ϴ�." << endl;
                    }
                }
            }
            else if (choice == 2)
            {
                cout << "������ �Ǵ� ���ڸ��� �Է��ϼ���." << endl;
                cin.ignore();
                getline(cin, temp);
                Book* book = manager.findBookByTitle(temp);
                if (book)
                {
                    borrow.returnBook(book->title);
                }
                else
                {
                    book = manager.findBookByAuthor(temp);
                    if (book)
                    {
                        borrow.returnBook(book->title);
                    }
                    else
                    {
                        cout << "��ġ�ϴ� å�� �����ϴ�." << endl;
                    }
                }
            }
            else
            {
                cout << "�������� ���ư��ϴ�." << endl;
            }
        }
        else if (choice == 5) 
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

        system("pause");
    }

    return 0; // ���α׷� ���� ����
}
