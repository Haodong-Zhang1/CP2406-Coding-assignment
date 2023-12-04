#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <fstream>

#include "Database.h"

using namespace std;

namespace Records
{

    /**
     * Add a new employee to database.
     *
     * @param firstName first name of new employee
     * @param middleName middle name of new employee
     * @param lastName last name of new employee
     * @param address address of new employee
     * @param role role of employee
     *
     * @return a reference to added employee
     */
    Employee& Database::addEmployee(const string &firstName, const string &middleName,
            const string &lastName, const string &address, const Role role)
    {
        Employee theEmployee(firstName, middleName, lastName, address);
        theEmployee.setRole(role);
        theEmployee.setEmployeeNumber(mNextEmployeeNumber++);
        theEmployee.hire();
        mEmployees.push_back(theEmployee);

        return mEmployees[mEmployees.size() - 1];
    }

    /**
     * Get an employee by number.
     *
     * @param employeeNumber the employee number to check
     *
     * @return a reference to founded employee
     * @throws logic_error if not employee found
     */
    Employee& Database::getEmployee(int employeeNumber)
    {
        for (auto &employee : mEmployees)
        {
            if (employee.getEmployeeNumber() == employeeNumber)
            {
                return employee;
            }
        }
        throw logic_error("No employee found.");
    }

    /**
     * Get an employee by name.
     *
     * @param firstName first name of new employee
     * @param middleName middle name of new employee
     * @param lastName last name of new employee
     *
     * @return a reference to founded employee
     * @throws logic_error if not employee found
     */
    Employee& Database::getEmployee(const string &firstName, const string &middleName,
            const string &lastName)
    {
        for (auto &employee : mEmployees)
        {
            if (employee.getFirstName() == firstName && employee.getMiddleName() == middleName
                    && employee.getLastName() == lastName)
            {
                return employee;
            }
        }
        throw logic_error("No employee found.");
    }

    /**
     * Display all employees.
     */
    void Database::displayAll() const
    {
        for (const auto &employee : mEmployees)
        {
            employee.display();
        }
    }

    /**
     * Display all hired employees.
     */
    void Database::displayCurrent() const
    {
        for (const auto &employee : mEmployees)
        {
            if (employee.isHired())
                employee.display();
        }
    }

    /**
     * Display all former employees.
     */
    void Database::displayFormer() const
    {
        for (const auto &employee : mEmployees)
        {
            if (!employee.isHired())
                employee.display();
        }
    }

    /**
     * Generate employee database.
     */
    void Database::generateDatabase()
    {
        //library of first names
        string firstNames[20] =
        { "Arias", "Austin", "Baca", "Baker", "Colin", "Colter", "Duke", "Duran", "Eder", "Ellis",
                "Fait", "Felix", "Gale", "Garcia", "Haasl", "Hale", "Ingle", "Islam", "James",
                "Jasso" };
        //library of middle names
        string middleNames[20] =
        { "Nicole", "Elizabeth", "Nicholas", "Zoe", "June", "Barrett", "Charity", "Jade", "Ashton",
                "Danielle", "Marie", "Rose", "John", "Riley", "Alan", "Leigh", "Mae", "Grace",
                "Kurt", "Xavier" };
        //library of last names
        string lastNames[20] =
        { "Ally", "Alex", "Lyla", "Kylia", "Bryce", "Daniela", "Jacob", "Reily", "Micaela",
                "Breonia", "Miranda", "Jessica", "Jase", "Samuel", "Kara", "Dalton", "Casey",
                "Julia", "Alexa", "Jim" };
        //library of addresses
        string addresses[20] =
        { "6348 Finn Hill, Beaubury, Australian Capital Territory 1926, Australia",
                "4223 Hand Parkway, North Lauderdale, Australian Capital Territory 0635, Australia",
                "05799 Mia Parade, Port Jade, Australian Capital Territory 2299, Australia",
                "6011 Feil Estate Dr, West Lily, New South Wales 0845, Australia",
                "734 Heathcote Drive, Goldnertown, Northern Territory 8482, Australia",
                "1810 Hoppe Estate Dr, New Jade, Victoria 6984, Australia",
                "7562 Johns Summit, Arlington, Australian Capital Territory 5477, Australia",
                "14379 Christopher Track, Sophieberg, South Australia 2038, Australia",
                "813 Goodwin Parade, Montebello, South Australia 6774, Australia",
                "259 James Street, Loveland, Australian Capital Territory 5154, Australia",
                "9974 Reilly Track, South Williamfurt, Queensland 3502, Australia",
                "604 Sebastian Crescent, Hunterville, Western Australia 4609, Australia",
                "005 Kulas Manor, Woodbury, Western Australia 7947, Australia",
                "27507 Hoppe Plaza, Nicholasland, Australian Capital Territory 7209, Australia",
                "42243 Alyssa Plaza, Walshberg, Australian Capital Territory 0141, Australia",
                "4072 Sarah Junction, Reesborough, Tasmania 0640, Australia",
                "134 Alex Avenue, Camarillo, Australian Capital Territory 6419, Australia",
                "3826 Amelie Drive, Aloha, Northern Territory 3632, Australia",
                "99023 Rose Manor, Lakewood, Queensland 2373, Australia",
                "90194 Willow Drive, Robinsonfurt, Victoria 5322, Australia" };

        //remove existing elements
        mEmployees.clear();
        mNextEmployeeNumber = kFirstEmployeeNumber;

        //generate 8000(20*20*20) employees
        for (int i = 0; i < 20; i++)
        {
            for (int j = 0; j < 20; j++)
            {
                for (int k = 0; k < 20; k++)
                {
                    int addrIndex = rand() % 20;
                    string firstName = firstNames[i];
                    string middleName = middleNames[j];
                    string lastName = lastNames[k];
                    string address = addresses[addrIndex];

                    Role role = addrIndex < 10 ? Role::ManagerRole : Role::EmployeeRole;
                    addEmployee(firstName, middleName, lastName, address, role);
                }
            }
        }
    }
    /**
     * Save employees to file.
     *
     * @param filename the path of data file.
     */
    void Database::saveFile(const std::string &filename) const
    {
        ofstream ofs(filename);
        for (const auto &employee : mEmployees)
        {
            ofs << employee.getEmployeeNumber() << " ";
            ofs << employee.getSalary() << " ";
            ofs << employee.isHired() << " ";
            ofs << employee.getFirstName() << " ";
            ofs << employee.getMiddleName() << " ";
            ofs << employee.getLastName() << " ";
            ofs << employee.getRole() << endl;
            ofs << employee.getAddress() << endl;
        }
        ofs.close();
    }
    /**
     * Load employees from file.
     *
     * @param filename the path of data file.
     */
    void Database::loadFile(const std::string &filename)
    {
        std::string firstName; //first name
        std::string middleName; //middle name
        std::string lastName; //last name
        std::string address; //address
        int employeeNumber = -1; //number of employee
        int salary = kDefaultStartingSalary; //salary of employee
        bool hired = false; //is hired or not
        int role;

        ifstream ifs(filename);
        if (ifs.is_open())
        {
            //remove existing elements
            mEmployees.clear();
            mNextEmployeeNumber = kFirstEmployeeNumber;

            while (ifs >> employeeNumber >> salary >> hired >> firstName >> middleName >> lastName
                    >> role)
            {
                ifs.ignore(kMaximumStringLength, '\n');
                getline(ifs, address);

                Employee theEmployee(firstName, middleName, lastName, address);
                theEmployee.setEmployeeNumber(employeeNumber);
                if (role == 0)
                {
                    theEmployee.setRole(Role::ManagerRole);
                }
                else
                {
                    theEmployee.setRole(Role::EmployeeRole);
                }
                theEmployee.setSalary(salary);
                if (hired)
                {
                    theEmployee.hire();
                }
                else
                {
                    theEmployee.fire();
                }

                mEmployees.push_back(theEmployee);

                if (employeeNumber >= mNextEmployeeNumber)
                {
                    mNextEmployeeNumber = employeeNumber + 1;
                }
            }
            ifs.close();
        }
        else
        {
            throw logic_error("Failed to open file.");
        }
    }

    static std::string toLower(const std::string &str)
    {
        std::string result;

        for (size_t i = 0; i < str.length(); i++)
        {
            char ch = str[i];
            ch = tolower(ch);
            result += ch;
        }
        return result;
    }
    /**
     * Search employees.
     *
     * @param key the searching keyword
     * @return a vector of found employees
     */
    std::vector<Employee> Database::search(const std::string &key) const
    {
        std::vector<Employee> result;
        string lower_key;

        lower_key = toLower(key);
        for (const auto &employee : mEmployees)
        {
            std::string info = employee.getFirstName() + employee.getMiddleName()
                    + employee.getLastName() + employee.getAddress();
            info = toLower(info);
            if (info.find(lower_key.c_str(), 0) != std::string::npos)
            {
                result.push_back(employee);
            }
        }
        return result;
    }
    /**
     * Save login ids and passwords to file.
     *
     * @param filename the path of data file.
     */
    void Database::saveLogin(const std::string &filename) const
    {
        ofstream ofs(filename);
        for (const auto &employee : mEmployees)
        {
            if (employee.getLoginId() != "")
            {
                ofs << employee.getEmployeeNumber() << " ";
                ofs << employee.getLoginId() << " ";
                ofs << employee.getPassword() << endl;
            }
        }
        ofs.close();
    }
    /**
     * Load login ids and passwords from file.
     *
     * @param filename the path of data file.
     */
    void Database::loadLogin(const std::string &filename)
    {
        int employeeNumber;
        std::string loginId;
        std::string password;

        ifstream ifs(filename);
        if (ifs.is_open())
        {
            while (ifs >> employeeNumber >> loginId >> password)
            {
                try
                {
                    Employee &emp = getEmployee(employeeNumber);
                    emp.setLoginInfo(loginId, password);
                } catch (const std::logic_error &exception)
                {
                    cerr << "Unable to find employee: " << exception.what() << endl;
                }
            }
            ifs.close();
        }
        else
        {
            throw logic_error("Failed to open file.");
        }
    }

}
