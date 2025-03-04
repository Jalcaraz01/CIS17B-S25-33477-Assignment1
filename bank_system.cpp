//Justin Alcaraz
//Lesson 1 Assignment

#include <iostream>
#include <cctype>
#include <iomanip>
using namespace std;

//The BankAccount class is declared here, including a constructor which allows the user to create their account.
//This class also includes functions which may be accessed by the rest of the program in order to change or view private members of
//an object.
class BankAccount{
        private:
        string accountHolderName;
        int accountNumber;
        double balance;

        public:
        BankAccount(string name, double starting_balance){
        accountHolderName = name;
        balance = starting_balance;
        }
        
        
        void deposit(double deposit_amount){
            balance = balance + deposit_amount;
        }
        
        void withdraw(double withdraw_amount){
        balance -= withdraw_amount;
        }

        double getBalance(){
            return balance;
        }
};

//input_validation() checks if a user's input is a number, returns true if the input is valid and false if input is invalid.
//Messages are outputted depending on what caused the input to be invalid.
//Negative numbers and numbers including whitespace are considered invalid.
bool input_validation(string user_input){
    //for loop iterates through the characters of a string, checking for whitespace that would make an input invalid.
    for (int i=0; i < user_input.length(); i++){
        if (isspace(user_input[i])){
            cout << "Invalid input, please enter a number with no spaces." << endl;
            return false;
        }
    }
    //the try-catch block here tries to convert string to a double, if it fails it will give an exception which will be caught.
    try{
        stod(user_input);
        if(stod(user_input) < 0){
            cout << "Invalid input, please enter a positive number." << endl;
            return false;
        }
        else{
            return true;
        }
    }
    catch(...){
        cout << "Invalid input, please enter a number." << endl;
        return false;
    }
}

//deposit_money() takes a object address as a parameter so that it is able to deposit to its balance.
//Takes user input and uses input_validation function to verify.
//Outputs error message if user attempts to input a negative deposit.
//Returns 0 if deposit was unsuccessful and 1 if deposit was successful.
double deposit_money(BankAccount &object){
    string user_deposit;
    cout << "Enter amount to deposit: ";
    getline(cin, user_deposit);
    if (input_validation(user_deposit) == false){
        return 0;
    }
    else{
        if (stod(user_deposit) < 0){
            cout << "Cannot deposit negative amounts!" << endl;
            return 0;
        }
        else{
            object.deposit(stod(user_deposit));
            cout << "Deposit Successful! New Balance: $" << fixed << setprecision(2) << object.getBalance() << endl;
            return 1;
        }
    }
}

//withdraw_money() takes an object address as a parameter in order to directly withdraw from its balance.
//Takes user input and uses input_validation function to verify.
//Outputs error messages if user tries to input a negative withdrawal or an amount that is greater than the current balance.
//Returns 0 if withdrawal was unsuccessful and 1 if withdrawal was successful (or if funds were insufficient).
double withdraw_money(BankAccount &object){
    string user_withdrawal;
    cout << "Enter amount to withdraw: ";
    getline(cin, user_withdrawal);
    if (input_validation(user_withdrawal) == false){
        return 0;
    }
    if (stod(user_withdrawal) < 0){
        cout << "Cannot withdraw negative amounts!" << endl;
        return 0;
    }
    else if(object.getBalance() - stod(user_withdrawal) < 0){
        cout << "Insufficient funds!" << endl;
        return 1;
    }
    else{
        object.withdraw(stod(user_withdrawal));
        cout << "Withdraw Successful! New Balance: $" << fixed << setprecision(2) << object.getBalance() << endl;
        return 1;
    }
}

//This function takes an object address as a parameter and simply outputs its current balance.
//No return value.
void displayBalance(BankAccount &object){
    cout << "Current Balance: $" << fixed << setprecision(2) << object.getBalance() << endl;
}



int main(){
    
    //The main function begins with a while loop menu, which does not allow the user to select any option except to exit and to
    //create an account until an account is created.
    
    string userChoice = "";
    cout << "Welcome to Simple Bank System" << endl;
    
    while (userChoice != "1" && userChoice != "5"){
        cout << endl;
        cout << "1. Create Account" << endl << "2. Deposit Money" << endl << "3. Withdraw Money" << endl << "4. Check Balance" << endl << "5. Exit" << endl << endl;
        
        cout << "Enter your choice: ";
        
        getline(cin, userChoice);
        input_validation(userChoice);
        
        if (userChoice == "2" || userChoice == "3" || userChoice == "4"){
            cout << "Please create an account first!" << endl << endl;
        }
    }
    
    //End of while loop.
    //If the user chose to exit the program, it will return 0. Else (chose 1), the program will continue onto creating a bank account.
    
    if (userChoice == "5"){
        cout << "Thank you for using Simple Bank System!" << endl;
        return 0;
    }
    
    //Beginning of account creation, including verification for inputs.
    
    string user_name;
    string initial_deposit;
    
    cout << "Enter account holder name: ";
    getline(cin, user_name);
    
    cout << "Enter initial deposit: ";
    getline(cin, initial_deposit);
    while(input_validation(initial_deposit) == false){
        cout << "Enter initial deposit: ";
        getline(cin, initial_deposit);
    }
    
    BankAccount AccountOne(user_name, stod(initial_deposit));
    cout << endl;
    cout << "Account created successfully!" << endl;
    
    //End of account creation, an object has been initialized with a name and initial balance.
    
    //While loop is used again here to continue running the program until the user chooses to exit.
    userChoice = "";
    while (userChoice != "4"){
        cout << endl;
        cout << "1. Deposit Money" << endl << "2. Withdraw Money" << endl << "3. Check Balance" << endl << "4. Exit" << endl << endl;
        cout << "Enter your choice: ";
        getline(cin, userChoice);
        
        if (input_validation(userChoice) == false){
            continue;
        }
        //This switch statement switches between different functions depending on what the user input is.
        //Cases 1 and 2 will continue the loop if the return from the function called is not 1 (successful).
        switch(stoi(userChoice)){
            case 1:
                while(deposit_money(AccountOne) != 1){
                    continue;
                }
                break;
            case 2:
                while(withdraw_money(AccountOne) != 1){
                    continue;
                }
                break;
            case 3:
                displayBalance(AccountOne);
                break;
        }
        
    }
    cout << "Thank you for using Simple Bank System!" << endl;
    return 0;
}

