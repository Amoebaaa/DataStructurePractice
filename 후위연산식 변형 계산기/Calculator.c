/*
* 소괄호를 포함한 사칙연산을 구현
* 
* 
* 동적할당을 이용해 길이 제한 = 메모리 제한인 문자열로 식을 입력 받을 것
* ㄴ 양식에 맞는지 파악할 것
* 
* 1) 동적할당을 이용한 길이 제한이 없는 (메모리 제한은 제외) 문자열 형태로 사칙연산 식 입력받기
* 2) 양식에 맞는지 검사
* 
* 3) 식을 후위연산식으로 변경
* 
* 4) 후위연산식을 계산
* 
* 5) 결과 출력
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "stack_using_linked_list.h"

//////////////////////////////////// 함수 원형 선언

/*
* 개행을 입력받을때까지 getchar를 반복하여 input buffer를 비운다.
*/
void flush_input_buffer();

/*
* 사용자로부터 문자열을 받아 첫번째 매개변수가 가리키도록한다.
* 두번째 매개변수는 해당 문자열의 길이를 담는다.
* 개행은 문자열에 포함되지 않는다.
* 
* 반환값
* 0: 메모리 할당 실패
* 0: 최대길이 도달
* 1: 입력 성공
*/
int input_str(char** str, unsigned int* str_length);

/*
* 문자열이 사칙연산에 적합한지 검사한다.
* 
* 반환값
* 0: 적합하지 않은 경우
* 1: 적합한 경우
*/
int exam_expression();

/*
* 중위 연산식을 후위 연산식으로 변경하는 함수
* 
* 각 연산기호, 숫자는 공백으로 구분되어 있다고 가정된다.
* 변환된 문자열은 세번째 매개변수가 가리키게된다.
* 두번째 매개변수로는 문자열의 길이를 입력받는다.
* 
* 각 숫자값은 long의 범위를 벗어나지 않았다고 가정한다.
* 
* 반환값
* 0: 메모리 할당 실패
* 1: 변환 성공
*/
int infix_to_postfix(char**infix_str, unsigned int length, char**postfix_str);

/*
* 연산자간 우선순위 판단함수
* 입력 문자 : + - * / 만 입력되었다고 가정한다.
* 
* 반환값
* 1 : op1이 우선순위가 더 높을 때
* 0 : 둘의 우선순위가 같을 떄
* -1 : op1의 우선순위가 더 낮을 때
*/
int cmp_operator(char op1, char op2);


/*
* 후위표현식 계산 함수
* postfix_str: 토큰은 공백으로 구분된 문자열(예: "1 2 +")
* success: NULL 허용, 실패 시 FALSE(0)를 설정
* 반환값: 계산 결과 (정상일 때) / 오류 시 0 반환(성공 여부는 success로 확인)
*/
long evaluate_postfix(const char* postfix_str, int* success);

///////////////////////////////////////// 함수 구현


int input_str(char **str, unsigned int* str_length) {

	/*
	* 입력 버퍼에 있는 문자를 하나하나 읽는다.
	* malloc으로 각 바이트에 담는다.
	* 개행, EOF를 받았다면 해당 자리에 널문자로 대체한다.
	* 
	* 길이 최대값에 도달했다면 가장 마지막위치에 \0 삽입 후 뒤 부분은 자를 것
	*/
	
	*str_length = 0;	//길이 초기화
	char* tmp;
	char ch;
	

	printf("식을 입력하세요>:");

	//초기 메모리 할당
	if ((*str = (char*)malloc(1)) == NULL) {
		return FALSE;
	}

	//개행을 입력받을때까지 반복
	while (1) {
		ch = getchar();
		(*str_length)++;

		//길이 최대값에 도달했다면
		if (*str_length == UINT_MAX) { //길이 최대값에 도달했다면
			(*str)[*str_length-1] = '\0'; //가장 마지막 인덱스를 \0로 변환

			if (ch != '\n') { //입력이 끝난게 아니라면 입력버퍼 지우기
				flush_input_buffer(); 
			}
			return FALSE;
		}

		tmp = (char*)realloc(*str,sizeof(char) * (*str_length));
		if (tmp == NULL) { //메모리 할당 실패 시

			free(*str);
			return FALSE;
		}
		*str = tmp;


		if (ch == '\n' || ch == EOF) { //개행, EOF를 입력받았다면 대신 \0 삽입 후 탈출
			(*str)[*str_length - 1] = '\0';
			break;
		}
		(*str)[*str_length - 1] = ch;

	}
	return TRUE;
}

int exam_expression() {
	//자세한 구현은 현 시점에서 생략
	return 1;
}

void flush_input_buffer() {
	while (getchar() != '\n');
}

int cmp_operator(char op1, char op2) {
	

	//우선 순위가 같은 경우
	if (op1 == op2) {
		return 0;
	}
	if ((op1 == '+' || op1 == '-') && (op2 == '+' || op2 == '-')) {
		return 0;
	}

	if((op1 == '*' || op1 == '/') && (op2 == '*' || op2 == '/')) {
		return 0;
	}

	
	//op1가 높은 우선순위를 가질 경우
	if (op1 == '*' || op1 == '/') {
		return 1;
	}

	//op2가 더 높은 우선순위를 가질 경우
	return -1;
}

int infix_to_postfix(char** infix_str, unsigned int length, char** result_str) {
	/*
	* 단순하고 안전한 후위표현식 변환 구현
	* - postfix_str은 infix 길이 +1 바이트 할당
	* - strcat 대신 버퍼 위치(pos)를 관리하며 snprintf로 안전하게 추가
	*/

	stack_t stack;
	stack_init(&stack);

	char ch;
	char stack_ch;
	char* endptr;
	long digit_value;
	char digit_str[32];
	int digit_len;
	unsigned int infix_index = 0;

	// 할당: infix 길이 + 1 (널)
	char *postfix_str = (char*)malloc(length + 1);
	if (postfix_str == NULL) {
		return FALSE;
	}
	unsigned int pos = 0;
	postfix_str[0] = '\0';

	while (infix_index < length) {
		ch = (*infix_str)[infix_index];

		// 공백 건너뛰기
		if (ch == ' ') {
			infix_index++;
			continue;
		}

		// 숫자 파싱 시도
		digit_value = strtol(&(*infix_str)[infix_index], &endptr, 10);
		if (endptr != &(*infix_str)[infix_index]) { // 숫자였음
			digit_len = (int)(endptr - &(*infix_str)[infix_index]);
			// 숫자를 문자열로 변환하여 버퍼에 추가
			snprintf(digit_str, sizeof(digit_str), "%ld", digit_value);
			// 남은 공간 계산 및 안전하게 추가
			if (pos < length) {
				int written = snprintf(postfix_str + pos, (length + 1) - pos, "%s", digit_str);
				if (written > 0) pos += (unsigned int)written;
			}
			// 숫자 뒤에 공백 추가
			if (pos < length) {
				postfix_str[pos++] = ' ';
				postfix_str[pos] = '\0';
			}
			infix_index += digit_len;
			continue;
		}

		// 괄호/연산자 처리
		if (ch == '(') {
			stack_push(&stack, ch);
			infix_index++;
			continue;
		}
		if (ch == ')') {
			// '(' 나올때까지 pop
			while (stack_isEmpty(&stack) == 0) {
				stack_pop(&stack, &stack_ch);
				if (stack_ch == '(') break;
				// append operator and space
				if (pos < length) postfix_str[pos++] = stack_ch;
				if (pos < length) postfix_str[pos++] = ' ';
				if (pos < length) postfix_str[pos] = '\0';
			}
			infix_index++;
			continue;
		}

		// 연산자 처리(+ - * /)
		if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
			// 스택의 top이 연산자이고 우선순위가 높거나 같으면 pop하여 출력
			while (stack_isEmpty(&stack) == 0) {
				stack_peek(&stack, &stack_ch);
				if (stack_ch == '(') break;
				// stack_ch의 우선순위가 ch보다 크거나 같으면 pop
				int cmp = cmp_operator(stack_ch, ch);
				if (cmp >= 0) {
					stack_pop(&stack, &stack_ch);
					if (pos < length) postfix_str[pos++] = stack_ch;
					if (pos < length) postfix_str[pos++] = ' ';
					if (pos < length) postfix_str[pos] = '\0';
				} else break;
			}
			// 현재 연산자 push
			stack_push(&stack, ch);
			infix_index++;
			continue;
		}

		// 알 수 없는 문자: 무시하고 다음 문자로
		infix_index++;
	}

	// 스택에 남은 연산자 모두 출력
	while (stack_isEmpty(&stack) == 0) {
		stack_pop(&stack, &stack_ch);
		if (stack_ch == '(' || stack_ch == ')') continue;
		if (pos < length) postfix_str[pos++] = stack_ch;
		if (pos < length) postfix_str[pos++] = ' ';
		if (pos < length) postfix_str[pos] = '\0';
	}

	// 끝의 여분 공백 제거
	if (pos > 0 && postfix_str[pos - 1] == ' ') {
		postfix_str[pos - 1] = '\0';
	}

	*result_str = postfix_str;
	return TRUE;
}

long evaluate_postfix(const char* postfix_str, int* success) {
	if (success) *success = FALSE;
	if (postfix_str == NULL) return 0;

	// 간단한 동적 스택 구현 (long)
	size_t cap = 16;
	size_t top = 0;
	long* stack = (long*)malloc(sizeof(long) * cap);
	if (stack == NULL) return 0;

	const char* p = postfix_str;
	char* endptr = NULL;

	while (*p != '\0') {
		// 공백 스킵
		while (*p == ' ') p++;
		if (*p == '\0') break;

		// 숫자(부호 포함)인지 확인
		if (isdigit((unsigned char)*p) || ((*p == '+' || *p == '-') && isdigit((unsigned char)*(p + 1)))) {
			errno = 0;
			long val = strtol(p, &endptr, 10);
			if (endptr == p) { // 파싱 실패
				free(stack);
				return 0;
			}
			// 스택 공간 확보
			if (top >= cap) {
				size_t newcap = cap * 2;
				long* tmp = (long*)realloc(stack, sizeof(long) * newcap);
				if (tmp == NULL) { free(stack); return 0; }
				stack = tmp;
				cap = newcap;
			}
			stack[top++] = val;
			p = endptr;
			continue;
		}

		// 연산자 처리: single-char 토큰 기대 (+ - * /)
		char op = *p;
		if (op == '+' || op == '-' || op == '*' || op == '/') {
			// 피연산자 2개 필요
			if (top < 2) { free(stack); if (success) *success = FALSE; return 0; }
			long b = stack[--top];
			long a = stack[--top];
			long r = 0;
			if (op == '+') r = a + b;
			else if (op == '-') r = a - b;
			else if (op == '*') r = a * b;
			else if (op == '/') {
				if (b == 0) { free(stack); if (success) *success = FALSE; return 0; }
				r = a / b;
			}
			// push result
			if (top >= cap) {
				size_t newcap = cap * 2;
				long* tmp = (long*)realloc(stack, sizeof(long) * newcap);
				if (tmp == NULL) { free(stack); return 0; }
				stack = tmp;
				cap = newcap;
			}
			stack[top++] = r;
			p++; // 다음 토큰으로
			continue;
		}

		// 알 수 없는 문자면 건너뜀
		p++;
	}

	// 최종 스택 검사
	if (top != 1) {
		free(stack);
		if (success) *success = FALSE;
		return 0;
	}

	long result = stack[0];
	free(stack);
	if (success) *success = TRUE;
	return result;
}

int main() {
	char* str;
	unsigned int length;
	char* postfix_str;
	input_str(&str, &length);
	infix_to_postfix(&str, length, &postfix_str);

	printf("%s\n", postfix_str);

	int eval_success = FALSE;
	long result = evaluate_postfix(postfix_str, &eval_success);
	if (eval_success) {
		printf("결과: %ld\n", result);
	} else {
		printf("후위 표기법 식 평가 실패\n");
	}
}
