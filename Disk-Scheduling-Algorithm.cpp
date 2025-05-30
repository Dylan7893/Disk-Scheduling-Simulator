//
//  main.cpp
//  Project 2
//
//  Created by Dylan Hardy
//  C++ program for implementation of the FCFS, SSFT, and LOOK optimization strategies
//  Disk scheduling algorithms

//----------------------------------------namespace and directives----------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

//----------------------------------------constants----------------------------------------
const int NUM_OF_SAMPLE_REQUESTS = 10;  //number of requests for default file
const int MOVEMENT_TIME_CONSTANT = 12;  //constant used in seek time calculations
const int NUM_OF_SECTORS = 10;          //number of sectors
const double SEEK = 0.1;                //constant used in the seek time calculation
const double TRANSFER = 1.2;            //transfer time
const double SEARCH = 0.5;              //constant used in search time formula

//----------------------------------------class----------------------------------------
class Requests  //class describing a request
{
private:
    //-------class variables-------
    double arrivalTime;       //variable to hold arrival time
    int trackRequested;       //variable to hold track requested
    int sectorRequested;      //variable to hold sector requested
    double seekTime;          //variable to hold the seek time
    double searchTime;        //variable to hold the search time
    double dataTranfer;       //variable to hold data transfer time
    double totalTime;         //variable to hold total time
    int requestNumber;        //variable to hold the request
    int distanceFromCurrent;  //variable to hold the distance from the current track
    int jobFinished = 0;      //variable to hold the status of a requests finish status
    
public:
    //-------class constructors-------
    Requests() //default constructor
    {
    }
    
    //-------mutators-------
    void setArrivalTime(double value) //sets the value of the arrivalTime variable
    {
        arrivalTime = value;
    }
    
    void setTrackRequested(int value) //sets the value of the trackRequested variable
    {
        trackRequested = value;
    }
    
    void setSectorRequested(int value) //sets the value of the sectorRequested variable
    {
        sectorRequested = value;
    }
    
    void setSeekTime(double value) //sets the value of the seekTime variable
    {
        seekTime = value;
    }
    
    void setSearchTime(double value) //sets the value of the searchTime variable
    {
        searchTime = value;
    }
    
    void setDataTransfer(double value) //sets the value of the dataTranfer variable
    {
        dataTranfer = value;
    }
    
    void setTotalTime(double value) //sets the value of the totalTime variable
    {
        totalTime = value;
    }
    
    void setRequestNumber(double value) //sets the value of the requestNumber variable
    {
        requestNumber = value;
    }
    
    void setDistanceFromCurrent(int value) //sets the value of the distanceFromCurrent variable
    {
        distanceFromCurrent = value;
    }
    
    void setJobFinished(bool value) //sets the value of the jobFinished variable
    {
        jobFinished = value;
    }
    
    //-------accessors-------
    double getArrivalTime() //gets the value of the arrivalTime variable
    {
        return arrivalTime;
    }
    
    int getTrackRequested() //gets the value of the trackRequested variable
    {
        return trackRequested;
    }
    
    int getSectorRequested() //gets the value of the sectorRequested variable
    {
        return sectorRequested;
    }
    
    double getSeekTime() //gets the value of the seekTime variable
    {
        return seekTime;
    }
    
    double getSearchTime() //gets the value of the searchTime variable
    {
        return searchTime;
    }
    
    double getDataTransfer() //gets the value of the dataTranfer variable
    {
        return dataTranfer;
    }
    
    double getTotalTime() //gets the value of the totalTime variable
    {
        return totalTime;
    }
    
    int getRequestNumber() //gets the value of the requestNumber variable
    {
        return requestNumber;
    }
     
    int getDistanceFromCurrent() const //gets the value of the distanceFromCurrent variable
    {
        return distanceFromCurrent;
    }
    
    int getJobFinished() //gets the value of the jobFinished variable
    {
        return jobFinished;
    }
    
};

//----------------------------------------overloaded operators----------------------------------------

bool operator < (const Requests& p1, const Requests& p2)
{
    
    return p1.getDistanceFromCurrent()> p2.getDistanceFromCurrent();    //used in priority queue arranges distance from current sector from shortest to largest
}
    
//----------------------------------------prototypes----------------------------------------
void menu(); //displays a menu
void FCFS(queue<Requests>, int); //simulates FCFS algorithm
void SSRT(queue<Requests>, int); //simulates SSRT algorithm
void LOOK(Requests[], int); //simulates the LOOK algorithm

//----------------------------------------driver function----------------------------------------
int main()
{
    //-------variable delcarations-------
    int algChoice = 0; //variable used to hold user input of algorithm initialized to zero
    int fileChoice = 0; //variable used to hold user input of file choice initialized to zero
    ifstream infile; //variable used for the input file
    string fileName; //variable for the user input of file name
    string lineText; //variable used to hold the text read from the file
    int lineTextInteger; //variable used to take hold the text read from the file as an integer
    int numOfRequest = NUM_OF_SAMPLE_REQUESTS; //variable to hold the number of requests initialized to default ten
    int requestNum = 1; //variable used to hold the number corresponding to a request
    bool validFile = 0; //variable used to hold the status of the validity of a file
    int firstLoop = 1; //variable used to represent the increment of a loop
    
    while(algChoice < 1 || algChoice > 3) //while loop for input validation value must be 1-3
    {
        menu(); //displays menu
        cin >> algChoice; //holds user input for menu selection
        
        if(algChoice < 1 || algChoice > 3) //if user input is invalid display error
            cout << "\n\n*Invalid response, please enter a corresponding value from the menu*\n" << endl;
    }
    
    while(fileChoice < 1 || fileChoice > 2) //while loop for input validation value must be 1-2
    {
        //displays formatted instruction and takes input
        cout << "\nWhat file would you like to use for your simulation?" << endl;
        cout << "1:  Sample File" << endl;
        cout << "2:  Personal File" << endl;
        cout << endl;
        
        cout << "Enter value 1-2: ";
        cin >> fileChoice;
        
        if(fileChoice < 1 || fileChoice > 2) //if user input is invalid display erro
            cout << "\n\n*Invalid response, please enter a corresponding value from the menu*\n" << endl;
    }
    
    if(fileChoice == 2) //if the user selected a personal file we ask how many request are in the new file
    {
        cout << "How many request does file contain: ";
        cin >> numOfRequest;
    }

    //declare a queue and an array to hold reqests
    queue<Requests> myQueue;
    Requests *arr = new Requests [numOfRequest];
    
    if(fileChoice == 1) //if the user selected the sample file
    {
        infile.open("sample.txt"); //open sample file
        
        for(int iteration = 0; iteration < numOfRequest; iteration++) //iterate through all requests in file
        {
            Requests r; //temporary object
            
            getline(infile, lineText, ' '); //reads line
            lineTextInteger = stoi(lineText); //converts to int
            r.setArrivalTime(lineTextInteger); //gives property to object
            
            getline(infile, lineText, ' '); //reads line
            lineTextInteger = stoi(lineText); //converts to int
            r.setTrackRequested(lineTextInteger); //gives property to object
            
            getline(infile, lineText); //reads line
            lineTextInteger = stoi(lineText); //converts to int
            r.setSectorRequested(lineTextInteger); //gives property to object
            r.setRequestNumber(requestNum); //gives property to object
            
            requestNum++; //increments the current request that was previously initialized to one

            
            arr[iteration] = r; //puts temporary object into array of objects
            myQueue.push(r); //puts temporary object into queue of objects
        }
    }
    
    else //if the user chooses to use their own file
    {
        while(validFile == 0) //continue asksing for a file until file is valid
        {
            cout << "\nEnter the file name with the job information. (Use Pathname)" << endl; //displays instruction
            
            //using ignore() function on the first loop to clear buffer for succeeding getline
            if(firstLoop == 1)
                cin.ignore();
            
            getline(cin, fileName);  //gets the first line from the text file and saves into fileName variable
            
            string text;   //declares a temporary variable to hold the text on a given line for the file name
            
            firstLoop = 0; //at this point into the loop we change the flag to false since it is no longer the first iteration
            
            infile.open(fileName);  //attempts to opens the file
            
            //if the file does not open validFile is set to false and error is displayed before re-entry
            if(!infile)
            {
                validFile = 0;
                cout << "\nSorry this file could not be opened please try again." << endl;
            }
            //if it does open validFile is set to true
            else
                validFile = 1;
        }
        
        for(int iteration = 0; iteration < numOfRequest; iteration++)
        {
            Requests r; //temporary object
            
            getline(infile, lineText, ' '); //reads line
            lineTextInteger = stoi(lineText); //converts to int
            r.setArrivalTime(lineTextInteger); //gives property to object
            
            getline(infile, lineText, ' '); //reads line
            lineTextInteger = stoi(lineText); //converts to int
            r.setTrackRequested(lineTextInteger); //gives property to object
             
            getline(infile, lineText); //reads line
            lineTextInteger = stoi(lineText); //converts to int
            r.setSectorRequested(lineTextInteger); //gives property to object
            r.setRequestNumber(requestNum); //gives property to object
            
            requestNum++; //increments the current request that was previously initialized to one
            
            myQueue.push(r); //puts temporary object into array of objects
            arr[iteration] = r; //puts temporary object into queue of objects
        }
    }
        
    //displays the title of the table
    cout << "\nRequest\t Arrival  Track\t\tSector \tSeek\tSearch\t Data\t  Total\n";
    
    switch(algChoice) //switch control flow of program
    {
        case 1:
            FCFS(myQueue, numOfRequest);
            break;
        case 2:
            SSRT(myQueue, numOfRequest);
            break;
        case 3:
            LOOK(arr, numOfRequest);
            break;
    }
    
    delete[] arr; //deallocate array memory
    
    cout << endl << endl; //formatting
    return 0; //program end
}


void menu() //displays a menu of optimization strategy's
{
    //displays several formatted outputs
    cout << "----------Simulate An Optimization Strategy---------" << endl << endl;
    cout << "\nWhat algorithm would you like to simulate?" << endl;
    cout << "1:  FCFS" << endl;
    cout << "2:  SSFT" << endl;
    cout << "3:  LOOK" << endl;
    cout << endl;
    cout << "Enter value 1-3: ";
}

void FCFS(queue<Requests> myQueue, int numOfRequest) //simulates the FCFS algoritm
{
    //------- localvariable delcarations-------
    double tot = 0; //accumulator for total time
    double seektot = 0; //accumulator for total seek time
    double searchtot= 0; //accumulator for total search time
    double datatot = 0; //accumulator for total data time
    double variance = 0; //variable to hold the variance
    Requests previous; //temporary object to hold the previous object in queue
    Requests current; //temporary object to hold the current object in the queue
    queue<Requests> resetQueue; //queue used to hold all of the elements after they are removed from original queue
    Requests resetCurrent; //temporary object to hold the current element after reset
    
    for(int i = 0; i < numOfRequest; i++) //iterates through each element
    {
        current = myQueue.front(); //sets the current request to the first queue
        
        if(i==0) //if first element
        {
            //calculate seek and search time using appropriate formulas
            current.setSeekTime(MOVEMENT_TIME_CONSTANT + SEEK * current.getTrackRequested());
            current.setSearchTime(current.getSectorRequested() * SEARCH);
        }

        else if(current.getSectorRequested() > previous.getSectorRequested()) //if the sector requested is larger than the previous
        {
            //calculate seek and search time using appropriate formulas
            current.setSeekTime(MOVEMENT_TIME_CONSTANT + SEEK * abs(current.getTrackRequested() - previous.getTrackRequested()));
            current.setSearchTime((current.getSectorRequested() - (previous.getSectorRequested() + 1)) * SEARCH);
        }
        
        else if(current.getSectorRequested() < previous.getSectorRequested()) //if the sector requested is smaller than the previous
        {
            //calculate seek and search time using appropriate formulas
            current.setSeekTime(MOVEMENT_TIME_CONSTANT + SEEK * abs(current.getTrackRequested() - previous.getTrackRequested()));
            current.setSearchTime((NUM_OF_SECTORS-(previous.getSectorRequested() + 1) + current.getSectorRequested())* SEARCH);
        }
        
        else //if the sector times are equal
        {
            //calculate seek and search time using appropriate formulas
            current.setSeekTime(MOVEMENT_TIME_CONSTANT + SEEK * abs(current.getTrackRequested() - previous.getTrackRequested()));
            current.setSearchTime(0);
        }
        
        //set transfer time and total for current element
        current.setDataTransfer(TRANSFER);
        current.setTotalTime(current.getSeekTime() + current.getSearchTime() + current.getDataTransfer());
        
        
        //increment accumulators
        tot+= current.getTotalTime();
        seektot += current.getSeekTime();
        searchtot += current.getSearchTime();
        datatot += current.getDataTransfer();
        
        //move element to the reset queue
        resetQueue.push(current);
        
        //display formatted table
        cout << fixed << setprecision(1) << setw(5) << right
        << current.getRequestNumber()
        << setw(10)
        << current.getArrivalTime() << setw(7) << current.getTrackRequested() << setw(10) << current.getSectorRequested() << setw(8)
        << current.getSeekTime() << setw(8) << current.getSearchTime() << setw(8) << current.getDataTransfer()
        << setw(11) << current.getTotalTime() <<endl;
        
        
        previous = myQueue.front(); //before removing top we hold previous
        myQueue.pop();  //removes top element
    }
    
    //displays formatted total and average
    cout << "Total:" << right << setw(35) << seektot << setw(8)<< searchtot << setw(8) << datatot << setw(11) << tot << endl;
    cout << "Average:" << right << setw(32) << seektot/numOfRequest << setw(8)<< searchtot/numOfRequest << setw(8) << datatot/numOfRequest << setw(11) << tot/numOfRequest << endl;
    
    for(int i = 0; i < numOfRequest; i++) //iterates through reset queue and calculates variance
    {
        resetCurrent = resetQueue.front(); //sets temporary variable equal to front of reset queue
        variance += pow((resetCurrent.getTotalTime()- (tot/numOfRequest)),2); //sample variance formula before division
        resetQueue.pop(); //remove top element before repeating
    }
    
    variance/= (numOfRequest - 1); //finished sample variance formula
    
    //displays formatted variance and standard deviation
    cout << "Variance:" << setw(58) << variance << endl;
    cout << "Standard Deviation:" << setw(47) << sqrt(variance); //takes the square root of varince to get the standard deviation
}

void SSRT(queue<Requests> myQueue, int numOfRequest) //simulates the SSRT algorithm
{
    //------- local variable declarations -------
    double tot = 0; //accumulator for total time
    double seektot = 0; //accumulator for total seek time
    double searchtot = 0; //accumulator for search total time
    double datatot = 0; //accumulator for data total time
    double variance = 0; //variable to hold the variance

    queue<Requests> resetQueue; //queue used to hold all of the elements after they are removed from original queue
    Requests resetCurrent; //temporary object to hold the current element after reset
    Requests current; //temporary object to hold the current object in queue
    Requests previous; //temporary object to hold the previous element in queue
    Requests shortest; //temporary object to hold the shortest object in queue starting with the first element

    if (myQueue.empty()) {
        cerr << "Error: Queue is empty at start of SSRT." << endl;
        return;
    }

    shortest = myQueue.front(); //get first request
    myQueue.pop(); //remove the top of queue
    double currentTime = shortest.getArrivalTime(); //variable to hold current time starting with the arrival time of the first request

    //priority queue to arrange requests by shortest distance
    auto cmp = [](Requests a, Requests b) {
        return a.getDistanceFromCurrent() > b.getDistanceFromCurrent(); // min-heap
    };
    priority_queue<Requests, vector<Requests>, decltype(cmp)> shortestQueue(cmp);

    for (int i = 0; i < numOfRequest; i++) //iterates through each request
    {
        if (i == 0) //if first element
        {
            //calculate seek and search time using appropriate formulas
            shortest.setSeekTime(MOVEMENT_TIME_CONSTANT + SEEK * shortest.getTrackRequested());
            shortest.setSearchTime(shortest.getSectorRequested() * SEARCH);
        }
        else if (shortest.getSectorRequested() > previous.getSectorRequested()) //if shortest sector is larger than the previous sector
        {
            //calculate seek and search time using appropriate formulas
            shortest.setSeekTime(MOVEMENT_TIME_CONSTANT + SEEK * abs(shortest.getTrackRequested() - previous.getTrackRequested()));
            shortest.setSearchTime((shortest.getSectorRequested() - (previous.getSectorRequested() + 1)) * SEARCH);
        }
        else if (shortest.getSectorRequested() < previous.getSectorRequested()) //if the shortest sector is smaller than the previous sector
        {
            //calculate seek and search time using appropriate formulas
            shortest.setSeekTime(MOVEMENT_TIME_CONSTANT + SEEK * abs(shortest.getTrackRequested() - previous.getTrackRequested()));
            shortest.setSearchTime((NUM_OF_SECTORS - (previous.getSectorRequested() + 1) + shortest.getSectorRequested()) * SEARCH);
        }
        else //if the sectors are the same
        {
            //calculate seek and search time using appropriate formulas
            shortest.setSeekTime(MOVEMENT_TIME_CONSTANT + SEEK * abs(shortest.getTrackRequested() - previous.getTrackRequested()));
            shortest.setSearchTime(0);
        }

        //set transfer time and total for current element
        shortest.setDataTransfer(TRANSFER);
        shortest.setTotalTime(shortest.getSeekTime() + shortest.getSearchTime() + shortest.getDataTransfer());

        //if first request
        if (i == 0)
            currentTime = shortest.getTotalTime(); //current time is updated to the total time of the first request
        else
            currentTime += shortest.getTotalTime(); //current time is updated to the total time of the shortest request

        //increment time accumulators
        tot += shortest.getTotalTime();
        seektot += shortest.getSeekTime();
        searchtot += shortest.getSearchTime();
        datatot += shortest.getDataTransfer();

        resetQueue.push(shortest); //moves element to reset queue before being deleted

        //displays formatted results
        cout << fixed << setprecision(1) << setw(5) << right
             << shortest.getRequestNumber()
             << setw(10) << shortest.getArrivalTime()
             << setw(7) << shortest.getTrackRequested()
             << setw(10) << shortest.getSectorRequested()
             << setw(8) << shortest.getSeekTime()
             << setw(8) << shortest.getSearchTime()
             << setw(8) << shortest.getDataTransfer()
             << setw(11) << shortest.getTotalTime()
             << setw(11) << currentTime << endl;

        previous = shortest; //previous request set to the shortest element

        if (!myQueue.empty()) // check to avoid accessing front on empty queue
            current = myQueue.front(); //current request is set to the front of the queue

        if (!shortestQueue.empty()) //if the queue is not empty remove the top
            shortestQueue.pop();

        bool flag = false; //flag to stop while loop when all arrived request have been processed
        while (!flag)
        {
            if (myQueue.empty()) //if queue is empty can stop here
                flag = true; //set flag
            else if (current.getArrivalTime() <= currentTime) //if the current request has arrived
            {
                while (!myQueue.empty() && current.getArrivalTime() <= currentTime)
                {
                    current.setDistanceFromCurrent(abs(previous.getTrackRequested() - current.getTrackRequested())); //set the distance for current track
                    shortestQueue.push(current); //move to the shortest queue
                    myQueue.pop(); //remove from original queue

                    if (!myQueue.empty()) //if original queue is not empty
                        current = myQueue.front(); //set the current to the front
                    else
                        break; //any other case we can just exit while loop early
                }

                flag = true; //sets flag to exit
            }
            else //if no elements arrived
                currentTime += 0.1; //increment current time by 0.1
        }

        flag = false; //reset flag value

        if (!shortestQueue.empty()) {
            shortest = shortestQueue.top(); //sets shortest equal to the top of the priority queue

            //temporary data to update each element’s current distance
            Requests temp; //declares temporary Requests object
            priority_queue<Requests, vector<Requests>, decltype(cmp)> tempQ(cmp); //declares a temporary priority queue
            int tempCount = 0; //initializes tempCount to zero which will hold the amount of elements in queue

            while (!shortestQueue.empty()) //if the shortest queue is not empty
            {
                temp = shortestQueue.top(); //temp object holds top of shortest queue
                shortestQueue.pop(); //remove from top
                temp.setDistanceFromCurrent(abs(temp.getTrackRequested() - shortest.getTrackRequested())); //update the distance
                tempQ.push(temp); //push into the temporary queue
                tempCount++; //increment the amount of object in queue
            }

            for (int j = 0; j < tempCount; j++) //increments through all elements moving them back into original priority queue with updated objects
            {
                temp = tempQ.top(); //temporary object holds top of temp queue
                shortestQueue.push(temp); //moves back to original priority queue
                tempQ.pop(); //removes from temp queue
            }
        }
    }

    //displays formatted total and average
    cout << "Total:" << right << setw(35) << seektot << setw(8) << searchtot << setw(8) << datatot << setw(11) << tot << endl;
    cout << "Average:" << right << setw(32) << seektot / numOfRequest << setw(8) << searchtot / numOfRequest << setw(8) << datatot / numOfRequest << setw(11) << tot / numOfRequest << endl;

    //increments through the reset queue
    for (int i = 0; i < numOfRequest; i++)
    {
        resetCurrent = resetQueue.front(); //current reset object is front of reset queue
        variance += pow((resetCurrent.getTotalTime() - (tot / numOfRequest)), 2); //calculate sample variance sum
        resetQueue.pop(); //remove from reset queue
    }

    variance /= (numOfRequest - 1); //finish the sample variance formula

    //display the formatted sample variance and standard deviation
    cout << "Variance:" << setw(58) << variance << endl;
    cout << "Standard Deviation:" << setw(47) << sqrt(variance) << endl; //takes the square root of variance to get standard deviation
}



void LOOK(Requests arr[], int numOfRequest) //simulates the look algorithm
{
    //------- localvariable delcarations-------
    double tot = 0; //accumulator for total time
    double seektot = 0; //accumulator for total seek time
    double searchtot= 0; //accumulator for search total time
    double datatot = 0; //accumulator for data total time
    double variance = 0; //variable to hold the variance
    int finished = 1; //variable to hold the amount of jobs finished starting with one because first element will finish before entering the loop
    int iteration = 0; //holds the iteration of the loop
    
    Requests p; //temporary Request objects
    Requests temp; //temporary Request objects
    Requests previous; //holds the previous request
    
    //calculate seek and search time using appropriate formulas, sets data transfer and total times
    arr[0].setSeekTime(MOVEMENT_TIME_CONSTANT + SEEK * arr[0].getTrackRequested());
    arr[0].setSearchTime(arr[0].getSectorRequested() * SEARCH);
    arr[0].setDataTransfer(TRANSFER);
    arr[0].setTotalTime(arr[0].getSeekTime() + arr[0].getSearchTime() + arr[0].getDataTransfer());
        
    //updates total accumulator
    tot+= arr[0].getTotalTime(); //increment the total time
    seektot += arr[0].getSeekTime();
    searchtot += arr[0].getSearchTime();
    datatot += arr[0].getDataTransfer();
    
    //displays formatted results
    cout << fixed << setprecision(1) << setw(5) << right
    << arr[0].getRequestNumber()
    << setw(10)
    << arr[0].getArrivalTime() << setw(7) << arr[0].getTrackRequested() << setw(10) << arr[0].getSectorRequested() << setw(8)
    << arr[0].getSeekTime() << setw(8) << arr[0].getSearchTime() << setw(8) << arr[0].getDataTransfer()
    << setw(11) << arr[0].getTotalTime() << setw(11) <<endl;
    arr[0].setJobFinished(1);
    
    double currentTime = arr[0].getTotalTime(); //sets current time to the finish time of the first request
    double prevTime = arr[0].getTotalTime(); //sets the previous time to the finish time of the first request
    previous = arr[0]; //sets the previous request to the first request
    
    while(finished < numOfRequest) //loop continues until all jobs are finished
    {
        //bubble sort elements by track
        for(int i = 0; i < numOfRequest - 1; i++)
        {
            for(int j = 0; j < numOfRequest - i - 1; j++)
            {
                Requests jElem = arr[j];
                Requests jNextElem = arr[j+1];
                if ( iteration % 2 == 0)//on even iterations sort smallest to largest
                {
                    if (jElem.getTrackRequested() > jNextElem.getTrackRequested())
                    {
                        Requests t = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = t;
                    }
                }
                else//on odd iterations sort largest to smallest
                    if (jElem.getTrackRequested() < jNextElem.getTrackRequested())
                    {
                        Requests t = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = t;
                    }

            }
        }
        
        for(int i = 1; i < numOfRequest; i++) //increments through each request
        {
            temp = arr[i]; //temporary variable holds current element
            
            if(temp.getJobFinished() == 0) //if the job is not already finished
            {
                if(temp.getSectorRequested() > previous.getSectorRequested()) //if current sector is larger than the previous sector
                {
                    //calculate seek and search time using appropriate formulas
                    temp.setSeekTime(MOVEMENT_TIME_CONSTANT + SEEK * abs(temp.getTrackRequested() - previous.getTrackRequested()));
                    temp.setSearchTime((temp.getSectorRequested() - (previous.getSectorRequested() + 1)) * SEARCH);
                }
                
                else if(temp.getSectorRequested() < previous.getSectorRequested()) //if the current sector is smaller than the previous sector
                {
                    //calculate seek and search time using appropriate formulas
                    temp.setSeekTime(MOVEMENT_TIME_CONSTANT + SEEK * abs(temp.getTrackRequested() - previous.getTrackRequested()));
                    temp.setSearchTime((NUM_OF_SECTORS-(previous.getSectorRequested() + 1) + temp.getSectorRequested())* SEARCH);
                }
                
                else //if the current sector is equal to the previous sector
                {
                    //calculate seek and search time using appropriate formulas
                    temp.setSeekTime(MOVEMENT_TIME_CONSTANT + SEEK * abs(temp.getTrackRequested() - previous.getTrackRequested()));
                    temp.setSearchTime(0);
                }
                
                //set transfer time and total for current element
                temp.setDataTransfer(TRANSFER);
                temp.setTotalTime(temp.getSeekTime() + temp.getSearchTime() + temp.getDataTransfer());
                    
                prevTime = currentTime; //update the previous time to the current time
                
                currentTime += temp.getSeekTime(); //increment the current time with the calculated seek time of the potential next request
                
                //if the request has arrived, array is sorted smallest to largest, sector is bigger than the first request, and job isnt finished
                if(temp.getArrivalTime() <= currentTime && iteration % 2 == 0 && temp.getSectorRequested() > arr[0].getSectorRequested() && temp.getJobFinished() == 0)
                {
                    //display formatted information
                    cout << fixed << setprecision(1) << setw(5) << right << temp.getRequestNumber() << setw(10)
                    << temp.getArrivalTime() << setw(7) << temp.getTrackRequested() << setw(10) << temp.getSectorRequested() << setw(8)
                    << temp.getSeekTime() << setw(8) << temp.getSearchTime() << setw(8) << temp.getDataTransfer()
                    << setw(11) << temp.getTotalTime() << setw(11) << currentTime <<endl;
                    
                    currentTime = prevTime; //reset the current time to the previous time
                    currentTime += temp.getTotalTime(); //and the increment from this time by the finish time

                    temp.setJobFinished(1); //mark job as finished
                    finished++; //increment the total number of jobs that have finished
                    
                    //increment total accumulators
                    tot+= temp.getTotalTime();
                    seektot += temp.getSeekTime();
                    searchtot += temp.getSearchTime();
                    datatot += temp.getDataTransfer();
                    
                    previous = arr[i]; //previous request is set to the finished request
                    arr[i] = temp; //updates the array
                }
                
                //if the request has arrived, the array is sorted largest to smallest, and the reqeust is not finished
                else if(temp.getArrivalTime() <= currentTime && iteration % 2 != 0 && temp.getJobFinished() == 0)
                {
                    //displays formatted information
                    cout << fixed << setprecision(1) << setw(5) << right << temp.getRequestNumber() << setw(10)
                    << temp.getArrivalTime() << setw(7) << temp.getTrackRequested() << setw(10) << temp.getSectorRequested() << setw(8) << temp.getSeekTime() <<
                    setw(8) << temp.getSearchTime() << setw(8) << temp.getDataTransfer() << setw(11) << temp.getTotalTime() << setw(11) << currentTime <<endl;
                    
                    
                    currentTime = prevTime; //resets current time to the previous time
                    currentTime += temp.getTotalTime(); //increments the current time with the finish time of request
                    temp.setJobFinished(1); //mark job as finished
                    finished++; //increment the amount of jobs finished
                    
                    //increment the total time
                    tot+= temp.getTotalTime();
                    seektot += temp.getSeekTime();
                    searchtot += temp.getSearchTime();
                    datatot += temp.getDataTransfer();
                    
                    previous = arr[i]; //previous is set to the finished request
                    arr[i] = temp; //updates array element
                }
                else
                    currentTime = prevTime; //if not, current time is reset
            }
        }
        iteration++; //increment the iteration
    }
    
    //display formatted total and average
    cout << "Total:" << right << setw(35) << seektot << setw(8)<< searchtot << setw(8) << datatot << setw(11) << tot << endl;
    cout << "Average:" << right << setw(32) << seektot/numOfRequest << setw(8)<< searchtot/numOfRequest << setw(8) << datatot/numOfRequest << setw(11) <<
    tot/numOfRequest << endl;
       
    
    for(int i = 0; i < numOfRequest; i++) //iterate through array to calculate variance
    {
        variance += pow((arr[i].getTotalTime() - (tot/numOfRequest)),2); //calulates the sample variance
    }
    
    variance/= (numOfRequest - 1); //finishes the sample variance
       
    //displays formatted variance and standard deviation
    cout << "Variance:" << setw(58) << variance << endl;
    cout << "Standard Deviation:" << setw(47) << sqrt(variance); //calculates standard deviation by takig the square root of the variance
}
