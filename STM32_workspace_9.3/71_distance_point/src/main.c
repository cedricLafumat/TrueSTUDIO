#include<stdio.h>
#include<math.h>


double calc_distance(int x1, int y1, int x2, int y2){
	double dist = ((x2- x1)*(x2- x1))+((y2- y1)*(y2- y1));
	dist = sqrt(dist);
	return dist;
}


int main(int argc, char* argv[]){

	int x1 = 100;
	int y1 = 100;
	int x2 = 200;
	int y2 = 200;

	double res = calc_distance(x1, y1, x2, y2);
	printf("%.2f", res);

	return 0;
}
