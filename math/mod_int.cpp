template<const int MOD>
struct mod_int
{
	long long x;
	mod_int() : x(0) { }
	mod_int(long long u) : x(u) {
		if (x >= MOD || x < 0) {
			x %= MOD;
			if (x < 0) {
				x += MOD;
			}
		}
	}
	mod_int(const mod_int &m) : x(m.x) { }
	mod_int& operator=(const mod_int &m) {
		x = m.x;
		return *this;
	}

	friend bool operator==(const mod_int& a, const mod_int& b) {
		return a.x == b.x;
	}

	friend bool operator!=(const mod_int& a, const mod_int& b) {
		return a.x != b.x;
	}

	friend bool operator<(const mod_int& a, const mod_int& b) {
		return a.x < b.x;
	}

	friend std::ostream& operator << (std::ostream& out, const mod_int& a) {
		return out << a.x;
	}

	mod_int& operator+=(const mod_int& m) {
		x += m.x;
		if (x >= MOD) {
			x -= MOD;
		}
		return *this;
	}

	mod_int& operator-=(const mod_int& m) {
		x -= m.x;
		if (x < 0) {
			x += MOD;
		}
		return *this;
	}

	mod_int& operator*=(const mod_int& m) {
		x = (1ll * x * m.x) % MOD;
		return *this;
	}	

	friend mod_int operator-(const mod_int &a) {
		mod_int res(a);
		if (res.x != 0) {
			res.x = MOD-res.x;
		}
		return res;
	}

	friend mod_int operator+(const mod_int& a, const mod_int &b) {
		return mod_int(a) += mod_int(b);
	}

	friend mod_int operator-(const mod_int& a, const mod_int &b) {
		return mod_int(a) -= mod_int(b);
	}

	friend mod_int operator*(const mod_int& a, const mod_int &b) {
		return mod_int(a) *= mod_int(b);
	}

	mod_int f2() {
		return mod_int(x) += mod_int(x);
	}

	static long long fp(long long u, long long k) {
		long long res = 1;
		while (k > 0) {
			if (k & 1) {
				res = (res * u) % MOD;
			}
			u = (u * u) % MOD;
			k /= 2;
		}
		return res;
	}

	mod_int fastpow(long long k) {
		return mod_int(fp(x, k));
	}
	mod_int inv() {
		return mod_int(fp(x, MOD-2));
	}

	static mod_int sign(long long k) {
		return ((k & 1) ? mod_int(MOD - 1) : mod_int(1));
	}

};

