# printtty
This is a simple module with a interface `printtty` to print to current TTY, which makes the kernel debugging more convenient!~

Use this module as an external one

1) add `KBUILD_EXTRA_SYMBOLS := <path-to-printtty>/Module.symvers` at the very **top** of your Makefile, divided paths by space

2) make

P.S.  **Don't** use obsolete Module.symvers
