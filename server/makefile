serverapp: main.o functions_for_server.o server.o
	g++    main.o functions_for_server.o server.o -o serverapp

	main.o: main.cpp 
		g++ -c main.cpp

	functions_for_server.o: functions_for_server.cpp
		g++ -c functions_for_server.cpp
		
	server.o: server.cpp
		g++ -c server.cpp