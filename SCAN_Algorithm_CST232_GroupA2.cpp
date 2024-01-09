#include<iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>
using namespace std;

const int disk_size = 199;

// Function to print the results of the disk scheduling algorithm
void printRes(int seekCount, const vector<int>& seekSequence, const vector<int>& eachSeekDistance) 
{
    // Calculating the average seek time
    double avgSeekTime = double(seekCount) / seekSequence.size();

    // Displaying the total number of seeks
    cout << "The seek count is: " << seekCount << endl;

    // Displaying the average seek time with precision of 4 decimal places
    cout << "The average seek time is: " << setprecision(4) << avgSeekTime << endl; //second or milisecond(ms)
    cout << "The seek sequence is: ";

    // Printing the sequence of seeks
    for (int seq : seekSequence) 
    {
        cout << seq << " ";
    }
    
    cout << "\nEach seek distance by head movement: ";
    // Printing each seek distance moved by the head
    for (int dist : eachSeekDistance) {
        cout << dist << " ";
    }
    cout << endl;
}

// Function implementing the SCAN disk scheduling algorithm
void SCAN(vector<int> arr, int head, string direction) 
{
    int seek_count = 0;
    vector<int> left, right;
    vector<int> seek_sequence;
    vector<int> each_seek_distance;

    // Adding end values of disk to the appropriate vectors based on direction
    if (direction == "left")
        left.push_back(0);
    else if (direction == "right")
        right.push_back(disk_size - 1);

    // Dividing the disk locations into left and right of the head position
    for (int i = 0; i < arr.size(); i++) 
    {
        if (arr[i] < head)
            left.push_back(arr[i]);
        if (arr[i] > head)
            right.push_back(arr[i]);
    }

    // Sorting the requests in left and right for SCAN algorithm
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    // Scanning left and right of the head position
    int run = 2;
    while (run--) 
    {
        if (direction == "left") 
        {
            for (int i = left.size() - 1; i >= 0; i--) 
            {
                int cur_track = left[i];
                // Storing the seek sequence
                seek_sequence.push_back(cur_track);
                int distance = abs(cur_track - head);
                // Calculating the seek distance and adding it to the total
                each_seek_distance.push_back(distance);
                seek_count += distance;
                // Updating the head position
                head = cur_track;
            }
            // Switching the direction
            direction = "right";
        } else if (direction == "right") 
        {
            for (int i = 0; i < right.size(); i++) 
            {
                int cur_track = right[i];
                seek_sequence.push_back(cur_track);
                int distance = abs(cur_track - head);
                each_seek_distance.push_back(distance);
                seek_count += distance;
                head = cur_track;
            }
            direction = "left";
        }
    }

    // Calling the function to print the results
    printRes(seek_count, seek_sequence, each_seek_distance);
}

int main() 
{
    // Seeding the random number generator
    srand(time(0));
    int requests; // Change here: 10, 20, 50 or 100.
    cout <<"Enter How Many Random Requests: ";
    cin >>requests;
    vector<int> requestList(requests);

    // Optional between using requestList or requestSample.
    for(int &index : requestList)
    {
        index = rand() % 200;
    }
    
    // Sample request sequence for disk scheduling
    vector<int> requestSample = {176, 79, 34, 60, 92, 11, 41, 114};
    
    // Initial position of the disk head
    int startHead= 50;
    
    // Calling the SCAN algorithm
    SCAN(requestList, startHead, "left");
    
    return 0;
}
