main: 
	g++ -c src/main.cpp -o obj/main.o

util:
	g++ -c src/Util/Util.cpp -o obj/Util.o

employeelist:
	g++ -c src/DataStructure/EmployeeList.cpp -o obj/EmployeeList.o

eventlist:
	g++ -c src/DataStructure/EventList.cpp -o obj/EventList.o

all: util employeelist eventlist main
	g++ obj/Util.o obj/EmployeeList.o obj/EventList.o obj/main.o -o bin/main.exe

run: all
	bin/main.exe

last: 
	bin/main.exe

static:
	g++ -fexec-charset=GBK -finput-charset=UTF-8 -c src/Util/Util.cpp -o obj/Util.o
	g++ -fexec-charset=GBK -finput-charset=UTF-8 -c src/DataStructure/EmployeeList.cpp -o obj/EmployeeList.o
	g++ -fexec-charset=GBK -finput-charset=UTF-8 -c src/DataStructure/EventList.cpp -o obj/EventList.o
	g++ -fexec-charset=GBK -finput-charset=UTF-8 -c src/main.cpp -o obj/main.o
	g++ -fexec-charset=GBK -finput-charset=UTF-8 --static obj/Util.o obj/EmployeeList.o obj/EventList.o obj/main.o -o bin/main.exe

