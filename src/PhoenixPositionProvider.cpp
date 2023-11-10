/*
process(long simTime, long deltaTime): This function is 
called once per simulation step.Use this function to update
 the internal position/rotation state.
*/

class PhoenixPosiionProvider{
    public:
        int currCoords[3] = {0, 0, 0};
        int previousRotState;
        int updatedRotState;
        int igniteCounter;
        int destroyed;
         // if it is 0, then rocket isn't ignited. If 1, then it is
        // a boolean to check if the chute has to be deployed?
        
        /*
        WHAT WE CURRENTLY UNDERSTAND:
            - There is an update loop being called in another file
            - The process function in our file will be called at each step in the loop
            - 
        */
       void process(long simTime, long deltaTime){

       }
       
       int* getPosition(){
            return currCoords;
       }



       
};