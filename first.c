/*
이 코드는 회문을 판단하기 위한 코드입니다.
대소문자를 비교하는 옵션이 있습니다.

사용하는 변수 : 

input_char[](unsigned char) : 255자까지 입력받을 수 있음
MAX_LENGTH (define) : 256
UPPERTOLOWER (define) : 32 (A -> a 까지 값 차이 32)
TRUE (define) : 1
FALSE (define) : 0
CLEAR_VALUE (define) : 0
END_STR (define) : ;
result_val(int) : 회문인지 아닌지 true/false 값을 저장하는 변수
str_length(int) : 255개까지 입력받을 수 있는 배열에서 실제로 입력된 단어의 갯수

사용하는 함수 : 

1. void lets_input(void) : 문자 입력받는 함수
2. void upper_to_lower(void) : 입력받은 문자 배열에서 대소문자 구분을 없애주는 함수
3. void is_it_palindrome(void) : 입력받은 배열 앞, 뒤를 각각 비교하여 회문을 판단하는 함수
4. void * memset ( void * input_char, 0, size_t num ) : 
*/
#include<stdio.h>
#define MAX 256

int main(void)
{
    unsigned char inputchar[MAX];

    while((*inputchar = getchar() )!= EOF);
    printf("%c\n", inputchar);
    
    return 0;
}