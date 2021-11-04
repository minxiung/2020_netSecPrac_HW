#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
int encrypted[5] = {0x8e , 0x41 , 0xb1 , 0xdc, 0x76};
bool verify(string &input)
{
    for(int i = 0; i < 5; i++){
        int num1 = ((input[i] ^ i) << ((i ^ 9) & 3)) % 0x100;
        int num2 = ((input[i] ^ i) >> (8 - ((i ^ 9) & 3))) % 0x100;
        int num = (num1 | num2) % 0x100;
        if( encrypted[i] != (num+8) )
            break;
        if(i == 4)  return true;
    }

    return false;
}

int main(int argc, char *argv[])
{
    string s(argv[1]);
    if(verify(s))
        printf("You got it!!\n");
    else
        printf("You failed!! Please try penis again\n");
    return 0;
}
