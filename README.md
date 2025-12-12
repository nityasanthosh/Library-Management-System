# Library-Management-System

This is a console-based Library Management System written in C++.  
It is used to manage books and student records in a library.

## What this project does
- Add and remove books
- Add and remove students
- Issue books to students
- Accept returned books
- Calculate fine for late returns
- Store records using files

## Main data structure used
This project mainly uses **Linked Lists**.

Each book and student is stored as a node in a linked list.

## Why I used linked lists
Linked lists are useful here because:
- Number of books and students can change
- Records can be added or deleted easily
- Memory is used efficiently

## How to run
```
g++ lms.cpp -o lms.exe
.\lms.exe
```
