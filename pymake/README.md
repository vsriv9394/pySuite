# PyMake

### Installation

An executable script is auto-created in the downloaded `pymake` folder and a corresponding entry
is added to the ~/.bashrc file.
```
python install.py
```

### Things to note

1.  Names of the directory, the header file inside it, and the struct within it must be identical.

2.  All functions must be defined in an `src` directory.

3.  Every source file must contain only one non-static function.

4.  Format the line breaks when implementing non-static functions in the source files exactly like,
    ```
    void <function-name>
    (
        <arg1_type> <arg1_name>,
        <arg2_type> <arg2_name>,
        ...
    )
    {
        // contents here ...
    }
    ```

5.  Format the line breaks when defining structures exactly like,
    ```
    typedef struct
    {
        <arg1_type> <arg1_name>,
        <arg2_type> <arg2_name>,
        ...
    }
    <struct-name>;
    ```

6.  When writing a function "belonging" to a struct, pass the owning struct type as a `void*` pointer in the arguments.

7.  The first argument for all principal functions **must** be of type `void*` as explained in the previous point
    and have the name `_self`.

8.  All non-static functions must end with the suffix `__<name-of-owner-struct>`.

9.  Each struct **must** own functions named `init__<name-of-owner-struct>` (and in most cases `delete__<name-of-owner-struct>`
    as well) implementing initialization (and destruction) of objects in the struct.

10.  The only `#include` statement in the source files should be to include the corresponding header file.

11. Any `#include` statements that correspond to other pymake classes must be enclosed between `//INCLUDES_BEGIN`
    and `//INCLUDES_END` tags.

12. For installation and uninstallation details, run `python install.py -h`.

13. Python 3.7+ is recommended.

14. One can write a `makefile.py` file to change the C compiler (default is `gcc`, but `mpicc` and `nvcc` can also be used) or
    to add paths to include directories and paths to shared library files for non-pymake style dependencies. A template file is
    given in the `pymake` directory. Please do not delete this file, as this provides the default options which are overriden if
    a local `makefile.py` is present.