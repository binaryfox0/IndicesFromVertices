# OpenGL Index Generation Program

This program is designed to generate indices from a set of vertices for use in OpenGL rendering. It takes in a list of vertices and analyzes their connectivity to create a corresponding list of indices. The generated indices can be used to define the order in which vertices should be rendered, optimizing performance and avoiding redundant vertex duplication.

## Prerequisites

To run this program, you'll need the following:

- C++ Compiler (supporting C++11 or higher)
- Tested on Windows 10, MSVC compiler

## Compilation
```
cl /Zi /EHsc /nologo /std:c++14 /Fe:indicesgenerator.exe Main.cpp
```

## Usage

**_Warning_: A bug found when inputing a vertices list with program code can be made program generate faulty indices list. Moderator is fixing it as fast as possible. Thank you**

1. Launch the program from command line.
2. Copy the vertices from your code directly to program.
3. Press Enter 2 times to process
4. Copy the generate indices and modified vertices to your code

## Contributing

Contributions to this application are welcome. If you find any issues or have suggestions for improvement, please feel free to open an issue or submit a pull request.

## License

This project is licensed under the [The MIT License](LICENSE).

## Contact

If you have any questions or need further assistance, please feel free to contact the project maintainer at phamducduy6122011@gmail.com
