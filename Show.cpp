#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include "Employee.cpp"
using namespace std;
class show:public Employee{
    public:
    friend ifstream& operator>>(ifstream& din, show& temp);
    friend ostream& operator<<(ostream& ,show&);
    void update_job();
    void update_salary();
    void update_contract_validity();
    void showdata(){
    cout <<"Enter your ID";
    string id = "";
    cin>>id;
    ifstream fin(id + ".txt");
    if(!fin.is_open()){
        throw "No Employee with this ID";
        cin.ignore();
        cin.get();
    }
    fin>>(*this);
    cout<<(*this);
    }
};
void show::update_job(){
    system("cls");
    cout<<"Enter new job"<<endl;
    cin>>job.first;
    cout<<"Enter additional info"<<endl;
    cin>>job.second;
    cout<<"Job of the Employee has been updated"<<endl;
    getch();
}
void show::update_salary(){
    system("cls");
    cout<<"Current Salary of the employee: "<<salary<<endl;
    float percent = 101;
    while(percent>100){
    cout<<"Enter percentage increment"<<endl;
    cin>>percent;
    if(percent>100){
        cout<<"Percent should be between -100 to 100 "<<endl;
        getch();
    }
    else{
        salary += (salary/100.0)*percent;
        cout<<"Salary has been updated"<<endl;
        getch();
    }
    }
}
void show::update_contract_validity(){
    system("cls");
    int temp;
    while(1)
    {
    cout<<"Enter new contract validity period"<<endl;
    cin>>temp;
    if(temp<contract_validity){
        cout<<"New value cannot be less than old one!"<<endl;
        getch();
    }
    else{
        contract_validity = temp;
        break;
    }
    }
}
ifstream& operator>>(ifstream& fin,show& temp){
    fin>>temp.name;
    fin.ignore();
    fin>>temp.age;
    fin.ignore();
    getline(fin,temp.job.first);
    getline(fin,temp.job.second);
    fin>>temp.salary;
    fin.ignore();
    fin>>temp.date_joined;
    fin.ignore();
    fin>>temp.contract_validity;
    return fin;
    
}
ostream& operator<<(ostream& dout,show& temp){
    cout<<"Name : "<<temp.name<<endl
        <<"Age : "<<temp.age<<endl
        <<"Job : "<<temp.job.first<<endl
        <<setw(5)<<" "<<temp.job.second<<endl
        <<"Joined On : "<<temp.date_joined<<endl
        <<"Salary : "<<temp.salary<<endl
        <<"Contract Validity : "<<temp.contract_validity
        <<endl;
    return dout;
}