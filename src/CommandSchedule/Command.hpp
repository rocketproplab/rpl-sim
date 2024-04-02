#ifndef COMMAND_H
#define COMMAND_H

class Command
{
    private:
        
    public:
        Command(std::string description, std::string payload, double time);
        
        const std::string description;    // A human-readable name for the command
        const std::string payload;        // Text that is sent to the flight computer
        const double time;                // The time at which the command will be sent
};

#endif /* COMMAND_H */