grammar ifcc;

axiom : prog EOF ;

prog : 'int' 'main' '(' ')' '{' (stmt)* return_stmt '}' ;

stmt : declaration ';'
      | assignment ';'
      ;
declaration : 'int' VAR ;

assignment : VAR '=' expr
           ;

return_stmt : RETURN expr ';' ;

expr : PAR_OPEN expr PAR_CLOSE # par_expr
     | expr (MULT | DIV | MOD) expr # mult_div_mod_expr
     | SUB expr # minus_expr
     | NOT expr # not_expr
     | expr (SHIFT_L | SHIFT_R) expr # shift_expr
     | expr BIT_AND expr # bit_and_expr
     | expr BIT_OR expr # bit_or_expr
     | expr BOOL_AND expr # bool_and_expr
     | expr BOOL_OR expr # bool_or_expr
     | expr (ADD | SUB) expr # add_sub_expr
     | expr (LT | GT ) expr # cmp_expr
     | expr (LTE | GTE) expr # cmp_eq_expr
     | expr (EQ | NEQ) expr # eq_expr
     | VAR # var_expr
     | CONST # const_expr
     ;


RETURN : 'return' ;
CONST : [0-9]+ ;
VAR : [a-zA-Z][a-zA-Z0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

ADD : '+' ;
SUB : '-' ;
MULT : '*' ;
DIV : '/' ;
MOD : '%' ;
BIT_AND : '&' ;
BIT_OR : '|' ;
SHIFT_L : '<<' ;
SHIFT_R : '>>' ;
BOOL_AND : '&&' ;
BOOL_OR : '||' ;
NOT : '!' ;
LT : '<' ;
GT : '>' ;
EQ : '==' ;
NEQ : '!=' ;
LTE : '<=' ;
GTE : '>=' ;

PAR_OPEN : '(' ;
PAR_CLOSE : ')' ;

