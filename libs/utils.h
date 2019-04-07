#include <vector>
#include <cmath>
#include <cstring>
#include <cctype>


using namespace std;

int hextoint(char c[2]);
vector<int> split(unsigned char* c);


int hextodec(unsigned char c);

unsigned char dectohex(int c);

unsigned char* fixed_xor(unsigned char* c1, unsigned char* c2);

int hammingdist(int a, int b);

int hammingdist(unsigned char* t1, unsigned char* t2);

vector<int> base64tobytes(unsigned char* c);

int getbitk(int x, int k);
