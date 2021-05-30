all:server.exe client.exe TAGS

server.exe:server.cpp
	g++ -g3 $< -o $@

client.exe:client.cpp
	g++ -g3 $< -o $@

UNAME := $(shell uname)

ifneq (,$(findstring CYGWIN,$(UNAME)))
	MKTAGS_P = -p d:/cygwin64 -w
endif

TAGS:server.exe client.exe
	mktags.exe -e server.exe client.exe $(MKTAGS_P)

clean:
	rm -f server.{i,j,exe} client.{i,j,exe} TAGS *~

