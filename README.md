# Computorv1

## Description
Computorv1 is a program that takes in a cubic or lower equation and solves it, or simplifies any polynomial expression.

## Getting Started
To compile and run the program, use the following commands:

- **Bonus Version (Full Features):**
  ```bash
  make bonus
  ./computorv1_bonus [input]
  ```

- **Standard Version (Full Features):**
    ```bash
    make
    ./computorv1 [input]
    ```

(If the input argument is left empty, the program will prompt you to enter one.)

## AI Disclosure
Artificial Intelligence was used to make this README file and nothing else.

## Operation Hierarchy
The expression parser evaluates operations in the following strict order of precedence (from highest to lowest):

-Brackets ()
<!--  -->
-Exponentiation ^

-Unary negation or addition +, -

-Implied multiplication   (no operator symbol)

-Multiplication and division *, /

-Addition and subtraction +, -

addition/subtraction and unary versions mixing is not allowed, in general, 2 operators in a row will result in an error, no 1--1 for you