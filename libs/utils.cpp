#include <vector>
#include <cmath>
#include <cstring>
#include <cctype>
#include <map>
#include <iostream>

using namespace std;
char b64idx[255] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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

int hammingdist(int a, int b)
{

    int cnt = 0;
    int temp = a^b;
    while(temp)
    {
        if(temp & 1 == 1)
            cnt++;
        temp >>= 1;
    }
    return cnt;
}

int hammingdist(unsigned char* t1, unsigned char* t2)
{
    int temp1, temp2;
    int length1 = strlen((const char*) t1);
    int length2 = strlen((const char*) t2);
    int cnt = 0;
    for(int i = 0; i < max(length1, length2); ++i)
    {
        temp1 = (i <= length1 ? t1[i] : 0);
        temp2 = (i <= length2 ? t2[i] : 0);

        //cout << (char)temp1 << ' ' << (char)temp2;
        //cout << '\n';
        cnt += hammingdist(temp1, temp2);
    }
    return cnt;
}

int getbitk(int x, int k)
{
    return ((x & (1 << (k))) >> k);
}

vector<int> base64tobytes(vector<char> c)
{
    map<char, int> b64_int;
    for(int i = 0; i < strlen(b64idx); ++i)
        b64_int.insert(pair<char,int>(b64idx[i], i));
    b64_int.insert(pair<char, int>('=',0));
    vector<int> res;


    int bitcount = 6;
    int secbitcount  = 8;

    for(int i = 0; i < c.size(); i+=4)
    {
        int temp[24];
        int cnt = 0;
        for(int j = 0; j <= 3;++j)
        {
            for(int k = bitcount-1; k >= 0; --k)
            {
                temp[cnt] = getbitk(b64_int[c[i+j]],k);
                cnt++;
            }

        }
        cnt = 0;
        int nr = 0;
        for(int j = 0; j <= 23; ++j)
        {
            if(cnt == secbitcount)
            {
                res.push_back(nr);
                cnt %= secbitcount;
                nr = 0;
            }
            nr = (nr << 1) + temp[j];
            cnt++;
        }
        res.push_back(nr);

    }
    return res;

}



