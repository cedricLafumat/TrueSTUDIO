#include<stdio.h>

int and_bit_by_bit(int param_A, int param_B) {
	int result;
	if (param_A && param_B) {
		result = 1;
	} else {
		result = 0;
	}
	return result;
}

int or_bit_by_bit(int param_A, int param_B) {
	int result;
	if (param_A || param_B) {
		result = 1;
	} else {
		result = 0;
	}
	return result;
}

int compl_to_1(int param_A){
	int result;
	if (param_A == 1){
		result = 0;
	}
	else{
		result = 1;
	}
	return result;
}

int main(void) {
	int result_and_bit_by_bit;
	int result_or_bit_by_bit;
	int result_compl_to_1;
	int param_A = 1;
	int param_B = 0;
	result_and_bit_by_bit = and_bit_by_bit(param_A, param_B);
	result_or_bit_by_bit = or_bit_by_bit(param_A, param_B);
	result_compl_to_1 = compl_to_1(param_A);

	printf("%i\n", result_and_bit_by_bit);
	printf("%i\n", result_or_bit_by_bit);
	printf("%i\n", result_compl_to_1);


	return 0;
}
