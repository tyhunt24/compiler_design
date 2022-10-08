//Abstract Syntax Tree Implementation
#include <string.h>

struct AST{
	char nodeType[50];
	char LHS[50];
	char RHS[50];
	char value[50];

	//since C doesn't have booleans
	//I used ints if a value isNumber = 1
	//If the value is not a number it gets a 0
	int isNumber; 
	
	//gives us left and right side of a tree
	struct AST * left; 
	struct AST * right;

	// review pointers to structs in C 
	// complete the tree struct with pointers
};

//Something like ID = ID
struct AST * AST_assignment(char nodeType[50], char LHS[50], char RHS[50]){
	

	struct AST* ASTassign = malloc(sizeof(struct AST));
	strcpy(ASTassign->nodeType, nodeType);
	strcpy(ASTassign->LHS, LHS);
	strcpy(ASTassign->RHS, RHS);
	

/*
       =
	 /   \
	x     y

*/	
	return ASTassign;
	
}

struct AST * AST_Write(char nodeType[50], char LHS[50], char RHS[50]){
	
	struct AST* ASTtype = malloc(sizeof(struct AST));
	strcpy(ASTtype->nodeType, nodeType);
	strcpy(ASTtype->LHS, LHS);
	strcpy(ASTtype->RHS, RHS);
		
	return ASTtype;
	
}

//function for expressions
//also used this at the bottom of for Numbers and IDS
struct AST * newTree(char nodeType[50], struct AST *l, struct AST *r) {
	struct AST* astTree = malloc(sizeof(struct AST));
	strcpy(astTree->nodeType, nodeType);
	astTree->left = l; //points us to the left side expression
	astTree->right = r; // points us to the right side expression

/*
       +
	 /   \
MathExpr MathExpr

*/	
}

//gives us that id = mathExpr
struct AST * idMathexp(char nodeType[50], char lhs[50], struct AST *r) {
	struct AST* astTree = malloc(sizeof(struct AST));
	strcpy(astTree->nodeType, nodeType); //gives us the node type which would be +
	strcpy(astTree->LHS, lhs); // gives us the ID on the left hand side
	astTree->right = r;

	/*
       =
	 /   \
	id   mathExpr

*/	
}

//allows something like ids and numbers to be put in the tree
struct AST * addTree(char nodeType[50], int isNum) {
	struct AST* astTree = malloc(sizeof(struct AST));
	strcpy(astTree->nodeType, nodeType); //gives us whatever value either variable or int
	astTree->isNumber = isNum;
}

