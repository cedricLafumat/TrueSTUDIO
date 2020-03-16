#include<stdio.h>
#include<math.h>

typedef struct {
    int x;
    int y;
} point;



double calc_distance(point p1, point p2){
	double dist = ((p2.x- p1.x)*(p2.x- p1.x))+((p2.y - p1.y)*(p2.y - p1.y));
	dist = sqrt(dist);
	return dist;
}


int main(int argc, char* argv[]){

	point p1;
	p1.x = 100;
	p1.y = 100;

	point p2;
	p2.x = 300;
	p2.y = 300;

	double res = calc_distance(p1, p2);
	printf("Distance entre p1 et p2 : %.2f\n", res);
	printf("Les coordonnées du point p1 sont 'x:%d y:%d'\n", p1.x, p1.y);
	printf("Les coordonnées du point p2 sont 'x:%d y:%d'\n", p2.x, p2.y);

	return 0;
}
