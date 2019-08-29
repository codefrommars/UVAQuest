//https://code.google.com/codejam/contest/32013/dashboard#s=p2

#include <cstdio>
#include <cmath>
#include <assert.h>

//Circle centered at 0, 0
double intersect_seg_circle( double x0, double y0, double x1, double y1, double cr, double* out_x, double* out_y ) {
	//Find d
	double dx = x1 - x0;
	double dy = y1 - y0;
	double len = sqrt(dx*dx + dy*dy);
	dx /= len;
	dy /= len;
	
	double a = 1.0; //dx * dx + dy * dy must always be 1
	double b = 2 * (x0 * dx + y0 * dy);
	double c = x0 * x0 + y0 * y0 - cr * cr;
	
	double det = b*b - 4*a*c;
	
	if( det < 0 )//No intersection
		return -1.0;	
	
	double sq_part = sqrt(det);
	
	double t = ( -b + sq_part ) / ( 2 * a );
	
	if( t < 0 )
		t = ( -b - sq_part ) / ( 2 * a );
	
	*out_x = x0 + t * dx;
	*out_y = y0 + t * dy;
	
	return t;
}

bool inline circle_contains(double x, double y, double cr ){
	return x*x + y*y < cr*cr;
}

void inline cut_segment(double cr, double ox, double oy, double endx, double endy, double* out_x, double* out_y){
	double t = intersect_seg_circle(ox, oy, endx, endy, cr, out_x, out_y);
	assert( t >= 0 );
}

double area_tri(double x0, double y0, double x1, double y1, double x2, double y2){
	double ax = x1 - x0;
	double ay = y1 - y0;
	
	double bx = x2 - x0;
	double by = y2 - y0;
	
	return abs(0.5 * (ax * by - ay * bx));
}

double area_circle_seg(double x0, double y0, double x1, double y1, double cr) {	
	double mag_cross = abs(x0 * y1 - y0 * x1);
	double angle = asin( mag_cross / (cr * cr) );	
	
	double area_sector = 0.5 * angle * cr * cr;
	double area_triangle = 0.5 * mag_cross;
	
	return area_sector - area_triangle;
}

double inscr_area(double px[4], double py[4], double cr) {
	if( !circle_contains(px[0], py[0], cr) )
		return 0;
	
	bool inside3 = circle_contains(px[3], py[3], cr);
	if( inside3 ){//full area		
		return (px[1] - px[0]) * (py[2] - py[0]);	
	}
	
	//3 is out of the circle
	bool inside1 = circle_contains(px[1], py[1], cr);
	if( !inside1 )
		cut_segment(cr, px[0], py[0], px[1], py[1], &px[1], &py[1]);
	
	bool inside2 = circle_contains(px[2], py[2], cr);
	if( !inside2 )
		cut_segment(cr, px[0], py[0], px[2], py[2], &px[2], &py[2]);
	
	if( !inside1 && !inside2 )
		return area_tri(px[0], py[0], px[1], py[1], px[2], py[2]) + area_circle_seg(px[1], py[1], px[2], py[2], cr);
	
	if( inside1 && inside2 ){
		double e1x, e1y, e2x, e2y;
		cut_segment(cr, px[1], py[1], px[3], py[3], &e1x, &e1y);
		cut_segment(cr, px[2], py[2], px[3], py[3], &e2x, &e2y);
		
		double as = area_circle_seg(e1x, e1y, e2x, e2y, cr);

		return 	area_tri(px[0], py[0], px[1], py[1], e1x, e1y) +
				area_tri(px[0], py[0], px[2], py[2], e2x, e2y) +
				area_tri(px[0], py[0], e1x, e1y, e2x, e2y) + 
				area_circle_seg(e1x, e1y, e2x, e2y, cr);
	}
	
	//one is in, the other is out
	double area_circular = 0;
	if( !inside1 ){
		cut_segment(cr, px[2], py[2], px[3], py[3], &px[3], &py[3]);
		area_circular = area_circle_seg(px[1], py[1], px[3], py[3], cr);
	}
	
	if( !inside2 ){
		cut_segment(cr, px[1], py[1], px[3], py[3], &px[3], &py[3]);
		area_circular = area_circle_seg(px[3], py[3], px[2], py[2], cr);
	}
	
	return 	area_circular + 
			area_tri(px[0], py[0], px[1], py[1], px[3], py[3]) +
			area_tri(px[0], py[0], px[3], py[3], px[2], py[2]);
}

void inline set_square(double* px, double* py, double x, double y, double len){
	px[0] = x;
	py[0] = y;
	px[1] = x + len;
	py[1] = y;
	px[2] = x;
	py[2] = y + len;
	px[3] = x + len;
	py[3] = y + len;
}

double find_prob(double f, double R, double t, double r, double g) {
	double delta = 2 * r + g;
	double cr = R - t - f;
	
	double len = g - 2 * f;
	
	if( len <= 0 )
		return 1;
	
	int gCount = ceil(cr / delta);
	
	double esc_area = 0;
	
	double px[4];
	double py[4];
	
	for(int i = 0; i < gCount; i++){
		for(int j = 0; j < gCount; j++){
			double x = r + f + delta * i;
			double y = r + f + delta * j;
			
			set_square(&px[0], &py[0], x, y, len);
			
			esc_area += inscr_area(px, py, cr);
		}
	}
	
	double area = M_PI * R * R * 0.25;
	return 1 - esc_area / area;
}

int main(){
	int n;
	std::setbuf(stdout, NULL);
	
	std::scanf("%i", &n);
	
	for(int i = 0; i < n; i++){
		float f, R, t, r, g;		
		std::scanf("%f %f %f %f %f\n", &f, &R, &t, &r, &g);
		float p = find_prob(f, R, t, r, g);
		std::printf("Case #%i: %.6f\n", i + 1, p);
	}
}