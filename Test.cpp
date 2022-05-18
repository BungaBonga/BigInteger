#include "BigInteger.h"


int main() {
	BigInteger p;
	BigInteger* b1 = NULL;
	BigInteger* b2 = NULL;

	try {
		b1 = new BigInteger("10000000000000000000000");
	}
	catch (...) {
		std::cout << "Test1 failed" << std::endl;
	}
	std::cout << "Test1 passed" << std::endl;

	try {
		b2 = new BigInteger();
	}
	catch (...) {
		std::cout << "Test2 failed" << std::endl;
	}
	std::cout << "Test2 passed" << std::endl;
	try {
		b2->get_r();
	}
	catch (...) {
		std::cout << "Test3 failed" << std::endl;
	}
	if (*b2 == 0) {
		std::cout << "Test3 failed" << std::endl;
	}
	else { std::cout << "Test3 passed" << std::endl; }

	try {
		b2->remove_leading_zeros();
	}
	catch (...) {
		std::cout << "Test5 failed" << std::endl;
	}
	if (*b2 == 0) {
		std::cout << "Test5 passed" << std::endl;
	}
	else { std::cout << "Test5 failed" << std::endl; }

	try {
		if (b1->toString() != "10000000000000000000000") {
			std::cout << "Test6 failed" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Test6 failed" << std::endl;
	}
	std::cout << "Test6 passed" << std::endl;

	try {
		if (b1->ChangeSign(*b1) != -*b1) {
			std::cout << "Test7 failed" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Test7 failed" << std::endl;
	}
	std::cout << "Test7 passed" << std::endl;

	try {
		*b1 / *b2;
	}
	catch (const BigInteger::big_int_error& ex) {
		if (ex == BigInteger::ELOGFAIL) {
			std::cout << "Test8 passed" << std::endl;
		}
		else {
			std::cout << "Test8 failed" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Test8 failed" << std::endl;
	}

	try {
		*b2 = *b1;
	}
	catch (...) {
		std::cout << "Test9 failed" << std::endl;
	}
	std::cout << "Test9 passed" << std::endl;
	std::cout << *b1 << std::endl;
	std::cout << *b2 << std::endl;

	try {
		if (BigInteger(10000000) != BigInteger("100000000000")) {
			std::cout << "Test10 passed" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Test10 failed" << std::endl;
	}

	try {
		p = "--100000000000000000000000000000";
	}
	catch (const BigInteger::big_int_error& ex) {
		if (ex == BigInteger::EINVARG) {
			std::cout << "Test11 passed" << std::endl;
		}
		else {
			std::cout << "Test11 failed" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Test11 failed" << std::endl;
	}

	bool m;
	try {
		m = bool(*b1);
	}
	catch (...) {
		std::cout << "Test12 failed" << std::endl;
	}
	if (m == 1) {
		std::cout << "Test12 passed" << std::endl;
	}
	else { std::cout << "Test12 failed" << std::endl; }

	try {
		*b1 /= "string"; //��� ��������� ��������� ������������ ����� ����� ��
	}
	catch (const BigInteger::big_int_error& ex) {
		if (ex == BigInteger::EINVARG) {
			std::cout << "Test13 passed" << std::endl;
		}
		else {
			std::cout << "Test13 failed" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Test13 failed" << std::endl;
	}

	try {
		*b1 / "string"; //��� ��������� �������� �������� ����� ����� ��
	}
	catch (const BigInteger::big_int_error& ex) {
		if (ex == BigInteger::EINVARG) {
			std::cout << "Test14 passed" << std::endl;
		}
		else {
			std::cout << "Test14 failed" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Test14 failed" << std::endl;
	}

	BigInteger t = "100000000000000000000000000000";
	p = "100000000000000000000000000000";
	try {
		if (p == t) {
			std::cout << "Test15 passed" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Test15 failed" << std::endl;
	}

	try {
		if (++p != t) {
			std::cout << "Test16 passed" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Test16 failed" << std::endl;
	}

	try {
		if (--p == t) {
			std::cout << "Test17 passed" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Test17 failed" << std::endl;
	}

	try {
		if (p++ == t) {
			std::cout << "Test18 passed" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Test18 failed" << std::endl;
	}

	try {
		if (p-- != t) {
			std::cout << "Test19 passed" << std::endl;
		}
	}
	catch (...) {
		std::cout << "Test19 failed" << std::endl;
	}
	delete b1;
	delete b2;
	p.~BigInteger();
	t.~BigInteger();
}