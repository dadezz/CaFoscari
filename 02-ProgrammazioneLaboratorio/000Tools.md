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

###Make
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
