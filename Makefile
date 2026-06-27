build:
	gcc main.c -o build/main

run:
	build/main

debug:
	gcc main.c -o build/main && build/main