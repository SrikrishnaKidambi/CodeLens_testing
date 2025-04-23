def factorial(n):
  """
  This function calculates the factorial of a non-negative integer.

  Args:
    n: An integer greater than or equal to 0.

  Returns:
    The factorial of n.
    Returns 1 if n is 0.
    Returns None if n is negative.
  """
  if n < 0:
    return None
  elif n == 0:
    return 1
  else:
    result = 1
    for i in range(1, n + 1):
      result *= i
    return result

# Get input from the user
num = int(input("Enter a non-negative integer: "))

# Calculate and print the factorial
fact = factorial(num)
if fact is not None:
  print(f"The factorial of {num} is {fact}")
else:
  print("Factorial is not defined for negative numbers.")