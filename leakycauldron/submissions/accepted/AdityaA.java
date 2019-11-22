import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayDeque;
import java.util.InputMismatchException;

public class AdityaA {

	static int[][] depth;
	static boolean[][] vis;
	static int[][] marked;
	static int[] dr = new int[] { -1, 0, 1, 0 };
	static int[] dc = new int[] { 0, 1, 0, -1 };

	static void dfs(int r, int c, int h) {
		vis[r][c] = true;
		if (depth[r][c] <= h)
			marked[r][c] = 1;

		for (int i = 0; i < dr.length; i++) {
			int nxtR = r + dr[i];
			int nxtC = c + dc[i];
			if (nxtR >= 0 && nxtR < depth.length && nxtC >= 0 && nxtC < depth[0].length && !vis[nxtR][nxtC] && marked[r][c] > 0) {
				dfs(nxtR, nxtC, h);
			}
		}
	}

	static int maxHistogram(int[] row) {
		ArrayDeque<Integer> res = new ArrayDeque<>();

		int top;
		int maxArea = 0;
		int currArea = 0;

		int i = 0;
		while (i < row.length) {
			if (res.isEmpty() || row[res.peek()] <= row[i])
				res.push(i++);
			else {
				top = row[res.pop()];
				currArea = top * i;

				if (!res.isEmpty())
					currArea = top * (i - res.peek() - 1);

				maxArea = Math.max(currArea, maxArea);
			}
		}

		while (!res.isEmpty()) {
			top = row[res.pop()];
			currArea = top * i;
			if (!res.isEmpty())
				currArea = top * (i - res.peek() - 1);

			maxArea = Math.max(maxArea, currArea);
		}

		return maxArea;
	}

	static int maxRect() {
		int maxArea = maxHistogram(marked[0]);

		for (int i = 1; i < marked.length; i++) {
			for (int j = 0; j < marked[0].length; j++) {
				if (marked[i][j] > 0)
					marked[i][j] += marked[i - 1][j];
			}

			maxArea = Math.max(maxArea, maxHistogram(marked[i]));
		}

		return maxArea;
	}

	public static void main(String[] args) {
		FastScanner in = new FastScanner(System.in);
		int N = in.nextInt();
		int M = in.nextInt();
		int K = in.nextInt();

		depth = new int[N][M];

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < M; j++) {
				depth[i][j] = in.nextInt();
			}
		}

		for (int k = 0; k <= K; k++) {
			vis = new boolean[N][M];
			marked = new int[N][M];

			dfs(N / 2, M / 2, k);
			System.out.println(maxRect());
		}

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

