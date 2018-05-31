#include <graphics.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include <cstring>
#define X 1000
#define Y 800
#define RAD (3.1415/180)
#define DEFAULT k*rand()%(Y/2)
#define VAL DEFAULT

//COMPILE USING C++11

using namespace std;
void wait ( long double seconds )
{
    clock_t endwait;
    endwait = clock () + seconds * CLOCKS_PER_SEC ;
    while (clock() < endwait);
}
void Loading(int n)
{
    char * mess = (char*)".";

    if(n%3==0)
    {
        mess = (char*)"...";
    }
    else
    {
        if(n%2==0)
        {
            mess = (char*)"..";
        }
    }


    outtextxy(X-80, Y-35, mess);
    if(n%3==0)
        outtextxy(X-80, Y-35, (char*)"        ");
}

string toString(int n)
{
    string out;
    while(n)
    {
        out = (char)(n%10 +48)+out;
        n /= 10;
    }
    return out;
}
class Point
{

    static int k,q;
public:

    long double x, y;
    Point(const int &ran)
    {
        x=q*rand()%((int) X/2);
        y=rand()%((int)Y/2);

    }

    Point(const long double &xx=.0F, const long double &yy=.0F):x(xx), y(yy) {}
    inline long double Distance(const Point &P)
    {
        return hypot(x-P.x, y-P.y);
    }

    inline bool isEqual(const Point &P)
    {
        return (x==P.x && y==P.y);
    }
    friend class Cloud;
    friend ostream& operator << (std::ostream &out, const Point &);
    bool operator=(const Point &P)
    {
        x = P.x;
        y = P.y;
        return true;
    }
};

std::ostream& operator<< (std::ostream &out, const Point &P)
{
    out << '(' << P.x << ',' << P.y << ')';
    return out;
}
class Cloud : protected Point
{
    vector<Point*> P;
    vector<unsigned int> Points[2];
    Point PP[2];
    int k, q;


public:
    Cloud(const unsigned int &n=1)
    {
        k=1;
        q=1;
        string str;
        for(int i=0; i<n; i++)
        {
            int x;
            str = "Generating Points "+toString(i+1);
            P.push_back(new Point(x=q*rand()%((int) X/2), VAL));
            setcolor(WHITE);
            outtextxy(X-155, Y-20, &str[0]);
            // Points[0].push_back(i);

            if((i+1)%4==0)
            {
                q = -1;
                k = -1;

            }
            else
            {
                if((i+1)%3==0)
                {
                    q = -1;
                    k = 1;

                }
                else
                {
                    if((i+1)%2==0)
                    {
                        q =1;
                        k =-1;

                    }
                    else
                    {
                        q=1;
                        k=1;
                    }
                }
            }
            putpixel(X/2+P.at(i)->x, Y/2-P.at(i)->y, WHITE);
            wait(0.001);
        }
    }

    Point getCenter(const unsigned int &choice)
    {

        long double Sx(0), Sy(0);
        for(int i=0; i<P.size() && i<Points[choice].size(); i++)
        {
            Sx += P[Points[choice].at(i)]->x;
            Sy += P[Points[choice].at(i)]->y;
        }
        return Point(Sx/Points[choice].size(), Sy/Points[choice].size());
    }

    void setCenter(const Point &P0, const Point &P1)
    {
        PP[0] = P0;
        PP[1] = P1;
        Extract();
    }
    void Extract()
    {
        Points[0].clear();
        Points[1].clear();
        for(int i=0; i<P.size(); i++)
            PP[0].Distance(*P[i]) < PP[1].Distance(*P[i]) ? Points[0].push_back(i) : Points[1].push_back(i);


    }
    void oncreate()
    {
        for(int i=0; i<Points[0].size(); i++)
        {
            putpixel(X/2+P[Points[0].at(i)]->x,Y/2-P[Points[0].at(i)]->y, LIGHTCYAN);
            wait(0.001);
        }
        for(int i=0; i<Points[1].size(); i++)
        {
            putpixel(X/2+P[Points[1].at(i)]->x,Y/2-P[Points[1].at(i)]->y, LIGHTRED);
            wait(0.001);
        }
    }
    int getSize(const int &choice)
    {
        return Points[choice].size();
    }

};
int Point::k=1;
int Point::q=1;

void draway(const Point &P1, const Point &P2){
    static int count = 1;
   count%2  ? setcolor(LIGHTGREEN) : setcolor(LIGHTMAGENTA);
    line(X/2+P1.x, Y/2 - P1.y, X/2 + P2.x, Y/2-P2.y);
    count++;
}

void drawc(const Point&P, int c){
    static int count = 1;

putpixel(X/2+P.x, Y/2-P.y,c);
putpixel(X/2+P.x, Y/2-P.y-1, c);
putpixel(X/2+P.x, Y/2-P.y+1,c);
putpixel(X/2+P.x+1, Y/2-P.y, c);
putpixel(X/2+P.x-1, Y/2-P.y, c);
count++;
}
int main(void)
{
    srand((unsigned int)time(NULL));
    initwindow(X, Y, "IMAGE POINTS SEGMENTATION BY YOUNES MANSOURI");

    int x, y;
    setcolor(RED);
    line(X/2, 0, X/2, Y);
    line(0, Y/2, X, Y/2);
    int num;
    cout << "NOMBRES DE POINTS: ";
    cin >> num;
    Cloud N(num);
    //Point P[2]={Point(100.4, 12.4), Point(100.4, 430.3)};
    Point P[2]= {Point(1),Point(1)};
    vector<Point> P0LIN, P1LIN;
    P0LIN.push_back(P[0]);
    P1LIN.push_back(P[1]);
    N.setCenter(P[0], P[1]);

    int count = 1;
    string out;
    char *mess;
    do
    {
        P0LIN.push_back(P[0]);
        P1LIN.push_back(P[1]);
        draway(P[0], P0LIN[P0LIN.size()-2]);
        draway(P[1], P1LIN[P1LIN.size()-2]);
        cout << "P1" << P[0] << "  P2" << P[1] << endl ;

        out = "N1= " +toString(N.getSize(0));
        char *mess = strdup(out.c_str());
        outtextxy(X-155, Y-40, &out[0u]);
        out = "N2= " + toString(N.getSize(1)) + "                            ";
        outtextxy(X-155, Y-20, &out[0u]);
        Loading(count);
        cout << count << endl;
        count++;
        drawc(P[0], LIGHTMAGENTA);
        drawc(P[1], YELLOW);
        N.oncreate();

        // cout << "P1" << P[0] << "  P2" << P[1] << endl ;
        N.setCenter(P[0], P[1]);
    }
    while(!P[0].isEqual(N.getCenter(0)) &&  !P[1].isEqual(N.getCenter(1)) && (P[0]=N.getCenter(0), P[1]=N.getCenter(1)));
    setcolor(LIGHTBLUE);
    out = "N1= " +toString(N.getSize(0))+"      ";
    mess = strdup(out.c_str());

    outtextxy(X-155, Y-40, &out[0u]);
    out = "N2= " + toString(N.getSize(1))+"     ";
    outtextxy(X-155, Y-20, &out[0u]);
    outtextxy(X-80, Y-35, (char*)"        ");
    cout << "END" << endl;
    system("PAUSE");
    closegraph();
    system("cls");
    main();
    return 0;
}

