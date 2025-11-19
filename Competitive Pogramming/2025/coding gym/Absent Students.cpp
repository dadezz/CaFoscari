/*
A professor calls out student IDs of students one by one while marking attendance. 
He notices that the number of students recorded in the attendance sheet is far more than the number of students who are actually present in the classes.

Hence, he decides to use a robot which can record the students' voices and keep track of which students have responded to attendance calls.

At the end of each session, the robot outputs the student IDs of the students who have responded to attendance calls. With this information, the professor needs your help to find out which students were absent.

Complete the function findTheAbsentStudents which takes in an integer array

denoting the student IDs recorded by the robot and returns the list of student IDs of the students which were absent in increasing order.

Input Format

The first line of input contains a single integer
denoting the number of students. The second line contains space-separated integers denoting the student IDs recorded by the robot. The students have IDs from to

, inclusive.

Constraints

    There is at least one absent student.

Output Format

Print a single line containing the student IDs of the students which were absent, space-separated and in increasing order.

Sample Input 0

10
1 2 2 3 4 5 2 8 9 10

Sample Output 0

6 7
*/
#include <iostream>
#include <vector>


void parse_input(int n, std::vector<bool>& present) {
    for (int i = 1; i <= n; ++i) {
        int id;
        std::cin >> id;
        present[id] = true;
    }
}

void print_absent_students(int n, const std::vector<bool>& present) {
     for (int i = 1; i <= n; ++i) {
        if (!present[i]) {
            std::cout << i << " ";
        }
    }
}


int main() { 
    int n;
    std::cin >> n;
    std::vector<bool> present(n + 1, false);
    
    parse_input(n, present);
    print_absent_students(n, present);
    return 0;
}