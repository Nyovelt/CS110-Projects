# Scenario 1:

Hit Rate: `0`

- What combination of parameters is producing the hit rate you observe? (Hint: Your answer should be the process of your calculation.)

 step_size $* 4$ $\bmod$ cache size  

- What is our hit rate if we increase Rep Count arbitrarily? Why?

0 Because all cache are flashed

- How could we modify our program parameters to maximize our hit rate?

$$ Step Size = Array Size = 128 (To ensure hit one address ), and Increase Repeat Count. $$

![image-20210511150655057](/Users/canarypwn/Library/Application Support/typora-user-images/image-20210511150655057.png)



 ![nQtTMS](https://oss.aaaab3n.moe/uPic/nQtTMS.png)

# Scenario 2:

Hit Rate: `0.75`
1. What combination of parameters is producing the hit rate you observe? (Hint: Your answer should be the process of your calculation.)

every block hit 3 of 4


2. What happens to our hit rate as Rep Count goes to infinity? Why?

-> 1

![C5u87X](https://oss.aaaab3n.moe/uPic/C5u87X.png)

No first miss

3. Suppose we have a program that uses a very large array and during each Rep, we apply a different operator to the elements of our array (e.g. if Rep Count = 1024, we apply 1024 different operations to each of the array elements). How can we restructure our program to achieve a hit rate like that achieved in this scenario? (Assume that the number of operations we apply to each element is very large and that the result for each element can be computed independently of the other elements.) What is this technique called?

Cache Blocking

# Scenario 3:
Hit Rate: 0.375

0-0.5

Arraysize = 8