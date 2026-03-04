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
     | expr (ADD | SUB) expr # add_sub_expr
     | VAR # var_expr
     | CONST # const_expr
     ;


RETURN : 'return' ;
CONST : [0-9]+ ;
VAR : [a-zA-Z0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

ADD : '+' ;
SUB : '-' ;
MULT : '*' ;
DIV : '/' ;
MOD : '%' ;
PAR_OPEN : '(' ;
PAR_CLOSE : ')' ;
