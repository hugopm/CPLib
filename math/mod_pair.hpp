#pragma once
#include "hl/math/mod_int.hpp"

template<int M1, int M2>
struct mod_pair {
	mod_int<M1> x1;
	mod_int<M2> x2;
	mod_pair() : x1(0), x2(0) { }
	mod_pair(const mod_int<M1> &m1, const mod_int<M2> &m2) : x1(m1), x2(m2) { }
	mod_pair(long long u) : x1(u), x2(u) { }
	mod_pair(long long u1, long long u2) : x1(u1), x2(u2) { }

	friend bool operator==(const mod_pair &a, const mod_pair &b) {
		return a.x1 == b.x1 && a.x2 == b.x2;
	}
	friend bool operator!=(const mod_pair &a, const mod_pair &b) {
		return a.x1 != b.x1 || a.x2 != b.x2;
	}

	friend bool operator<(const mod_pair &a, const mod_pair &b) {
		if (a.x1 != b.x1) {
			return a.x1 < b.x1;
		} else {
			return a.x2 < b.x2;
		}
	}

	mod_pair& operator+=(const mod_pair& m) {
		x1 += m.x1;
		x2 += m.x2;
		return *this;
	}

	mod_pair& operator-=(const mod_pair& m) {
		x1 -= m.x1;
		x2 -= m.x2;
		return *this;
	}

	mod_pair& operator*=(const mod_pair& m) {
		x1 *= m.x1;
		x2 *= m.x2;
		return *this;
	}

	friend mod_pair operator+(const mod_pair& a, const mod_pair &b) {
		return mod_pair(a) += mod_pair(b);
	}

	friend mod_pair operator-(const mod_pair& a, const mod_pair &b) {
		return mod_pair(a) -= mod_pair(b);
	}

	friend mod_pair operator*(const mod_pair& a, const mod_pair &b) {
		return mod_pair(a) *= mod_pair(b);
	}

	mod_pair fastpow(int k) {
		return mod_pair(x1.fastpow(k), x2.fastpow(k));
	}

	mod_pair inv() {
		return mod_pair(x1.inv(), x2.inv());
	}

	std::vector<mod_pair> all_pow(int k) {
		auto a1 = x1.all_pow(k);
		auto a2 = x2.all_pow(k);
		std::vector<mod_pair> res(k+1);
		for (int i = 0; i <= k; ++i) {
			res[i] = mod_pair(a1[i], a2[i]);
		}
		return res;
	}
};
