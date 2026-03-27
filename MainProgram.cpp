#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
using namespace std;

class Temperature {
private:
    double celsius_;

public:
    explicit Temperature(double celsius) {
        if(celsius< -273.15){
            throw invalid_argument("temperature cannot be less than absolute 0");
        }
        celsius_= celsius;   
    }
    double getCelsius() const {
        return celsius_;
    }
    double getFahrenheit() const {
        return celsius_ * 9 / 5 + 32;
    }
    void setCelsius(double celsius) {
        if(celsius< -273.15){
            throw invalid_argument("temperature cannot be less than absolute 0");
        }
        celsius_= celsius;   
    }
};

// --------------------------------------------------
// Class: BankAccount
// Represents a simple bank account.
// Invariants:
//   - balance must never be negative
//   - owner name must not be empty
// --------------------------------------------------
class BankAccount {
private:
    string owner_;
    double balance_;

public:
    BankAccount(const string& owner, double initialBalance) {
        if(initialBalance<0){
            throw invalid_argument ("balance cannot be less than 0");
        }
        if(owner.empty()){
            throw invalid_argument ("owner cannot be empty");
    }
    owner_ = owner;
    balance_ = initialBalance;
    }
    string getOwner() const {
        return owner_;
    }
    double getBalance() const {
        return balance_;
    }

    void deposit(double amount) {
        if(amount<=0){
            throw invalid_argument ("ammount cannot be less than or equal to 0");
        }
        balance_ += amount;
    }
    void withdraw(double amount) {
        if(amount<=0){
            throw invalid_argument ("ammount cannot be less than or equal to 0");
        }
        if(amount > balance_){
            throw runtime_error ("insufficient funds");
        }
        balance_ -= amount;
    }
    void transfer(BankAccount& other, double amount) {
        if(amount<=0){
            throw invalid_argument ("transfer cannot be less than or equal to 0");
        }
        if(amount > balance_){
            throw runtime_error ("insufficient funds");
        }
        withdraw(amount);
        other.deposit(amount);
    }
};

// --------------------------------------------------
// Class: Password
// Represents a password with strength rules.
// Invariants:
//   - password length must be >= 8
//   - password must contain at least one digit
// --------------------------------------------------
class Password {
private:
    string password_;

    // Helper: check if a string contains at least one digit
    static bool hasDigit(const string& s) {
        for (char c : s){
            if (c >= '0' && c <= '9'){
                return true;
            }
        }
        return false;
    }

    // Helper: validate password against all rules
    static void validate(const string& pwd) {
        // TODO: Check length >= 8 and hasDigit
        // Throw std::invalid_argument with descriptive message if invalid
    if (!hasDigit(pwd)){
        throw invalid_argument("need atleast 1 digit");
        }
    if (pwd.length() < 8){
        throw invalid_argument("need more than 8");
        }
    }

public:
    // Constructor: create a password.
    // Must pass validation.
    explicit Password(const string& pwd) {
        // TODO: Validate and set password_
        validate(pwd);
        password_=pwd; 
    }

    // Change password: old password must match, new must be valid.
    // Throw std::invalid_argument if oldPassword doesn't match
    // Throw std::invalid_argument if newPassword fails validation
    void change(const string& oldPassword, const string& newPassword) {
        // TODO: Implement
        if(oldPassword != password_){
            throw invalid_argument ("oldpassword is not equal to the password");
        }
        validate(newPassword);
        password_ = newPassword;
    }

    // Check if a given string matches the stored password.
    bool matches(const string& attempt) const {
        // TODO: Implement
        
        return attempt == password_;
    }

    // Return the length of the password (safe to expose)
    size_t getLength() const {
        // TODO: Implement
        
        return password_.length();
    }

    // NOTE: There is deliberately NO getPassword() method.
    // Exposing the raw password would break encapsulation.
};


// ================================
// MAIN FUNCTION
// ================================
int main() {
    cout << "=== Encapsulation and Invariants Lab ===" << endl;
    cout << endl;

    // --- Temperature Demo ---
    cout << "--- Temperature ---" << endl;
    try {
        Temperature t(100.0);
        cout << "Celsius: " << t.getCelsius() << endl;
        cout << "Fahrenheit: " << t.getFahrenheit() << endl;
        t.setCelsius(-40.0);
        cout << "Updated Celsius: " << t.getCelsius() << endl;
        cout << "Updated Fahrenheit: " << t.getFahrenheit() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    // Try invalid temperature
    try {
        Temperature bad(-300.0);
        cout << "This should not print!" << endl;
    } catch (const invalid_argument& e) {
        cout << "Caught expected error: " << e.what() << endl;
    }
    cout << endl;

    // --- BankAccount Demo ---
    cout << "--- BankAccount ---" << endl;
    try {
        BankAccount alice("Alice", 1000.0);
        BankAccount bob("Bob", 500.0);
        cout << alice.getOwner() << " balance: " << alice.getBalance() << endl;

        alice.deposit(200.0);
        cout << "After deposit: " << alice.getBalance() << endl;

        alice.transfer(bob, 300.0);
        cout << "After transfer:" << endl;
        cout << "  Alice: " << alice.getBalance() << endl;
        cout << "  Bob:   " << bob.getBalance() << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
    cout << endl;

    // --- Password Demo ---
    cout << "--- Password ---" << endl;
    try {
        Password pw("Secure99");
        cout << "Password length: " << pw.getLength() << endl;
        cout << "Matches 'wrong': " << pw.matches("wrong") << endl;
        cout << "Matches 'Secure99': " << pw.matches("Secure99") << endl;
        pw.change("Secure99", "NewPass1");
        cout << "Password changed successfully." << endl;
    } catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    cout << endl;
    cout << "=== Lab Complete ===" << endl;
    return 0;
}
