#include "BigInteger.h"

//----------------------------------ÊÎÍÑÒĞÓÊÒÎĞÛ---------------------------------------------------------------------------
BigInteger::BigInteger() {
	digits.push_back(0);
	sign = 0;
}
BigInteger::BigInteger(int i) {
	if (i < 0) {
		sign = 1;
		i = -i;
	}
	else if (i == 0) {
		digits.push_back(0);
		sign = 0;
	}
	while (i > 0) {
		digits.push_back(i % base);
		i /= base;
	}
	this->remove_leading_zeros();
}
BigInteger::BigInteger(const BigInteger& b) {
	digits.resize(b.digits.size());
	sign = b.sign;
	digits = b.digits;
}
BigInteger::BigInteger(std::string s) {
	if (s.length() == 0) {
		digits.push_back(0);
		this->sign = 0;
	}
	else {
		if (s[0] == '-') {
			s = s.substr(1);
			this->sign = 1;
		}
		else {
			this->sign = 0;
		}
		for (auto i : s) {
			if (static_cast<int>(i) < 48 || static_cast<int>(i) > 58) {
				std::cerr << "Not a number" << " ";
				throw EINVARG;
			}
		}
		for (int i = s.length(); i > 0; i -= static_cast<int>(log10(base))) {
			if (i < static_cast<int>(log10(base)))
				this->digits.push_back(atoi(s.substr(0, i).c_str()));
			else
				this->digits.push_back(atoi(s.substr(i - static_cast<int>(log10(base)), static_cast<int>(log10(base))).c_str()));
		}
	}
	this->remove_leading_zeros();
}
BigInteger::BigInteger(const char* x) :BigInteger(std::string(x)) {}

//--------------------------ÂÑÏÎÌÎÃÀÒÅËÜÍÛÅ ÔÓÍÊÖÈÈ----------------------------------------------------------------------------------
void BigInteger::remove_leading_zeros() {
	while (this->digits.size() > 1 && this->digits.back() == 0) {
		this->digits.pop_back();
	}
	if (this->digits.size() == 1 && this->digits[0] == 0) {
		this->sign = 0;
	}
}

BigInteger& BigInteger::ChangeSign(BigInteger& b) {
	if (b == 0) return b;
	b.sign = !(b.sign);
	return b;
}

std::string BigInteger::toString() const {
	std::string ans;
	BigInteger copy = *this;
	copy.remove_leading_zeros();
	if (sign) ans += "-";
	ans += std::to_string(copy.digits[copy.digits.size() - 1]);
	for (int i = copy.digits.size() - 2; i >= 0; --i) {
		if (copy.digits[i] < 10) ans += "000";
		else if (copy.digits[i] < 100) ans += "00";
		else if (copy.digits[i] < 1000) ans += "0";
		ans += std::to_string(copy.digits[i]);

	}
	return ans;
}

BigInteger& BigInteger::operator=(const BigInteger& x) {
	digits = x.digits;
	sign = x.sign;
	this->remove_leading_zeros();
	return (*this);
}

BigInteger BigInteger::operator-() const {
	BigInteger copy = *this;
	if (copy == 0) return copy;
	else {
		copy.sign = !(copy.sign);
		return copy;
	}
}

BigInteger::operator bool() {
	return (*this != 0);
}

//-----------------ÏÅĞÅÍÎÑ ÍÀ ĞÀÇĞßÄ ÂÏÅĞÅÄ(ÍÀÄÎ ÄËß ÄÅËÅÍÈß)----------------------
void BigInteger::get_r() {
	if (digits.size() == 0) {
		digits.push_back(0);
		return;
	}
	digits.push_back(digits[digits.size() - 1]);
	for (int i = static_cast<int>(digits.size()) - 2; i > 0; --i) {
		digits[i] = digits[i - 1];
	}
	digits[0] = 0;
}

//-------------------------ËÎÃÈ×ÅÑÊÈÅ ÎÏÅĞÀÖÈÈ----------------------------------------------------------------------
bool BigInteger::operator==(const BigInteger& b_right) const {
	if (digits.size() != b_right.digits.size()) return false;
	if (digits.empty() == 1 && b_right.digits.empty() == 1) return true;
	if (sign != b_right.sign) return false;
	for (int i = 0; i < static_cast<int>(digits.size()); ++i) {
		if (b_right.digits[i] != digits[i]) return false;
	}
	return true;
}
bool BigInteger::operator!=(const BigInteger& b_right) const {
	if (*this == b_right) return false;
	else return true;
}
bool BigInteger::operator<(const BigInteger& b_right) const {
	if (*this == b_right) return false;
	if (sign) {
		if (b_right.sign) return ((-b_right) < (-*this));
		else return true;
	}
	else if (b_right.sign) return false;
	else {
		if (digits.size() != b_right.digits.size()) {
			return digits.size() < b_right.digits.size();
		}
		else {
			for (int i = static_cast<int>(digits.size() - 1); i >= 0; --i) {
				if (digits[i] != b_right.digits[i]) return digits[i] < b_right.digits[i];
			}
			return false;
		}
	}
}
bool BigInteger::operator>(const BigInteger& b_right) const {
	if (*this == b_right || *this < b_right) return false;
	else return true;
}
bool BigInteger::operator <=(const BigInteger& b_right) const {
	if (*this < b_right || *this == b_right) return true;
	else return false;
}
bool BigInteger::operator>=(const BigInteger& b_right) const {
	if (*this == b_right || *this > b_right) return true;
	else return false;
}

//-------------------------ÑÎÑÒÀÂÍÎÅ ÏĞÈÑÂÀÈÂÀÍÈÅ-------------------------------------------------------------------
BigInteger& BigInteger::operator+=(const BigInteger& b) {
	// ìåíÿş çíàêè, åñëè îáà íå + +
	if (sign) {
		if (b.sign) {
			return ChangeSign(ChangeSign(*this) += (-b));
		}
		else {
			return ChangeSign(ChangeSign(*this) -= b);
		}
	}
	else if (b.sign) return (*this -= (-b));
	else {
		int transfer = 0;
		for (size_t i = 0; i < std::max(digits.size(), b.digits.size()) || transfer != 0; ++i) {
			if (i == digits.size()) digits.push_back(0);
			digits[i] += transfer + (i < b.digits.size() ? b.digits[i] : 0);
			transfer = digits[i] >= base;
			if (transfer != 0) digits[i] -= base;
		}
		return *this;
	}
}
BigInteger& BigInteger::operator-=(const BigInteger& b) {
	if (sign) {
		if (b.sign) return ChangeSign(ChangeSign(*this) -= (-b));
		else return ChangeSign(ChangeSign(*this) += (b));
	}
	else if (b.sign) {
		return *this += -b;
	}
	else {
		if (*this < b) {
			BigInteger temp = *this;
			*this = b;
			return ChangeSign((*this -= temp));
		}
		else {
			int transfer = 0;
			for (size_t i = 0; i < b.digits.size() || transfer != 0; ++i) {
				digits[i] -= transfer + (i < b.digits.size() ? b.digits[i] : 0);
				transfer = digits[i] < 0;
				if (transfer != 0) digits[i] += base;
			}
			this->remove_leading_zeros();
			return *this;
		}
	}
}
BigInteger& BigInteger::operator*=(const BigInteger& b) {
	BigInteger result;
	result.digits.resize(digits.size() + b.digits.size());
	for (int i = 0; i < static_cast<int>(digits.size()); ++i) {
		int transfer = 0;
		for (int j = 0; j < static_cast<int>(b.digits.size()) || transfer != 0; ++j) {
			int res;
			if (j < static_cast<int>(b.digits.size())) res = result.digits[i + j] + digits[i] * b.digits[j] + transfer;
			else  res = transfer;
			result.digits[i + j] = res % base;
			transfer = res / base;
		}
	}
	result.sign = (sign != b.sign);
	result.remove_leading_zeros();
	*this = result;
	return *this;
}
//-----------------------------ÏËŞÑ, ÌÈÍÓÑ, ÓÌÍÎÆÈÒÜ----------------------------------------------------------------------
BigInteger BigInteger::operator+(const BigInteger& b_left) const {
	BigInteger copy = *this;
	copy += b_left;
	return copy;
}
BigInteger BigInteger::operator-(const BigInteger& b_left) const {
	BigInteger copy = *this;
	copy -= b_left;
	return copy;
}
BigInteger BigInteger::operator*(const BigInteger& b_left) const {
	BigInteger copy = *this;
	copy *= b_left;
	return copy;
}
//----------------------------------------ÄÅËÅÍÈÅ---------------------------------------------------------------------
BigInteger& BigInteger::operator/=(const BigInteger& b) {
	BigInteger big = b;
	if (big == 0) {
		std::cerr << "Division by zero" << " ";
		throw ELOGFAIL;
	}
	BigInteger copy = *this;
	digits.clear();
	big.sign = 0;
	BigInteger current = 0;
	digits.resize(copy.digits.size());
	for (int i = static_cast<int>(digits.size()) - 1; i >= 0; --i) {
		current.get_r();
		current.digits[0] = copy.digits[i];
		current.remove_leading_zeros();
		int left = 0, right = base;
		int temp = 0;
		while (right >= left) {
			int middle = (left + right) / 2;
			BigInteger turn = big * BigInteger(middle);
			if (turn <= current) {
				temp = middle;
				left = middle + 1;
			}
			else right = middle - 1;
		}
		BigInteger turn = big * BigInteger(left);
		if (turn <= current) temp = left;
		digits[i] = temp;
		current -= big * BigInteger(temp);
	}
	sign = (sign != b.sign);
	remove_leading_zeros();
	return *this;
}
BigInteger BigInteger::operator/(const BigInteger& b_left) const {
	BigInteger copy = *this;
	copy /= b_left;
	return copy;
}
//---------------------------------------------ÎÑÒÀÒÊÈ--------------------------------------------------------------
BigInteger& BigInteger::operator%=(const BigInteger& b) {
	*this = *this - (*this / b) * b;
	return *this;
}


BigInteger BigInteger::operator%(const BigInteger& b_left) const {
	BigInteger copy = b_left - (const_cast<BigInteger&>(b_left) / *this) * (*this);
	return copy;
}

//-------------------------ÈÍÊĞÅÌÅÍÒÛ È ÄÅÊĞÅÌÅÍÒÛ--------------------------------------------------------------------
BigInteger& BigInteger::operator++() {
	*this += 1;
	return *this;
}
BigInteger BigInteger::operator++(int) {
	BigInteger copy = *this;
	*this += 1;
	return copy;
}
BigInteger& BigInteger::operator--() {
	*this -= 1;
	return *this;
}
BigInteger BigInteger::operator--(int) {
	BigInteger copy = *this;
	*this -= 1;
	return copy;
}

//-------------------------ÂÛÂÎÄ-------------------------------------------------------------------------------
std::ostream& operator <<(std::ostream& out, const BigInteger& b) {
	if (b.digits.size() == 0) out << 0;
	else {
		std::string str = b.toString();
		out << str;
	}
	return out;
}

