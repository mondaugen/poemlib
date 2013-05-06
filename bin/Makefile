INC = -I../
LIB = /usr/local/lib/libkyotocabinet.dylib
OPT = -ggdb3
CXX = clang++
BIN = makepronundb ezrhyme cmudbfill

all : ${BIN}

makepronundb : makepronundb.cc
	${CXX} ${INC} ${LIB} $< -o $@

ezrhyme : ezrhyme.cc
	${CXX} ${INC} ${LIB} $< -o $@

cmudbfill : cmudbfill.cc
	${CXX} ${INC} ${LIB} $< -o $@

clean :
	rm ${BIN}
