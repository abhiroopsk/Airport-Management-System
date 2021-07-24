#include<sstream>
#include<vector>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;
class Airlines_Data
{
private:
    string fromlocation;
    string tolocation;
    string date;
    string FlightNumber;
    static int number_of_seats;
    int booked_seats;
    string boarding_time;
    string landing_time;

public:
    Airlines_Data(string from, string to, string date, int n, string FlightNumber,string bt,string lt)
    {
        fromlocation = from;
        tolocation = to;
        this->date = date;
        number_of_seats = n;
        booked_seats = 0;
        this->FlightNumber = FlightNumber;
        boarding_time = bt;
        landing_time = lt;
        print_to_file();
        print_fromtolocation();
        printseatinfo();
    }
    Airlines_Data(string extract)
    {
        ifstream fin(extract + ".txt");
        getline(fin, fromlocation);
        getline(fin, tolocation);
        getline(fin, date);
        getline(fin,boarding_time);
        getline(fin,landing_time);
        
        fin >> number_of_seats;
        fin.ignore();
        fin >> booked_seats;
        fin.ignore();
        getline(fin, FlightNumber);
    }

    void update_fromlocation(string newlocation)
    {
        fromlocation = newlocation;
    }
    void update_tolocation(string newlocation)
    {
        tolocation = newlocation;
    }
    void update_date(string date)
    {
        this->date = date;
    }
    void update_boardingtime(string bt){
        this->boarding_time = bt;
    }
    void update_landingtime(string lt){
        this->landing_time = lt;
    }
    void print_to_file()
    {
        ofstream fout(FlightNumber + ".txt");
        
        fout << fromlocation << "\n"
             << tolocation << "\n"
             << date << "\n"
             << boarding_time << "\n"
             << landing_time << "\n"
             << number_of_seats << "\n"
             << booked_seats << "\n"
             << FlightNumber << "\n";


        fout.close();
    }
    void print_fromtolocation()
    {

        ofstream fout;
        
        fout.open("fromtolocation.txt", ios::app);
        fout << FlightNumber << " " << setiosflags(ios::left) << setw(18) << setfill('_') << fromlocation << " " << setiosflags(ios::left) << setw(18)<< setfill('_') << tolocation
             << " " << date << " " << boarding_time <<  " " <<landing_time << endl;
        fout.close();
    }
    void search_and_update()
    {
        fstream fin("fromtolocation.txt");
        string s;

        while (!fin.eof())
        {
            fin >> s;
            if (s == FlightNumber)
            {
                
                fin  << setiosflags(ios::left) << setw(18) << setfill('_') << fromlocation << " " << setiosflags(ios::left) << setw(18)<< setfill('_') << tolocation
             << " " << date << " " << boarding_time <<  " " <<landing_time << endl;
                break;
            }
            fin >> s >> s >> s >> s >> s;
        }
        fin.close();
    }
    void printseatinfo()
    {
        ofstream fin(FlightNumber + "Business.txt");
        for (int i = 1, j = 1; i <= number_of_seats; i++)
        {
            fin << setw(3) << setfill('0') << j << " " << (i % 3 ? i % 3 : 3) << " "
                << "0" << endl;
            if (i % 3 == 0)
                j++;
        }
        fin.close();
        fin.open(FlightNumber + "First.txt");
        for (int i = 1, j = 1; i <= number_of_seats; i++)
        {
            fin << setw(3) << setfill('0') << j << " " << (i % 3 ? i % 3 : 3) << " "
                << "0" << endl;
            if (i % 3 == 0)
                j++;
        }
        fin.close();
        fin.open(FlightNumber + ("Economic.txt"));
        for (int i = 1, j = 1; i <= number_of_seats; i++)
        {
            fin << setw(3) << setfill('0') << j << " " << (i % 3 ? i % 3 : 3) << " "
                << "0" << endl;
            if (i % 3 == 0)
                j++;
        }
        fin.close();
    }
    ~Airlines_Data(){
        
    }
    vector<string> get_current_flight(string d){
        vector<string >v1;
        ifstream fin("fromtolocation.txt");
        string temp = "";
        string c_,d_,s;
        while(!fin.eof()){
        getline(fin,temp);
        istringstream is(temp);
        is>>c_;
        is>>s>>s;
        is>>d_;
        is>>s;
        fin.ignore();
        if(d_ == date)
        v1.push_back(c_);
        }
        return v1;
    }
};
