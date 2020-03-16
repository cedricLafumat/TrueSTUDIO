#ifndef CGI_PILE_H
#define CGI_PILE_H

 /*  Structure repr�sentant un �l�ment de la pile. */

        typedef struct pile
        {
                int valeur;
                struct pile *prec;
        } pile ;

#ifdef __cplusplus
extern "C" {
#endif

 /*  Push empile une valeur sur la pile. */

        void Push(pile **, int);


 /*  Pop retire la derni�re valeur empil�e sur la pile. */

        int Pop(pile **);


 /*  Clear vide la pile. */

        void Clear(pile **);


 /*  Length retourne le nombre d'�l�ments de la pile. */

        int Length(pile *p);


 /*  Affiche la totalit� de la pile en commen�ant par le sommet. */

        void View(pile *);

#ifdef __cplusplus
}
#endif

#endif
