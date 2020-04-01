/*
 * f1.c
 *
 *  Created on: 2 avr. 2020
 *      Author: cedric
 */

#include "f1.h"
#include <stdio.h>

//int MA_POURRIE_GLOBALE=12;

int f1_glob = 11;   // définition variable global
// DÉFINITION == LA MEMOIRE EST ALLOUÉE ICI
// 1 seule définition d'une même variable.
// durée de vie : Tout le programme (c'est la définition d'une variable globale), global à tous les .c
// porté : partout


static int f1_glob_limite_au_fichier = 20; // Définition == allocation de mémoire ici
		// durée de vie : tout le programme.
		// porté : Ce bloc de compilation uniquement (static), global à ce .c uniquement
		// static sur une globale ==> modification de la porté de la variable
		// La variable n'est visible que dans l'unité de compilation
		// visible que dans le fichier f1.c
		// **SUPER PROTECTION**  POUR LA LIBRAIRIE, pcq par erreur, ce n'est plus possible
		// a qq d'autre d'utiliser ma variable globale

void f11(void) {

//	MA_POURRIE_GLOBALE++;
	int ma_local = 1; // définition de la variable, dans la pile, elle n'existe que le temps de f11
	ma_local++;

	printf("f11:ma_local= %d\n", ma_local);

	static int ma_local_static = 1; // définition local. static => La zone mémoire reste persistance tout le temps du programme
	// static => Durée de vie == tout le programme
	// local  => Porté : Le bloc de la fonction
	// usage : Ca permet d'avoir une variable qui continue a exister
	// lors des appels successif (pour se "souvenir" de qq)
	ma_local_static++;
	printf("f11:ma_local_static= %d (addr=%p)\n", ma_local_static,
			&ma_local_static);

	f1_glob++;
	printf("f11:Ma glob = %d (addr=%p)\n", f1_glob, &f1_glob);

	f1_glob_limite_au_fichier++;
	printf("f11:f1_glob_limite_au_fichier = %d (addr=%p)\n", f1_glob_limite_au_fichier,
			&f1_glob_limite_au_fichier);

}

void f12(void) {

	static int ma_local_static = 5; // Cette variable n'a RIEN A VOIR AVEC ma_loca_static de f11
	ma_local_static++;
	printf("f12:ma_local_static= %d (addr=%p)\n", ma_local_static,
			&ma_local_static);

	f1_glob++;
	printf("f12:Ma glob = %d (addr=%p)\n", f1_glob, &f1_glob);

	f1_glob_limite_au_fichier++;
	printf("f11:f1_glob_limite_au_fichier = %d (addr=%p)\n", f1_glob_limite_au_fichier,
			&f1_glob_limite_au_fichier);

}


