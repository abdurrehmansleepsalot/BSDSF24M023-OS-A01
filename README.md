# BSDSF24M023-OS-A01
Well a repo to complete my OS assignment

So its 22,Sep,2026
today i well revised my task 2 and also added a tag and made a release 
1. The Linking Rule: $(TARGET): $(OBJECTS) vs. Linking a Library
   $(TARGET): $(OBJECTS) Rule: This rule tells make that the final executable program (the $(TARGET)) depends on the individual compiled object files (the $(OBJECTS), like main.o, mystrfunctions.o, etc.). When make executes the recipe for this rule (usually something like gcc $(OBJECTS) -o $(TARGET)), the linker combines all these raw, individual object files that you just compiled into one final executable.

    However when you link against a library (like a static .a or shared .so file), you are not providing all the raw object files to the linker. Instead, the library is already a pre-compiled bundle of object files. A rule linking a library would use specific flags, like -L (to specify the folder) and -l (to specify the library name, e.g., gcc main.o -L./lib -lmylib -o client). The linker then searches the library and extracts only the specific functions your program actually uses, rather than blindly mashing all the .o files together.
