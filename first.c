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
# include<stdio.h>

#define MAX_LENGTH 256
#define UPPER_TO_LOWER 32
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define CLEAR_VALUE 0
#define END_STR '#'

void * memset ( void * ptr, int value, size_t num );

int main(void)
{
    unsigned char input_str[MAX_LENGTH];
    char input_word = 0;
    int temp_val = 0;
    int result_val = 0;
    int str_length = 0;

}


/*====================================================================================*/
/*unsigned char 배열과 getchar()을 이용하여 회문 판단을 할 문자 배열을 입력받는 함수입니다. 
- 매개 변수 : input_char 배열의 포인터를 이용하여 첫째 자리 부터 배열을 입력 받습니다.
             input_char 배열의 값에 직접 접근하여 값을 변경하는 과정이 필요하므로 매개 변수를 포인터로 둡니다.
- 반환값 : 회문 판단 시 맨 첫번째 자리 배열과 맨 끝 자리 배열을 시작으로 앞뒤를 비교해 줄 수 있도록
배열을 입력 받은 후 입력한 문자가 들어갈 배열의 index를 나타내는 input_length를 반환합니다.*/
/*====================================================================================*/

int lets_input(unsigned char * input_char)
{
    /*사용하는 변수 선언 및 초기화 부분*/
    start: /*문자 입력이 너무 길어지면 문자를 맞는 범위안에 재입력을 요청, 첫 초기화 부분으로 돌아온다.*/
    char input_word = 0;
    int input_length = 0;

    memset(input_char, 0, MAX_LENGTH-1);

    /*배열 초기화 exception 처리*/
    if ( input_char == NULL){
        printf("배열 초기화가 제대로 이루어지지 않았습니다.\n");
        return -1;
    }

    printf("문자를 입력해주세요. 영어와 완료 문자만 입력이 가능합니다. 문자 입력을 완료하려면 %c를 입력해주세요.\n",END_STR);
    

    while(1){
        /*char 자료형의 input_word 변수에 getchar()을 통해 단어 하나를 입력 받는다.*/
        input_word = getchar();
        
        /*문자 입력이 너무 길어지면 문자를 맞는 범위안에 재입력을 요청, 
        버퍼를 지워준 뒤, 
        start 라벨(함수의 맨 처음)로 돌아간다.
        유효범위 exception*/
        if ( input_length >= MAX_LENGTH ) {
            printf("문자열 입력 범위를 초과하였습니다. 문자를 재입력 해주세요.\n");
            getchar_clear();
            goto start;    
            }   

        /*입력 단어가 문자열 끝처리 단어와 일치하면 입력 루프를 종료한다.*/
        if ( input_word = END_STR ) {
            printf("문자 입력을 완료합니다.\n");
            break;
        }

        /*정해진 입력 문자 이외의 문자를 입력했을 시 발생할 수 있는 exception을 잡기 위한 if 문*/
        if ( !((input_word >='A' && input_word =< 'Z') | (input_word >= 'a' && input_word =< 'z')) ) {
            printf("영문 입력만 해주세요ㅠㅠ 다른 문자는 입력이 어렵습니다.\n");
            continue;
        }

        /*input_char 배열에 순서대로 입력받은 단어를 넣어주기 위한 부분. 
        각 배열의 칸에 입력을 할 수 있도록 input_length를 기준으로, 
        while 루프가 돌아 getchar()이 수행될 때마다 1 값씩 증가시켜준다.*/
        input_char[input_length] = input_word;
        input_length = input_length + 1;
    }

    /*함수 종료부. 
    getchar_clear()로 버퍼를 다시 지워주고, */
    getchar_clear();

    /*반환값 리턴*/
    return input_length;
   
}
