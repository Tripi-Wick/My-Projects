#include <iostream>     // Input Output Stream
#include <sqlite3.h>    // For SQL Lite Libraries
#include <string>
#include <sstream>      // For String Operations
#include <Windows.h>    // For Sleep and system functions
#include <conio.h>      // For getch()

using namespace std;

// Student Class -- to store users
class Student {
  private:
      string Id;
  public:
      Student() : Id(""){}         //Member initializer list
  
      void setId(string id){
          this->Id = id;
      }
  
      string getId(){
          return Id;
      }
};

// Library Class -- to store books
class Library{
  private:
    string Name;
    int Quant;

  public:
    Library() : Name(""), Quant(0) {}

    void setName(string name){
        this->Name = name;
    }

    void setQuantity(int quant){
        this->Quant = quant;
    }

    int getQuantity(){
        return Quant;
    }

    string getName(){
        return Name;
    }

};

// Creating Tables
void initializeDatabase(sqlite3* DB) {
    char* errorMessage;
    string createStudentTable = "CREATE TABLE IF NOT EXISTS student (Id TEXT PRIMARY KEY);";
    string createLibraryTable = "CREATE TABLE IF NOT EXISTS lib (Name TEXT PRIMARY KEY, Quantity INTEGER);";

    if (sqlite3_exec(DB, createStudentTable.c_str(), 0, 0, &errorMessage) != SQLITE_OK) {
        cerr << "Failed to create student table: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }

    if (sqlite3_exec(DB, createLibraryTable.c_str(), 0, 0, &errorMessage) != SQLITE_OK) {
        cerr << "Failed to create library table: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}

// SQLite function for query results
// NotUsed --> Signature Argument
// Argc --> No of Columns
// Argv --> Value of Columns
// azColName --> Name of Columns
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << endl;
    }
    cout << endl;
    return 0;
}

// Book Availability Check
// sqlite3_prepare_v2()-->  Prepares the SQL statement for execution.
// DB  --> is the database connection.
// sql.c_str() -->  provides the SQL query as a C-style string.
// -1  --> indicates that the SQL string is null-terminated.
// &stmt -->  is where the prepared statement will be stored.
// NULL -->  for unused parameter.
int bookAvail(sqlite3* DB, string Bname) {
    string sql = "SELECT Name, Quantity FROM lib WHERE Name = '" + Bname + "';";

    sqlite3_stmt* stmt;
    if ( sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK ) {
        cerr << "\n\t\t\t\t\tError: " << sqlite3_errmsg(DB) << endl;
        return 0;
    }

    int quantity = 0;
    while ( sqlite3_step(stmt) == SQLITE_ROW ) {
        string name = reinterpret_cast<const char*>( sqlite3_column_text(stmt, 0));
        if (Bname == name) {
            quantity = sqlite3_column_int(stmt, 1);
        } 
        else {
            cout << "\n\t\t\t\t\tBook Not Found." << endl;
        }
    }

    sqlite3_finalize(stmt);   //Cleans and frees resources attached with the statement
    return quantity;
}

// Available Books Display
void display(sqlite3* DB) {
    system("cls");

    cout << "\n\t\t\t\t\t-------------------------------" << endl;
    cout << "\t\t\t\t\t>> AVAILABLE BOOKS <<" << endl;
    cout << "\t\t\t\t\t-------------------------------" << endl;

    string sql = "SELECT * FROM lib;";

    char* errorMessage;
    if ( sqlite3_exec(DB, sql.c_str(), callback, 0, &errorMessage) != SQLITE_OK ) {
        cerr << "\n\t\t\t\t\tError: " << errorMessage << endl;
        sqlite3_free(errorMessage);
    }
}

// User Menu
void user(sqlite3* DB, Library l, Student s) {
    system("cls");
    display(DB);

    string Sid;
    cout << "\n\t\t\t\t\tEnter Your ID: ";
    cin.ignore();
    getline(cin,Sid);

    string sql = "SELECT * FROM student WHERE Id = '" + Sid + "';";

    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        cerr << "\n\t\t\t\t\tError: " << sqlite3_errmsg(DB) << endl;
        return;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        cout << "\n\t\t\t\t\tStudent ID Found." << endl;


        cout << "\n\t\t\t\t\t***Note: Add a Space Before Entering Books Name***" << endl;
        string Bname;
        cout << "\t\t\t\t\tEnter Book Name: ";
        cin.ignore();
        getline(cin,Bname);


        int bookQuantity = bookAvail(DB, Bname);

        if (bookQuantity > 0) {
            bookQuantity--;

            stringstream ss;
            ss << "UPDATE lib SET Quantity = " << bookQuantity << " WHERE Name = '" << Bname << "';";
            string sqlUpdate = ss.str();

            char* errorMessage;
            if ( sqlite3_exec(DB, sqlUpdate.c_str(), 0, 0, &errorMessage ) != SQLITE_OK) {
                cerr << "\n\t\t\t\t\tError: " << errorMessage << endl;
                sqlite3_free(errorMessage);
            } 
            else {
                cout << "\n\t\t\t\t\tBook is available. Borrowing Book...." << endl;
            }
        } 
        else {
            cout << "\n\t\t\t\t\tBook is not available." << endl;
        }
    } 
    else {
        cout << "\n\t\t\t\t\tThis Student is Not Registered." << endl;
    }

    sqlite3_finalize(stmt);
    Sleep(2000);
}

// Administration Menu
void admin(sqlite3* DB, Library l, Student s){
    bool closed = false;

    while(!closed){
        system("cls");   // clears the console

        // Menu Display
        int choice;
        cout << "\n\t\t\t\t\t-------------------------------" << endl;
        cout << "\t\t\t\t\t>> LIBRARY MANAGEMENT SYSTEM <<" << endl;
        cout << "\t\t\t\t\t-------------------------------" << endl;
        cout << "\n\t\t\t\t\t 1. Add Book." << endl;
        cout << "\t\t\t\t\t 2. Add Student." << endl;
        cout << "\t\t\t\t\t 0. Exit." << endl;
        cout << "\t\t\t\t\t.................................." << endl;
        cout << "\t\t\t\t\t>> Choice Options: [1/2/0] <<" << endl;
        cout << "\t\t\t\t\t.................................." << endl;
        cout << "\n\t\t\t\t\tEnter Your Choice: ";
        cin >> choice;

        // Adding Book
        if (choice == 1) {
            system("cls");
            string name;
            int quantity;

            cout << "\n\t\t\t\t\tEnter Book Name: ";
            cin.ignore();
            getline(cin,name);
            l.setName(name);

            cout << "\n\t\t\t\t\tEnter Quantity: ";
            cin >> quantity;
            l.setQuantity(quantity);


            stringstream ss;
            ss << "INSERT INTO lib (Name, Quantity) VALUES('" << l.getName() << "', " << l.getQuantity() << ");";
            string sql = ss.str();

            char* errorMessage;
            if ( sqlite3_exec(DB, sql.c_str(), 0, 0, &errorMessage) != SQLITE_OK ) {
                cerr << "\n\t\t\t\t\tError: " << errorMessage << endl;
                sqlite3_free(errorMessage);
            } else {
                cout << "\n\t\t\t\t\tBook Inserted Successfully!" << endl;
            }
        }
        else if (choice == 2) {
            system("cls");
            string id;

            cout << "\n\t\t\t\t\tEnter Student ID: ";
            cin >> id;
            s.setId(id);

            string sql = "INSERT INTO student (Id) VALUES('" + s.getId() + "');";

            char* errorMessage;
            if ( sqlite3_exec(DB, sql.c_str(), 0, 0, &errorMessage) != SQLITE_OK ) {
                cerr << "\n\t\t\t\t\tError: " << errorMessage << endl;
                sqlite3_free(errorMessage);
            } 
            else {
                cout << "\n\t\t\t\t\tStudent Inserted Successfully!" << endl;
            }
        } 
        else if (choice == 0) {
            closed = true;
            cout << "\n\t\t\t\t\tSystem is closing..." << endl;
        }
        Sleep(2000);
    }
}

// Home Main Menu
void home(sqlite3* DB, Library l, Student s){
    bool exitProgram = false;

    while (!exitProgram) {
        system("cls");    // clears the console

        // Menu Display
        int val;
        cout << "\n\t\t\t\t\t-------------------------------" << endl;
        cout << "\t\t\t\t\t>> LIBRARY MANAGEMENT SYSTEM <<" << endl;
        cout << "\t\t\t\t\t-------------------------------" << endl;
        cout << "\n\t\t\t\t\t 1. Administration." << endl;
        cout << "\t\t\t\t\t 2. User." << endl;
        cout << "\t\t\t\t\t 0. Exit." << endl;
        cout << "\t\t\t\t\t.................................." << endl;
        cout << "\t\t\t\t\t>> Choice Options: [1/2/0] <<" << endl;
        cout << "\t\t\t\t\t.................................." << endl;
        cout << "\n\t\t\t\t\tEnter Your Choice: ";
        cin >> val;


        // Admin Menu Open
        if (val == 1) {
            Sleep(800);
            admin(DB, l, s);
        } else if (val == 2) {
            Sleep(1000);
            user(DB, l, s);
        } else if (val == 0) {
            exitProgram = true;
            cout << "\n\t\t\t\t\tGood Luck!" << endl;
            Sleep(1000);
            system("cls");
        }
    }
}

// Driver Main Function
int main() {
    sqlite3* DB;
    int exit = sqlite3_open("library.db", &DB);
    
    if (exit) {
        cerr << "\n\t\t\t\t\tError opening database: " << sqlite3_errmsg(DB) << endl;
        return -1;
    } 
    else {
        cout << "\n\t\t\t\t\tLogged In!" << endl;
    }

    Student s;
    Library l;

    // Create tables if they don't exist
    initializeDatabase(DB);

    Sleep(1000);
    
    home(DB,l,s);

    sqlite3_close(DB);
    return 0;
}


// Defintion of sqlite3_exec Function
// int sqlite3_exec(
//   sqlite3 *db,              /* An open database */
//   const char *sql,          /* SQL statement to execute */
//   int (*callback)(void*,int,char**,char**), /* Callback function */
//   void *arg,                /* First argument to callback */
//   char **errmsg             /* Error msg written here */
// );

// Defintion of sqlite3_prepare_v2 Function
// int sqlite3_prepare_v2(
//   sqlite3 *db,                /* An open database connection */
//   const char *sql,            /* SQL statement to prepare */
//   int sql_length,             /* Length of the SQL statement in bytes */
//   sqlite3_stmt **stmt,        /* Output parameter to receive the prepared statement */
//   const char **tail           /* Pointer to the first unused portion of the SQL statement */
// );
