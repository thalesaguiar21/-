comp:
	@g++ -std=c++11 Main.cpp -o renderer
	@rm renderer

render1:
	@g++ -std=c++11 Main.cpp -o renderer
	@./renderer inputs/file1.txt
	@rm renderer

render2:
	@g++ -std=c++11 Main.cpp -o renderer
	@./renderer inputs/file2.txt
	@rm renderer
