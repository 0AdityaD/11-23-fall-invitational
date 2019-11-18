import java.io.IOException;
import java.io.InputStream;
import java.util.InputMismatchException;

public class Candies {

	static long MOD = 1000000007;

	static long modPow(long a, long p) {
		if (p == 0)
			return 1;

		long ret = modPow((a * a) % MOD, p / 2);

		if ((p & 1) == 1) {
			return (a * ret) % MOD;
		} else {
			return ret;
		}
	}

	static long modInv(long a) {
		return modPow(a, MOD - 2);
	}

	static long solve(int K) {
		long[] fact = new long[K + 1];
		long[] invFact = new long[K + 1];

		fact[0] = fact[1] = invFact[0] = invFact[1] = 1;
		for (int i = 2; i <= K; i++) {
			fact[i] = (i * fact[i - 1]) % MOD;
			invFact[i] = modInv(fact[i]);
		}

		long ans = 0;
		for (int len = 2; len <= K + 1; len++) {
			long curr = fact[K - 1];
			curr = (curr * invFact[len - 2]) % MOD;
			curr = (curr * invFact[K - len + 1]) % MOD;
			curr = (curr * fact[len - 1]) % MOD;
			curr = (curr * len) % MOD;
			ans = (ans + curr) % MOD;
		}

		return (K * ans) % MOD;
	}

	public static void main(String[] args) {
		FastScanner in = new FastScanner(System.in);
		int N = in.nextInt();
		System.out.println(solve(N));
	}

	// Matt Fontaine's Fast I/O
	static class FastScanner {
		private InputStream stream;
		private byte[] buf = new byte[1024];
		private int curChar;
		private int numChars;

		public FastScanner(InputStream stream) {
			this.stream = stream;
		}

		int read() {
			if (numChars == -1)
				throw new InputMismatchException();
			if (curChar >= numChars) {
				curChar = 0;
				try {
					numChars = stream.read(buf);
				} catch (IOException e) {
					throw new InputMismatchException();
				}
				if (numChars <= 0)
					return -1;
			}
			return buf[curChar++];
		}

		boolean isSpaceChar(int c) {
			return c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == -1;
		}

		boolean isEndline(int c) {
			return c == '\n' || c == '\r' || c == -1;
		}

		int nextInt() {
			return Integer.parseInt(next());
		}

		long nextLong() {
			return Long.parseLong(next());
		}

		double nextDouble() {
			return Double.parseDouble(next());
		}

		String next() {
			int c = read();
			while (isSpaceChar(c))
				c = read();
			StringBuilder res = new StringBuilder();
			do {
				res.appendCodePoint(c);
				c = read();
			} while (!isSpaceChar(c));
			return res.toString();
		}

		String nextLine() {
			int c = read();
			while (isEndline(c))
				c = read();
			StringBuilder res = new StringBuilder();
			do {
				res.appendCodePoint(c);
				c = read();
			} while (!isEndline(c));
			return res.toString();
		}
	}
}

