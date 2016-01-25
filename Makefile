
exe_out := d2b
inclusive_exe_out := d2bI

default:
	g++ -std=c++11 dtob.cpp -o $(exe_out)
	g++ -std=c++11 dtob_inclusive.cpp -o $(inclusive_exe_out)

clean:
	rm -f $(exe_out)
	rm -f $(inclusive_exe_out)

