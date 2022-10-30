# Turtle
Le but de ce projet est de concevoir et d’implémenter un langage pour faire du dessin, un peu à la manière de la tortue LOGO.

## Pour commencer
Ce projet a été conçu pour un environnement Linux. Après une prise en main des outils d'analyse lexicale et sémantique, l'objectif est de constuire un arbre de syntaxe abstrait. 

### Pré-requis
- Flex : un analyseur lexical. Il permet de créer une suite de tokens qui seront analysés par l’analyseur syntaxique. 
Il prend en entrée une description des tokens via des expressions régulières et renvoie un fichier C contenant une fonction yylex() qui réalise l’analyse.
Une documentation est disponible à l'adresse : https://westes.github.io/flex/manual/
- Bison : un analyseur syntaxique. Plus précisément, c’est un générateur d’analyseur syntaxique, appelé aussi compilateur de compilateur. 
Il prend en entrées une suite de tokens fournis par Flex et réalise une analyse. Le développeur choisit le résultat de cette analyse.
Une documentation est disponible à l'adresse : https://www.gnu.org/software/bison/manual/html_node/

Ces deux outils peuvent être téléchargés avec la commande ``sudo apt-get install flex bison``

### Installation
Le fichier CMakeLists.txt permet de construire le programme, il faut au préalable créer un dossier ``build``. 

Construction du programme 
```
mkdir build
cd build
cmake ..
```
Compilation
```
make
```
## Utilisation
Pour une utilisation plus poussée du projet, des fichiers d'exemple se trouvent dans le dossier ``exemples``. Un viewer est également à disposition. Il est nécessaire d'avoir la librairie libsndio7.0 pour le lancer, récupérable avec la commande ``sudo apt install libsndio7.0``.

Exécution simple
```
./turtle
```
Exécution d'un fichier d'exemple
```
build/turtle < exemples/hello.turtle
```
Exécution d'un fichier d'exemple et visualisation dans le viewer
```
build/turtle < exemples/hello.turtle | ./turtle-viewer 
```
