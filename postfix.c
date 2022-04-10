/* postfix.c
 *
 *  Created on: Apr 2, 2019
 *      Author: rsyoung
 */

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];

int postfixStackTop = -1;
int evalStackTop = -1;

int evalResult = 0;

void postfixPush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	printf("[----- [김기남]  [2022299002] -----]\n");
	char command;

	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;


}
// postfix를 변환하는 과정에서 사용되는 Stack쌓기
void postfixPush(char x)
{
    postfixStack[++postfixStackTop] = x;
}
// postfix를 변환하는 과정에서 Stack LastIn을 하나 빼기
char postfixPop()
{
	char x;
	// postfixStack이 모두 사용되었을 경우 문자열의 종료를 알리는 '\0' 반환
    if(postfixStackTop == -1)
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}

// postfix를 연산하는 과정에서 사용되는 Stack 쌓기
void evalPush(int x)
{
    evalStack[++evalStackTop] = x;
}

// postfix를 연산하는 과정에서 Stack LastIn 하나 뺴기
int evalPop()
{
	// evalStack이 모두 사용되 었을 경우 -1 반환
    if(evalStackTop == -1)
        return -1;
    else
	// operand를 한 개씩 Pop
        return evalStack[evalStackTop--];
}

// Infix형식을 infixExp에 할당받음
void getInfix()
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol)
{
	// 각 operate를 연산자 우선순위에 맞게 반환해줌.
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}
}

precedence getPriority(char x)
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);
	else
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')
	// 문자열의 끝("\0")을 만났을 때까지 반복
	{
		if(getPriority(*exp) == operand)
		{
			x = *exp;
        	charCat(&x);
		}
		// "(" 를 만났을 때, postfixPush함수 사용
        else if(getPriority(*exp) == lparen) {

        	postfixPush(*exp);
        }
		// ")" 를 만났을 때, "("위치가 있는 곳 postfixexp에 추가
        else if(getPriority(*exp) == rparen)
        {
        	while((x = postfixPop()) != '(') {
        		charCat(&x);
        	}
        }
        else
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
            {
				// 연산자 마지막 값은 뺀 후, postfixexp에 추가
            	x = postfixPop();
            	charCat(&x);
            }
            postfixPush(*exp);
        }
		// 다음 exp를 위와 같이 반복함
        exp++;
	}

    while(postfixStackTop != -1)
    {
    	x = postfixPop();
    	charCat(&x);
    }

}

void debug()
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';
         
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

// postfixExp에 postfix형식으로 할당된 값을 연산하는 함수
void evaluation()
{
	// opr은 피연사자를 할당하기 위한 변수
	int opr1, opr2, i;
	// 가지고 있는 피연산자의 개수를 할당. 개수만큼 아래에서 반복문
	int length = strlen(postfixExp);
	char symbol;
	// 0번째 Index부터 순차적으로 확인 하기 위해 -1 할당
	evalStackTop = -1;

	for(i = 0; i < length; i++)
	{
		// i번째 연산자를 symbol에 할당
		symbol = postfixExp[i];
		if(getToken(symbol) == operand) {
			evalPush(symbol - '0');
		}
		else {
			// 피연산자를 Stack방식으로 한개씩 총 2개를 opr2와 opr1에 할당
			opr2 = evalPop();
			opr1 = evalPop();
			switch(getToken(symbol)) {
			// getToken(symbol) 값이 'plus'일 경우 opr1 + opr2
			case plus: evalPush(opr1 + opr2); break;
			// getToken(symbol) 값이 'minus'일 경우 opr1 - opr2
			case minus: evalPush(opr1 - opr2); break;
			// getToken(symbol) 값이 'times'일 경우 opr1 * opr2
			case times: evalPush(opr1 * opr2); break;
			// getToken(symbol) 값이 'divide'일 경우 opr1 / opr2
			case divide: evalPush(opr1 / opr2); break;
			default: break;
			}
		}
	}
	// Stack에 쌓여있는 모든 연산이 끝날 경우, evalResult에 결과 할당
	evalResult = evalPop();
}

