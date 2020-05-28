/* enum과 shift 연산을 활용하여 
    Category를 구현하였습니다.*/

# include<stdio.h>

enum flavors {
    chocolate = 1, 
    strawberry, 
    vanilla, 
    mango, 
    yoghurt, 
    cookie
    };

int add_myflavor( unsigned long my_flavor_list, int flavor_number );
int delete_myflavor( unsigned long my_flavor_list, int flavor_number );
int search_myflavor( unsigned long my_flavor_list, int flavor_number );

int main(void)
{
    /*변수의 초기화
    my_flavor_list : 64개의 칸을 가진 리스트
    pre_board : 2진수로 변형된 flavor 번호를 담을 리스트
    service_number : 사용자가 선택한 서비스 번호
    flavor_number : 사용자가 선택한 flavor 번호
    shift_value : flavor 번호를 2진수로 바꾸기 위해 해야하는 shift 연산값을 담을 integer
    */
    unsigned long my_flavor_list = 0;
    unsigned long pre_board = 0;
    int service_number = 0;
    int flavor_number = 0;
    int shift_value = 0;

    while(1){
        printf("이용하실 서비스 번호를 입력해주세요\n");
        printf("1. 내 맛에 추가하기 \n2. 내 맛에서 삭제하기 \n3. 내 맛에서 검색하기 \n4. 아이스크림 맛! 종료하기 \n");
       
        /*이용할 서비스 번호를 입력받는다.*/
        scanf("%d", &service_number);
        
        /*입력받은 서비스 번호를 넘겨받아 switch문을 실행하여 검사 후, 해당 서비스를 실행한다. */
        switch (service_number)
        {
        case 1:
            printf("추가하기를 선택하셨습니다.\n");
            printf("아이스크림 맛!\n 1. 초콜렛 2. 딸기 3. 바닐라 4. 망고 5. 요거트 6. 쿠키앤크림\n");
            printf("추가할 맛을 선택해주세요.\n");
            scanf("%d", &flavor_number);
            add_myflavor(my_flavor_list, flavor_number);
            break;

        case 2:
            printf("삭제하기를 선택하셨습니다.\n");
            printf("아이스크림 맛!\n 1. 초콜렛 2. 딸기 3. 바닐라 4. 망고 5. 요거트 6. 쿠키앤크림\n");
            printf("삭제할 맛을 선택해주세요.\n");
            scanf("%d", &flavor_number);
            delete_myflavor(my_flavor_list, flavor_number);
            break;

        case 3:
            printf("검색하기를 선택하셨습니다.\n");
            printf("아이스크림 맛!\n 1. 초콜렛 2. 딸기 3. 바닐라 4. 망고 5. 요거트 6. 쿠키앤크림\n");
            printf("검색할 맛을 선택해주세요.\n");
            scanf("%d", &flavor_number);
            search_myflavor(my_flavor_list, flavor_number);
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

/*========================================================================*/

/* 추가하기 함수 입니다.
값을 추가하는 my_flavor_list와 사용자가 선택한 flavor_number 값을 전달받습니다.
shift연산을 통해 */
int add_myflavor ( unsigned long my_flavor_list, int flavor_number )
{
    /*각 flavor가 의미하는 (상수-1)을 한 숫자에 따라 flavor가 
    shift연산을 하여 pre_board 1의 위치를 이동하게 되고, 
    각 flavor의 고유한 위치 값이 pre_board에 저장됩니다.
    */
    unsigned long added = 0;
    unsigned long pre_board = 1;
    int shift_val = flavor_number-1;

    pre_board = pre_board << shift_val;

    added = my_flavor_list | pre_board;

    /*추가 연산을 해주기 전, 이미 추가가 된 값인지 확인을 해줍니다.
    추가가 되어있지 않다면 연산을 진행하고,
    연산 후 제대로 추가가 되었는지 다시 한번 확인을 합니다.*/
    if ( my_flavor_list == added ){
        printf("이미 추가된 맛입니다.\n");
    }else{
        my_flavor_list = my_flavor_list | pre_board;

        if ( my_flavor_list == my_flavor_list & pre_board ){
            printf("맛이 새로 추가되었습니다!!!\n");
        }else{
            printf("추가가 안된 듯 합니다..\n");
        }
    }

    return 0;
}

/*========================================================================*/

/*삭제하기 함수 입니다.
사용자의 맛 리스트 my_flavor_list와 삭제를 원하는 맛의 flavor_number를 전달 인자로 받습니다.
*/
int delete_myflavor( unsigned long my_flavor_list , int flavor_number )
{
    /*각 flavor가 의미하는 (상수-1)을 한 숫자에 따라 flavor가 
    shift연산을 하여 pre_board 1의 위치를 이동하게 되고, 
    각 flavor의 고유한 위치 값이 pre_board에 저장됩니다.
    */
    unsigned long pre_board = 1;
    int shift_val = flavor_number-1;

    pre_board = pre_board << shift_val;
    /*추가가 된 값을 삭제하는 것이 맞는지 확인하여 준다.
    추가가 되어있다면, 
    pre_board의 값을 반전해준 뒤,
    & 연산자를 활용하여 pre_board의 값을 뺀 나머지 my_flavor_list로 업데이트 해준다.
    삭제 후 비교 연산을 통해 삭제가 제대로 되었는지 확인한다.*/
    if ( my_flavor_list == my_flavor_list & pre_board ){
            printf("추가되지 않은 맛은 삭제 못합니다!\n");

        }else{
            pre_board = ~pre_board;
            my_flavor_list = my_flavor_list & pre_board;
            if ( my_flavor_list == my_flavor_list & pre_board ){
            printf("삭제가 안됐나봐요..\n");
        }else{
            printf("삭제 완료입니다!\n");

        }
    return 0;
    }
}

/*========================================================================*/

/*검색하기 함수 입니다.
사용자의 맛 리스트 my_flavor_list와 검색을 원하는 맛의 flavor_number를 전달 인자로 받습니다.
*/
int search_myflavor( unsigned long my_flavor_list , int flavor_number )
{
    /*각 flavor가 의미하는 (상수-1)을 한 숫자에 따라 flavor가 
    shift연산을 하여 pre_board 1의 위치를 이동하게 되고, 
    각 flavor의 고유한 위치 값이 pre_board에 저장됩니다.
    */
    unsigned long pre_board = 1;
    int shift_val = flavor_number-1;

    pre_board = pre_board << shift_val;

    if(pre_board == pre_board & my_flavor_list){
        printf("내 맛에 맛이 있습니다!\n");
    }else{
        printf("내 맛에 맛이 존재하지 않아요..\n");
    }
    return 0;
}