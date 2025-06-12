#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

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

    // 책 추가 메서드
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
            cout << "중복된 도서명입니다. 추가할 수 없습니다." << endl;
        }
        else
        {
            books.push_back(Book(title, author)); // push_back 사용
            cout << "책이 추가되었습니다: " << title << " by " << author << endl;
        }
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
        for (size_t i = 0; i < books.size(); i++) // 일반적인 for문 사용
        {   // size_t == unsigned integer 부호 없는 정수
            cout << "- " << books[i].title << " by " << books[i].author << endl;
        }
    }
};

class BorrowManager
{
private:
    unordered_map<string, int> stock; // 중복X 도서명, 권수

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
            cout << title << " 대출 완료" << endl;
        }
        else
        {
            cout << "도서 대출 실패" << endl;
        }
    }

    void returnBook(string title)
    {
        if (stock.find(title) != stock.end() && stock[title] != 3)
        {
            stock[title] += 1;
            cout << title << " 반납 완료" << endl;
        }
        else
        {
            cout << "도서 반납 실패" << endl;
        }
    }

    void displayStock()
    {
        for (auto it : stock)
        {
            cout << "'" << it.first << "'의 잔여량 : ";
            cout << it.second << "/3" << endl;
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
        cout << "3. 도서 검색" << endl; // 도서 검색 분기점
        cout << "4. 도서 대출 현황" << endl;
        cout << "5. 도서 대출 / 반납" << endl;
        cout << "6. 종료" << endl; // 프로그램 종료
        cout << "선택: ";

        int choice; // 사용자의 메뉴 선택을 저장
        cin >> choice;

        if (choice == 1) 
        {
            // 1번 선택: 책 추가
            // 사용자로부터 책 제목과 저자명을 입력받아 BookManager에 추가합니다.
            string title, author;
            cout << "책 제목: ";
            cin.ignore(); // 이전 입력의 잔여 버퍼를 제거 = 개행 문자 제거
            getline(cin, title); // 제목 입력 (공백 포함)
            cout << "책 저자: ";
            getline(cin, author); // 저자명 입력 (공백 포함)
            manager.addBook(title, author); // 입력받은 책 정보를 추가
            borrow.initializeStock(title);
        }
        else if (choice == 2) 
        {
            // 2번 선택: 모든 책 출력
            // 현재 BookManager에 저장된 책 목록을 출력합니다.
            manager.displayAllBooks();
        }
        else if (choice == 3)
        {
            // 3번 선택: 도서 검색 분기점
            cout << "1. 도서명 검색" << endl;
            cout << "2. 작가명 검색" << endl;
            cout << "선택: ";
            string temp;
            cin >> choice;
            if (choice == 1)
            {
                cout << "도서명 입력: ";
                cin.ignore();
                getline(cin, temp);
                if (manager.findBookByTitle(temp) != nullptr)
                {
                    cout << manager.findBookByTitle(temp)->title << " by ";
                    cout << manager.findBookByTitle(temp)->author << endl;
                }
                else
                {
                    cout << "검색 실패. 메인으로 돌아갑니다." << endl;
                }

            }
            else if (choice == 2)
            {
                cout << "작가명 입력: ";
                cin.ignore();
                getline(cin, temp);
                if (manager.findBookByAuthor(temp) != nullptr)
                {
                    cout << manager.findBookByAuthor(temp)->title << " by ";
                    cout << manager.findBookByAuthor(temp)->author << endl;
                }
                else
                {
                    cout << "검색 실패. 메인으로 돌아갑니다." << endl;
                }
            }
            else
            {
                cout << "잘못된 입력입니다. 메인으로 돌아갑니다." << endl;
            }
        }
        else if (choice == 4) // 도서 대출 현황
        {
            borrow.displayStock();
        }
        else if (choice == 5) // 도서 대출/반납
        {
            cout << "1. 도서 대출" << endl;
            cout << "2. 도서 반납" << endl;
            cout << "선택: ";
            cin >> choice;
            string title;
            if (choice == 1)
            {
                cout << "대출할 도서명 입력: ";
                cin.ignore();
                getline(cin, title);
                borrow.borrowBook(title);
            }
            else if (choice == 2)
            {
                cout << "반납할 도서명 입력: ";
                cin.ignore();
                getline(cin, title);
                borrow.returnBook(title);
            }
            else
            {
                cout << "잘못된 입력입니다. 메인으로 돌아갑니다." << endl;
            }
        }
        else if (choice == 6)
        {
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
    }

    return 0; // 프로그램 정상 종료
}