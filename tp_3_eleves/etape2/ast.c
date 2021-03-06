#include "ast.h"

// Cette variable globale vaut au depart 0, et est incrementee a chaque fois
int countDigraph;

nodeType *createNumericNode(float v)
{
	nodeType *p;

	if ((p=malloc(sizeof(nodeType))) == NULL)
	{
		printf("out of memory error\n");
		exit(1);
	}

	p->type=typeNumeric;
	p->t_numeric.valeur=v;
	
	return p;
}

nodeType *createOperatorNode(int oper, int nops, ...) 
{
    	va_list ap;
    	nodeType *p;
    	int i;

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

    	/* copy information */
    	p->type = typeOperator;
    	p->t_oper.oper = oper;
    	p->t_oper.nOperands = nops;
    	va_start(ap, nops);
    	for (i = 0; i < nops; i++)
        	p->t_oper.op[i] = va_arg(ap, nodeType*);
    	va_end(ap);
    	return p;
}

nodeType *createIdentifierNode(char *id)
{
        nodeType *p;

        if ((p=malloc(sizeof(nodeType))) == NULL)
        {
                printf("out of memory error\n");
                exit(1);
        }

        p->type=typeIdentifier;
        p->t_identifier.ident=strdup(id);

        return p;
}

void generateAsmRec(nodeType *n, FILE *fout)
{
	if (n==NULL)
		return;

	switch (n->type)
	{
		case typeNumeric:
		case typeIdentifier:
			break;
		case typeOperator:
			{
				switch (n->t_oper.oper)
				{
					case OPER_SEQUENCE:
						generateAsmRec(n->t_oper.op[0],fout);
						generateAsmRec(n->t_oper.op[1],fout);
						break;
					case OPER_WRITE:
						generateAsmExpression(n->t_oper.op[0],fout);
						fprintf(fout,"\toutput\n");
						break;
					case OPER_SKIP:
						break;
					default:
						break;
				}
			}
			break;
	}
}

void generateAsmExpression(nodeType *n, FILE *fout)
{
        if (n==NULL)
                return;

        switch (n->type)
        {
                case typeIdentifier:
			break;
                case typeNumeric:
                        {
                                fprintf(fout,"\tpushr\t%f\n",n->t_numeric.valeur);
                        }
                        break;
                case typeOperator:
                        {
                                switch (n->t_oper.oper)
                                {
                                        case OPER_ADD:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\tadd\n");
                                                break;
                                        case OPER_SUB:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\tsub\n");
                                                break;
                                        case OPER_MULT:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\tmult\n");
                                                break;
                                        case OPER_DIV:
                                                generateAsmExpression(n->t_oper.op[0],fout);
                                                generateAsmExpression(n->t_oper.op[1],fout);
                                                fprintf(fout,"\tdiv\n");
                                                break;
                                        default:
                                                break;
                                }
                        }
                        break;
        }
}

void generateAsm(nodeType *n, char *filename)
{
	FILE *fout;

	fout=fopen(filename,"w");
	generateAsmRec(n,fout);
	fprintf(fout,"\thalt\n");
	fprintf(fout,"\tend\n");
	fclose(fout);	
}

void generateDigraphNameNode(nodeType *n,FILE *fout)
{
        if (n==NULL)
                return;

        switch (n->type)
        {
		case typeIdentifier:
			break;
                case typeNumeric:
                        {
				n->digraphNode=countDigraph++;
                                fprintf(fout,"\tA%3.3d [label=\"%f\"]\n",n->digraphNode,n->t_numeric.valeur);
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
                                                fprintf(fout,"\tA%3.3d [label=\"+\"]\n",n->digraphNode);
                                                break;
                                        case OPER_SUB:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\"-\"]\n",n->digraphNode);
                                                break;
                                        case OPER_MULT:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\"*\"]\n",n->digraphNode);
                                                break;
                                        case OPER_DIV:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
                                                n->digraphNode=countDigraph++;
                                                fprintf(fout,"\tA%3.3d [label=\"/\"]\n",n->digraphNode);
                                                break;
                                        case OPER_SKIP:
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\"skip\"]\n",n->digraphNode);
                                                break;
                                        case OPER_WRITE:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\"write\"]\n",n->digraphNode);
                                                break;
                                        case OPER_SEQUENCE:
                                                generateDigraphNameNode(n->t_oper.op[0],fout);
                                                generateDigraphNameNode(n->t_oper.op[1],fout);
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\";\"]\n",n->digraphNode);
                                                break;
                                        case OPER_RESERVE_SPACE:
						n->digraphNode=countDigraph++;
                                		fprintf(fout,"\tA%3.3d [label=\"reserve_space\"]\n",n->digraphNode);
                                                break;
                                        default:
                                                break;
                                }
                        }
                        break;
        }
}

void generateDigraphEdges(nodeType *n,FILE *fout)
{
        if (n==NULL)
                return;

        switch (n->type)
        {
                case typeNumeric:
                case typeIdentifier:
                        break;
                case typeOperator:
                        {
                                switch (n->t_oper.oper)
                                {
                                        case OPER_ADD:
                                        case OPER_SUB:
                                        case OPER_MULT:
                                        case OPER_DIV:
                                        case OPER_SEQUENCE:
                                                fprintf(fout,"\tA%3.3d -> A%3.3d\n",
							n->digraphNode,n->t_oper.op[0]->digraphNode);
                                                fprintf(fout,"\tA%3.3d -> A%3.3d\n",
							n->digraphNode,n->t_oper.op[1]->digraphNode);
                                                generateDigraphEdges(n->t_oper.op[0],fout);
                                                generateDigraphEdges(n->t_oper.op[1],fout);
                                                break;
                                        case OPER_WRITE:
                                                fprintf(fout,"\tA%3.3d -> A%3.3d\n",
							n->digraphNode,n->t_oper.op[0]->digraphNode);
                                                generateDigraphEdges(n->t_oper.op[0],fout);
                                                break;
					case OPER_SKIP:
						break;
                                        default:
                                                break;
                                }
                        }
                        break;
        }
}

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
