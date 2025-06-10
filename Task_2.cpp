#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool loggingIn(){
    string username, password, user, pass;
    cout<<"Enter username : ";
    cin>>username;
    cout<<"Enter password : ";
    cin>>password;

    ifstream read(username + ".txt");
    getline(read, user);
    getline(read, pass);

    if(user == username && pass == password){
        return true;
    }else{
        return false;
    }
}

int main(){
    int choice;
    cout<<"Select your choice!"<<endl;
    cout<<"1.Registration"<<endl;
    cout<<"2.Login"<<endl;
    cout<<"Your choice is : ";
    cin>>choice;
    if(choice == 1){
        string username, password;
        cout<<"Select name of user : ";
        cin>>username;
        cout<<"Select password : ";
        cin>>password;

        ofstream file;
        file.open(username+".txt");
        file<<username<<endl<<password;
        file.close();

        main();

    }
    else if(choice == 2){
        bool status = loggingIn();
        if(!status){
            cout<<"Incorrect Information, Try Again:"<<endl;
            system("PAUSE");
            return 0;
            
        }else 
        {
            cout<<"Login Successful!"<<endl;
            system("PAUSE");
            return 1;
        }
    }

    return 0;
}