SRC=main.cpp MyVisitor.cpp
TINYXML_SRC=tinyxml.cpp tinystr.cpp tinyxmlparser.cpp tinyxmlerror.cpp
TINYXML_DIR=tinyxml/

COMPILER=g++
EXEC_NAME=test-app

RES=  ${addprefix ${TINYXML_DIR}, ${TINYXML_SRC}} ${addprefix src/, ${SRC}}

all: build run

build:
	mkdir -p bin
	${COMPILER} ${RES} -o ./bin/${EXEC_NAME}

run: ./bin/${EXEC_NAME}
	./bin/${EXEC_NAME} --in input --out output1.xml --operation 1
	./bin/${EXEC_NAME} --in input --out output2.xml --operation 2

clean: ./bin/
	rm -R ./bin