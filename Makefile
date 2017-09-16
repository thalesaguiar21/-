comp:
	@g++ -std=c++11 Main.cpp -o renderer
	@rm renderer

render:
	@g++ -std=c++11 Main.cpp -o renderer
	@./renderer inputs/file1.txt
	@rm renderer
