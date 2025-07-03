# 42_get_next_line

This project is part of the 42Prague curriculum.

## Overview

**get_next_line** is a function designed to read a file or input stream line by line, returning each line with every call. The goal of this project is to master static variables, memory allocation, and file descriptor management in C. This function is especially useful for reading text files or streams where the size of each line is not known in advance.

## Features

- Reads from any file descriptor (including files, standard input, etc.).
- Returns the next line each time it is called, including the terminating newline character (`\n`) if present.
- Manages its own memory and buffers for efficient reading.
- Compliant with 42 coding standards.

## Directory Structure

```
.
├── *.c
└── *.h
```

## How to Use

1. **Clone the repository:**
    ```bash
    git clone https://github.com/ivantsowlad/get_next_line.git
    cd get_next_line
    ```

## There is no Makefile in this project because of 42 subject. But there are 2 options: add Makefile or add main.c and compile it manually.

2. **Build the library:**
    ```bash
    make
    ```
   This will generate the `get_next_line.a` static library file.

4. **Include in your project:**
   - Add `get_next_line.a` to your project's linking step.
   - Include `get_next_line.h` in your source files.

    ```c
    #include "get_next_line.h"
    ```

5. **Clean built files:**
    ```bash
    make clean      # Removes object files
    make fclean     # Removes object files and get_next_line.a
    make re         # Rebuilds the library
    ```

## Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

Compile and link with the library:
```bash
gcc main.c -L. -lget_next_line
```

## Requirements

- GCC or compatible C compiler
- Make

## Notes

- The implementation only uses the allowed C standard library functions per 42 project requirements.
- The function prototype is:
    ```c
    char *get_next_line(int fd);
    ```
- The buffer size can be set with the `BUFFER_SIZE` macro at compile time.

## License

This project is part of the 42Prague curriculum and is intended for educational use.

## Author

- [ivantsowlad](https://github.com/ivantsowlad)
