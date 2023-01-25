#include <iostream>
using namespace std;


int main(){
    int cafe_visitors, hour, minutes, lasthour = -1, lastminutes = -1, cash_number = 1, max_cash_number = 1;
    cin >> cafe_visitors;
    for (int i = 0 ; i < cafe_visitors ; ++i){
        cin >> hour >> minutes;
        if (hour == lasthour && minutes == lastminutes){
            cash_number++;
            if  (max_cash_number < cash_number)
                max_cash_number = cash_number;
        }
        else if (hour != lasthour || minutes != lastminutes)
            cash_number = 1;
        lasthour = hour;
        lastminutes = minutes;
    }
    cout << max_cash_number << endl;
    return 0;
}