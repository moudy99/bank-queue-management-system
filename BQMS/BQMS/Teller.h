#pragma once

#include "Customer.h"
#include <iostream>

using namespace std;

class Teller {
public:

    ////////   getter methods ===>
    int get_teller_number() { return teller_number; }

    bool is_available() { return is__available; }


    /////// all the setter methods ===>

    void set_teller_number(int teller_number) { this->teller_number = teller_number; }

    void set_is_available(bool is_available) { this->is__available = is_available; }

    void add_customer_to_teller() { total_customer_served++; }

    int get_total_customer_served() { return total_customer_served; }



    void set_customer_finish_at(int customer_finish_at) { this->customer_finish_at = customer_finish_at; }

    int get_customer_finish_at() { return customer_finish_at; }


private:
    int teller_number;
    bool is__available = true;
    int customer_finish_at;
    int total_customer_served = 0;
};
