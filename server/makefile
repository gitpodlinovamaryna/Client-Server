serverapp: main.o server.o functions_for_server.o
	g++    main.o server.o functions_for_server.o -o serverapp

main.o: main.cpp
	g++ -c main.cpp

client.o: server.cpp
	g++ -c server.cpp

functions_for_server.o: functions_for_server.cpp
	g++ -c functions_for_server.cpp