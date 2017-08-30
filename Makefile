ppm:
	@g++ make_img.cpp -o make_ppm

rppm:
	@g++ make_img.cpp -o make_ppm
	@./make_ppm file_examples/my_file.txt
	@rm make_ppm

render:
	@g++ Render.cpp -o render
	@./render file_examples/my_file.txt
	@rm render