# Discrete Cosine Transform Image Compression (DCT)

### Introduction

DCT is a somewhat trivial implementation of a lossy image compression
strategy that uses the Discrete Cosine Transform and Linear Quantization.

It was created as a way to explore compression technology. It is not expected to
be exceptionally fast, or even good at what it is supposed to do. It does not output
a smaller image, just the reconstructed one. This library would make a horrible tool
in any production environment, but having immediate access to before and after images
of a compression strategy is incredibly useful.

### Usage

Invocations must follow the form:

`./dct -c {path to infile} -d {degree} -p {p-value}`

> A file called 'out.png' will be generated in the same directory as the executable.

### CLI Arguments

The cli arguments are defined  below:

    CLI Arguments:

 	compress (-c)
 		Image to be compressed.

	degree (-d)
 		Desired degree of the DCT matrix to be used. Takes the form n x n where n is the
		magnitude of each dimension.

	p-value (-p)
 		Desired p-value used to initialize the quantization matrix.

### Building

To build DCT, you must have the following installed:
* CMake
* libpng
* OpenCL

To clone and build, run the following command:

```
git clone https://github.com/idobbins/DCT.git

# out of source builds are encouraged
mkdir build
cd build

cmake ../DCT
make
``` 





---
### Reference Links

Test image sources:
* [basis_universal](https://github.com/BinomialLLC/basis_universal)
* [PNG Test.png](https://commons.wikimedia.org/wiki/File:PNG_Test.png)

Third Party Libraries:
* [libpng](http://www.libpng.org)
* [OpenCL](https://www.khronos.org/opencl/) - not fully implemented
