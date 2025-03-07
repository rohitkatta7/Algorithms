
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <list>
#include <iostream>
#include <string.h>
#include <vector>
#include <set>
#include <string>
#include <complex>
#include <queue>
#include <stack>
#include <fstream>
#include <map>
#define MAX_N 501

using namespace std;
int  c = 1;

struct Point
{
    int x, y;
    bool operator <(const Point& p) const
    {
        return (x < p.x);
    }
};
Point pts[MAX_N];

double error[MAX_N][MAX_N]; 
double a[MAX_N][MAX_N]; 
double b[MAX_N][MAX_N]; 

double xySums[MAX_N], xSums[MAX_N], ySums[MAX_N], xSqrSums[MAX_N], ySqrSums[MAX_N]; 
double M[MAX_N];
int min_i[MAX_N];

struct Segment
{
    double a_final, b_final;
    int p1, p2;
    Segment()
    {
        this->a_final = 0;
        this->b_final = 0;
        this->p1 = 0;
        this->p2 = 0;
    }
    Segment(double a_final, double  b_final, int p1, int p2)
    {
        this->a_final = a_final;
        this->b_final = b_final;
        this->p1 = p1;
        this->p2 = p2;

    }
};
vector<Segment> ret; 

inline void pre_cal(int n, vector<pair<double, double> >& pts)
{

    for (int i = 1; i <= n; i++)
    {
        xSums[i] = xSums[i - 1] + pts[i - 1].first;
        ySums[i] = ySums[i - 1] + pts[i - 1].second;
        xSqrSums[i] = xSqrSums[i - 1] + pts[i - 1].first * pts[i - 1].first;
        xySums[i] = xySums[i - 1] + pts[i - 1].first * pts[i - 1].second;
        ySqrSums[i] = ySqrSums[i - 1] + pts[i - 1].second * pts[i - 1].second;
    }


    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            int nn = j - i + 1;
            double xySum = xySums[j] - xySums[i - 1];
            double xSum = xSums[j] - xSums[i - 1];
            double ySum = ySums[j] - ySums[i - 1];
            double xSqrSum = xSqrSums[j] - xSqrSums[i - 1];
            double ySqrSum = ySqrSums[j] - ySqrSums[i - 1];

            double aVal, bVal, errorVal;

            if (j == i + 1) { 
                aVal = 0.0;
                bVal = 0.0;
                errorVal = 0.0;
            }
            else {
                aVal = (((nn * xySum) - (xSum * ySum)) * 1.0) / (((nn * xSqrSum) - (xSum * xSum)) * 1.0);
                bVal = ((ySum - (aVal * xSum)) * 1.0) / (nn * 1.0);

                errorVal = (aVal * aVal * xSqrSum) + (2.0 * aVal * bVal * xSum) - (2.0 * aVal * xySum) + (nn * bVal * bVal) - (2.0 * bVal * ySum) + ySqrSum;
            }

            a[i][j] = aVal;
            b[i][j] = bVal;
            error[i][j] = errorVal;
        }
    }
}

void segment_least_sq(int n)
{
    M[0] = M[1] = 0;
    min_i[0] = min_i[1] = INT_MIN;

    for (int j = 2; j <= n; j++) {
        M[j] = INT_MAX; // Initializing with a large value
        for (int i = 1; i < j; i++) {
            if (M[j] > error[i][j] + c + M[i]) {
                M[j] = error[i][j] + c + M[i];
                min_i[j] = i; // Store the value of i for minimum M[j]
            }
        }
    }
    cout << "J   opt   breakpoint" << endl;
    for (int j = 0; j <= n; j++) {
        cout << j << "   " << M[j] << "   " << min_i[j] << endl;
    }

}

inline void ip_Segments(int n, vector<pair<double, double> >& pts)
{
    stack<Segment> S;
    int current_index = n;
    while (current_index > 1)
    {
        int next_index = min_i[current_index];
        if (next_index == current_index)
        {
            //continue
        }
        else
        {
            double a_final = a[next_index][current_index];
            double b_final = b[next_index][current_index];
            int p2 = current_index;
            int p1 = next_index;
            S.push(Segment(a_final, b_final, p1, p2));
        }
        current_index = next_index;
    }
    while (!S.empty())
    {
        ret.push_back(S.top());
        S.pop();
    }
}

int main(int argc, char** argv)
{
    vector<pair<double, double>> pts;
    //taking input from external file
    ifstream inputFile("data1.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }
    double x, y;
    while (inputFile >> x >> y) {
        pts.emplace_back(x, y);
    }

    inputFile.close();

    int n = pts.size();

    pre_cal(n, pts);

    segment_least_sq(n);

    ip_Segments(n, pts);
    for (int i = 0; i < ret.size(); i++)
    {
        printf("LineSegement starts at point %d to %d point is y =  %lfx + %lf\n", ret[i].p1, ret[i].p2, ret[i].a_final, ret[i].b_final);
    }
    return 0;
}