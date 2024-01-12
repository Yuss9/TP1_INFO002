### TP1 INFO 002 CRYPTOLOGIE 

Sujet : https://pierre-hyvernat.apps.math.cnrs.fr/data/Enseignement/2324/info002/tp1.html#toc_1

### STATUS 

Equipe : YURTSEVEN Hüseyin, CHAVANCE Rémi, DURAND-NOËL Amaury
Etat : on est au debut de la question 7

## QUESTIONS

### QUESTIONS 5

La complexité de la recherche dans la table dépend du nombre de colonnes que vous choisissez de stocker (représenté par le paramètre k). Supposons que la table initiale contienne hauteur lignes et largeur colonnes.

### Recherche dans la table avec k colonnes (compromis temps-mémoire)

#### Complexité en temps:
- Recherche dichotomique dans la dernière colonne: O(log(hauteur))
- Pour chaque valeur trouvée dans la dernière colonne, test de candidat potentiel: O(k)

La complexité totale serait alors O(k * log(hauteur))

#### Complexité en espace:
- Stockage des premières et dernières colonnes pour chaque entrée: O(k * hauteur)

### Comparaison avec la recherche exhaustive

#### Complexité en temps:
- Recherche exhaustive: O(hauteur)

#### Complexité en espace:
- Aucun espace supplémentaire requis, car la recherche est effectuée directement sur la fonction de hachage.

### Comparaison avec le précalcul complet

#### Complexité en temps:
- Précalcul complet: O(hauteur) pour générer toutes les empreintes.
- Recherche directe dans la table: O(log(hauteur)) pour trouver l'entrée correspondante.

#### Complexité en espace:
- Stockage complet de la table: O(hauteur * largeur)

La méthode avec un compromis temps-mémoire offre une complexité en temps généralement meilleure que la recherche exhaustive mais peut être plus lente que le précalcul complet, lorsque k est proche de largeur. En termes d'espace, elle utilise moins de mémoire que le précalcul complet mais plus que la recherche exhaustive.

### QUESTIONS 8

L'ajout du paramètre `t` dans la fonction `h2i` permet d'introduire un décalage supplémentaire dans le calcul de la fonction de hachage. Ce décalage permet de générer des indices différents pour des empreintes identiques, augmentant ainsi la couverture de la table. En d'autres termes, des textes clairs qui produiraient normalement la même empreinte pourraient être différenciés en ajoutant une valeur de décalage `t`.

Cela est particulièrement utile pour éviter des collisions dans la table arc-en-ciel. Dans le contexte des tables arc-en-ciel, on a une collision quand lorsqu'une même valeur d'indice est obtenue pour des empreintes différentes. En ajoutant le paramètre `t`. On permet la diversification des indices générés pour des empreintes similaires.