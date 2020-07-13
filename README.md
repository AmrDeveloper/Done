# Done
Toy Compiler to generate C Code and executable and has preprocessor to handle multi-files

Done support most of C Features like struct, enum, pointer, address and can use any C library
and also have some new features from other languages like single line function and Elvis operator 
and can separate number with _ for example 1_000_000

Simple code Example

```
//Files written in Done Language
//import "source.done"

//C Standard Libraries or Done Runtime Libraries written in C
include "stdio.h"

fun isOdd(x : int) : bool -> return x%2 == 0;
fun isEvent(x : int) : bool -> return x%2 != 0;

fun main() : int {
    printf("Enter your number : ");
    var number : int;
    scanf("%d", &number);
    if(isEvent(number)) {
       printf("Even Number");
    }else{
       printf("Odd Number");
    }
    return 0;
}
```
 
 Video Example : [Youtube](https://www.youtube.com/watch?v=SJO56RAF2UY)
