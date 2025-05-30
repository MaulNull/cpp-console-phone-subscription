#ifndef FILTER_H
#define FILTER_H

#include "phone_subscription.h"

phone_subscription** filter(phone_subscription* array[], int size, bool (*check)(phone_subscription* element), int& result_size);

/*
  <function_name>:
              ,
          true,
    ,

:
    array       -
    size        -
    check       -    .

                   ,
    result_data - ,    - ,



          ,
     (     true)
*/


bool check_phone_subscription_by_mobile(phone_subscription* element);

/*
  check_book_subscription_by_author:
      - ,

:
    element -   ,


    true,           ,  false
*/


bool check_phone_subscription_by_date(phone_subscription* element);

/*
  check_book_subscription_by_date:
      - ,           2021-

:
    element -   ,


    true,           2021- ,  false
*/

#endif

