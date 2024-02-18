#pragma once
enum Response
{
    yes = 0,
    no = 1,
};
#include <iostream>
#include<fstream>
#include <queue>
#include <list>
#include <vector>
#include <string>
#include "Customer.h"
#include "Teller.h"
using namespace std;



/////////////////////////////////////////////////////////////  comparing functions =?
///// --> for temp queue ,,only with arrival time
struct compare_function_temp_queue {
    bool operator()(Customer c1, Customer c2) {
        return c1.get_arrival_time() > c2.get_arrival_time();
    };
};
///// --> for customer queue ,,compare with arrival time and priority ->

struct compare_function_customer_queue {

    bool operator()(Customer c1, Customer c2) {
        // if customer 1 has vip account ->
        if (c1.get_has_vip_account() && !c2.get_has_vip_account())
            return false;
        // if customer 2 has vip account ->
        else if (!c1.get_has_vip_account() && c2.get_has_vip_account())
            return true;
        // if 2 customer has vip or not->
        else
            return c1.get_arrival_time() > c2.get_arrival_time();

    }

};

void show_cursor();
void color(int ForgC);
int display_menu(string& title, vector<string>& options, int x = 30, int y = 6, int xx = 10);


class Bank {
public:

    priority_queue<Customer, vector<Customer>, compare_function_customer_queue> customer_queue;
    priority_queue<Customer, vector<Customer>, compare_function_temp_queue> Temp; // Temp queue sorted by arrival time

    list<Teller> tellers_list;
    int time_Counter;
    int customer_numbers = 1;
    vector<string> yes_no = { "YES", "NO" };
    ofstream file;
    ofstream bank_data;
    vector<string> customerData;

    Bank() {
        Teller t1;
        Teller t2;
        Teller t3;

        t1.set_teller_number(1);
        t2.set_teller_number(2);
        t3.set_teller_number(3);
        tellers_list.push_back(t1);
        tellers_list.push_back(t2);
        tellers_list.push_back(t3);
    }


    vector<string> options = { "Add data to simulate with", " simulation with local data", " simulation with data file" };
    string Title = "";

    void Start_simulation() {

        time_Counter = 0;
        bool selected = false;
        while (!selected) {

            time_Counter++;
            int answer = display_menu(Title, options);

            switch (answer) {
            case 0:
                while (!Temp.empty()) {
                    Temp.pop();
                }
                Add_customer();
                selected = true;
                break;

            case 1:
                color(6);
                selected = true;
                break;

            case 2:
                color(9);
                while (!Temp.empty()) {
                    Temp.pop();
                }
                use_local_data();
                selected = true;
                break;
            }
        }

        time_Counter = 0;
        bool finish_simulation = false;

        while (!finish_simulation) {
            time_Counter++;

            // Adding to customer queue
            if (!Temp.empty() || !customer_queue.empty() || !all_tellers_finished()) {
                do {
                    if (!Temp.empty() && Temp.top().get_arrival_time() <= time_Counter) {
                        Customer c = Temp.top();
                        c.set_customer_number(customer_numbers);
                        customer_numbers++;
                        customer_queue.push(c);
                        Temp.pop();

                        if (any_teller_available()) {
                            assign_customer_to_teller();
                            make_taller_available();
                        }
                    }
                } while (!Temp.empty() && Temp.top().get_arrival_time() <= time_Counter);

                if (any_teller_available()) {
                    assign_customer_to_teller();
                }

                make_taller_available();
            }

            // Finish Condition
            if (Temp.empty() && customer_queue.empty() && all_tellers_finished()) {
                finish_simulation = true;
            }

            // Rush Hour Condition to add another teller if waiting > 10
            if (customer_queue.size() > 10 && tellers_list.size() == 3) {
                Teller t4;
                t4.set_teller_number(4);
                tellers_list.push_back(t4);
            }
        }


        generate_reportt();
    }

    void Add(int arrive, int operation_time, bool has_vip) {
        if (arrive > 100 || arrive < 0)return;
        Customer c;
        c.set_arrival_time(arrive);
        c.set_has_vip_account(has_vip);
        c.set_operations_time(operation_time);



        Temp.push(c);
    }

private:


    // Adding new Customer using console ===>
    void Add_customer() {
        int answer;
        do {
            Customer new_customer;
            add_account_type(new_customer);
            set_arrived_time(new_customer);
            Temp.push(new_customer);
            string titel1 = "Add another customer";
            answer = display_menu(titel1, yes_no, 40, 8);
            if (answer == Response::yes) {
                new_customer.set_has_vip_account(false);
            }
        } while (answer != Response::no);
    }

    //Ask if account vip or regular ==>
    void add_account_type(Customer new_customer) {
        string titel1 = "Have Account in the bank";
        int answer1 = display_menu(titel1, yes_no, 40, 8);
        if (answer1 == Response::no) {
            new_customer.set_has_vip_account(false);
            new_customer.set_has_account(false);
        }
        else {
            string titel2 = "Have an platinum account?";
            int answer2 = display_menu(titel2, yes_no, 40, 8);
            if (answer2 == Response::no) {
                new_customer.set_has_vip_account(false);
                new_customer.set_has_account(true);
            }
            else {
                new_customer.set_has_account(true);
                new_customer.set_has_vip_account(true);
            }
        }
        system("cls");
    }

    // Add arrival time ->
    void set_arrived_time(Customer& new_customer) {
        cout << "Customer arrived to the bank at ?" << endl;
        int arrival_time;
        do {
            cin >> arrival_time;
            if (arrival_time >= 100 || arrival_time <= 0) {
                if (arrival_time >= 100) {
                    string s1 = "You can't assign customer .. the bank close at 100";
                    vector<string> ss1 = { "Add arrival time", "Cancel" };
                    int answer = display_menu(s1, ss1);
                    if (answer == 1) return;
                    system("cls");
                    cout << "Customer arrived to the bank at ?" << endl;
                }
                else {
                    cout << "Enter valid Number" << endl;
                    system("cls");
                    cout << "Customer arrived to the bank at ?" << endl;
                }
            }
        } while (arrival_time > 100 || arrival_time <= 0);
        new_customer.set_arrival_time(arrival_time);
    }


    // add customer to teller =>
    void assign_customer_to_teller() {
        if (customer_queue.empty()) {
            return;
        }

        // If no teller is available, return
        if (!any_teller_available()) {
            return;
        }

        // Assign customers to available tellers
        while (!customer_queue.empty()) {
            bool customer_assigned = false;
            for (Teller& t : tellers_list) {
                if (t.is_available()) {
                    Customer customer = customer_queue.top();
                    int waiting_time = time_Counter - customer.get_arrival_time();
                    customer.set_waiting_time(waiting_time);

                    t.add_customer_to_teller();
                    customer.set_teller_number(t.get_teller_number());

                    int finish_time = time_Counter + customer.get_operations_time();
                    customer.set_finished_time(finish_time);
                    t.set_customer_finish_at(finish_time);

                    store_customer_data(customer);
                    t.set_is_available(false);

                    customer_queue.pop();
                    customer_assigned = true;
                    break;
                }
            }
            // If no more customers can be assigned, break
            if (!customer_assigned) {
                break;
            }
        }
    }
    // Check if any teller is available

    bool any_teller_available() {
        for (Teller t : tellers_list) {
            if (t.is_available())
                return true;
        }
        return false;
    }

    // remove customer from teller
    void make_taller_available() {
        for (Teller& t : tellers_list) {
            if (t.get_total_customer_served() == 0 || t.is_available()) continue; // Skip tellers with no customers or already available
            if (t.get_customer_finish_at() <= time_Counter) {
                t.set_is_available(true);
                t.set_customer_finish_at(0);
            }
        }
        //  if any teller available assign customer to it -->
        if (any_teller_available()) {
            assign_customer_to_teller();

        }
    }

    // check if all the tellers are available
    bool all_tellers_finished() {
        for (Teller t : tellers_list) {
            if (!t.is_available()) {
                return false;
            }
        }
        return true;
    }




    // store the customer's data in the data vector -->
    void store_customer_data(Customer& customer) {
        string customerInfo = "Customer number: " + to_string(customer.get_customer_number()) + "\n"
            + "Arrival time: " + to_string(customer.get_arrival_time()) + "\n"
            + "Waiting time: " + to_string(customer.get_waiting_time()) + "\n"
            + "Services Time: " + to_string(customer.get_operations_time()) + "\n"
            + "Finished time: " + to_string(customer.get_finished_time()) + "\n"
            + "Teller: " + to_string(customer.get_teller_number()) + "\n"
            + "Account Type: " + (customer.get_has_vip_account() ? "VIP" : "Regular") + "\n";
        customerData.push_back(customerInfo);
    }

    //     print and write the report
    void generate_reportt() {
        ofstream report_file("report-file.txt");
        system("cls");
        cout << "Customer report:" << endl;
        for (string info : customerData) {
            report_file << info << endl;
            cout << info << endl;

        }

        cout << "************==================*******************" << endl;
        report_file << "************==================*******************" << endl;
        for (Teller t : tellers_list) {
            report_file << "Teller: " << t.get_teller_number() << " Serve: " << t.get_total_customer_served()
                << endl;
            cout << "Teller: " << t.get_teller_number() << " Serve: " << t.get_total_customer_served() << endl;

        }
        report_file.close();
    }

    // read data from txt file to use it
    void use_local_data() {

        ifstream data_file("simulation-data.txt");
        if (!data_file.is_open()) {
            return;
        }
        string customer;
        while (getline(data_file, customer)) {
            int arrival, operation_time;
            bool vip;
            Customer c;
            size_t start = customer.find('(');
            size_t comma_1 = customer.find(',', start);
            string num = customer.substr(start + 1, comma_1 - start - 1);
            arrival = stoi(num);

            size_t comma_2 = customer.find(',', comma_1 + 1);
            size_t end = customer.find(')', comma_2);
            num = customer.substr(comma_1 + 1, comma_2 - comma_1 - 1);
            operation_time = stoi(num);

            string vip_status = customer.substr(comma_2 + 1, end - comma_2 - 1);
            if (vip_status == "true")vip = true;
            if (vip_status == "false") vip = false;
            Add(arrival, operation_time, vip);

        }
        data_file.close();

    }

};
