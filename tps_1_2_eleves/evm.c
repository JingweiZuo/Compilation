#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "vm_codops.h"

#define MAX_CODESEGMENT_SIZE 1000
#define MAX_STACK_SIZE 100

// Q1 : Les registres de la machine virtuelle
int pc =0;
int sp= -1;
int bp= -1;

// Q2 : Declaration du segment de code
int codeSegment[MAX_CODESEGMENT_SIZE];

float pile[MAX_STACK_SIZE];

// Q4 : Fonction de lecture d'un fichier langage machine
//      ouvert et dont le pointeur de fichier est fin

void readAssembly(FILE *fin)
{
	int i;
	int taille;
	rewind(fin);
	fscanf(fin, "%d", &taille);
	int num[MAX_CODESEGMENT_SIZE];
	for(i = 0; i < taille; i++){
		while (fgetc(fin)!=':'){}
		fscanf(fin, "%d",&codeSegment[i]);
		printf("%d\n", codeSegment[i]);
		
	}
}

// Q5 : Fonction de debug qui affiche la pile jusqu'a son sommet 

void printPile()
{
	int i = sp;
	while(i > 0){
		printf(" %f\n", pile[i]);
		i--;
	}
	printf("\n");
}

// Q6 : Boucle principale d'exécution de la machine virtuelle 
//      On sort de cette fonction si l'instruction pointee
//      par pc est OP_HALT. On traitera les erreurs et on
//	pensera a ajouter des traces et des moyens de mise
//	au point

void run()
{
	float fv;
	int vm1,v;
    	int i,depile,n,orig,dest;
	char strReal[256];
	int strRealLength,pos;

	//printExecStack();
	while (codeSegment[pc]!=OP_HALT)
	{
		//printf("%d: ",pc);
		//printf("%d ",codeSegment[pc]);
		switch (codeSegment[pc])
		{	
		//code instruction assembleur
			case OP_ADD:
				pile[sp-1]=pile[sp-1]+pile[sp]; 
				sp-- ; pc++ ; break;
			case OP_SUB:
				pile[sp-1]=pile[sp-1]-pile[sp]; 
				sp-- ; pc++ ; break;
			case OP_MULT:
			pile[sp-1]=pile[sp-1]*pile[sp]; 
				sp-- ; pc++ ; break;
			case OP_DIV:
			pile[sp-1]=pile[sp-1]/pile[sp]; 
				sp-- ; pc++ ; break;
			case OP_DIVI:
			pile[sp-1]=(int)(pile[sp-1]/pile[sp]); 
				sp-- ; pc++ ; break;
		//case logique
			case OP_NEG:
			pile[sp-1]= - pile[sp-1]; 
				pc++ ; break;

			case OP_AND:
			pile[sp-1]=pile[sp-1] && pile[sp]; 
				sp-- ; pc++ ; break;

			case OP_OR:
			pile[sp-1]=pile[sp-1] || pile[sp];
				sp-- ; pc++ ; break;

			case OP_NOT:
			pile[sp-1]= !pile[sp-1]; 
				pc++ ; break;

			case OP_EQ:
			if(pile[sp-1] == pile[sp]){
				pile[sp-1]=1;
			}
			else{
				pile[sp-1]=0;
			}
				sp-- ; pc++ ; break;

			case OP_LS:
			if(pile[sp-1] < pile[sp]){
				pile[sp-1]=1; 
			}
			else{
				pile[sp-1]=0;
			}
				sp-- ; pc++ ; break;

			case OP_GT:
			if(pile[sp-1] > pile[sp]){
				pile[sp-1]=1;
			}
			else{
				pile[sp-1]=0;
			}
				sp-- ; pc++ ; break;

			case OP_INC:
			sp = sp + codeSegment[pc+1];
				pc += 2 ; break;

			case OP_DEC:
			sp = sp - codeSegment[pc+1]; 
				pc += 2 ; break;

		//case d'opération
			case OP_PUSH:
			pile[++sp]=(float)codeSegment[pc+1]; 
				 pc +=2 ; break;	

			case OP_DUPL:
			pile[++sp]=pile[sp]; 
				pc++ ; break;

			case OP_CONT:
			pile[sp] = pile[(int)pile[sp]];
				sp-- ; pc++ ; break;

			case OP_JP:
				pc = codeSegment[pc+1];
				break;

			case OP_JF:
				if(pile[sp]==0)
					pc = codeSegment[pc+1];
				else
					sp-- ; pc+=2 ; break;
				
			case OP_JL:
				if(pile[sp-1] <= pile[sp])
					pc = codeSegment[pc+1];
				else
					sp-=2 ; pc++ ; break;

			case OP_JG:
				if(pile[sp-1] >= pile[sp])
					pc = codeSegment[pc+1];
				else
					sp-=2 ; pc++ ; break;
	
		//case affichage
			case OP_INPUT:
				scanf("%f",&fv);
				pile[(int)pile[++sp]] = fv;
				pc++; break;

			case OP_OUTPUT:
	
			//printf("pile: %f\n",pile[sp]);
			printPile();
				sp-- ; pc++ ; break;

			case OP_OUTCHAR:	
				while(codeSegment[pc+1]!=0){
					printf("%c",(char)codeSegment[pc+1]);
					pc++ ;
				}
				pc+=2;
				break;

			case OP_CALLS:
				pile[sp] = pc + 2;
				sp++ ; pc = codeSegment[pc+1]; break;

			case OP_HALT:
				printf("Arrêt de la machine virtuelle\n");
				exit(1);
			default:
				printf("Instruction non reconnue: %i\n",codeSegment[pc]);
				exit(1);
		}
		//printExecStack();
	}
}

// Q7 : Programme principal. Apres les tests de nombre et de qualite
//	des arguments, ouvrir le fichier langage machine, appeler
//	la fonction readAssembly, et fermer le fichier ouvert. Ensuite
//	initialiser pc a 0, sp et bp a -1. Enfin, lancer la machine
//	virtuelle avec la fonction run().

int main(int argc, char **argv)
{
	if (argc!=2)
	{
		printf("Usage : vm infile.bin\n");
	}
	FILE *fin=fopen(argv[1],"r");
	if (fin==NULL)
	{
		printf("Error opening read file %s\n",argv[1]);
		exit(1);
	}
	// add code here
	readAssembly(fin);
	
	run();
	//printPile();
	fclose(fin);
	return 0;
}
