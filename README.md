# Bank Queue Management System (BQMS)

## Overview

BQMS is a simulation project designed to emulate a bank queue management system. It enables users to add customers, manage queues, assign tellers, and generate reports on customer service and teller performance. The project offers flexibility in data input, allowing users to simulate with data from a text file, manually enter data during runtime, or utilize pre-defined data within the IDE.

## Features

- **Customer Management**: Add customers manually or from a data file.
- **Queue Management**: Simulate customer queue management and teller assignments.
- **Reporting**: Generate reports on customer service and teller performance.
- **Customization**: Customize simulation parameters such as arrival times and service times.
- **Command-Line Interface (CLI)**: Intelligible command-line interface for ease of use.
- **Rush Hour Handling**: Automatically adds tellers during rush hours when all tellers are busy and there are more than 10 customers waiting.

## Getting Started

To get started with the project, follow these steps:

1. Clone the repository: `https://github.com/moudy99/bank-queue-management-system.git`
2. Navigate to the project directory: `cd bank-queue-management-system`
3. Compile the source code: `make`
4. Run the simulation: `BQMS.exe`

## Usage

### Adding Customers

You can add customers manually by following the prompts or by providing data from a file.

### Running the Simulation

Once customers are added, you can start the simulation. The simulation will continue until all customers are served, displaying reports on customer service and teller performance. During rush hours, a new teller will be automatically added if all tellers are busy and there are more than 10 customers waiting.

## Configuration

Various simulation parameters can be configured, such as the number of tellers, queue management strategies, and simulation duration, either by modifying the source code or providing command-line arguments.

## Reports

After the simulation, portable text report files are generated containing information such as arrival time, waiting time, service time, teller number, and account type for each customer.

## Data Sources

You can simulate with data from a text file or enter data manually through the console while the program is running.

## License

This project is licensed under the MIT License. See the [MOUDY RASMY](https://github.com/moudy99) file for details.

## Contact

For questions or feedback, feel free to contact the project maintainer:

- Name: Moudy Rasmy
- Email: moudy99.rasmy@gmail.com
#
