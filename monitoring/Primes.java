import java.text.NumberFormat;
import java.util.LinkedList;

/**
 * Use link list to find all prime numbers from two to a billion.
 * Used to generate trafic to test monitoring of HPC resources.
 * 
 * @author Phillip Benoit
 *
 */
public class Primes {

	/**
	 * entry point
	 */
	public static void main(String[] args) {

		//used value because known number of primes
		int max = 1000000000;
		
		//number of divides for progress monitoring
		int slice = 100;
		
		//prevent making slice sizes that will not work
		if (max % slice != 0) {
			System.err.println("Slice did not evenly divide the max");
			System.exit(-1);
		}
		
		//percent formatting for monitoring
		NumberFormat percent = NumberFormat.getPercentInstance();
		percent.setMinimumFractionDigits(0);
		percent.setMaximumFractionDigits(1);

		//used for progress output
		int step = max/slice;

		//use linklist to store primes
		LinkedList<Integer> primes = new LinkedList<Integer>();

		//start with 2 as a known prime number
		primes.add(2);
		
		//number being tested for "primeness"
		//start x at the next number
		int x = 3;

		//used to print progress bar
		int y = step;

		//used to track progress
		for (; y <= max; y+=step) {

			//loop through numbers to test
			for (; x <= y; x+=2) {

				//use square root of possible prime as an upper limit to test
				int sqrt = (int) Math.sqrt(x);

				//step through list of prime numbers
				for (Integer test_number:primes) {

					//if the test number is larger than the square root, x is prime
					if (test_number > sqrt) {
						primes.add(x);
						break;
					}

					//if x is evenly divisible by a prime number, it is not prime
					if (x % test_number == 0) break;
				}
			}
			
			//monitoring output
			System.out.println(java.time.LocalDateTime.now() + " " + percent.
					format((double)x/max) + " Primes up to " + (x-1) + " found so "
							+ "far: " + primes.size());

		}

		//print number found
		System.out.println("Number of prime found from 2 - "
				+ "" + max + " = " + primes.size());

		//test against known list size
		// https://primes.utm.edu/howmany.html
		String correct = 50847534 == primes.size() ? "right number of primes "
				+ "found" : "wrong number of primes found";

		//print results
		System.out.println(correct);
	}

}

