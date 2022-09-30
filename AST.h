#include <string.h>

struct AST {

    char nodeType[50];
    
    struct AST * left;
    struct AST * right;
};

struct AST * tree(char node[50], struct AST* l, struct AST * r) {
    struct AST* ASTassign = malloc(sizeof(struct AST));
    strcpy(ASTassign->nodeType, node);
    ASTassign->left = l;
    ASTassign->right = r;

    return ASTassign;
}