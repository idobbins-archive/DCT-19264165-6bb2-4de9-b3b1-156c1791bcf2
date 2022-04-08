# Discrete Cosine Transform Image Compression (DCT)

Given curiosity, I build things and find myself illuminated.

DCT is a somewhat trivial implementation of a lossy image compression
strategy that uses the Discrete Cosine Transform and Linear Quantization.

It doesn't do much other than that.

The cli parameters are rigid; there is minimal checking.

Invocations should follow the form:

`./dct -c {path to infile} -d {degree} -p {p-value}`

The cli arguments are defined  below, all are reqired:

    CLI Arguments:

 	compress (-c)
 		Image to be compressed.

	degree (-d)
 		Desired degree of the DCT matrix to be used. Takes the form n x n where n is the
		magnitude of each dimension.

	p-value (-p)
 		Desired p-value used to initialize the quantization matrix.

Basic logging is provided to show the progress of the compression. For now,
every invocation outputs the reconstructed image as 'out.png' in the same directory
the executable was called from.

DCT was not built with optimization in mind. I am aware of places where memory
is allocated more often than I would prefer. I also have not done much in the 
way of cache-friendliness.

The linear algebra operations I have written were all I needed to get this working
so I didn't feel the need to import a more fully-fledged library for them.

---

Test image sources:
* [basis_universal](https://github.com/BinomialLLC/basis_universal)
* [PNG Test.png](https://commons.wikimedia.org/wiki/File:PNG_Test.png)

Third Party Libraries:
* [libpng](http://www.libpng.org)
* [OpenCL](https://www.khronos.org/opencl/) - not fully implemented
