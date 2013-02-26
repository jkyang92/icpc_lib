#include <cmath>
#include <stdio.h>
using std::abs;
double ep = 1e-10;

struct Point{
	double x,y;
	Point(double x,double y){
		this->x =x;
		this->y = y;
	}

	bool equals(Point o){
		return abs(x-o.x)<ep && abs(y-o.y)<ep;
	}
};

double crossProduct(Point start1, Point start2, Point end1, Point end2){
	return (end1.x-start1.x)*(end2.y-start2.y)-(end1.y-start1.y)*(end2.x-start2.x);
}

double triangleArea( Point a, Point b, Point c){
	return 	abs(crossProduct(a, a, b, c));
}

bool arePointsCollinear(Point a, Point b, Point c){
	return triangleArea(a, b, c)<ep;
}

struct Segment{
	Point& start, &end;
	Segment (Point &s,Point &e):start(s),end(e)	{}
};

char doSegmentsIntersects(Segment one, Segment two);

bool containsPoint(Segment s, Point point){
	return s.start.equals(point)|| s.end.equals(point);
}

bool doSegmentsIntersectExceptAtEnds(Segment one, Segment two){
	char a = doSegmentsIntersects(one, two);
	return a!='v' && a!='0' && a!='e';
}

bool doSegmentsIntersectAtEdge(Segment one, Segment two){
	char a = doSegmentsIntersects(one, two);
	return a=='e';
}

bool doSegmentsIntersectAtVertex(Segment one, Segment two){
	char a = doSegmentsIntersects(one, two);
	return a=='v';
}

bool doSegmentsIntersect(Segment one, Segment two){
	return doSegmentsIntersects(one, two)!='0';
}

bool isPointBetweenSegment(Segment one, Point p){
	if ( abs(one.start.x - one.end.x)>ep )
		return ((one.start.x <= p.x) && (p.x <= one.end.x)) ||
				((one.start.x >= p.x) && (p.x >= one.end.x) );
	else
		return ((one.start.y <= p.y) && (p.y <= one.end.y)) ||
				((one.start.y >= p.y) && (p.y >= one.end.y));
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
	if(containsPoint(one,two.start) || containsPoint(one,two.end))
		if(containsPoint(one,two.start) && containsPoint(one,two.end))
			return 'e';
		//else
			//return 'v';	//Not quite correct.  This potentially could be 'e'
	double s,t;
	double num, denom;
	char code = '?';

	denom =	one.start.x * ( two.end.y   - two.start.y ) +
		one.end.x   * ( two.start.y - two.end.y   ) +
		two.end.x   * ( one.end.y   - one.start.y ) +
		two.start.x * ( one.start.y - one.end.y	  );

	//Parallel
	if(abs(denom) < ep)
		return parallelSegmentIntersection(one, two);

	num = 	one.start.x * ( two.end.y   - two.start.y ) +
		two.start.x * ( one.start.y - two.end.y   ) +
		two.end.x   * ( two.start.y - one.start.y );

	if( (abs(num) <ep) || (abs(num -denom)<ep) )
		code = 'v';

	s = num / denom;

	num = -(one.start.x * ( two.start.y - one.end.y	  ) +
 		one.end.xi  * ( one.start.y - two.start.y ) +
		two.start.x * ( one.end.y   - one.start.y ));

	if( (abs(num) <ep) || (abs(num -denom)<ep) )
		code = 'v';

	t = num / denom;

	if ( (0.0 < s) && (s < 1.0) &&
             (0.0 < t) && (t < 1.0) )
		code = '1';
	else if ( (0.0 > s) || (s > 1.0) ||
		  (0.0 > t) || (t > 1.0) )
		code = '0';

	return code;
}

//Returns 0 for Sucess, -1 for parallel
int getIntersectionPoint(double x1, double y1, double x2, double y2,
                         double x3, double y3, double x4, double y4, Point& ipt){
	double s, num, denom;

	denom = x1 * ( y4 - y3 ) +
		x2 * ( y3 - y4 ) +
		x4 * ( y2 - y1 ) +
		x3 * ( y1 - y2 );
	//Parallel
	if(abs(denom) < ep)
		return -1;

	num =   x1 * ( y4 - y3 ) +
		x3 * ( y1 - y4 ) +
		x4 * ( y3 - y1 );

	s = num / denom;

	num = -(x1 * ( y3 - y2 ) +
		x2 * ( y1 - y3 ) +
		x3 * ( y2 - y1 ));

	ipt = Point( x1 + s * ( x2 - x1 ), y1 + s * ( y2 - y1 ));
	return 0;
}

int getIntersectionPoint(Segment one, Segment two, Point& ipt){
	return getIntersectionPoint(one.start.x,one.start.y,one.end.x,one.end.y,
                                two.start.x,two.start.y,two.end.x,two.end.y, ipt);
}
