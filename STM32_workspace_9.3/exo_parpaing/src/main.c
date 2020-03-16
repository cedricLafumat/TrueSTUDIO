#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


int ref_weight = 19000;
int ref_width = 200;
int ref_length = 500;
int ref_height = 200;
int value_weight;
int value_width;
int value_length;
int value_height;
int weight_input;
int width_input;
int length_input;
int height_input;
int tolerance_input;
int tolerance;


bool in_range(int Value, int Ref, int tolerance){
	int Value_min;
	int Value_max;
	Value_min = Ref - ((Ref * tolerance) /100);
	Value_max = Ref + ((Ref * tolerance) /100);
	if ((Value < Value_max) && (Value > Value_min)){
		return true;
	}
	else {
		return false;
	}
}

int check_number_error() {
	int cpt_error = 0;
	if (!in_range(value_length, ref_length, tolerance)){
		cpt_error += 1;
	}
	if (!in_range(value_width, ref_width, tolerance)){
		cpt_error +=1;
	}
	if (!in_range(value_height, ref_height, tolerance)) {
		cpt_error +=1;
	}
	return cpt_error;
}



int main(int argc , char* argv []) {



	printf("Saisissez une valeur pour le poids: ");
	weight_input = scanf("%d", &value_weight);
	printf("Saisissez une valeur pour le longueur: ");
	width_input = scanf("%d", &value_length);
	printf("Saisissez une valeur pour le largeur: ");
	length_input = scanf("%d", &value_width);
	printf("Saisissez une valeur pour le hauteur: ");
	height_input = scanf("%d", &value_height);
	printf("Saisissez une valeur pour la tolérance: ");
	tolerance_input = scanf("%d", &tolerance);
	int cpt =0;
	cpt=check_number_error();
	if (in_range(value_weight, ref_weight, tolerance)){
		if (cpt <= 1){
			printf("categorie A");
		}
		else {
			printf("categorie B");
		}
	}
	else {
		if (cpt == 0 ){
			printf("categorie B");
		}
		else {
			printf("categorie C");
		}
	}
	return 0;
}
