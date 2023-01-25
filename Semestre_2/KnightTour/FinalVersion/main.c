#include <stdio.h>
#include "KnightTour.h"

int main(){
   for (int i = 1; i < 9; i++){
        for (int j = 1; j < 9; j++){
            passeio(i,j);
        }
    }
    return 0;
}