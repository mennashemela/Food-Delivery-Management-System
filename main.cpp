//nadeen mohamed farid 20245070 g6
//yassin nabil mohamed 20245076 g7
#include "order.h"
#include "customer.h"
#include "deliveryDriver.h"
#include "ENUMS.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <fstream> 

using namespace std;

struct OrderRecord {
    char orderId[10];
    double total;
    char status[20];
    char customerName[30];
    char driverName[30];
};

void saveCompletedOrders(order**orders,int count){
    ofstream file("completed_orders.txt");
    cout<<"saving file"<<endl;
    if(file.is_open()){
        for(int i=0 ; i< count; i++){
            order*currentOrder=orders[i];
            if (currentOrder && currentOrder->getStatus() == OrderStatus::DELIVERED) {
                file << *currentOrder <<endl; }}
        cout<<"file saved successfully"<<endl;
        file.close();}
    else{cout<<"unable to open file"<<endl;}}

void saveDriverStatistics(deliveryDriver** drivers, int count){
    ofstream file("driver_stats.txt");
    cout<<"saving driver stat file"<<endl;
    if(file.is_open()){
        for(int i=0 ; i< count; i++){
            deliveryDriver*driver=drivers[i];
            if(driver) {
                file << "ID:" << driver->getuserid()
                     << "Name: " << driver->getname()
                     << "Deliveries: " << driver->getcompletedDeliveries()
                     << "Earnings: " << driver->gettotalEarnings() << " EGP\n";}}
        cout<<"report saved successfully"<<endl;
        file.close();}
    else{cout<<"unable to open file"<<endl;}}

void saveOrderToBinary(order** orders, int count, const string& filename) {
    ofstream file(filename, ios::binary | ios::out | ios::trunc);
    if (!file.is_open()) {
        cerr << " Could not open binary file for writing" << endl;
        return;}

    file.write(reinterpret_cast<const char*>(&count), sizeof(int));

    for (int i = 0; i < count; ++i) {
        order* currentOrder = orders[i];
        OrderRecord record;
        strncpy(record.orderId, currentOrder->getorderId().c_str(), 9);
        record.orderId[9] = '\0';
        strncpy(record.status, orderStatusToString(currentOrder->getStatus()).c_str(), 19);
        record.status[19] = '\0';

        record.total = currentOrder->calculateTotal();

        file.write(reinterpret_cast<const char*>(&record), sizeof(OrderRecord));}
    file.close();
    cout << "SUCCESS: " << count << " orders saved to binary file " << filename << endl;}

void loadOrderByPosition(const string& filename, int position) {
    ifstream file(filename, ios::binary | ios::in);
    if (!file.is_open()) {
        cerr << " Could not open binary file '" << filename << "' for reading. Did you save it first?" << endl;
        return;}
    if (position < 0) {
        cerr << " Position must be non-negative." << endl;
        file.close();
        return;}

    int totalCount = 0;
    file.read(reinterpret_cast<char*>(&totalCount), sizeof(int));

    if (position >= totalCount || file.fail()) {
        cerr << " Failed to read record at position " << position
             << ". Only " << totalCount << " records exist in the file." << endl;
        file.close();
        return;}


    auto start_time = chrono::high_resolution_clock::now();


    long recordSize = sizeof(OrderRecord);
    long offset = sizeof(int) + (static_cast<long>(position) * recordSize);

    file.seekg(offset, ios::beg);

    OrderRecord record;
    file.read(reinterpret_cast<char*>(&record), recordSize);

    auto end_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);


    if (file.gcount() == sizeof(OrderRecord)) {
        cout << "\n--- Binary Record Loaded (O(1)) ---" << endl;
        cout << "Position in file: " << position << endl;
        cout << "Order ID: " << record.orderId << endl;
        cout << "Status: " << record.status << endl;
        cout << "Total: " <<fixed <<record.total << " EGP" <<endl;
        cout << "Time taken (microseconds): " << duration.count() <<endl;}
    else {cerr << "ERROR: Reached end of file or failed to read complete record." <<endl;}

    file.close();}


void displayMainMenu() {
    cout << "\n==========================================" << endl;
    cout << "=== ELEMUS MANAGEMENT SYSTEM v1.0 ===" << endl;
    cout << "==========================================" << endl;
    cout << "=== USER MANAGEMENT ==="<<endl;
    cout << "1. Register New Customer"<<endl;
    cout << "2. Register New Delivery Driver"<<endl;
    cout << "==========================================" << endl;
    cout << "=== ORDER MANAGEMENT ==="<<endl;
    cout << "3. Create New Order"<<endl;
    cout << "4. Add Items to Order"<<endl;
    cout << "5. Assign Driver to Order"<<endl;
    cout << "6. Update Order Status"<<endl;
    cout << "7. Display Order Details"<<endl;
    cout << "==========================================" << endl;
    cout << "=== INFORMATION & REPORTS ==="<<endl;
    cout << "8. Display Customer Information"<<endl;
    cout << "9. Display Driver Information"<<endl;
    cout << "10. Compare Two Orders by Total"<<endl;
    cout << "11. Display System Statistics"<<endl;
    cout << "==========================================" << endl;
    cout << "=== FILE OPERATIONS ==="<<endl;
    cout << "12. Save Completed Orders to File (Text)"<<endl;
    cout << "13. Save Driver Statistics to File (Text)"<<endl;
    cout << "==========================================" << endl;
    cout << "=== BONUS FEATURES (Requires 14 to be run first ==="<<endl;
    cout << "14. Save Orders to Binary File (orders.dat)"<<endl;
    cout << "15. Load Order by Position (O(1))"<<endl;
    cout << "16. Binary File Statistics"<<endl;
    cout << "==========================================" << endl;
    cout << "17. Exit System"<<endl;
    cout << "\nPick your choice: ";}


int main(){

    const int MAX_USERS = 100;
    const int MAX_ORDERS = 100;

    customer* customers[MAX_USERS] = {nullptr};
    deliveryDriver* drivers[MAX_USERS] = {nullptr};
    order* orders[MAX_ORDERS] = {nullptr};

    int customerCount = 0;
    int driverCount = 0;
    int orderCount = 0;


    int choice;

    do{
        displayMainMenu();
        cin>>choice;
        string id, id1, id2;
        order* targetOrder = {nullptr};
        customer* targetCustomer = {nullptr};
        deliveryDriver* targetDriver = {nullptr};



        switch(choice){

            case 1 :{
                if (customerCount >= MAX_USERS) { cout << "System limit reached. Cannot add more customers." << endl; break; }

                string id, name, phone, addr;
                cout << "Enter customer ID: ";
                cin >> id;
                cout << "\n Enter name: ";
                cin>>name;
                cout << "\n Enter phone: ";
                cin >> phone;
                cout << "Enter address: ";
                cin>>addr;

                customers[customerCount] = new customer(id, name, phone, addr, 0);
                customerCount++;
                cout << "\n new customer registered "<<endl;
                break;}
            case 2 :
            {if (customerCount >= MAX_USERS) { cout << "System limit reached. Cannot add more customers." << endl; break; }

                string id , name , phone , veh;

                cout << "\n Enter driver ID: ";
                cin >> id;
                cout << "\n Enter name: ";
                cin>>name;
                cout << "\n Enter phone: ";
                cin >> phone;
                cout << "\n Enter vehicle type: ";
                cin>>veh;

                drivers[driverCount] = new deliveryDriver(id, name, phone, veh, 0, 0.0);
                driverCount++;
                cout << "\n new driver registered "<<endl;
                break;}

            case 3:
            {if (orderCount >= MAX_ORDERS) { cout << "system limit reached. Cannot add more orders" << endl; break; }
                if (customerCount == 0) { cout << "no customers registered. Cannot create order" << endl; break; }

                string oid;
                int cid;
                cout << "Enter order ID: ";
                cin >> oid;
                cout << "Pick customer index (0 to " << customerCount - 1 << "): ";
                cin>>cid;

                if (cid < 0 || cid >= customerCount)
                    cout << "Invalid customer index!"<<endl;
                else {
                    orders[orderCount] = new order(oid, customers[cid]);
                    orderCount++;
                    cout << "order Created"<<endl;}
                break;}



            case 4:
            { if (orderCount == 0) { cout << "no orders available" << endl; break; }

                int oid;
                cout << "Enter order index (0 to " << orderCount - 1 << "): ";
                cin>>oid;

                if (oid < 0 || oid >= orderCount){cout << "Invalid order index"<<endl;}

                else {
                    string name; double price; int qty;
                    cout << "\n Item name: ";
                    cin>>name;
                    cout << "\n Price: ";
                    cin>>price;
                    if ( price <= 0) { cout << "Invalid price."<<endl;
                        break; }
                    cout << "Quantity: ";
                    cin>>qty;
                    if ( qty <= 0) { cout << "\n Invalid quantity."<<endl;
                        ; break; }

                    FoodItem item(name, price, qty);
                    *orders[oid] += item;
                    cout << "new item added , New total: " << orders[oid]->calculateTotal() << " EGP\n";}
                break;}



            case 5:
            { if (orderCount == 0 || driverCount == 0) { cout << "no orders or drivers available" << endl; break; }
                int oid, did;
                cout << "Enter order index (0 to " << orderCount - 1 << "): ";
                cin>>oid;
                cout << "Enter driver index (0 to " << driverCount - 1 << "): ";
                cin>>did;

                if (oid < 0 || oid >= orderCount || did < 0 || did >= driverCount)
                    cout << "invalid indexes!"<<endl;
                else {orders[oid]->assignDriver(drivers[did]);
                    cout << "driver " << drivers[did]->getname() << " assigned to Order " << orders[oid]->getorderId()<<endl;}
                break;}


            case 6: {
                if (orderCount == 0) { cout << "No orders available." << endl; break; }

                int oid, s;
                cout << "Enter order index (0 to " << orderCount - 1 << "): "<<endl;
                cin>>oid;

                cout << "Status (0=PENDING, 1=PREPARING, 2=OUT, 3=DELIVERED, 4=CANCELLED): ";
                cin>>s;
                if ( s < 0 || s > 4) { cout << "Invalid status input."<<endl;
                    break; }

                if (oid < 0 || oid >= orderCount) {cout << "Wrong order index"<<endl;}
                else {
                    orders[oid]->updateStatus(static_cast<OrderStatus>(s));
                    cout << "Status updated to " << orderStatusToString(orders[oid]->getStatus()) << endl;}
                break;}


            case 7:
            { if (orderCount == 0) { cout << "No orders available." << endl; break; }
                int oid;
                cout << "Enter order index (0 to " << orderCount - 1 << "): ";
                cin>>oid;
                if (oid < 0 || oid >= orderCount) {cout << "Wrong order index"<<endl;}
                else {
                    orders[oid]->displayOrder();}
                break;}


            case 8:
            { if (customerCount == 0) { cout << "No customers registered." << endl; break; }
                int cid;
                cout << "Enter customer index (0 to " << customerCount - 1 << "): ";
                cin>>cid;
                if (cid < 0 || cid >= customerCount) {cout << "Wrong customer index"<<endl;}
                else {
                    customers[cid]->displayinfo();}
                break;}


            case 9:
            { if (driverCount == 0) { cout << "No drivers registered." << endl; break; }
                int did;
                cout << "Enter driver index (0 to " << driverCount - 1 << "): ";
                cin>>did;
                if (did < 0 || did >= driverCount) {cout << "Wrong driver index"<<endl;}
                else {
                    drivers[did]->displayinfo();}
                break;}


            case 10:
            { if (orderCount < 2) { cout << "Need at least 2 orders to compare." << endl; break; }
                int oid1, oid2;
                cout << "Enter first order index (0 to " << orderCount - 1 << "): ";
                cin>>oid1;
                cout << "Enter second order index (0 to " << orderCount - 1 << "): ";
                cin>>oid2;

                if (oid1 < 0 || oid1 >= orderCount || oid2 < 0 || oid2 >= orderCount)
                    cout << "Invalid order index(es)"<<endl;
                else {
                    if (*orders[oid1] > *orders[oid2]) {
                        cout << "Order " << orders[oid1]->getorderId() << " (Total: " << orders[oid1]->calculateTotal()
                             << ") is more expensive than Order " << orders[oid2]->getorderId()
                             << " (Total: " << orders[oid2]->calculateTotal() << ")"<<endl;}
                    else if (*orders[oid2] > *orders[oid1]) {
                        cout << "Order " << orders[oid2]->getorderId() << " (Total: " << orders[oid2]->calculateTotal()
                             << ") is more expensive than Order " << orders[oid1]->getorderId()
                             << " (Total: " << orders[oid1]->calculateTotal() << ")"<<endl;}
                    else {
                        cout << "Orders are the same price."<<endl;}}
                break;}


            case 11:
            { cout << "\n=== SYSTEM STATISTICS ==="<<endl;
                cout << "Total Users (Customers + Drivers): " << user::gettotalusers() << endl;
                cout << "Registered Customers: " << customerCount << endl;
                cout << "Registered Drivers: " << driverCount << endl;
                cout << "Total Orders Created: " << order::getTotalOrders() << endl;
                break;}


            case 12:
            { saveCompletedOrders(orders, orderCount);
                break;}


            case 13:
            { saveDriverStatistics(drivers, driverCount);
                break;}


            case 14:
            { saveOrderToBinary(orders, orderCount, "orders.dat");
                break;}


            case 15:
            { int pos;
                cout << "Enter order position to load (0 to " << orderCount - 1 << "): ";
                cin>>pos;
                loadOrderByPosition("orders.dat", pos);
                break;}


            case 16:
            { cout << "\n=== BINARY FILE STATISTICS ==="<<endl;
                cout << "Size of OrderRecord struct: " << sizeof(OrderRecord) << " bytes" << endl;
                cout << "Total records (orders) saved: " << orderCount << endl;
                cout << "Expected file size (excluding header): " << orderCount * sizeof(OrderRecord) << " bytes" << endl;
                cout << "File 'orders.dat' includes an initial 4-byte integer for total count." << endl;
                break;}


            case 17:
            { cout << "Exiting system. Cleaning up memory..."<<endl;
                for (int i = 0; i < customerCount; i++) delete customers[i];
                for (int i = 0; i < driverCount; i++) delete drivers[i];
                for (int i = 0; i < orderCount; i++) delete orders[i];
                break;}

            default:
            { cout << "Invalid choice. Please try again." << endl;
                break;}
        }

    } while (choice != 17);

    return 0;
}