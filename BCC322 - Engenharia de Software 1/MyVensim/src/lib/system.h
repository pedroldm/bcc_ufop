#ifndef SYSTEM_H
#define SYSTEM_H

#include "systemAbstract.h"
#include "handleBody.h"

using namespace std;

/**
 * @brief Class that represents a system/stock
 * 
 */
class SystemBody : public Body {
    protected:
        /**
         * @brief System's current value
         * 
         */
        double value;
        /**
         * @brief System's name for identification purposes
         * 
         */
        string name;

    public:
    //    /**
    //     * @brief Construct a new System object
    //     * 
    //     */
    //    System();
    //    /**
    //     * @brief Construct a new System object
    //     * 
    //     * @param name System's name
    //     * @param value System's initial value
    //     */
    //    System(string name, double value);
    //    /**
    //     * @brief Construct a new System object
    //     * 
    //     * @param a Const System object used to construct a System copy
    //     */
    //    System(const System& a); 
    //    /**
    //     * @brief Destroy the System object
    //     * 
    //     */
        virtual ~SystemBody() {}

        /**
         * @brief Set the Value object
         * 
         * @param value System's value
         */
        void setValue(double value);
        /**
         * @brief Set the Name object
         * 
         * @param name System's name
         */
        void setName(string name);
        
        /**
         * @brief Get the Value object
         * 
         * @return double 
         */
        double getValue();
        /**
         * @brief Get the Name object
         * 
         * @return string 
         */
        string getName();

        ///**
        // * @brief Overloads = operator
        // * 
        // * @param a 
        // * @return System& 
        // */
        //System & operator=(const System &a);
        ///**
        // * @brief Constructs the output string used by << overload
        // * 
        // * @param out String to be printed with system's data
        // */
        //virtual void sysOut (ostream &out);
        ///**
        // * @brief Overloads << operator
        // * 
        // * @param out String to be printed with system's data
        // * @param system System pointer that references variables used on cout
        // * @return ostream& 
        // */
        //friend ostream &operator <<(ostream & out, System &system);
};

class SystemHandle : public SystemAbstract, public Handle<SystemBody> {
    public:
        SystemHandle(double value = 0, string name = ""){
            pImpl_->setValue(value);
            pImpl_->setName(name);
        }
        virtual ~SystemHandle() {}

        virtual void setValue(double value) { pImpl_->setValue(value);}
        virtual void setName(string name) { pImpl_->setName(name); }
        virtual double getValue() { return pImpl_->getValue();}
        virtual string getName() { return pImpl_->getName(); }
};

#endif