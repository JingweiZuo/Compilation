// Cet enum contient tous les types possibles pour un noeud "operator"
typedef enum { OPER_ADD, OPER_SUB, OPER_MULT, OPER_DIV, OPER_OUTPUT } nodeOper;

// Les deux types de noeuds possibles, "numeric" ou "operator"
typedef enum { typeNumeric, typeOperator } nodeEnum;

/* un noeud numeric (float) permet de stocker une valeur reelle */
typedef struct {
	float valeur;
} numericNodeType;

/* un noeud operator permet de stocker un operateur, le nombre d'operandes et les pointeurs vers les noeuds
   operande correspondants */
typedef struct {
	int oper;
	int nOperands;
	struct nodeTypeTag **op; 
} operatorNodeType;

/* Cette structure, fondamentale, permet de definir un noeud a geometrie variable. Le type
   permet de definir le type du noeud (numeric ou operator) et l'union permet, en fonction
   du type, d'acceder aux bonnes informations */

typedef struct nodeTypeTag {
	nodeEnum type;
	int digraphNode;		// Pour generer des beaux graphes avec dot
	union {
		numericNodeType t_numeric;
		operatorNodeType t_oper;
	};
} nodeType;

// La, il faudrait mettre les extern de toutes les fonctions definies dans ast.c
extern nodeType *createNumericNode(float v);
extern nodeType *createOperatorNode(int oper, int nOperands, ...);
