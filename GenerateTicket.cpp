#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include <conio.h>
#include "class_registration.cpp"
using namespace std;
class GenerateTicket : public registration
{
private:
    string airlineCompany;
    map<string, string> ETicketID;
    string Class;
    char seat;

    string seat_number;
    string price;
    tuple<string,string>time;
    string date;

public:
    GenerateTicket()
    {
        this->airlineCompany = "NULL";

        this->Class = "NULL";
        seat = '\0';
    }
    void SaveTicket();
    void UserCopy();
    // vector<tuple<string,string>> search(vector<tuple<string,string>>);
    void Boardingclass(tuple<string, string, string, string, string> match,tuple<string,string>time,string date)
    {

        ETicketID.insert(pair<string, string>("Class", get<1>(match)));
        ETicketID.insert(pair<string, string>("Seat_Number", get<3>(match)));
        ETicketID.insert(pair<string, string>("Seat_Type", get<4>(match)));
        ETicketID.insert(pair<string, string>("flight_number", get<0>(match)));
        get<0>(this->time) = get<0>(time);
        get<1>(this->time) = get<1>(time);
        this->date = date;
        Class = get<1>(match);

        fstream fin(get<0>(match) + get<1>(match) + ".txt");
        if (!fin.is_open())
        {
            string s = "";
            s += "generation failed";
            getch();
            // throw s;
        }
        char ch[9] = {'\0'};
        
        string s1, s2, s3;
        int n = 0;
        ifstream gin(ETicketID["flight_number"]+".txt");
        for(int i = 0;i<5;i++){
            string temp;
            getline(gin,temp);
        }
        gin>>n;
        gin.close();
        while (n--)
        {
            fin.read(ch, 7);
            
            fin.seekg(1, ios::cur);
            if (ch[0] == ETicketID["Seat_Number"][0] && ch[1] == ETicketID["Seat_Number"][1] && ch[2] == ETicketID["Seat_Number"][2] && ch[4] == ETicketID["Seat_Type"][0] && ch[6] == '0')
                break;
            
        }
        fin.seekg(-2, ios::cur);
        fin << "1";
        fin.close();
        try{
            SaveTicket();
        }
        catch(...){
            string s = "Cannot open price file";
            getch();
            // throw s;
        }
        UserCopy();
        ETicketID.clear();

        
    }
};
void GenerateTicket::SaveTicket()
{

    string fname = "";
    fname += ETicketID["flight_number"] + "_" + ETicketID["Class"][0] + ETicketID["Seat_Number"] + ETicketID["Seat_Type"];
    ofstream fout(fname + ".txt");
    fout << fname<< endl;

    if (ETicketID["Seat_Type"][0] == '1')
        seat = 'R';
    if (ETicketID["Seat_Type"][0] == '2')
        seat = 'M';
    if (ETicketID["Seat_Type"][0] == '3')
        seat = 'W';
    fout << name << endl;
    fout << age << endl;
    fout << email << endl;
    fout << contact_no << endl;
    fout << get<0>(time) << " " << get<1>(time) << endl;
    fout << date;
    char ch;
    string code;
    string flight;
    string flight_number = "";
    for (int i = 0; i < 3; i++)
        flight_number += ETicketID["flight_number"][i];
    ifstream fin("Airline_code.txt");
    while (!fin.eof())
    {
        fin >> code >> flight;
        fin.get(ch);
        if (code == flight_number)
        {
            airlineCompany = flight;
            break;
        }
    }
    fin.close();
    fin.open(airlineCompany + "_price" + ".txt");
    if (!fin.is_open())
    {
        throw;
    }
    string p;
    while (!fin.eof())
    {
        string C;
        char ch;
        fin >> C >> p;
        fin.get(ch);
        
        
        if (C == ETicketID["Class"])
        {
            
            price = p;
            break;
        }
    }
    fin.close();
    fout << price << "/-" << endl;
    fout << airlineCompany;
    fout.close();
    fout.open("BookedTickets.txt", ios::app);
    fout << name<<endl;
    fout.close();
}
void GenerateTicket::UserCopy()
{

    string fname = "";
    fname += ETicketID["flight_number"] + "_" + ETicketID["Class"][0] + ETicketID["Seat_Number"] + ETicketID["Seat_Type"] + "_UserCopy";
    ofstream fout(fname + ".txt");
    fout <<setw(15)<<setiosflags(ios::left)<< name << endl;
    fout << "Airline Company: " << airlineCompany << endl;
    fout <<setw(15)<<setiosflags(ios::left)<< age << endl;
    fout << "Boarding Date: "<<date << endl;
    fout <<setw(15)<<setiosflags(ios::left)<< "EMAIL ID    : " << email << endl;
    fout << "ETicketID    : " <<ETicketID["flight_number"] << "_" << ETicketID["Class"][0] << ETicketID["Seat_Number"] <<setw(10)<<setiosflags(ios::left)<< ETicketID["Seat_Type"]  << endl;
    fout << "Boarding Time: "<< get<0>(time)<<endl;
    fout <<setw(15)<<setiosflags(ios::left)<< contact_no << endl;
    fout << "Landing Time: "<< get<1>(time)<<endl;
    fout <<setw(15)<<setiosflags(ios::left)<< "Amount Paid: " << price;
    fout << "Seat Number  : "
         << ETicketID["Seat_Number"] << seat << endl;
    fout.close();
}
