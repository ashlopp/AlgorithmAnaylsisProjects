# Authors: Ashley Lopez & Nick Giaccio                          #
# Date: 9/10                                                    #
# Assignment: Project 2                                         #
# description: This program takes input from the user and will  #
# tell the user if the number they entire is prime, make a new  #
# n bit prime number or encrypt and decrypt a message           #
# How to use: run code using ptython and use options to do      #
# calculations                                                  #
#################################################################
#all the computations for HW 1 shall be done using binary arithmetic
# only the user input and the final output will be in decimal.
# dec2bin and bin2dec convert between binary and decimal.

# functions provided: Add, Mult, Divide and many supporting functions such as
# Compare to compare two unbounded integers, bin2dec and dec2bin etc.

# missing functions: subtraction, Problem1, Problem2, Problem3 and the main function
# for user interface

import random
import sys
import time

sys.setrecursionlimit(10000000)

#from random import *

def shift(A, n):
    if n == 0:
        return A
    return [0]+shift(A, n-1)
    
def mult(X, Y):
    # mutiplies two arrays of binary numbers
    # with LSB stored in index 0
    if zero(Y):
        return [0]
    Z = mult(X, div2(Y))
    if even(Y):
        return add(Z, Z)
    else:
        return add(X, add(Z, Z))

def Mult(X, Y):
    X1 = dec2bin(X)
    Y1 = dec2bin(Y)
    return bin2dec(mult(X1,Y1))

def zero(X):
    # test if the input binary number is 0
    # we use both [] and [0, 0, ..., 0] to represent 0
    if len(X) == 0:
        return True
    else:
        for j in range(len(X)):
            if X[j] == 1:
                return False
    return True

def div2(Y):
    if len(Y) == 0:
        return Y
    else:
        return Y[1:]

def even(X):
    if ((len(X) == 0) or (X[0] == 0)):
        return True
    else:
        return False


def add(A, B):
    A1 = A[:]
    B1 = B[:]
    n = len(A1)
    m = len(B1)
    if n < m:
        for j in range(len(B1)-len(A1)):
            A1.append(0)
    else:
        for j in range(len(A1)-len(B1)):
            B1.append(0)
    N = max(m, n)
    C = []
    carry = 0
    for j in range(N):
        C.append(exc_or(A1[j], B1[j], carry))
        carry = nextcarry(carry, A1[j], B1[j])
    if carry == 1:
        C.append(carry)
    return C

def Add(A,B):
    return bin2dec(add(dec2bin(A), dec2bin(B)))

def exc_or(a, b, c):
    return (a ^ (b ^ c))

def nextcarry(a, b, c):
    if ((a & b) | (b & c) | (c & a)):
        return 1
    else:
        return 0 
        
def bin2dec(A):
    if len(A) == 0:
        return 0
    val = A[0]
    pow = 2
    for j in range(1, len(A)):
        val = val + pow * A[j]
        pow = pow * 2
    return val

def reverse(A):
    B = A[::-1]
    return B

def trim(A):
    if len(A) == 0:
        return A
    A1 = reverse(A)
    while ((not (len(A1) == 0)) and (A1[0] == 0)):
        A1.pop(0)
    return reverse(A1)


def compare(A, B):
    # compares A and B outputs 1 if A > B, 2 if B > A and 0 if A == B
    A1 = reverse(trim(A))
    A2 = reverse(trim(B))
    if len(A1) > len(A2):
        return 1
    elif len(A1) < len(A2):
        return 2
    else:
        for j in range(len(A1)):
            if A1[j] > A2[j]:
                return 1
            elif A1[j] < A2[j]:
                return 2
        return 0

def Compare(A, B):
    return bin2dec(compare(dec2bin(A), dec2bin(B)))

def dec2bin(n):
    if n == 0:
        return []
    m = n/2
    A = dec2bin(m)
    fbit = n % 2
    return [fbit] + A

def map(v):
    if v==[]:
        return '0'
    elif v ==[0]:
        return '0'
    elif v == [1]:
        return '1'
    elif v == [0,1]:
        return '2'
    elif v == [1,1]:
        return '3'
    elif v == [0,0,1]:
        return '4'
    elif v == [1,0,1]:
        return '5'
    elif v == [0,1,1]:
        return '6'
    elif v == [1,1,1]:
        return '7'
    elif v == [0,0,0,1]:
        return '8'
    elif v == [1,0,0,1]:
        return '9'   
        
def bin2dec1(n):
    if len(n) <= 3:
        return map(n)
    else:
        temp1, temp2 = divide(n, [0,1,0,1])
        return bin2dec1(trim(temp1)) + map(trim(temp2))

def divide(X, Y):
    # finds quotient and remainder when A is divided by B
    if zero(X):
        return ([],[])
    (q,r) = divide(div2(X), Y)
    q = add(q, q)
    r = add(r, r)
    if (not even(X)):
        r = add(r,[1])
    if (not compare(r,Y)== 2):
        r = sub(r, Y)
        q = add(q, [1])
    return (q,r)

def Divide(X, Y):
    (q,r) = divide(dec2bin(X), dec2bin(Y))
    return (bin2dec(q), bin2dec(r))

#--------------------------- Project 1 code ------------------------------------------------------------

def sub (x, y): # This is the function that does the subtracting once its in binary - used by other functions
    #created temp variables to hold to the flipped b value and the final answer
    temp_b = []
    answer = []
    #makes the binary numbers have the same number of bits
    if (len(x) > len(y)):
        for i in range (len(x) - len(y)):
            y.append(0)
    elif (len(y) > len(x)):
        for i in range (len(y) - len(x)):
            x.append(0)
    x = x + [0]
    y = y + [0]
    length = len(x)
    #loop that makes b become the inverse for 2's complement, and then stores
    #it in temp_b 
    for i in range (len(y)):
        if(y[i] == 1):
            temp_b.append(0)
        elif(y[i] == 0):
            temp_b.append(1)
    #makes the add one happen in the add function because it cant add a string 
    #and an int 
    temp_b = add(temp_b, [1])
    answer = add(x, temp_b)
    if (len(answer) > length):
        answer = answer[:len(answer) - 2]
    return (answer)

def subtract(x, y): # This is the function the user uses when they want to 
    #subtract from the terminal.
    #turns the numbers into binary and then calls the sub function to do the subtraction
    answer = sub(dec2bin(x), dec2bin(y))
    if (answer[len(answer) - 1] == 0):
        return str(bin2dec(answer))
    #flips the bits so we can still do two's complement 
    elif (answer[len(answer) - 1] == 1):
        for i in range(len(answer)):
            if (answer[i] == 0):
                answer[i] = 1
            elif (answer[i] == 1):
                answer[i] = 0
        #adds one for two's complement 
        answer = add(answer, [1])
        #puts negative is subtraction causes a negative number 
        return '-' + str(bin2dec(answer))
    else:
        return "Error subtract"

def gcd(x, y):
    #makes the gcd to help problem 3 simplify the fraction
    if (zero(y)):
        return x
    newx = divide(x, y)
    answer = gcd(y, newx[1])
    return answer

def problem1(A, B, C, D):
    #takes the A and raises it to the power of B 
    #takes C and raises it to the power of D
    # then takes the difference of both functions by using the subtraction function
    a = dec2bin(A)
    first = [1]
    for i in range(B): # exponentiation
        first = mult(first, a)
    c = dec2bin(C)
    second = [1]
    for i in range(D): # exponentiation
        second = mult(second, c)
    #takes the new numbers that were created from the exponential arthmetic and then
    #subtracts those two numbers to give us the answer
    answer = subtract(bin2dec(first), bin2dec(second))
    return answer

def problem2(A, B, C, D):
    #outputs the quotient and the remainder (q,r) when A^B / C^D

    #changes the number to decimal
    a = dec2bin(A)
    first = [1]
    for i in range(B): # exponentiation
        first = mult(first, a)
    c = dec2bin(C)
    second = [1]
    for i in range(D): # exponentiation
        second = mult(second, c)
    #takes the new numbers and then calls the divide function so we can get the 
    #quotient and the remainder
    answer = Divide(bin2dec(first), bin2dec(second))
    return answer

def problem3(A):
    #creates the numerator and denominator arrays to store the numbers 
    top = [1]
    bottom = [1]
    #does the math that is needed for fractions to work correctly 
    for i in range(2, A + 1):
        top = add(mult(top, dec2bin(i)), mult(bottom,[1]))
        bottom = mult(bottom, dec2bin(i))
    #makes the gcd of top and bottom to simplify the fraction
    answer = gcd(top, bottom)
    top1 = divide(top, answer)
    bottom1 = divide(bottom, answer)
    #changes the binary number back to decimal and then returns the answer 
    return (bin2dec(top1[0]), bin2dec(bottom1[0]))
#---------------------------- Project 2 -----------------------------------------------------------
def modexp(A, B, N):
    #i think t9his is working properly now..? i dont understand how to do the math 9/28 @4:34
    #inputs = binary, return = binary
    if(zero(B)):
        return[1]
    else:
        B1 = div2(B)
        z = modexp(A, B1, N)
        if(even(B)):
            (q, r) = divide(mult(z, z), N)
            return r
        else:
            (q, r) = divide(mult(A, mult(z, z)), N)
            return r

def primality(n):
    #believe this is working correcly 9/29
    a = random.randint(2, n)
    #a = a ** (n - 1)
   # Doesnt work properly. example 3 is prime and returned no
    check = modexp(dec2bin(a), dec2bin(n - 1), dec2bin(n))
    if(compare(check, [1]) == 0):
        return "yes"
    else:
        return "no"

def primality2(n, k):
    for i in range (k):
        a = primality(n)
        if (a == "no"):
            return "no"
    return "yes"

def primality3(n, k):
    #problem 1 project 2
    newn = dec2bin(n)
    two = dec2bin(2)
    three = dec2bin(3)
    five = dec2bin(5)
    seven = dec2bin(7)
    
    (q, r) = divide(newn, two)
    if (zero(r)):
       return "no it is not prime"
  
    (q, r) = divide(newn, three)
    if(zero(r)):
        return "no it is not prime"
    
    (q, r) = divide(newn, five)
    if(zero(r)):
        return "no it is not prime"
    
    (q, r) = divide(newn, seven)
    if(zero(r)):
        return "no it is not prime"

    #for i in range(k):
    prime = primality2(n, k)
    if(prime == "no"):
        return "no it is not prime"
    return "Yes it is prime" 

def proj2prob2(n, k):
    if (n > 50):
        n = int(input("n is too big, please enter another number: "))
    #generate a random number with n bits
    v = []
    for i in range(n - 2):
        bit = random.randint(0, 2)
        v.append(bit) 
    v= v + [1]
    v.reverse()
    v = v + [1]
    v.reverse()
    v = bin2dec(v)
    #need to keep calling this if answer isnt prime until we generate a prime number
    #use recursion and if statements 
    answer = primality3(v, k)
    if(answer == "Yes it is prime"):
        return v
    return proj2prob2(n, k)

def proj2prob3(n, k):
    #p and q are decimal
    p = proj2prob2(n, k)
    while (len(dec2bin(p)) != n):
        p = proj2prob2(n, k)
    q = proj2prob2(n, k)
    while(len(dec2bin(q)) != n):
        q = proj2prob2(n, k)
    #newp and newq are binary 
    newp = dec2bin(p)
    newq = dec2bin(q)
    # N is binary 
    N = mult(newp, newq)
    e = []
    for i in range(n):
        bit = random.randint(0,2)
        e.append(bit)
    # e is  decimal
    #e = bin2dec(e)
    newp = sub(newp, [1])
    newq = sub(newq, [1])
    #number is binary
    number = mult(newp, newq)
    #checkgcd is a list containing (x,y,d,s)
    (x, y, d, s) = egcd(e, number)
    while(compare(d, [1]) != 0):
        e = []
        for i in range(n):
            bit = random.randint(0,2)
            e.append(bit)
        #e = bin2dec(newe)
        #checkgcd is a list containing (x,y,d,s)
        (x, y, d, s) = egcd(e, number)


    #d is binary 
    D = modinv(e, number)
    print(bin2dec(N), bin2dec(e), bin2dec(D))
    M = int(input("Enter an Integer: " ))
    #use N & E to encrypt M
    code = encrypt(N, e, M)
    print("encrypt")
    print(bin2dec(code))
    decode = decrypt(code, D, N)
    print("decode" )
    return bin2dec(decode)

def encrypt(n, e, m):
    #inputs: n,e = binary/m = decimal, return = binary
    encrypt = modexp(dec2bin(m), e, n)
    return encrypt

def decrypt(m, D, N):
    #inputs = binary
    decrypt = modexp(m, D, N)
    return decrypt
        
def egcd(a, b):
    # inputs: a,b = binary, returns: a,y,d = binary/s = decimal
    if (zero(b) == True):
        return([1], [0], a, 0)
    (q, r) = divide(a, b)
    (x, y, d, s) = egcd(b, r)
    if ((s == 0) and (compare([1], x) == 0)):
        return ([0], [1], d, 0)
    if((s == 0) and  (compare([0], x) == 0)):
        return([1], mult(q, y), d, 2)
    if(s == 2):
        return(y, add(x, mult(q, y)), d, 1)
    if(s == 1):
        return(y, add(x, mult(q, y)), d, 2)

def modinv(a, n):
    #honestly dont even know where to start with this code.
    # inputs: a,n = binary, return: temp = binary
    (x, y, d, s) = egcd(a, n)
    if compare(d, [1]) != 0:
        return []
    (q,r) = divide(x, n)
    #temp = r
    if (s == 2):
        return r
    else:
        #(q, r) = divide(x, n)
        temp = sub(mult(add(q, [1]), n), x)
        return temp

def main():
    print('1: takes in two parameters, N & K, tells you if N is prime')
    print('2: takes two inputs, makes a random number that is going to be odd and tells you if it is prime')
    print('3: encyption and decryption of a message, using 2 parameters to know how long the number is')
    print ('4: exit')
    option = int(input('Please choose an option - 1, 2, 3 or 4: '))
    #takes the input and makes it do the appropriate calculation until the user enters a '4'
    while(option == 1 or option == 2 or option == 3):
        varN = int(input('N: '))
        varK = int(input('K: '))
        if (option == 1):
            answer = primality3(varN, varK)
        if(option == 2):
           answer = proj2prob2(varN,varK)
        if (option == 3):
            answer = proj2prob3(varN, varK)
        print(answer)
        option = int (input('Please choose again - 1, 2, 3, 4: '))
    #once the user chooses '4' then it will end the program 
    if (option == 4):
        print('BYE! SEE YOU LATER, DUDE')
main()
