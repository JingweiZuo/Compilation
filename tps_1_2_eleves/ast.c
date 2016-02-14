#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "ast.h"

// Cette variable globale vaut au depart 0, et est incrementee a chaque fois
int countDigraph;

// Q1 : Ecrire la fonction qui permet d'allouer et d'initialiser un noeud
// de type numeric avec la bonne valeur reelle
nodeType *createNumericNode(float v)
{
	nodeType *p;

	// add code here

	return p;
}

// Q2 : Ecrire la fonction qui permet d'allouer et d'initialiser un
// noeud de type operator. L'argument oper definit l'operation avec
// des valeurs extraites de l'enum, nops definit le nombre d'operandes
// et ... represente la liste des noeuds fils, fils0 jusqu'a fils_nops-1
nodeType *createOperatorNode(int oper, int nops, ...) 
{
    	va_list ap;
    	nodeType *p;
    	int i;

	// add core here

    	return p;
}

// Q3 : Ecrire la fonction, recursive, qui permet de generer
// le code assembleur EVM equivalent a un AST a partir
// d'un pointeur sur la racine de celui-ci
void generateAsmRec(nodeType *n, FILE *fout)
{
}

// Q4 ; Ecrire la fonction, non recursive, qui va permettre
// de generer un fichier assembleur correct a partir de l'AST.
// La fonction devra inserer a la fichier du fichier assembleur
// l'instruction halt, pour arreter l'execution de la machine virtuelle
// et la pseudo-instruction end qui arretera l'assemblage
void generateAsm(nodeType *n, char *filename)
{
}

// Q5 : Ecrire la fonction, recursive, qui permet de generer
// la partie "liste des noeuds" d'un digraph dot a partir
// d'un pointeur sur la racine de l'AST. L'ecriture se
// fera dans le fichier pointe par fout. Cette fonction
// doit parcourir l'AST et affecter le champs digraphNode 
// avec un entier definissant le nom du noeud. Ce champs
// sera utilise par la fonction recursive suivante permettant
// de generer les arcs du graphe.
void generateDigraphNameNode(nodeType *n,FILE *fout)
{
}

// Q6 : Ecrire la fonction, recursive, qui permet de generer
// la partie "liste des arcs" d'un digraph dot a partir
// d'un pointeur sur la racine de l'AST. L'ecriture se
// fera dans le fichier pointe par fout. La fonction utilise la numerotation
// faite par la fonction recursive precedente 
void generateDigraphEdges(nodeType *n,FILE *fout)
{
}

// Q7 : Ecrire la fonction, non recursive, permettant de
// generer un fichier res.dot contenant toutes les infos
// permettant un affichage graphique plaisant. On pourra
// utiliser l'appel syeme "system" pour lancer automatiquement
// la conversion res.dot en res.png
void generateDigraph(nodeType *n)
{
}

// La encore cadeau...
int main(int argc, char **argv)
{
	nodeType *n0=createNumericNode(1.23);
	nodeType *n1=createNumericNode(4.56);
	nodeType *n2=createNumericNode(7.89);
	nodeType *n3=createOperatorNode(OPER_ADD,2,n0,n1);
	nodeType *n4=createOperatorNode(OPER_ADD,2,n3,n2);
	nodeType *n5=createOperatorNode(OPER_OUTPUT,1,n4);
	generateAsm(n5,"res.asm");
	generateDigraph(n5);

	return 0;
}
