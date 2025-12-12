// main.cpp
// Linked-list based Library Management System (console, modern C++)
// Compile: g++ -std=c++17 main.cpp -o library.exe

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include<limits>
#include <fstream>


using namespace std;

// ------------------ Data node types ------------------
struct Book {
    string bookNo;
    string title;
    string author;
    bool issued = false;
    Book* next = nullptr;
};

struct Student {
    string admNo;
    string name;
    bool hasBook = false;
    string issuedBookNo;
    Student* next = nullptr;
};

// ------------------ Globals: list heads ------------------
Book* bookHead = nullptr;
Student* studentHead = nullptr;

// ------------------ Utility helpers ------------------
void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// ------------------ Book list operations ------------------
Book* findBook(const string& bno) {
    Book* cur = bookHead;
    while (cur) {
        if (cur->bookNo == bno) return cur;
        cur = cur->next;
    }
    return nullptr;
}

void addBook() {
    clearScreen();
    cout << "ADD NEW BOOK\n";
    Book* node = new Book;
    cout << "Book No: ";
    getline(cin, node->bookNo);
    if (node->bookNo.empty()) { delete node; cout << "Cancelled.\n"; pause(); return; }
    if (findBook(node->bookNo)) { delete node; cout << "Book with that number already exists.\n"; pause(); return; }
    cout << "Title: ";
    getline(cin, node->title);
    cout << "Author: ";
    getline(cin, node->author);
    node->next = bookHead;
    bookHead = node;
    cout << "Book added successfully.\n";
    pause();
}

void listBooks() {
    clearScreen();
    cout << left << setw(12) << "Book No" << setw(30) << "Title" << setw(25) << "Author" << "Issued\n";
    cout << string(80, '=') << "\n";
    Book* cur = bookHead;
    while (cur) {
        cout << left << setw(12) << cur->bookNo << setw(30) << cur->title << setw(25) << cur->author << (cur->issued ? "Yes" : "No") << "\n";
        cur = cur->next;
    }
    pause();
}

void showBookDetails() {
    clearScreen();
    cout << "Enter Book No: ";
    string bno; getline(cin, bno);
    Book* b = findBook(bno);
    if (!b) cout << "Book not found.\n";
    else {
        cout << "\nBook No: " << b->bookNo << "\nTitle: " << b->title << "\nAuthor: " << b->author << "\nIssued: " << (b->issued ? "Yes" : "No") << "\n";
    }
    pause();
}

void modifyBook() {
    clearScreen();
    cout << "Enter Book No to modify: ";
    string bno; getline(cin, bno);
    Book* b = findBook(bno);
    if (!b) { cout << "Not found.\n"; pause(); return; }
    cout << "Current Title: " << b->title << "\nNew Title (leave empty to keep): ";
    string s; getline(cin, s); if (!s.empty()) b->title = s;
    cout << "Current Author: " << b->author << "\nNew Author (leave empty to keep): ";
    getline(cin, s); if (!s.empty()) b->author = s;
    cout << "Updated.\n";
    pause();
}

void deleteBook() {
    clearScreen();
    cout << "Enter Book No to delete: ";
    string bno; getline(cin, bno);
    Book* cur = bookHead; Book* prev = nullptr;
    while (cur) {
        if (cur->bookNo == bno) break;
        prev = cur; cur = cur->next;
    }
    if (!cur) { cout << "Not found.\n"; pause(); return; }
    if (cur->issued) { cout << "Cannot delete: book is currently issued.\n"; pause(); return; }
    if (!prev) bookHead = cur->next;
    else prev->next = cur->next;
    delete cur;
    cout << "Deleted.\n"; pause();
}

// ------------------ Student list operations ------------------
Student* findStudent(const string& adm) {
    Student* cur = studentHead;
    while (cur) {
        if (cur->admNo == adm) return cur;
        cur = cur->next;
    }
    return nullptr;
}

void addStudent() {
    clearScreen();
    cout << "ADD NEW STUDENT\n";
    Student* s = new Student;
    cout << "Admission No: ";
    getline(cin, s->admNo);
    if (s->admNo.empty()) { delete s; cout << "Cancelled.\n"; pause(); return; }
    if (findStudent(s->admNo)) { delete s; cout << "Student already exists.\n"; pause(); return; }
    cout << "Name: ";
    getline(cin, s->name);
    s->next = studentHead; studentHead = s;
    cout << "Student added.\n"; pause();
}

void listStudents() {
    clearScreen();
    cout << left << setw(12) << "Adm No" << setw(25) << "Name" << setw(12) << "Has Book" << "Book No\n";
    cout << string(70, '=') << "\n";
    Student* cur = studentHead;
    while (cur) {
        cout << left << setw(12) << cur->admNo << setw(25) << cur->name << setw(12) << (cur->hasBook ? "Yes" : "No") << cur->issuedBookNo << "\n";
        cur = cur->next;
    }
    pause();
}

void showStudentDetails() {
    clearScreen();
    cout << "Enter Admission No: ";
    string adm; getline(cin, adm);
    Student* s = findStudent(adm);
    if (!s) cout << "Student not found.\n";
    else {
        cout << "\nAdmission No: " << s->admNo << "\nName: " << s->name << "\nHas Book: " << (s->hasBook ? "Yes" : "No");
        if (s->hasBook) cout << "\nIssued Book No: " << s->issuedBookNo;
        cout << "\n";
    }
    pause();
}

void modifyStudent() {
    clearScreen();
    cout << "Enter Admission No to modify: ";
    string adm; getline(cin, adm);
    Student* s = findStudent(adm);
    if (!s) { cout << "Not found.\n"; pause(); return; }
    cout << "Current Name: " << s->name << "\nNew Name (leave empty to keep): ";
    string t; getline(cin, t); if (!t.empty()) s->name = t;
    cout << "Updated.\n"; pause();
}

void deleteStudent() {
    clearScreen();
    cout << "Enter Admission No to delete: ";
    string adm; getline(cin, adm);
    Student* cur = studentHead; Student* prev = nullptr;
    while (cur) {
        if (cur->admNo == adm) break;
        prev = cur; cur = cur->next;
    }
    if (!cur) { cout << "Not found.\n"; pause(); return; }
    if (cur->hasBook) { cout << "Cannot delete: student has a book issued.\n"; pause(); return; }
    if (!prev) studentHead = cur->next; else prev->next = cur->next;
    delete cur; cout << "Deleted.\n"; pause();
}

// ------------------ Issue & deposit ------------------
void issueBook() {
    clearScreen();
    cout << "BOOK ISSUE\n";
    cout << "Enter Admission No: "; string adm; getline(cin, adm);
    Student* s = findStudent(adm);
    if (!s) { cout << "Student not found.\n"; pause(); return; }
    if (s->hasBook) { cout << "Student already has a book issued (" << s->issuedBookNo << ").\n"; pause(); return; }
    cout << "Enter Book No to issue: "; string bno; getline(cin, bno);
    Book* b = findBook(bno);
    if (!b) { cout << "Book not found.\n"; pause(); return; }
    if (b->issued) { cout << "Book already issued to somebody else.\n"; pause(); return; }
    // Issue
    b->issued = true;
    s->hasBook = true;
    s->issuedBookNo = b->bookNo;
    cout << "Book issued successfully. Return within 15 days.\n";
    pause();
}

void depositBook() {
    clearScreen();
    cout << "BOOK DEPOSIT\n";
    cout << "Enter Admission No: "; string adm; getline(cin, adm);
    Student* s = findStudent(adm);
    if (!s) { cout << "Student not found.\n"; pause(); return; }
    if (!s->hasBook) { cout << "Student does not have any book issued.\n"; pause(); return; }
    Book* b = findBook(s->issuedBookNo);
    if (!b) { cout << "Error: issued book record missing.\n"; pause(); return; }
    cout << "Enter number of days book was with student: ";
    int days = 0; string tmp;
    getline(cin, tmp);
    try { days = stoi(tmp); } catch(...) { days = 0; }
    int fine = 0;
    if (days > 15) fine = (days - 15) * 15; // Rs 15 per day as example
    // Return
    b->issued = false;
    s->hasBook = false;
    s->issuedBookNo.clear();
    cout << "Book deposited. Fine: Rs " << fine << "\n";
    pause();
}

void saveBooks() {
    ofstream out("books.dat", ios::binary);
    if (!out) return;

    Book* cur = bookHead;
    while (cur) {
        // Write lengths + strings (safe for dynamic content)
        size_t len;

        len = cur->bookNo.size();
        out.write((char*)&len, sizeof(len));
        out.write(cur->bookNo.c_str(), len);

        len = cur->title.size();
        out.write((char*)&len, sizeof(len));
        out.write(cur->title.c_str(), len);

        len = cur->author.size();
        out.write((char*)&len, sizeof(len));
        out.write(cur->author.c_str(), len);

        out.write((char*)&cur->issued, sizeof(cur->issued));

        cur = cur->next;
    }
    out.close();
}

void loadBooks() {
    ifstream in("books.dat", ios::binary);
    if (!in) return;

    // Clear existing list first
    while (bookHead) {
        Book* t = bookHead;
        bookHead = bookHead->next;
        delete t;
    }

    while (true) {
        size_t len;
        Book* node = new Book;

        // bookNo
        if (!in.read((char*)&len, sizeof(len))) break;
        node->bookNo.resize(len);
        in.read(&node->bookNo[0], len);

        // title
        in.read((char*)&len, sizeof(len));
        node->title.resize(len);
        in.read(&node->title[0], len);

        // author
        in.read((char*)&len, sizeof(len));
        node->author.resize(len);
        in.read(&node->author[0], len);

        // issued flag
        in.read((char*)&node->issued, sizeof(node->issued));

        // insert at head
        node->next = bookHead;
        bookHead = node;
    }
    in.close();
}

void saveStudents() {
    ofstream out("students.dat", ios::binary);
    if (!out) return;

    Student* cur = studentHead;
    while (cur) {
        size_t len;

        len = cur->admNo.size();
        out.write((char*)&len, sizeof(len));
        out.write(cur->admNo.c_str(), len);

        len = cur->name.size();
        out.write((char*)&len, sizeof(len));
        out.write(cur->name.c_str(), len);

        out.write((char*)&cur->hasBook, sizeof(cur->hasBook));

        len = cur->issuedBookNo.size();
        out.write((char*)&len, sizeof(len));
        out.write(cur->issuedBookNo.c_str(), len);

        cur = cur->next;
    }
    out.close();
}

void loadStudents() {
    ifstream in("students.dat", ios::binary);
    if (!in) return;

    // Clear old list
    while (studentHead) {
        Student* t = studentHead;
        studentHead = studentHead->next;
        delete t;
    }

    while (true) {
        size_t len;
        Student* node = new Student;

        // admNo
        if (!in.read((char*)&len, sizeof(len))) break;
        node->admNo.resize(len);
        in.read(&node->admNo[0], len);

        // name
        in.read((char*)&len, sizeof(len));
        node->name.resize(len);
        in.read(&node->name[0], len);

        // hasBook
        in.read((char*)&node->hasBook, sizeof(node->hasBook));

        // issuedBookNo
        in.read((char*)&len, sizeof(len));
        node->issuedBookNo.resize(len);
        in.read(&node->issuedBookNo[0], len);

        node->next = studentHead;
        studentHead = node;
    }
    in.close();
}



// ------------------ Menus ------------------
void adminMenu() {
    while (true) {
        clearScreen();
        cout << "ADMIN MENU\n1. Add Student\n2. List Students\n3. Show Student\n4. Modify Student\n5. Delete Student\n6. Add Book\n7. List Books\n8. Show Book\n9. Modify Book\n10. Delete Book\n11. Back\nChoose: ";
        string ch; getline(cin, ch);
        if (ch=="1") addStudent();
        else if (ch=="2") listStudents();
        else if (ch=="3") showStudentDetails();
        else if (ch=="4") modifyStudent();
        else if (ch=="5") deleteStudent();
        else if (ch=="6") addBook();
        else if (ch=="7") listBooks();
        else if (ch=="8") showBookDetails();
        else if (ch=="9") modifyBook();
        else if (ch=="10") deleteBook();
        else if (ch=="11") break;
    }
}

int main() {
    loadBooks();
    loadStudents();

    {
        Book* b = new Book{"B001","C++ Basics","Bjarne Stroustrup",false, bookHead};
        bookHead = b;
        b = new Book{"B002","DSA in C++","S. Author",false, bookHead}; bookHead = b;
    }
    // add a sample student
    {
        Student* s = new Student{"S001","Alice",false,"", studentHead};
        studentHead = s;
    }

    while (true) {
        clearScreen();
        cout << "LIBRARY MANAGEMENT SYSTEM\n";
        cout << "1. Book Issue\n2. Book Deposit\n3. Administrator Menu\n4. Exit\nChoose: ";
        string ch; getline(cin, ch);
        if (ch=="1") issueBook();
        else if (ch=="2") depositBook();
        else if (ch=="3") adminMenu();
        else if (ch=="4") { cout << "Goodbye!\n"; break; }
    }

    // cleanup lists (optional)
    while (bookHead) { Book* t = bookHead; bookHead = bookHead->next; delete t; }
    while (studentHead) { Student* t = studentHead; studentHead = studentHead->next; delete t; }
    
    saveBooks();
    saveStudents();

    return 0;
}
