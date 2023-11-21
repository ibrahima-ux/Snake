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
    int windowsMargin = 10;
    int nbligne = 40, nbcolone = 60;
    int taillecase = 20;
    int windowsH = taillecase*nbligne + windowsMargin*3, windowsL = taillecase*nbcolone + windowsMargin*2;
    CreerFenetre(10,10,windowsL,windowsH);

    ChoisirCouleurDessin(CouleurParComposante(0, 0, 0));
    RemplirRectangle(0,0,windowsL,windowsH);

    couleur Background;
    Background=CouleurParComposante(38, 132, 0);
    ChoisirCouleurDessin(Background);
    RemplirRectangle(windowsMargin ,windowsMargin ,windowsL-2*windowsMargin ,windowsH - windowsMargin*3 -TailleSupPolice(2));

    ChoisirCouleurDessin(CouleurParComposante(255, 255, 255));
    int y = windowsMargin*2 +TailleSupPolice(2) - TailleSupPolice(2) + windowsH-windowsMargin*3 -TailleSupPolice(2);
    y = windowsH - windowsMargin;
    EcrireTexte(windowsMargin +10 ,y ,"01:27" ,2);
    char textes[8] = "0000190";
    int x = windowsL - windowsMargin - TailleChaineEcran(textes,2);
    EcrireTexte(x,y,textes,2);




    int posHeadX=20, posHeadY=25;
    int taileSnake = 10;
    int plateau[60][40] = {0};
    for (int i = posHeadY; i < taileSnake; i++){
        int empl = 1;
        if (i == posHeadY){
            plateau[posHeadX][i]=1;
        }else if(empl == taileSnake){
            plateau[posHeadX][i]=3;
        }else{
            plateau[posHeadX][i]=2;
        }
        empl++;
    }

    int snakehead, snaketail, numbody=0;
    int snakebody[25];
    snakehead = ChargerSprite("./snakeHead.png");
	AfficherSprite(snakehead,posHeadY*taillecase+windowsMargin,posHeadX*taillecase+windowsMargin);
    for (int i = posHeadY; i < taileSnake; i++){
        int empl = 1;
        if (i == posHeadY){
            snakehead = ChargerSprite("./snakeHead.png");
            AfficherSprite(snakehead,i*taillecase+windowsMargin,posHeadX*taillecase+windowsMargin);
        }else if(empl == taileSnake){
            snaketail = ChargerSprite("./snakeTail.png");
            AfficherSprite(snaketail,i*taillecase+windowsMargin,posHeadX*taillecase+windowsMargin);
        }else{
            snakebody[numbody]=ChargerSprite("./snakeBody.png");
            AfficherSprite(snakebody[numbody],i*taillecase+windowsMargin,posHeadX*taillecase+windowsMargin);
            numbody++;
        }
        empl++;
    }
    

    int touche;
    while(touche!=XK_Escape){
        

    	if (ToucheEnAttente()){
    		touche=Touche();
    	}
    }



    FermerGraphique();
    return EXIT_SUCCESS;
}