all: 
	g++ judger.cpp -pthread -lmongoclient -lboost_thread -lboost_system -lboost_regex -o judger -lboost_filesystem -lboost_program_options -g

clean:
	rm judger -f
