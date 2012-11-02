#include <stdio.h>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <functional>
#include <limits.h>

using namespace std;
template<typename T,int n>
class vect{
	T val[n];
	public:
	//always constructs the zero vector
	vect(){ fill_n(val,n,0); }
	vect(const vect<T,n>& other){ copy(other.val,other.val+n,val);}
	vect<T,n>& operator=(const vect<T,n>& other){
		if(&other==this) return *this;
		copy(other.val,other.val+n,val);
		return *this;
	}
#define V_OP(op)                                                        \
	vect<T,n>& operator op ## =(const vect<T,n>& other){                \
		for(int i=0;i<n;i++) val[i] op ##= other.val[i];                \
		return *this;                                                   \
	}
	V_OP(+);
	V_OP(-);
#undef V_OP
	vect<T,n> operator-() const{
		vect<T,n> ret;
		transform(val,val+n,ret.val,negate<T>());
		return ret;
	}
	//note, this is the length squared norm
	T norm() const{ return (*this)*(*this); }
	bool operator==(const vect<T,n>& other) const{ return equal(val,val+n,other.val); }
	bool operator!=(const vect<T,n>& other) const{ return !(this==other); }
	//dot product
	T operator*(const vect<T,n>& other) const{ return inner_product(val,val+n,other.val,(T)0); }
#define S_OP(op)                                             \
	vect<T,n>& operator op ## =(const T& k){                 \
		for(int i=0;i<n;i++) val[i] op ## = k;               \
		return *this;                                        \
	}
	S_OP(*);
	S_OP(/);
#undef S_OP
	const T& operator[](int index) const { return val[index]; }
	T& operator[](int index){ return val[index]; }
};

#define WRAP(op,t2)                                                     \
	template<typename T,int n>                                          \
vect<T,n> operator op (const vect<T,n>& a,t2 b){                    \
	vect<T,n> ret (a);                                              \
	return (ret op##= b);                                           \
}
#define COMMA ,
	WRAP(+,const vect<T COMMA n>&)
	WRAP(-,const vect<T COMMA n>&)
	WRAP(*,const T&)
WRAP(/,const T&)
#undef WRAP
	//backwards versions
	template<typename T, int n>
	vect<T,n> operator*(const T& k, const vect<T,n>& a){ return a*k; }
	template<typename T, int n>
	vect<T,n> operator/(const T& k, const vect<T,n>& a){ return a/k; }

#include <cstdarg>

	//additional utilities for vect.cpp
	template<typename T>
	vect<T,3> cross(const vect<T,3>& a, const vect<T,3>& b){
		vect<T,3> ret;
		ret[0] = a[1]*b[2]-a[2]*b[1];
		ret[1] = a[2]*b[0]-a[0]*b[2];
		ret[2] = a[0]*b[1]-a[1]*b[0];
		return ret;
	}

template<typename T,int n,int m>
vect<T,n> change_dim(const vect<T,m>& v){
	vect<T,n> ret;
	for(int i=0;i<min(n,m);i++) ret[i] = v[i];
	return ret;
}
template<typename T,int n>
vect<T,n> make_vect(T first,...){
	va_list args;
	vect<T,n> ret;
	ret[0]=first;
	va_start(args,first);
	for(int i=1;i<n;i++)
		ret[i]=va_arg(args,T);
	va_end(args);
	return ret;
}

//project a onto b
template<typename T,int d>
vect<T,d> proj(vect<T,d> a,vect<T,d> b){
	return ((a*b)/(b*b))*b;
}

template<typename T,int n>
vect<T,n> orth_proj(const vect<T,n>& a, const vect<T,n>& b){
	return a-proj(a,b);
}

#include <utility>

#ifndef EPSILON
#define EPSILON 1e-10
#endif

typedef vect<double,2> point;

//note, will return false if the two circles have the same center
bool circle_intersection(point c1, double r1, point c2, double r2,pair<point,point>& ints){
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

bool circle_line_intersection(point c, double r, point b, vect<double,2> v,pair<point,point>& ints){
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

const int mo = 20;

vect<double,2> points[mo*mo*mo];
vector<int> circlePoints[mo];
vector<int> linePoints[mo];

typedef pair<point,double> circle;
vector<circle> circles;
typedef pair<point, vect<double,2> > line;
vector<line> lines;

double dist[mo*mo*mo][mo*mo*mo];

double pd2(point p1, point p2){
	vect<double, 2> f;
	f[0] = p1[0]-p2[0];
	f[1] = p1[1]-p2[1];
	return f.norm();
}

//Returns 0 for Sucess, -1 for parallel
int getIntersectionPoint(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, point& ipt){
	double s, num, denom;
	//printf("x1 %lf y1 %lf\n",x1,y1);
	denom = (x1-x2) * (y4-y3) + (x4-x3) * (y2-y1);
	//Parallel
	if(abs(denom) < 1E-14)
		return -1;

	num = 	x1	* ( y4	- y3 ) +
		x3	* ( y1	- y4 ) +
		x4	* ( y3	- y1 );

	s = num / denom;

	num = -(x1	* ( y3	- y2 ) +
		x2	* ( y1	- y3 ) +
		x3	* ( y2	- y1 ));

	ipt = make_vect<double,2>(x1 + s * ( x2 - x1 ), y1 + s * ( y2 - y1 ));
	//printf("num %lf denom %lf (x,y) (%lf %lf) (%lf %lf) (%lf %lf) (%lf %lf) inter: %lf %lf s %lf\n", num, denom,x1,y1,x2,y2,x3,y3,x4,y4,ipt[0],ipt[1],s);
	return 0;
}

int main()
{
	bool looking=true;
	while(true){
		circles.clear();
		lines.clear();
		while(true){
			char a[100];
			scanf("%s",a);
			//printf("ai %c\n", a[0]);
			if(a[0]=='*' && !looking)
				return 0;
			else if(a[0]=='*'){
				looking = false;
				break;
			}
			else if(a[0]=='L'){
				//printf("found line\n");
				double x1,y1,x2,y2;
				scanf("%lf %lf %lf %lf",&x1,&y1,&x2,&y2);
				point p; p[0]=x1;p[1]=y1;
				vect<double,2> d;d[0]=x2-x1;d[1]=y2-y1;
				line l(p,d);
				lines.push_back(l);
			}
			else{
				//printf("found circle\n");
				double x,y,r;
				scanf("%lf %lf %lf",&x,&y,&r);
				point p;p[0]=x;p[1]=y;
				circles.push_back(circle(p,r));
			}
			looking = true;
		}
		//printf("Here\n");
		int numPoints = 0;
		for(int i=0;i<lines.size();i++)
			linePoints[i].clear();
		for(int i=0;i<circles.size();i++)
			circlePoints[i].clear();
		for(int i =0; i <circles.size();i++){
			circle c1 = circles[i];
			for(int j=0; j < i; j++){
				circle c2 = circles[j];
				pair<point, point> ints;
				if(circle_intersection(c1.first, c1.second, c2.first, c2.second,ints)){
					points[numPoints]=ints.first;
					circlePoints[i].push_back(numPoints);
					circlePoints[j].push_back(numPoints);
					numPoints++;

					points[numPoints]=ints.second;
					circlePoints[i].push_back(numPoints);
					circlePoints[j].push_back(numPoints);
					numPoints++;
				}
			}
			for(int j=0; j < lines.size();j++){
				line l1 = lines[j];
				pair<point,point> ints;
				if(circle_line_intersection(c1.first, c1.second,l1.first,l1.second,ints)){
					double ds1 = pd2(l1.first,ints.first);
					double de1 = pd2(l1.second+l1.first, ints.first);
					double ds2 = pd2(l1.first,ints.second);
					double de2 = pd2(l1.second+l1.first, ints.second);
					double le = l1.second.norm();

					if(le-ds1>-1E-14 && le-de1>-1E-14){
						points[numPoints]=ints.first;
						circlePoints[i].push_back(numPoints);
						linePoints[j].push_back(numPoints);
						numPoints++;
					}	
					if(le-ds2>-1E-14 && le-de2>-1E-14){
						points[numPoints]=ints.second;
						circlePoints[i].push_back(numPoints);
						linePoints[j].push_back(numPoints);
						numPoints++;
					}
				}
			}
		}
		for(int i =0; i < lines.size();i++){
			line l1 = lines[i];
			point p1 = l1.first;
			point p2 = l1.second;
			p2+=p1;
			//printf("examing lines %lf %lf\n",p1[0],p1[1]);
			for(int j=0; j< i;j++){
				line l2 = lines[j];
				point p3 = l2.first;
				point p4 = l2.second;
				p4+=p3;
				point p;
				int result = getIntersectionPoint(p1[0],p1[1],p2[0],p2[1],p3[0],p3[1],p4[0],p4[1],p);
				
				if(result==0){

					double ds1 = pd2(p1,p);
					double de1 = pd2(p2,p);
					double ds2 = pd2(p3,p);
					double de2 = pd2(p4,p);
					double le = l1.second.norm();
					double le2 = l2.second.norm();
					//printf("ds1 %lf de1 %lf le %lf p2(%lf %lf)\n",ds1,de1,le, p2[0], p2[1]);	
					if(le-ds1>-1E-14 && le-de1>-1E-14 && le2-ds2>-1E-14 && le2-de2>-1E-14){
						points[numPoints]=p;
						//printf("found interpoint: i %d j %d (%lf %lf)\n",i,j,p[0],p[1]);
						linePoints[i].push_back(numPoints);
						linePoints[j].push_back(numPoints);
						numPoints++;
					}
				}
			}
			//printf("adding points to %d %d %d\n",i,numPoints,numPoints+1);
			points[numPoints]=p1;
			linePoints[i].push_back(numPoints);
			numPoints++;

			points[numPoints]=p2;
			linePoints[i].push_back(numPoints);
			numPoints++;
		}
		//printf("num points: %d circles: %d lines %d\n",numPoints,circles.size(),lines.size());
		for(int i=0; i < numPoints; i++){
			fill(dist[i],dist[i]+numPoints,-1);
			dist[i][i]=0;
		}
		double max= -1;
		for(int i=0;i <lines.size();i++){
			//printf("line[%d], linePoints size %d\n",i,linePoints[i].size());
			for(int j=0; j < linePoints[i].size(); j++){
				for(int k=0; k < j; k++){
					int p1 = linePoints[i][j];
					int p2 = linePoints[i][k];
					double dx = points[p1][0]-points[p2][0];
					double dy = points[p1][1]-points[p2][1];
					//printf("adding dist: %d %d %lf\n",p1,p2,sqrt(dx*dx+dy*dy));
					dist[p1][p2] = sqrt(dx*dx+dy*dy);
					dist[p2][p1] = dist[p1][p2];
				}
			}
		}
		for(int i=0; i <circles.size();i++){
			circle c1 = circles[i];
			for(int j=0; j<circlePoints[i].size(); j++){
				for(int k=0; k<j;k++){
					int p1 = circlePoints[i][j];
					int p2 = circlePoints[i][k];
					double rad1 = atan2((c1.first)[1]-points[p1][1], (c1.first)[0]-points[p1][0]);
					double rad2 = atan2((c1.first)[1]-points[p2][1], (c1.first)[0]-points[p2][0]);
					double r = circles[i].second;
					double drad = abs(rad1-rad2);
					const double pi = 3.141592653;
					if(drad > pi)
						drad = 2.0*pi-drad;
					double distance = drad*r;
					dist[p1][p2] = distance;
					dist[p2][p1] = distance;
				}
			}
		}
		for(int k=0; k < numPoints;k++)
			for(int i=0; i<numPoints; i++)
				for(int j=0;j<numPoints;j++){
					if(dist[i][k]==-1 || dist[k][j]==-1)
						continue;
					if(dist[i][j]==-1)
						dist[i][j]= dist[i][k]+dist[k][j];
					else
						dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
					//printf("i j %d %d %lf %lf\n",i,j,dist[i][j],max);
				}
		for(int j=0; j < numPoints;j++)
			for(int i=0; i<numPoints; i++){
				//printf("i %d j %d (%lf %lf) (%lf %lf) %lf %lf\n",i,j,points[i][0],points[i][1],points[j][0],points[j][1],dist[i][j],max);
				max = (dist[i][j]>max)?dist[i][j]:max;
			}
		
		printf("%.1lf\n",max);
	}
}
