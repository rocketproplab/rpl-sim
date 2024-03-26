class PhoenixPositionProvider{
    private:
        // x, y, z position
        double currCoords[3] = {0, 0, 0};

    public:
        enum class State {
            PRE_FLIGHT,
            BURN,
            COAST,
            DROGUE,
            CHUTE
        };

        PhoenixPositionProvider();
        void process(double simTime, double deltaTime);
        double* getPosition();
        State rocketState;
};