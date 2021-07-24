#include<conio.h>
#include <iostream>
#include <fstream>
#include "class_Airlines_Data.cpp"
#include "Show.cpp"
using namespace std;
int empmain();
Airlines_Data *makeobject(string);
Airlines_Data *makeobject();
string time(string);
string date();
int Airlines_Data::number_of_seats;
int main()
{
    while (1)
    {
        system("cls");
        cout << "\t\t\t\t"<<"ADMIN" << endl;
        cout << "Would You Like to :" << endl
             << "1.\t"
             << "Update Flight" << endl
             << "2.\t"
             << "Create a FLight" << endl
             << "3.\t"
             << "View Current Flights" << endl
             << "4.\t"
             << "View Flight data" << endl
             << "5.\t"
             << "Employee data"<<endl
             << "6.\t"
             << "Exit" << endl;
        int choice;
        cin >> choice;
        system("cls");
        string FlightNumber = "";
        string option = "";
        string s = "";
        vector<string> v1;
        fstream fout;
        bool b = true;
        Airlines_Data *flight = NULL;
        switch (choice)
        {
        case 2:

            cout << "Enter Flight Number" << endl;
            cin >> FlightNumber;
            flight = makeobject(FlightNumber);
            delete flight;
            break;

        case 1:

            flight = makeobject();
            if (!flight)
                break;

            cout << "would you like to update:" << endl
                 << "1.\tFrom Location" << endl
                 << "2.\tTo Location" << endl
                 << "3.\tDate" << endl
                 << "4.\tBoarding Time" << endl
                 << "5.\tLanding Time" << endl;

            cout << "Enter All the options as a string in which each option" << endl
                 << " is seperated by space: ";

            cin.ignore();
            getline(cin, option);
            do
            {
                int i = 0;
                while (i < option.size())
                {

                    string temp = "";
                    switch (option[i])
                    {
                    case '1':
                        cout << "Enter From Location" << endl;
                        cin >> temp;
                        flight->update_fromlocation(temp);
                        /* code */
                        break;
                    case '2':
                        cout << "Enter to location" << endl;
                        cin >> temp;
                        flight->update_tolocation(temp);
                        break;
                    case '3':
                        temp = date();
                        flight->update_date(temp);
                        break;
                    case '4':
                        temp = time("boarding");
                        flight->update_boardingtime(temp);
                        break;
                    case '5':
                        temp = time("landing");
                        flight->update_landingtime(temp);
                        break;
                    default:
                        cout << "One or more options provided in the string are incorrect" << endl;
                        b = false;
                        break;
                    }
                    if (b == false)
                        break;
                    i += 2;
                }
            } while (!b);
            try{
            flight->print_to_file();
            flight->search_and_update();
            }
            catch(string s){
                cout<<s;
                cin.get();
            }
            delete flight;

            break;
        case 3:
            cout<<"Enter date"<<endl;
            cin>>s;
            v1 = flight->get_current_flight(s);
            for(auto it:v1){
                cout<<it<<endl;
            }
            cout<<"would you like to print this to file Y/N"<<endl;
            cin>>option;
            if(option =="Y"){
            fout.open(s + "_flights.txt");
            for(auto it:v1){
                fout<<it<<endl;
            }
            fout.close();
            }
            else break;   
        case 4:
            cout<<"Enter Flight code"<<endl;
            cin>>s;
            fout.open(s + ".txt");
            if(fout.is_open()){
                cout<<"Seat data for all classes for this flight has been generated"<<endl;
                getch();
            }
            else {
                cout<<"No such flight have been issued"<<endl;
                getch();
            }
        break;
        case 5:
            empmain();
            break;
        case 6:
        exit(0);
        break;
        default:
            cout << "Wrong Option Selected" << endl;
            cin.get();
            break;
        }
    }
}
Airlines_Data *makeobject(string FlightNumber)
{
    string from, to, date = "", bt = "", lt = "";
    int n;
    cout << "Enter From Location" << endl;
    cin >> from;
    cout << "Enter TO Location" << endl;
    cin >> to;
    cout << "Enter passenger capacity of flight: " << FlightNumber << endl;
    cin >> n;
    cin.ignore();
    int day = 34;
    while (day > 30)
    {
        cout << "Enter Day " << endl;
        cin >> day;
        if (day > 30)
            cout << "wrong input" << endl;
    }

    int month = 13;
    while (month > 11)
    {
        cout << "Enter Month " << endl;
        cin >> month;
        if (month > 11)
            cout << "wrong input" << endl;
    }
    int hour = 25;
    while (hour > 23)
    {
        cout << "Enter boarding hour in 24h format " << endl;
        cin >> hour;
        if (hour > 23)
            cout << "wrong input" << endl;
    }
    int minute = 70;
    while (minute > 59)
    {
        cout << "Enter boarding minute " << endl;
        cin >> minute;
        if (minute > 59)
            cout << "wrong input";
    }
    bt += hour / 10 + '0' ; bt+= hour % 10 + '0' ; bt += ':' ; bt+= minute / 10 + '0' ; bt+= minute % 10 + '0';
    hour = 25;
    while (hour > 23)
    {
        cout << "Enter landing hour in 24h format " << endl;
        cin >> hour;
        if (hour > 23)
            cout << "wrong input" << endl;
    }
    minute = 70;
    while (minute > 59)
    {
        cout << "Enter landing minute " << endl;
        cin >> minute;
        if (minute > 59)
            cout << "wrong input";
    }
    lt += hour / 10 + '0' ; lt+= hour % 10 + '0' ; lt+= ':' ; lt+= minute / 10 + '0' ; lt+= minute % 10 + '0';
    date += day / 10 + '0' ; date+= day % 10 + '0'; date += '/' ; date+= month / 10 + '0'; date+= month % 10 + '0';  date+= '/';
    date += "2021";
    cin.ignore();
    Airlines_Data *p = new Airlines_Data(from, to, date, n, FlightNumber, bt, lt);
    return p;
}
Airlines_Data *makeobject()
{
    string filename;
    cout << "Enter File Name" << endl;
    cin >> filename;
    try
    {
        fstream fin(filename);

        fin.close();
        Airlines_Data *p = new Airlines_Data(filename);
        return p;
    }
    catch (...)
    {
        cout << "cannot open file" << endl;
        cin.get();
        return NULL;
    }
}
string date()
{
    string date = "";
    int day = 34;
    cin.ignore();
    while (day > 30)
    {
        cout << "Enter Day " << endl;
        cin >> day;
        if (day > 30)
            cout << "wrong input" << endl;
    }

    int month = 13;
    while (month > 11)
    {
        cout << "Enter Month " << endl;
        cin >> month;
        if (month > 11)
            cout << "wrong input" << endl;
    }
     date += day / 10 + '0' ; date+= day % 10 + '0'; date += '/' ; date+= month / 10 + '0'; date+= month % 10 + '0';  date+= '/';
    date += "2021";
    return date;
}
string time(string s)
{
    string lt = "";
    int hour = 25;
    cin.ignore();
    while (hour > 23)
    {
        cout << "Enter "<<s<<  " hour in 24h format " << endl;
        cin >> hour;
        if (hour > 23)
            cout << "wrong input" << endl;
    }
    int minute = 70;
    while (minute > 59)
    {
        cout << "Enter "<< s<<" minute " << endl;
        cin >> minute;
        if (minute > 59)
            cout << "wrong input";
    }
    lt += hour / 10 + '0' ; lt+= hour % 10 + '0' ; lt+= ':' ; lt+= minute / 10 + '0' ; lt+= minute % 10 + '0';
    return lt;
}
bool checkid(string id);
void update_id_file(string id);
int empmain(){
    bool b = true;
    while(b){
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
            <<"go to main menu"<<endl;
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
            cout<<"Enter employee id: "<<endl;
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
            b = false;
            break;
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