#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <cmath>


class BigInteger {
	static const int base = 10000;
	std::vector<int> digits;
	bool sign = false;

public:

	enum big_int_error {
		EINVARG,
		ELOGFAIL
	};

	BigInteger& operator=(const BigInteger& x);

	bool operator==(const BigInteger&) const;
	bool operator!=(const BigInteger&) const;
	bool operator<(const BigInteger&) const;
	bool operator>(const BigInteger&) const;
	bool operator<=(const BigInteger&) const;
	bool operator>=(const BigInteger&) const;

	BigInteger& operator+=(const BigInteger&);
	BigInteger& operator-=(const BigInteger&);
	BigInteger& operator/=(const BigInteger&);
	BigInteger& operator*=(const BigInteger&);
	BigInteger& operator%=(const BigInteger&);

	BigInteger operator+(const BigInteger& b_left) const;
	BigInteger operator-(const BigInteger& b_left) const;
	BigInteger operator*(const BigInteger& b_left) const;
	BigInteger operator/(const BigInteger& b_left) const;
	BigInteger operator%(const BigInteger& b_left) const;

	BigInteger& operator++();
	BigInteger operator++(int);
	BigInteger& operator--();
	BigInteger operator--(int);

	BigInteger();
	BigInteger(std::string);
	BigInteger(int);
	BigInteger(const BigInteger&);
	BigInteger(const char*);
	~BigInteger() = default;

	explicit operator bool();

	BigInteger operator-() const;

	void get_r();
	void remove_leading_zeros();
	std::string toString() const;
	BigInteger& ChangeSign(BigInteger& b);

	friend std::ostream& operator <<(std::ostream&, const BigInteger&);
	friend std::istream& operator >>(std::istream&, BigInteger&);
};

