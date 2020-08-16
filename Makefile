# target: dependencies
# 	action

output: Main.o Render.o Obj.o structures.o
	g++ Main.o Render.o Obj.o structures.o -o output

Main.o: Main.cpp
	g++ -c Main.cpp

Render.o: Render/Render.cpp Render/Render.h
	g++ -c Render/Render.cpp

Obj.o: Obj/Obj.cpp Obj/Obj.h
	g++ -c Obj/Obj.cpp

structures.o: structures/structures.cpp structures/structures.h
	g++ -c structures/structures.cpp

clean:
	rm *.o output