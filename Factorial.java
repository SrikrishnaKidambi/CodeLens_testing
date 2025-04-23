public class Factorial {

    public static long factorial(int n) {
        if (n < 0) {
            return -1; // Indicate an error for negative input
        } else if (n == 0) {
            return 1;
        } else {
            long result = 1;
            for (int i = 1; i <= n; i++) {
                result *= i;
            }
            return result;
        }
    }

    public static void main(String[] args) {
        int num = 5; // You can change this value to calculate the factorial of a different number
        long fact = factorial(num);
        if (fact != -1) {
            System.out.println("The factorial of " + num + " is " + fact);
        } else {
            System.out.println("Factorial is not defined for negative numbers.");
        }
    }
} 