#include <stdio.h>

int passed_days(int d, int m, int y){
    int days = 0, current_day = 17, current_month = 9, current_year = 2020, condition_bis = 0, condition_month = 0;
    while (1){
        if (d == current_day && m == current_month && y == current_year)
            return days + 1;
        if ((((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) && condition_bis == 0)// ve se o ano e bissexto
            condition_bis++;
        if ((condition_month == 0) && (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)){ // Ve se o mes tem 31 ou 30 dias
            days++;
            condition_month++;
        }else if ((condition_month == 0) && (m == 2) && (days > 28)){ // se for fevereiro tira 2 ou 1 dependendo do ano ser ou não bissexto
            if (condition_bis)
                days -= 1;
            else
                days -=2;
            condition_month++;
        }
        if (d > 30){
            d = 1;
            condition_month = 0;
            m++;
        }
        else if (m > 12){
            m = 1;
            condition_bis = 0;
            y++;
        }
        d++;
        days++;
    }
}

int main(){
    int d, m, y;
    while (scanf("%d%d%d", &d, &m, &y) != EOF)
        printf("%d\n", passed_days(d, m, y));
    return 0;
}