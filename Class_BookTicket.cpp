#include <set>
#include <iostream>
#include <vector>
#include <iomanip>
#include <conio.h>
#include <algorithm>
#include "GenerateTicket.cpp"
#include <cstdlib>
#include <cstring>
#include <sstream>
using namespace std;

class BookTicket : public GenerateTicket
{
private:
    string source;
    string destination;
    string boarding_time;
    string landing_time;

public:
    BookTicket() {}
    void menu();
    void LookForFlight();
    void give_recommendations_list();
    void read();
    void DisplayTicket();
    void cancelticket();
};
void BookTicket::menu()
{
    while (1)
    {
        system("cls");
        cout << "\t\t\t\t\t\t\t"
             << "User Registration and Ticket Booking Portal" << endl;
        cout << endl;
        cout << "Select your preffered option" << endl;
        cout << endl;
        cout << setw(4) << setiosflags(ios::left) << "1"
             << "Login" << endl
             << setw(4) << setiosflags(ios::left) << "2"
             << "New User" << endl
             << setw(4) << setiosflags(ios::left) << "3"
             << "Display Ticket" << endl
             << setw(4) << "4" << setiosflags(ios::left) << "Cancel Ticket" << endl
             << setw(4) << "5" <<setiosflags(ios::left) << "View Prices" << endl
             << setw(4) << "6" << setiosflags(ios::left) << "City Information" << endl
             << setw(4) << "7" << setiosflags(ios::left) << "Exit" << endl;

        int choice;
        cin >> choice;
        bool b = true;
        vector<string> v1;
        string temp = "";
        char ch;
        // istringstream is(s);
        ifstream fin,gin;
        try
        {
            switch (choice)
            {
            case 1:
                registered_users();
                break;
            case 2:
                for_new_users();
                break;
            case 3:
                system("cls");
                DisplayTicket();
                cin.get();
                b = false;
                break;
            case 4:
                system("cls");
                cancelticket();
                cin.get();
                b = false;
                break;
            case 5:
                system("cls");
                fin.open("Airline_code.txt");
                while(!fin.eof()){
                cout.setf(ios::left);
                fin>>temp>>temp;
                fin.get(ch);
                fin.get(ch);
                // fin.seekg(1,ios::cur);
                cout.width(15);
                cout<<temp;
                cout.width(0);
                cout<<"First    "<<"Business  "<<"Economic"<<endl;
                cout.width(15);
                cout<<" ";
                
                gin.open(temp + "_price.txt");
                gin>>temp>>temp;
                cout<<temp<<" ";
                gin>>temp>>temp;
                cout<<temp<<"    ";
                gin>>temp>>temp;
                cout<<temp<<endl;
                gin.close();
                }
                b = false;
            getch();
            break;
            case 6:
                read();
                b = false;
                break;
            case 7:
                exit(0);
            default:
                cout << "wrong option selected try again" << endl;
                b = false;
                getch();
                break;
            }
        }

        catch (tuple<string, string> temp)
        {
            if (get<0>(temp) == "RegError")
            {
                cout << get<1>(temp) << endl;
                getch();
                b = false;
            }
            if (get<0>(temp) == "ReRegError")
            {
                cout << get<1>(temp) << endl;
                getch();
                b = false;
            }
        }
        catch (string s)
        {
            cout << s << endl;
            b = false;
            getch();
        }
        catch (...)
        {

            getch();
            b = false;
        }
        while (b)
        {
            cout << "\033[2J\033[1;1H";
            cout << "*********************************************************************" << endl;
            cout << endl
                 << "Would you like to" << endl
                 << setw(4) << setiosflags(ios::left) << "1.\t"
                 << "Book Ticket" << endl
                 << setw(4) << setiosflags(ios::left) << "2.\t"
                 << "Go to Main Menu" << endl
                 << setw(4) << setiosflags(ios::left) << "3.\t"
                 << "Exit" << endl;

            do
            {

                cin >> choice;
                try
                {
                    if (choice == 1)
                    {
                        LookForFlight();
                    }
                    else if (choice == 2)
                        b = false;
                    else if (choice == 3)
                        exit(0);
                    else
                        throw("Wrong option selected! Try Again");
                }

                catch (string s)
                {
                    if (s[s.size() - 4] == '.')
                    {
                        cin.ignore();
                        cout << "This flight cannot be booked";
                        cin.get();
                        throw 10;
                    }

                    cin.get();
                    if (s == "generation failed")
                        break;
                    else
                    {
                        cout << s << endl;
                        getch();
                        break;
                    }
                }
                catch (char const *ch)
                {
                    cout << ch;
                    cin.get();
                    break;
                }
            } while (choice < 1 && choice > 3);
        }
    }
}
//
void BookTicket::LookForFlight()
{
    string from;
    string to;
    string date;
    cout << "Enter From Location" << endl;
    cin >> from;
    cout << "Enter Destination" << endl;
    cin >> to;

    source = from;
    destination = to;

    {

        cout << "Here is our recommendations list for your source" << endl
             << "Destination pair" << endl;
        try
        {
            give_recommendations_list();
        }

        catch (string s)
        {
            cout<< s;
            getch();
        }
        catch (bool b)
        {
            cout << "Sorry! No FLights available" << endl;
            getch();
        }
    }
}
void BookTicket::give_recommendations_list()
{
    ifstream fin("fromtolocation.txt");
    if (!fin.is_open())
    {
        string s = "";
        s += "fromtolocation.txt";
        throw;
    }
    // string path = "D:\mycodes\Airport_Management_System";
    vector<tuple<string, string, string, string, string>> sliced;
    vector<tuple<string, string, string, string, string>> window;
    vector<tuple<string, string>> time;
    string flight;
    string date;
    string from;
    string to;
    string bt;
    string lt;
    ifstream gin;
    while (!fin.eof())
    {
        char ch;
        string from_ = "";
        string to_ = "";
        fin >> flight >> from_ >> to_ >> date >> bt >> lt;
        fin.get(ch);
        time.push_back(make_tuple(bt, lt));
        for (auto it : from_)
        {
            if (it == '_')
                break;
            from += it;
        }
        for (auto it : to_)
        {
            if (it == '_')
                break;
            to += it;
        }
        if (from == source && to == destination)
        {

            gin.open(flight + "Business" + ".txt");
            string s1, s2, s3;

            if (!gin.is_open())
            {
                throw flight + "Business" + ".txt";
            }

            while (!gin.eof())
            {
                gin >> s1 >> s2 >> s3;
                fin.get(ch);
                fin.get(ch);

                if (s3 == "0")
                {
                    sliced.push_back(make_tuple(flight, "Business", date, s1, s2));
                    break;
                }
            }
            gin.clear();
            gin.seekg(0, ios::beg);
            while (!gin.eof())
            {
                gin >> s1 >> s2 >> s3;
                fin.get(ch);
                if (s2 == "3" && s3 == "0")
                {
                    window.push_back(make_tuple(flight, "Business", date, s1, s2));
                    break;
                }
            }
            gin.close();

            gin.open(flight + "Economic" + ".txt");
            if (!gin.is_open())
            {
                throw flight + "Economic" + (".txt");
            }

            while (!gin.eof())
            {
                gin >> s1 >> s2 >> s3;
                fin.get(ch);
                if (s3 == "0")
                {
                    sliced.push_back(make_tuple(flight, "Economic", date, s1, s2));
                    break;
                }
            }
            gin.clear();
            gin.seekg(0, ios::beg);
            while (!gin.eof())
            {
                gin >> s1 >> s2 >> s3;
                fin.get(ch);
                if (s2 == "3" && s3 == "0")
                {
                    window.push_back(make_tuple(flight, "Economic", date, s1, s2));
                    break;
                }
            }
            gin.close();
            gin.open(flight + "First" + ".txt");
            if (!gin.is_open())
            {
                throw flight + "First" + (".txt");
            }

            while (!gin.eof())
            {
                gin >> s1 >> s2 >> s3;
                fin.get(ch);
                if (s3 == "0")
                {
                    sliced.push_back(make_tuple(flight, "First", date, s1, s2));
                    break;
                }
            }
            gin.clear();
            gin.seekg(0, ios::beg);
            while (!gin.eof())
            {
                gin >> s1 >> s2 >> s3;
                fin.get(ch);
                if (s2 == "3" && s3 == "0")
                {
                    window.push_back(make_tuple(flight, "First", date, s1, s2));
                    break;
                }
            }
            gin.close();
        }
    }
    fin.close();

    if (!sliced.empty())
    {
        int choice;

        cout << "Do you want" << endl
             << setw(5) << "1."
             << "  Window" << endl
             << setw(5) << "2. "
             << "  any" << endl;

        cin >> choice;

        int i = 1;
        switch (choice)
        {
        case 1:
            for (auto it : window)
            {
                cout << i
                     << "\t" << get<0>(it) << "\t" << get<1>(it) << "\t" << get<2>(it)
                     << "\t" << get<0>(time[i % 3 ? i / 3 : i / 3 - 1]) << "\t" << get<1>(time[i % 3 ? i / 3 : i / 3 - 1]) << endl; 
                i++;
            }
            if (window.empty())
            {
                cout << "No window seats available" << endl;
                cout << "Press enter to chek for all seats" << endl;

                getch();
            }
            else
            {
                int choice;
                cin >> choice;
                try
                {

                    Boardingclass(window[choice - 1], time[choice - 1], date);
                }
                catch (string s)
                {
                    cout<< s;
                    getch();
                }
                break;
            }
        case 2:
            int i = 1;
            for (auto it : sliced)
            {
                cout << i
                     << "\t" << get<0>(it) << "\t" << get<1>(it) << "\t" << get<2>(it)
                     << "\t" << get<0>(time[i % 3 ? i / 3 : i / 3 - 1]) << "\t" << get<1>(time[i % 3 ? i / 3 : i / 3 - 1]) << endl;
                i++;
            }
            if (sliced.empty())
            {
                cout << "No seats available" << endl;

                getch();
            }
            else
            {
                int choice;
                cin >> choice;
                try
                {
                    Boardingclass(sliced[choice - 1], time[choice - 1], date);
                }
                catch (string s)
                {
                    cout<< s;
                    getch();
                }
            }
        }
    }
    else
    {
        throw false;
    }
}
void BookTicket::DisplayTicket()
{
    string TicketNumber;
    cout << "Enter Ticket Number" << endl;
    cin >> TicketNumber;
    ifstream fout(TicketNumber + ".txt");
    if(!fout.is_open()){
        string s = "";
        s += "No Ticket with ID " +TicketNumber+" Has been issued\nPlease register to book Ticket";
        throw s;

    }
    system("cls");
    while (!fout.eof())
    {
        char arr[100] = {0};
        fout.getline(arr, 100);
        cout << arr << endl;
    }
    cin.get();
}
void BookTicket::cancelticket()
{
    char TicketNumber[17] = {0};
    cout << "Enter ticket number" << endl;
    cin.ignore();
    cin.getline(TicketNumber, 100);
    strcat(TicketNumber, ".txt");
    ifstream fin(TicketNumber);
    if (fin.is_open())
    {
        fin.close();
        remove(TicketNumber);
        cout << "Ticket Cancelled" << endl;
        fstream fin;
        string flight = "";

        for (int i = 0; i < 6; i++)
        {
            flight += TicketNumber[i];
        }
        switch (TicketNumber[7])
        {
        case 'F':
            fin.open(flight + "First" + ".txt");
            break;
        case 'B':
            fin.open(flight + "Business" + ".txt");
            break;
        case 'E':
            fin.open(flight + "Economic" + ".txt");
            break;

        default:
            break;
        }
        int n = (TicketNumber[8] - '0') * 100 + (TicketNumber[9] - '0') * 10 + (TicketNumber[10] - '0');
        n += (TicketNumber[11] - '0') - 1;
        fin.seekg((n - 1) * 8 + 6, ios::beg);
        fin << "0";
        fin.close();
    }
    else
    {
        string s = "";
        s += "No Ticket Booked with this ID \n Please register to book ticket \n";
        throw s;
    }
}
void BookTicket::read()
{
    while (1)
    {
        system("cls");
        cout << "\n\n\n\n";
        cout << setfill('*') << setw(42) << "*"
             << "Miscellaneous" << setfill('*') << setw(42) << "*" << endl;
        cout << "Press Q to Go TO Main Menu" << endl;

        cout << "\nSearch about Your Travel Destination Here" << endl;
        string search = "";
        string temp;
        char ch;
        cin.get(ch);
        if (ch== 'Q')
        {
            return (void)"";
        }
        cin>>temp;
        search += ch;
        search += temp;
        transform(search.begin(), search.end(), search.begin(), ::tolower);
        ifstream fin("TravelDestinations.txt");
        if (!fin.is_open())
        {
            cout << "hello";
            getch();
            throw;
        }
        
        while (!fin.eof())
        {
            fin >> temp;
            if (temp == search)
            {
                break;
            }
        }
        fin.close();
        fin.open(search + ".txt");
        if (!fin.is_open())
        {
            throw;
        }
        if (!fin.eof() || temp == search)
        {
            char temp[1000] = {0};

            while (!fin.eof())
            {
                fin.getline(temp, 200);
                cout << temp << endl;
            }
            cin.ignore();
            cin.get();
        }
        else
        {
            cout << "Oops we don’t have that location as a travel destination";
            cin.get();
        }
    }
}