C 언어의 깊은 이해



#### 21장. 문자와 문자열 처리 함수

##### 21-1. 스트림과 데이터의 전송

* 입력이란?
  * 실행중인 프로그램이 데이터를 받아들이는 것. (키보드)
* 출력이란?
  * 실행중인 프로그램이 데이터를 보내는 것(모니터)



* 스트림이란?
  * 프로그램 상에서 모니터로 데이터를 전송해주기 위해 둘을 연결해주는 다리. 
  * stream : 연속된 데이터의 열
  * 입, 출력 순서에 의해서 순차적으로 처리가 되는 데이터
  * !stream.png!
* 파일 입, 출력 | 콘솔(키보드&모니터) 입, 출력
  * 표준 스트림(standard stream)



##### 21-2. 문자 단위 입, 출력 함수

* 1) 문자 출력 함수

  * <pre>
    /*문자를 출력할 때 사용하는 함수 두 개 구분하기*/

    /*콘솔에 문자를 출력하는 함수*/
    int putchar(int 변수);

    /*콘솔 + 파일에 문자를 출력(저장)하는 함수
    FILE * stream : 문자를 출력할 스트림 지정*/
    int fputc(int 변수, FILE* stream);
    </pre>

  * 2) 문자 입력 함수

  * <pre>
    /*문자를 입력받을 때 사용하는 함수*/
    /*표준 입력 스트림(stdin)-키보드-으로부터 한 문자를 입력받아서 반환해주는 함수*/
    int getchar(void);

    /*문자를 입력받을 스트림을 지정할 수 있는 함수
    (파일 데이터 읽기 가능!!)*/

    int fgetc(FILE* stream);

    </pre>

  * 3) EOF 란(End Of File)

    * 실제 지닌 값 : -1
    * 오류, 혹은 함수가 역할을 다 하였을 때 호출

  * 4) 문자 단위 입, 출력 함수가 존재하는 이유?

    * 필요에 따른 메모리 공간 및 속도 조절을 위해서..?


##### 21-3. 문자열 단위 입, 출력 함수

* 1) 문자열 출력 함수

  * <pre>
    /*하나의 문자열 출력할 때 쓰는 함수*/

    /*자동 줄바꿈 O*/
    int puts(const char* s); 

    /*줄바꿈 없다!*/ 
    int fputs(const char* S , FILE* stream);
    </pre>

    

* 2) 문자열 입력 함수

  * <pre>
    /*하나의 문자열을 입력받을 때 쓰는 함수*/
    /*문자열을 저장하기 위한 배열을 선언,*

    시작 주소를 인자로 전달하여 gets 함수 실행 시 

    stdin으로 데이터를 입력받음

    단점 : 오버플로우 발생의 경우/
    char* gets(char* s);

    /*gets 함수와 다르게 최대 문자열의 길이를 함수에 매개변수로 함께 전달해주어 그 이상의 문자를 읽어들이지 않는다.*

    입력되는 문자열의 실제 길이 : length - 1의 값!

    이유 : 문자열의 끝엔 '\0' 널값으로 끝처리를 해줘야하기 때문/
    char* fgets(char* s , int length , FILE* stream) ; 

    </pre>

##### 21-4. 표준 입, 출력과 버퍼

* 1)  표준 입, 출력 기반의 버퍼

  * 버퍼란? : 여분의 임시 메모리 공간
  * !buffer.png!
  * '엔터'키를 누르는 시점이 입력 버퍼에 데이터가 들어가는 시점

* 2) 버퍼링을 하는 이유?

  * 한번에 작업을 처리하여 작업의 최적화를 위해서.

* 3) fflush 함수(버퍼를 비우는 작업)

  * <pre>
    /*버퍼를 비우는 작업을 하는 함수*/
        int fflush(FILE * stream);
    </pre>

  * 매개 변수가 입력 스트림:

    * 입력 버퍼의 데이터를 지운다.
    * 원하는 값 이상의 데이터가 입력되었을 때, 다음 입력 스트림에 영향을 주지 않도록 버퍼를 비워줄 때 이용

  * 매개 변수가 출력 스트림 :

    * 출력 버퍼 내의 데이터가 즉시 출력

##### 21-5. 문자열 조작 함수

* 1) 문자열의 길이를 반환하는 strlen 함수

  * <pre>
    #include<string.h>

    /*인자로 전달된 문자열의 길이 반환해주는 함수*/
    size_t strlen(const char* s)
    </pre>

  * 문자열 마지막의 NULL은 길이에 포함되지 않는다.

  * 근데 입력할 때 쳐야하는 엔터키 '\n' 은 포함됨..

  * size_t = unsigned int..? (부호 없는 정수형)

* 2) 문자열을 복사하는 strcpy와 strncpy 함수

  * strcpy 함수

  * <pre>
    /*문자열을 복사하는 함수*/

    char* strcpy(char* dest, const char* src);     
    </pre>

  * dest로 전달된 배열에 src로 전달된 문자열 복사

  * 컴파일러에 따라 오버플로우가 체크될 수도, 안될수도 있는 현상을 가진 함수..

  * strncpy 함수

  * <pre>
    /*할당해놓은 배열의 크기만큼만 문자열을 복사하는 함수*/
    char * strncpy(char* dest, const char* src , size_t n);  
    </pre>

  * 근데 이 함수는 '\n', 스트링 NULL 처리가 되지 않으므로 맨날 체크해줘야함

* 문자열을 추가하는 strcat, strncat

  * strcat 함수

  * 기존의 문자열 뒤에 다른 문자열을 추가하는 함수

  * <pre>
    char* strcat(char* dest, const char* src);

    </pre>

  * src로 전달된 문자열을 dest로 전달된 문자열의 뒤에 추가

  * 역시나 오버플로우의 문제 발생 가능성

  * strncat 함수

  * 복사하고자 하는 문자열의 최대 길이을 인자로 전달하는 기능 추가

  * <pre>
    char* strncat(char* dest, const char* src , size t n);
    </pre>

* 문자열을 비교하는 strcmp, strncmp 함수

  * 문자열의 내용을 비교하는 함수!!!

  * strcmp 함수

  * 두 개의 문자열 포인터를 인자로 받아서 포인터가 가리키는 문자열의 내용 비교

  * <pre>
    int strcmp(const char* str1 , const char* str2);  
    </pre>

  * 반환값 : !strcmp.png!

  * strncmp 함수

  * str1 이 가리키는 문자열과, str2가 가리키는 문자열을 처음부터 num개까지 비교하는 함수

  * <pre>
    int strncmp(const char* str1 , const char* str2 , size_t num);
    </pre>

* 문자 및 문자열에 관련된 그 밖의 함수들

  * 문자열을 숫자로 변환하는 함수들

  * <pre>
    #include <stdlib.h>

    /*문자열을 int 형 데이터로 변환*/
    int atoi(char *ptr);

    /*문자열을 long 형 데이터 로 변환*/
    long atol(char *ptr);

    /*문자열을 double 형 데이터로 변환 */
    double atof(char *str);   
    </pre>

  * 대소문자의 변환을 처리하는 함수들

  * <pre>
    #include <ctypes.h>
    /*소문자를 대문자로*/
    int toupper(int val);

    /*대문자를 소문자로*/
    int tolower (int val); 
    </pre>

#### 22장. 구조체와 사용자 정의 자료형1

##### 22-1. 구조체란 무엇인가?

* 구조체 : 하나 이상의 변수를 그룹지어서 새로운 자료형을 정의하는 것

* 1)구조체 정의

* ```c
  struct point /*point라는 이름의 구조체 선언*/
  {
  	int x;  /*구조체 멤버들*/
  	int y;
  }
  ```

* 사용자 정의 자료형  : 기본 자료형 변수를 묶어서 새로운 자료형을 만드는 것.

* 위의 예시 : point라는 이름의 자료형

* 2) 구조체 변수의 선언 + 구조체 변수로의 접근

* ```c
  #include<stdio.h>
  
  /*(x,y)의 좌표값을 나타내기 위한 구조체 point*/
  struct point
  {
      int x;
      int y;
  }
  
  /*main함수에서 point 구조체 변수를 선언한 후, 구조체 내의 x와 y의 좌표값을 대입하여 준다.*/
  int main(void)
  {
      /*구조체 변수 선언*/
      struct point p1;
      
      /*구조체 변수 내의 변수에 접근, 값 대입!!*/
      p1.x = 10;
      p1.y = 20;
      
  return 0;    
  }
  ```

* 구조체 변수의 초기화

* !struct.png!

* !struct2.png!

##### 22-2. 구조체와 배열 그리고 포인터

* 구조체 배열의 선언 및 접근

* ```c
  #include<stdio.h>
  /*person_info라는 구조체를 만들어 회원정보를 관리하기 위한 구조체 배열을 선언하는 코드입니다.*/
  
  /*이름과 전화번호 최대 길이를 정의합니다.*/
  #define MAX_NAME 20
  #definde MAX_PHONE_NUM 20
  
  /*구조체 선언, 이름, 전화번호, 나이를 변수로 갖는다.*/
  struct person_info
  {
      char name[MAX_NAME];
      char phone[MAX_PHONE_NUM];
      int age;
      
  }
  
  int main(void)
  {
      /*pinfo_array는 10개의 구조체를 담을 수 있는 배열*/
      struct person_info pinfo_array[10];
      
  return 0;    
  }
  ```

* !parray.png!



* 구조체 변수와 포인터
* !pman.png!
* !pman2.png!
* 포인터를 이용하여 구조체 내의 변수에 접근하는 방법
* 1. (*pMan).name
  2. pMan -> name



* 포인터 변수와 구조체 멤버

* ```c
  #include<stdio.h>
  /*구조체 내에 다른 구조체의 포인터를 변수로 받는 것을 보여주기 위한 코드입니다.*/
  
  #define MAX_ADDR 30
  #define MAX_TEL 20
  #define MAX_NAME 20
  #define MAX_PID 20
  
  struct person_info
  {
      char addr[MAX_ADDR];
      char tel[MAX_TEL];
  }
  
  struct person
  {
      char name[MAX_NAME];
      char PID[MAX_PID];
      struct person_info* info;
  }
  
  int main(void)
  {
      struct person_info info = {"Seoul", "1234-1234"};
      struct person me = {"NY KIM", "950808-0000000"};
      me.info = &info;
      
  return 0;
  }
  ```

* !me.png!



* 구조체 변수의 주소 값과 구조체 변수의 첫번째 멤버의 주소값은 같다!!!!!!
* !sameaddr.png!

#### 23장. 구조체와 사용자 정의 자료형2



#### 24장. 파일 입. 출력



#### 25장. 메모리 관리와 동적 할당



#### 26장. 매크로와 전처리기(preprocessor)



#### 27장. 모듈화 프로그래밍

