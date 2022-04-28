main: static dynamic dynamic2
	@gcc -o main main.c -L. -lCoolLib -ldl 
	@ #если убрать -ldl, то линковка не завершится, т.к. все способы продемонстрированы в одном файле
	@ # т.е. "подключение динамической библиотеки во время исполнения" работает всегда
	@echo "static call"
	./main 2 3
	@gcc -c main.c
	@gcc  main.o -L./eltex_lib/ -l:libCL.so -ldl
	@# на ubuntu 20.04 по какой-то причине отказывается работать LB_LIBRARY_PATH, поэтому
	@# подгружаю по-другому немного, но суть та же
	@echo "dynamic call"
	./main 4 5
static:
	@gcc -c sum.c power2.c
	@ar rc libCoolLib.a sum.o power2.o
	@ranlib libCoolLib.a
dynamic: 
	@mkdir -p eltex_lib
	@gcc -fpic -c sum.c power2.c
	@gcc -shared -o eltex_lib/libCL.so sum.o power2.o
dynamic2:
	@mkdir -p eltex_lib
	@gcc -fPIC -c sum.c power2.c
	@gcc -shared -o eltex_lib/libDL.so sum.o power2.o
clean:
	@rm -f *.o *.a *.out main
	@rm -rf eltex_lib
	@echo "Cleaned"
