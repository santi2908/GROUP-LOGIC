# Analizador Léxico - Lenguaje L-Rust

Este repositorio contiene la implementación de un analizador léxico (lexer) construido mediante el metacompilador **Flex**. El analizador está diseñado para procesar **L-Rust**, un lenguaje subconjunto simplificado del lenguaje de programación Rust.

Este proyecto fue desarrollado para la asignatura Lenguajes y Compiladores (Periodo Académico 2026-I) de la Universidad Nacional Experimental de Guayana (UNEG).

## Equipo de Desarrollo
* Santiago Sanchez (C.I: 30.001.012)
* Nicole García (C.I: 30.809.865)
* Mauricio Leal (C.I: 30.366.382)
* Jesús Ramírez (C.I: 31.074.731)

---

## Descripción del Lenguaje L-Rust

L-Rust mantiene la sintaxis estricta de Rust pero se enfoca en estructuras elementales para fines académicos. El lexer es capaz de reconocer los siguientes componentes:

### Palabras Reservadas
`fn`, `let`, `mut`, `if`, `else`, `while`, `return`

### Tipos de Datos y Literales
* **Tipos:** `i32`, `bool`
* **Booleanos:** `true`, `false`
* **Números:** Secuencias de dígitos enteros (ej. 10, 42)

### Identificadores
Secuencias que comienzan con una letra o guion bajo, seguidas de letras o números (ej. `contador`, `variable_1`).

### Operadores y Delimitadores
* **Aritméticos y Relacionales:** `+`, `-`, `*`, `/`, `==`, `!=`, `=`, `<`, `>`
* **Sintácticos:** `{`, `}`, `(`, `)`, `;`, `:`, `->`

---

## Requisitos Previos

Para compilar y ejecutar este analizador léxico en un entorno local, necesitas:

1. **Flex (Fast Lexical Analyzer Generator):** Herramienta para generar el código C del analizador.
2. **GCC (GNU Compiler Collection):** Compilador de C para generar el ejecutable final (en Windows se recomienda usar MinGW/MSYS2).

---

## Pasos de Instalación e Implementación

A continuación, se detalla el proceso paso a paso para poner a funcionar el lexer desde la terminal.

### Paso 1: Generar el código fuente en C
Ejecuta Flex apuntando al archivo de especificación léxica `.l`. Esto leerá las expresiones regulares y generará automáticamente un archivo llamado `lex.yy.c`.

Comando:
`flex lexer_rust.l`

### Paso 2: Compilar el analizador
Utiliza GCC para compilar el archivo C generado en el paso anterior y crear el archivo ejecutable. Es fundamental incluir la bandera `-lfl` para enlazar la librería de Flex.

Comando:
`gcc lex.yy.c -o lexer_rust -lfl`

### Paso 3: Ejecutar el analizador léxico
Pasa un archivo fuente de prueba escrito en L-Rust como argumento al ejecutable generado. El programa leerá el texto e imprimirá en consola cada token detectado.

Comando:
`./lexer_rust prueba.rs`

---

## Archivo de Prueba de Ejemplo

Puedes utilizar el siguiente bloque de código L-Rust dentro de un archivo `prueba.rs` para validar el funcionamiento del lexer:

```rust
fn calcular_valor() -> bool {
    let mut contador: i32 = 10;
    let limite: i32 = 0;
    
    if contador != limite {
        contador = contador * 2;
    } else {
        return false;
    }
    
    while contador > 0 {
        contador = contador - 1;
    }
    
    return true;
}