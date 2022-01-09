# ParallelComputing

Projet de programmation parallèle et distribuée (IATIC4-ISTY) avec la méthodes des puissances

### Exemple de complilation



- Afin de calculer la valeur propre d'une matrice, on utilise le MakeFile afin de compiler puis d'executer de la manière suivante :
```bash
$ make
```

- Ensuite donner la taille de la matrice carré souhaitée
```bash
Tapez la taille de la matrice carré souhaitez
$
```

- Vous avez le choix entre saisir les valeurs de votre matrice ou avoir une matrice du type i + j  :
```textarea
[ 0  1  2  3  4 ]
[ 1  2  3  4  5 ]
[ 2  3  4  5  6 ]
[ 3  4  5  6  7 ]
[ 4  5  6  7  8 ]
```

Ainsi saisir 0 pour saisir les valeurs à la main 1 sinon :
```bash
Voulez vous tapez les valeurs ? (0 : oui, 1 : non)
$
```

- Le taux de convergence vous ai demandé (si l'on saisit 0.001 cela correspond à un taux d'erreur de 0.1%) :

```bash
Taux de convergence souhaiter
$
```

- Enfin, vous pouvez choisri le type d'éxecution, soit une execution en séquentiel soit en parallèle.
Ainsi saisir 0 pour l'éxecution en séquentiel ou 1 pour l'éxecution en parallèle :
```bash
Execution souhaiter (0 : seq, 1 : para)
$
```

- Si vous choisissez l'éxecution en parallèle, veuilliez siasir le nombre de threads pour l'éxecution :
```bash
Nombre de Thread
$
```

- Une fois l'éxecution et les résultats affichés, vous pouvez de nouveau saisir une nouvelle matrice en commencant par sa taille : 
```bash
Tapez la taille de la matrice carré souhaitez (-1 si vous voulez arreter)
$
```