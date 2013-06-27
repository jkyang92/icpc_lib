#define X    0
#define Y    1

//returns true if point is inside of the polygon
bool baryc_tri_based ( double pgon[][2], int numverts, double point[2] )
{
    double *vtx0 = pgon[numverts-1];
    double *vtx1 = pgon[0] ;
    int count = 0;
    for (int i = 0;i<numverts;i++) {
        double x0X = vtx0[X] - point[X];
        double x1X = vtx1[X] - point[X];
        //check that point[X] is between vtx0[X] and vtx1[X]
        if ( x0X * x1X <= 0 ) {
            double a = vtx1[Y] - point[Y];
            double b = vtx0[Y] - point[Y];
            //c is signed distance from the line
            double c = ( x0X * a ) - ( x1X * b );
            //check that the point is above the line
            if ( x1X * c <= 0 && x0X * c >= 0) {
                if ( c > 0 && x0X > 0 && x1X < 0 )
                    count += 2;
                else if ( c < 0 && x0X < 0 && x1X > 0 )
                    count -= 2;
                else if ( c > 0 )
                    count++;
                else if ( c < 0 )
                    count--;
                else if ( x0X != 0 || x1X != 0 ||  a * b <= 0)
                    return true;
            }
        }
        vtx0 = vtx1;
        vtx1 += 2;
    }
    return (count==2);
}
