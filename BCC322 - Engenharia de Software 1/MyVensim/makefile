output: myvensim
	g++ ./test/funcional/*.cpp ./bin/dll/myvensim.dll -o ./bin/main_funcional.exe 
	#g++ ./test/unit/*.cpp ./bin/dll/myvensim.dll -o ./bin/main_unitario.exe 

myvensim: ./src/lib/*.cpp
	g++ -shared ./src/lib/*.cpp -o ./bin/dll/myvensim.dll -fPIC

mfe:
	./bin/main_funcional.exe

mue:
	./bin/main_unitario.exe