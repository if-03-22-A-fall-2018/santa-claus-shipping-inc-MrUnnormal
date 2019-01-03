#include <string.h>
#include <stdlib.h>
#include "tour_plan.h"

TourPlan* plan_createTour(ChildDataMgmt *cdm){
  _tourPlan* plan=(_tourPlan*)malloc(sizeof(_tourPlan));
  Node* curr=cdm_get_sorted_data(cdm);
  int count_presents=0;
  ChildData* curr_child_data=0;
  const char* last_city;
  plan->city_plans=list_create();
  _cityPlan* curr_city;
  _childPlan* curr_child;

  while (curr!=0) {
    /*prepare Plan*/
    curr_child_data=(ChildData*) list_get_data(curr);
    count_presents=plan_calc_presents(curr_child_data->goodness);
    plan->total_children=plan->total_children+1;
    plan->total_presents=plan->total_presents+count_presents;
    curr=list_get_next(curr);

    /*prepare cityplan*/
    if (strcmp(last_city, curr_child_data->city)!=0) {
      curr_city=(_cityPlan*)malloc(sizeof(_cityPlan));
      curr_city->child_plans=list_create();
      curr_city->city=curr_child_data->city;
      list_add(plan->city_plans, curr_city);
    }
    last_city=curr_child_data->city;

    /*prepare children*/
    curr_child=(_childPlan*)malloc(sizeof(_childPlan));
    curr_child->name=curr_child_data->name;
    curr_child->presents=count_presents;
    list_add(curr_city->child_plans, curr_child);
  }
  return plan;
}

void plan_print(TourPlan *plan){

}

void plan_delete(TourPlan *plan){

}

int plan_calc_presents(double goodness){
  if (goodness<0.6) {
    return 0;
  }
  else if (goodness>=1.0) {
    return 5;
  }
  else{
    return (goodness-0.5)*10.0+0.5;
  }
}
