#include<stdio.h>
#include<string.h>
#include <stdlib.h>


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

#define SUCC_STRIKE 1
#define SUCC_BALL 0
#define NONE_MATCH -1

int challenge_num = 0;
int match_num = 0;

void global_val_init(void); /*글로벌 변수 초기화*/
void it_is_random(unsigned int * computer_arr); /*사용자가 입력한 숫자 갯수만큼 랜덤으로 값을 생성하여 배열에 넣는 함수(중복 없음)*/
void input_your_num(unsigned int * challenger_arr); /*사용자의 숫자 입력을 받는 함수*/
int compare_with_computer(unsigned int * computer_arr, int challenge_val, int index, int * strike, int * ball);
int match_it(unsigned int * computer_arr, unsigned int * challenger_arr, int * strike, int * ball); /*컴퓨터의 랜덤 숫자와 사용자 입력을 비교하는 함수*/
void clean_up(void); /*자원 free 함수*/
void getchar_clear(void);/*사용자가 값을 입력할 때 버퍼 오류가 나지 않도록 하는 함수*/
void not_enough_val(void); /* argc 값이 올바르지 않을 때 안내문을 출력하는 함수.*/
int check_valid(int **argv); /* argv의 값에 문자열이 들어갔는지 검사하는 함수 */


int main(int argc, int *argv[])
{
    /*argc 값을 기준으로 정해진 값이 아니면 안내 메세지를 출력 후 프로그램을 종료한다.*/
    if(argc != ARGC_NUM){
        not_enough_val();
        goto exit; /*바로 main 함수 return 문으로!!!*/
    }
    int TFval = 0;

    /*예외 처리 후, 받아올 값들에 대해서도 예외처리를 진행한다.
    if 조건문에 걸리는 값이 들어오면 프로그램 종료.
    Exception 체크 대상 : challenge_num(도전 횟수), match_num(매칭 숫자 갯수)*/
    challenge_num = atoi(argv[1]);
    match_num = atoi(argv[2]);

    /*argv 값이 모두 숫자가 들어왔는지 유효성 체크!
    TFval 값을 받아 체크하고, false를 받으면 종료시켜버린다.*/
    TFval = check_valid(*argv);
    if ( TFval == 0 ){
        not_enough_val();
        goto exit;
    }
    /*숫자 값임이 확인이 되면, 범위값을 체크한 뒤, 범위 안 값이 아니면 종료시켜버린다.*/
    if( challenge_num > MAX_CHALLENGE || challenge_num < MIN_CHALLENGE ){
        print("내가 입력한 도전 횟수 : %d\n", challenge_num);
        print("유효한 도전 횟수  :10 ~ 100\n");
        not_enough_val();
        goto exit;
    }
    if( match_num > MAX_MATCH || match_num < MIN_MATCH ){
        print("내가 입력한 매칭 숫자 갯수 : %d\n", match_num);
        print("유효한 매칭 숫자 갯수  : 4 ~ 8\n");
        not_enough_val();
        goto exit;
    }

    /*모든 유효성 검사가 끝났다면 야구게임 시작~~!!*/
    start_game();

exit:

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
void getchar_clear(void)
{
    int temp_val = 0;
    temp_val = getchar();
    while (1) {
        if (temp_val == '\n') {
            break;
        }
    }
return;
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
    /*사용할 변수 선언 및 초기화*/
    unsigned int computer_arr[MAX_MATCH];
    unsigned int challenger_arr[MAX_MATCH];
    int index = 0;
    int strike = 0;
    int ball = 0;
    int attempt = 0;

    /*배열 초기화 진행*/
    memset(computer_arr, 0, sizeof(computer_arr));
    memset(challenger_arr, 0, sizeof(challenger_arr));

    printf("==============================================\n");
    printf("===========숫자 야구 게임을 시작합니다!==========\n");
    printf("매칭 숫자 랜덤 생성 중.......");

    /*랜덤 숫자 생성 및 컴퓨터 매칭 숫자 선정*/
    it_is_random(computer_arr);

    while(1){
        /*사용자의 입력값을 받아 배열 생성*/
        input_your_num(challenger_arr);
        printf("내가 입력한 숫자 :");
        for( index = 0; index < match_num; index ++ ){
            printf(challenger_arr[index]);
        }  
        /*두 개의 배열을 이용해 매칭!*/
        match_it(computer_arr, challenger_arr, strike, ball);
        attempt ++;
        printf("스트라이크 : %d", strike);
        printf("볼 : %d", ball);
        printf("내가 도전한 횟수 : %d  /  내가 도전할 수 있는 횟수 :%d\n", attempt, challenge_num);

        if( attempt == challenge_num ){
            printf("아이쿠,, 도전 기회를 다 쓰셨어요ㅠㅠ 실패~~~~\n");
            printf("내가 도전한 횟수 : %d  /  내가 도전할 수 있는 횟수 :%d\n", attempt, challenge_num);
            printf("프로그램을 종료합니다. 새로운 게임을 원하시면 재시작해주세요.");
            break;
        }

        if( strike == match_num ){
            printf("와 다 맞추셨어요!!\n");
            printf("***********성공을 축하합니다 짝짝짝 *************\n");
            printf("내가 도전한 횟수 : %d  /  내가 도전할 수 있는 횟수 :%d\n", attempt, challenge_num);
            printf("프로그램을 종료합니다. 새로운 게임을 원하시면 재시작해주세요.");
            break;
        }

        printf("");
    }
return 0;
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
    printf("맞출 숫자를 입력해주세요!!중복되는 숫자는 넣어도 소용이 없답니다.\n");
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
        getchar_clear();

        if( input_num >= MAX_INPUT_VAL || input_num <= MIN_INPUT_VAL ){
            printf("0 ~ 9까지의 숫자만 입력이 가능합니다. 다시 입력해주세요.\n");
            continue;
        }
        challenger_arr[index] = input_num;
    }
}

/*=================================================*/
int match_it(unsigned int * computer_arr, unsigned int * challenger_arr, int * strike, int * ball)
{
    int computer_val = 0;
    int challenge_val = 0;
    int index = 0;
    int result = 0;

    if( computer_arr ==NULL ) {
        printf("매칭될 숫자가 제대로 입력이 안되었나봐요.. \n");
        return -1; 
    } 
    if( challenger_arr ==NULL ) {
        printf("당신의 숫자 리스트 값이 이상한 것 같아요... \n");
        return -1; 
    } 
    if( strike == NULL ){
        print("스트라이크 평가 값이 이상해요..");
    }
    if( ball == NULL ){
        print("볼 평가 값이 이상해요..\n");
    }

    for(index = 0; index < match_num; index++){
        challenge_val = challenger_arr[index];
        compare_with_computer(computer_arr, challenge_num, index, strike, ball);
    }
return 0;
}

int compare_with_computer(unsigned int * computer_arr, int challenge_val, int index, int * strike, int * ball)
{
    if( computer_arr ==NULL ) {
        printf("매칭될 숫자가 제대로 입력이 안되었나봐요.. \n");
        return -1; 
    } 
    if( challenge_val == NULL ){
        print("당신의 입력값이 제대로 전달되지 않았네요..\n");
    }
    if( strike == NULL ){
        print("스트라이크 평가 값이 이상해요..");
    }
    if( ball == NULL ){
        print("볼 평가 값이 이상해요..\n");
    }
    int computer_index = 0;
    int computer_val = 0;

    for( computer_index = 0; computer_index < match_num; computer_index++ ){
        computer_val = computer_arr[computer_index];
        if( computer_index == index && computer_val == challenge_val ){
            * strike++;
            return 1;
        }else if( computer_index != index && computer_val == challenge_val ){
            * ball++;
            return 0;
        }else{
            return -1;
        }
    }
return 0;
}