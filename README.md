# CSPB2270-Final-Project
Data structure implemented Skip List:

A skiplist is a variation of a linked list that uses levels and probabilities to cut down on the time it takes to search the list in the average case. The various levels act as express lanes to find values because they can allow the program to skip over a certain number of entires in the list. A random number generator is used to decide how many levels a certain value will have which keeps the structure generally balanced. Skiplists have an average time complexity of O(log n) for search.

The project goal was to create a recurring task manager using skip lists that would take a recurrence variable for each task and add it back into the list with a new priority after completion. I think that there are better data structures for achieving this goal e.g. heaps, but used this project as an opportunity to understand a data structure that I have less experience with.  

The implementation of the skip list data structure in this project uses forward pointers only and each node contains a vector of forward pointers with each position in the vector corresponding to a level in the skip list. The first few examples of the skip list structure that I encountered used four different pointers per node, [next, previous, above, below], and created nodes to sit in the levels. It occured to me that this method would actually make searchinig this list more time intensive if the list were large enough. It would also take up much more space. Eventually I found some examples of skip lists implemented with single pointers and decided to do it that way. 

The project has three classes; Node, Task, and SkipList. The SkipList is made up of Nodes which all contain Tasks. The Tasks contain a start time which the Node usese to determine its key and therefore its place in the list. A task can be rescheduled based on its recurrence interval and re-inserted into the SkipList.

Full breakdown:
Task contains
   Name of task to be completed

   Start time - used to informt the node key and add to list

   recurrenceInterval - number of days between the task recurring, used to update the start time when rescheduling

Node contains 
   key - set based on the start time of the task.

   task - of class Task

   vector of forward pointers that keeps track of the levels in the skip list.

SkipList contains
   maxLevel - a cieling for the levels to prevent the levels from accidentally getting out of hand. 

   probability - the number of levels for each entry is probabalistic. The probability here informs the likelihood of an entry residing in a higher level. 

   head - a dummy Node to act as the head, giving the traversal functions a place to start. 

   currentLevel - tracks the current hight of the levels, which may or may not have reached the maxHeight. 

Major functions of the Skip List:
   insert - Takes in a task and traverses the list starting at the head. It moves from the top level down until finding where to insert the new node. Then it creates a node using the tasks startTime and updates the pointers to insert it into the list. 

   search - takes in the node's key and traverses the list from the top level until it finds the corresponding node and returns a pointer to the corresponding task. 

   erase - takes in the node's key and traverses from the top level until it finds the one to delete. It then updates the pointers of the previous nodes in each level before deleting it. 

I created this project from a copy of an existing homework assignment so it has working test and build files. After downloading the project run cmake .., change directory to build, make the files, and run tests with ./run_tests. 
