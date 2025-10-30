# **BX++**
### **Written in C**
#### ~~*of course it is!*~~

This is a prototype language written in c. This emulates the features of **C1** for learning purposes only.

*(Its a requirement for school!)*

![my pet](https://static.wikia.nocookie.net/the-unofficial-outcome-memories/images/e/e8/Meowl.jpg/revision/latest?cb=20251009174607)


# WORK IN PROGRESS!!!!!
This project still only has the lexical analysis phase down, please stay tuned for the full release!!

# Prerequisites
- [MinGW](https://sourceforge.net/projects/mingw/)
- PCRE2 (for non-POSIX systems)
  - Used for regex since windows doesnt have it for some reason!!!

# Installation (WINDOWS)
1. Clone the repository using `git clone`
2. Download PCRE2 10.47 from [here](https://github.com/PCRE2Project/pcre2/releases).
3. Navigate to `pcre2-10.47\cmake` and run `CMake -G 'MinGW Makefiles' ..`
4. It will show you an option, if I ever spelt it wrong, make sure to find something along the lines of `MinGW` I forgot
5. After it compiles, go to the root folder `pcre2-10.47` and paste it to the project file, and rename it as 
6. **Make sure your `gcc` has parameters: `-L "{pcre}\cmake"` & `-I "{pcre}\cmake\interface"`**

# Installation (MacOS/Linux)
**Linux and MacOS** contains the **POSIX regex**, so there is no need to install them.
1. Clone the repository using `git clone`
2. Build the project using `gcc`

# Usage
The file extension of this programming language should be **.bx**. It will not compile files that do not contain this extension. an example .bx project:

`Hello.bx`
```
var char first_char = 'a';
var = 35
var char second_char = 'b';
var int first_int = 32;

// This is my Comment

var float first_float = 54.23 + 32.43;
var int second_int = 324 * 32 + 44 - 66 + first_int;

for (var i = 0; i <= 32; < i++) {
  first_int--;
}

if (first_int == 32) {
  first_int = 2;
} else {
  first_int = 3;
}
```
# Documentation

<Upload the formal document here!>