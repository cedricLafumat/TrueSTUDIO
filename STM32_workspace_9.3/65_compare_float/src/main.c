#include<stdio.h>
#include<stdbool.h>

int is_equal(float c, float d){
	if (c == d){
		return 0;
	}
	else if (c < d){
		return -1;
	}
	else{
		return 10;
	}
}

int main(int argc, char* argv[]){
	float a;
	float b;
	while (true){
		printf("Saisissez deux nombres flottant: ");
		scanf("%f %f", &a,&b);

		int res = is_equal(a,b);
		if (res == 0){
			printf("Les deux nombres sont égaux\n");
		}
		else if (res == -1){
			printf("%.2f est inférieur à %.2f\n", a, b);
		}
		else{
			printf("%.2f est supérieur à %.2f\n", a, b);
		}
	}
	return 0;
}
