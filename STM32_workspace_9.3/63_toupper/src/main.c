#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

int main(int argc, char* argv[]){



	FILE* file_text = NULL;
	file_text = fopen("/home/cedric/Bureau/Lafumat_Cedric/C_dossier/long_text.txt", "r+");
	char newline[128];


	char vowel[] = {'a','e','i','o','u','y','A','E','I','O','U','Y','é','à','è','ù','â','ê','î','ô','û'};
	char consomn[] = {'b','c','d','f','g','h','j','k','l','m', 'n', 'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'z',
			'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z', 'ç'};



	int nb_vowel = 0;
	int nb_cons = 0;
	int count_words = 0;
	int isvowel;



	while (fgets(newline, 128, file_text) != NULL){
			printf("%s", newline);

		for (int i = 0; newline[i] != '\0' ; i++) {
			isvowel = 0;
			/*if ((newline[i] == ' ') || (newline[i] == '.') || (newline[i] == ',')){
				count_words += 1;
			}*/
			if (newline[i] >= 97 && newline[i] <= 122){
				newline[i]=newline[i] -32;
			}
	    	for (int j = 0; vowel[j] != '\0'; j++) {
	    		if (newline[i] == vowel[j]) {
	    			nb_vowel +=1;
	    			isvowel = 1;
	    			break;
	    		}
	    	}
	    	for (int k =0; ((consomn[k] != '\0') && (!isvowel)); k++) {
	    		if (newline[i] == consomn[k]) {
	    			nb_cons += 1;
	    			break;
	    		}
	    	}
	    }
		printf("%s", newline);
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
	printf("Pourcentage de voyelle : %.2f %%\n", pct_vowel);
	printf("Pourcentage de consonne : %.2f %%\n", pct_cons);


	fclose(file_text);
	return 0;
}
