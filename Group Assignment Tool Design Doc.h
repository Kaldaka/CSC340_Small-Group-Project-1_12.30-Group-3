/*
Input:
    Two sections of students with their respective group data
    The number of unassigned students for each section
    Minimum and maximum group size (Depending on desired group size)
Output:
    The final random distribution of students across groups for each section
    The groups should meet the minimum and maximum size constraints
Algorithm:
    A. Assign unique numbers to each unassigned student
    - Create a vector to store the assigned numbers for each unassigned student
    - Assign unique numbers from 1 to the total number of unassigned students

    B. Adjust the number of groups in the dataset
    - Calculate the number of groups required to fit all students in a section
    - Add or remove groups from the dataset based on the calculated number of required groups
        - In the case of having to few or to many groups

    C. Assign unassigned students to random groups
    - While there are still unassigned students:
        1. Select a random student from the unassigned students list
        2. Select a random group from the group dataset
        3. If the selected group is not full, add the student to the group and remove them from the unassigned students list
        4. If the selected group is full, repeat step 2 until a non-full group is selected

    D. Adjust groups to meet the minimum group size
    - Identify groups with less than the minimum number of students
    - Combine small groups and redistribute students to meet the minimum group size
    - If a group is still smaller than the minimum size, either spread its students into other groups or fill it with students from other groups

    E. Clear empty groups from the dataset
        - In the case of having a student removed from a group in order to meet the min requirement
*/