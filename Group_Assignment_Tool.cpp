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
void assignToGroups(std::vector<std::pair<int, int>>& groupsData, std::vector<int>& unassignedStudents, int numOfStudentInSec, int min, int max);

int main(){
    using namespace std;
    const int SECTION1SIZE= 40; //number of students in section 1
    const int SECTION2SIZE= 45; //number of students in section 2
    int min =3;
    int max=4;
    int numOfunassignedStudents1=6;
    int numOfunassignedStudents2=8;

    //vector stores groups of section 1 as pairs, pair: groupnumber, number of student in group
    vector<pair<int, int>> Sec1Groups={{7,3},{2,2},{3,1},{4,3},{5,1},{6,4},{8,2},{9,2},{10,1}};

    //vector stores groups of section 2 as pairs, pair: groupnumber, number of student in group
    vector<pair<int, int>> Sec2Groups{{1,3},{2,4},{3,4},{4,4},{5,2},{6,4},{7,4},{8,4},{9,2},{11,4},{12,1}};

    vector<int> unassignedStudents1; //to store unassigned students in section 1, each student represented by a number
    vector<int> unassignedStudents2; //to store unassigned students in section 2, each student represented by a number
   

    // generate number to represent each unassigned student 1-numOfunassignedStudents
    assignNumbers(unassignedStudents1, numOfunassignedStudents1);//for section 1
    assignNumbers(unassignedStudents2, numOfunassignedStudents2);//for section 2

    //assign the unassigned students to groups
    cout<<"Section 1:"<<endl;
    cout<<"----------"<<endl;
    cout<<"\nAdding random students to random groups..."<<endl;
    assignToGroups(Sec1Groups, unassignedStudents1, SECTION1SIZE,3,5);//for section 1
    cout<<"\n\nSection 2:"<<endl;
    cout<<"----------"<<endl;
    cout<<"\nAdding random students to random groups..."<<endl;
    assignToGroups(Sec2Groups, unassignedStudents2, SECTION2SIZE, 3, 5);//for section 2
    cout<<endl;
}



//generate number to represent each unassigned student 1-numOfunassignedStudents
void assignNumbers(std::vector<int>& unassignedStudents, int numOfunassignedStudents){
    for(int i =1; i<=numOfunassignedStudents; i++){
        unassignedStudents.push_back(i);
    }
}

void displayGroups(const std::vector<std::pair<int, int>> &groupsData){
    for(auto group: groupsData){
        std::cout<<"<"<<group.first<<","<<group.second<<">"<<std::endl;
    }
    std::cout<<std::endl;
}
void displayGroupspt(const std::vector<std::pair<int, int>*> &groupsData){
    for(auto group: groupsData){
        std::cout<<"<"<<group->first<<","<<group->second<<">  ";
    }
    std::cout<<std::endl;
}

void clearEmptyGroups(std::vector<std::pair<int, int>>& groupsData){
    for (int i = 0; i<groupsData.size();i++){
        if (groupsData[i].second==0){
            groupsData.erase(groupsData.begin()+i);
            i--;
        }
    }
}

//return the number of total empty spots in all groups except for the given group
int getEmptySpots(std::vector<std::pair<int, int>> groupsData, int groupNum, int max) {
    int sum;
    for (auto CurrGroup: groupsData){
        if (CurrGroup.first!=groupNum && CurrGroup.second!=0){
            sum+=max-CurrGroup.second;
        }
    }
    return sum;
}

//spread the given group's members into the other groups
void spreadGroup(std::vector<std::pair<int, int>>& groupsData, int max, std::pair<int, int>& group){
    while(group.second>0){
        for(int i = 0; i<groupsData.size() && group.second>0;i++) {
            if(group.first != groupsData[i].first && groupsData[i].second <max &&  groupsData[i].second!=0){
                groupsData[i].second++;
                group.second--;
                std::cout <<"Moved a student from group number " << group.first << " to group number "<<  groupsData[i].first<<std::endl;
            }
            
        }
    }
}

//fills the given groups with students from other groups
void fillGroup(std::vector<std::pair<int, int>>& groupsData, int min, std::pair<int, int>& group){
    while(group.second<min){
            for(auto currentGroup :groupsData) {
                if(group.first != currentGroup.first && currentGroup.second >min){
                    currentGroup.second--;
                    group.second++;
                    std::cout <<"Moved a student from group number " << currentGroup.first << " to group number "<< group.first <<std::endl;
                }
            }
        }
}

//combines all the gorups in the vector
//returns true if all groups are >= to min
//return false if otherwise. The unfinished group is located at the last element
bool combineGroups(std::vector<std::pair<int, int>*> &smallGroups,  int max){//time Complexity O(n*c1*c2)
    for(int i =0; i<smallGroups.size()-1; i++){
        while(i<smallGroups.size()-1 && smallGroups[i]->second>0 && smallGroups[i]->second<max ){//as long as current group not empty and not full
            //move from next group to current group
                smallGroups[i+1]->second--;
                smallGroups[i]->second++;
            std::cout <<"Moved a student from group number " << smallGroups[i+1]->first << " to group number "<<  smallGroups[i]->first<<std::endl;
            while (i<smallGroups.size()-1 && smallGroups[i+1]->second==0 ){// while next group got empty 
                smallGroups.erase(smallGroups.begin()+i+1);//delete empty group
            }  
        }
    }
    return true;
}

//adjusts the groups to to have the required min num of students
void adjustGroupsToMin(std::vector<std::pair<int, int>>& groupsData, int min, int max){//time complexity= O(3n)
    std::vector<std::pair<int, int>*> smallGroups; //stores pointers of groups with low num of students
    for(auto &group:groupsData){
        if (group.second<min){
            smallGroups.push_back(&group);
        }
    }
    if(smallGroups.size()==0){
        std::cout<<"\nNo Adjustments Needed!"<<std::endl;
        return;
    }
    if(smallGroups.size()>1){
        std::cout<<"_____________________________________________________"<<std::endl<<std::endl;
        std::cout<<"The following groups are too small!"<<std::endl;
        displayGroupspt(smallGroups);
        std::cout<<"_____________________________________________________"<<std::endl;
        std::cout<<"\nCombining Small Groups..."<<std::endl;
        combineGroups(smallGroups,  max);
        std::cout<<"---------------------------------------"<<std::endl;
        std::cout<<"Small Groups were Combined Successfuly!"<<std::endl;
        std::cout<<"---------------------------------------"<<std::endl;
        std::cout<<"\n_____________________________________________________"<<std::endl<<std::endl;
        std::cout<<"Result of combining small groups:"<<std::endl;
        displayGroupspt(smallGroups);
        std::cout<<"_____________________________________________________"<<std::endl;
    }
    if(smallGroups[smallGroups.size()-1]->second>0 && smallGroups[smallGroups.size()-1]->second<min){ //this last element is the only small group left 
        //in this case we two choices:(1) spread the left small group into other group or (2)fill it with students from the other groups
        //check if spreading works
      std::cout<<"\nNote: it seems that group number " <<smallGroups[smallGroups.size()-1]->first 
      <<" is still too small!"<<std::endl;
    std::cout<<"_____________________________________________________"<<std::endl;
        std::pair<int, int>* smallGroup=smallGroups[smallGroups.size()-1];
        if (getEmptySpots(groupsData,smallGroup->first, max) >= smallGroup->second){
            std::cout<<"\nSpreading group number " <<smallGroups[smallGroups.size()-1]->first 
            <<" to the other groups..."<<std::endl;
            spreadGroup(groupsData,  max,  *smallGroup);
        }
        else {
            fillGroup(groupsData,  min,  *smallGroup);
        }
    }

}

//adjusts the number of groups in groupsData to the required amount to fit the number of students in class 
void adjustNumberOfGroups(std::vector<std::pair<int, int>>& groupsData, int numOfunassignedStudents,int max, int numOfStudentInSec){
    int numNeededGroups;//number of groups needed to include all students in class
    numNeededGroups = numOfStudentInSec / max; 
    int numGroupsToAdd; //number of groups need be added to groupsData
    numGroupsToAdd = numNeededGroups - groupsData.size();
     if(numGroupsToAdd>0)
        std::cout<< "/nAdding "<< numGroupsToAdd<<" groups to the database..."<<std::endl;
    for (int i=0; i<numGroupsToAdd;i++){
        std::pair<int,int> newGroup;
        newGroup.first = groupsData.size()+1; //set the new group's number to the next availble group number
        newGroup.second = 0;// set the number of students in the new group to 0;
        groupsData.push_back(newGroup);
    }
   
}


//assigns random students from unassignedStudents to random groups in groupsData
void assignToGroups(std::vector<std::pair<int, int>>& groupsData, std::vector<int>& unassignedStudents, int numOfStudentInSec, int min, int max){
   adjustNumberOfGroups(groupsData, unassignedStudents.size(), max, numOfStudentInSec);
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
   std::cout<<std::endl;
    std::cout<<"----------------------------"<<std::endl;
   std::cout<<"Current State of The Groups:"<<std::endl;
   std::cout<<"----------------------------"<<std::endl;
   displayGroups(groupsData);
   adjustGroupsToMin(groupsData, min, max);
   clearEmptyGroups(groupsData);
   std::cout<<std::endl;
   std::cout<<"-------------"<<std::endl;
   std::cout<<"Final Result:"<<std::endl;
   std::cout<<"-------------"<<std::endl;
   displayGroups(groupsData);
  
}

