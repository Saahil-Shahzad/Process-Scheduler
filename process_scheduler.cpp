/*
    # CPU Process Scheduler #
    # using linked list in  #
    # c++                   #
    -------------------------
    # By: Saahil Shahzad    #
    #     469370            #
    -------------------------
    # 10/4/2024             # 

*/


# include <iostream>

// defining a process as a node
struct processNode
{
    int processId;  // to identify a specific process
    int executionTime;  // total time it will take
    int remainingTime;  // the time remaining after each cyle of the scheduler

    processNode* next;  // will point to the next process node

    processNode(int processId, int executionTime) : processId(processId), executionTime(executionTime), remainingTime(executionTime), next(nullptr) {}  // constructor
};

// singly linked list to store the processes 
class ProcessList
{
    int numOfProcesses; // size of the process list
    processNode* head;  // point to the head of the list

    public:
        ProcessList() : numOfProcesses(0), head(nullptr) {}

        // inserts a process node at the end
        void createAndInsertProcess(int executionTime)
        {
            numOfProcesses++;   // incrementing the process counter

            processNode* newNode = new processNode(numOfProcesses, executionTime);

            if (!head)  // if list is empty, make new node the head  
            {
                head = newNode;
                newNode = nullptr;
            }
            else    // if list is not empty, insert at the end
            {
                processNode* temp = head;

                while (temp->next != nullptr)   // iterating to the end
                {
                    temp = temp->next;
                }

                temp->next = newNode;   // making the end node point to the new node
            }
        }

        // to remove a completed process
        void endProcess(processNode* completedProcess)
        {   
            numOfProcesses--;   // decrementing the process counter

            if (head == completedProcess)   // if head is the completed process, make next node in the list the head then delete the completed process
            {
                head = completedProcess->next;
                delete completedProcess;
            }
            else    // if head is not the completed process, bypass and delete the completed process
            {
                processNode* temp = head;

                while (temp->next != completedProcess)  // iterating to the node before the completed process node
                {
                    temp = temp->next;
                }

                temp->next = completedProcess->next;    // bypassing the completed process node

                delete completedProcess;    // deallocating the completed process node
            }
        }

        // to find and delete completed processes
        void deleteCompletedProcesses()
        {
            if (!head)  // if list is empty, return
            {   
                return;
            }

            processNode* temp = head;

            processNode* nodeToBeDeleted = nullptr;

            do   // iterating over the entire list
            {
                if (temp->remainingTime <= 0)    // if no remaining time left, delete the process node
                {   
                    nodeToBeDeleted = temp;
                    temp = temp->next;

                    endProcess(nodeToBeDeleted);    // deleting the process node
                    nodeToBeDeleted = nullptr;


                    continue;   // move on to the next iteration
                }

                temp = temp->next;
            } while (temp != nullptr);
        }

        // to print the system state
        void showSystemState()
        {
            if (!head)  // if list is empty, inform and return
            {
                std::cout << "No active process.\n";
                
                return;
            }

            processNode* temp = head;

            while (temp != nullptr)   // iterating over the entire list
            {
                if (temp->remainingTime > 0)    // if remaining time is left, print the remaining time
                {
                    std::cout << " P" << temp->processId << " (Remaining: " << temp->remainingTime << "),";
                    temp = temp->next;

                    continue;   // move on to the next iteration
                }

                // else print the process as completed
                std::cout << " P" << temp->processId << " (Completes),";
                temp = temp->next;
            }

            std::cout << "\b\n";
        }

        // to print the initial system state
        void showInitialSystemState()
        {
            if (!head)  // if list is empty, inform and return
            {
                std::cout << "Process list is empty.\n";
                
                return;
            }

            processNode* temp = head;

            std::cout << "Initial Processes: [";

            while (temp != nullptr)   // iterating over the entire list
            {
                std::cout << "(P" << temp->processId << ", " << temp->executionTime << "), ";
                temp = temp->next;
            }

            std::cout << "\b\b]\n";
        }

        // to check whether the list is empty
        bool isEmpty()
        {
            if (!head)  // if list is empty return true
            {
                return true;
            }

            return false;   // else return false
        }

        // the main scheduling method
        void scheduler(int cpuTimePerProcessPerCycle)
        {
            int cycleCount = 0; // to keep track of the cycle count

            this->showInitialSystemState();
            std::cout << "CPU Time per Process per Cycle: " << cpuTimePerProcessPerCycle << "\n";

            while (!this->isEmpty())    // continuing the process until the is empty
            {
                cycleCount++;   // incrementing the cycle counter

                processNode* temp = head;

                while (temp != nullptr)   // iterating over the entire list
                {
                    if (temp->remainingTime > 0)    // if remaining time is left, reduce it by cpu time per process per cycle
                    {
                        temp->remainingTime -= cpuTimePerProcessPerCycle;   // reducing the remaining time by cpu time per process per cycle
                    }

                    temp = temp->next;
                }

                std::cout << "Cycle " << cycleCount << ": ";
                this->showSystemState();    // printing the system state
                this->deleteCompletedProcesses();   // deleting all completed processes
            }
        }
};


int main()
{   
    // creating an instance of the process list
    ProcessList processList = ProcessList();

    // creating processes of execution times: 10, 5, 8 respectively, and inserting them into the list
    processList.createAndInsertProcess(10);
    processList.createAndInsertProcess(5);
    processList.createAndInsertProcess(8);

    // calling the process scheduler function
    processList.scheduler(3);

    return 0;
}