#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <iomanip>
#include <cstring>

using namespace std;

// Estructura para almacenar las reglas (Token y Regex)
struct Regla {
    string tipo;
    string patron;
};

void analizarDocker(string codigo) {
    // Definición de expresiones regulares para Docker
    vector<Regla> reglas = {
        {"TK_COMENTARIO", "^#.*"},
        {"TK_INSTRUCCION", "^(FROM|RUN|CMD|LABEL|EXPOSE|ENV|ADD|COPY|ENTRYPOINT|VOLUME|USER|WORKDIR|ARG|STOPSIGNAL|HEALTHCHECK|ONBUILD)\\b"},
        {"TK_VALOR_ENV", "^\\b[A-Z_]+=[^\\s]+"},
        {"TK_RUTA", "^(/[a-zA-Z0-9._-]+)+|(\\.[a-zA-Z0-9._-]+)+"},
        {"TK_STRING", "^\"[^\"]*\"|^'[^']*'"},
        {"TK_IDENTIFICADOR", "^[a-zA-Z0-9._-]+"},
        {"TK_ESPACIO", "^[ \\t\\r\\n]+"}
    };

    cout << left << setw(20) << "TOKEN" << setw(25) << "LEXEMA" << "LINEA" << endl;
    cout << "------------------------------------------------------------" << endl;

    // Procesamiento línea por línea
    char* contexto = (char*)codigo.c_str();
    char* token_linea = strtok(contexto, "\n");
    int num_linea = 1;

    while (token_linea != NULL) {
        string str_linea(token_linea);
        size_t cursor = 0;

        while (cursor < str_linea.length()) {
            bool coincidencia = false;
            string sub = str_linea.substr(cursor);

            for (const auto& regla : reglas) {
                smatch match;
                regex e(regla.patron);

                if (regex_search(sub, match, e) && match.position() == 0) {
                    if (regla.tipo != "TK_ESPACIO") {
                        cout << left << setw(20) << regla.tipo 
                             << setw(25) << match.str() 
                             << num_linea << endl;
                    }
                    cursor += match.length();
                    coincidencia = true;
                    break;
                }
            }

            if (!coincidencia) {
                if (!isspace(str_linea[cursor])) {
                    cout << "ERROR LEXICO: Caracter '" << str_linea[cursor] 
                         << "' no reconocido en linea " << num_linea << endl;
                }
                cursor++;
            }
        }
        token_linea = strtok(NULL, "\n");
        num_linea++;
    }
}

int main() {
    // Ejemplo de contenido de un archivo Docker para pruebas
    string dockerfile = 
        "# Imagen base\n"
        "FROM ubuntu:22.04\n"
        "RUN apt-get update\n"
        "ENV APP_HOME=/app\n"
        "WORKDIR $APP_HOME\n"
        "COPY . .\n"
        "CMD [\"python3\", \"app.py\"]\n"
        "RUN apt-get @install\n";

    analizarDocker(dockerfile);
    return 0;
}