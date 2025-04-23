public class Factorial {

    // Calculates the factorial of a given integer.
    public static long factorial(int n) {
        // Handle negative input
        if (n < 0) {
            return -1; // Return -1 to indicate an error
        } 
        // Base case: factorial of 0 is 1
        else if (n == 0) {
            return 1;
        } 
        // Calculate factorial for positive numbers
        else {
            long result = 1;
            for (int i = 1; i <= n; i++) {
                result *= i;
            }
            return result;
        }
    }

    public static void main(String[] args) {
        // Input number to calculate factorial
        int num = 5; 
        // Calculate factorial
        long fact = factorial(num);
        // Print result or error message
        if (fact != -1) {
            System.out.println("The factorial of " + num + " is " + fact);
        } else {
            System.out.println("Factorial is not defined for negative numbers.");
        }
    }
}