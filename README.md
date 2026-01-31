# Library Management System

A professional, console-based application developed in **C** to streamline library operations. This system provides a secure environment for administrators to manage book inventories and track student issuance records using efficient **File Handling** techniques.

## 🚀 Key Features

* **Secure Admin Authentication**: Integrated login system requiring both a Username and Password to prevent unauthorized access.
* **Book Inventory Management**: Complete CRUD functionality to Add, View, Search, and Remove books from the database.
* **Duplicate Prevention**: Smart validation logic that prevents adding multiple books with the same ID.
* **Issuance Tracking**: Dedicated module to issue books to students and maintain a log of their Department and Roll IDs.
* **Persistent Storage**: All data is permanently stored in binary format within `books.txt` and `issue.txt` files, ensuring data is saved even after the program closes.
* **User-Friendly Interface**: Organized console menus with clear instructions and color-coded feedback (via ANSI escape codes).

## 🛠️ Tech Stack

* **Language**: C
* **Development Environment**: VS Code / MinGW
* **Key Libraries**: `<stdio.h>`, `<stdlib.h>`, `<string.h>`, `<conio.h>`.

## 📋 Installation and Usage

### Prerequisites
Ensure you have a C compiler (like GCC) installed on your system.

### Steps to Run
1.  **Clone the Repository**:
    ```bash
    git clone [https://github.com/YourUsername/YourRepositoryName.git](https://github.com/YourUsername/YourRepositoryName.git)
    ```
2.  **Navigate to Project Directory**:
    ```bash
    cd "Library Management System"
    ```
3.  **Compile the Code**:
    ```bash
    gcc main.c -o main.exe
    ```
4.  **Execute the Program**:
    ```bash
    ./main.exe
    ```

## 👤 Admin Credentials
* **Username**: `admin`
* **Password**: `admin123`

## 📂 Project Structure
* `main.c`: Contains the source code including logic for file handling, searching, and the admin dashboard.
* `books.txt`: Stores the list of available books in the library.
* `issue.txt`: Stores the records of books currently issued to students.

## 📑 License
This project is open-source and available for educational purposes.
