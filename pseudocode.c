/* enum과 비트 연산을 활용하여
카테고리 값을 설정한 뒤, 추가, 삭제, 검색 기능을 구현한 프로그램입니다.*/
#include<stdio.h>

/*전역 변수
카테고리 값 설정(초기화 값은 1)*/
enum flavor {
chocolate = 1, /* 1 */
strawberry,  /* 2 */
vanilla,    /* 3 */
mango,     /* 4 */
yogurt,   /* 5 */
cookie   /* 6 */
};

/*사용할 함수의 원형 선언 */
void add_myflavor(my_flavor_list);
void delete_myflavor(my_flavor_list);
int is_myflavor_exist(my_flavor_list, empty_list);
int select_flavor(void);

/* main함수가 작동하는 부분입니다.
기능 : 사용자가 각 서비스를 이용할 수 있는 함수
서비스 목차 :1. 추가하기 2. 삭제하기 3. 검색하기 4. 종료하기
변수 : 
1. my_flavor_list(unsigned long) : 카테고리 값을 추가하여 업데이트 가능한 64비트 변수
2. empty_list(unsigned long) : 각 카테고리 값을 비트 연산 할 수 있도록 2진수로 변환한 값을 담을 변수
3. service_number(int) : 사용자가 이용할 서비스에 해당하는 숫자를 담는 변수
4. flavor_number(int) : enum에 해당하는 각 요소에 붙는 숫자
5. shift_value(int) : flavor_number -1로, 쉬프트 연산을 얼마나 할지를 담기 위한 변수
6. true와 false(const int): true false 값을 명시
7. return_val(int) : boolean 반환값을 받아올 시, true false의 값을 다루기 편하도록 담기 위한 변수
*/
int main(void)
{ 
    /*변수 초기화*/
    unsigned long my_flavor_list = 0;
    unsigned long empty_list = 0;
    int service_number = 0;
    int flavor_number = 0;
    int shift_value = 0;
    const int true = 1;
    const int false = 0;
    int return_val = 0;

    /*종료하기 서비스로 빠져나오기 전까지 true(1) 값을 유지하며 무한루프*/
    while(true){
        printf("이용하실 서비스 번호를 입력해주세요\n");
        printf("1. 내 맛에 추가하기 \n2. 내 맛에서 삭제하기 \n3. 내 맛에서 검색하기 \n4. 프로그램 종료하기 \n");

        /*이용할 서비스 번호를 입력받는다.*/
        scanf("%d", &service_number);
        
        /*입력받은 서비스 번호를 넘겨받아 switch문을 실행하여 검사 후, 해당 서비스를 실행한다. 
        1번 선택 : 추가하기 서비스, add_myflavor(my_flavor_list)함수가 작동
        2번 선택 : 삭제하기 서비스, delete_myflavor(my_flavor_list)함수가 작동
        3번 선택 : 검색하기 서비스, is_myflavor_exist(my_flavor_list, empty_list)함수가 작동, 
                함수 반환 값을 return_val에 담아 유효성을 검사한 후 존재 유무를 확인하여 준다.
        4번 선택 : 종료하기 서비스, 반환값 0을 출력하여 while문을 종료해준다.
        이외의 값을 입력할 시 확인해달라는 문구를 출력하며 처음으로 돌아간다.*/
        switch (service_number)
        {
        case 1:
            printf("추가하기를 선택하셨습니다.\n");
            add_myflavor(my_flavor_list);
            break;

        case 2:
            printf("삭제하기를 선택하셨습니다.\n");
            delete_myflavor(my_flavor_list);
            break;

        case 3:
            printf("검색하기를 선택하셨습니다.\n");
            is_myflavor_exist(my_flavor_list, empty_list);
            return_val = is_myflavor_exist(my_flavor_list, empty_list);
            if( return_val == 1){
                printf("내 맛 리스트에 존재합니다!");
            }else if( return_val == 0 ){
                printf("흠.. 맛을 찾을 수가 없네요.");
            }else{
                printf("뜻밖의 오류입니다.");
            }
            break;

        case 4:
            printf("종료하기를 선택하셨습니다.\n 서비스를 종료합니다.\n");
            return 0;

        default:
            printf("번호를 잘못 입력하셨습니다.\n");
            break;
        }
    }
    return 0;   
}

/*동작 : 선택한 맛의 int 값을 입력받아 반환하는 함수
변수 : int flavor_number
반환 값 : int flavor number*/
int select_flavor(void)
{
    int flavor_number = 0;
    printf("아이스크림 맛!\n 1. 초콜렛 2. 딸기 3. 바닐라 4. 망고 5. 요거트 6. 쿠키앤크림\n");
    printf("맛을 선택해주세요.\n");
    scanf("%d", &flavor_number);
    if( flavor_number > 7 && flavor_number < 1 ){
        printf("선택한 번호를 다시 확인해주세요.");
    }

    return flavor_number;
}

/*동작 : 선택한 값이 값을 추가하는 64비트 변수에 존재하는지 확인하는 함수
변수 : unsigned long my_flavor_list, unsigned long empty_list 
or 연산자를 활용하여 기존의 my_flavor_list와 or 연산을 실행한 my_flavor_list를 비교연산한다.
같으면 true(1), 다르면 false(0) 값을 반환값으로 출력한다. */
int is_myflavor_exist(my_flavor_list, empty_list)
{
    if( my_flavor_list == my_flavor_list | empty_list ){
        return 1;
    }else if( my_flavor_list != my_flavor_list | empty_list ){
        return 0;
    }else{
        printf("오류가 발생했습니다.");
        break;
    }
}

/*동작 : 64비트 변수에 선택한 값을 추가하는 함수.
변수 : unsigned long my_flavor_list, unsigned long empty_list
int flavor_number, int shift_value, int return_val
함수 활용 : void select_flavor(), int is_myflavor_exist(my_flavor_list, empty_list) 
    1. flavor_number 값 획득(select_flavor() 이용)
	2. flavor_number-1의 값으로 shift value 설정,
	3. empty_list를 1로 초기화
	4. empty_list의 1값을 shift 연산 실행
	6. 변환된 flavor_number가 my_flavor_list에 존재하는지 존재유무 확인, false반환시	(is_myflavor_exist())
	7. 연산 실행
	8. my_flavor_list = my_flavor_list | empty_list	(or 연산자 활용)
	10.추가 되었음을 알리고 종료*/

void add_myflavor(my_flavor_list)
{
    select_flavor();
    int flavor_number = select_flavor();
    int shift_value = flavor_number -1;
    unsigned long empty_list = 1 ;
    unsigned long empty_list = empty_list << shift_value

    is_myflavor_exist(my_flavor_list, empty_list);
    int return_val = is_myflavor_exist(my_flavor_list, empty_list);

    if( return_val == 1 ){
        printf("이미 추가되어있는 맛입니다.");
    }else if( return_val == 0 ){
        printf("없던 맛임이 확인되었습니다.");
        myflavor_list == my_flavor_list | empty_list;
        printf("맛이 무사히 추가되었습니다.");
    }else{
        printf("오류가 발생했습니다.");
        break;

    }
}



/*동작 : 64비트 변수에 선택한 값을 추가하는 함수.
변수 : unsigned long my_flavor_list, unsigned long empty_list
int flavor_number, int shift_value, int return_val
함수 활용 : void select_flavor(), int is_myflavor_exist(my_flavor_list, empty_list) 
    1. flavor_number 값 획득(select_flavor() 이용)
	2. flavor_number-1의 값으로 shift value 설정,
	3. empty_list를 1로 초기화
	4. empty_list의 1값을 shift 연산 실행
	6. 변환된 flavor_number가 my_flavor_list에 존재하는지 존재유무 확인, true반환시	(is_myflavor_exist())
	7. 연산 실행
    8. empty_list의 값 반전(~)
	9. 반전된 empty_list값과 my_flavor_list값 (&) 연산자 실행
	10. 삭제 되었음을 알리고 종료
*/    
void delete_myflavor(my_flavor_list)
{
    select_flavor();
    int flavor_number = select_flavor();
    int shift_value = flavor_number -1;
    unsigned long empty_list = 1 ;
    unsigned long empty_list = empty_list << shift_value

    is_myflavor_exist(my_flavor_list, empty_list);
    int return_val = is_myflavor_exist(my_flavor_list, empty_list);

    if( return_val == 1 ){
        printf("맛이 확인되었습니다. 삭제를 진행합니다.");
        empty_list = ~empty_list;
        my_flavor_list = my_flavor_list & empty_list;
        printf("맛이 무사히 삭제되었습니다.");
    }else if( return_val == 0 ){
        printf("원래 없던 맛이네요!");
    }else{
        printf("오류가 발생했습니다.");
        break;
    }
}