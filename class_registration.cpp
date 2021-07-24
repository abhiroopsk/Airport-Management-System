#include<iostream>
#include<fstream>
#include<string>
#include<tuple>
using namespace std;
class registration
{
    protected:
    string first_name,last_name,email,name;
    string contact_no,age;
    public:

    void registered_users()
    {
        cout<<"Enter your registered email: ";
        cin>>email;
        ifstream obj(email+".txt");
        if(! obj.is_open()){
            string s1 = "";
            s1 += "ReRegError";
            string s2 = "";
            s2+="No instance for the email : "+email;
            throw make_tuple(s1,s2);
        }
        system("cls");
        getline(obj,name);
        cout<<name<<endl;
        getline(obj,email);
        cout<<email<<endl;
        getline(obj,age);
        cout<<age<<endl;
        getline(obj,contact_no);
        cout<<contact_no<<endl;
        cin.ignore();
        cin.get();
        obj.close();
        
        
    }
    void for_new_users()
    {
        
        cout<<"Enter First Name: ";
        cin>>first_name;
        cout<<"Enter last name: ";
        cin>>last_name;
        cout<<"Enter your e_mail: ";
        cin>>email;
       
        cout<<"Enter your age and contact no"<<endl;
        cin.ignore();
        cin>>age>>contact_no;
        
        
        name=first_name+last_name;
        ifstream fin(email  + ".txt");
        if(fin.is_open()){
            fin.close();
            string s1 = "";
            s1 += "RegError";
            string s2 = "";
            s2+="You are already registered : "+email;
            throw make_tuple(s1,s2);
        }
        ofstream obj;
        obj.open(email+".txt");
        obj<<"Name: "<<first_name<<" "<<last_name<<endl;
        obj<<"email: "<<email<<endl;
        obj<<"age: "<<age<<endl;
        obj<<"contact number: "<<contact_no;
        obj.close();
    }
    registration customer_details()
    {
       return *this;
    }

};