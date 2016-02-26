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
	if ((p=malloc(sizeof(nodeType))) == NULL)
	{
		printf("out of memory error\n");
		exit(1);
	}

	p->type=typeNumeric;
	p->t_numeric.valeur=v;

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
	/* allocate node */
    	if ((p = malloc(sizeof(nodeType))) == NULL)
	{
		printf("out of memory error\n");
		exit(1);
	}
    	if ((p->t_oper.op = malloc(nops * sizeof(nodeType))) == NULL)
	{
		printf("out of memory error\n");
		exit(1);
	}
	
	p->type = typeOperator;
	p->t_oper.oper = oper;
	p->t_oper.nOperands = nops;
	va_start(ap, nops);
    	for (i = 0; i < nops; i++)
        	p->t_oper.op[i] = va_arg(ap, nodeType*);
    	va_end(ap);

    	return p;
}

// Q3 : Ecrire la fonction, recursive, qui permet de generer
// le code assembleur EVM equivalent a un AST a partir
// d'un pointeur sur la racine de celui-ci
void generateAsmRec(nodeType *n, FILE *fout)
{
	if (n==NULL)
		return;

	switch (n->type)
	{
		case typeNumeric:
			fprintf(fout,"\tpush %f\n",n->t_numeric.valeur);
		case typeOperator:
			{
				switch (n->t_oper.oper)
				{
					case OPER_ADD:
                                                generateAsmRec(n->t_oper.op[0],fout);
                                                generateAsmRec(n->t_oper.op[1],fout);
						fprintf(fout,"\tadd\n");
                                                break;
					case OPER_SUB:
                                                generateAsmRec(n->t_oper.op[0],fout);
                                                generateAsmRec(n->t_oper.op[1],fout);
						fprintf(fout,"\tsub\n");
                                                break;
					case OPER_MULT:
                                                generateAsmRec(n->t_oper.op[0],fout);
                                                generateAsmRec(n->t_oper.op[1],fout);
						fprintf(fout,"\tmult\n");
                                                break;
					case OPER_DIV:
                                                generateAsmRec(n->t_oper.op[0],fout);
                                                generateAsmRec(n->t_oper.op[1],fout);
						fprintf(fout,"\tdiv\n");
                                                break;
					case OPER_OUTPUT:
						generateAsmRec(n->t_oper.op[0],fout);
                                                generateAsmRec(n->t_oper.op[1],fout);
						fprintf(fout,"\toutput\n");
						break;
					default:
						break;
				}
			}
			break;
	}
}

// Q4 ; Ecrire la fonction, non recursive, qui va permettre
// de generer un fichier assembleur correct a partir de l'AST.
// La fonction devra inserer a la fichier du fichier assembleur
// l'instruction halt, pour arreter l'execution de la machine virtuelle
// et la pseudo-instruction end qui arretera l'assemblage
void generateAsm(nodeType *n, char *filename)
{
	FILE *fout;
	fout=fopen(filename,"w");
	fprintf(fout,"Debut\n");
	generateAsmRec(n,fout);
	fprintf(fout,"\thalt\n");
	fprintf(fout,"\tend\n");
	fclose(fout);	
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
	if (n==NULL)
                return;

        switch (n->type)
        {
                case typeNumeric:
                        {
				n->digraphNode=countDigraph++;
                                fprintf(fout,"\tN%3.3d [label=\"%f\"]\n",n->digraphNode,n->t_numeric.valeur);
                        }
                        break;
                case typeOperator:
                        {
                                switch (n->t_oper.oper)
                                {
                                        case OPER_ADD:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tN%3.3d [label=\"+\"]\n",n->digraphNode);
                                                break;
                                        case OPER_SUB:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tN%3.3d [label=\"-\"]\n",n->digraphNode);
                                                break;
                                        case OPER_MULT:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tN%3.3d [label=\"*\"]\n",n->digraphNode);
                                                break;
                                        case OPER_DIV:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tN%3.3d [label=\"/\"]\n",n->digraphNode);
                                                break;
                                    	case OPER_OUTPUT:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tN%3.3d [label=\"output\"]\n",n->digraphNode);
                                                break;
                                        default:
                                                break;
                                }
                        }
                        break;
        }
}

// Q6 : Ecrire la fonction, recursive, qui permet de generer
// la partie "liste des arcs" d'un digraph dot a partir
// d'un pointeur sur la racine de l'AST. L'ecriture se
// fera dans le fichier pointe par fout. La fonction utilise la numerotation
// faite par la fonction recursive precedente 
void generateDigraphEdges(nodeType *n,FILE *fout)
{
	if (n==NULL)
                return;

        switch (n->type)
        {
                case typeNumeric:
                case typeOperator: {
                	switch (n->t_oper.oper)
		        {
				case OPER_ADD:
					fprintf(fout,"\tN%3.3d -> N%3.3d\n",
						n->digraphNode,n->t_oper.op[0]->digraphNode);
				        fprintf(fout,"\tN%3.3d -> N%3.3d\n",
						n->digraphNode,n->t_oper.op[1]->digraphNode);
				        generateDigraphEdges(n->t_oper.op[0],fout);
				        generateDigraphEdges(n->t_oper.op[1],fout);
					break;
				case OPER_SUB:
					fprintf(fout,"\tN%3.3d -> N%3.3d\n",
						n->digraphNode,n->t_oper.op[0]->digraphNode);
				        fprintf(fout,"\tN%3.3d -> N%3.3d\n",
						n->digraphNode,n->t_oper.op[1]->digraphNode);
				        generateDigraphEdges(n->t_oper.op[0],fout);
				        generateDigraphEdges(n->t_oper.op[1],fout);
					break;
				case OPER_MULT:
					fprintf(fout,"\tN%3.3d -> N%3.3d\n",
						n->digraphNode,n->t_oper.op[0]->digraphNode);
				        fprintf(fout,"\tN%3.3d -> N%3.3d\n",
						n->digraphNode,n->t_oper.op[1]->digraphNode);
				        generateDigraphEdges(n->t_oper.op[0],fout);
				        generateDigraphEdges(n->t_oper.op[1],fout);
					break;
				case OPER_DIV:
					fprintf(fout,"\tN%3.3d -> N%3.3d\n",
						n->digraphNode,n->t_oper.op[0]->digraphNode);
				        fprintf(fout,"\tN%3.3d -> N%3.3d\n",
						n->digraphNode,n->t_oper.op[1]->digraphNode);
				        generateDigraphEdges(n->t_oper.op[0],fout);
				        generateDigraphEdges(n->t_oper.op[1],fout);
					break;
				case OPER_OUTPUT:
					fprintf(fout,"\tN%3.3d -> N%3.3d\n",
						n->digraphNode,n->t_oper.op[0]->digraphNode);
					generateDigraphEdges(n->t_oper.op[0],fout);
					break;

		   		default:
			  		break;
			}
		break;
		}
		default:
			break;
        }

}

// Q7 : Ecrire la fonction, non recursive, permettant de
// generer un fichier res.dot contenant toutes les infos
// permettant un affichage graphique plaisant. On pourra
// utiliser l'appel syeme "system" pour lancer automatiquement
// la conversion res.dot en res.png
void generateDigraph(nodeType *n)
{
	FILE *fout;

	fout=fopen("res.dot","w");
	countDigraph=0;
	fprintf(fout,"digraph {\n");
	generateDigraphNameNode(n,fout);
	generateDigraphEdges(n,fout);
	fprintf(fout,"}\n");
	fclose(fout);
	system("dot -Tpng res.dot -o res.png");
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
