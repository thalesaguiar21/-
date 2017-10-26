comp:
	@g++ -pthread -std=c++11 Main.cpp -o renderer
	@rm renderer

render1:
	@clear
	@g++ -pthread -std=c++11 Main.cpp -o renderer
	@./renderer inputs/file1.txt
	@rm renderer

render2:
	@g++ -pthread -std=c++11 Main.cpp -o renderer
	@./renderer inputs/file2.txt
	@rm renderer
