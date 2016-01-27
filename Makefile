
exe_out := d2b

default:
	g++ -std=c++11 dtob.cpp -o $(exe_out)

clean:
	rm -f $(exe_out)

