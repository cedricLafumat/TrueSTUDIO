#include<stdio.h>

int compare_chaine(char chaine1[], char chaine2[]){
	int i = 0;
	for (i = 0; ((chaine1[i] != '\0') || (chaine2[i] != '\0')); i++){
		if (chaine1[i] == chaine2[i]){
			continue;
		}
		else if(chaine1[i] < chaine2[i]){
			return -1;
		}
		else{
			return 1;
		}
	}
return 0;
}

int main(int argc, char* argv[]){
	char chaine1[] = "Tot";
	char chaine2[] = "Toto";


	int result = compare_chaine(chaine1,chaine2);
	if (result == 0){
		printf("Les deux cha�nes de caract�res sont �gales\n");
	}
	else if (result == -1){
		printf("%s est avant � %s par ordre alphab�tique\n", chaine1, chaine2);
	}
	else{
		printf("%s est apr�s � %s par ordre alphab�tique\n", chaine1, chaine2);
	}
return 0;
}
