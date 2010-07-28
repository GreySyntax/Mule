CC = gcc
FRAME =-F/Library/Frameworks -framework CoreFoundation -F/System/Library/PrivateFrameworks -framework MobileDevice -I./include

all:
	@echo 'Mule - Copyright GreySyntax NSPwn.com'
	@echo ''
	@echo 'Cleaning'
	@rm -rf bin
	@echo 'Creating ./bin'
	@mkdir -p bin
	@echo 'Building enterrecovery'
	@$(CC) src/enterrecovery.c -o bin/enterrecovery $(FRAME)
	@echo 'Building deactivate'
	@$(CC) src/deactivate.c -o bin/deactivate $(FRAME)
	@echo 'Building setautoboot'
	@$(CC) src/setautoboot.c -o bin/setautoboot $(FRAME)
	@echo 'Building getproduct type'
	@$(CC) src/getproducttype.c -o bin/producttype $(FRAME)

clean:
	@echo 'Cleaning'
	@rm -rf bin
