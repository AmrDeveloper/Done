# Done
Toy Compiler Project that generate C code

Done support most of C Features like struct, enum, pointer, address and can use any C library
and also have some new features from other languages like single line function and Elvis operator 
and can separate number with _ for example 1_000_000

Code Example

Utils.done
```
fun isOdd(x : int) : bool -> return x%2 == 0;
fun isEvent(x : int) : bool -> return x%2 != 0;
```

Main.done
```
// Import File written in Done Language
import {
   "Utils"
}

// Include C Standard Libraries
include {
   "stdio"
}

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

To compile this code you should write
```
donec Main.done -x
```

Now you will see main.c and main.exe if you using Windows OS,

To run the executable
```
./main
```

- Compiler Options
To the compiler name gcc or clang 
```
-c gcc
```

To set the optimization level
```
-o O3
```

To set the C generated file name
```
-g main.c
```

To set the executable file name
```
-e main
```

To enable generating executable
```
-x
```

To generate and run executable
```
-r
```

To print the donec version
```
-v
```

To Print the help menu
```
-h
```
 
Video Example : [Youtube](https://www.youtube.com/watch?v=SJO56RAF2UY)

License

```
MIT License

Copyright (c) 2020 Amr Hesham

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```