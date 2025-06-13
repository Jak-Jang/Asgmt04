#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std; // namespace std 사용

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
    vector<Book> books; // 책 목록 저장

public:
    // 책 추가 메서드
    void addBook(const string& title, const string& author) 
    {
        books.push_back(Book(title, author)); // push_back 사용
        cout << "책이 추가되었습니다: " << title << " by " << author << endl;
    }

    // 모든 책 출력 메서드
    void displayAllBooks() const 
    {
        if (books.empty()) 
        {
            cout << "현재 등록된 책이 없습니다." << endl;
            return;
        }

        cout << "현재 도서 목록:" << endl;
        for (size_t i = 0; i < books.size(); i++) 
        { // 일반적인 for문 사용
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }

    void searchByTitle(string& title)
    {
        for (Book& book : books)
        {
            if (book.title == title)
            {
                cout << "도서명: " << title << "을(를) 찾았습니다." << endl;
                return;
            }
        }

        cout << title << "라는 책을 찾지 못했습니다." << endl;
    }

    void searchByAuthor(string& author)
    {
        for (Book& book : books)
        {
            if (book.author == author)
            {
                cout << "저자: " << author << "을(를) 찾았습니다." << endl;
                return;
            }
        }

        cout << "저자 '" << author << "'의 책을 찾지 못했습니다." << endl;
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
        cout << "책이 추가되었습니다." << endl;
    }

    void borrowBook(const string& title)
    {
        if (stock.end() != stock.find(title))
        {
            if (stock[title] > 0)
            {
                --stock[title];
                cout << title << "을(를) 대여했습니다." << endl;
            }
            else
            {
                cout << "재고 부족 / 대여 실패" << endl;
            }
        }
        else
        {
            cout << "일치하는 책이 없습니다." << endl;
        }
    }

    void returnBook(const string& title)
    {
        if (stock.end() != stock.find(title))
        {
            if (stock[title] < 3)
            {
                ++stock[title];
                cout << title << "을(를) 반납했습니다." << endl;
            }
            else
            {
                cout << "반납 실패" << endl;
            }
        }
        else
        {
            cout << "일치하는 책이 없습니다." << endl;
        }
    }

    void displayStock()
    {
        for (pair<const string, int> e : stock)
        {
            cout << "책 제목: " << e.first << " / 재고: " << e.second << endl;
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

    // 도서관 관리 프로그램의 기본 메뉴를 반복적으로 출력하여 사용자 입력을 처리합니다.
    // 프로그램 종료를 선택하기 전까지 계속 동작합니다.
    while (true) 
    {
        cout << "\n도서관 관리 프로그램" << endl;
        cout << "1. 책 추가" << endl; // 책 정보를 입력받아 책 목록에 추가
        cout << "2. 모든 책 출력" << endl; // 현재 책 목록에 있는 모든 책 출력
        cout << "3. 검색" << endl;
        cout << "4. 대여/반납" << endl;
        cout << "5. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) 
        {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
            borrow.initializeStock(manager.findBookByTitle(title));
        }
        else if (choice == 2) 
        {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
            borrow.displayStock();
        }
        else if (choice == 3)
        {
            cout << "1. 도서명 / 2. 저자명" << endl;
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
                cout << "메인으로 돌아갑니다." << endl;
            }
        }
        else if (choice == 4)
        {
            cout << "1. 대출 / 2. 반납" << endl;
            cin >> choice;
            string temp;
            if (choice == 1)
            {
                cout << "도서명 또는 저자명을 입력하세요." << endl;
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
                        cout << "일치하는 책이 없습니다." << endl;
                    }
                }
            }
            else if (choice == 2)
            {
                cout << "도서명 또는 저자명을 입력하세요." << endl;
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
                        cout << "일치하는 책이 없습니다." << endl;
                    }
                }
            }
            else
            {
                cout << "메인으로 돌아갑니다." << endl;
            }
        }
        else if (choice == 5) 
        {
            // 3번 선택: 종료
            // 프로그램을 종료하고 사용자에게 메시지를 출력합니다.
            cout << "프로그램을 종료합니다." << endl;
            break; // while 루프 종료
        }
        else 
        {
            // 잘못된 입력 처리
            // 메뉴에 없는 번호를 입력했을 경우 경고 메시지를 출력합니다.
            cout << "잘못된 입력입니다. 다시 시도하세요." << endl;
        }

        system("pause");
    }

    return 0; // 프로그램 정상 종료
}
