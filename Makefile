CC=g++
CFLAGS= -Wall -g -fprofile-arcs -ftest-coverage

all: Test
Test.o: Test.cpp
	${CC} -c Test.cpp -o Test.o ${CFLAGS}
BigInteger.o: BigInteger.cpp
	${CC} -c BigInteger.cpp -o BigInteger.o ${CFLAGS}
Test: Test.o BigInteger.o
	${CC} BigInteger.o Test.o -o Test ${CFLAGS}
clean:
	@rm -rf *.o *.gcno *.gcda *.gcov Test 2&>/dev/null
tar:
	tar czvf ../BigInteger_cpp.tgz ../BigInteger_cpp
