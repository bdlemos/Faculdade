#include <stdio.h>

int passed_days(int d, int m, int y){
    int days = 0, current_day = 17, current_month = 9, current_year = 2020, condition_bis = 0, number_days;
    while ((d != current_day) || (m != current_month) || (y != current_year)){
        if ((((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) && condition_bis == 0)// ve se o ano e bissexto
            condition_bis++;
        if ((m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12))
            number_days = 31;
        else if (m == 2){
            if (condition_bis)
                number_days = 29;
            else
                number_days = 28;
        }else
            number_days = 30;
        if (d > number_days){
            d = 1;
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
    return days + 1;
}

int main(){
    int d, m, y;
    while (scanf("%d%d%d", &d, &m, &y) != EOF)
        printf("%d\n", passed_days(d, m, y));
    return 0;
}