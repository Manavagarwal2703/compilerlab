#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

char tac_stack[MAX][MAX];
int tac_top = -1;
int temp_var_count = 0;

int precedence(char c) {
    if (c == '*') 
        return 3;
    else if (c == '.' || c == '|')
        return 2;
    return 0;
}

int isOperand(char c) {
    return isalpha(c);
}

void infixToPostfix(char* infix, char* postfix) {
    int i = 0, k = 0;
    char symbol;
    while (infix[i] != '\0') {
        symbol = infix[i];

        if (isOperand(symbol)) {
            postfix[k++] = symbol;
        }
        else if (symbol == '(') {
            stack[++top] = symbol;
        }
        else if (symbol == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = stack[top--];
            }
            top--;
        }
        else {
            while (top != -1 && precedence(stack[top]) >= precedence(symbol)) {
                postfix[k++] = stack[top--];
            }
            stack[++top] = symbol;
        }
        i++;
    }

    while (top != -1) {
        postfix[k++] = stack[top--];
    }
    postfix[k] = '\0';
}

void generateThreeAddressCode(char* postfix) {
    printf("\nThree Address Code:\n");
    for (int i = 0; postfix[i] != '\0'; i++) {
        if (isOperand(postfix[i])) {
            char temp[2] = {postfix[i], '\0'};
            strcpy(tac_stack[++tac_top], temp);
        } else {
            char op1[MAX], op2[MAX], result[MAX];
            strcpy(op2, tac_stack[tac_top--]);
            strcpy(op1, tac_stack[tac_top--]);
            snprintf(result, MAX, "t%d", ++temp_var_count);
            printf("%s = %s %c %s\n", result, op1, postfix[i], op2);
            strcpy(tac_stack[++tac_top], result);
        }
    }
}

int main() {
    char infix[MAX], postfix[MAX];
    printf("Enter the Regular Expression: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);
    
    generateThreeAddressCode(postfix);
    
    return 0;
}
