#include <cmath>
#include <algorithm>
#include <stdio.h>

using std::sort;
using std::abs;

struct Point;

Point *stopPoint;

struct Point{
    double x,y;
    mutable double dist, cos;
    mutable bool vals;

    Point(){x=0;y=0;vals=false, dist=0, cos=0;}

    Point(double x, double y){
        this->x = x; this->y = y;
        vals=false, dist=0, cos=0;
    }

    void setVals () const;
};

Point minPoint;

void Point::setVals () const{
    vals = true;
    dist =  (x-minPoint.x)*(x-minPoint.x)+(y-minPoint.y)*(y-minPoint.y);
    cos =     (x-minPoint.x)/sqrt(dist);
}


int crossProduct(Point& start1, Point& start2, Point& end1, Point& end2){
    double crossProduct = (end1.x-start1.x)*(end2.y-start2.y)
        -(end1.y-start1.y)*(end2.x-start2.x);
    return crossProduct < -1E-14 ? -1 : (crossProduct > 1E-14 ? 1 : 0);
}

bool compareTo(const Point& a, const Point& b) {
    if(!a.vals)
        a.setVals();
    if(!b.vals)
        b.setVals();

    if(abs(a.cos - b.cos) > 1e-14)
        return (a.cos - b.cos)>0;
    else
        return (b.dist - a.dist)>0;
};

void grahamScan(Point* points, int length, Point minPoint);
//Find the bottom left point and run grahamScan
void grahamScan(Point* points, int length){
    for(int i=0; i < length;i++)
    {
        Point p = points[i];
        if(i==0 || p.y<minPoint.y || (p.y==minPoint.y && p.x <minPoint.x))
            minPoint = p;

    }

    grahamScan(points, length, minPoint);
}

//minPoint = bottom, left point
void grahamScan(Point* points, int length, Point minPoint) {
    Point * end = points+length;

    sort(points, end, compareTo);
    stopPoint = &points[length-1];

    int m = 1;
    for(int i = 2; i < length; i++){
        while(i<length && crossProduct(points[m-1],points[m-1],points[m],points[i])<=0)
            if(m==1)    //Check if first points are collinear, if so ignore unnecessary points.
                points[m]=points[i++];
            else
                m--;
        if(i!=length)
            points[++m]=points[i];
    }
}

int main()
{
    Point points[3];
    points[0] = Point(-10000,0);
    points[1] = Point(-234,-234);
    points[2] = Point(10000,0);
    //points[3] = Point(1,0);
    //points[4] = Point(1,-1);
    //points[5] = Point(0,-1);
    //points[6] = Point(-1,-1);
    //points[7] = Point(-1,0);
    //points[8] = Point(-1,1);

    grahamScan(points, 3);
    for(int i =0; points[i].x!=stopPoint->x || points[i].y!=stopPoint->y ; i++)
    {
        printf("%lf %lf\n",points[i].x,points[i].y);
    }

    printf("%lf %lf\n",stopPoint->x,stopPoint->y);
}
