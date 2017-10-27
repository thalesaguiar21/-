comp:
	@g++ -pthread -std=c++11 Main.cpp -o renderer
	@rm renderer

render:
	@g++ -pthread -std=c++11 Main.cpp -o renderer
	@./renderer $(input)
	@rm renderer