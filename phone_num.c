#include<stdio.h>
#include<string.h>

#define MAX_FILE_INPUT 1024
#define MAX_PATH_INPUT 256
#define MIN_INPUT 0

#define MAX_USER_NUMBER 10
#define MAX_USER_INPUT 32
#define MAX_ID_SIZE 8
#define MAX_NAME_SIZE 8
#define MAX_PHONE_NUM 16

#define TRUE 1
#define FALSE 0

#define SUCCESS 0
#define FAIL 1
#define ERROR -1

#define APPEND_PHONE_NUM 1
#define DELETE_PHONE_NUM 2
#define SEARCH_PHONE_NUM 3
#define SAVE_PHONE_NUMS_AS_FILE 4

#define OPNE_EXISTING_FILE 1
#define CREATE_NEW_FILE 2

/*/수도 코드

* 전역변수
struct new new;
struct file file;
struct user * user[MAX_USER_NUMBER];

1. 메인
    - 파일 생성할 것인지 읽을 것인지 선택(1. 불러오기, 2. 생성)
        - 1 선택 시 read_file()
        - 2 선택 시 create_file()
        - 각각 함수를 통해 file 구조체에 file 정보를 담는다.
    - 전화번호부 업데이트 메뉴 (1. 추가하기 2. 삭제하기 3. 검색하기 4. 종료하기)
        - 한번에 하나의 기능만 실행할 수 있으며, 하나의 기능 실행 후 종료됨.
        - 1 선택시 add_phone_num()
        - 2 선택시 del_phone_num()
            - 이전에 user_choice때 create_file()을 선택한 경우 삭제할 내용이 없으므로 안내 문구 출력 후 프로그램 자동 종료.
        - 3 선택시 search_phone_num()
            - 이전에 user_choice때 create_file()을 선택한 경우 검색할 내용이 없으므로 - 이전에 user_choice때 create_file()을 선택한 경우 삭제할 내용이 없으므로 프로그램 자동 종료. 프로그램 자동 종료.
        - 4 선택시 프로그램 종료
return 0;

2. read_file()
- 전역변수 struct file *file을 매개변수로 받는다.

    - 파일 위치를 입력받는다
    - file_path에 저장
    - stat()을 이용하여 파일 사이즈를 얻는다.
    - MAX_FILE_INPUT만큼 file 구조체에 malloc()
    - open()으로 파일을 연다. (반환값 -1 예외 처리) / fd = open( user_input, mode)
    - 연 파일을 읽는다. result = read( fd, file->*file_pointer, file->*file_size ) (0보다 작은 수 : 에러 반환값)
    - 파일을 닫아준다. 

3. create_file()
- 전역변수 struct file *file을 매개변수로 받는다.

    - 파일의 이름을 입력받는다.
    - file_path에 저장
    - fd = creat(user_input, 0644) , fd가 음수면 예외처리
    - MAX_FILE_INPUT만큼 file 구조체에 malloc()
    - 만든 파일을 읽는다. result = read( fd, file->*file_pointer, file->*file_size ) (0보다 작은 수 : 에러 반환값, 0이 아니면 만든 파일에 쓰레기 값이 있는 것이므로 에러 반환값)
    - 파일을 닫아준다.

4. parse_user_info()
- 전역변수 struct file *file과 *user[] 구조체 배열을 매개변수로 받는다.

    - 파일 구조체의 값을 memchr()을 이용하여 ':'와 'SP'를 기준으로 ID, NAME, PHONE_NUM의 값을 배열에 저장한다.
    - if  (CRLF를 만나면 index ++, continue로 다음 인덱스로 넘어간다.)
    -   if CRLF 다음 포인터가 가리키는 값이 CRLF이면 (index ++ 후, break문으로 for 문 탈출한다.)
    - 탈출한 index 값을 반환한다.

5. check_id_valid()
- 전역변수 *user[] 구조체 배열과 user_id와 index를 매개변수로 받는다.

    - for ( int check_index = 0, check_index < index + 1, check_index ++)
        - user[check_index]-> user_id 와 비교, 
        - 맞는 값이 있으면 false(1),
        - 일치하는 값이 없으면 true(0)를 반환한다.

6. add_phone_num()
- 전역변수 struct file *file과 index를 매개변수로 받는다.(파일을 새로 생성한 경우 index = 0, 검사한 경우 index 값에 따라 다름)

    - for ( int add_index = index, add_index < 10, add_index ++)
        - user[index] 에 (struct user)만큼 malloc()
        
        - user ID를 입력받는다.
        - 8자리 length 체크
        - check_id_valid()
        - memcpy( target, source, sizeof(source));
        
        - user_name을 입력받는다.
        - max size 체크
        - memcpy( target, source, sizeof(source));

        - user_phone_num을 입력받는다. 
        - memchr(phone_num_pointer, '-', buffer)
        - '-'가 하나 있는 경우와 없는 경우에 대한 EXCEPTION 처리
        - memcpy( target, source, sizeof(source));

        - 그만 입력을 원하는 경우 'q'를 입력하도록 함, 
        - 'q'가 입력되면 해당 index 값의 내용 입력된 부분은 모두 초기화
        - 늘어난 add_index 값을 반환한다.
    - 저장 여부 물어본 후, 
    - fclose()

7. del_phone_num()
- 전역변수 struct file *file과 index와 *user[] 구조체 배열을 매개변수로 받는다.

    - 파일을 연다.(fd  예외 처리)
    - index 값만큼 user 배열을 printf,
    - 삭제할 index 번호를 입력받는다.
    - 입력받은 index 번호부터, 
    - user[index]-> user_ID = user[index+1]-> user_ID의 방식으로 자료들을 앞으로 한칸씩 당긴다.
    - 마지막 index 값은 0으로 초기화한다.
    - index-1만큼 다시 printf, 삭제되었습니다 문구 출력,
    - 입력받은 index부터의 user 배열을 write으로 파일에 덮어쓰기 한다.
    - 저장 여부 물어본 후 
    - fclose()

8. search_phone_num()
- 전역변수 struct file *file과 index와 *user[] 구조체 배열을 매개변수로 받는다.

    - 검색할 사항을 사용자로부터 입력받는다.
    - 검색받은 모든 사항을 기준으로 memchr을 시도한다. 
    - memchr 포인터를 search_word_start로 저장한다.
    - SP를 기준으로 memchr 다시 시도
    - 반환 포인터 -1 지점의 포인터를 search_word_end로 저장한다. 
    - start부터 end 포인터까지의 length를 구한 후, memcpy로 비교 함수로 저장한다.
    - user 구조체 배열을 index 값 안에서 memcpy로 저장한 배열과 비교하여 일치하는 값의 index를 찾고, 
    - 해당 index의 내용을 출력한다. 

9. free_all_variables()
- malloc으로 할당된 모든 변수의 메모리를 free 시킨다.

10. init()
- 전역 변수 초기화

=====================================================
* 요구 사항
    - 전화번호부 파일의 생성, 존재하는 파일은 로드
    - 전화번호 추가
        - ID(최대 8자리, 중복 불가)
        - 이름
        - 전화번호
    - 전화번호 삭제
    - 전화번호 검색
    - 전화번호부 파일로 저장
=======================================================

* 구조체 

struct new{
    char * new_fill_buff;

}

struct file{
    char * file_pointer;
    char * file_path;
    int file_size;
};

struct user{
    char user_ID[MAX_ID_SIZE];
    char user_name[MAX_NAME_SIZE];
    char phone_number[MAX_PHONE_NUM];
};

int main(void)
{
    int menu_num = 0;
    int user_choice = 0;

    struct file file;
    struct user user;


    printf("전화번호부 프로그램입니다.");
    printf("메뉴를 선택해주세요.");

file_menu_choice:
    printf("1. 파일 불러오기\n 2. 파일 새로 만들기\n");
    scanf("%d", &user_choice);
    get_char_clear();
    if ( user_choice < 0 || user_choice > 3 ){
        printf("메뉴를 잘못 선택하셨습니다.\n 다시 선택해주세요.\n");
        goto file_menu_choice;
    }

    if ( user_choice == 1 ){
        printf("이전 파일을 불러옵니다.\n");


    }else if ( user_choice == 2 ){
        printf("새로운 전화번호부 파일을 생성합니다.\n");

    }



}


1. read_file

int get_file_size(char *user_input)
{
	
	struct stat stat_stat;
	int result = 0;

	memset(stat_stat, 0, sizeof(stat_stat));

	result = stat(file_path, &stat_stat);

	if( result != 0 ){
        printf("get_file_size : 파일 정보를 읽어오는 것에 실패하였습니다....");
		return -1;
	}
return stat_stat.st_size;
}

int read_file(struct file * file)
{   
    if ( file == NULL ){
        printf(" 구조체 선언에 문제가 있는 것 같습니다.");
        return -1;
    }

    file->*file_size = 0;
    file->*file_path = NULL;
    file->*file_pointer = NULL;
    int fd = 0;

    char * user_input[MAX_INPUT];

    memset(user_input, 0, MAX_INPUT);


    printf("읽을 파일의 경로를 입력해주세요.");
    scanf("%s", &user_input);
    if ( strlen(user_input) <= 0 ){
        printf("말이 되는 파일 이름을 입력하세요....");
        return -1;
    }

    fd = open( user_input, O_RDWR | O_APPEND );
    if ( fd == -1){
        print("파일 오픈 오류입니다. 프로그램을 종료합니다.");
        return -1;
    }

    file->* file_size
    

    

}



/*/