### TP1 INFO 002 CRYPTOLOGIE 

Sujet : https://pierre-hyvernat.apps.math.cnrs.fr/data/Enseignement/2324/info002/tp1.html#toc_1

### STATUS 

Equipe : YURTSEVEN Hüseyin, CHAVANCE Rémi, DURAND-NOËL Amaury
Etat : on est au debut de la question 11 la fonction recherche fonctionne


### COMMANDES : 

```bash
make
```



## QUESTIONS

### QUESTIONS 1

```bash
./main hash Salut Bob
```

### QUESTIONS 2

```bash
./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=4 test calculateN
```

### QUESTIONS 3

Voici la commande pour voir toutes les commandes : 

```bash
./main --help
```

### QUESTIONS 4

```bash
./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=4 test i2c
```

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

### QUESTIONS 6

```bash
./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 test h2i
```

### QUESTIONS 7

```bash
./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 test nouvelle_chaine
```

### QUESTIONS 8

L'ajout du paramètre `t` dans la fonction `h2i` permet d'introduire un décalage supplémentaire dans le calcul de la fonction de hachage. Ce décalage permet de générer des indices différents pour des empreintes identiques, augmentant ainsi la couverture de la table. En d'autres termes, des textes clairs qui produiraient normalement la même empreinte pourraient être différenciés en ajoutant une valeur de décalage `t`.

Cela est particulièrement utile pour éviter des collisions dans la table arc-en-ciel. Dans le contexte des tables arc-en-ciel, on a une collision quand lorsqu'une même valeur d'indice est obtenue pour des empreintes différentes. En ajoutant le paramètre `t`. On permet la diversification des indices générés pour des empreintes similaires.


### QUESTIONS 9

```bash
./main --alphabet=abcdefghijklmnopqrstuvwxyz --alphabet_length=26 --size=5 --height=100 --width=200 test create_table
```

### QUESTIONS 10

```bash
./main --alphabet=abcdefghijklmnopqrstuvwxyz --alphabet_length=26 --size=5 --height=100 --width=200 test save_table
```

### QUESTIONS 11

**On ajoute dans un premier temps le fichier table.txt avec le tableau a l'intérieur**

```bash
 ./main --alphabet=abcdefghijklmnopqrstuvwxyz --alphabet_length=26 --size=4 --height=1000 --width=3000 test save_table
```


```bash
 ./main --alphabet=abcdefghijklmnopqrstuvwxyz --alphabet_length=26 --size=4 --height=1000 --width=3000 test inverse
```


### QUESTIONS 12

Dans le contexte d'une table arc-en-ciel, la complexité pourrait être évaluée à O(log(hauteur) * largeur * largeur).

-La recherche dichotomique présente une complexité de log(hauteur).
-La dimension largeur doit également être prise en compte, car en moyenne, la découverte du hash se produit à la moitié du tableau, sous réserve de sa validité et de sa correspondance avec un mot de passe répertorié dans la table. La largeur (2) intervient car à chaque itération, le recalcul du nouveau candidat à rechercher nécessite (largeur - t) itérations, soit en moyenne largeur/2 itérations.
-La complexité totale de cette recherche est exprimée comme O(hauteur) en raison du chargement de la table en mémoire.
-Les autres calculs associés sont en temps constant.


### Question 13

```bash
./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --alphabet_length=26 --size=4 --height=1000 --width=1000 test stats
```
