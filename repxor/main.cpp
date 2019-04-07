#include <iostream>
//#include "../detectxor/utils.h"
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;
ifstream is("in.in");

int main()
{

    unsigned char text[10000] = "Burn";
    unsigned char key[100] = "YELLOW SUBMARINE";
    int text_hex[100];
    vector<int> res;
    int cnt = 0;
    while (true) {
        char x;
        is >> x;
        text[cnt] = x;
        cnt++;
        if( is.eof() ) break;

    }
    text[cnt] = '\0';

    for(char c : text)
            cout << c;
    cout << '\n';

    int cnt2 = 0;
    int temp;
    for(int i = 0;i< cnt; ++i)
    {
        temp = (int)text[i] ^ (int)key[cnt];
        res.push_back(temp);
        cnt2 = (cnt+1)%strlen((const char *)key);
    }


    for(int v : res)
        cout << v <<' ';
    cout << '\n';
    for(int v : res)
        cout << (char)v <<' ';
    return 0;
}
