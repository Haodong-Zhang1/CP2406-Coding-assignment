#pragma once

#include <string>

namespace Records
{
    const int kDefaultStartingSalary = 30000;
    const int kMaximumStringLength = 100;

    enum Role
    {
        ManagerRole, EmployeeRole
    };

    class Employee
    {
    public:
        /**
         * Creates a new employee.
         *
         * @param firstName first name of new employee
         * @param middleName middle name of new employee
         * @param lastName last name of new employee
         * @param address address of new employee
         */
        Employee(const std::string &firstName, const std::string &middleName,
                const std::string &lastName, const std::string &address);

        /**
         * Promote this employee.
         *
         * @param raiseAmount the amount to raise
         */
        void promote(int raiseAmount = 1000);
        /**
         * Demote this employee.
         *
         * @param demeritAmount the amount to demote
         */
        void demote(int demeritAmount = 1000);
        /**
         * Hire this employee.
         */
        void hire(); // Hires or rehires the employee
        /**
         * Dismisses the employee
         */
        void fire(); // Dismisses the employee
        /**
         *  Outputs employee info to console
         */
        void display() const; // Outputs employee info to console

        // Getters and setters
        void setFirstName(const std::string &firstName);
        const std::string& getFirstName() const;

        void setLastName(const std::string &lastName);
        const std::string& getLastName() const;

        void setEmployeeNumber(int employeeNumber);
        int getEmployeeNumber() const;

        void setSalary(int newSalary);
        int getSalary() const;

        bool isHired() const;

        void setMiddleName(const std::string &middleName);
        const std::string& getMiddleName() const;

        void setAddress(const std::string &address);
        const std::string& getAddress() const;

        void setLoginInfo(const std::string &loginId, const std::string &password);
        const std::string& getLoginId() const;
        const std::string& getPassword() const;
        void setPassword(const std::string &password);

        Role getRole() const;
        void setRole(Role role);
    private:
        std::string mFirstName; //first name
        std::string mMiddleName; //middle name
        std::string mLastName; //last name
        std::string mAddress; //address
        int mEmployeeNumber = -1; //number of employee
        int mSalary = kDefaultStartingSalary; //salary of employee
        bool mHired = false; //is hired or not

        std::string mLoginId;
        std::string mPassword;

        Role role;
    };
}

