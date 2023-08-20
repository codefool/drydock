main : main.cpp attributes.cpp
	g++ main.cpp attributes.cpp -I/usr/local/include -L/usr/local/lib -lxerces-c  -o main
