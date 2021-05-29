all:server.exe TAGS

server.exe:server.cpp
	g++ -g3 $< -o $@

TAGS:server.exe
	mktags.exe -e server.exe -p d:/cygwin64 -w

clean:
	rm -f server.{i,j,exe} TAGS *~

