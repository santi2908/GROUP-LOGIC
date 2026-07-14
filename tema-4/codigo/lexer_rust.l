%{
#include <stdio.h>
%}

%option noyywrap

/* Definiciones de expresiones regulares */
DIGITO      [0-9]
LETRA       [a-zA-Z_]
ID          {LETRA}({LETRA}|{DIGITO})*
NUMERO      {DIGITO}+
ESPACIO     [ \t\n\r]+

%%

"fn"        { printf("TOKEN_PALABRA_RESERVADA: fn\n"); }
"let"       { printf("TOKEN_PALABRA_RESERVADA: let\n"); }
"mut"       { printf("TOKEN_PALABRA_RESERVADA: mut\n"); }
"if"        { printf("TOKEN_PALABRA_RESERVADA: if\n"); }
"else"      { printf("TOKEN_PALABRA_RESERVADA: else\n"); }
"while"     { printf("TOKEN_PALABRA_RESERVADA: while\n"); }
"return"    { printf("TOKEN_PALABRA_RESERVADA: return\n"); }
"i32"       { printf("TOKEN_TIPO_DATO: i32\n"); }
"bool"      { printf("TOKEN_TIPO_DATO: bool\n"); }
"true"      { printf("TOKEN_BOOLEANO: true\n"); }
"false"     { printf("TOKEN_BOOLEANO: false\n"); }

{ID}        { printf("TOKEN_IDENTIFICADOR: %s\n", yytext); }
{NUMERO}    { printf("TOKEN_LITERAL_ENTERO: %s\n", yytext); }

"+"         { printf("TOKEN_OPERADOR: +\n"); }
"-"         { printf("TOKEN_OPERADOR: -\n"); }
"*"         { printf("TOKEN_OPERADOR: *\n"); }
"/"         { printf("TOKEN_OPERADOR: /\n"); }
"=="        { printf("TOKEN_OPERADOR: ==\n"); }
"!="        { printf("TOKEN_OPERADOR: !=\n"); }
"="         { printf("TOKEN_OPERADOR: =\n"); }
"<"         { printf("TOKEN_OPERADOR: <\n"); }
">"         { printf("TOKEN_OPERADOR: >\n"); }
"->"        { printf("TOKEN_DELIMITADOR: ->\n"); }

"{"         { printf("TOKEN_DELIMITADOR: {\n"); }
"}"         { printf("TOKEN_DELIMITADOR: }\n"); }
"("         { printf("TOKEN_DELIMITADOR: (\n"); }
")"         { printf("TOKEN_DELIMITADOR: )\n"); }
";"         { printf("TOKEN_DELIMITADOR: ;\n"); }
":"         { printf("TOKEN_DELIMITADOR: :\n"); }

{ESPACIO}   { /* Ignorar espacios en blanco */ }

.           { printf("ERROR LÉXICO: Carácter no reconocido: %s\n", yytext); }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            printf("Error al abrir el archivo.\n");
            return 1;
        }
    }
    yylex();
    return 0;
}