/* ptinpoly.c - point in polygon inside/outside code.

   by Juan J. Jiménez, Francisco R. Feito and Rafael J. Segura
   University of Jaen (Spain), juanjo@ujaen.es
   
   Code of "Computer Graphics Forum" journal 2008
   "Robust and optimized algorithms for the point-in-polygon inclusion test
   without pre-processing"

   This code contains the following algorithms:
        baryc_tri_based : sum of signs based in barycentric coordinates
                        determinant signs and an appropiated arrange of
                        calculations
        baryc_and_euclidean : sum of signs based in barycentric and 
                            euclidean signs
   Both algorithms performs a dynamic covering in which the origin of the
   covering results on (0,-1) and the test point on (0,0)
*/

#define X    0
#define Y    1

/* ======= baryc_tri_based inclusion test =================================== */

/* Input 2D polygon _pgon_ with _numverts_ number of vertices and test point
   _point_, returns 1 if inside, 0 if outside.
   
   The algorithm sums the sign of the triangles in which the point is included.
   Considers the situations of a test point on the border of the polygon.
   When a point is in a edge shared by two triangles, counts 1/2 multiplied by
   the sign of each triangle. Obtains inclusion if the total ammount is 2.
 
   We can take advantage of the reduction in the number of calculations if we 
   perform the dynamic covering proposed in Section 4.2.3. Then we replace each 
   determinant with its equivalent expression, and P and O are different.
   In this form only |PViVj| must be calculated and stored for future comparisons 
   just when the first condition is satisfied. The condition "if (P.in(ViVj)) ..." 
   could be replaced with "if (yi * yj <= 0) ..."

   For each triangle tested, the translation T(-P) of one vertex of the edge is 
   calculated at the first of the loop and stored at the end for reusing in the 
   next triangle. Some additional calculations could be avoided if we only apply 
   this transformation to x's coordinates, and substitute the expressions in which 
   y's are present with y-yp. In this form the translation for the y is only 
   performed when early rejection tests have been overcome and there is no need 
   of storing and coping later this value for the next triangle. This method works 
   fine in the first early rejection test approach.
   
   The signs in brackets represents in order the sign of |PViVj|, |OPVj| and |OViP|
   like in Table 1 (? means indifference)
*/

int baryc_tri_based ( double pgon[][2], int numverts, double point[2] )
{
register double    ty, tx, *vtx1, x0X, x1X;
register double *vtx0;
register int j, count;
register double a,b,c;

    tx = point[X] ;
    ty = point[Y] ;

    vtx0 = pgon[numverts-1];
    x0X = pgon[numverts-1][X] - tx;
    vtx1 = pgon[0] ;

    count = 0;
    for ( j = numverts+1 ; --j ; ) {
        x1X = vtx1[X] - tx;
        if ( x0X * x1X <= 0 ) {       /* reject if (?+-) or (?-+) */
    	   a = vtx1[Y] - ty;
    	   b = vtx0[Y] - ty;
    	   c = ( x0X * a ) - ( x1X * b );
    	   if ( x1X * c <= 0 ) {      /* reject if (+-?) or (-+?) */
              if (x0X * c >= 0) {     /* reject if (+?-) or (-?+) */
    			if ( c > 0 && x0X > 0 && x1X < 0 )       /* (+++) */
    				count += 2;
    			else if ( c < 0 && x0X < 0 && x1X > 0 )  /* (---) */
    				count -= 2;
    			else if ( c > 0 )  /* (++0) or (+0+), (+00) not possible */
    				count++;
    			else if ( c < 0 )  /* (--0) or (-0-), (-00) not possible */
    				count--;
    			else if ( x0X != 0 || x1X != 0 )      /* (0??) */
    				return 1;
    			else if ( a * b <= 0 ) return (1);    /* (000) */
    		 }	
    	  }
       }
       x0X = x1X;
       vtx0 = vtx1;
       vtx1 += 2;
     }
     return (count==2);
}

/* ======= baryc_and_euclidean inclusion test =================================== */

/* Input 2D polygon _pgon_ with _numverts_ number of vertices and test point
   _point_, returns 1 if inside, 0 if outside.
   
   The algorithm sums the sign of the triangles in which the point is included.
   Considers the situations of a test point on the border of the polygon.
   When a point is in a edge shared by two triangles, counts 1/2 multiplied by
   the sign of each triangle. Obtains inclusion if the total ammount is 2.
 
   We perform the dynamic covering proposed in Section 4.2.3. and combine barycentric
   and Euclidean calculations to obtain the sign of the triangles.

   For each triangle tested, the translation T(-P) of one vertex of the edge is 
   calculated at the first of the loop and stored at the end for reusing in the 
   next triangle. Some additional calculations could be avoided if we only apply 
   this transformation to x's coordinates, and substitute the expressions in which 
   y's are present with y-yp. In this form the translation for the y is only 
   performed when early rejection tests have been overcome and there is no need 
   of storing and coping later this value for the next triangle. This method works 
   fine in the first early rejection test approach.
*/

int baryc_and_euclidean ( double pgon[][2], int numverts, double point[2] )
{
register double    ty, tx, *vtx1, x0X, x1X;
register double *vtx0, x0Yt, x1Yt;
register int j, count;
register double a, b;

    tx = point[X] ;
    ty = point[Y] ;

    vtx0 = pgon[numverts-1];
    x0X = pgon[numverts-1][X] - tx;
    vtx1 = pgon[0] ;

    count = 0;
    for ( j = numverts+1 ; --j ; ) {
        x1X = vtx1[X] - tx;
        if ( x0X*x1X <= 0 ) {                   /* reject triangles with beta<0 or gamma<0 */
    	   x0Yt = vtx0[Y] - ty;
    	   x1Yt = vtx1[Y] - ty;
    	   if (( x0Yt >= 0) || ( x1Yt >= 0 )) { /* reject triangles under x-axis */
    	      if ( x0X > x1X ) {
    				a = x0X*x1Yt ; b = x1X*x0Yt ;
    				if ( a > b ) {
    					if ( x0X == 0 || x1X == 0 ) {     /* on edge OVi or OVj */
    						count++;
    					} else {                          /* inside triangle OViVj */
    						count += 2;
    					}
    				} else if ( a == b ) {                /* on edge ViVj or vertices Vi or Vj */
    					return (1);
    				}
    		  } else if ( x0X < x1X ) {
    				a = x0X*x1Yt ; b = x1X*x0Yt ;
    				if ( a < b ) {
    					if ( x0X == 0 || x1X == 0 ) {     /* on edge OVi or OVj */
    						count--;
    					} else {                          /* inside triangle OViVj */
    						count -= 2;
    					}
    				} else if ( a == b ) {                /* on edge ViVj or vertices Vi or Vj */
    					return (1);
    				}
    		  } else {
    			     if (( x0Yt <= 0 ) || ( x1Yt <= 0 )) {   /* on vertical edge ViVj */
    				    return (1);
                     }
              }
           }
        }
        x0X = x1X;
        vtx0 = vtx1;
        vtx1 += 2;
    }
    return (count==2);
}

