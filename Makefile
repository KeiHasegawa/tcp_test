all:server.exe client.exe TAGS.server TAGS.client

server.exe:server.cpp
	g++ -g3 $< -o $@

client.exe:client.cpp
	g++ -g3 $< -o $@

UNAME := $(shell uname)

ifneq (,$(findstring CYGWIN,$(UNAME)))
	MKTAGS_P = -p d:/cygwin64 -w
endif

TAGS.server:server.exe
	mktags.exe -e server.exe $(MKTAGS_P) -o $@

TAGS.client:client.exe
	mktags.exe -e client.exe $(MKTAGS_P) -o $@

clean:
	rm -f server.{i,j,exe} client.{i,j,exe} TAGS.{server,client} *~

