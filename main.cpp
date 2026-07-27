#include <iostream>
#include <string>
using namespace std;

const int MAX_CARS = 50;
const int MAX_CUSTOMERS = 50;
const int ADMIN_PASSWORD = 2006;

// ================= ABSTRACT CLASS =================
class Vehicle
{
protected:
    int carID;
    string brand;
    string model;
    string type;
    float dailyRent;
    bool available;

public:
    Vehicle()
    {
        available = true;
    }

    virtual void displayCar() = 0;

    int getCarID()
    {
        return carID;
    }

    float getRent()
    {
        return dailyRent;
    }

    bool isCarAvailable()
    {
        return available;
    }

    void setAvailability(bool status)
    {
        available = status;
    }

    string getCarName()
    {
        return brand + " " + model;
    }
};

// ================= CAR CLASS =================
class Car : public Vehicle
{
public:
    Car() {}

    Car(int id, string b, string m, string t, float rent)
    {
        carID = id;
        brand = b;
        model = m;
        type = t;
        dailyRent = rent;
        available = true;
    }

    void addCar()
    {
        cout << "\n===== ADD NEW CAR =====\n";

        cout << "Enter Car ID: ";
        cin >> carID;

        cin.ignore();

        cout << "Enter Brand Name: ";
        getline(cin, brand);

        cout << "Enter Model Name: ";
        getline(cin, model);

        cout << "Enter Type: ";
        getline(cin, type);

        cout << "Enter Daily Rent: ";
        cin >> dailyRent;

        available = true;

        cout << "\nCar Added Successfully!\n";
    }

    void displayCar()
    {
        cout << "\nCar ID: " << carID;
        cout << "\nBrand: " << brand;
        cout << "\nModel: " << model;
        cout << "\nType: " << type;
        cout << "\nRent Per Day: " << dailyRent;

        if (available)
            cout << "\nStatus: Available\n";
        else
            cout << "\nStatus: Rented\n";

        cout << "---------------------------\n";
    }
};

// ================= CUSTOMER CLASS =================
class Customer
{
private:
    string name;
    int carID;
    int days;
    float bill;

public:
    void set(string n, int id, int d, float b)
    {
        name = n;
        carID = id;
        days = d;
        bill = b;
    }

    void show()
    {
        cout << "\n===== RENTAL RECORD =====\n";
        cout << "Customer Name: " << name << endl;
        cout << "Car ID: " << carID << endl;
        cout << "Days: " << days << endl;
        cout << "Total Bill: " << bill << endl;
        cout << "==========================\n";
    }
};

// ================= RENTAL SYSTEM =================
class RentalSystem
{
private:
    Car cars[MAX_CARS];
    Customer customers[MAX_CUSTOMERS];

    int totalCars;
    int totalCustomers;

public:
    RentalSystem()
    {
        totalCars = 0;
        totalCustomers = 0;

        loadCars();
    }

    void loadCars()
    {
        cars[totalCars++] = Car(101, "Toyota", "Corolla", "Sedan", 5000);
        cars[totalCars++] = Car(102, "Honda", "Civic", "Sedan", 7000);
        cars[totalCars++] = Car(103, "Suzuki", "Alto", "Hatchback", 3000);
    }

    // ================= MAIN MENU =================
    void mainMenu()
    {
        int choice;

        do
        {
            cout << "\n===== CAR RENTAL SYSTEM =====\n";
            cout << "1. Admin Panel\n";
            cout << "2. Customer Panel\n";
            cout << "0. Exit\n";

            cout << "Enter Choice: ";
            cin >> choice;

            if (choice == 1)
            {
                adminLogin();
            }
            else if (choice == 2)
            {
                customerMenu();
            }

        } while (choice != 0);
    }

    // ================= ADMIN LOGIN =================
    void adminLogin()
    {
        int pass;

        cout << "\n===== ADMIN LOGIN =====\n";
        cout << "Enter Password: ";
        cin >> pass;

        if (pass == ADMIN_PASSWORD)
        {
            adminMenu();
        }
        else
        {
            cout << "\nWrong Password!\n";
        }
    }

    // ================= ADMIN MENU =================
    void adminMenu()
    {
        int choice;

        do
        {
            cout << "\n===== ADMIN PANEL =====\n";
            cout << "1. Add Car\n";
            cout << "2. View Cars\n";
            cout << "3. View Rentals\n";
            cout << "4. View Available Cars\n";
            cout << "0. Back\n";

            cout << "Enter Choice: ";
            cin >> choice;

            if (choice == 1)
            {
                cars[totalCars].addCar();
                totalCars++;
            }
            else if (choice == 2)
            {
                for (int i = 0; i < totalCars; i++)
                {
                    cars[i].displayCar();
                }
            }
            else if (choice == 3)
            {
                showRentals();
            }
            else if (choice == 4)
            {
                showAvailableCars();
            }

        } while (choice != 0);
    }

    // ================= CUSTOMER MENU =================
    void customerMenu()
    {
        int choice;

        do
        {
            cout << "\n===== CUSTOMER PANEL =====\n";
            cout << "1. View Available Cars\n";
            cout << "2. Rent Car\n";
            cout << "3. Return Car\n";
            cout << "4. View Rentals\n";
            cout << "0. Back\n";

            cout << "Enter Choice: ";
            cin >> choice;

            switch (choice)
            {
            case 1:
                showAvailableCars();
                break;

            case 2:
                rentCar();
                break;

            case 3:
                returnCar();
                break;

            case 4:
                showRentals();
                break;
            }

        } while (choice != 0);
    }

    // ================= SHOW AVAILABLE CARS =================
    void showAvailableCars()
    {
        cout << "\n===== AVAILABLE CARS =====\n";

        for (int i = 0; i < totalCars; i++)
        {
            if (cars[i].isCarAvailable())
            {
                cars[i].displayCar();
            }
        }
    }

    // ================= FIND CAR =================
    int findCar(int id)
    {
        for (int i = 0; i < totalCars; i++)
        {
            if (cars[i].getCarID() == id)
            {
                return i;
            }
        }

        return -1;
    }

    // ================= RENT CAR =================
    void rentCar()
    {
        string name;
        int id;
        int days;

        cin.ignore();

        cout << "Enter Customer Name: ";
        getline(cin, name);

        showAvailableCars();

        cout << "Enter Car ID: ";
        cin >> id;

        int pos = findCar(id);

        if (pos == -1 || !cars[pos].isCarAvailable())
        {
            cout << "Car Not Available!\n";
            return;
        }

        cout << "Enter Number of Days: ";
        cin >> days;

        float bill = days * cars[pos].getRent();

        customers[totalCustomers].set(name, id, days, bill);

        totalCustomers++;

        cars[pos].setAvailability(false);

        // ===== BILL =====
        cout << "\n========== RENTAL BILL ==========\n";
        cout << "Customer Name : " << name << endl;
        cout << "Car Rented    : " << cars[pos].getCarName() << endl;
        cout << "Days          : " << days << endl;
        cout << "Rent Per Day  : " << cars[pos].getRent() << endl;
        cout << "---------------------------------\n";
        cout << "TOTAL BILL    : " << bill << endl;
        cout << "=================================\n";
    }

    // ================= RETURN CAR =================
    void returnCar()
    {
        int id;

        cout << "Enter Car ID to Return: ";
        cin >> id;

        int pos = findCar(id);

        if (pos != -1)
        {
            cars[pos].setAvailability(true);

            cout << "Car Returned Successfully!\n";
        }
        else
        {
            cout << "Invalid Car ID!\n";
        }
    }

    // ================= SHOW RENTALS =================
    void showRentals()
    {
        for (int i = 0; i < totalCustomers; i++)
        {
            customers[i].show();
        }
    }
};

// ================= MAIN =================
int main()
{
    RentalSystem system;

    system.mainMenu();

    return 0;
}