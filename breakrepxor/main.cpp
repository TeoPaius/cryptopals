#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include "../libs/utils.h"


using namespace std;

char * read()
{
    ifstream ifile("pass.txt");
    string str;
    getline(ifile,str,EOF);

    str.erase(std::remove(str.begin(), str.end(), 'a'), str.end());

    char* tab2 = new char[10000];
    strncpy(tab2, str.c_str(), sizeof(tab2));
    tab2[sizeof(tab2) - 1] = 0;
    return tab2;

}

int main()
{
    unsigned char text[100] = "this is a test";
    unsigned char text2[100] = "wokka wokka!!!";
    unsigned char text3[100] = "TWFuTWE=";
    int res = hammingdist(text, text2);
    //cout << hammingdist(9,3) << '\n';
    //cout << res;

/*    vector<int> textbytes = base64tobytes()
    for(int i : textbytes)
    {
        cout << i << '\n';
    }
  */
    char * r = read();
    for(int i = 0; i < strlen(r); ++i)
        cout << r[i];
    return 0;
}


