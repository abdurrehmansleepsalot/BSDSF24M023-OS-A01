# BSDSF24M023-OS-A01

A repo to complete my OS assignment.

**Date:** 22 Sep, 2026

Today I revised Task 2, added a tag, and made a release.

---

## 1. The Linking Rule: `$(TARGET): $(OBJECTS)` vs. Linking a Library

### `$(TARGET): $(OBJECTS)` Rule
This rule tells `make` that the final executable program (`$(TARGET)`) depends on the individual compiled object files (`$(OBJECTS)`, like `main.o`, `mystrfunctions.o`, etc.). When `make` executes the recipe for this rule — usually something like:

```makefile
gcc $(OBJECTS) -o $(TARGET)
```

— the linker combines all these raw, individual object files that you just compiled into one final executable.

### Linking Against a Library
When you link against a library (static `.a` or shared `.so`), you are **not** providing all the raw object files to the linker. Instead, the library is already a pre-compiled bundle of object files. A rule linking a library uses specific flags:

- **`-L`** — specifies the folder to search
- **`-l`** — specifies the library name (e.g., `-lmylib`)

```makefile
gcc main.o -L./lib -lmylib -o client
```

The linker then searches the library and extracts **only** the specific functions your program actually uses, rather than blindly combining all the `.o` files together.

---

### Comparing Makefiles: Part 2 vs. Part 3

| | **Part 2 (Direct Linking)** | **Part 3 (Static Library Linking)** |
|---|---|---|
| **Dependency** | `client: main.o myfilefunctions.o mystrfunctions.o` — depends explicitly on all individual object files | `client_static: main.o` — only requires the driver object file |
| **Compile command** | `gcc main.o myfilefunctions.o mystrfunctions.o -o client` | `gcc main.o -L../lib -lmyutils -o client_static` |
| **Source of implementation** | Passed directly as raw `.o` files | Resolved from the static library |

**New flags introduced:**

| Flag | Purpose |
|---|---|
| `-L../lib` | Tells the linker which directory to search for custom libraries |
| `-lmyutils` | Tells the linker the specific library name to link against (omitting the `lib` prefix and `.a` extension) |

**Rule transformation:**
```makefile
# Before (direct object linking)
client: main.o myfilefunctions.o mystrfunctions.o
	gcc main.o myfilefunctions.o mystrfunctions.o -o client

# After (library linking)
client_static: main.o
	gcc main.o -L../lib -lmyutils -o client_static
```

---

## 2. Purpose of `ar` and `ranlib`

### The `ar` (Archiver) Command
Bundles multiple compiled object files (`.o`) into a single archive file — a static library (`.a`). It acts like a zip file for object code, grouping related functions together so developers don't have to manually link dozens of individual `.o` files.

### The Purpose of `ranlib`
Generates an index (table of contents) of all the symbols (functions and variables) stored inside the archive, and embeds this index into the archive itself. When the linker (`ld`) uses the library later, this index lets it instantly find which object file contains a specific function — dramatically speeding up linking.

> **Note:** Modern versions of `ar` using the `s` flag (`ar rcs`) build this index automatically, doing the job of `ranlib` at the same time.

---

## 3. `nm` Output and Static Linking Mechanics

**Are the symbols present?**
Yes — running `nm` on the `client_static` executable shows symbols for functions like `mystrlen` distinctly present, usually marked with **`T`** (indicating they reside in the `.text` / executable code section).

**What this tells us about static linking:**
This proves static linking operates as a direct **"copy-and-paste"** mechanism. During compilation, the linker extracts the required machine code from the static library (`libmyutils.a`) and physically embeds it inside the final `client_static` executable.

As a result, the final executable is **entirely self-contained** and will run independently — even if the original static library file is deleted or moved.
## 4. Dynamic Libraries and Execution

### Position-Independent Code (-fPIC)
`-fPIC` stands for Position-Independent Code. It directs the compiler to generate machine code that executes correctly regardless of its absolute address in memory. 

This is a fundamental requirement for shared libraries (`.so` files) because multiple different programs might load the exact same shared library simultaneously. If the library required a specific, fixed memory address, it would cause conflicts (address collisions) with other libraries or programs. `-fPIC` solves this by using relative addressing (offsets) instead of absolute memory addresses, allowing the operating system to safely load the library wherever there is free space in RAM.

### File Size Comparison: Static vs. Dynamic
When comparing the file sizes using `ls -lh`, the static client (`client_static`) is significantly larger than the dynamic client (`client_dynamic`). 

This difference exists because of how the linker handles the code:
*   **Static Linking:** Physically copies the compiled machine code for all used functions (like `mystrlen`) directly into the `client_static` executable. 
*   **Dynamic Linking:** Does not copy the function code. Instead, it only embeds a lightweight reference (a stub) in the `client_dynamic` executable. The actual code remains inside the `libmyutils.so` file and is only loaded into memory when the program is actively running.

### LD_LIBRARY_PATH and the Dynamic Loader
`LD_LIBRARY_PATH` is a Linux environment variable that instructs the system's dynamic loader to search specific custom directories for shared libraries (`.so` files) before looking in the standard system directories (like `/usr/lib` or `/lib`).

**Why it was necessary:**
By default, the operating system has no idea that our custom `libmyutils.so` exists in our project's local `../lib` directory. Setting this variable temporarily points the loader to our local folder so it can find the required library to run the program.

**What this tells us about the dynamic loader:**
This demonstrates that the operating system's dynamic loader is actively responsible for locating, loading, and linking external dependencies into the program's memory *on the fly* at runtime. It also shows that the loader strictly adheres to predefined search paths for security and efficiency, requiring explicit instructions (like `LD_LIBRARY_PATH`) to trust and load libraries from non-standard locations.
