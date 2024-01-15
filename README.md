### TP1 INFO 002 CRYPTOLOGIE 

Sujet : https://pierre-hyvernat.apps.math.cnrs.fr/data/Enseignement/2324/info002/tp1.html#toc_1

### STATUS 

Equipe : YURTSEVEN Hüseyin, CHAVANCE Rémi, DURAND-NOËL Amaury
Etat : on a fait toutes les questions, sauf la partie bonus. 

### COMMANDES : 

```bash
make
```



## QUESTIONS

### QUESTIONS 1

```bash
./main test hash Salut Bob
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

**En mode random :**

```bash
./main --alphabet=abcdefghijklmnopqrstuvwxyz --randTable --size=5 --height=100 --width=200 test create_table
```


**En mode test prof :**

```bash
./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 --height=100 --width=200 test create_table
```

### QUESTIONS 10

**En mode random :**
```bash
./main --alphabet=abcdefghijklmnopqrstuvwxyz --randTable --size=5 --height=100 --width=200 test save_table
```

**En mode test prof :**

```bash
./main --alphabet=abcdefghijklmnopqrstuvwxyz --size=5 --height=100 --width=200 test save_table
```

### QUESTIONS 11

**On ajoute dans un premier temps le fichier table.txt avec le tableau a l'intérieur**

```bash
 ./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --size=4 --height=1000 --width=3000 test save_table
```


```bash
./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --hash=16de25af888480da1af57a71855f3e8c515dcb61 --size=4 --height=1000 --width=3000 test crack
```


### QUESTIONS 12

Dans le contexte d'une table arc-en-ciel, la complexité pourrait être évaluée à O(log(hauteur) * largeur * largeur).

-La recherche dichotomique présente une complexité de log(hauteur).
-La dimension largeur doit également être prise en compte, car en moyenne, la découverte du hash se produit à la moitié du tableau, sous réserve de sa validité et de sa correspondance avec un mot de passe répertorié dans la table. La largeur (2) intervient car à chaque itération, le recalcul du nouveau candidat à rechercher nécessite (largeur - t) itérations, soit en moyenne largeur/2 itérations.
-La complexité totale de cette recherche est exprimée comme O(hauteur) en raison du chargement de la table en mémoire.
-Les autres calculs associés sont en temps constant.


### Question 13

```bash
./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --size=4 --height=1000 --width=1000 test stats
```


### Question 14

#### 1° hash

Pour **16de25af888480da1af57a71855f3e8c515dcb61** avec une taille de 4 et l'alphabet suivant : **ABCDEFGHIJKLMNOPQRSTUVWXYZ**

**On ajoute dans un premier temps le fichier table.txt avec le tableau a l'intérieur**

```bash
 ./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --size=4 --height=1000 --width=3000 test save_table
```


```bash
./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --hash=16de25af888480da1af57a71855f3e8c515dcb61 --size=4 --height=1000 --width=3000 test crack
```

On obtient ceci  : 

>temps de génération de la table dans le fichier table.txt : 3.268s
>
>taille de la table : 10Ko
>
>temps de calcul de l'inverse (crackage) : 0.33s  

#### 2° hash

Pour `dafaa5e15a30ecd52c2d1dc6d1a3d8a0633e67e2` de taille `5` et l'alphabet suivant : `abcdefghijklmnopqrstuvwxyz0123456789,;:$.` 

Nous recherchons une bonne couverture : 

```bash
 ./main --alphabet='abcdefghijklmnopqrstuvwxyz0123456789,;:$.' --size=5 --height=20000 --width=10000 test stats
```
ce qui donne une couverture de 71.1955 % 

on génère une table adaptée.

```bash
 ./main --alphabet='abcdefghijklmnopqrstuvwxyz0123456789,;:$.' --size=5 --height=20000 --width=10000 test save_table
```

```bash
./main --alphabet='abcdefghijklmnopqrstuvwxyz0123456789,;:$.' --hash=dafaa5e15a30ecd52c2d1dc6d1a3d8a0633e67e2 --size=5 --height=20000 --width=10000 test crack
```

le resultat est **n00b.**

On obtient ceci  : 

>temps de génération de la table dans le fichier table.txt : 3m 42s
>
>taille de la table : 283Ko
>
>temps de calcul de l'inverse (crackage) : 0.76s


### Question 15

Pour garantir la couverture de l'ensemble des mots de passe potentiels, la taille totale de la table arc-en-ciel est donnée par le produit de la taille de l'alphabet élevée à la puissance de la taille minimale du mot de passe, soit $`\text{len(alphabet)}^{(\text{taille\_password})}`$, équivalent à $36^8$ dans ce cas particulier.

Le temps nécessaire pour générer cette table serait approximativement $`\text{{len(alphabet)}}^{(\text{taille\_password})} \times t`$, où $t$ représente le temps nécessaire pour calculer un hash et écrire les informations correspondantes dans un fichier, en considérant les deux colonnes (password et H8).

### Question 16

#### PARTIE 1

Pour le mot **CODE** : 

```bash
 ./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --size=4 --height=1000 --width=3000 test save_table
```


```bash
./main --alphabet=ABCDEFGHIJKLMNOPQRSTUVWXYZ --hash=16de25af888480da1af57a71855f3e8c515dcb61 --exhaustif --size=4 --height=1000 --width=3000 test crack
```


On obtient ceci  : 

>temps de génération de la table dans le fichier table.txt : 3s
>
>taille de la table : 10K
>
>temps de calcul de l'inverse (crackage) : 0.076s

#### PARTIE 2 

Pour le mot **n00b.** : 

```bash
 ./main --alphabet='abcdefghijklmnopqrstuvwxyz0123456789,;:$.' --size=5 --height=20000 --width=10000 test save_table
```


```bash
./main --alphabet='abcdefghijklmnopqrstuvwxyz0123456789,;:$.' --hash=dafaa5e15a30ecd52c2d1dc6d1a3d8a0633e67e2 --exhaustif --size=5 --height=20000 --width=10000 test crack
```

On obtient ceci  : 

>temps de génération de la table dans le fichier table.txt : 3m 42s
>
>taille de la table : 283K
>
>temps de calcul de l'inverse (crackage) : 34s


#### CONCLUSION QUESTION 16 

Avec une recherche exaustive, en moyenne, le temps pour trouver le mot de passe est de
$len(alphabet)^{taille password}/2 = (36^8)/2$ 


### Question 17

L'utilisation du sel dans le contexte des mots de passe vise à accroître la complexité du processus de hachage, rendant plus complexe la tâche des attaquants cherchant à utiliser des tables arc-en-ciel pour casser les mots de passe. Le sel consiste en l'ajout de caractères aléatoires au mot de passe avant le hachage. En conséquence, même si deux utilisateurs ont le même mot de passe, le hash résultant sera différent en raison de l'incorporation du sel unique.

Cette différenciation des hashs rend inefficace l'utilisation de tables arc-en-ciel, car ces dernières reposent sur la précomputation de couples de mots de passe et de hashs correspondants. Avec l'ajout de sel, la relation entre un mot de passe et son hash devient spécifique à chaque utilisateur, compromettant ainsi la validité des tables arc-en-ciel précalculées. En conclusion, l'utilisation du sel renforce la sécurité en introduisant une variabilité individuelle dans le processus de hachage, décourageant les attaquants de s'appuyer sur des méthodes précalculées pour casser les mots de passe.
