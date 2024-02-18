#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

class Customer {
public:
    ////////  all the getter methods ===>
    int get_customer_number() { return customer_number; }

    int get_arrival_time() const { return arrival_time; }

    int get_waiting_time() const { return waiting_time; }

    int get_finished_time() const { return finished_time; }

    int get_operations_time() { return operations_time; }

    bool get_has_vip_account() { return has_vip_account; }

    bool get_has_account() { return has_account; }

    int get_teller_number() { return teller_number; }

    //// setter methodes

    void set_customer_number(int customer_number) { this->customer_number = customer_number; }

    void set_arrival_time(int arrival_time) { this->arrival_time = arrival_time; }

    void set_waiting_time(int waiting_time) { this->waiting_time = waiting_time; }

    void set_finished_time(int finished_time) { this->finished_time = finished_time; }

    void set_operations_time(int operation_time) { this->operations_time = operation_time; }

    void set_has_vip_account(bool has_vip_account) { this->has_vip_account = has_vip_account; }

    void set_has_account(bool has_account) { this->has_account = has_account; }

    void set_teller_number(int teller_number) { this->teller_number = teller_number; }



    // generate random number to assign in operation time
    int generate_random_number() {
        srand(time(0)); // Seed the random number generator only once
        int random_number = rand() % 20 + 1; // Generate a random number between 1 and 20
        return random_number; // Return the generated number
    }

    ////////////////////////////////////////////////////////////////////////////////

private:
    int customer_number = 0;
    int arrival_time = 0;
    int waiting_time = 0;
    int operations_time = generate_random_number();
    int teller_number = 0;
    int finished_time = 0;
    bool has_vip_account;
    bool has_account;
};
