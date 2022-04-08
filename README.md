# Discrete Cosine Transform Image Compression (DCT)

Given curiosity, I build things and find myself illuminated.

DCT is a somewhat trivial implementation of a lossy image compression
strategy that uses the Discrete Cosine Transform and Linear Quantization.

It doesn't do much other than that.

The cli parameters are rigid; there is minimal checking.

Invocations should follow the form:

`./dct -c {path to infile} -d {degree} -p {p-value}`

The cli arguments are defined  below:

    CLI Arguments:

 	compress (-c)
 		Image to be compressed.

	degree (-d)
 		Desired degree of the DCT matrix to be used. Takes the form n x n where n is the
		magnitude of each dimension.

	p-value (-p)
 		Desired p-value used to initialize the quantization matrix.

There is also some basic logging to show the progress of the compression.

---

Test image sources:
* [basis_universal](https://github.com/BinomialLLC/basis_universal)
* [PNG Test.png](https://commons.wikimedia.org/wiki/File:PNG_Test.png)

Third Party Libraries:
* [libpng](http://www.libpng.org)
* [OpenCL](https://www.khronos.org/opencl/) - not fully implemented
