#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
using namespace std;

int hextoint(char c[2])
{
    int res = 0;
    int cnt = 1;
    while(cnt >= 0)
    {
        if(c[1-cnt] >= '0' && c[1-cnt] <= '9')
        {
            res += (c[1-cnt] - '0')*pow(16,cnt);
        }
        else
        {
            res += (c[1-cnt]-'a' + 10)*pow(16,cnt);
        }
        cnt--;
    }
    return res;

}

vector<int> split(unsigned char* c)
{
    vector<int> res;

    for(int i = 0; i < strlen((char*)c)/2;++i)
    {
        char buff[2];
        buff[0] = c[i*2];
        buff[1] = c[i*2+1];
        res.push_back(hextoint(buff));
    }
    return res;

}

vector<int*> splitobytes(vector<int> v)
{
    vector<int*> res;
    int *buff = new int[24];
    int cnt = 0;

    for(int i = 0; i < v.size()/3; ++i)
    {
        buff = new int[24];
        for(int j = 0; j <= 2; ++j)
        {
            int nr = v[i*3+j];
            for(int k = 0; k <= 7; ++k)
            {
                buff[7*(j+1)-k] = (nr&1);
                nr>>1;
            }
        }
        for(int i = 0; i <= 23; ++i)
            cout << i;
        cout << '\n';
        res.push_back(buff);
    }

    return res;
}

unsigned char* hextob64(unsigned char *c)
{

    vector<int> r = split(c);
    for(int i : r)
    {
        cout << i << ' ';
    }

    splitobytes(r);
    return c;
}

int main()
{
    unsigned char text[1000] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    unsigned char* res = hextob64(text);



}
