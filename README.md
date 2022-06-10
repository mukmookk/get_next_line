# get_next_line (GNL)

## Goal
`get_next_line`: 주어진 file descriptor로부터 한 줄씩 읽어들이는 함수 작성

> 42에서는 일부 허용된 함수 외에는 허용되지 않은 function call을 금지합니다. 

> 만약 허용되지 않은 function call이나 허용되지 않은 라이브러리를 include 한다면, 
> 이는 평가시 0점으로 반영되는 사유에 해당합니다.


## Description

이번 프로젝트는 호출될 때마다 해당하는 file descriptor의 한 줄을 반환하는 함수 `get_next_line`의 작성을 목표로 합니다. 

다만, 함수 작성시 주의할 점은 해당 호출 이후에도 더 읽어들일 내용이 남아있다면 해당 반환에 new line 문자를 붙여 반환한다는 점입니다. 

프로젝트 메뉴얼에서는 해당 프로젝트를 통해, 향후 사용하게 될 유용한 함수를 작성함과 동시에 해당 함수의 구현에서 핵심으로 동작하는 정적 변수를 직접 사용해보며 정적 변수의 동작 원리를 이해할 수 있었습니다.

동시에 메모리 측면에서 allocation과 이에 대한 책임으로서의 deallocation을 수행해보며, C 프로그래밍 측면에서 메모리를 관리해보았습니다.

별도의 Makefile은 필요하지 않습니다.

이외의 특징으로 컴파일을 다음과 같은 명령어로 수행한다는 점이 있습니다.
```
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c.
```

`-D` 옵션을 통해 BUFFER_SIZE라는 프로그램 내부에서 사용되는 매크로를 정의합니다.  

<br>
구현하고자 하는 `get_next_line` 함수의 프로토타입은 다음과 같습니다 : 

```c
char *get_next_line(int fd);
```

## Prototype
> 2021 07 이후 함수 프로토타입이 변경되었습니다. gnl의 변경 이전 프로토타입은 다음과 같습니다. 
> 
> `int get_next_line(int fd, char **line);`


- 입력되는 매개변수가 int `fd`만 존재합니다. 이때 해당 매개변수는 열고자하는 파일의 desriptor를 의미합니다. 다만, file descriptor의 정의에 따라 fd가 0인 경우 standard input으로 동작합니다.

- 해당 함수의 반환은 두 경우가 존재합니다:
  

| 반환 값 | 설명 |
| :---------- | :-----------|
|char *| 함수에 의해 읽어들여온 해당 줄을 포함하는 string |
| null	|EOF (End of File)에 도달하거나, 에러의 발생 |

## Function Overview

| 함수 | 설명 |
| :-- | :---------|
| get_next_line (int fd) |  Reads from fd and returns one line or null |
| get_newread (int fd) | Performs a new read from BUFFER_SIZE bytes and stores it in aux |
| gnl_expand_buffer (char *buf, int fd) | Expandse the static variable buf with a new read |
| gnl_shrink_buffer (char *buf, char *line) | Shrinks static variable buf when a line has been selected |
| gnl_strlen (const char *s) | Returns length of a string |
| gnl_strchr_i (const char *s, int c) | Returns index of first occurence of c in a string, or -1 |
| gnl_strlcpy (char *dst, const char *src, size_t size) | Copies chars from src into dst, ensuring \0 |
| gnl_substr (const char *s, unsigned int start, size_t len) | Allocates enough memory and performs gnl_strlcpy |
| gnl_strlcat (char *dst, const char *src, size_t size) | Contatenates two strings |


## Bonus

보너스를 수행하기 위해 과제에서 요구하는 사항은 두가지 입니다.

* Bonus 1: 단일 정적 변수를 사용할 것. 
  
* Bonus 2: 프로그램 실행 중 여러 file descriptor 값을 받더라도 함수가 문제없이 동작해야 합니다. 구체적으로 업타임 중 fd가 다른 함수의 호출이 여러번 일어나고, 이전에 호출하였던 fd를 매개변수로 get_next_line을 다시 호출하더라도 해당하는 fd 값에 대한 reading thread가 유지되어야만 합니다.
  * 이를 수행하기 위해 fixed string array를 추가적으로 생성하여, 해당하는 각 fd 값에 대해 static 변수가 기록될 수 있도록 하였습니다. 

