#include <iostream>
#include <vector>
#include <string>
using namespace std;

void one_to_all_broadcast_linear_ring(int my_id, int num_processes, const string& message) {
    vector<string> received_messages(num_processes, "");

    for (char ch : message) {
        received_messages[my_id].push_back(ch);
    }

    // Perform the one-to-all broadcast
    int mask = 1;
    for (int i = 0; i < num_processes; i++) {
        if ((my_id & mask) == 0) {
            if ((my_id & (1 << i)) == 0) {
                int msg_destination = (my_id ^ (1 << i)) % num_processes;
                if (msg_destination != my_id) {
                    cout << "Process " << my_id << " sending message to process " << msg_destination << endl;
                    // Send message to msg_destination
                    received_messages[msg_destination] += received_messages[my_id];
                }
            } else {
                int msg_source = (my_id ^ (1 << i)) % num_processes;
                cout << "Process " << my_id << " receiving message from process " << msg_source << endl;
                // Receive message from msg_source
                received_messages[my_id] += received_messages[msg_source];
            }
        }
        mask |= (1 << i); // Set bit i of mask to 1
    }

    
    for (int i = 0; i < num_processes; i++) {
        if (!received_messages[i].empty()) {
            // cout << "Process " << my_id << " received message: " << received_messages[i] << endl;
        }
    }
}

int main() {
    int num_processes;
    cout << "Enter the number of processes in the linear ring: ";
    cin >> num_processes;

    cin.ignore(); 

    string message;
    cout << "Enter the message to broadcast: ";
    getline(cin, message);

    // Simulate one-to-all broadcast for each process
    for (int my_id = 0; my_id < num_processes; my_id++) {
        one_to_all_broadcast_linear_ring(my_id, num_processes, message);
        cout<<"------------------------------------------------------\n";
    }

    return 0;
}
