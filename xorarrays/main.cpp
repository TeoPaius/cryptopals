#include <iostream>
#include <cstring>

using namespace std;

int hextodec(unsigned char c)
{
    if(c >= '0' && c <= '9' )
        return c - '0';
    if(c >= 'a' && c <= 'f')
        return c - 'a' + 10;
}

unsigned char dectohex(int c)
{
     if(c >= 0 && c <= 9 )
        return '0' + c;
     if(c >= 10 && c <= 15)
        return 'a' + c - 10;
}

unsigned char* fixed_xor(unsigned char* c1, unsigned char* c2)
{
    unsigned char* res = new unsigned char[100];
    for(int i = 0; i < strlen((char*)c1); ++i)
    {
        int a = hextodec(c1[i]);
        int b = hextodec(c2[i]);
        res[i] = dectohex(a^b);
    }
    res[strlen((char*)c1)] = '\0';
    return res;
}

int main()
{
    unsigned char c1[100] = "1c0111001f010100061a024b53535009181c";
    unsigned char c2[100] = "686974207468652062756c6c277320657965";

    unsigned char *res = fixed_xor(c1,c2);
    for(int i = 0; i < strlen((char*)res); ++i)
        cout << res[i];
    return 0;
}
