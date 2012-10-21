package library;

import java.util.LinkedList;
import java.util.List;

public class NumberTheory {

	static char[] alphabet = {	'0','1','2','3','4','5','6','7','8','9',
		'a','b','c','d','e','f','g','h','i','j','k','l','m',
		'n','o','p','q','r','s','t','u','v','w','x','y','y'};

	static boolean[] primeciv;
	static List<Integer>primes;

	/**
	 * Euclids Algorithm
	 * @param a
	 * @param b
	 * @return
	 */
	public static int greatestCommonDivisor(int a, int b){
		int tmp=a;
		a = Math.max(a, b);
		b = Math.min(tmp, b);
		while (b!=0){
			tmp=b;
			b=a%b;
			a=tmp;		
		}
		return a;
	}

	public static int leastCommonMultiple(int a, int b){
		return Math.abs(a*b)/greatestCommonDivisor(a,b);
	}

	/**
	 * Finds the number of factors that a particular number has.
	 * The formula for this is:
	 * 		let a[i] be the number of times the ith prime number appears in the result.
	 * 		for instance, 24 = 2^3 * 3
	 * 		
	 * 		# factors = (a[1]+1)*(a[2]+1)*(a[3]+1)....
	 * Requires a prime civ to be created first!!!!
	 * @param num
	 * @return
	 */
	public static long numFactors(long num){
		long numPrimes  = 1;
		for(int prime : primes){
			if(num==1)
				break;
			int count = 1;
			while(num%prime ==0){
				num/=prime;
				count++;
			}
			numPrimes*=count;
		}
		return numPrimes;
	}

	/**
	 * Creates a prime civ
	 * @param to
	 */
	public static void primeciv(int to){
		primes=new LinkedList<Integer>();
		primeciv = new boolean[to+1];
		primeciv[1]=true;

		for(int start=2; start < to+1; start++)
			if (!primeciv[start]){
				primes.add(start);
				int current = start*2;
				while (current<to+1){
					primeciv[current]=true;
					current+=start;
				}
			}				
	}
	/**
	 * Determines if a number is prime using a premade civ.
	 * First generate the civ.
	 * @param num
	 * @param civ
	 * @return
	 */
	public static boolean isPrime(long num, boolean[] civ){
		if (num<civ.length)
			return !civ[(int)num];
		else if(num <= Math.pow(civ.length,2)){
			for(int i: primes)
				if (num%i==0)
					return false;
			return true;
		}
		else{
			System.out.println("cannot determine if prime");
			System.out.println(Math.pow(civ.length,2));
			return false;
		}
	}

	/**
	 * Converts a base 10 number to unsigned binary
	 * @param number
	 * @return
	 */
	public static String toBinary(long number){
		String a="";
		long mod=2;
		while(number!=0){
			a+=(number%mod)*2/mod;
			number-=(number%mod);
			mod*=2;
		}
		a=new StringBuffer(a).reverse().toString();
		return a;
	}

	/**
	 * Converts a base 10 number to two's complement
	 * @param number
	 * @return
	 */
	public static String to2scomplementBinary(long number){
		boolean neg=number<0;
		number*=neg?-1:1;
		number-=neg?1:0;
		String a="";
		long mod=2;
		while(number!=0){
			a+=((number%mod)*2/mod)==1?neg?0:1:neg?1:0;
			number-=(number%mod);
			mod*=2;
		}
		a+=neg?"1":"0";
		a=new StringBuffer(a).reverse().toString();
		return a;
	}

	/**
	 * Converts an unsigned binary number to base 10
	 * @param binary
	 * @return
	 */
	public static long fromBinary(String binary){
		long a=0;
		int length=binary.length()-1;
		for (int i=length; i >=0 ; i--){
			a+=(binary.charAt(i)=='0'?0:1)*Math.pow(2, length-i);
		}
		return a;
	}

	/**
	 * Converts a two's-complement binary number to base 10
	 * @param binary
	 * @return
	 */
	public static long from2scomplementBinary(String binary){
		long a=0;
		int length=binary.length()-1;
		boolean neg=binary.charAt(0)=='1';
		for (int i=length; i >0 ; i--){
			a+=(neg?binary.charAt(i)=='0'?1:0:binary.charAt(i)=='0'?0:1)*Math.pow(2, length-i);
		}
		a+=neg?1:0;
		a*=neg?-1:1;

		return a;
	}

	/**
	 * Converts a base10 number to any other base
	 * @param number
	 * @param base
	 * @return
	 */
	public static String toBase(long number, int base){
		if (base>alphabet.length){
			System.out.println("cannot represent accurately");
			return "";
		}

		String a="";
		long mod=base;
		while(number!=0){
			a+=alphabet[(int) ((number%mod)*base/mod)];
			number-=(number%mod);
			mod*=base;
		}
		a=new StringBuffer(a).reverse().toString();
		return a;
	}

	/**
	 * Converts a number in any base to base 10
	 * @param binary
	 * @param base
	 * @return
	 */
	public static long fromBase(String binary, int base){
		binary=binary.toLowerCase();
		int length = binary.length()-1;
		long a=0;
		for (int i=length; i >=0; i--){
			for(int j =0; j < alphabet.length; j++)
				if (binary.charAt(i)==alphabet[j]){
					a+=j*Math.pow(base, length-i);
					break;
				}
		}
		return a;
	}


	public static void main(String[] args) {

		System.out.println(greatestCommonDivisor(462,1071));
		System.out.println(leastCommonMultiple(462,1071));
		long time = System.currentTimeMillis();
		primeciv((int)(Math.sqrt(2147483647)));
		long time2=System.currentTimeMillis();

		for (int i =0; i < 100; i++){
			if (!primeciv[i])
				System.out.println(i+ " "+primeciv[i]);
		}

		System.out.println(isPrime(2147483647,primeciv));

		//System.out.println("td: "+(time2-time));
		//System.out.println(toBinary(41));
		System.out.println(fromBinary("101001"));
		/*
		System.out.println(toBase(11213,15));
		System.out.println(fromBase("34C8",15));
		 */

		System.out.println(from2scomplementBinary("1101001"));
		System.out.println(from2scomplementBinary("1101001"));
		System.out.println(from2scomplementBinary("1111111"));

		System.out.println(to2scomplementBinary(-23));
	}

}
