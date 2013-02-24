#include "vect_util.cpp"
#include <utility>
#include <cmath>

using namespace std;

#ifndef EPSILON
#define EPSILON 1e-10
#endif

typedef vect<double,2> point;

//note, will return false if the two circles have the same center
bool circle_intersection(point c1, double r1, point c2, double r2,
                         pair<point,point>& ints){
    if(r1<r2) return circle_intersection(c2,r2,c1,r1,ints);
    double d2 = (c1-c2).norm();
    if(d2<EPSILON || d2-(r1+r2)*(r1+r2)>EPSILON || (r1-r2)*(r1-r2)-d2>EPSILON)
        return false;
    double a = ((r1*r1-r2*r2)/d2+1)/2;
    vect<double,2> v1 = a*(c1-c2);
    double h = 0;
    if(r1*r1/d2-a*a>0)
        h = sqrt(r1*r1/d2-a*a);
    vect<double,2> v2 = make_vect<double,2>((c1-c2)[1],-(c1-c2)[0])*h;
    ints.first = c1-v1+v2;
    ints.second = c1-v1-v2;
    return true;
}

bool circle_line_intersection(point c, double r, point b, vect<double,2> v,
                              pair<point,point>& ints){
    vect<double,2> unit = v/(sqrt(v.norm()));
    vect<double,2> delta1 = (c-b)-proj(c-b,unit);
    if(delta1.norm()-r*r>EPSILON)
        return false;
    vect<double,2> delta2;
    if(r*r-delta1.norm()>0)
        delta2 = unit*sqrt(r*r-delta1.norm());
    ints.first = c-delta1+delta2;
    ints.second = c-delta1-delta2;
    return true;
}
