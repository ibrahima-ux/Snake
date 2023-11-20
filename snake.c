#include <stdio.h>
#include <stdlib.h>
#include<graph.h>
/*
void recupCase(int case, int h, int l){
    printf("case[%d][%d] est : %d ",h ,l , case);
}
*/

int main(void) {
    /*
    int l=10, h=30;
	int plateau[h][l];
	
    int i, j;
	for (i = 0; i < h; i++){
        for (j = 0; j < l; j++){
            
	    }
	}
    */
    
    InitialiserGraphique();
    CreerFenetre(10,10,900,500);

    ChoisirCouleurDessin(CouleurParComposante(0, 0, 0));
    RemplirRectangle(0,0,900,500);

    couleur Background;
    Background=CouleurParComposante(38, 132, 0);
    ChoisirCouleurDessin(Background);
    RemplirRectangle(10,10,880,400);

    ChoisirCouleurDessin(CouleurParComposante(255, 255, 255));
    int y = 80 - TailleSupPolice(2) + 410;
    EcrireTexte(15,y,"01:27",2);
    char[8] textes = "0000190";
    int x = 980 - TailleChaineEcran(textes,2);
    EcrireTexte(x,y,textes,2);

    Touche();
    FermerGraphique();
    return EXIT_SUCCESS;
}