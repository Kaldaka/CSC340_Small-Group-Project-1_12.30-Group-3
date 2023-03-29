#include <iostream>
#include <utility>
#include <vector>
#include <cstdlib>
#include <time.h>

//generate number to represent each unassigned student 1-numOfunassignedStudents
void assignNumbers(std::vector<int>& unassignedStudents, int numOfunassignedStudents);

//adjusts the number of groups in groupsData to the required amount to fit the number of students in class 
void adjustNumberOfGroups(std::vector<std::pair<int, int>>& groupsData, int numOfunassignedStudents, int numOfStudentInSec);

//assigns random students from unassignedStudents to random groups in groupsData
void assignToGroups(std::vector<std::pair<int, int>>& groupsData, std::vector<int>& unassignedStudents, int numOfStudentInSec);



int main(){
    using namespace std;
    const int SECTION1SIZE= 40; //number of students in section 1
    const int SECTION2SIZE= 45; //number of students in section 2

    //vector stores groups of section 1 as pairs, pair: groupnumber, number of student in group
    vector<pair<int, int>> Sec1Groups={{7,4},{2,3},{3,5},{4,5},{5,4},{6,4},{8,4},{9,4},{10,4}};

    //vector stores groups of section 2 as pairs, pair: groupnumber, number of student in group
    vector<pair<int, int>> Sec2Groups{{1,3},{2,4},{3,4},{4,4},{5,2},{6,4},{7,4},{8,4},{9,2},{11,4},{12,1}};

    vector<int> unassignedStudents1; //contains unassigned students in section 1, each student represented by a number
    vector<int> unassignedStudents2; //contains unassigned students in section 2, each student represented by a number

    int numOfunassignedStudents1;//number of unassigned students in section 1
    int numOfunassignedStudents2;//number of unassigned students in section 2
   
    numOfunassignedStudents1=3;//according to canvas
    numOfunassignedStudents2=8;//according to canvas

    // generate number to represent each unassigned student 1-numOfunassignedStudents
    assignNumbers(unassignedStudents1, numOfunassignedStudents1);//for section 1
    assignNumbers(unassignedStudents2, numOfunassignedStudents2);//for section 2

    //assign the unassigned students to groups
    cout<<"Section 1:"<<endl;
    assignToGroups(Sec1Groups, unassignedStudents1, SECTION1SIZE);//for section 1
    cout<<endl;
    cout<<"Section 2:"<<endl;
    assignToGroups(Sec2Groups, unassignedStudents2, SECTION2SIZE);//for section 2
    cout<<endl;
}



//generate number to represent each unassigned student 1-numOfunassignedStudents
void assignNumbers(std::vector<int>& unassignedStudents, int numOfunassignedStudents){
    for(int i =1; i<=numOfunassignedStudents; i++){
        unassignedStudents.push_back(i);
    }
}


//adjusts the number of groups in groupsData to the required amount to fit the number of students in class 
void adjustNumberOfGroups(std::vector<std::pair<int, int>>& groupsData, int numOfunassignedStudents, int numOfStudentInSec){
    int numNeededGroups;//number of groups needed to include all students in class
    numNeededGroups = numOfStudentInSec /5; 
    int numGroupsToAdd; //number of groups need be be added to groupsData
    numGroupsToAdd = numNeededGroups - groupsData.size();
    for (int i=0; i<numGroupsToAdd;i++){
        std::pair<int,int> newGroup;
        newGroup.first = groupsData.size()+1; //set the new group's number to the next availble group number
        newGroup.second = 0;// set the number of students in the new group to 0;
        groupsData.push_back(newGroup);
    }
}


//assigns random students from unassignedStudents to random groups in groupsData
void assignToGroups(std::vector<std::pair<int, int>>& groupsData, std::vector<int>& unassignedStudents, int numOfStudentInSec){
   adjustNumberOfGroups(groupsData, unassignedStudents.size(), numOfStudentInSec);
   int randomStudentIndex;// store random index for unassignedStudents;
   int randomGroupIndex;// store random index for groupsData
   srand(time(0));
   while (!unassignedStudents.empty()){
        randomStudentIndex = rand() %  unassignedStudents.size();//random index in unassignedStudents   
        randomGroupIndex = rand() %  groupsData.size();//random index in groupsData;
        
        while(groupsData[randomGroupIndex].second ==5){//while the chosen random group is full
            randomGroupIndex = rand() %  groupsData.size();//find a new random group
        }
        
        groupsData[randomGroupIndex].second++; //add student to the group
        std::cout<<"Student number "<<unassignedStudents[randomStudentIndex]<< " was added to group number " <<groupsData[randomGroupIndex].first <<".\n";
        unassignedStudents.erase (unassignedStudents.begin()+randomStudentIndex);//remove the chosen student from unassignedStudents
   }
}