#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

void printRes(int &seekCount, vector<int> &seekSequence, int requestSize, int &diskSize, vector<int> &eachSeekDistance);

void CSCAN(vector<int> requests, int diskSize, int head)
{
    int seekCount = 0, distance = 0, currTrack = 0;
    
    //store tracks on the left and right of the head
    vector<int> left, right;

    //store each of the 
    vector<int> eachSeekDistance;
    
    //store seek sequence
    vector<int> seekSequence;

    //append end values first which have to be visited before reversing direction
    left.push_back(0);
    right.push_back(diskSize - 1);

    //split the tracks: left & right

    for(int &request : requests)
    {
        if(request < head) left.push_back(request);
        if(request > head) right.push_back(request);
    }

    //sort the left and right arrays
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    //service requests on the right side of head
    for(int &request : right)
    {
        currTrack = request;

        seekSequence.push_back(currTrack);

        distance = abs(currTrack - head);
        eachSeekDistance.push_back(distance);

        //increase total count of seek operations
        seekCount += distance;

        //set current track as new head
        head = currTrack;
    }

    //jump to the min track
    head = 0;

    //add seek count for head returning from last track to beginning
    seekCount += diskSize - 1;
    
    eachSeekDistance.push_back(diskSize - 1);

    
    //left side requests
    for(int &request : left)
    {
        currTrack = request;
        seekSequence.push_back(currTrack);
        distance = abs(currTrack - head);
        eachSeekDistance.push_back(distance);
        seekCount += distance;
        head = currTrack;
    }

    printRes(seekCount, seekSequence, requests.size(), diskSize, eachSeekDistance);

}

void printRes(int &seekCount, vector<int> &seekSequence, int requestSize, int &diskSize, vector<int> &eachSeekDistance)
{
    double avgSeekTime = double(seekCount) / requestSize;
    int worstCaseSeekTime = diskSize - 1; // Due to zero-based indexing

    cout << "The seek count is: " << seekCount << endl;
    cout << "The average seek time is: " << avgSeekTime << endl;
    cout << "The worst-case seek time is: " << worstCaseSeekTime << endl;
    cout << "The seek sequence is: ";

    for(int &seq : seekSequence)
    {
        cout << seq << " ";
    }
    
    cout << "\nEach seek distance by head movement: ";

    for(int &dist : eachSeekDistance)
    {
        cout << dist << " ";
    }

}

int main()
{    
    srand(time(0));
    int requests;
    cout <<"Enter How Many Random Requests: ";
    cin >> requests;

    
    vector<int> requestList(requests);

    for(int &index : requestList)
    {
        index = rand() % 200;
    }

    vector<int> requestSample = {98, 183, 40, 122, 10, 124, 65};

    int maxCylinderDiskSize = 200, startHead = 53;
    CSCAN(requestList, maxCylinderDiskSize, startHead);
    
          
}





