#include <cmath>
#include <stdio.h>
//#include "vect.cpp"
#include "vect_util.cpp"
using std::abs;
double ep = 1e-10;


typedef vect<double,2> point;
double triangleArea(point a, point b, point c){
    vect<double,2> d1=a-b,d2=a-c;
    double temp = d2[0];
    d2[0]=-d2[1];
    d2[1]=temp;
	return abs(d1*d2)/2;
}

bool arePointsCollinear(point a, point b, point c){
	return triangleArea(a, b, c)<ep;
}

struct Segment{
	point& start, &end;
	Segment (point &s,point &e):start(s),end(e)	{}
};

char doSegmentsIntersects(Segment one, Segment two);

bool isEndPoint(Segment s, point point){
	return (s.start-point).norm()<ep || (s.end-point).norm()<ep;
}

bool doSegmentsIntersectExceptAtEnds(Segment one, Segment two){
	char a = doSegmentsIntersects(one, two);
	return a!='v' && a!='0' && a!='e';
}

bool doSegmentsIntersectAtEdge(Segment one, Segment two){
	return doSegmentsIntersects(one, two)=='e';
}

bool doSegmentsIntersectAtVertex(Segment one, Segment two){
	return doSegmentsIntersects(one, two)=='v';
}

bool doSegmentsIntersect(Segment one, Segment two){
	return doSegmentsIntersects(one, two)!='0';
}

bool isPointBetweenSegment(Segment one, point p){
	if ( abs(one.start[0] - one.end[0])>ep )
		return ((one.start[0] <= p[0]) && (p[0] <= one.end[0])) ||
				((one.start[0] >= p[0]) && (p[0] >= one.end[0]));
	else
		return ((one.start[1] <= p[1]) && (p[1] <= one.end[1])) ||
				((one.start[1] >= p[1]) && (p[1] >= one.end[1]));
}

//return 0 for no parallel intersection, e for if they overlap at an edge
char parallelSegmentIntersection(Segment one, Segment two){
	if ( !arePointsCollinear( one.start, one.end, two.start) )
		return '0';

	if ( isPointBetweenSegment( one, two.start) )
		return 'e';
	else if ( isPointBetweenSegment( one, two.end) )
		return 'e';
	else if ( isPointBetweenSegment( two, one.start) )
		return 'e';
	else if ( isPointBetweenSegment( two, one.end) )
		return 'e';

	return '0';
}

char doSegmentsIntersects(Segment one, Segment two){
	if(isEndPoint(one,two.start) || isEndPoint(one,two.end))
		if(isEndPoint(one,two.start) && isEndPoint(one,two.end))
			return 'e';
		//else
			//return 'v';	//Not quite correct.  This potentially could be 'e'
	double s,t;
	double num, denom;
	char code = '?';

	denom = (one.start[0]-one.end[0])*(two.end[1]-two.start[1])
        -(two.end[0]-two.start[0])*(one.start[1]-one.end[1]);

	//Parallel
	if(abs(denom) < ep)
		return parallelSegmentIntersection(one, two);

	num = 	one.start[0]	* ( two.end[1]		- two.start[1] ) +
			two.start[0]	* ( one.start[1]	- two.end[1] 	) +
			two.end[0]		* ( two.start[1]	- one.start[1] );

	if( (abs(num) <ep) || (abs(num -denom)<ep) )
		code = 'v';

	s = num / denom;

	num = -(one.start[0]	* ( two.start[1]	- one.end[1]	) +
			one.end[0]		* ( one.start[1]	- two.start[1]	) +
			two.start[0]	* ( one.end[1]		- one.start[1] ));

	if( (abs(num) <ep) || (abs(num -denom)<ep) )
		code = 'v';

	t = num / denom;

	if	  ( (0.0 < s) && (s < 1.0) &&
			(0.0 < t) && (t < 1.0) )
		code = '1';
	else if ( (0.0 > s) || (s > 1.0) ||
			(0.0 > t) || (t > 1.0) )
		code = '0';

	return code;
}

//Returns 0 for Sucess, -1 for parallel
int getIntersectionPoint(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, point& ipt){
	double s, num, denom;
	denom = (x1-x2) * (y4-y3) + (x4-x3) * (y2-y1);
	//Parallel
	if(abs(denom) < ep)
		return -1;

	num = 	x1	* ( y4	- y3 ) +
			x3	* ( y1	- y4 ) +
			x4	* ( y3	- y1 );

	s = num / denom;

	num = -(x1	* ( y3	- y2 ) +
			x2	* ( y1	- y3 ) +
			x3	* ( y2	- y1 ));

	ipt = make_vect<double,2>(x1 + s * ( x2 - x1 ), y1 + s * ( y2 - y1 ));
	return 0;
}

int getIntersectionPoint(Segment one, Segment two, point& ipt){
	return getIntersectionPoint(one.start[0],one.start[1],one.end[0],one.end[1],two.start[0],two.start[1],two.end[0],two.end[1], ipt);
}

int main()
{
	point o = make_vect<double,2>(-1.0,1.0), t = make_vect<double,2>(-1.0,-1.0),th = make_vect<double,2>(1.0,-1.0),f = make_vect<double,2>(1.0,1.0);
	Segment one(o,th);
	Segment two(t,f);
	Segment three(o,t);
	Segment four (th,f);

	point z = make_vect<double,2>(0.0,0.0);
	Segment a(o,z);
	Segment b(t,z);

	printf("%c\n",doSegmentsIntersects(one,two));
	printf("%c\n",doSegmentsIntersects(three,four));
	printf("%c\n",doSegmentsIntersects(b,a));
	printf("%c\n",doSegmentsIntersects(one,a));
	printf("%c\n",doSegmentsIntersects(two,a));
}
