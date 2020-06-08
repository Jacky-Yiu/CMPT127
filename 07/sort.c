#include <stdio.h>
#include <stdlib.h>

#include "list.h"

element_t* SortedMerge(element_t* a, element_t* b); 

void FrontBackSplit(element_t* source, 
                    element_t** frontRef, element_t** backRef);


int mergesort(element_t** headRef)
{
	element_t* head = *headRef; 
	element_t* a;
	element_t* b;

	if (head==NULL||head->next==NULL)
	{
		return 0;
	}



	FrontBackSplit(head, &a, &b);

	mergesort(&a);
	mergesort(&b);

	*headRef = SortedMerge(a,b);

	return 0;
}


element_t* SortedMerge(element_t* a, element_t* b) 
{ 
    element_t* result = NULL; 
  
    /* Base cases */
    if (a == NULL) 
        return (b);

    else if (b == NULL) 
        return (a); 
  
    /* Pick either a or b, and recur */
    if (a->val <= b->val) 
    { 
        result = a; 
        result->next = SortedMerge(a->next, b); 
    } 
    else 
    { 
        result = b; 
        result->next = SortedMerge(a, b->next); 
    } 

    return (result); 
} 

void FrontBackSplit(element_t* source, 
                    element_t** frontRef, element_t** backRef) 
{ 
    element_t* fast; 
    element_t* slow; 
    slow = source; 
    fast = source->next; 
  
    /* Advance 'fast' two nodes, and advance 'slow' one node */
    while (fast != NULL) { 
        fast = fast->next; 
        if (fast != NULL) { 
            slow = slow->next; 
            fast = fast->next; 
        } 
    } 
  
    /* 'slow' is before the midpoint in the list, so split it in two 
    at that point. */
    *frontRef = source; 
    *backRef = slow->next; 
    slow->next = NULL; 
} 







void list_sort(list_t* list)
{
	mergesort(&(list->head));

	return;
	
}
