#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
using namespace std;
class SmartDevice {
private:
    string deviceId;
    string name;

public:
    SmartDevice(const string& id, const string& deviceName)
        : deviceId(id), name(deviceName) {
        setDeviceId(id);
        setName(deviceName);
    }

    virtual ~SmartDevice() = default;

    string getDeviceId() const { return deviceId; }
    string getName() const { return name; }

    void setDeviceId(const string& id) {
        if (id.empty()) {
            throw invalid_argument("Device ID cannot be empty.");
        }
        deviceId = id;
    }

    void setName(const string& deviceName) {
        if (deviceName.empty()) {
            throw invalid_argument("Device name cannot be empty.");
        }
        name = deviceName;
    }

    virtual string getType() const = 0;
    virtual void display() const = 0;
    virtual string serialize() const = 0;
};


class SmartLight : public SmartDevice {
private:
    bool isOn;
    int brightness;

public:
    SmartLight(const string& id, const string& name,
               bool on = false, int level = 100)
        : SmartDevice(id, name), isOn(false), brightness(100) {
        setIsOn(on);
        setBrightness(level);
    }

    bool getIsOn() const { return isOn; }
    int getBrightness() const { return brightness; }

    void setIsOn(bool value) {
        isOn = value;
    }

    void setBrightness(int level) {
        if (level < 0 || level > 100) {
            throw invalid_argument("Brightness must be between 0 and 100.");
        }
        brightness = level;

        if (brightness == 0) {
            isOn = false;
        }
    }

    void turnOn() { isOn = true; }
    void turnOff() { isOn = false; }

    void dim(int level) {
        setBrightness(level);
    }

    string getType() const override {
        return "LIGHT";
    }

    void display() const override {
        cout << "[Light] " << getDeviceId()
             << " | " << getName()
             << " | " << (isOn ? "ON" : "OFF")
             << " | Brightness: " << brightness << "%\n";
    }

    string serialize() const override {
        return "LIGHT|" + getDeviceId() + "|" + getName() + "|" +
               (isOn ? "1" : "0") + "|" + to_string(brightness);
    }
};


class SmartThermostat : public SmartDevice {
private:
    double temperature;

public:
    SmartThermostat(const string& id, const string& name,
                    double temp = 22.0)
        : SmartDevice(id, name), temperature(22.0) {
        setTemperature(temp);
    }

    double getTemperature() const { return temperature; }

    void setTemperature(double temp) {
        if (temp < -50.0 || temp > 60.0) {
            throw invalid_argument(
                "Temperature must be between -50 and 60 degrees Celsius.");
        }
        temperature = temp;
    }

    string getType() const override {
        return "THERMOSTAT";
    }

    void display() const override {
        cout << fixed << setprecision(1);
        cout << "[Thermostat] " << getDeviceId()
             << " | " << getName()
             << " | Temperature: " << temperature << " C\n";
    }

    string serialize() const override {
        ostringstream out;
        out << fixed << setprecision(1) << temperature;
        return "THERMOSTAT|" + getDeviceId() + "|" + getName() +
               "|" + out.str();
    }
};



class SmartDoorLock : public SmartDevice {
private:
    bool isLocked;
    string lastUnlockedBy;

public:
    SmartDoorLock(const string& id, const string& name,
                  bool locked = true,
                  const string& person = "")
        : SmartDevice(id, name), isLocked(true), lastUnlockedBy("") {
        setIsLocked(locked);
        setLastUnlockedBy(person);
    }

    bool getIsLocked() const { return isLocked; }
    string getLastUnlockedBy() const { return lastUnlockedBy; }

    void setIsLocked(bool value) {
        isLocked = value;
    }

    void setLastUnlockedBy(const string& person) {
        lastUnlockedBy = person;
    }

    void lock() {
        isLocked = true;
    }

    void unlock(const string& person) {
        if (person.empty()) {
            throw invalid_argument("Person name cannot be empty.");
        }

        isLocked = false;
        lastUnlockedBy = person;
    }

    string getType() const override {
        return "LOCK";
    }

    void display() const override {
        cout << "[Door Lock] " << getDeviceId()
             << " | " << getName()
             << " | " << (isLocked ? "LOCKED" : "UNLOCKED")
             << " | Last unlocked by: "
             << (lastUnlockedBy.empty() ? "Nobody recorded" : lastUnlockedBy)
             << "\n";
    }

    string serialize() const override {
        return "LOCK|" + getDeviceId() + "|" + getName() + "|" +
               (isLocked ? "1" : "0") + "|" + lastUnlockedBy;
    }
};



class SmartHome {
private:
    vector<unique_ptr<SmartDevice>> devices;
    const string dataFile = "devices.txt";

    bool idExists(const string& id) const {
        return find_if(devices.begin(), devices.end(),
            [&id](const unique_ptr<SmartDevice>& device) {
                return device->getDeviceId() == id;
            }) != devices.end();
    }

public:
    SmartHome() {
        load();
    }

    ~SmartHome() {
        save();
    }

    void addDevice(unique_ptr<SmartDevice> device) {
        if (idExists(device->getDeviceId())) {
            throw invalid_argument("A device with that ID already exists.");
        }

        devices.push_back(move(device));
        save();
    }

    SmartDevice* getDevice(const string& id) {
        for (auto& device : devices) {
            if (device->getDeviceId() == id) {
                return device.get();
            }
        }
        return nullptr;
    }

    void removeDevice(const string& id) {
        auto it = find_if(devices.begin(), devices.end(),
            [&id](const unique_ptr<SmartDevice>& device) {
                return device->getDeviceId() == id;
            });

        if (it == devices.end()) {
            throw invalid_argument("Device not found.");
        }

        devices.erase(it);
        save();
    }

    void displayAllDevices() const {
        cout << "\n========== ALL DEVICES ==========\n";

        if (devices.empty()) {
            cout << "No devices have been added.\n";
        } else {
            for (const auto& device : devices) {
                device->display();
            }
        }

        cout << "=================================\n";
    }

    string applyAutoMode(const SmartThermostat& thermostat) {
        bool changed = false;
        string action = "UNCHANGED";

        if (thermostat.getTemperature() > 25.0) {
            for (auto& device : devices) {
                auto* light = dynamic_cast<SmartLight*>(device.get());

                if (light != nullptr && !light->getIsOn()) {
                    light->turnOn();
                    changed = true;
                }
            }
            action = "ON";
        }
        else if (thermostat.getTemperature() < 18.0) {
            for (auto& device : devices) {
                auto* light = dynamic_cast<SmartLight*>(device.get());

                if (light != nullptr && light->getIsOn()) {
                    light->turnOff();
                    changed = true;
                }
            }
            action = "OFF";
        }

        if (changed) {
            save();
        }

        return action;
    }

    void save() const {
        ofstream file(dataFile);

        if (!file) {
            cerr << "Warning: Could not save device data.\n";
            return;
        }

        for (const auto& device : devices) {
            file << device->serialize() << '\n';
        }
    }

    void load() {
        ifstream file(dataFile);

        if (!file) {
            return;
        }

        string line;

        while (getline(file, line)) {
            if (line.empty()) {
                continue;
            }

            try {
                vector<string> fields;
                string field;
                stringstream ss(line);

                while (getline(ss, field, '|')) {
                    fields.push_back(field);
                }

                if (fields.empty()) {
                    continue;
                }

                if (fields[0] == "LIGHT" && fields.size() == 5) {
                    bool on = (fields[3] == "1");
                    int brightness = stoi(fields[4]);

                    devices.push_back(make_unique<SmartLight>(
                        fields[1], fields[2], on, brightness));
                }
                else if (fields[0] == "THERMOSTAT" && fields.size() == 4) {
                    double temperature = stod(fields[3]);

                    devices.push_back(make_unique<SmartThermostat>(
                        fields[1], fields[2], temperature));
                }
                else if (fields[0] == "LOCK" && fields.size() == 5) {
                    bool locked = (fields[3] == "1");

                    devices.push_back(make_unique<SmartDoorLock>(
                        fields[1], fields[2], locked, fields[4]));
                }
            }
            catch (...) {
                cerr << "Warning: Skipping invalid saved device data.\n";
            }
        }
    }
};



string readNonEmpty(const string& prompt) {
    while (true) {
        cout << prompt;

        string value;
        getline(cin, value);

        if (!value.empty()) {
            return value;
        }

        cout << "Invalid input. Value cannot be empty.\n";
    }
}

int readInt(const string& prompt, int minimum, int maximum) {
    while (true) {
        cout << prompt;

        string input;
        getline(cin, input);

        try {
            size_t pos = 0;
            int value = stoi(input, &pos);

            if (pos != input.size()) {
                throw invalid_argument("Invalid");
            }

            if (value < minimum || value > maximum) {
                throw out_of_range("Range");
            }

            return value;
        }
        catch (...) {
            cout << "Invalid input. Enter a whole number between "
                 << minimum << " and " << maximum << ".\n";
        }
    }
}

double readDouble(const string& prompt, double minimum, double maximum) {
    while (true) {
        cout << prompt;

        string input;
        getline(cin, input);

        try {
            size_t pos = 0;
            double value = stod(input, &pos);

            if (pos != input.size()) {
                throw invalid_argument("Invalid");
            }

            if (value < minimum || value > maximum) {
                throw out_of_range("Range");
            }

            return value;
        }
        catch (...) {
            cout << "Invalid input. Enter a number between "
                 << minimum << " and " << maximum << ".\n";
        }
    }
}



void addDeviceMenu(SmartHome& home) {
    cout << "\n========== ADD DEVICE ==========\n";
    cout << "1. Smart Light\n";
    cout << "2. Smart Thermostat\n";
    cout << "3. Smart Door Lock\n";

    int choice = readInt("Select device type: ", 1, 3);

    string id = readNonEmpty("Device ID: ");
    string name = readNonEmpty("Device name: ");

    try {
        if (choice == 1) {
            home.addDevice(make_unique<SmartLight>(id, name));
        }
        else if (choice == 2) {
            double temp = readDouble(
                "Initial temperature (C): ", -50.0, 60.0);

            home.addDevice(
                make_unique<SmartThermostat>(id, name, temp));
        }
        else {
            home.addDevice(make_unique<SmartDoorLock>(id, name));
        }

        cout << "Device added and saved successfully.\n";
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << '\n';
    }
}

void controlDeviceMenu(SmartHome& home) {
    cout << "\n========== CONTROL DEVICE ==========\n";

    string id = readNonEmpty("Enter device ID: ");
    SmartDevice* device = home.getDevice(id);

    if (device == nullptr) {
        cout << "Device not found.\n";
        return;
    }

    try {
        if (auto* light = dynamic_cast<SmartLight*>(device)) {
            cout << "1. Turn ON\n";
            cout << "2. Turn OFF\n";
            cout << "3. Set Brightness\n";

            int choice = readInt("Choose action: ", 1, 3);

            if (choice == 1) {
                light->turnOn();
            }
            else if (choice == 2) {
                light->turnOff();
            }
            else {
                int brightness = readInt(
                    "Brightness (0-100): ", 0, 100);
                light->dim(brightness);
            }

            home.save();
            cout << "Light updated and saved successfully.\n";
        }
        else if (auto* thermostat =
                     dynamic_cast<SmartThermostat*>(device)) {

            double temperature = readDouble(
                "New temperature (C): ", -50.0, 60.0);

            thermostat->setTemperature(temperature);

            string action = home.applyAutoMode(*thermostat);

            if (action == "ON") {
                cout << "Auto-Mode: temperature is above 25 C "
                        "-> all lights turned ON.\n";
            }
            else if (action == "OFF") {
                cout << "Auto-Mode: temperature is below 18 C "
                        "-> all lights turned OFF.\n";
            }
            else {
                cout << "Auto-Mode: temperature is between 18 C "
                        "and 25 C -> lights unchanged.\n";
            }

            home.save();
            cout << "Thermostat updated and saved successfully.\n";
        }
        else if (auto* lock = dynamic_cast<SmartDoorLock*>(device)) {
            cout << "1. Lock\n";
            cout << "2. Unlock\n";

            int choice = readInt("Choose action: ", 1, 2);

            if (choice == 1) {
                lock->lock();
            }
            else {
                string person =
                    readNonEmpty("Who is unlocking the door? ");
                lock->unlock(person);
            }

            home.save();
            cout << "Door lock updated and saved successfully.\n";
        }
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << '\n';
    }
}


int main() {
    SmartHome home;

    cout << "========================================\n";
    cout << "     HomeTech Solutions Smart Home\n";
    cout << "========================================\n";

    while (true) {
        cout << "\n=============== MENU ===============\n";
        cout << "1. Add Device\n";
        cout << "2. Control Device\n";
        cout << "3. View All Devices\n";
        cout << "4. Remove Device\n";
        cout << "5. Exit\n";
        cout << "====================================\n";

        int choice = readInt("Enter choice: ", 1, 5);

        if (choice == 1) {
            addDeviceMenu(home);
        }
        else if (choice == 2) {
            controlDeviceMenu(home);
        }
        else if (choice == 3) {
            home.displayAllDevices();
        }
        else if (choice == 4) {
            string id = readNonEmpty("Enter device ID to remove: ");

            try {
                home.removeDevice(id);
                cout << "Device removed and saved successfully.\n";
            }
            catch (const exception& e) {
                cout << "Error: " << e.what() << '\n';
            }
        }
        else {
            home.save();
            cout << "All data saved. Goodbye!\n";
            break;
        }
    }

    return 0;
}
