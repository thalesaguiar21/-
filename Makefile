ppm:
	@g++ make_img.cpp -o make_ppm

rppm:
	@g++ make_img.cpp -o make_ppm
	@./make_ppm utils/my_file.txt
