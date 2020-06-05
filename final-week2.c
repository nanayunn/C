/*
문자열을 getchar()을 이용하여 배열로 받은 뒤, 입력된 문자열의 회문을 판단하는 코드입니다.
대소문자를 비교하는 옵션이 있습니다.

사용하는 변수 : 

input_char[](unsigned char) : 255자까지 입력받을 수 있음
MAX_LENGTH (define) : 256
UPPERTOLOWER (define) : 32 (A -> a 까지 값 차이 32)
TRUE (define) : 1
FALSE (define) : 0
CLEAR_VALUE (define) : 0
END_STR (define) : '#'
input_word(char) : getchar()을 통해 받아온 단어 1개를 담을 char 형 변수
check_num(int) : 회문 판단을 위해 앞뒤 글자를 비교해줄 때 필요한 판단 횟수를 담고있는 int형 변수
temp_val(int) : getchar_clear() 함수를 쓸 때, 함수 내에서 일시적으로 getchar()값을 담고 있을 변수
input_length(int) : 문자를 입력받은 횟수를 카운트한 값을 받아 담는 변수. index 값을 쉽게 얻기 위해 설정.
idx(int) : index의 약자로, for문을 작동하도록 하기 위해서 필요한 변수.
menu_val(int) : 사용자가 선택한 서비스의 번호를 받는 변수.

사용하는 함수 : 

1. void menu_menu(void) : 사용자가 선택하는 메뉴 번호에 따라 함수를 호출하는 함수입니다.
2. void getchar_clear(void) : scanf 및 입력함수 사용 후 입력버퍼에 남는 '\n' 데이터를 비워주기 위한 함수입니다. 
3. int lets_input(unsigned char * input_char) : 문자 입력받는 함수, 입력받은 길이를 반환합니다.
4. void upper_to_lower(unsigned char * input_char, int input_length) : 입력받은 문자 배열에서 대소문자 구분을 없애주는 함수
5. void is_it_palindrome(unsigned char * input_char, int input_length) : 입력받은 배열 앞, 뒤를 각각 비교하여 회문을 판단하는 함수
<string.h> 헤더파일 참조 함수 : void * memset ( void * input_char, 0, size_t num ) 배열의 초기화를 위한 함수입니다.
*/
# include<stdio.h>
# include<string.h> 

#define MAX_LENGTH 256
#define UPPER_TO_LOWER 32
#define TRUE 1
#define FALSE 0
#define ERROR -1
#define CLEAR_VALUE 0
#define END_STR '#'

void menu_menu(void);
void getchar_clear(void);
int lets_input(unsigned char * input_char);
void upper_to_lower(unsigned char * input_char, int input_length);
void is_it_palindrome(unsigned char * input_char, int input_length);

int main(void)
{
	menu_menu();

	return 0;
}

void menu_menu(void)
{
    /*사용하는 변수 선언 및 초기화 부분*/
	unsigned char input_char[MAX_LENGTH];
	char input_word = 0;
	int check_num = 0;
	int temp_val = 0;
	int input_length = 0;
	int idx = 0;
	int menu_val = 0;

    while(1){
        /*프로그램의 시작*/
        printf("================================\n");
        printf("회문 판단 프로그램입니다!\n");
        printf("======옵션을 선택해주세요!======\n");
        /*메뉴 번호 출력, scanf로 메뉴 번호 입력 받음*/
        printf("1. 대소문자 구분하기 2. 대소문자 구분 안하기 3. 종료하기\n");
        scanf_s(" %d", &menu_val);
        
        /*scanf 실행 후 입력 버퍼에 '\n' 엔터 데이터가 남아있으므로 
        다음 문자 배열 입력 실행 시 오류를 막기 위해 버퍼를 비워준다.*/
        getchar_clear();

        if (menu_val == 1) {
            printf("대소문자 구분 옵션을 선택하셨습니다. 대소문자를 구분하여 회문을 판단합니다.\n");
            /*대소문자를 구분하므로, 특별한 가공 과정 없이 문자 입력 함수와 회문 판단 함수를 작동*/
            input_length = lets_input(input_char);
            is_it_palindrome(input_char, input_length);

        }else if (menu_val == 2) {
            printf("대소문자 구분하지 않기를 선택하셨습니다. 모두 소문자로 변경 후 회문을 판단합니다.\n");
            /*대소문자를 구분하지 않으므로, 문자 입력 함수 후 소문자 획일화 함수 작동, 그 이후 회문 판단 함수를 작동*/
            input_length = lets_input(input_char);
            upper_to_lower(input_char, input_length);
            is_it_palindrome(input_char, input_length);

        }else if (menu_val == 3) {
            printf("종료하기를 선택하셨습니다. 프로그램을 종료합니다.");
            /*종료하기 이므로 입력 버퍼를 한 번 더 비워주고, return으로 바로 접근할 수 있도로 goto 설정*/
            getchar_clear();
            goto exit;
        }else{
            printf("잘못된 서비스 번호 입력입니다. 서비스 번호를 다시 확인해주세요.");
            /*이 외의 번호 입력 시 무시하고 다시 while 루프 진행*/
            continue;
        }
    }
exit:
	return;
}

/*====================================================================================*/
/*입력 버퍼의 초기화를 위한 함수
매개변수 : X
반환값 : X
임시의 int 값 temp_val을 초기화 한 후, 
getchar()로 버퍼를 비워주기 위해 하나씩 값을 읽어오는 값을 대입,
마지막으로 들어올 수 있는 데이터 '\n'값을 만날 때까지 모두 읽어온다.*/
/*====================================================================================*/

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
	/*문자 입력이 너무 길어지면 문자를 맞는 범위안에 재입력을 요청, 첫 초기화 부분으로 돌아온다.*/
	char input_word = 0;
	int input_length = 0;

	memset(input_char, 0, MAX_LENGTH);
	//getchar_clear();
	/*배열 초기화 exception 처리*/
	if (input_char == NULL) {
		printf("배열 초기화가 제대로 이루어지지 않았습니다.\n");
		return -1;
	}
    if ( input_length == NULL ) {
        printf("배열의 길이가 정의되지 않았습니다.\n");
        return -1;
    }
/*범위 초과 시 여기로 goto*/    
start:
	printf("문자를 입력해주세요. 영어와 완료 문자만 입력이 가능합니다. 문자 입력을 완료하려면 %c를 입력해주세요.\n", END_STR);


	while (1) {
		/*char 자료형의 input_word 변수에 getchar()을 통해 단어 하나를 입력 받는다.*/
		input_word = getchar();

		/*문자 입력이 너무 길어지면 문자를 맞는 범위안에 재입력을 요청,
		버퍼를 지워준 뒤,
		start 라벨(함수의 맨 처음)로 돌아간다.
		유효범위 exception*/
		if (input_length >= MAX_LENGTH) {
			printf("문자열 입력 범위를 초과하였습니다. 문자를 재입력 해주세요.\n");
			char input_word = 0;
			int input_length = 0;
			memset(input_char, 0, MAX_LENGTH);
			goto start;
		}

		/*입력 단어가 문자열 끝처리 단어와 일치하면 입력 루프를 종료한다.*/
		if (input_word == END_STR) {
			printf("문자 입력을 완료합니다.\n");
			break;
		}

		/*정해진 입력 문자 이외의 문자를 입력했을 시 발생할 수 있는 exception을 잡기 위한 if 문*/
		if (!((input_word >= 'A' && input_word <= 'Z') || (input_word >= 'a' && input_word <= 'z'))) {
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

/*====================================================================================*/
/*대소문자를 구분하지 않을 시, 배열 내의 모든 문자를 소문자로 재입력해주는 함수입니다.

- 매개 변수 : input_char 배열의 포인터를 이용하여 첫째 자리 부터 배열을 입력 받습니다.
input_char 배열의 값에 직접 접근하여 값을 변경하는 과정이 필요하므로 매개 변수를 포인터로 둡니다.
총 배열의 길이만큼 조회하여 알파벳을 비교하고 변경해주어야 하므로 input_length를 함께 매개변수로 받습니다.

- 반환값 : X*/
/*====================================================================================*/

void upper_to_lower(unsigned char * input_char, int input_length)
{
    /*사용하는 변수 선언 및 초기화 부분*/
	int idx = 0;

    /*배열 초기화 exception 처리*/
	if (input_char == NULL) {
		printf("배열 초기화가 제대로 이루어지지 않았습니다.\n");
		return -1;
	}
    if ( input_length == NULL ) {
        printf("배열의 길이가 정의되지 않았습니다.\n");
        return -1;
    }

    /*index의 최댓값은 배열의 총 길이보다 하나가 적으므로
    (idx < input_length)의 범위를 주고, 모든 index 값을 조회하여 
    대문자의 범위 안에 든다면 아스키 코드 소문자와 차이나는 값 32(UPPER_TO_LOWER)를 더하여준다.*/
	for (; idx < input_length; idx++) {

		if (input_char[idx] >= 'A'&& input_char[idx] <= 'Z') {
			input_char[idx] = input_char[idx] + UPPER_TO_LOWER;
		}
		else {
			/*소문자면 PASS!*/
			continue;
		}

	}
return;
}

/*====================================================================================*/
/*입력받은 배열을 바탕으로 회문을 판단하는 함수입니다.

- 매개 변수 : input_char 배열의 포인터를 이용하여 첫째 자리 부터 배열을 입력 받습니다.
input_char 배열의 값에 직접 접근하여 값을 변경하는 과정이 필요하므로 매개 변수를 포인터로 둡니다.
총 배열의 길이만큼 조회하여 알파벳을 비교하고 회문을 판단해주어야 하므로 input_length를 함께 매개변수로 받습니다.

- 반환값 : X*/
/*====================================================================================*/
void is_it_palindrome(unsigned char * input_char, int input_length)
{
    /*사용하는 변수 선언 및 초기화 부분*/
	int input_word = 0;
	int check_num = 0;
	int idx = 0;

    /*배열 초기화 exception 처리*/
	if (input_char == NULL) {
		printf("배열 초기화가 제대로 이루어지지 않았습니다.\n");
		return -1;
	}
    if ( input_length == NULL ) {
        printf("배열의 길이가 정의되지 않았습니다.\n");
        return -1;
    }

    
    /*배열의 길이가 1이라면 100% 회문이므로 바로 회문 판단을 한다.*/
	if (input_length == 1) {
		printf("회문입니다.");
	}

    /*input_length가 짝수라면 나누기 2를 한 횟수만큼 비교를 진행하고,
    input_length가 홀수라면 한가운데 문자를 제외한, 나머지 길이를 나누기 2한 횟수만큼 비교를 진행한다.*/
	check_num = (input_length/2);

    /*check_num은 배열의 총길이를 나눈 값이므로, 
    (idx<check_num)의 범위를 준다. 
    각 위치에 있는 배열의 값이 같지 않았을 때 
    for문을 빠져나가 return으로 바로 접근한다.*/
	for (; idx < check_num; idx++) {
		
		if (input_char[idx] != input_char[input_length - idx - 1]) {
			printf("이건..회문이 아닙니다.");
			goto exit;
		}
	}
	printf("이건.. 회문입니다!!");

exit:
	return;

}
