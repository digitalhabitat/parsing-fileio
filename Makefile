
parse: main.cpp
	g++ main.cpp -o parse
# compile executable if any changes made to main.cpp 

clean:
	rm output.txt parse
# remove ofstream outputs, and executable

cleanall:
	rm output.txt input.txt parse
# remove .txt files and executable

run: parse
	./parse
#run executable
