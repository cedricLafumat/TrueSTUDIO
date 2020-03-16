#include<stdio.h>
#include<stdbool.h>

int is_equal(int c, int d){
	if (c == d){
		return 0;
	}
	else{
		return 1;
	}
}

int main(int argc, char* argv[]){
	int a;
	int b;
	while (true){
		printf("Saisissez deux nombres : ");
		scanf("%d %d", &a,&b);

		int res = is_equal(a,b);
		if (res == 0){
			printf("Les deux nombres sont égaux\n");
		}
		else{
			printf("Non égaux\n");
		}
	}
	return 0;
}
