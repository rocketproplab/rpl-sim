#include <fstream>
#include <iostream>
#include <json.hpp>
#include <string>
#include <vector>

enum SolenoidState { CLOSED, OPEN };
using json = nlohmann::json;

class ValveState {
   public:
    std::string name;
    SolenoidState state;

    json serialize()
    {
        json j;
        j["name"] = name;
        j["state"] = state == SolenoidState::OPEN ? "OPEN" : "CLOSED";
        return j;
    }
};

class Entry {
   public:
    double time;
    double x_pos;
    double y_pos;
    double z_pos;
    ValveState valve_state;

    json serialize()
    {
        json j;
        j["time"] = time;
        j["x_pos"] = x_pos;
        j["y_pos"] = y_pos;
        j["z_pos"] = z_pos;
        j["valve_state"] = valve_state.serialize();
        return j;
    }
};

class DataLog {
   public:
    std::vector<Entry> entries;
    void add_entry(Entry entry) { entries.push_back(entry); }
    json serialize()
    {
        json j;
        for (auto entry : entries) {
            j.push_back(entry.serialize());
        }
        return j;
    }

    void write_to_file(std::string filename)
    {
        std::ofstream file;
        file.open(filename);
        file << serialize().dump(4);
        file.close();
    }
};
