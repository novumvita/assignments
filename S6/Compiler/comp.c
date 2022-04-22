#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int reg = 0;
int label = 0;

struct tnode{
 int val;
 int type;
 char op;
 struct symbol *var;
 struct tnode *left,*right, *exp;
 };


struct symbol{
    int binding;
    char *name;
    struct symbol *next;
};

int getLabel(){return label++;}

int getReg(){return reg++;}

void freeReg(){reg--;}

void pushRegs(FILE *fptr){
    int reg = getReg();
    for(int i = 0; i < reg; i++){
        fprintf(fptr, "PUSH R%d\n", i);
    }
    freeReg();
}

void popRegs(FILE *fptr){
    int reg = getReg();
    for(int i = reg - 2; i >= 0; i--){
        fprintf(fptr, "POP R%d\n", i);
    }
    freeReg();
}

int printAST(struct tnode* root){
    
    if(root == NULL)
		return 1;

	printf("%d\n", root->type);

	printAST(root->left);
	printAST(root->exp);
	printAST(root->right);
	return 1;
}

//--------------------------------------------------------------------------------------------------------------------------------

int evalExp (struct tnode *node, FILE *fptr){
    int l, r, e;
    switch(node->type){
        case 0:
        r = getReg();
        fprintf(fptr, "MOV R%d, %d\n", r, node->val);
        return r;
        break;
        case 1:
        r = getReg();
        l = getReg();
        fprintf(fptr, "MOV R%d, %d\n", l, node->var->binding);
        fprintf(fptr, "ADD R%d, BP\n", l);
        fprintf(fptr, "MOV R%d, [R%d]\n", r, l);
        freeReg();
        return r;
        break;
        case 2:
        l = evalExp(node->left, fptr);
        r = evalExp(node->right, fptr);
        switch(node->op){
            case '+':
            fprintf(fptr, "ADD R%d, R%d\n", l, r);
            break;
            case '*':
            fprintf(fptr, "MUL R%d, R%d\n", l, r);
            break;
            case '-':
            fprintf(fptr, "SUB R%d, R%d\n", l, r);
            break;
            case '<':
            fprintf(fptr, "LE R%d, R%d\n", l, r);
            break;
            case '>':
            fprintf(fptr, "GE R%d, R%d\n", l, r);
            break;
            case '=':
            fprintf(fptr, "EQ R%d, R%d\n", l, r);
            break;
            case '!':
            fprintf(fptr, "NE R%d, R%d\n", l, r);
            break;
        }
        freeReg();
        return l;
        break;
        case 8:
        pushRegs(fptr);
        e = evalExp(node->exp, fptr);
        fprintf(fptr, "PUSH R%d\n", e);
        fprintf(fptr, "PUSH R0\n");
        fprintf(fptr, "CALL 2122\n");
        fprintf(fptr, "POP R%d\n", e);
        fprintf(fptr, "POP R19\n");
        popRegs(fptr);
        return e;
    }
}

void evalStmt(struct tnode *node, FILE *fptr){
    if(node == NULL) return;
    int label1, label2, l, e;
    switch(node->type){
        case 3:
        evalStmt(node->left, fptr);
        evalStmt(node->right, fptr);
        break;
        case 4:
        e = evalExp(node->exp, fptr);
        label1 = getLabel();
        label2 = getLabel();
        fprintf(fptr, "JZ R%d, L%d\n", e, label1);
        evalStmt(node->left, fptr);
        fprintf(fptr, "JNZ R%d, L%d\n", e, label2);
        fprintf(fptr, "L%d:\n", label1);
        evalStmt(node->right, fptr);
        fprintf(fptr, "L%d:\n", label2);
        freeReg();
        break;
        case 5:
        label1 = getLabel();
        label2 = getLabel();
        fprintf(fptr, "L%d:\n", label1);
        e = evalExp(node->exp, fptr);
        fprintf(fptr, "JZ R%d, L%d\n", e, label2);
        evalStmt(node->left, fptr);
        fprintf(fptr, "JMP L%d\n", label1);
        fprintf(fptr, "L%d:\n", label2);
        freeReg();
        break;
        case 6:
        e = evalExp(node->exp, fptr);
        fprintf(fptr, "SUB BP, 2\n");
        fprintf(fptr, "MOV [BP], R%d\n", e);
        fprintf(fptr, "SUB SP, %d\n", 20);
        fprintf(fptr, "POP BP\n");
        fprintf(fptr, "RET\n");
        freeReg();
        break;
        case 7:
        l = getReg();
        e = evalExp(node->right, fptr);
        fprintf(fptr, "MOV R%d, R%d\n", l, node->left->var->binding);
        fprintf(fptr, "ADD R%d, BP\n", l);
        fprintf(fptr, "MOV [R%d], R%d\n", l, e);
        freeReg();
        freeReg();
        break;
    }
}

void header(FILE *fptr){
    int reg = getReg();
    fprintf(fptr, "0\n2056\n0\n0\n0\n0\n0\n0\n");
    fprintf(fptr, "MOV R%d, \"Read\"\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "MOV R%d, -1\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "MOV R%d, 4096\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "CALL 0\n");
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "MOV SP, 4097\n");
    fprintf(fptr, "MOV BP, SP\n");
    fprintf(fptr, "CALL 2122\n");
    freeReg();
}

void fHeader(FILE *fptr){
    fprintf(fptr, "PUSH BP\n");
    fprintf(fptr, "MOV BP, SP\n");
    fprintf(fptr, "ADD SP, 20\n");
}

void footer(FILE *fptr){
    int reg = getReg();
    int reg2 = getReg();
    fprintf(fptr, "MOV R%d, \"Write\"\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "MOV R%d, -2\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "MOV R%d, [4097]\n", reg2);
    fprintf(fptr, "MOV R%d, R%d\n", reg, reg2);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "PUSH R%d\n", reg);
    fprintf(fptr, "CALL 0\n");
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "POP R%d\n", reg);
    fprintf(fptr, "INT 10\n");
    freeReg();
    freeReg();
}