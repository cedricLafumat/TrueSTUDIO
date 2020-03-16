#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define SIZELINE 128

char vowel[] = {'a','e','i','o','u','y','A','E','I','O','U','Y','é','à','è','ù','â','ê','î','ô','û'};
char consomn[] = {'b','c','d','f','g','h','j','k','l','m', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z',
		'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z', 'ç'};


bool checkvowel(char textchar){
	bool findvowel;
	findvowel = false;
	for (int indexvowel = 0; (vowel[indexvowel] != '\0') && (findvowel == false); indexvowel++){
		if(textchar == vowel[indexvowel]){
			findvowel =  true;
		}
	}
	return findvowel;
}

bool checkconsomn(char textchar){
	bool findconsomn;
	findconsomn = false;
	for (int indexconsomn = 0; (consomn[indexconsomn] != '\0') && (findconsomn == false); indexconsomn++){
		if(textchar == consomn[indexconsomn]){
			findconsomn = true;
		}
	}
	return findconsomn;
}

bool checkword(char textchar){
	bool endword;
	endword = false;
	if ((textchar == ' ') || (textchar == '.') || (textchar == '\n')){
		endword = true;
	}
	return endword;
}

int main(int argc, char* argv[]){

	FILE* file_text = NULL;
	file_text = fopen("/home/cedric/Bureau/Lafumat_Cedric/C_dossier/long_text.txt", "r");

	char newline[SIZELINE];

	int nb_vowel = 0;
	int nb_cons = 0;
	int count_words = 0;

	while (fgets(newline, SIZELINE, file_text) != NULL){
		printf("%s", newline);

		//Parcours du texte
		for (int indextext = 0; newline[indextext] != '\0' ; indextext++) {
			//----------------    Compteur de mot
			if (checkword(newline[indextext]) == true ){
				count_words += 1;
			}
			//----------------    Traitement des voyelles
			if (checkvowel(newline[indextext]) == true) {
				nb_vowel +=1;
			}
			//----------------    Traitement des consomnes
			else if (checkconsomn(newline[indextext]) == true) {
				nb_cons +=1;
			}
		}
	}
	int nb_letters;
	nb_letters = nb_vowel + nb_cons;
	printf("Nombre de Voyelles : %d\n", nb_vowel);
	printf("Nombre de Consonnes : %d\n", nb_cons);
	printf("Nombre de lettres: %d\n", nb_letters);
	printf("Nombre de mot : %d\n", count_words);

	float pct_vowel;
	float pct_cons;
	pct_vowel = ((nb_vowel *100.00) / nb_letters);
	pct_cons = 100.00 - pct_vowel;
	printf("Pourcentage de voyelle : %.3f %%\n", pct_vowel);
	printf("Pourcentage de consonne : %.3f %%\n", pct_cons);


	fclose(file_text);
	return 0;
}
