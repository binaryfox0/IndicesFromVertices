# OpenGL Indices generator

This program is designed to generate indices from a set of vertices for use in OpenGL rendering. It takes in a list of vertices and analyzes their connectivity to create a corresponding list of indices. The generated indices can be used to define the order in which vertices should be rendered, optimizing performance and avoiding redundant vertex duplication.

## Compilation

To run this program, you'll need the following:

- C++ Compiler (supporting C++11 or higher)

```
g++ main.cpp -o IndicesFromVertices
```

## Usage

1. Launch the program from command line.
2. Copy the vertices from your code directly to program with the **format** like example below:
```
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f
```
3. Press Enter 3 times to proceed
4. Copy the generate indices and modified vertices to your code

## License

This project is licensed under the [The MIT License](LICENSE).
