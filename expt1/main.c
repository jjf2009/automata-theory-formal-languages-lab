#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool numCheck(char c) {
    return (c >= '0' && c <= '9');
}

bool alphaCheck(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_'));
}

bool alphaNumCheck(char c) {
    return (alphaCheck(c) || numCheck(c));
}

bool isNumber(char* str) {
    int i = 0;
    if (str[i] == '-' || str[i] == '+') i++; // optional sign
    if (str[i] == '\0') return false;         // just a sign is not a number

    bool hasDigit = false;
    while (numCheck(str[i])) { hasDigit = true; i++; } // integer part

    if (str[i] == '.') {                      // optional decimal part
        i++;
        while (numCheck(str[i])) { hasDigit = true; i++; }
    }

    return hasDigit && str[i] == '\0';
}

bool isKeyword(char* str) {
    char keywords[][20] = {
        "auto", "break", "case", "char", "const", "continue", "default", "do",
        "double", "else", "enum", "extern", "float", "for", "while", "goto",
        "if", "inline", "int", "long", "register", "restrict", "return", "short",
        "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "_Alignas", "_Alignof", "_Atomic",
        "_Bool", "_Complex", "_Generic", "_Noreturn", "_Static_assert",
        "_Thread_local", "alignas", "alignof", "bool", "constexpr", "false",
        "true", "nullptr"
    };

    int len = sizeof(keywords) / sizeof(keywords[0]);
    for (int i = 0; i < len; i++)
        if (!strcmp(str, keywords[i])) return true;
    return false;
}

bool isIdentifier(char* str) {
    if (str[0] == '\0') return false;
    if (!alphaCheck(str[0]) || isKeyword(str)) return false;

    for (int i = 1; str[i] != '\0'; i++)
        if (!alphaNumCheck(str[i])) return false;

    return true;
}

int main() {
    while (true) {
        char input[100];
        printf("Enter a string : ");
        fgets(input, 100, stdin);
        input[strcspn(input, "\n")] = 0;

        if (isKeyword(input)) {
            printf("-> C keyword\n\n");
        } else if (isNumber(input)) {
            printf("-> Number\n\n");
        } else if (isIdentifier(input)) {
            printf("-> Valid identifier\n\n");
        } else {
            printf("-> Invalid identifier\n\n");
        }
    }
}