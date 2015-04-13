# printtty
This is a simple module with a interface `printtty` to print to current TTY, which makes the kernel debugging more convenient!~

Want to use this module as an external one? Take the following methods:
	1) in your module source code, append `Modules.symvers` with the same file's content here.
	2) add `KBUILD_EXTRA_SYMBOLS := <path-to-printtty>/Modules.symvers` at the very **top** of your Makefile 
