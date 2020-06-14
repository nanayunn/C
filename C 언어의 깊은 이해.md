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
  #define MAX_PHONE_NUM 20
  
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

##### 23-1. 구조체 변수의 전달과 리턴

* 함수의 인자로 전달되는 구조체 변수

  * Call-by-reference
  * Call-by-Value

* 구조체 변수의 연산

  * 구조체 변수는 대입 연산만 가능하다!!!
  * 사칙연산, 비교연산은 불가능하다!!
  * sizeof 연산, 혹은 포인터와 관련된 연산(*, &, ->)는 가능

* 구조체 변수의 리턴

* 구조체의 변수도 함수 내의 리턴값으로 이용될 수 있다.

* !return.png!

  

##### 23-2. 구조체의 유용함에 대한 두 가지 이야기

* 관련있는 데이터를 하나의 자료형으로 묶을 경우, 관리하기가 편리해진다.
* 함수 값의 리턴을 구조체로 선언하여 둘 이상의 값을 동시에 리턴 받을 수도 있다!!



##### 23-3. 구조체를 포함하는 구조체

* 구조체 :  하나 이상의 변수를 그룹지어서 새로운 자료형을 정의
* 중첩된 구조체 : 하나 이상의 구조체를 그룹지어서 새로운 구조체 자료형을 정의
* !doublestruc.png!
* 배열과 마찬가지로, 초기화를 진행하지 않은 변수의 값은 0으로 초기화된다.

##### 23-4. 새로운 자료형의 완성

* 1) typedef 란?

* !typedef.png!

* 사용자가 기본 자료형에 부여하는 새로운 이름은 *대문자*를 사용하는 것이 좋다!

* 2) typedef와 구조체 변수의 선언

* ```c
  /*structure이라는 이름의 구조체를 typedef로 새로운 이름을 부여해주는 코드입니다.*/
  
  /*struct 구조체 생성*/
  struct structure
  {
  	int data 1;
  	int data2;
  };
  /*Structure이라는 이름으로 정의.
  궁금점 : 이때도 대문자로 표현해주는 것이 좋은가..?*/
  typedef struct structure Structure;
  
  /*========================================*/
  
  /*구조체 정의와 typedef 선언을 동시에 할 수도 있긴 하다.*/
  typedef struct structure
  {
  	int data 1;
  	int data2;
  }Structure;
  ```

* 

##### 23-5. 공용체

* 공용체란?

  * 서로 다른 자료형의 변수를 하나의 메모리 공간에서 공유하는 경우.
  * 사용될 데이터의 자료형이 유동적인 경우, 
  * 하나의 메모리 공간에서 들어오는 데이터의 자료형에 따라 메모리를 할당하게 된다.
  * 하드웨어 관련 프로그래밍에서 유용하게 사용된다!?
  * !union.png!
  * 공용체 안의 여러 개의 변수 중, 하나의 변수에 값을 대입하게 되면 나머지 변수에 대해서는 사용을 할 수 없다.
  * 한번에.. 하나의 값만...

    

##### 23-6. 열거형

* !enum.png!

* 열거형의 정의

  * 1. color이라는 이름의 자료형 정의
    2. 상수의 선언
  * 상수의 값이 정의되어있지 않은 경우 무조건 0부터 시작!

* 열거형을 사용하는 이유

  * 1. 변수가 지니는 값에 의미를 부여할 수 있다.
    2. 프로그램의 가독성이 높아진다.

    



#### 24장. 파일 입. 출력

##### 24-1. 파일의 개방(OPEN)과 종결(CLOSE)

* 파일과의 연결을 위해 필요한 것?!



* 파일의 개방(open)

  * 파일과 데이터를 주고 받을 수 있는 스트림을 생성

  * ```c
    /*성공 시 해당 파일의 파일 포인터, 실패 시 NULL 포인터 리턴 */
    FILE* fopen(const char * filename , const char * mode) 
        
    /*사용 예시*/
    /*filename에는 파일 경로 명
    파일 이름만 쓰는 경우, 프로그램이 실행되고 있는 디렉토리에서 전달된 이름의 파일을 찾아 개방하게 됨.*/
    /*슬래시가 두번?!
    => 특수문자 표현을 위해서.*/
    /*mode에는 파일의 특징 및 용도를 결정짓는다.*/
    FlLE* f = fopen( "c:\\work\\test.dat" , "rt" ); 
    ```

  * 파일의 개방모드 = 파일 접근 모드 + 데이터 입, 출력 모드

* 파일 접근 모드

  * !access.png!
  * '+'가 붙는 경우, 작업 모드를 변경할 때마다 입 출력 버퍼를 지워주어야 한다.

* 데이터 입, 출력 모드

  * !data.png!

  * CR(Carriage Return)

    * 특수문자 '\r'로 표현

    * 커서의 위치를 줄 맨 앞으로 이동하라는 의미

    * ```c
      /*CR의 의미를 출력의 결과를 통해 보여주기 위한 코드입니다.*/
      #include<stdio.h>
      
      int main(void)
      {
      	printf("ABCDEF \r");/*\r : CR*/
          printf("12345678");
      return 0;    
      }
      
      /*출력 결과 : 12345678*/
      ```

    * ABCDEF 출력 후, 커서를 맨 앞으로 이동하여 재 출력 하였으므로 ABCDEF의 출력값은 지워지게 된다.

  * LF(Line Feed)

    * 특수문자 '\n'으로 표현
    * 커서의 위치를 다음 줄로 이동하라는 의미.
    * !lf.png!
    * 프로그램 상의 \n 출력은 모니터 상에서는 \r\n으로 변환되어 출력된다!!(텍스트 모드이기 때문에..)
    * 텍스트 모드 : 문자열과 같은 텍스트 기반의 데이터
    * 2진 모드 :  데이터의 변환이 발생하면 안되는 경우(영상 데이터의 입, 출력)

* 파일 개방 모드의 완성

  * !openf.png!
  * r과 w는 기본적으로 텍스트 모드의 파일 개방 모드가 생성, t를 안붙이면 자동으로 텍스트 모드가 되지만 붙여주는 습관을 들이는 게 좋다고 한다.

* FILE 구조체의 포인터(파일 포인터)

  * 지정한 파일과의 데이터 입, 출력을 위해 스트림을 생성하는 함수
  * 리턴값이란?
    * FILE이라는 구조체 변수의 포인터(파일에 대한 여러가지 정보를 지니는 변수)
    * !fpoint.png!

* 파일의 종결(close)

  * 입출력을 완료한 파일은 반드시 닫아주어야 함.

  * 왜?! : 데이터 손실이 발생할 수도 있기 때문에.

  * 1분에 한번씩 파일을 열고 닫아야 해도 닫아주는게 좋다.

  * ```c
    #include <stdio.h>
    
    /*파일 종결 함수*/
    /*종료가 잘 이루어지면 0을 리턴*/
    int fclose(FlLE * stream);
    ```

  * ```c
    #include<stdio.h>
    
    /*파일의 open, close를 보여주기위한 코드입니다.*/
    
    int main(void)
    {
        int state = 0;
        
        /*open file*/
        /*Text.txt라는 파일을 쓰기 용도, 텍스트 모드로 연다.
        해당 파일이 존재하지 않으면 파일이 생성되게 된다.*/
        FILE * file = fopen("Text.txt", "wt");
        
        /*fopen에서 NULL 값이 출력되게 되면 Exception 처리*/
        if( file == NULL ){
            printf("file open error");
            return 1;/*-1이 아닌 1일 리턴하는 이유는??*/
        }
        
        /*file close*/
        /*파일의 종료 여부 상태를 앞서 선언한 변수에 대입하여 받아온다.*/
      	state = fclose(file);
        /*정상 종료 되었을 때 출력되는 0의 값이 대입되지 않았다면 Exception 처리*/
        if( state != 0 ){
            printf("file close error");
        	return 1;
        }
        
    return 0;  
    }
    ```

  * 



##### 24-2. 파일의 입, 출력 함수

* !stdio.png!
* f가 붙는 함수는 파일 및 기타 다른 영역으로의 데이터 입출력이 가능한 함수이다. 파일만 되는게 아님.
* fgets & fputs
* fprint & fscanf
* 파일 입, 출력 함수와 FILE 구조체 변수
  * 파일 위치 지시자(File Position indicator)
  * 파일을 어디까지 읽었는지, 위치를 기억하고 있는 변수
  * !floca.png!

##### 24-3. 파일의 끝을 확인합시다.

* !freturn.png!

* 파일의 끝을 확인하는 방법
* 1. 파일을 읽고 난 뒤 함수의 리턴값을 참조하는 방법.
     - 묵시적 형변환의 가능성에 따라 오류가 발생할 수 있다.

* 2. feof 함수를 사용하는 방법

     ```c
     /*파일의 끝에 도달한 경우 0이 아닌 값을 리턴*/
     int feof(FILE * stream);
     ```

       

##### 24-4. Random Access  파일 입, 출력

* 파일을 순차적으로 읽는 것이 아닌 경우?

* ```c
  /*stream이 가리키는 파일의 '파일 위치 지시자'를 시작 위치 wherefrom에서부터 offset만큼 이동한다” */
  int fseek(FILE * stream, long offset, int wherefrom);
  ```

* !fseek.png!

* stream : 파일 위치 지시자를 이동시킬 파일

* offset : 이동할 거리(0보다 큰수 : 파일 뒤//0보다 작은수 : 파일 앞)

* wherefrom : 이동할 기준

* !fseek2.png!



#### 25장. 메모리 관리와 동적 할당

##### 25-1.  C 언어 메모리 구조

* 스택, 힙, 데이터

* !memory.png!

* 1. 데이터 영역
     - 전역 변수, static 변수 할당
     - 프로그램의 시작과 동시에 할당
     - 프로그램 종료 시 메모리 소멸
  2. 스택 영역(Stack)
     - 지역 변수, 매개 변수(함수 호출 시 생성)
     - 함수 호출이 완료되면 사라진다.
  3. 힙 영역(Heap)
     - 프로그래머가 관리하는 메모리 영역
     - 프로그래머의 필요에 의해서 메모리 공간 할당 및 소멸되는 영역

  * 힙 영역의 특징과 필요성
    * 배열 선언 시 배열의 길이를 상수로 표현해야하는 이유?!
    * ""스택과 데이터 영역에 할당될 메모리 크기는 컴파일 되는 동안 결정되어야 한다."
    * 힙에 결정되는 메모리 크기는 런 타임 중 결정된다.

##### 25-2. 메모리 동적 할당

* 힙에 메모리를 할당하는 것
* *동적 할당(Dynamic Allocation)*
* 스택, 데이터 영역에 메모리 할당하는 것
* 정적 할당(Static Allocation)



* 1) malloc & free 함수

  * 힙 영역에 메모리를 할당 후 해제하는 함수

  * ```c
    #include<stdlib.h>
    
    /*힙 영역에 동적으로 메모리를 할당하는 함수
    성공 시 : 할당된 메모리의 첫번째 주소 리턴(void*형)
    실패 시 : NULL 리턴*/
    void * malloc(size_t size);
    ```

  * void* 형으로 주소값이 리턴되므로 형변환 필요

  * !malloc.png!

  * ```c
    #include<stdlib.h>
    
    /*할당한 메모리를 해제하는 함수*/
    void free(void* ptr);
    ```

  * 메모리 할당 => 용도에 맞게 형변환 => 값 대입 => free

* 2) calloc 함수

  * ```c
    #include<stdlib.h>
    
    /*elt_size 크기의 변수를 elt_count 갯수 만큼 저장할 수 있는 메모리 공간을 힙 영역에 할당하라.
    ==malloc(elt_count*elt_size)*/
    void *calloc(size_t elt_count, size_t elt_size);
    ```

  * !calloc.png!

#### 26장. 매크로와 전처리기(preprocessor)

##### 26-1. 전처리기에 의한 매크로 처리

* 1) 전처리기에 의한 전처리

  * '#'으로 시작하는 문장의 처리과정

* 2) '#define' 으로 시작하는 전처리기 지시자(preprocessor directive)

* !define.png!

* '#define' : 단순 치환 작업을 요청할 때 사용되는 지시자

* 매크로 : 치환의 대상이 되는 문장

* 대체 리스트 : 치환할 내용

  

##### 26-2. 매크로를 이용한 함수의 구현

* 1) 매크로 함수의 선언
* !macro.png!
* !macfunc.png!
* 1. 매크로 함수는 자료형에 독립적
  2. 실행 속도가 향상(함수의 크기가 작은 경우)
* 2) '#'을 이용한 매크로 함수 전달 인자의 문자열화
  * 1. C언어는 문자열 상수를 이어서 선언할 수 있다.
    2. '#'을 이용한 매크로 전달 인자의 문자열화
  * !ddfine.png!
* 3) '##'을 이용한 토큰의 결합
  * !shb.png!



##### 26-3. 이미 정의되어 있는 표준 매크로

* !mmacro.png!

#### 27장. 모듈화 프로그래밍



##### 27-1. 프로그래밍의 모듈화

* 모듈이란?
  * 프로그램의 일부분
  * 프로그램 코드를 기능별로 적절히 나눠서 독립된 파일에 저장하여 관리 => 모듈화 프로그래밍
* 파일의 분할 및 컴파일
  * 외부 변수의 사용 : extern
  * 함수에서 참조하는 외부의 변수 i가 다른 곳에 선언되어 있음을 컴파일러에게 알려주는 것
  * !extern.png!

##### 27-2. 헤더 파일의 구현과 유용성에 대한 이야기



##### 27-3. 조건부 컴파일

