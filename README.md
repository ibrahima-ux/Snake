# Snake Game Project

## Introduction
Ce projet vise à développer un jeu Snake en utilisant le langage C et la bibliothèque graphique de l’université. L'objectif principal est de mettre en œuvre les fonctionnalités classiques du jeu Snake tout en ajoutant des éléments personnels à travers la programmation en C. L'objectif est d'explorer différentes approches de programmation pour atteindre un objectif.

## Fonctionnalités
Le jeu Snake met en œuvre les fonctionnalités suivantes :

### Initialisation
- **Initialiser()** : Initialise le jeu en définissant le nombre de lignes, de colonnes, la position du serpent et sa direction.
- **InitialiserSnake()** : Dessine l'affichage du jeu, le fond de la fenêtre, le terrain de jeu et le serpent initial de taille 10. Charge également l’image de la barre d’information.

### Fonctions de jeu
- **checkDeplacement()** : Vérifie si un déplacement provoquera la fin de la partie.
- **deplacerSnake()** : Gère le déplacement du serpent en fonction de la direction et sauvegarde l’emplacement de la queue pour effacement ultérieur.
- **majSnake(InfosJeux, Snake)** : Met à jour l’affichage du serpent en dessinant un carré sur l’ancienne queue et en dessinant la tête du serpent.
- **majText()** : Met à jour le texte dans la barre d’information, affichant le niveau, le score et le timer.
- **gameOver()** : Gère l’affichage de l’écran de fin de partie avec le score.
- **gameStart()** : Gère le fonctionnement du Snake en appelant les fonctions aux moments adéquats et en générant les différentes pommes.

## Découpages et Explication des fonctions
Le code est divisé en structures et énumérations pour faciliter l'accès et la modification des informations. Les principales structures incluent :
- **Jeux** : Contient toutes les données nécessaires au jeu.
- **Snake** : Tableau de positions avec x, y, sprites et types pour représenter le serpent.
- **InfosJeux** : Définit les attributs de la grille de jeu, le timer et le score.
- **Apple** : Stocke les positions des pommes.

## Conclusion personnelle
### Bourama-Mike Djoco
Ce projet m'a permis de revoir mes méthodes de travail, de réfléchir avant de coder, et de rectifier les erreurs. Travailler en C avec la bibliothèque graphique a été un défi intéressant.

### Ibrahima Bah
Ce projet a été enrichissant, notamment dans la gestion des entrées utilisateur, la manipulation des sprites et la gestion des collisions. J'ai également apprécié la collaboration avec mes coéquipiers pour résoudre les problèmes.

**Collaborateurs :**  
- Bourama Djoco  
- Ibrahima Bah