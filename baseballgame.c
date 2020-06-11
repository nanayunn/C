#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<windows.h>

#define MIN_MATCH 4
#define MAX_MATCH 8
#define MIN_CHALLENGE 10
#define MAX_CHALLENGE 100
#define MIN_INPUT_VAL 0
#define MAX_INPUT_VAL 9
#define MAX_RANDOM_ATTEMPT 100
#define ARGC_NUM 3
#define SUCCESS 1
#define FAIL 0
#define ERROR -1
#define CLEAR_VAL 0


int challenge_num = 0;
int match_num = 0;

void global_val_init(void); /*글로벌 변수 초기화*/
void it_is_random(unsigned int * computer_arr); /*사용자가 입력한 숫자 갯수만큼 랜덤으로 값을 생성하여 배열에 넣는 함수(중복 없음)*/
void input_your_num(unsigned int * challenger_arr); /*사용자의 숫자 입력을 받는 함수*/
int match_it(unsigned int * computer_arr, unsigned int * challenger_arr); /*컴퓨터의 랜덤 숫자와 사용자 입력을 비교하는 함수*/
void clean_up(void); /*자원 free 함수*/
void not_enough_val(void); /* argc 값이 올바르지 않을 때 안내문을 출력하는 함수.*/
int check_valid(int **argv); /* argv의 값에 문자열이 들어갔는지 검사하는 함수 */


int main(int argc, int *argv[])
{
    /*사용할 변수 선언 및 초기화*/
    unsigned int computer_arr[MAX_MATCH];
    unsigned int challenger_arr[MAX_MATCH];
    unsigned int index = 0;
    unsigned int strike = 0;
    unsigned int ball = 0;
    int temp_val = 0;
    int TFval = 1;

    /*배열 초기화 진행*/
    memset(computer_arr, 0, sizeof(computer_arr));
    memset(challenger_arr, 0, sizeof(challenger_arr));

    /*argc 값을 기준으로 정해진 값이 아니면 안내 메세지를 출력 후 프로그램을 종료한다.*/
    if(argc != ARGC_NUM){
        goto exit; /*바로 main 함수 return 문으로!!!*/
    }
    
    /*예외 처리 후, 받아올 값들에 대해서도 예외처리를 진행한다.
    if 조건문에 걸리는 값이 들어오면 프로그램 종료.
    Exception 체크 대상 : challenge_num(도전 횟수), match_num(매칭 숫자 갯수)*/
    challenge_num = atoi(argv[1]);
    match_num = atoi(argv[2]);

    TFval = check_valid(*argv);
    if ( TFval == 0 ){
        goto exit;
    }
    
    if( challenge_num > MAX_CHALLENGE || challenge_num < MIN_CHALLENGE ){
        print("내가 입력한 도전 횟수 : %d\n", challenge_num);
        print("유효한 도전 횟수  :10 ~ 100\n");
        goto exit;
    }
    if( match_num > MAX_MATCH || match_num < MIN_MATCH ){
        print("내가 입력한 매칭 숫자 갯수 : %d\n", match_num);
        print("유효한 매칭 숫자 갯수  : 4 ~ 8\n");
        goto exit;
    }





exit:
not_enough_val();

global_val_init();

return 0;    
}

/*=================================================*/
void not_enough_val(void)
{
    printf("잘못된 입력입니다.\n");
    printf("프로그램을 종료합니다. 재실행해주세요.\n");
    printf("재 실행 시 실행하는 프로그램, 게임에 도전할 최대 횟수(10 ~ 100), 매칭을 원하는 숫자의 갯수(4 ~ 8)를 차례로 입력해주세요.\n");     

return;
}

/*=================================================*/
void global_val_init(void)
{
    challenge_num = 0;
    match_num = 0;
}

/*=================================================*/
int check_valid(int **argv)
{
    char temp_size = 0;
    char valid_argv = 0;
    char transit_challenge_size = 0;
    char transit_match_size = 0;
    int index = 0;
    int TFval = 1;
    transit_challenge_size = sizeof(challenge_num);
    transit_match_size = sizeof(match_num);

    for( index = 1; index < ARGC_NUM; index++ ){

        valid_argv = *argv[index];
        temp_size = sizeof(valid_argv);
        
        if(( index == 1 ) && ( transit_challenge_size != temp_size )){
        printf("도전 횟수에 문자열을 입력하셨군요?^^ 숫자만.. 입력해주세요...\n");
        TFval = 0;
        break;
        }
        
        if(( index == 2 ) && ( transit_match_size != temp_size )){
        printf("매칭 숫자 수에 문자열을 입력하셨군요?^^ 숫자만.. 입력해주세요...\n");
        TFval = 0;
        break;
        }

    }
    
return TFval;
}

/*=================================================*/
int start_game(void)
{
    printf("==============================================\n");
    printf("===========숫자 야구 게임을 시작합니다!==========\n");
    printf("매칭 숫자 랜덤 생성 중.......");


}

/*=================================================*/
void it_is_random(unsigned int * computer_arr)
{
    int random_num = 0;
    int try_num = 0;
    int index;
    if( computer_arr ==NULL ) {
        printf("컴퓨터의 숫자 리스트 초기화가 덜되었네요.. ");
        return -1; 
    }   
   
    for ( index = 0; index < match_num; index++ ){
        if( try_num == MAX_RANDOM_ATTEMPT ){
            printf("똑같은 숫자가 너무 많이 나와서 좀 쉴게요..");
            sleep(500);
            try_num = 0;
            index = 0;
        }
        
        random_num = (rand() % 10);
        computer_arr[index] = random_num;
        
        if(( index != 0 ) && ( computer_arr[index] == computer_arr[index - 1] )){
            index--;
            try_num++;
        }

    }

return;
}

/*=================================================*/
void input_your_num(unsigned int * challenger_arr)
{
    printf("이제 맞출 숫자를 입력해주세요!!중복되는 숫자는 넣어도 소용이 없답니다.\n");
    int index = 0;
    int input_num = 0;
    int input_loca = 0;

    if( challenger_arr ==NULL ) {
        printf("당신의 숫자 리스트가 초기화가 덜되었네요.. \n");
        return -1; 
    } 

    for ( index = 0; index <= match_num; index++ ){
        input_loca = index + 1;
        printf("%d 째 자리에 넣을 숫자를 입력해주세요.\n", input_loca);
        printf("입력해야하는 숫자의 총 개수 : %d\n",match_num);
        scanf("%d", &input_num);

        if( input_num >= MAX_INPUT_VAL || input_num <= MIN_INPUT_VAL ){
            printf("0 ~ 9까지의 숫자만 입력이 가능합니다. 다시 입력해주세요.\n");
            continue;
        }
        challenger_arr[index] = input_num;
    }
}

/*=================================================*/
int match_it(unsigned int * computer_arr, unsigned int * challenger_arr)
{
    int computer_index = 0;
    int challenger_index = 0;
    int temp_val = 0;
    int strike = 0;
    int ball = 0;

    if( computer_arr ==NULL ) {
        printf("매칭될 숫자가 제대로 입력이 안되었나봐요.. \n");
        return -1; 
    } 
    if( challenger_arr ==NULL ) {
        printf("당신의 숫자 리스트 값이 이상한 것 같아요... \n");
        return -1; 
    } 

    for(computer_index = 0; computer_index < match_num; computer_index++){
        for ( challenger_index = 0; challenger_index < match_num; challenger_index ++ ){
            
        }

    }
return strike, ball;
}