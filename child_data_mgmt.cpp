#include <stdlib.h>
#include <string.h>
#include "child_data_mgmt.h"
/**
 * Creates a structure for child data management
 */
ChildDataMgmt* cdm_create()
{
  _childDataMgmt* child=(_childDataMgmt*)malloc(sizeof(_childDataMgmt));
  child->kids=list_create();
  return child;
}

/**
 * Uses the child management logic to process child data
 * (hint: insert it, sorted by town into the internal list)
 */
void cdm_add_data(ChildDataMgmt *cdm, ChildData *data)
{
  Node* curr=list_get_first(cdm->kids);
  if (curr==0) {
    list_add(cdm->kids, (void*)data);

  }else{
    _childData* curr_data=(_childData*)list_get_data(curr);
    Node* prev=0;

    while (curr!=0&&strcmp(curr_data->city, data->city)<=0)
    {
      prev=curr;
      curr=list_get_next(curr);
      if (curr!=0) {
        curr_data=(_childData*)list_get_data(curr);
      }
    }
    if (prev!=0) {
      list_insert_after(prev, (void*)data);
    }
    else {
      list_add(cdm->kids, (void*)data);
    }
  }
}

/**
 * Returns a pointer to the first element of the properly sorted list
 * (hint: "sorting" should have already happened when inserting)
 */
 Node* cdm_get_sorted_data(ChildDataMgmt *cdm)
 {
   return list_get_first(cdm->kids);
 }

/**
 * Used to clean up memory allocated when creating the child management structure
 */
void cdm_delete(ChildDataMgmt *cdm)
{
  list_delete(cdm->kids);
  free(cdm);
}
