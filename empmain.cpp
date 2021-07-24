#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Show.cpp"
#include <sstream>
#include<conio.h>
using namespace std;
bool checkid(string id);
void update_id_file(string id);
int empmain(){
    while(1){
        system("cls");
        cout<<"\t\t\t\t\t";
        cout<<"Employee Entry Portal"<<endl;
        cout<<"Select Option\n"<<endl
            <<setw(4)<<setiosflags(ios::left)<<"1"
            <<"Enter New Employee"<<endl
            <<setw(4)<<setiosflags(ios::left)<<"2"
            <<"Display Employee Information"<<endl
            <<setw(4)<<setiosflags(ios::left)<<"3"
            <<"Update Employee"<<endl
            <<setw(4)<<setiosflags(ios::left)<<"4"
            <<"Remove employee"<<endl
            <<setw(4)<<setiosflags(ios::left)<<"5"
            <<"Exit"<<endl;
        int choice;
        cin>>choice;
        show *obj = new show;
        ofstream fout;
        string id = "";
        istringstream is(id);
        char arr[10] = {0};
        switch(choice){
            case 1:
            system("cls");
            obj->getdata();
            operator<<<show>(fout,obj);
            fout.close();
            getch();
            break;
            case 2:
            system("cls");
            obj->showdata();
            getch();
            break;
            case 3:
            system("cls");
            cout<<"Enter employee id"<<endl;
            cin>>id;
            try{
                if(!checkid(id)){
                    cout<<"No employee with this id"<<endl;
                    getch();
                    break;
                }
            }
            catch(...){
                cout<<"File error!";
                getch();
                break;
            }
            operator<<<show>(fout,obj);
            cout<<"select option"<<endl;
            cout
            <<setw(4)<<setiosflags(ios::left)<<"1"
            <<"Job"<<endl
            <<setw(4)<<setiosflags(ios::left)<<"2"
            <<"Salary"<<endl
            <<setw(4)<<setiosflags(ios::left)<<"3"
            <<"Contract"<<endl
            <<setw(4)<<setiosflags(ios::left)<<"4"
            <<"Exit"<<endl;
            cin>>choice;
            do
                switch(choice){
                    case 1:
                    obj->update_job();
                    break;
                    case 2:
                    obj->update_salary();
                    break;
                    case 3:
                    obj->update_salary();
                    break;
                    case 4:
                    exit(0);
                    default:
                    cout<<"Invalid entry"<<endl;
                    getch();
                }
            while(choice>=1&&choice<=4);
            break;
            case 4:
            cout<<"Enter employee id"<<endl;
            cin>>id;
            try{
                if(!checkid(id)){
                    cout<<"No employee with this id"<<endl;
                    getch();
                    break;
                }
            }
            catch(...){
                cout<<"File error!";
                getch();
                break;
            }
            update_id_file(id);
            id += ".txt";
            is>>arr;
            remove(arr);
            break;
            case 5:
            exit(0);
            default:
            cout<<"Wrong option selected!"<<endl
                <<"Try again"<<endl;
            getch();
        }
    }
    
    
}
bool checkid(string id){
    ifstream fin("empid_file.txt");
    if(!fin.is_open())
    throw ;
    while(!fin.eof()){    
        string temp;
        getline(fin,temp);
        if(temp == id);
        return true;
    }
    return false;
}
void update_id_file(string id){
    ifstream fin("empid_file.txt");
    if(!fin.is_open())
    throw;
    vector<string> temp ;
    while(!fin.eof()){
        temp.push_back("");
    getline(fin,temp.back());
    if(temp.back() == id)
    temp.pop_back();
    }
    fin.close();
    ofstream fout("empid_file.txt");
    for(auto it:temp){
        fout<<it<<endl;
    }
    fout.close();
}