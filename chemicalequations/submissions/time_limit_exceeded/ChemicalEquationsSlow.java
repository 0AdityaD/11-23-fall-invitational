import java.io.IOException;
import java.io.InputStream;
import java.util.InputMismatchException;
import java.util.TreeMap;

public class ChemicalEquationsSlow {

	public static void main(String[] args) {
		FastScanner in = new FastScanner(System.in);
		int N = in.nextInt();
		TreeMap<String, TreeMap<String, Integer>> eqn = new TreeMap<>();

		for (int i = 0; i < N; i++) {
			String name = in.next();
			TreeMap<String, Integer> place = new TreeMap<>();
			eqn.put(name, place);

			int ri = in.nextInt();
			for (int j = 0; j < ri; j++) {
				int q = in.nextInt();
				String reactant = in.next();
				place.put(reactant, q);
			}
		}

		String desired = in.next();
		TreeMap<String, Integer> res = simplify(desired, eqn);

		if (res == null) {
			System.out.println(desired + " " + 1);
		} else {
			for (String reactant : res.keySet()) {
				System.out.println(reactant + " " + res.get(reactant));
			}
		}
	}

	static TreeMap<String, Integer> simplify(String curr, TreeMap<String, TreeMap<String, Integer>> eqn) {
		TreeMap<String, Integer> simplified = new TreeMap<>();
		TreeMap<String, Integer> prev = eqn.get(curr);

		if (prev == null)
			return null;

		for (String reactant : prev.keySet()) {
			int quantity = prev.get(reactant);
			TreeMap<String, Integer> sub = simplify(reactant, eqn);
			if (sub == null) {
				simplified.put(reactant, simplified.getOrDefault(reactant, 0) + quantity);
			} else {
				for (String subreactant : sub.keySet()) {
					simplified.put(subreactant,
							simplified.getOrDefault(subreactant, 0) + quantity * sub.get(subreactant));
				}
			}
		}

		return simplified;
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

