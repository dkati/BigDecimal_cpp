#include <iostream>
#include <string>
using namespace std;

class BigDecimal {

private:
	double mThisNum;
	int mDecimalPlaces;
	template <typename T>
	std::enable_if_t<(std::is_floating_point<T>::value), std::size_t>
		countDecimals(T v)
	{
		std::size_t decs = 0;
		v = std::abs(v);
		auto floored = v - std::floor(v);
		T basefactor = 10;
		T __CPUepsilon = std::numeric_limits<T>::epsilon() * floored;
		while ((floored > __CPUepsilon && floored < (1 - __CPUepsilon)) && decs < std::numeric_limits<T>::max_digits10)
		{
			floored = v * basefactor;
			floored = floored - std::floor(floored);
			basefactor *= 10;
			__CPUepsilon = std::numeric_limits<T>::epsilon() * v * basefactor;
			decs++;
		}

		return decs;
	}
public:
	BigDecimal() {}
	BigDecimal(std::string x) {
		mThisNum = std::stod(x);
	}
	BigDecimal(double x) {
		mThisNum = x;
	}

	inline double get() { return mThisNum; }
	inline void print() {
		cout.precision(countDecimals(mThisNum));
		cout << std::fixed << mThisNum << endl;
	}

	inline BigDecimal operator* (BigDecimal x) {
		BigDecimal z(this->mThisNum * x.get());
		return z;
	}

	inline BigDecimal operator+ (BigDecimal x) {
		BigDecimal z(this->mThisNum + x.get());
		return z;
	}

	inline BigDecimal operator- (BigDecimal x) {
		BigDecimal z(this->mThisNum - x.get());
		return z;
	}

	inline BigDecimal operator/ (BigDecimal x) {
		BigDecimal z(this->mThisNum / x.get());
		return z;
	}

	inline bool operator< (BigDecimal x) {
		return (mThisNum < x.get());
	}

	inline bool operator> (BigDecimal x) {
		return (mThisNum > x.get());
	}

	template <typename T>
	BigDecimal increaseBy(T v) {
		mThisNum += v;
		return *this;
	}

	template <typename T>
	BigDecimal decreaseBy(T v) {
		mThisNum -= v;
		return *this;
	}
};

int main()
{
	BigDecimal x(34.00000000001);
	BigDecimal y(22.00000000001);
	BigDecimal z("31.55555555");

	x.print();
	y.print();
	z.print();

	(x + y).print();
	(x * y).print();

	if (x > y) cout << "ok" << endl;

	x = x.increaseBy(4);

	x = x.increaseBy(3);

	x.print();

	return 0;
}


