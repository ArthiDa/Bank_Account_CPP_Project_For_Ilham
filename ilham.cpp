#include<bits/stdc++.h>
#include<conio.h>
using namespace std;

class Account
{
public:
    string name,userName;
    int accountNumber,depositAmount,savingBalance,currentBalance,withdrawalAmount,interest,penaltyAmount;
    char accountType;

    void reg();
    void login();
    void menu(char,string);
    /// Saving
    void customerDeposit(string);
    void customerWithdraw(string);
    void customerBalance(string);
    void customerInterest(string);
    /// Current
    void currentDeposit(string);
    void chequeBook(string);
    void current_balance(string);
    void penalty(string);
};

void Account::reg()
{
    system("cls");
    cout << "\t\t Welcome to Registration Page\n";
    cout << "\t\t Enter your Name(ex-Ilham): ";
    cin >> name;
    cout << "\t\t Enter your user-name(ex-ilham123): ";
    string userNameIn;
    cin >> userNameIn;

    ///check userName is available or not
    fstream fl;
    fl.open("customer.txt");
    while(fl){
        fl >> userName >> name >> accountNumber >> accountType;
        if(userName==userNameIn){
            cout << "Username already exist...\n";
            return;
        }
    }
    fl.close();
    userName = userNameIn;

    cout << "\t\t Enter your account number(ex-12345): ";
    cin >> accountNumber;
    cout << "\t\t Enter your account type(Saving = S and Current = C): ";
    cin >> accountType;

    /// Open customer File to write customer information
    fstream fin,saving,current;
    fin.open("customer.txt",ios::app);
    saving.open("saving.txt",ios::app);
    current.open("current.txt",ios::app);
    savingBalance = 1000;
    currentBalance = 1000;
    interest = 0;

    if(accountType=='S' ||accountType=='s' ||accountType=='C' ||accountType=='c')
    {
        fin << userName << "\n" << name << "\n" << accountNumber << "\n" << accountType << "\n";
        if(accountType=='S' || accountType=='s') saving << userName << "\n" << savingBalance << "\n" << interest << "\n";
        else current <<  userName << "\n" << currentBalance << "\n" << penaltyAmount << "\n";
    }
    else
    {
        cout << "Type S/C or s/c...\n";
        system("Pause");
        reg();
    }

}

void Account::login()
{
    system("cls");
    string nameIn;
    int accNumIn;
    cout << "\t\t Welcome to Login Page\n";
    cout << "\t\t Enter your username: ";
    cin >> nameIn;
    cout << "\t\t Enter your Account Number: ";
    cin >> accNumIn;

    /// Open customer file to match the details
    fstream fout;
    fout.open("customer.txt");
    bool flag = 0;
    while(!fout.eof())
    {
        fout >> userName >> name >> accountNumber >> accountType;
        if(userName==nameIn && accountNumber==accNumIn)
        {
            cout << "Login Successfull\n";
            system("Pause");
            fout.close();
            menu(accountType,userName);
            flag = 1;
        }
    }
    if(!flag)
    {
        cout << "Username and Account Number not match...\n";
        system("Pause");
        fout.close();
        login();
    }
}

void Account::menu(char type,string customerName)
{
    system("cls");
    cout << "\t\t Welcome to your Account\n";
    cout << "\t\t Available features\n";
    if(type=='s' || type=='S')
    {

        cout << "\t\t 1. Deposit\n";
        cout << "\t\t 2. Withdraw\n";
        cout << "\t\t 3. Balance\n";
        cout << "\t\t 4. Total Interest on Deposit\n";
        cout << "\t\t 5. Logout\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch(choice)
        {
        case 1:
            customerDeposit(customerName);
            break;
        case 2:
            customerWithdraw(customerName);
            break;
        case 3:
            cout << type << " " << customerName << endl;
            customerBalance(customerName);
            break;
        case 4:
            customerInterest(customerName);
            break;
        case 5:
            login();
            break;
        default:
            cout << "Please select proper choice!!!\n";
            system("Pause");
            menu(type,customerName);
        }
        menu(type,customerName);
    }
    else
    {
        cout << "\t\t 1. Deposit\n";
        cout << "\t\t 2. Withdraw with Cheque Book\n";
        cout << "\t\t 3. Balance\n";
        cout << "\t\t 4. Penalty Amount\n";
        cout << "\t\t 5. Logout\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch(choice)
        {
        case 1:
            currentDeposit(customerName);
            break;
        case 2:
            chequeBook(customerName);
            break;
        case 3:
            current_balance(customerName);
            break;
        case 4:
            penalty(customerName);
            break;
        case 5:
            login();
            break;
        default:
            cout << "Please select proper choice!!!\n";
            system("Pause");
            menu(type,customerName);
        }
        menu(type,customerName);
    }

}

void Account::customerDeposit(string customerName)
{
    system("cls");
    Account ob1;
    vector<Account>temp;
    cout << "\t\t Welcome to Deposit Page\n";
    cout << "Enter the deposit amount: ";
    cin >> depositAmount;

    /// Open saving account file and get the total balance
    fstream saving;
    saving.open("saving.txt");
    while(saving)
    {
        saving >> userName >> savingBalance >> interest;
        if(userName==customerName)
        {
            savingBalance += depositAmount;
            savingBalance += (depositAmount*.05);
            interest += (depositAmount*.05);
        }
        ob1.userName = userName;
        ob1.savingBalance = savingBalance;
        ob1.interest = interest;
//        cout << "ok " << ob1.userName << " " << ob1.savingBalance << " " << ob1.interest << endl;
        temp.push_back(ob1);
    }
    saving.close();
    remove("saving.txt");
    temp.pop_back();
    saving.open("saving.txt",ios::app);
    for(auto ob:temp)
    {
        userName = ob.userName;
        savingBalance = ob.savingBalance;
        interest = ob.interest;
        saving << userName << "\n" << savingBalance << "\n" << interest << "\n";
    }
    saving.close();
    system("Pause");

}
void Account::customerBalance(string customerName)
{
    system("cls");
    cout << "\t\t Welcome to Balance\n";
    /// Open saving account file and get the balance;
    fstream saving;
    saving.open("saving.txt");
    while(!saving.eof())
    {
        saving >> userName >> savingBalance >> interest;
        if(userName==customerName)
        {
            cout << "Your total saving balance is: " << savingBalance << endl;
            break;
        }
    }
    system("Pause");

}
void Account::customerWithdraw(string customerName)
{
    system("cls");
    Account ob1; // ob1.userName, ob1.savingBalance, ob1.interest
    vector<Account>temp; // Account temp[] = {(ob1.userName, ob1.savingBalance, ob1.interest),(ob1.userName, ob1.savingBalance, ob1.interest),(ob1.userName, ob1.savingBalance, ob1.interest)}
    cout << "Welcome to Withdrawal Page\n";
    cout << "Enter the Withdrawal amount: ";
    cin >> withdrawalAmount;

    /// Open saving account file and get the total balance
    fstream saving;
    saving.open("saving.txt");
    while(saving)
    {
        saving >> userName >> savingBalance >> interest;
        if(userName==customerName)
        {
            if(savingBalance<withdrawalAmount)
            {
                cout << "You don't have enough balance on your account...\n";
            }
            else savingBalance -= withdrawalAmount;
        }
        ob1.userName = userName;
        ob1.savingBalance = savingBalance;
        ob1.interest = interest;
//        cout << "ok " << ob1.userName << " " << ob1.savingBalance << " " << ob1.interest << endl;
        temp.push_back(ob1); //
    }
    saving.close();
    remove("saving.txt");
    temp.pop_back();
    saving.open("saving.txt",ios::app);
    for(auto ob:temp)  /// for(int i=0, i<temp.size(); i+=1){userName = temp[i].userName}
    {
        userName = ob.userName;
        savingBalance = ob.savingBalance;
        interest = ob.interest;
        /// Save the information into Saving file
        saving << userName << "\n" << savingBalance << "\n" << interest << "\n";
    }
    saving.close();
    system("Pause");
}
void Account::customerInterest(string customerName)
{
    system("cls");
    cout << "\t\t Welcome to Balance\n";
    /// Open saving account file and get the interest;
    fstream saving;
    saving.open("saving.txt");
    while(!saving.eof())
    {
        saving >> userName >> savingBalance >> interest;
        if(userName==customerName)
        {
            cout << "Your total interest is: " << interest << endl;
            break;
        }
    }
    system("Pause");
}

void Account::currentDeposit(string user_name)
{
    system("cls");
    Account ob1;
    vector<Account>temp;
    cout << "\t\t Welcome to Deposit Page\n";
    cout << "Enter the deposit amount: ";
    cin >> depositAmount;

    /// Open current account file and get the total balance
    fstream current;
    current.open("current.txt");
    while(current)
    {
        current >> userName >> currentBalance >> penaltyAmount;
        if(userName==user_name)
        {
            currentBalance += depositAmount;
        }
        ob1.userName = userName;
        ob1.currentBalance = currentBalance;
        ob1.penaltyAmount = penaltyAmount;
        temp.push_back(ob1);
    }
    current.close();
    remove("current.txt");
    temp.pop_back();
    current.open("current.txt",ios::app);
    for(auto ob:temp)
    {
        userName = ob.userName;
        currentBalance = ob.currentBalance;
        penaltyAmount = ob.penaltyAmount;
        current << userName << "\n" << currentBalance << "\n" << penaltyAmount << "\n";
    }
    current.close();
    system("Pause");
}
void Account::chequeBook(string user_name)
{
    system("cls");
    Account ob1;
    vector<Account>temp;
    cout << "\t\t Welcome to Cheque Book Page\n";
    cout << "Enter the withdrawal amount: ";
    cin >> withdrawalAmount;

    /// Open current account file and get the total balance
    fstream current;
    current.open("current.txt");
    while(current)
    {
        current >> userName >> currentBalance >> penaltyAmount;
        if(userName==user_name)
        {
            currentBalance -= withdrawalAmount;
            if(currentBalance<1000)
            {
                penaltyAmount += (currentBalance*.05);
                currentBalance -= penaltyAmount;
                if(currentBalance<0) currentBalance = 0;

            }
            ob1.userName = userName;
            ob1.currentBalance = currentBalance;
            ob1.penaltyAmount = penaltyAmount;
            temp.push_back(ob1);
        }
    }
    current.close();
    remove("current.txt");
    temp.pop_back();
    current.open("current.txt",ios::app);
    for(auto ob:temp)
    {
        userName = ob.userName;
        currentBalance = ob.currentBalance;
        penaltyAmount = ob.penaltyAmount;
        current << userName << "\n" << currentBalance << "\n" << penaltyAmount << "\n";
    }
    current.close();
    system("Pause");
}

void Account::current_balance(string user_name)
{
    system("cls");
    cout << "\t\t Welcome to Balance Page\n";
    fstream current;
    current.open("current.txt");
    int balance = 0;
    while(current)
    {
        current >> userName >> currentBalance >> penaltyAmount;
        if(userName==user_name)
        {
            balance = currentBalance;
            break;
        }
    }
    cout << "Your Current Balance is: " << balance << endl;
    current.close();
    system("Pause");
}
void Account::penalty(string user_name)
{
    system("cls");
    cout << "\t\t Welcome to Penalty Page\n";
    fstream current;
    current.open("current.txt");
    int balance = 0;
    while(current)
    {
        current >> userName >> currentBalance >> penaltyAmount;
        if(userName==user_name)
        {
            balance = penaltyAmount;
            break;
        }
    }
    cout << "Your Penalty is: " << balance << endl;
    current.close();
    system("Pause");
}
int main()
{
    Account myAcc;
    while(1)
    {
        system("cls");
        char choice;
        cout << "Do you have an account? Type Y/N\n";
        cin >> choice;
        if(choice=='Y' || choice=='y')
        {
            myAcc.login();

        }
        else if(choice=='N' || choice=='n')
        {
            myAcc.reg();
        }
        else
        {
            cout << "Please Type Y/N.Thank you!\n";
        }
        system("pause");
    }

}

