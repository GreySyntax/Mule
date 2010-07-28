CC = gcc
FRAME =  -F/Library/Frameworks -framework CoreFoundation -F/System/Library/PrivateFrameworks -framework MobileDevice -I./include

all:
	@$(CC) src/enterrecovery.c -o bin/enterrecovery $(FRAME)
	@$(CC) src/deactivate.c -o bin/deactivate $(FRAME)
	@$(CC) src/setautoboot.c -o bin/setautoboot $(FRAME)
	@$(CC) src/getproducttype.c -o bin/producttype $(FRAME)
