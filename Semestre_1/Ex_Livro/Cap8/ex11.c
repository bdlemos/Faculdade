#include <stdio.h>

struct data{
    int dd, mm, yy;
};

int main(){
    struct data datas[2];
    int dif_anos, dif_meses, dif_dias;
    for (int i = 0 ;  i < 2 ; ++i){
        setbuf(stdin, NULL);
        scanf("%d/%d/%d", &datas[i].dd, &datas[i].mm, &datas[i].yy);
    }
    dif_anos = (datas[0].yy - datas[1].yy) * 365;
    dif_meses = (datas[0].mm - datas[1].mm) * 30;
    dif_dias =  datas[0].dd - datas[1].dd;
    printf("Sao %d dias entre essas datas\n", (dif_anos + dif_meses + dif_dias > 0) ? dif_anos + dif_meses + dif_dias : -(dif_anos + dif_meses + dif_dias));
    return 0;
}