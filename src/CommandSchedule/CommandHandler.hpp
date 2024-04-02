#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "Command.hpp"

class CommandHandler
{
    private:

        struct InternalCommand 
        {
            bool didSend;
            const Command command;
        };
        vector<InternalCommand> commands; 



    public:

        vector<Command> 


};

#endif /* COMMAND_HANDLER_H */