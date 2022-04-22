%{
	#include <stdlib.h>
	#include <stdio.h>
  #include <string.h>

  #include "comp.c"

	int yylex(void);
  void yyerror(char const *s);
  int yydebug = 1;


struct tnode* makeFunNode(struct tnode *e);
struct tnode* makeAssgNode(struct tnode *l,struct tnode *r);
struct tnode* makeRetNode(struct tnode *e);
struct tnode* makeWhileNode(struct tnode *e,struct tnode *l);
struct tnode* makeIfNode(struct tnode *e,struct tnode *l,struct tnode *r);
struct tnode* makeConnNode(struct tnode *l,struct tnode *r);
struct tnode* makeOpNode(char c,struct tnode *l,struct tnode *r);
struct tnode* makeVarNode(char *c);
struct tnode* makeNumNode(int n);

%}

%union{
	struct tnode *no;
    char *s;
    int i;	
}
%type <no> Program Stmts Stmt AssgStmt IfElseStmt IfStmt RetStmt E WhileStmt
%token <s> VAR FUN READ WRITE ARGC IF ELSE RET WHILE DO
%token <i> NUM
%nonassoc '>' '<' '!'
%left '+' '-'
%left '*'
%left '='

%%

Program : READ'('ARGC')'';' ARGC'='FUN'('ARGC')''{' Stmts '}' WRITE'('ARGC')'';'      {FILE *fptr = fopen("output.txt", "w");header(fptr); footer(fptr); fHeader(fptr); evalStmt($13, fptr);}

Stmts : Stmts Stmt                                        {$$ = makeConnNode($1, $2);}
      | Stmt                                              {$$ = $1;}

Stmt : AssgStmt                                           {$$ = $1;}
     | IfStmt                                             {$$ = $1;}
     | IfElseStmt                                         {$$ = $1;}
     | RetStmt                                            {$$ = $1;}
     | WhileStmt                                          {$$ = $1;}

AssgStmt : VAR '=' E ';'                                  {$$ = makeAssgNode(makeVarNode($1), $3);}

WhileStmt : WHILE '('E')' DO '{' Stmts '}'                {$$ = makeWhileNode($3, $7);}

IfStmt : IF '('E')' '{' Stmts '}'                         {$$ = makeIfNode($3, $6, NULL);}

IfElseStmt : IF '('E')' '{' Stmts '}' ELSE '{' Stmts '}'  {$$ = makeIfNode($3, $6, $10);}

RetStmt : RET E';'                                        {$$ = makeRetNode($2);}    

E : E '+' E	                                              {$$ = makeOpNode('+', $1, $3);}
  | E '*' E                                               {$$ = makeOpNode('*', $1, $3);}
  | E '-' E                                               {$$ = makeOpNode('-', $1, $3);}
  | E '<''=' E                                            {$$ = makeOpNode('<', $1, $4);}
  | E '>''=' E                                            {$$ = makeOpNode('>', $1, $4);}
  | E '=''=' E	                                          {$$ = makeOpNode('=', $1, $4);}
  | E '!''=' E		                                      {$$ = makeOpNode('!', $1, $4);}
  | '('E')'                                               {$$ = $2;}
  | NUM                                                   {$$ = makeNumNode($1);}
  | VAR                                                   {$$ = makeVarNode($1);}
  | ARGC                                                  {$$ = makeVarNode("argc");}
  | FUN'('E')'                                            {$$ = makeFunNode($3);}
;

%%

void yyerror(char const *s)
{
    printf("yyerror %s\n",s);
}

struct symbol *head = NULL;

struct symbol* getSym(char *name)
{
    struct symbol *temp;
    if(strcmp("argc", name) == 0){
        temp = (struct symbol*)malloc(sizeof(struct symbol));
        temp->name = name;
        temp->binding = -3;
        temp->next = NULL;
        return temp;
    }
    temp = head;
    if (temp == NULL){
        temp = (struct symbol*)malloc(sizeof(struct symbol));
        temp->name = name;
        temp->binding = 1;
        temp->next = NULL;
        head = temp;
        return temp;
            
    }
    while(strcmp(temp->name, name)){
        if (temp->next == NULL){
            struct symbol *temp2 = (struct symbol*)malloc(sizeof(struct symbol));
            temp2->name = name;
            temp2->binding = temp->binding + 1;
            temp->next = temp2;
            temp2->next = NULL;
            return temp2;
        }
        temp = temp->next;
    }
    return temp;    
}
	
struct tnode* makeNumNode(int n)
{
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->type = 0;
    temp->val = n;
    temp->left = NULL;
    temp->right = NULL;
    temp->exp = NULL;
    return temp;
}

struct tnode* makeVarNode(char *c)
{
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->type = 1;
    temp->var = getSym(c);
    temp->left = NULL;
    temp->right = NULL;
    temp->exp = NULL;
    return temp;
}

struct tnode* makeOpNode(char c,struct tnode *l,struct tnode *r){
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->type = 2;
    temp->op = c;
    temp->left = l;
    temp->right = r;
    temp->exp = NULL;
    return temp;
}

struct tnode* makeConnNode(struct tnode *l,struct tnode *r){
    struct tnode* temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->type = 3;
    temp->left = l;
    temp->right = r;
    temp->exp = NULL;
    return temp;
}

struct tnode* makeIfNode(struct tnode *e,struct tnode *l,struct tnode *r){
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->type = 4;
    temp->exp = e;
    temp->left = l;
    temp->right = r;
    return temp;
}

struct tnode* makeWhileNode(struct tnode *e,struct tnode *l){
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->type = 5;
    temp->exp = e;
    temp->left = l;
    temp->right = NULL;
    return temp;
}

struct tnode* makeRetNode(struct tnode *e){
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->type = 6;
    temp->left = NULL;
    temp->exp = e;
    temp->right = NULL;
    return temp;
}

struct tnode* makeAssgNode(struct tnode *l,struct tnode *r){
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->type = 7;
    temp->left = l;
    temp->right = r;
    temp->exp = NULL;
    return temp;
}

struct tnode* makeFunNode(struct tnode *e){
    struct tnode *temp;
    temp = (struct tnode*)malloc(sizeof(struct tnode));
    temp->type = 8;
    temp->exp = e;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int main(int argc, char *argv[]) {
  extern FILE *yyin;
  yyin = fopen(argv[1], "r");
	yyparse();
	return 0;
}