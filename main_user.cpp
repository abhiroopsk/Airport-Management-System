#include <iostream>
#include"class_BookTicket.cpp"

using namespace std;

int main()
{
    BookTicket *Book = new BookTicket;
    try{
        Book->menu();
    }
    catch(string s){
        cout<<"An error occured"<<endl;
        cin.get();
        Book->menu();
    }
    catch (int x){
        Book->menu();

    }
    return 0;
}
