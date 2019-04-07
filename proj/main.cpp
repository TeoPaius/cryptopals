#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;
ifstream is("in.in");
ofstream os("out.out");

class ride
{
public:
    int startx, starty, finx, finy, startT, lastF;

    ride(int a, int b, int c, int d, int e, int f)
    {
        startx = a;
        starty = b;
        finx = c;
        finy = d;
        startT = e;
        lastF = f;
    }
};

int rows, cols;
int nrveh;
int nrrides;
int bonus;
int tmax;
vector<ride> rides;
vector<bool> used(10000);
vector<vector<int>> routes(1000);


int dist(int x1, int y1, int x2, int y2)
{
    return abs(x2-x1) + abs(y2 - y1);
}

int timeroute(int x0, int y0, int x1, int y1, int x2, int y2, int t0, int t1, int t2)
{
    return max(t0 + dist(x0,y0,x1,y1), t1) + dist(x1, y1, x2,y2);
}

bool isvalid(int x0, int y0, int x1, int y1, int x2, int y2, int t0, int t1, int t2)
{
    int tottime = t0 + dist(x0,y0,x1,y1) + dist(x1, y1, x2,y2);
    if( tottime<= t2)
        if(tottime <=tmax)
            return true;
    return false;
}

int score(int x0, int y0, int x1, int y1, int x2, int y2, int t0, int t1, int t2)
{
    int bon = 0;
    if(t0 + dist(x0,y0,x1,y1) <= t1)
        bon = bonus;

    bon += dist(x1, y1, x2,y2);
    return bon;
}

int max_global, xf_global, yf_global, tf_global;
vector <int> global_pos;
vector <int> stiva;

void bfs(int clvl, int maxlvl, int maxwide, int current_score, int x0, int y0, int t0)
{
    if(current_score <= max_global)
    {
        max_global = current_score;
        xf_global = x0;
        yf_global = y0;
        tf_global = t0;
        global_pos = stiva; //!!!
    }
    if(clvl == maxlvl)
    {
        return;
    }

    priority_queue<pair<int,int>> prioq;
    for(int j = 0; j < nrrides; ++j)
    {
        if(used[j])
            continue;
        if(!isvalid(x0,y0,rides[j].startx,rides[j].starty,rides[j].finx,rides[j].finy,t0,rides[j].startT,rides[j].lastF))
            continue;
        int scor = score(x0,y0,rides[j].startx,rides[j].starty,rides[j].finx,rides[j].finy,t0,rides[j].startT,rides[j].lastF);
        prioq.push(make_pair(scor,j));
    }

    int auxmaxwide = maxwide;


    while(! prioq.empty() && auxmaxwide)
    {
        pair<int,int> p = prioq.top();
        prioq.pop();
        used[p.second] = 1;
        t0 = timeroute(x0,y0,rides[p.second].startx,rides[p.second].starty,rides[p.second].finx,rides[p.second].finy,t0,rides[p.second].startT,rides[p.second].lastF);
        x0 = rides[p.second].finx;
        y0 = rides[p.second].finy;
        stiva.push_back(p.second);
        bfs(clvl+1,maxlvl,maxwide,current_score+p.first,x0,y0,t0);
        stiva.pop_back();
        used[p.second] = 0;
        --auxmaxwide;
    }
}


void domagic()
{
    int t0, x0,y0, x1,y1, t1,x2,y2,t2;


    for(int i = 0; i < nrveh; ++i)
    {
        t0 = 0;
        x0 = 0;
        y0 = 0;
        int found = 0;
        int maxscore = 0;
        int maxpos = -1;
        while(true)
        {
            max_global = 0x3f3f3f3f;

            bfs(0,1,1,0,x0,y0,t0);

            if(max_global == 0x3f3f3f3f)
                break;
            /*for(int j = 0; j < nrrides; ++j)
            {
                if(used[j])
                    continue;
                if(!isvalid(x0,y0,rides[j].startx,rides[j].starty,rides[j].finx,rides[j].finy,t0,rides[j].startT,rides[j].lastF))
                                continue;
                int scor = score(x0,y0,rides[j].startx,rides[j].starty,rides[j].finx,rides[j].finy,t0,rides[j].startT,rides[j].lastF);

                if(scor >= maxscore)
                {
                    maxscore = scor;
                    maxpos = j;
                }
            }*/

            for(auto p : global_pos)
            {
                routes[i].push_back(p);
                used[p] = 1;
            }

            t0 = tf_global;
            x0 = xf_global;
            y0 = yf_global;
        }


    }

}

void printstuff()
{
    for(int i = 0; i < nrveh; ++i)
    {
        os << routes[i].size() << ' ';
        for(int j : routes[i])
        {
            os  << j << ' ';
        }
        os  << '\n';

    }
}


int main()
{
    //yolo
    is >> rows >> cols >> nrveh >> nrrides >> bonus >> tmax;

    for(int i = 0; i < nrrides; ++i)
    {
        int a,b,c,e,d,f;
        is >> a >> b >> c >> d >> e >> f;
        ride temp(a,b,c,d,e,f);
        rides.push_back(temp);
    }
    domagic();
    printstuff();
    return 0;
}
