#ifndef MODEL_H
#define MODEL_H

#include "modelAbstract.h"
#include "handleBody.h"

/**
 * @brief Class that contains all systems and executes every FluxAbstract in the determined interval of time
 * 
 */
class ModelBody : public Body {
    private:
        /**
         * @brief Adds a SystemAbstract* to the model
         * 
         * @param SystemAbstract SystemAbstract to be added
         */
        void add(SystemAbstract* SystemAbstract);
        /**
         * @brief Adds a FluxAbstract* to the model
         * 
         * @param FluxAbstract FluxAbstract to be added
         */
        void add(FluxAbstract* Flux);
        /**
         * @brief Add a ModelAbstract* to the model
         * 
         * @param model Model to be inserted
         */
        static void add(ModelAbstract* Model);
    protected:
        /**
         * @brief Current time
         * 
         */
        double time;
        /**
         * @brief Vector of pointers to fluxes
         * 
         */
        vector<FluxAbstract*> fluxes;
        /**
         * @brief Vector of pointers to systems
         * 
         */
        vector<SystemAbstract*> systems;
        /**
         * @brief Vector of models
         * 
         */
        static vector<ModelAbstract*> models;

    public:
        /**
         * @brief Removes a SystemAbstract* from the model's vector of systems
         * 
         * @param sys SystemAbstract to be removed
         */
        void remove(SystemAbstract* sys);
        /**
         * @brief Removes a FluxAbstract* from the model's vector of fluxes
         * 
         * @param FluxAbstract FluxAbstract to be inserted
         */
        void remove(FluxAbstract* FluxAbstract);
        /**
         * @brief Remove a ModelAbstract* from the model's vector of models
         * 
         * @param model Model to be inserted
         */
        void remove(ModelAbstract* model);
        ///**
        // * @brief Construct a new Model object
        // * 
        // */
        //Model();
        //
        ///**
        // * @brief Construct a new Model object
        // * 
        // * @param time Current model time
        // * @param f Fluxes that shall belong to the model
        // * @param s Systems that shall belong to the model
        // */
        //Model(double time, vector<FluxAbstract*> f, vector<SystemAbstract*> s);
        //
        ///**
        // * @brief Construct a new Model object
        // * 
        // * @param a Const Model object used to construct a Model copy
        // */
        //Model(const Model& a);
        ///**
        // * @brief Destroy the Model object
        // * 
        // */
        virtual ~ModelBody() {}
        /**
         * @brief Set the Time object
         * 
         * @param time Current time
         */
        void setTime(double time);
        /**
         * @brief Get the Time object
         * 
         * @return double 
         */
        double getTime();
        /**
         * @brief Executes every fluxe's functions and assigns the difference of values according to the FluxAbstract direction
         * 
         * @param start Initial time
         * @param end End time
         * @param increase Increase rate
         */
        void execute(double start, double end, double increase);
        /**
         * @brief System factory
         * 
         * @param value System's current value
         * @return SystemAbstract* 
         */
        SystemAbstract* createSystem(string name, double value);
        /**
         * @brief Flux factory
         * 
         * @param source Source system of the flux
         * @param target Target system of the flux
         * @param fluxDirection Indicates if the value to be used belongs to source or target flux
         * @param lastValue Value calculated from the last function execution
         * @param name Flux's name
         * @param func Function pointer that is used to calculate the transit of values
         * @return FluxAbstract* 
         */
        FluxAbstract* createFlux(SystemAbstract* source, SystemAbstract* target, bool fluxDirection, double lastValue, string name, double (*func) (SystemAbstract* a));
        /**
         * @brief Create a Model object
         * 
         * @param time Model's time
         * @param f flux vector
         * @param s system vector
         * @return ModelAbstract& 
         */
        static ModelAbstract* createModel();
        /**
         * @brief 
         * 
         * @return vector<FluxAbstract*>::iterator 
         */
        vector<FluxAbstract*>::iterator getFluxesBegin();
        /**
         * @brief 
         * 
         * @return vector<FluxAbstract*>::iterator 
         */
        vector<FluxAbstract*>::iterator getFluxesEnd();
        /**
         * @brief 
         * 
         * @return vector<SystemAbstract*>::iterator 
         */
        vector<SystemAbstract*>::iterator getSystemsBegin();
        /**
         * @brief Get the Models Begin object
         * 
         * @return vector<ModelAbstract*>::iterator 
         */
        vector<ModelAbstract*>::iterator getModelsBegin();
        /**
         * @brief Get the Models End object
         * 
         * @return vector<ModelAbstract*>::iterator 
         */
        vector<ModelAbstract*>::iterator getModelsEnd();
        /**
         * @brief 
         * 
         * @return vector<FluxAbstract*>::iterator 
         */
        vector<SystemAbstract*>::iterator getSystemsEnd();
        ///**
        // * @brief Overloads = operator
        // * 
        // * @param a const Model object
        // * @return Model& 
        // */
        //Model & operator=(const Model &a);
};

class ModelHandle : public ModelAbstract, public Handle<ModelBody> {
    public:
    ModelHandle(double time = 0) { pImpl_->setTime(time); }
    virtual ~ModelHandle() {
        pImpl_->setTime(0.0);
    }

    void remove (SystemAbstract* sys) { pImpl_->remove(sys); }
    void remove (FluxAbstract* flux) { pImpl_->remove(flux); }
    void remove (ModelAbstract* model) { pImpl_->remove(model); }

    SystemAbstract* createSystem(string name, double value) {return pImpl_->createSystem(name, value);}
    FluxAbstract* createFlux(SystemAbstract* source, SystemAbstract* target, bool fluxDirection, double lastValue, string name, double (*func) (SystemAbstract* a)) { return pImpl_->createFlux(source, target, fluxDirection, lastValue, name, func); }

    void execute(double start, double end, double increase) { pImpl_->execute(start, end, increase); }
    void setTime(double time) { pImpl_->setTime(time); }
    double getTime() { return pImpl_->getTime(); }
    vector<FluxAbstract*>::iterator getFluxesBegin() { return pImpl_->getFluxesBegin(); }
    vector<FluxAbstract*>::iterator getFluxesEnd() { return pImpl_->getFluxesEnd(); }
    vector<SystemAbstract*>::iterator getSystemsBegin() { return pImpl_->getSystemsBegin(); }
    vector<SystemAbstract*>::iterator getSystemsEnd() { return pImpl_->getSystemsEnd(); }
    vector<ModelAbstract*>::iterator getModelsBegin() { return pImpl_->getModelsBegin(); }
    vector<ModelAbstract*>::iterator getModelsEnd() { return pImpl_->getModelsEnd(); }
};

#endif