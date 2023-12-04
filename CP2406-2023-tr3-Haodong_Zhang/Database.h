#pragma once

#include <iostream>
#include <vector>
#include "Employee.h"

namespace Records
{
    const int kFirstEmployeeNumber = 1000;

    class Database
    {
    public:
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
        Employee& addEmployee(const std::string &firstName, const std::string &middleName,
                const std::string &lastName, const std::string &address, const Role role);

        /**
         * Get an employee by number.
         *
         * @param employeeNumber the employee number to check
         *
         * @return a reference to founded employee
         * @throws logic_error if not employee found
         */
        Employee& getEmployee(int employeeNumber);

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
        Employee& getEmployee(const std::string &firstName, const std::string &middleName,
                const std::string &lastName);

        /**
         * Display all employees.
         */
        void displayAll() const;

        /**
         * Display all hired employees.
         */
        void displayCurrent() const;
        /**
         * Display all former employees.
         */
        void displayFormer() const;
        /**
         * Generate employee database.
         */
        void generateDatabase();
        /**
         * Save employees to file.
         *
         * @param filename the path of data file.
         */
        void saveFile(const std::string &filename) const;
        /**
         * Load employees from file.
         *
         * @param filename the path of data file.
         */
        void loadFile(const std::string &filename);

        /**
         * Search employees.
         *
         * @param key the searching keyword
         * @return a vector of found employees
         */
        std::vector<Employee> search(const std::string &key) const;

        /**
         * Save login ids and passwords to file.
         *
         * @param filename the path of data file.
         */
        void saveLogin(const std::string &filename) const;

        /**
         * Load login ids and passwords from file.
         *
         * @param filename the path of data file.
         */
        void loadLogin(const std::string &filename);
    private:
        std::vector<Employee> mEmployees;
        int mNextEmployeeNumber = kFirstEmployeeNumber;
    };
}
