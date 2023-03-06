#C++ coding tools
---

###C++ project directory layout

A C++ project is a collection of header + source files: 
####• Header files:
- define class interfaces / function signatures
- hpp extension
- put into include/
  
####• Source files:
  - contain the implementation of the signatures defined in the
  corresponding .hpp files
  - cpp extension
  - put into src/

---

###Header and source files


Header files (extension .hpp) are used to declare just the prototypes (also known as, “signatures” or “declarations”) of the functions whose body is defined elsewhere (in a .cpp file).
For example, this is a function’s prototype defined in the header file “include/myfunction.hpp”:

>     int myfunction(int, double);

Header files are then included in the cpp files that need to use those functions (because the compiler requires that at least the prototype of a function is defined in the cpp file using that function).
The file “src/myfunction.cpp” will begin with
>     #include “myfunction.hpp”
This is exactly like writing
>     int myfunction(int x, double y);
directly in the .cpp file.
The object files (.o) defining the function’s body have to be linked at compile time.

---

##Make
https://www.gnu.org/software/make/manual/make.html

• The program make can be used to automatize a pipeline of tasks, each of which may
depend on the output of other tasks.
• Example: a task produces file . Task requires and produces file . Hence, task cannot be run if file has not been created (i.e. if task is not run first)!
• Typically used to compile code (many intermediate object files).
• The pipeline of tasks is specified in a “special” file, called Makefile.

---

###Makefiles
• A Makefile is composed by many rules.
• A rule is made up of:
- target: name of a file we want to generate or name of an action (e.g., clean, debug, or release)
- prerequisites: file(s) needed as input to generate the target
- recipe: an action to be performed (e.g., one or more commands)

• Behaviour of make <target>:
- If any prerequisite changed (timestamps are used) execute recursively the recipe of the prerequisite.
- Execute the recipe of the target.

• If no target specified (you just typed make): take the first one.
#####Example
Makefiles are not used only for compiling tasks
>       final.txt: text1.txt text2.txt
>           cat text1.txt text2.txt > final.txt
>       text1.txt:
>           echo "text 1" > text1.txt
>       text2.txt:
>           echo "text 2" > text2.txt

#####Example

>       OPTIONS=-O3
> 
>       all: build/mytool
> 
>       debug: OPTIONS=-O0 -g
>       debug: build/mytool
>
>       build/mytool: build/myfunc.o tools/main.cpp
>           g++ ${OPTIONS} tools/main.cpp -o build/mytool -I ./include/ build/myfunc.o
>
>       build/myfunc.o: src/myfunc.cpp include/myfunc.hpp
>           g++ ${OPTIONS} -c src/myfunc.cpp -I ./include/ -o build.myfunc.o 
>
>       clean:
>           rm -rf build/*.o build/mytool

---

###Makefiles as directed acyclic graphs (DAGs)

The dependencies in Makefiles can be specified as directed acyclic graphs (or DAGs). 
To determine the order of execution of the targets, make sorts this graph so that
arrows (dependencies) go only in one direction.
This is called topological sorting (more details in CT0371) and is always possible on
acyclic graphs.

---
##Setting-up a project step-by-step
###Example step-by-step
1. In your home folder, create a folder power-root-example-project/ and enter it.
2. Create the project directory layout (sub-directories: include/, src/, tools/, build/).
3. Create a header include/myfunctions.hpp declaring the prototypes of these functions:
>     int power(int, int);
>     int root(int, int);
4. Create a source code file src/power.cpp defining the body of int power(int x, int y), which returns (use a for loop).
5. Create a source code file src/root.cpp defining the body of int root(int x, int y) which returns the largest integer
such that (use function power(int,int) and a while loop).
6. Create a source code file tools/main.cpp containing the main function which computes the 3-rd root of 74088. The result
has to be printed on the screen as “The answer is” followed by the result of root(74088,3).
7. Create a Makefile that compiles everything in an executable called theanswer:
     + Specify the path of the includes using g++’s option –I.
     + Use optimization level 3.
     + Create a separate object file and a separate Makefile’s  target for each cpp file.
     + Add also a clean target that removes all object files.
     + Optional: add other targets (e.g., debug) to compile with different options.
8. Compile and run the project.

There's a very similar example in "prova_makefile", without subfolders for the code.

--- 
# Asserts and Valgrind
What kind of errors can we run into when programming?
1. Linking-Time errors
2. Compilation-time errors
3. Run-time 
  
Some possible solutions are debugging, pre/post conditions (asserts), exceptions

### Debugging
Debugging means finding logical errors in your program.
• Sometimes very hard to find: the program links, compiles, and runs but the output is
wrong!
• Even worse, on some inputs the program works but on other input it does not work:
hard to reproduce the bug.
• To find bugs, we need to inspect the program at run-time (while it is executing).
##### How? Options:
• Plan you algorithms carefully :D
• Ensure pre/post conditions (asserts)
• Throw exceptions (next lectures)
• Use a debugger (Linux has gdb; but we will not cover this)

--- 
##### minimalist example - asserts
>     #include <cassert>
>     int main() {
>       /* throws a failed assertion */
>       assert(3 != 3);
>     }

Assert is a function that takes as input a boolean condition (actually, an int: it fails when the input is 0) and halts the program when the condition is not satisfied. It is somehow the best way to document your code. 
Compile with g++’s -DNDEBUG (gcc’s option -D, argument NDEBUG) to disable asserts (they are enabled by default): this way, they do not affect performance! Good idea is to leave them enabled only in debug mode