#ifndef FLUX_H
#define FLUX_H

#include "fluxAbstract.h"
#include "handleBody.h"

/**
 * @brief Class that contains 2 systems (source and target) and calculates the flux of values between them. Inherit from the pure abstract class FluxBase.
 * 
 */
class FluxBody : public Body {
    protected:
        /**
         * @brief Source System
         * 
         */
        SystemAbstract* source;
        /**
         * @brief Target System
         * 
         */
        SystemAbstract* target;
        /**
         * @brief Boolean variable that indicates the flux direction
         * 
         */
        bool fluxDirection;
        /**
         * @brief Calculated from source's or target's value, depending on the flux direction
         * 
         */
        double lastValue;
        /**
         * @brief Flux's name for identification
         * 
         */
        string name;
        /**
         * @brief Function provided by the client, used to calculate the transit of values
         * 
         */
        double (*func)(SystemAbstract* a);

    public:
//        /**
//         * @brief Construct a new Flux object
//         * 
//         */
//        Flux();
//        
//        /**
//         * @brief Construct a new Flux object
//         * 
//         * @param source Source system of the flux
//         * @param target Target system of the flux
//         * @param fluxDirection Indicates if the value to be used belongs to source or target flux
//         * @param lastValue Value calculated from the last function execution
//         * @param name Flux's name
//         * @param func Function pointer that is used to calculate the transit of values
//         */
//        Flux(SystemAbstract* source, SystemAbstract* target, bool fluxDirection, double lastValue, string name, double (*func) (SystemAbstract* a));

//        /**
//         * @brief Construct a new Flux object
//         * 
//         * @param rhs Const Flux object used to construct a Flux copy
//         */
//        Flux(const Flux& rhs); 
//
//        /**
//         * @brief Destroy the Flux object
//         * 
//         */
//        virtual ~Flux();

        /**
         * @brief Set the Source object
         * 
         * @param source Source system of the flux
         */
        void setSource(SystemAbstract* source);
        /**
         * @brief Set the Target object
         * 
         * @param target Target system of the flux
         */
        void setTarget(SystemAbstract* target);
        /**
         * @brief Set the Func object
         * 
         * @param func Function pointer that is used to calculate the transit of values
         */
        void setFunc(double (*func) (SystemAbstract* a));
        /**
         * @brief Set the Flux Direction object
         * 
         * @param fluxDirection Indicates if the value to be used belongs to source or target flux
         */
        void setFluxDirection(bool fluxDirection);
        /**
         * @brief Set the Last Value object
         * 
         * @param lastValue Value calculated from the last function execution
         */
        void setLastValue(double lastValue);
        /**
         * @brief Set the Name object
         * 
         * @param name Flux's name
         */
        void setName(string name);
        /**
         * @brief Get the Source object
         * 
         * @return System* 
         */
        SystemAbstract* getSource();
        /**
         * @brief Get the Target object
         * 
         * @return System* 
         */
        SystemAbstract* getTarget();
        /**
         * @brief Get the Flux Direction object
         * 
         * @return true 
         * @return false 
         */
        bool getFluxDirection();
        /**
         * @brief Get the Last Value object
         * 
         * @return double 
         */
        double getLastValue();
        /**
         * @brief Get the Name object
         * 
         * @return string 
         */
        string getName();

        /**
         * @brief Remove the source system, setting it's pointer to NULL
         * 
         */
        void removeSource();
        /**
         * @brief Remove the target system, setting it's pointer to NULL
         * 
         */
        void removeTarget();

        /**
         * @brief Executes double (*func)(System* a) and set this->lastValue with the function's return.
         * 
         */
        void execute();

//        /**
//         * @brief Constructs the output string used by << overload
//         * 
//         * @param out String to be printed with flux's data
//         */
//        virtual void fluxOut (ostream &out);
//        /**
//         * @brief Overloads << operator
//         * 
//         * @param out String to be printed with flux's data
//         * @param flux Flux pointer that references variables used on cout
//         * @return ostream& 
//         */
//        friend ostream &operator <<(ostream & out, Flux &flux);
//        /**
//         * @brief Overloads = operator
//         * 
//         * @param a const Flux memory address
//         * @return Flux& 
//         */
//        Flux & operator=(const Flux &a);
};

class FluxHandle : public FluxAbstract, public Handle<FluxBody> {
    public:
    FluxHandle(SystemAbstract* source = NULL, SystemAbstract* target = NULL, bool fluxDirection = true, double lastValue = 0.0, string name = "", double (*func) (SystemAbstract* a) = NULL){
        pImpl_->setSource(source);
        pImpl_->setTarget(target);
        pImpl_->setFluxDirection(fluxDirection);
        pImpl_->setLastValue(lastValue);
        pImpl_->setName(name);
        pImpl_->setFunc(func);
    }

    virtual ~FluxHandle() {}
    void setSource(SystemAbstract* source) { pImpl_->setSource(source); }
    void setTarget(SystemAbstract* target) { pImpl_->setTarget(target); }
    void setFluxDirection(bool fluxDirection) { pImpl_->setFluxDirection(fluxDirection); }
    void setLastValue(double lastValue) { pImpl_->setLastValue(lastValue); }
    void setName(string name) { pImpl_->setName(name); }
    void setFunc(double (*func) (SystemAbstract* a)) { pImpl_->setFunc(func); }
    SystemAbstract* getSource() { return pImpl_->getSource(); }
    SystemAbstract* getTarget() { return pImpl_->getTarget(); }
    bool getFluxDirection() { return pImpl_->getFluxDirection(); }
    double getLastValue() { return pImpl_->getLastValue(); }
    string getName() { return pImpl_->getName(); }
    void removeSource() { return pImpl_->removeSource(); } 
    void removeTarget() { return pImpl_->removeTarget(); }
    void execute() { return pImpl_->execute(); }
};

#endif