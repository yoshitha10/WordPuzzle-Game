#include <bits/stdc++.h>
#include<conio.h>
using namespace std;

bool validPassword(const string& password) 
{
    bool has_lowercase=false;
    bool has_uppercase=false;
    bool has_special_char=false;
    bool has_digit=false;

    if (password.length()<8) 
    {
        return false;
    }

    for (char c:password) 
    {
        int asciiValue = static_cast<int>(c);
        if (islower(c)) {
            has_lowercase=true;
        } 
        else if (isupper(c)) {
            has_uppercase=true;
        } 
        else if (isdigit(c)) {
            has_digit=true;
        }
        else if ((asciiValue>=33 && asciiValue<=47) || (asciiValue>=58 && asciiValue<=64) ||(asciiValue>=91 && asciiValue<=96) || (asciiValue>=123 && asciiValue<=126)) {
            has_special_char=true;
        } 
        if (has_lowercase && has_uppercase && has_special_char && has_digit) {
            return true;
        }
    }

    return false;
}

bool UsernameExists(const string& username,const string& filename) 
{
    ifstream file(filename);
    string line;
    
    while (getline(file,line)) 
    {
        size_t pos=line.find(",");
        if (pos!=string::npos) 
        {
            string username_in_file=line.substr(0,pos);
            if (username_in_file==username) 
            {
                file.close();
                return true;
            }
        }
    }
    file.close();
    return false;
}

void signup(const string& given_username,const string& filename) 
{
    string username=given_username;
    while (UsernameExists(username,filename)) 
    {
        cout<<"Username already exists. Please choose another username.\n";
        cout<<"Enter a different username: ";
        cin>>username;
    }
    string password;
    int password_attempts=0;
    cout<<"Enter your password(at least 8 characters with 1 lowercase, 1 uppercase, 1 special character, and 1 number): ";
    char ch;
    while ((ch = _getch()) != '\r') 
    {
        if (ch == '\b' && !password.empty()) 
        {
            cout << "\b \b";
            password.pop_back();
        } 
        else if (isprint(ch)) 
        {
            cout << '*';
            password.push_back(ch);
        }
    }
    cout << endl;

    while (!validPassword(password))
    {
        password_attempts++;
        cout<<"Invalid password format...Enter a valid password: ";
        while ((ch = _getch()) != '\r') 
        {
            if (ch == '\b' && !password.empty()) 
            {
                cout << "\b \b";
                password.pop_back();
            } 
            else if (isprint(ch)) 
            {
                cout << '*';
                password.push_back(ch);
            }
        }
        cout << endl;
    }

    ofstream file(filename, ios::app);
    file<<username<<","<<password<<"\n";
    file.close();
    cout<<endl;
    cout<<setw(53)<<setfill(' ')<<"Registration successful!\n";
    cout<<setw(83)<<setfill('-')<<endl;
    return;
}

string signin(const string& filename) 
{
    string username,password;
    //int attempts=0;

    while (true) 
    {
        cout<<endl;
        cout<<setw(49)<<setfill(' ')<<"Enter your username: ";
        cin>>username;
        int attempts=0;

        if (UsernameExists(username,filename)) 
        {
            while (attempts<3) 
            {
                cout<<setw(49)<<setfill(' ')<<"Enter your password: ";

                char ch;
                while ((ch = _getch()) != '\r') {
                    if (ch == '\b' && !password.empty()) {
                        cout << "\b \b";
                        password.pop_back();
                    } else if (isprint(ch)) {
                        cout << '*';
                        password.push_back(ch);
                    }
                }
                cout << endl;


                ifstream file(filename);
                string user;
                while (getline(file,user)) 
                {
                    size_t pos=user.find(",");
                    string username_in_file=user.substr(0, pos);
                    string password_in_file=user.substr(pos + 1);
                    if (username_in_file==username && password_in_file==password) {
                        file.close();
                        cout<<endl;
                        cout << setw(52)<<setfill(' ')<<"Sign in successful!\n";
                        cout<<setw(83)<<setfill('-')<<endl;
                        return username;
                    }
                }
                file.close();

                attempts++;
                cout<<"Invalid password. Attempts remaining: "<<(3-attempts)<<"\n";
            }

            cout<<"Maximum login attempts reached. Please try again later.\n";
        } 
        else 
        {
            char choice;
            cout<<setw(47)<<setfill(' ')<<"Username not found\n";
            cout<<endl;

            cout<<"Do you want to register with this username? (y/n): ";
            cin>>choice;
            
            if (choice=='y' || choice=='Y') {
                signup(username,filename);
                break;
            }
        }
    }
    return username;
}
