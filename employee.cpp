#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Employee{
    private:
        string firstName , lastName , socialSecurityNumber;
    public:
        Employee( const string & , const string & , const string & );

        void setFirstName( const string & );
        string getFirstName() const;
        void setLastName( const string & );
        string getLastName() const;
        void setSocialSecurityNumber( const string & );
        string getSocialSecurityNumber() const;

        virtual double earnings() const = 0;
        virtual void print() const;
};

//Employee constructor
Employee::Employee( const string &first , const string &last , const string &ssn )
    : firstName( first ) , lastName( last ) , socialSecurityNumber( ssn ){

}

//set first name
void Employee::setFirstName( const string &first ){
    firstName = first;
}

//get first name
string Employee::getFirstName() const{
    return firstName;
}

//set last name
void Employee::setLastName( const string &last ){
    lastName = last;
}

//get last name
string Employee::getLastName() const{
    return lastName;
}

//set social security number
void Employee::setSocialSecurityNumber( const string &ssn ){
    socialSecurityNumber = ssn;
}

//get social security number
string Employee::getSocialSecurityNumber() const{
    return socialSecurityNumber;
}

//print Employee's information
void Employee::print() const{
    cout << getFirstName() << ' ' << getLastName() << "\nsocial security number: " << getSocialSecurityNumber();
}

class SalariedEmployee : public Employee{
    private:
        double weeklySalary;
    public:
        SalariedEmployee( const string & , const string & , const string & , double = 0.0 );

        void setWeeklySalary( double );
        double getWeeklySalary() const;

        virtual double earnings() const;
        virtual void print() const;
};

//SalariedEmployee constructor will validate weekly salary
SalariedEmployee::SalariedEmployee( const string &first , const string &last , const string &ssn , double salary )
    :Employee( first , last , ssn ){
        setWeeklySalary( salary );
}

//set weekly salary, and validate the weekly salary to ensure that it is greater than or equal to 0
void SalariedEmployee::setWeeklySalary( double salary ){
    weeklySalary = ( salary < 0.0 ) ? 0.0 : salary;
}

//get weekly salary
double SalariedEmployee::getWeeklySalary() const{
    return weeklySalary;
}

//calculate earnings, override pure virtual function earings in Employee
double SalariedEmployee::earnings() const{
    return getWeeklySalary();
}

//print SalariedEmployee's information
void SalariedEmployee::print() const{
    cout << "salaried employee: ";
    Employee::print();
    cout << "\nweekly salary: " << getWeeklySalary();
}

class HourEmployee : public Employee{
    private:
        double wage , hours;
    public:
        static const int hoursPerWeek = 168;

        HourEmployee( const string & , const string & , const string & , double = 0.0 , double = 0.0 );
        
        void setWage( double );
        double getWage() const;
        void setHours( double );
        double getHours() const;

        virtual double earnings() const;
        virtual void print() const;
};

//HourEmployee constructor will validate hourly wage and hours worked
HourEmployee::HourEmployee( const string &first , const string &last , const string &ssn , double hourlyWage , double hoursWorked )
    :Employee( first , last , ssn ){
        setWage( hourlyWage );
        setHours( hoursWorked );
}

//set wage, and validate the wage to ensure that it is greater than or equal to 0
void HourEmployee::setWage( double hourlyWage ){
    wage = ( ( hourlyWage < 0.0 ) ? 0.0 : hourlyWage );
}

//get wage
double HourEmployee::getWage() const{
    return wage;
}

//set hours, and validate the hours to ensure that it is greater than or equal to 0 and smaller than hours per week
void HourEmployee::setHours( double hoursWorked ){
    hours = ( ( ( hoursWorked >= 0.0 ) && ( hoursWorked <= hoursPerWeek )) ? hoursWorked : 0.0 );
}

//get hours
double HourEmployee::getHours() const{
    return hours;
}

//calculate earnings, override pure virtual function earings in Employee
double HourEmployee::earnings() const{
    if ( getHours() <= 40 )
        return getWage() * getHours();
    else
        return 40 * getWage() + ( ( getHours() - 40 ) * getWage() * 1.5 );
}

//print HourEmployee's information
void HourEmployee::print() const{
    cout << "hourly employee: ";
    Employee::print();
    cout << "\nhourly salary: " << getWage() << ": hours worked: " << getHours();
}

class CommissionEmployee : public Employee{
    private:
        double grossSales , commissionRate;
    public:
        CommissionEmployee( const string & , const string & , const string & , double = 0.0 , double = 0.0 );

        void setCommissionRate( double );
        double getCommissionRate() const;
        void setGrossSales( double );
        double getGrossSales() const;

        virtual double earnings() const;
        virtual void print() const;
};

//CommissionEmployee constructor will validate gross sales and commission rate
CommissionEmployee::CommissionEmployee( const string &first , const string &last , const string &ssn , double sales , double rate )
    :Employee( first , last , ssn ){
        setGrossSales( sales );
        setCommissionRate( rate );
}

//set commission rate, and validate the commission rate to ensure that it is greater than or equal to 0 and smaller than 1
void CommissionEmployee::setCommissionRate( double rate ){
    commissionRate = ( ( rate > 0.0 && rate < 1.0 ) ? rate : 0.0 );
}

//get commission rate
double CommissionEmployee::getCommissionRate() const{
    return commissionRate;
}

//set gross sales, and validate the gross sales to ensure that it is greater than or equal to 0
void CommissionEmployee::setGrossSales( double sales ){
    grossSales = ( ( sales < 0.0 ) ? 0.0 : sales );
}

//get gross sales
double CommissionEmployee::getGrossSales() const{
    return grossSales;
}

//calculate earnings, override pure virtual function earings in Employee
double CommissionEmployee::earnings() const{
        return getCommissionRate() * getGrossSales();
}

//print CommissionEmployee's information
void CommissionEmployee::print() const{
    cout << "comission employee: ";
    Employee::print();
    cout << "\ngross sales: " << getGrossSales() << ": commission rate: " << getCommissionRate();
}

class BasePlusCommissionEmployee : public CommissionEmployee{
    private:
        double baseSalary;
    public:
        BasePlusCommissionEmployee( const string & , const string & , const string & , double = 0.0 , double = 0.0 , double = 0.0 );

        void setBaseSalary( double );
        double getBaseSalary() const;

        virtual double earnings() const;
        virtual void print() const;
};

//BasePlusCommissionEmployee constructor will validate base salary
BasePlusCommissionEmployee::BasePlusCommissionEmployee( const string &first , const string &last , const string &ssn , double sales , double rate , double salary )
    : CommissionEmployee( first , last , ssn , sales , rate ){
        setBaseSalary( salary );
}

//set base salary, and validate the base salary to ensure that it is greater than or equal to 0
void BasePlusCommissionEmployee::setBaseSalary( double salary ){
    baseSalary = ( ( salary < 0.0 ) ? 0.0 : salary );
}

//get base salary
double BasePlusCommissionEmployee::getBaseSalary() const{
    return baseSalary;
}

//calculate earnings, override pure virtual function earings in Employee
double BasePlusCommissionEmployee::earnings() const{
        return getBaseSalary() +  CommissionEmployee::earnings();
}

//print BasePlusCommissionEmployee's information
void BasePlusCommissionEmployee::print() const{
    cout << "base-salaried: ";
    CommissionEmployee::print();
    cout << "; base salary: " << getBaseSalary();
}

//call Employee virtual functions to print each Employee's information and earnings using dynamic binding
void EmployeePtr( const Employee * const EmployeePtr ){
    EmployeePtr->print();
    cout << "\nearned $" << EmployeePtr->earnings() << "\n" <<endl;
}

int main(){
//set floating-point output formatting
    cout << fixed << setprecision(2);

//create derived-class output formatting 
    SalariedEmployee s( "John" , "Smith" , "111-11-1111" , 800 );
    HourEmployee h( "Karen" , "Price" , "222-22-2222" , 16.75 , 40.00 );
    CommissionEmployee c( "Sue" , "Jones" , "333-33-3333" , 10000.00 , .06 );
    BasePlusCommissionEmployee b( "Bob" , "Lewis" , "444-44-4444" , 5000.00 , .04 , 300 );

//call EmplyeePtr function to print each Employee's information and then assign its address to EmployeePtr immediately
    EmployeePtr(&s);
    EmployeePtr(&h);
    EmployeePtr(&c);
    EmployeePtr(&b);
}