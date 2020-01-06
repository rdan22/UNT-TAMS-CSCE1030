#include <iostream>
#include <stdio.h>
using namespace std;

enum Status {FLAG = 'F', BOMB = 'B'};

int main()
{
        Status blue = FLAG;

        printf("\033[1;34m%c\033[0m\n", static_cast<char>(blue));

        Status red  = BOMB;

        printf("\033[1;31m%c\033[0m\n", static_cast<char>(red));

        return 0;
}