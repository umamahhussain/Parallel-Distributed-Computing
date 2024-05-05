#include <iostream>
#include <vector>

using namespace std;

void general_one_to_all_bc(int d, int my_id, int source, string X) {
    int my_virtual_id = my_id ^ source;
    int mask = (1 << d) - 1;

    for (int i = d - 1; i >= 0; i--) {
        mask ^= (1 << i);

        if ((my_virtual_id & mask) == 0) {
            if ((my_virtual_id & (1 << i)) == 0) {
                int virtual_dest = my_virtual_id ^ (1 << i);
                int physical_dest = virtual_dest ^ source;
                cout << "Sending message \"" << X << "\" from process " << my_id << " to process " << physical_dest << endl;
                
            } else {
                int virtual_source = my_virtual_id ^ (1 << i);
                int physical_source = virtual_source ^ source;
                cout << "Receiving message \"" << X << "\" at process " << my_id << " from process " << physical_source << endl;
                
            }
        }
    }
}

int main() {
    int d = 3; // Dimension of hypercube
    int source = 0; // Source node
    int num_processes = 8; // Number of processes in the hypercube

    // Simulating one-to-all broadcast for each process
    for (int my_id = 0; my_id < num_processes; my_id++) {
        string message = "Hello";
        general_one_to_all_bc(d, my_id, source, message);
        cout<<"------------------------------------------------------\n";
    }

    return 0;
}
