![performance_checking-10](https://github.com/user-attachments/assets/3aa5cf96-9a60-4263-88d5-618c22aa765e)
Number of Rows: 10

Execution Time: 1.600000 microseconds 

Average run time: 0.053333 microseconds


![performance_checking-100](https://github.com/user-attachments/assets/6f3bc953-a441-43e4-b97e-e68029bf84cb)
Number of Rows: 100

Execution Time: 8.800000 microseconds

Average run time: 0.293333 microseconds


![performance_checking-1000](https://github.com/user-attachments/assets/c5cb9e40-18c6-4007-8cde-6c8baf5010ad)
Number of Rows: 1000

Execution Time: 80.900000 microseconds

Average run time: 2.696667 microseconds


![performance_checking-10000](https://github.com/user-attachments/assets/a8857cbd-1619-4f56-8514-86aa8694ed81)
Number of Rows: 10000

Execution Time: 801.600000 microseconds

Average run time: 26.720000 microseconds

To record the time of execution, the Windows.h library was used to record the time in microseconds. The reason why execution times are very fast is because assembly did most of the heavy lifting in the computational portion of the code. C is a higher-level language and in terms of execution times assembly would be faster as there are less convertions/translations required to make assmbly code into machine code unlike C. 

As for the performance of the code, it is observed that there is a linear relationship between input size and execution time as the input size increases by a factor of 10, the execution time also increases by a factor of 10.
