#include <iostream>
#include <conio.h>
using namespace std;

class Employee{
    private:
    string empid;
    protected:
    string name;
    int age;
    pair<string ,string> job;
    int salary;
    string date_joined;
    int contract_validity;
    public:
    template <class X>
    friend ofstream& operator<<(ofstream& ,X* );
    
    void getdata();
    void getdate();
    void generate_id();
    
    virtual void showdata() = 0;
};
template<class X>
ofstream& operator<<(ofstream& fout, X* temp){
    
    fout.open(temp->empid + ".txt");
    if(!fout.is_open()){
        cout<<temp->empid<<endl;
        cout<<temp->date_joined<<endl;
        cout<<"coudn’t do that"<<endl;
        getch();
        return fout;
    }
    fout<<temp->name<<endl
        <<temp->age<<endl
        <<temp->job.first<<endl<<temp->job.second<<endl
        <<temp->salary<<endl
        <<temp->date_joined<<endl
        <<temp->contract_validity<<endl;
    fout.close(); 
    fout.open("empid_file.txt",ios::app);
    fout<<temp->empid<<endl;
    
    return fout;
}
void Employee:: getdata(){
    cout<<"Enter Name: ";
    cin>>name;
    cout<<"Enter Age: ";
    cin>>age;
    cout<<"Enter Date joined: " << endl;
    getdate();
    cout<<"Enter Contract Validity Period: ";
    cin>>contract_validity;
    cout<<"Enter job post : ";
    cin.ignore();
    getline(cin,job.first);
    cout<<endl<<"Enter additional information about the job: "<<endl;
    cin.ignore();
    getline(cin,job.second);
    cout<<"Enter Salary: ";
    cin>>salary;
    generate_id();
}

void Employee::getdate(){
    cout<<endl<<"Enter day";
    int day = 31;
    while(day>30){
        cin>>day;
        if(day > 30) cout<<"enter valid date"<<endl;
    }
    cout<<"Enter Month"<<endl;
    int month = 15;
    while(month > 12){
        cin>>month;
        if(month > 12) 
        cout<<"Enter valid month"<<endl;
    }
    string year;
    cout<<"Enter year"<<endl;
    cin>>year;
    date_joined = "";
    date_joined += day/10 + '0'; date_joined += day%10 + '0'; date_joined += "/" ; 
    date_joined = month/10 + '0'; date_joined += month%10 + '0'; date_joined += "/" ; 
    date_joined  += year; 
}
void Employee::generate_id(){
    empid = job.first[0];
    for(auto it:date_joined){
        if(it != '/')
            empid += it;
    }
    empid += contract_validity + '0';

}