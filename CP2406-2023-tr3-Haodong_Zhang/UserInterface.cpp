#include <iostream>
#include <stdexcept>
#include <exception>
#include <cstring>
#include "Database.h"
#include "Logger.h"

using namespace std;
using namespace Records;

#define log(...) Logger::log(__func__, "(): ", __VA_ARGS__)

/**
 * display manager's menu.
 */
int displayMenu();
/**
 * Hire an employee.
 *
 * @param db the reference to database
 */
void doHire(Database &db);
/**
 * Fire an employee.
 *
 * @param db the reference to database
 */
void doFire(Database &db);
/**
 * Promote an employee.
 *
 * @param db the reference to database
 */
void doPromote(Database &db);
/**
 * Save employees to file.
 *
 * @param db the reference to database
 */
void doSaveFile(Database &db);
/**
 * Load employees from file.
 *
 * @param db the reference to database
 */
void doLoadFile(Database &db);
/**
 * Edit an employee.
 *
 * @param db the reference to database
 */
void doEdit(Database &db);
/**
 * Search employees by first name, middle name, last name and address.
 *
 * @param db the reference to database
 */
void doSearch(Database &db);
/**
 * Create login id and password for an employee.
 *
 * @param db the reference to database
 */
void doCreateLogin(Database &db);
/**
 * Edit login id and password for an employee.
 *
 * @param db the reference to database
 */
void doEditLogin(Database &db);
/**
 * Delete login id and password for an employee.
 *
 * @param db the reference to database
 */
void doDeleteLogin(Database &db);
/**
 * Save login ids and passwords to file.
 *
 * @param db the reference to database
 */
void doSaveLogin(Database &db);
/**
 * Load login ids and passwords from file.
 *
 * @param db the reference to database
 */
void doLoadLogin(Database &db);
/**
 * Show manager's menu.
 *
 * @param db the reference to database
 */
void showManagerMenu(Database &db);
/**
 * Check if debug mode is set.
 *
 * @param argc the number of command line arguments
 * @param argv the string array for all arguments
 */
bool isDebugSet(int argc, char *argv[]);

/**
 * Main function.
 *
 * @param argc the number of command line arguments
 * @param argv the string array for all arguments
 */
int main(int argc, char *argv[])
{
    Database employeeDB;
    int selection;

    //enable logger is "-d" is set.
    if (isDebugSet(argc, argv))
    {
        Logger::enableLogging(true);
        Logger::enableConsoleLogging(true);
    }

    while (true)
    {
        cout << endl;
        cout << "Login" << endl;
        cout << "-----------------" << endl;
        cout << "1) Root Manager" << endl;
        cout << "2) Login" << endl;
        cout << "0) Quit" << endl;
        cout << endl;
        cout << "---> ";

        cin >> selection;
        cin.ignore(kMaximumStringLength, '\n');

        if (selection == 1)
        {
            log("login as root manager");
            showManagerMenu(employeeDB);
        }
        else if (selection == 2)
        {

            int employeeNumber;
            string id;
            string password;

            cout << "Employee number? ";
            cin >> employeeNumber;
            cin.ignore(kMaximumStringLength, '\n');

            try
            {
                Employee &emp = employeeDB.getEmployee(employeeNumber);

                cout << "Login ID? ";
                cin >> id;
                cin.ignore(kMaximumStringLength, '\n');

                cout << "Password? ";
                cin >> password;
                cin.ignore(kMaximumStringLength, '\n');

                if (emp.getLoginId() == id && emp.getPassword() == password)
                {
                    if (emp.getRole() == Role::ManagerRole)
                    {
                        log("login as manager");
                        showManagerMenu(employeeDB);
                    }
                    else
                    {
                        log("login as employee");
                        emp.display();
                    }
                }
                else
                {
                    cout << "Login ID or password is invalid." << endl;
                }

            } catch (const std::logic_error &exception)
            {
                cerr << "Unable to find employee: " << exception.what() << endl;
            }
        }
        else if (selection == 0)
        {
            log("quit system");
            break;
        }
    }

    return 0;
}

bool isDebugSet(int argc, char *argv[])
{
    for (int i
    { 0 }; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            return true;
        }
    }
    return false;
}

/**
 * display manager's menu.
 */
int displayMenu()
{
    // Note:
    //		One important note is that this code assumes that the user will
    //		"play nice" and type a number when a number is requested.
    //		When you read about I/O in Chapter 13, you will learn how to
    //		protect against bad input.

    int selection;

    cout << endl;
    cout << "Employee Database" << endl;
    cout << "-----------------" << endl;
    cout << "1) Hire a new employee" << endl;
    cout << "2) Fire an employee" << endl;
    cout << "3) Promote an employee" << endl;
    cout << "4) List all employees" << endl;
    cout << "5) List all current employees" << endl;
    cout << "6) List all former employees" << endl;
    cout << "7) Generate new database" << endl;
    cout << "8) Save database to file" << endl;
    cout << "9) Load database from file" << endl;
    cout << "10) Edit employee" << endl;
    cout << "11) Search employee" << endl;
    cout << "12) Create login ID and password" << endl;
    cout << "13) Edit login ID and password" << endl;
    cout << "14) Delete login ID and password" << endl;
    cout << "15) Save login IDs and passwords" << endl;
    cout << "16) Load login IDs and passwords" << endl;
    cout << "0) Quit" << endl;
    cout << endl;
    cout << "---> ";

    cin >> selection;
    cin.ignore(kMaximumStringLength, '\n');

    return selection;
}

/**
 * Show manager's menu.
 *
 * @param db the reference to database
 */
void showManagerMenu(Database &employeeDB)
{
    bool done = false;
    while (!done)
    {
        int selection = displayMenu();
        switch (selection)
        {
        case 0:
            log("manager quit menu");
            done = true;
            break;
        case 1:
            log("Hire a new employee");
            doHire(employeeDB);
            break;
        case 2:
            log("Fire an employee");
            doFire(employeeDB);
            break;
        case 3:
            log("Promote an employee");
            doPromote(employeeDB);
            break;
        case 4:
            employeeDB.displayAll();
            break;
        case 5:
            employeeDB.displayCurrent();
            break;
        case 6:
            employeeDB.displayFormer();
            break;
        case 7:
            log("Generate new database");
            employeeDB.generateDatabase();
            cout << "database generated." << endl;
            break;
        case 8:
            doSaveFile(employeeDB);
            break;
        case 9:
            doLoadFile(employeeDB);
            break;
        case 10:
            doEdit(employeeDB);
            break;
        case 11:
            doSearch(employeeDB);
            break;
        case 12:
            doCreateLogin(employeeDB);
            break;
        case 13:
            doEditLogin(employeeDB);
            break;
        case 14:
            doDeleteLogin(employeeDB);
            break;
        case 15:
            doSaveLogin(employeeDB);
            break;
        case 16:
            doLoadLogin(employeeDB);
            break;
        default:
            cerr << "Unknown command." << endl;
            break;
        }
    }
}

/**
 * Hire an employee.
 *
 * @param db the reference to database
 */
void doHire(Database &db)
{
    string firstName;
    string middleName;
    string lastName;
    string address;
    string roleOption;
    Role role;

    cout << "First name? ";
    cin >> firstName;
    cin.ignore(kMaximumStringLength, '\n');

    cout << "Middle name? ";
    cin >> middleName;
    cin.ignore(kMaximumStringLength, '\n');

    cout << "Last name? ";
    cin >> lastName;
    cin.ignore(kMaximumStringLength, '\n');

    cout << "Address? ";
    getline(cin, address);

    cout << "Role?(1-Manager, 2-Employee) ";
    cin >> roleOption;
    cin.ignore(kMaximumStringLength, '\n');
    role = roleOption == "1" ? Role::ManagerRole : Role::EmployeeRole;

    db.addEmployee(firstName, middleName, lastName, address, role);
    cout << "New employee " << firstName << ", " << middleName << ", " << lastName << "\n    "
            << address << " added." << endl;

    log("New employee ", firstName, ", ", middleName, ", ", lastName, "\n    ", address, " added.");
}

/**
 * Fire an employee.
 *
 * @param db the reference to database
 */
void doFire(Database &db)
{
    int employeeNumber;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cin.ignore(kMaximumStringLength, '\n');

    try
    {
        Employee &emp = db.getEmployee(employeeNumber);
        emp.fire();
        cout << "Employee " << employeeNumber << " terminated." << endl;
        log("Employee ", employeeNumber, " terminated.");
    } catch (const std::logic_error &exception)
    {
        cerr << "Unable to terminate employee: " << exception.what() << endl;
        log("Unable to terminate employee: ", exception.what());
    }
}
/**
 * Promote an employee.
 *
 * @param db the reference to database
 */
void doPromote(Database &db)
{
    int employeeNumber;
    int raiseAmount;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cin.ignore(kMaximumStringLength, '\n');

    cout << "How much of a raise? ";
    cin >> raiseAmount;
    cin.ignore(kMaximumStringLength, '\n');

    try
    {
        Employee &emp = db.getEmployee(employeeNumber);
        emp.promote(raiseAmount);

        cout << "Employee " << employeeNumber << " promoted." << endl;
        log("Employee ", employeeNumber, " promoted.");
    } catch (const std::logic_error &exception)
    {
        cerr << "Unable to promote employee: " << exception.what() << endl;
        log("Unable to promote employee: ", exception.what());
    }
}

/**
 * Save database to a text file.
 *
 * @param db the reference to database
 */
void doSaveFile(Database &db)
{
    string filename;

    cout << "Filename? ";
    cin >> filename;
    cin.ignore(kMaximumStringLength, '\n');

    db.saveFile(filename);

    cout << "employees saved to " << filename << endl;
    log("employees saved to ", filename);
}

/**
 * Load database from a text file.
 *
 * @param db the reference to database
 */
void doLoadFile(Database &db)
{
    string filename;

    cout << "Filename? ";
    cin >> filename;
    cin.ignore(kMaximumStringLength, '\n');

    try
    {
        db.loadFile(filename);

        log("load employees from", filename);
    } catch (std::logic_error &exception)
    {
        cerr << "Unable to load file: " << exception.what() << endl;
        log("Unable to load file: ", exception.what());
    }
}

/**
 * Edit an employee.
 *
 * @param db the reference to database
 */
void doEdit(Database &db)
{
    int employeeNumber;
    string address;
    int salary;
    bool hired;
    string hired_str;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cin.ignore(kMaximumStringLength, '\n');

    try
    {
        Employee &emp = db.getEmployee(employeeNumber);

        cout << "Address? ";
        getline(cin, address);

        cout << "Salary? ";
        cin >> salary;
        cin.ignore(kMaximumStringLength, '\n');

        cout << "Hired?(y/n) ";
        cin >> hired_str;
        cin.ignore(kMaximumStringLength, '\n');
        hired = hired_str == "y" || hired_str == "Y";

        emp.setAddress(address);
        emp.setSalary(salary);
        if (hired)
        {
            emp.hire();
        }
        else
        {
            emp.fire();
        }

        cout << "Employee " << employeeNumber << " updated." << endl;
        log("Employee ", employeeNumber, " updated.");
    } catch (const std::logic_error &exception)
    {
        cerr << "Unable to find employee: " << exception.what() << endl;
        log("Unable to find employee: ", exception.what());
    }
}

/**
 * Search employees by first name, middle name, last name and address.
 *
 * @param db the reference to database
 */
void doSearch(Database &db)
{
    string key;

    cout << "Search key? ";
    cin >> key;
    cin.ignore(kMaximumStringLength, '\n');

    vector<Employee> result = db.search(key);
    for (const auto &emp : result)
    {
        emp.display();
    }
    cout << result.size() << " records found." << endl;
}

/**
 * Create login id and password for an employee.
 *
 * @param db the reference to database
 */
void doCreateLogin(Database &db)
{
    int employeeNumber;
    string id;
    string password;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cin.ignore(kMaximumStringLength, '\n');

    try
    {
        Employee &emp = db.getEmployee(employeeNumber);

        cout << "Login ID? ";
        cin >> id;
        cin.ignore(kMaximumStringLength, '\n');

        cout << "Password? ";
        cin >> password;
        cin.ignore(kMaximumStringLength, '\n');

        emp.setLoginInfo(id, password);

        cout << "Login ID and password for Employee " << employeeNumber << " created." << endl;
        log("Login ID and password for Employee ", employeeNumber, " created.");
    } catch (const std::logic_error &exception)
    {
        cerr << "Unable to find employee: " << exception.what() << endl;
        log("Unable to find employee: ", exception.what());
    }
}

/**
 * Edit login id and password for an employee.
 *
 * @param db the reference to database
 */
void doEditLogin(Database &db)
{
    int employeeNumber;
    string password;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cin.ignore(kMaximumStringLength, '\n');

    try
    {
        Employee &emp = db.getEmployee(employeeNumber);

        if (emp.getLoginId() == "")
        {
            cout << "Employee " << employeeNumber << " has no login ID." << endl;
            log("Employee ", employeeNumber, " has no login ID.");
        }
        else
        {
            cout << "Password? ";
            cin >> password;
            cin.ignore(kMaximumStringLength, '\n');

            emp.setPassword(password);

            cout << "Login ID and password for Employee " << employeeNumber << " edited." << endl;
            log("Login ID and password for Employee ", employeeNumber, " edited.");
        }
    } catch (const std::logic_error &exception)
    {
        cerr << "Unable to find employee: " << exception.what() << endl;
        log("Unable to find employee: ", exception.what());
    }
}

/**
 * Delete login id and password for an employee.
 *
 * @param db the reference to database
 */
void doDeleteLogin(Database &db)
{
    int employeeNumber;

    cout << "Employee number? ";
    cin >> employeeNumber;
    cin.ignore(kMaximumStringLength, '\n');

    try
    {
        Employee &emp = db.getEmployee(employeeNumber);
        emp.setLoginInfo("", "");

        cout << "Login ID and password for Employee " << employeeNumber << " deleted." << endl;
        log("Login ID and password for Employee ", employeeNumber, " deleted.");
    } catch (const std::logic_error &exception)
    {
        cerr << "Unable to find employee: " << exception.what() << endl;
        log("Unable to find employee: ", exception.what());
    }
}

/**
 * Save login ids and passwords to file.
 *
 * @param db the reference to database
 */
void doSaveLogin(Database &db)
{
    string filename;

    //prompt user to enter filename.
    cout << "Filename? ";
    cin >> filename;
    cin.ignore(kMaximumStringLength, '\n');

    db.saveLogin(filename);

    cout << "login ids and passwords saved to " << filename << endl;
    log("login ids and passwords saved to ", filename);
}

/**
 * Load login ids and passwords from file.
 *
 * @param db the reference to database
 */
void doLoadLogin(Database &db)
{
    string filename;

    //prompt user to enter filename.
    cout << "Filename? ";
    cin >> filename;
    cin.ignore(kMaximumStringLength, '\n');

    try
    {
        db.loadLogin(filename);

        log("load login ids and passwords from ", filename);
    } catch (std::logic_error &exception)
    {
        cerr << "Unable to load file: " << exception.what() << endl;
        log("Unable to load file: ", exception.what());
    }
}

