# Task_Search_file
## How to Use
### Compilation:

Used GCC compilier.

Building the Static Library and Application:

To compile the static library and the application,  run the make command in the terminal.
The make command will compile the code, create the static library (libfile_search_lib.a), and build the test application (test_app).

### Search

After successful compilation, execute the test_app application in the terminal.
The application will start searching for the file named test.txt." It will start with "C:\". To change these parameters, you should change

root_dir = opendir("C:/"); and search_file(root_path, "test.txt") in main.c accordingly.

### Cleaning Up:

To remove the compiled object files and executables, you can use the make clean command.
