#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "vm_codops.h"

#define MAX_CODESEGMENT_SIZE 1000
#define MAX_LABELS_SIZE 100
#define MAX_IDENTS_SIZE 100

// Structure tres simple qui va contenir le code
// genere. La seule fonction d'acces a ce tableau est
// la fonction
/*
	void addCode(int v), qui ajoute l'instruction v
	a la position courante dans codeSegment. La position
	courante est contenue dans la variable globale currentInst,
	qui est incrementee apres ajout d'une instruction
*/

unsigned int codeSegment[MAX_CODESEGMENT_SIZE];
int currentInst;

// Q1 : Ecrire le code
void addCode(int v)
{
}

// Structure permettant de definir les instructions de l'assembleur
// une instruction est definie par son nom, son codop, son type, son format
// et son nombre d'arguments
// Les instructions suivantes sont de type 0 car elles ne demandent pas
// de décodage d'operandes supplementaires. Leur chaine de format est ""
// et leur nombre d'argument est 0
/*
        addInstructionName("add", OP_ADD, 0, "", 0);
        addInstructionName("sub", OP_SUB, 0, "", 0);
        addInstructionName("mult", OP_MULT, 0, "", 0);
        addInstructionName("div", OP_DIV, 0, "", 0);
        addInstructionName("neg", OP_NEG, 0, "", 0);
        addInstructionName("and", OP_AND, 0, "", 0);
        addInstructionName("or", OP_OR, 0, "", 0);
        addInstructionName("not", OP_NOT, 0, "", 0);
        addInstructionName("eq", OP_EQ, 0, "", 0);
        addInstructionName("ls", OP_LS, 0, "", 0);
        addInstructionName("gt", OP_GT, 0, "", 0);
        addInstructionName("dupl", OP_DUPL, 0, "", 0);
        addInstructionName("cont", OP_CONT, 0, "", 0);
        addInstructionName("ret", OP_RET, 0, "", 0);
        addInstructionName("input", OP_INPUT, 0, "", 0);
        addInstructionName("output", OP_OUTPUT, 0, "", 0);
        addInstructionName("savebp", OP_SAVEBP, 0, "", 0);
        addInstructionName("rstrbp", OP_RSTRBP, 0, "", 0);
        addInstructionName("halt", OP_HALT, 0, "", 0);
*/
// Les instructions suivantes sont de type 1, ce qui signifie
// que le decodage d'un entier est necessaire. La chaine
// de format est donc "%s %d". Le %s represente l'instruction et le %d
// l'operande. Il y a un operande pour ce genre d'instruction
/*
        addInstructionName("inc", OP_INC, 1, "%s %d", 1);
        addInstructionName("dec", OP_DEC, 1, "%s %d", 1);
        addInstructionName("push", OP_PUSH, 1, "%s %d", 1);
        addInstructionName("libp", OP_LIBP, 1, "%s %d", 1);
        addInstructionName("move", OP_MOVE, 1, "%s %d", 1);
        addInstructionName("copy", OP_COPY, 1, "%s %d", 1);
*/
// L'instruction suivante est de type 2, ce qui signifie que
// le decodage d'une chaine de caracteres representant un nombre
// reel est necessaire. La chaine de format est donc "%s %s"
// et le deuxieme %s represente la chaine du nombre reel. Il y a
// un operande pour ce genre d'instruction
/*
        addInstructionName("pushr", OP_PUSHR, 2, "%s %s", 1);
*/
// Les instructions suivantes sont de type 3, ce qui signifie que
// le decodage d'une chaine de caracteres representant une etiquette
// est necessaire. La chaine de format est donc "%s %s" et
// le deuxieme %s represente l'etiquette. Il y a un
// operande pour ce genre d'instructions
/*
        addInstructionName("jf", OP_JF, 3, "%s %s", 1);
        addInstructionName("jl", OP_JL, 3, "%s %s", 1);
        addInstructionName("jg", OP_JG, 3, "%s %s", 1);
        addInstructionName("call", OP_CALL, 3, "%s %s", 1);
*/
// L'instruction suivante est de type 4, ce qui signifie que
// le decodage d'une chaine de caracteres est necessaire. 
// La chaine de format est donc "%s %s"
// et le deuxieme %s represente la chaine. Il y a
// un operande pour ce genre d'instruction
/*
        addInstructionName("outchar", OP_OUTCHAR, 4, "%s %s", 1);
*/

struct instructionName {
	char *name;			// Le nom de l'instruction
	int opcod;			// son codop, extrait de vm_codops.h
	int type;			// son type
	char *format;			// son format
	int nbops;			// le nombre d'operandes de l'inst
} tabInstructionNames[MAX_IDENTS_SIZE]; 
int currentInstructionName;

// Q2 : Ecrire le code 
void addInstructionName(char *instname, int opcod, int type, char *format, int nbops)
{
}

// La structure de donnees suivante permet de manipuler les etiquettes
// (labels en anglais). Chaque entree de ce tableau contient le nom d'une
// etiquette (label) et son adresse correspondante dans codeSegment
// Les fonctions d'acces a ce tableau sont
/*
	int findLabel(char *labelname), qui permet de savoir
		si un label existe dans la table. La fonction rend
		l'indice dans la table si le label existe, -1 sinon
	void addLabel(char *labelname,int addr), qui permet d'ajouter
		un label et son adresse dans la table
	la variable globale entiere currentLabel compte le nombre
		de labels et est incremente pour chaque ajout dans
		dans la table
*/

struct label {
	char *label;
	int addr;
} tabLabels[MAX_LABELS_SIZE]; 
int currentLabel;

// Q3 : Ecrire le code
int findLabel(char *labelname)
{
        return -1;
}

// Q4 : Ecrire le code
void addLabel(char *labelname,int addr)
{
}

// Structure permettant de manipuler les references dans le code, resolues
// ou non. Chaque entree de la table contient un label et une adresse precise
// dans le code representant une case ou on a mis temporairement un -1 et
// qu'il faut remplacer dans la deuxieme passe d'assemblage par la vraie
// reference, que l'on connaitra car tous les labels seront eux-meme connus.
// Les fonctions d'acces a ce tableau sont
/*
        void addReference(char *labelname,int addrInCode), qui permet d'ajouter
                une reference et son adresse dans le code dans la table
	void resolveReferences(), qui permet de resoudre les references
        la variable globale entiere currentRef compte le nombre
                de references et est incremente pour chaque ajout dans
                dans la table
*/

struct ref {
	char *label;
	int addrInCode;
} tabReferences[MAX_LABELS_SIZE]; 
int currentRef;

// Q5 : Ecrire le code
void addReference(char *labelname,int addrInCode)
{
}

// Q6 : Ecrire le code
void resolveReferences()
{
}

// La fonction decodeInstruction(char *line) est appelee par la boucle
// principale d'analyse lorsque la ligne d'assembleur lue n'est pas une
// (pas de : dans la ligne). Cette fonction fait le gros du travail
// de la passe 1, en identifiant le type de l'instruction, en faisant
// le decodage supplementaire, en appelant addCode() pour remplir codeSegment
// et en ajoutant des references si l'instruction decodee fait reference
// a une etiquette encore inconnue
 
// Q7 : Completer la fonction pour decoder les 4 types d'instructions
void decodeInstruction(char *line)
{
	int i,j,l,k,pos,comp;
	char *p;
	int int_operand;
	int found=0;
	char dummy[25];
	char string_operand[256];
	char string_label[25];
	char instname[25];

	// This stuff just to get the instruction name in the instname string
	pos=0;
	l=0;
	while (!isalpha(line[pos])) 
		pos++;
	while (isalpha(line[pos]))
		instname[l++]=line[pos++];
	instname[l++]=0;
	//printf("instname=|%s|\n",instname);

	for (i=0;i<currentInstructionName;i++)
	{
		comp=strcmp(instname,tabInstructionNames[i].name);
		if (comp==0)
		{
			switch(tabInstructionNames[i].type)
			{
				// no operands, just add the codop to the code
				// nothing to resolve
				case 0:
					found=1;
					addCode(tabInstructionNames[i].opcod);
					break;
				// one operand, of type integer
				// nothing to resolve
				case 1:
					found=1;
					sscanf(line,tabInstructionNames[i].format,dummy,&int_operand);
					addCode(tabInstructionNames[i].opcod);
					addCode(int_operand);
					break;
				// one operand, of type string for rpush
				// nothing to resolve
				case 2:
					// Add code here...
					break;
				// one operand, and it's a label
				// check if there is something to resolve later
				case 3:
					// Add code here...
					break;
                                // one operand, of type string with " for outchar
                                // nothing to resolve
                                case 4:
					// Add code here...
                                        break;
			}
		}
	}
	if ((i==currentInstructionName) && (found==0))
	{
		printf("Syntax error with line %s",line);
		exit(1);
	}
}

// Cette fonction parseAsm(FILE *fin) parcourt les lignes du fichier
// source assembleur tant qu'elle n'a pas rencontre de ligne avec
// "end" a l'interieur. Pour chaque ligne il y a deux cas de figure:
// - si la ligne de texte contient un :, il s'agit d'une etiquette et
//   on la declare
// - sinon, il s'agit d'une instruction et on appelle decodeInstruction()

// Q8 : Completer la fonction
void parseAsm(FILE *fin)
{
	char line[100];

	fgets(line,100,fin);
	while (strstr(line,"end")==NULL)
	{
		//printf("%s",line);

		/* if line contains ':', it's a label, and declare it as such*/
		char *p=strstr(line,":");

		// add code here

		fgets(line,100,fin);
	}
}

// Q9 : Ecrire des fonctions de mise au point permettant d'afficher
// les etiquettes et les references
void printLabels()
{
}

// Q10 : Completer la fonction suivante, qui permet de desassembler
// le code genere.
void dumpBinaryCode()
{
	int pc=0;
	int pos;

	while (pc!=currentInst)
	{
		printf("%5.5d: ",pc);
		switch (codeSegment[pc])
		{
                        case OP_ADD:
				printf("add\n");
                                pc++ ; break;
                        case OP_SUB:
				printf("sub\n");
                                pc++ ; break;

			// add lots of code here

                        case OP_HALT:
				printf("halt\n");
                                pc++; break;
			default:
				printf("Instruction inconnue :(\n");
				exit(1);
				break;
		}
	}
}

// Q11 : Ecrire la fonction permettant de genere le fichier langage
// machine a partir du tableau codeSegment, complet apres les
// deux passes d'assemblage
void generateBinary(FILE *fout)
{
}

// Cadeau : On vous donne le programme principale. Je sais, je sais,
// ma bonte me perdra.
int main(int argc, char **argv)
{
	if (argc!=3)
	{
		printf("Usage : asm infile.asm outfile.bin\n");
	}
	FILE *fin=fopen(argv[1],"r");
	if (fin==NULL)
		printf("Error opening read file %s\n",argv[1]);

	currentInstructionName=0;
	addInstructionName("add", OP_ADD, 0, "", 0);
	addInstructionName("sub", OP_SUB, 0, "", 0);
	addInstructionName("mult", OP_MULT, 0, "", 0);
	addInstructionName("div", OP_DIV, 0, "", 0);
	addInstructionName("neg", OP_NEG, 0, "", 0);
	addInstructionName("and", OP_AND, 0, "", 0);
	addInstructionName("or", OP_OR, 0, "", 0);
	addInstructionName("not", OP_NOT, 0, "", 0);
	addInstructionName("eq", OP_EQ, 0, "", 0);
	addInstructionName("ls", OP_LS, 0, "", 0);
	addInstructionName("gt", OP_GT, 0, "", 0);
	addInstructionName("inc", OP_INC, 1, "%s %d", 1);
	addInstructionName("dec", OP_DEC, 1, "%s %d", 1);
	addInstructionName("push", OP_PUSH, 1, "%s %d", 1);
	addInstructionName("pushr", OP_PUSHR, 2, "%s %s", 1);
	addInstructionName("libp", OP_LIBP, 1, "%s %d", 1);
	addInstructionName("dupl", OP_DUPL, 0, "", 0);
	addInstructionName("cont", OP_CONT, 0, "", 0);
	addInstructionName("move", OP_MOVE, 1, "%s %d", 1);
	addInstructionName("copy", OP_COPY, 1, "%s %d", 1);
	addInstructionName("jf", OP_JF, 3, "%s %s", 1);
	addInstructionName("jl", OP_JL, 3, "%s %s", 1);
	addInstructionName("jg", OP_JG, 3, "%s %s", 1);
	addInstructionName("call", OP_CALL, 3, "%s %s", 1);
	addInstructionName("ret", OP_RET, 0, "", 0);
	addInstructionName("input", OP_INPUT, 0, "", 0);
	addInstructionName("output", OP_OUTPUT, 0, "", 0);
	addInstructionName("outchar", OP_OUTCHAR, 4, "%s %s", 1);
	addInstructionName("savebp", OP_SAVEBP, 0, "", 0);
	addInstructionName("rstrbp", OP_RSTRBP, 0, "", 0);
	addInstructionName("halt", OP_HALT, 0, "", 0);

	currentLabel=0;
	currentInst=0;

	printf("First assembly phase (analyze and decode instructions)..");
	parseAsm(fin);
	fclose(fin);
	printf("no errors\n");
	printf("Second assembly phase (resolve undefined references)..");
	resolveReferences();
	printf("no errors\n");
	printLabels();
	printf("Dumping generated binary code (please verify)\n");
	dumpBinaryCode();
	printf("no errors\n");

	FILE *fout=fopen(argv[2],"w");
	if (fout==NULL)
		printf("Error opening write file %s\n",argv[2]);
	generateBinary(fout);
	fclose(fout);

	return 0;
}
