#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <cctype>
#include <fstream>

using namespace std;
ifstream is("input.in");

char b64idx[255] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char dictionary[100][100] = {"like","do","is","that", "party","in","he","food","are","are","do","done"};
char freq[70] = "etaoinsrhldcumfpgwybvkxjqz";
int nrwords = 10;

struct result
{
    int score;
    vector<char*> posible;
    char key;
};


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

result myxorfreq(vector<int> ver)
{
    int maxscore = -1;
    char text[100];
    int key;
    vector<char *> allres;
    cout << "~~possible solutions~~" << '\n';

    for(int t = 0; t < 256; ++t)
    {
        char res[1000];
        int cnt = 0;
        int sum = 0;
        for(int i : ver)
        {
            char r = i^t;
            res[cnt] = r;
            cnt++;
        }
        res[cnt] = '\0';
        int score = 0;
        for(int i = 0; i < strlen(res); ++i)
        {
            if(strchr(freq,tolower(res[i])) == nullptr)
                continue;
            score += (strlen(freq) - (strchr(freq, tolower(res[i])) - freq));
        }
        if(score > maxscore)
        {
            allres.clear();
            maxscore = score;
            strcpy(text,res);
            char* c = new char[1000];
            strcpy(c,res);
            allres.push_back(c);
            key = t;
        }
    }


    cout << "~~decrypted text~~" << '\n';
    for(char* i : allres)
        cout << i << '\n';
    cout << "key is : " << key;

    result r;
    r.posible = allres;
    r.score = maxscore;
    r.key = key;
    return r;

}



result myxor(vector<int> ver)
{
    int maxscore = -1;
    char text[100];
    int key;
    vector<char *> allres;
    cout << "~~possible solutions~~" << '\n';

    for(int t = 0; t < 256; ++t)
    {

        char res[1000];
        int cnt = 0;
        for(int i : ver)
        {
            char r = i^t;
            res[cnt] = r;
            cnt++;
        }
        res[cnt] = '\0';
        int score = 0;
        for(int i = 0; i < nrwords; ++i)
        {
            if(strstr(res,dictionary[i]) != nullptr)
                score++;
        }
        if(score != 0)
        {
            cout << res << '\n';
            cout << score << '\n';
        }
        if(score > maxscore)
        {
            allres.clear();
            maxscore = score;
            strcpy(text,res);
            char* c = new char[1000];
            strcpy(c,res);
            allres.push_back(c);
            key = t;
        }
    }


    result r;
    r.posible = allres;
    r.score = maxscore;
    r.key = key;
    return r;

}


int main()
{
    unsigned char text[100] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";

    string s;
    vector<char*> detected;
    int maxscore = -1;
    result detectedres;
    detectedres.score = -1;

    while(getline(is,s))
    {
        strcpy((char*)text,s.c_str());
        cout << text << '\n';

        vector<int> ver = split(text);
        cout << "~~ascii~~\n";
        for(int i : ver)
            cout  << (char)i << ' ';
        cout << '\n';
        cout << "~~hexa~~\n";
        for(int i : ver)
            cout << hex <<i << ' ';
        cout << dec;

        result r = myxorfreq(ver);
        if(r.score > detectedres.score)
            detectedres = r;

        cout << "~~~end test~~~\n";

    }

    cout << "end result is:\n";
    for(char* i : detectedres.posible)
    {
        cout << i;
    }
    cout << "\nkey is: " << detectedres.key;

    /*
    cout << "~~cypher text~~\n" << text << '\n';
    unsigned char *key = new unsigned char[100];
    unsigned char *res;
    unsigned char *b64;
    vector<int> ver = split(text);
    cout << "~~ascii~~\n";
    for(int i : ver)
        cout  << (char)i << ' ';
    cout << '\n';
    cout << "~~hexa~~\n";
    for(int i : ver)
        cout << hex <<i << ' ';
    cout << dec;

    cout << '\n';
    */
    return 0;
}
