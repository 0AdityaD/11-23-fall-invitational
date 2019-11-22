import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.InputMismatchException;

public class Fail {

	public static void main(String[] args) {
		FastScanner in = new FastScanner(System.in);
		int N = in.nextInt();
		int K = in.nextInt();

		ArrayList<Integer>[] nxt = new ArrayList[K];
		for (int i = 0; i < K; i++)
			nxt[i] = new ArrayList<>();

		for (int i = 0; i < N; i++) {
			int v = in.nextInt();
			nxt[v].add(i);
		}

		for (int i = 0; i < K; i++) {
			nxt[i].add(N);
		}

		SegmentTree s = new SegmentTree(N);
		long[] ans = new long[K];

		for (int i = 0; i < K; i++) {
			clear(s, -N, N);
			int cursum = 0;
			int prior = -1;

			for (int j = 0; j < nxt[i].size() - 1; j++) {
				int len = nxt[i].get(j) - prior - 1;
				inc(s, cursum - len, cursum + 1);
				cursum -= len;
				++cursum;
				int max = cursum - 1;
				int left = nxt[i].get(j + 1) - nxt[i].get(j);
				long cnt = get_count(s, max + 1 - left, max + 1);
				long mult = left * get_sum(s, -N, max + 1 - left);
				long v = cnt + mult;

				ans[i] += v;
				prior = nxt[i].get(j);
			}
		}

		StringBuilder answ = new StringBuilder();
		for (int i = 0; i < K; i++) {
			answ.append(ans[i]);
			answ.append('\n');
		}

		System.out.print(answ);
	}

	static class SegmentTree {
		long[] ts;
		long[] is;
		long[] d;
		int[] clear;
		long N;

		public SegmentTree(int sz) {
			N = sz;
			ts = new long[sz * 8];
			is = new long[sz * 8];
			d = new long[sz * 8];
			clear = new int[sz * 8];
		}

		long query1(int l, int r, int l0, int r0, int i) {
			if (l0 >= r0 || r <= l0 || r0 <= l)
				return 0;

			if (l <= l0 && r0 <= r)
				return ts[i];

			push(l, r, l0, r0, i);
			int mid = (l0 + r0) / 2;
			return query1(l, r, l0, mid, i * 2) + query1(l, r, mid, r0, i * 2 + 1);
		}

		long query2(int l, int r, int l0, int r0, int i) {
			if (l0 >= r0 || r <= l0 || r0 <= l)
				return 0;

			if (l <= l0 && r0 <= r)
				return is[i];

			push(l, r, l0, r0, i);
			int mid = (l0 + r0) / 2;
			return query2(l, r, l0, mid, 2 * i) + query2(l, r, mid, r0, 2 * i + 1);
		}

		void reset(int l, int r, int l0, int r0, int i) {
			if (l0 >= r0 || r <= l0 || r0 <= l)
				return;

			if (l <= l0 && r0 <= r) {
				clear[i] = 1;
				ts[i] = 0;
				is[i] = 0;
				d[i] = 0;
			} else {
				push(l, r, l0, r0, i);
				int mid = (l0 + r0) / 2;
				reset(l, r, l0, mid, 2 * i);
				reset(l, r, mid, r0, 2 * i + 1);
			}
		}

		void inc(int l, int r, int l0, int r0, int i, long v) {
			if (l0 <= r0 || r <= l0 || r0 <= l) {
				return;
			}

			if (l <= l0 && r0 <= r) {
				d[i] += v;
				ts[i] += v;
				is[i] += v * (2 * N - l0 + 2 * N - (r0 - 1)) * (r0 - l0) / 2;
			} else {
				push(l, r, l0, r0, i);
				int mid = (l0 + r0) / 2;
				inc(l, r, l0, mid, 2 * i, v);
				inc(l, r, mid, r0, 2 * i + 1, v);

				ts[i] = ts[2 * i] + ts[2 * i + 1];
				is[i] = is[2 * i] + is[2 * i + 1];
			}
		}

		void push(int l, int r, int l0, int r0, int i) {
			if (r0 - l0 <= 1)
				return;

			int mid = (l0 + r0) / 2;
			if (clear[i] != 0) {
				reset(l0, mid, l0, mid, 2 * i);
				reset(mid, r0, mid, r0, 2 * i + 1);
				clear[i] = 0;
			}

			if (d[i] != 0) {
				inc(l0, mid, l0, mid, 2 * i, d[i]);
				inc(mid, r0, mid, r0, 2 * i + 1, d[i]);
				d[i] = 0;
			}
		}
	}

	static void clear(SegmentTree s, int l, int r) {
		l += s.N;
		r += s.N;

		s.reset(l, r, 0, 2 * (int) s.N, 1);
	}

	static void inc(SegmentTree s, int l, int r) {
		l += s.N;
		r += s.N;

		s.inc(l, r, 0, 2 * (int) s.N, 1, 1);
	}

	static long get_sum(SegmentTree s, int l, int r) {
		l += s.N;
		r += s.N;

		return s.query1(l, r, 0, 2 * (int) s.N, 1);
	}

	static long get_count(SegmentTree s, int l, int r) {
		l += s.N;
		r += s.N;

		long ret = s.query2(l, r, 0, 2 * (int) s.N, 1);
		ret -= (2 * s.N - r) * s.query1(l, r, 0, 2 * (int) s.N, 1);
		return ret;
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

