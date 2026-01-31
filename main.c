#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<conio.h> // Added for getch()

// structure of book 
struct book{ 
    int id; 
    char bookName[50]; 
    char authorName[50]; 
}b; 

// structure of student  
struct student{ 
    int id; 
    char studName[50]; 
    char Department[50]; 
    int ID; 
    char bookName[50]; 
}s; 

// file pointer 
FILE *fp; 

// functions prototype 
// Note: These must match the function names exactly!
void addBook(); 
void booksList(); 
void del(); 
void issueBook(); 
void issueList(); 
void searchBook(); 
void updateBook(); 
void login();

int main() 
{ 
    int ch; 

    login();

    while (1) 
    { 
        system("cls"); 
        printf("*** Library Management System ***\n"); 
        printf("1. Add Book\n"); 
        printf("2. Book List\n"); 
        printf("3. Remove Book\n"); 
        printf("4. Issue Book\n"); 
        printf("5. Issued Book List\n"); 
        printf("0. Exit\n\n"); 
        printf("Enter your Choice: "); 
        scanf("%d", &ch); 

        switch (ch) 
        { 
            case 0: 
               exit(0); 
            case 1: 
               addBook(); // Fixed: Case sensitivity
               break; 
            case 2: 
               booksList(); // Fixed: Matches function name below
               break; 
            case 3: 
               del(); 
               break; 
            case 4: 
               issueBook(); 
               break; 
            case 5: 
               issueList(); 
               break; 
            case 6:
               searchBook();
               break;
            default: 
               printf("Invalid choice... please try again\n"); 
               break; 
        } 
        printf("\nPress any key to continue..."); 
        getch(); // Now works because of <conio.h>
    } 

    return 0; 
} 

// function for add book 
void addBook() {
    int id_exists = 0;
    int target_id;
    
    printf("Enter Book id: ");
    scanf("%d", &target_id);

    // Check for duplicates
    fp = fopen("books.txt", "rb");
    if (fp != NULL) {
        while (fread(&b, sizeof(b), 1, fp) == 1) {
            if (b.id == target_id) {
                id_exists = 1;
                break;
            }
        }
        fclose(fp);
    }

    if (id_exists) {
        printf("\nError: A book with ID %d already exists!", target_id);
        return;
    }

    // If ID is unique, proceed to save
    fp = fopen("books.txt", "ab");
    b.id = target_id;
    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookName);
    printf("Enter author name: ");
    fflush(stdin);
    gets(b.authorName);

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
    printf("\nBook Added Successfully!");
}

// function for Book list 
void booksList() { 
    system("cls");  
    printf("*** Available Books ***\n\n"); 
    printf("%-10s %-30s %-20s\n", "Book id", "Book Name", "Author"); 
    printf("------------------------------------------------------------\n");

    fp = fopen("books.txt", "rb"); 
    if(fp == NULL) {
        printf("No books found in records.\n");
        return;
    }

    while(fread(&b, sizeof(b), 1, fp) == 1) { 
        printf("%-10d %-30s %-20s\n", b.id, b.bookName, b.authorName); 
    } 
    fclose(fp); 
} 

// function for issue list 
void issueList() 
{ 
    system("cls"); 
    printf("<== Book Issue List ==>\n\n"); 
    printf("%-10s %-20s %-20s %-10s %-20s\n", "B.ID", "Name", "Dept", "S.ID", "Book Name"); 
    printf("----------------------------------------------------------------------------------\n");

    fp = fopen("issue.txt", "rb"); 
    if(fp == NULL) {
        printf("No issued books found.\n");
        return;
    }

    while(fread(&s, sizeof(s), 1, fp) == 1) { 
        printf("%-10d %-20s %-20s %-10d %-20s\n", s.id, s.studName, s.Department, s.ID, s.bookName); 
    } 
    fclose(fp); 
} 

// function to issue book 
void issueBook() 
{ 
    int f=0; 
    system("cls"); 
    printf("<== Issue Books ==>\n\n"); 
    printf("Enter Book id to issue: "); 
    scanf("%d", &s.id); 

    fp = fopen("books.txt", "rb"); 
    if(fp == NULL) {
        printf("Database error: No books available.\n");
        return;
    }

    while(fread(&b, sizeof(b), 1, fp) == 1) { 
        if(b.id == s.id) { 
            strcpy(s.bookName, b.bookName); 
            f=1; 
            break; 
        } 
    } 
    fclose(fp);

    if(f == 0) { 
        printf("No book found with this id.\n"); 
        return; 
    } 

    fp = fopen("issue.txt", "ab"); 
    printf("Enter Student Name: "); 
    fflush(stdin); 
    gets(s.studName); 

    printf("Enter Student Department: "); 
    fflush(stdin); 
    gets(s.Department); 

    printf("Enter Student ID: "); 
    scanf("%d", &s.ID); 

    fwrite(&s, sizeof(s), 1, fp); 
    printf("\nBook Issued Successfully!\n"); 
    fclose(fp); 
} 

// function to delete book 
void del()  
{ 
    int id, f=0; 
    system("cls"); 
    printf("<== Remove Books ==>\n\n"); 

    printf("Enter Book id to remove: "); 
    scanf("%d", &id); 

    FILE *ft;    
    fp = fopen("books.txt", "rb"); 
    if(fp == NULL) {
        printf("No books to delete.\n");
        return;
    }
    ft = fopen("temp.txt", "wb"); 

    while(fread(&b, sizeof(b), 1, fp) == 1) { 
        if(id == b.id) {  
            f=1; 
        } else { 
            fwrite(&b, sizeof(b), 1, ft); 
        } 
    } 

    fclose(fp); 
    fclose(ft); 

    remove("books.txt"); 
    rename("temp.txt", "books.txt"); 

    if(f == 1) { 
        printf("\nDeleted Successfully."); 
    } else { 
        printf("\nRecord Not Found!"); 
    } 
}

void searchBook() {
    char name[50];
    int f = 0;
    system("cls");
    printf("<== Search Book ==>\n\n");
    printf("Enter Book Name to Search: ");
    fflush(stdin);
    gets(name);

    fp = fopen("books.txt", "rb");
    if (fp == NULL) {
        printf("No books in database.\n");
        return;
    }

    printf("\n%-10s %-30s %-20s\n", "ID", "Book Name", "Author");
    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (strstr(strlwr(b.bookName), strlwr(name))) { // Case-insensitive search
            printf("%-10d %-30s %-20s\n", b.id, b.bookName, b.authorName);
            f = 1;
        }
    }
    fclose(fp);

    if (f == 0) printf("\nNo book found with that name.");
}
void login() {
    char username[20];
    char pass[20];

    system("cls"); // Screen clear karega login se pehle
    printf("--- Admin Login ---\n");

    printf("Enter Username: ");
    scanf("%s", username);

    printf("Enter Password: ");
    scanf("%s", pass);

    // Username "admin" aur Password "admin123" rakha gaya hai
    if (strcmp(username, "admin") == 0 && strcmp(pass, "admin123") == 0) {
        printf("\nAccess Granted! Press any key to enter the dashboard...");
        getch();
    } else {
        printf("\nInvalid Username or Password! Access Denied.\n");
        exit(0);
    }
}