#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

void printRes(int &seekCount, vector<int> &seekSequence, int requestSize, int &diskSize, vector<int> &eachSeekDistance, int worstCase);

void CLOOK(vector<int> requests, int diskSize, int head)
{
    int seekCount = 0, distance, currTrack;
    
    //store tracks on the left and right of the head
    vector<int> left, right;

    //store the distance between two track requests
    vector<int> eachSeekDistance;
    
    //store seek sequence
    vector<int> seekSequence;

    //split the tracks: left & right
    for(int &request : requests)
    {
        if(request < head) left.push_back(request);
        if(request > head) right.push_back(request);
    }

    //sort the left and right arrays
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    //service requests on the right side of head first
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

    //add seek count for head returning from last track to beginning
    seekCount += abs(head - left[0]);
    
    eachSeekDistance.push_back(head - left[0]);

    //jump to the lowest track request
    head = left[0];

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

    int worstCaseSeekCount = abs(right.back() - left[0]);
    
    printRes(seekCount, seekSequence, requests.size(), diskSize, eachSeekDistance, worstCaseSeekCount);

}

void printRes(int &seekCount, vector<int> &seekSequence, int requestSize, int &diskSize, vector<int> &eachSeekDistance, int worstCase)
{
    double avgSeekTime = double(seekCount) / requestSize;

    cout << "The seek count is: " << seekCount << endl;
    cout << "The average seek time is: " << avgSeekTime << endl;
    cout << "The worst-case seek time is: " << worstCase << endl;
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
    CLOOK(requestList, maxCylinderDiskSize, startHead);
    
          
}


