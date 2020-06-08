#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "list.h"

int main( int argc, char* argv[] )
{
  // test the create function
  list_t* list = list_create();

  // check to see if the create function did everything it was supposed to
  if( list == NULL )
  {
    printf( "1.1. create: create failed to malloc\n" );
    return 1;
  }

  if( list->head != NULL )
  {
    printf( "1.2. create: head is not null!\n" );
    return 1;
  }

  if( list->tail != NULL )
  {
    printf( "1.3. create: tail is not null!\n" );
    return 1;
  }

  // now test all the other functions (except list_print) to see if
  // they do what they are supposed to

  //********************************************************************************  
  element_t* el = malloc(sizeof(element_t));
  assert(el);
  memset(el,0xFF,sizeof(element_t));
  free(el);


  el = element_create(1);

  
  if( el == NULL )
  {
    printf( "2.1. el_create: element create failed to malloc\n" );
    return 1;
  }

  if( el->val != 1 )
  {
    printf( "2.2. el_create: element value not correct\n" );
    return 1;
  }

  if( el->next != NULL )
    {
      printf( "2.3. el_create: next is not null!\n" );
      return 1;
    }

  element_t* el_2 = element_create(2);

  el->next=el_2;

  el = element_create(3);

  if( el == NULL )
  {
    printf( "2.4. el_create: element create failed to malloc\n" );
    return 1;
  }

  if( el->val != 3 )
  {
    printf( "2.5. el_create: element value not correct\n" );
    return 1;
  }

  if( el->next != NULL )
    {
      printf( "2.6. el_create: next is not null!\n" );
      return 1;
    }


  //***********************************************************************************  
  list_append(list,0);

  if(list->head==NULL||list->tail==NULL)
  {
    printf( "3.1. append: element create failed to malloc\n" );
    return 1;
  }

  if(list->head->val!=0)
  {
    printf( "3.2. append: head element value not correct\n" );
    return 1;
  }

  if(list->tail->val!=0)
  {
    printf( "3.3. append: tail element value not correct\n" );
    return 1;
  }

  if(list->tail->next!=NULL)
  {
    printf( "3.4. append: tail next not NULL\n" );
    return 1;
  }

  for(int i = 1; i<=3; i++)
  {
    list_append(list,i);

    if(list->tail==NULL)
    {
      printf( "3.5.%d. append: element create failed to malloc\n",i );
      return 1;
    }

    if(list->head->val!=0)
    {
      printf( "3.6.%d. append: head element value not correct\n",i );
      return 1;
    }

    if(list->tail->val!=i)
    {
      printf( "3.7.%d. append: tail element value not correct\n",i );
      return 1;
    }

    if(list->tail->next!=NULL)
    {
      printf( "3.8.%d. append: tail next not NULL\n",i );
      return 1;
    }
  }
  // list shoud be [0->1->2->3]
  //******************************************************************************//
  list_prepend(list,-1);

  if(list->head==NULL)
  {
    printf( "4.1. prepend: element create failed to malloc\n" );
    return 1;
  }

  if(list->head->val!=-1)
  {
    printf( "4.2. prepend: head element value not correct\n" );
    return 1;
  }

  if(list->tail->val!=3)
  {
    printf( "4.3. prepend: tail element value not correct\n" );
    return 1;
  }

  if(list->tail->next!=NULL)
  {
    printf( "4.4. prepend: tail next not NULL\n" );
    return 1;
  }  
  
  list_prepend(list,-2);
  list_prepend(list,-3);


    
    if(list->head==NULL)
    {
      printf( "4.5. prepend: element create failed to malloc\n");
      return 1;
    }

    if(list->head->val!=-3)
    {
      printf( "4.5. prepend: head element value not correct\n");
      return 1;
    }
    
    if(list->head->next->val!=-2)
    {
      printf( "4.5. prepend: head next element value not correct\n");
      return 1;
    }

    if(list->tail->val!=3)
    {
      printf( "4.5. prepend: tail element value not correct\n");
      return 1;
    }

    if(list->tail->next!=NULL)
    {
      printf( "4.5. prepend: tail next not NULL\n");
      return 1;
    }


  //***********************************************************************************//
  
  list_t* list_2 = list_create();

  list_prepend(list_2,3);

  if(list_2->head==NULL||list->tail==NULL)
  {
    printf( "5.1. prepend: element create failed to malloc\n" );
    return 1;
  }

  if(list_2->head->val!=3)
  {
    printf( "5.2. prepend: head element value not correct\n" );
    return 1;
  }

  if(list_2->tail->val!=3)
  {
    printf( "5.3. prepend: tail element value not correct\n" );
    return 1;
  }

  if(list_2->tail->next!=NULL)
  {
    printf( "5.4. prepend: tail next not NULL\n");
    return 1;
  }


  list_prepend(list_2,2);
  list_prepend(list_2,1);
  list_prepend(list_2,0);

  if(list_2->tail==NULL||list_2->head==NULL)
  {
    printf( "5.5. prepend: element create failed to malloc\n");
    return 1;
  }

  if(list_2->head->val!=0)
  {
    printf( "5.6. prepend: head element value not correct\n");
    printf("it is %d\n",list_2->head->val);
  return 1;
  }

  if(list_2->tail->val!=3)
  {     
    printf( "5.7. prepend: tail element value not correct\n" );
    return 1;
  }

  if(list_2->tail->next!=NULL)
  {
    printf( "5.8. prepend: tail next not NULL\n");
    return 1;
  }
  //*************************************************************************************//
  element_t* result = list_index(list_2,0);

  if (result->val!=0)
  {
    printf( "6.1. index: positive result incorrect\n");
    return 1;
  }  

  result = list_index(list_2,5);
  if (result!=NULL)
  {
    printf( "6.2. index: negative result incorrect\n");
    return 1;
  }

  list_t* list_3 = list_create();
    
  result = list_index(list_3,2);
  if (result!=NULL)
  {
    printf( "6.3. index: empty list result incorrect\n");
    return 1;
  } 


  //***************************************************************************************//
  list_print(list);
  list_print(list_2);

  list_destroy(list);
  list_destroy(list_2);

  return 0; // tests pass
}
