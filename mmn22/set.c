#include "set.h"
/* _________________________________________________________________________________________________
  |This fuctions inputs the values of a list to a group by the name which the user inputs:         |
  |The order of the values is unsorted, and each value can only appear once.                       |
  |If the same value appears twice it skips for the next index.                                    |
  |The end of the list is marked by value of the last number: is -1.                               |
  |If the list is empty and there is only 1 index it will return empty list.                       |
  |________________________________________________________________________________________________|
  |                                          ★Parameters:★                                                              |
  |▸(set) x - inputting set of x group.                                                            |
  |▸(int - arr) temp - the list the user inputs is entered to a array.                             |
  |▸(int) i - index for the loops (indicates which index we are on right now)                      |
  |________________________________________________________________________________________________|
*/
/*This fuction reset the members: sum and members in group(set)
The array is combined from zeros and -7 at the begining*/
void reset(set *x)
{
	int i = 1;	
	x->sum = 0;
	x->arr[0]=-7;
	for(;i<127;i++)
	x->arr[i]=0;
}
/* _________________________________________________________________________________________________
  |This fuctions reads the group members:                                                          |
  |The members are sorted from the smallest to the largest.                                        |
  |________________________________________________________________________________________________|
  |                                          ★Parameters:★                                                              |
  |▸(set) x - inputting set of x group.                                                            |
  |▸(int arr) temp - the list the user inputs is entered to a array.                               |
  |▸(int) i - index for the loops (indicates which index we are on right now)                      |
  |________________________________________________________________________________________________|
*/
void read_set(set *x, int *temp, int amount)
{
	int i = 0;	
	for(;i<amount;i++)/*/sizeof(*temp))&&(temp[i]!=-1);i++)*/
	{	
		if(temp[i]!=-1)
		{
		x->arr[temp[i]] = temp[i]; /*a values can't appears twice in the same array*/
		x->sum += temp[i];
		}
	}		
}
/* _________________________________________________________________________________________________
  |This fuctions outputs the group members of a group given by the user (the name and values):     |
  |The members are sorted from the smallest to the largest.                                        |
  |At least each output line containts 16 members.                                                 |
  |If the list is empty and it will print "The set is empty".                                      |
  |________________________________________________________________________________________________|
  |                                          ★Parameters:★                                                              |
  |▸(set) x - inputting set of x group.                                                            |
  |▸(int arr) temp - the list the user inputs is entered to a array.                               |
  |▸(int) i - index for the loops (indicates which index we are on right now)                      |
  |________________________________________________________________________________________________|
*/
void print_set(set *x)
{
 	int i = 0, count = 0;
	if(x->sum==0)
	{
		printf("\nThe set is empty.\n");
		return;
	}
 	for(i=0;i<127;i++)
	{
		if((i!=0 && x->arr[i]!=0) || (i==0 && x->arr[i]!=-7))
		{
			printf("\nThe group members are: %d",x->arr[i]);
			count++;
		}
		
		if(count==16)
		{
			printf("\n");
			count = 0;
		}
	}/*end of for*/
}
/* _________________________________________________________________________________________________
  |This fuctions unified two group ('a' and 'b') and stores the result in a new group(group c):    |
  |Using two for loops: the first one is for taking the entire group of set a and stores it in c.  |
  |The second for loop is taking group b and adding it up to group c (currently storing group a).  |
  |The second loop is using j to pick up from the index we left on the first loop.                 |
  |________________________________________________________________________________________________|
  |                                          ★Parameters:★                                                              |
  |▸(int) i - index for the loops (indicates which index we are on right now)                      |
  |▸(set) a - inputting set of a group.                                                            |
  |▸(set) b - inputting set of b group.                                                            |
  |▸(set) c - inputting set of b group.                                                            |
  |________________________________________________________________________________________________|
*/
void union_set(set *a, set *b, set *c)
{
	int i = 0;
	reset(c);
	/* this loop going takes the entires members from group a - adds it to group c*/
	for(;i<127;i++) /*if the array is combined of int - dividing in order to get the amount of memory it takes*/
	{		
		c->arr[i]=(a->arr[i] > b->arr[i] ? a->arr[i] : b->arr[i]);
		c->sum += (c->arr[i]==-7 ? 0 : c->arr[i]);
	}
}
/* _________________________________________________________________________________________________
  |This fuctions intersect two group ('a' and 'b') and stores the result in a new group(group c):  |
  |Using two loop to go over two groups and if there is the same value in the index i or j(i+1).   |
  |Afterwards going over the array using the j = i+1, to make sure we go over the entire array.    |
  |________________________________________________________________________________________________|
  |                                          ★Parameters:★                                                              |
  |▸(int) i - index for the loops (indicates which index we are on right now)                      |
  |▸(set) a - inputting set of a group.                                                            |
  |▸(set) b - inputting set of b group.                                                            |
  |▸(set) c - inputting set of b group.                                                            |
  |________________________________________________________________________________________________|
*/
void intersect_set(set *a, set *b, set *c)
{
	int i = 0;
	reset(c);	
	/* this loop going takes the entires members from group a - adds it to group c*/
	for(;i<127;i++) 
	{
		if(i==0)
		{
		if(a->arr[i]==0 && b->arr[i]==0)
			c->arr[i]=0;
		else if(a->arr[i]==0 && b->arr[i]!=0)
			c->arr[i]=-7;
		else if(a->arr[i]!=0 && b->arr[i]==0)
			c->arr[i]=-7;
		else if(a->arr[i]==-7 && b->arr[i]==-7)
			c->arr[i]=-7;
		} else
			c->arr[i]=(a->arr[i] == b->arr[i] ? a->arr[i] : 0);
		c->sum += (c->arr[i]==-7 ? 0 : c->arr[i]); /*if it is -7 - adds nothing else adds the value*/	
	}
}
/* _________________________________________________________________________________________________
  |This fuctions substract one group (a) from the other (b) and stores group a in c.               |
  |The members must be found only in group a and not in group b, and then it stores in group c.    |
  |Using two loops: one to go over the entire array from first to last.                            |
  |The second loop go over the next index (i+1) in order to make sure:                             |
  |we didn't miss any equals index between the two groups.                                         |
  |________________________________________________________________________________________________|
  |                                          ★Parameters:★                                                              |
  |▸(int) i - index for the loops (indicates which index we are on right now)                      |
  |▸(set) a - inputting set of a group.                                                            |
  |▸(set) b - inputting set of b group.                                                            |
  |▸(set) c - inputting set of b group.                                                            |
  |________________________________________________________________________________________________|
*/
void sub_set(set *a, set *b, set *c)
{
	int i = 0;
	reset(c);
	/* this loop going takes the entires members from group a - adds it to group c*/
	for(;i<127;i++) /*if the array is combined of int - dividing in order to get the amount of memory it takes*/
	{
		if(i==0)
		{
		if(a->arr[i]==0 && b->arr[i]==0)
			c->arr[i]=-7;
		else if(a->arr[i]==0 && b->arr[i]!=0)
			c->arr[i]=0;
		else if(a->arr[i]==-7)
			c->arr[i]=-7;
		} else
			c->arr[i]=(a->arr[i] != b->arr[i] ? a->arr[i] : 0);
		c->sum += (c->arr[i]==-7 ? 0 : c->arr[i]);
	}
}
/* _________________________________________________________________________________________________
  |This fuctions substract one group (a) from the other (b), go over both groups make sure,        |
  |The members only appears in one group and not both, and then store the member in group c.       |
  |Using two loops: one to go over the entire array from first to last.                            |
  |The second loop go over the next index (i+1) in order to make sure:                             |
  |we didn't miss any equals index between the two groups.                                         |
  |________________________________________________________________________________________________|
  |                                          ★Parameters:★                                                              |
  |▸(int) i - index for the loops (indicates which index we are on right now)                      |
  |▸(set) a - inputting set of a group.                                                            |
  |▸(set) b - inputting set of b group.                                                            |
  |▸(set) c - inputting set of b group.                                                            |
  |________________________________________________________________________________________________|
*/
void symdiff_set (set *a, set *b, set *c)
{
	int i = 0;
	reset(c);
	/* this loop going takes the entires members from group a - adds it to group c*/
	for(;i<127;i++) /*if the array is combined of int - dividing in order to get the amount of memory it takes*/
	{
		if(i==0)
		{
		if(a->arr[i]==0 && b->arr[i]==0)
			c->arr[i]=-7;
		else if(a->arr[i]==0 && b->arr[i]!=0)
			c->arr[i]=0;
		else if(a->arr[i]==-7 && b->arr[i]==0)
			c->arr[i]=0;
		else if(a->arr[i]==-7 && b->arr[i]==-7)
			c->arr[i]=-7;
		}else
			c->arr[i]=(a->arr[i] == b->arr[i] ? 0 : (a->arr[i] > b->arr[i] ? a->arr[i] : b->arr[i]));
		c->sum += (c->arr[i]==-7 ? 0 : c->arr[i]);
	}
}
/* _________________________________________________________________________________________________
  |                       This fuctions stop the program immediately.                              |
  |________________________________________________________________________________________________|
*/
void stop()
{
	exit(0);
}

