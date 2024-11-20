sgol:main.c
	#gcc main.c model/model.a -lpthread -lm  -llwan -lz -o sgol -lsqlite3 
	gcc  -g  main.c model/model.a -Wl,-whole-archive ./lib/liblwan.a  -lsqlite3 -o sgol -Wl,-no-whole-archive  -I./ -llwan  -lpthread -lm -lz 
	#-mkdir data
clean:
	# -rm -rf data
	-rm sgol