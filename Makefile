CPPFILES := $(wildcard ./*.cpp)
OFILES = $(CFILES: ./%.c = ./Output/%.o)
OBJFILES := $(wildcard ./Output/*.o)

all: clean $(OBJFILES) 

./Output/*.o: ./Review/*.cpp ./User/*.cpp ./System/system.cpp ./Request/*.cpp ./Function/*.cpp ./bike/MotorBike.cpp

# review
	g++ -c ./review/review.cpp -o ./Output/rev.o
	g++ -c ./review/bikeReview.cpp -o ./Output/bikerev.o
	g++ -c ./review/memReview.cpp -o ./Output/memrev.o

# user
	g++ -c ./user/user.cpp -o ./Output/user.o
	g++ -c ./user/admin.cpp -o ./Output/admin.o
	g++ -c ./user/member.cpp -o ./Output/member.o

# system
	g++ -c ./System/System.cpp -o ./Output/System.o

# request
	g++ -c ./Request/Request.cpp -o ./Output/Request.o

# function
	g++ -c ./Function/Function.cpp -o ./Output/Function.o

# bike
	g++ -c ./bike/MotorBike.cpp -o ./Output/bike.o

# main
	g++ -c main.cpp -o ./output/main.o
run:
	g++ $(OBJFILES) -o ./output/main.exe
	./output/main.exe
clean:
	del .\Output\bike.o .\Output\rev.o .\Output\bikerev.o   .\Output\memrev.o .\Output\request.o  
	del .\Output\admin.o .\Output\member.o .\Output\user.o
	del .\Output\function.o
	del .\Output\system.o .\Output\main.exe