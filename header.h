#ifndef HEADER_H

#define HEADER_H

#include "vector.h"
//Base abstract class
class zmogus {
protected:
    std::string firstName;
    std::string secondName;
    zmogus (const std::string inpName, const std::string inpSName ) : firstName(inpName), secondName(inpSName) {}
public:
    // getters
    virtual std::string getName() const {return firstName;}
   virtual std::string getSurname() const {return secondName;}
    // setters
    virtual void setName(std::istream & stream) {stream >> firstName;}
    virtual void setSurname(std::istream & stream) {stream >> secondName;}

};
//Derived class
class studentas: public zmogus {
private:
    Vector<int> nd;
    double egz;
    double allMarks;
    int haha; // used for creating random numbers
public:
    //Constructors
    studentas() : zmogus("Vardas", "Pavarde"), egz(0.0), allMarks(0.0), haha(0) {}
    ~studentas() {nd.clear();}
    // getters
    double getAllMarks() const {return allMarks;}
    double getEgz() const {return egz;}
    // setters
    void setAllMarks(std::istream & stream) {stream >> allMarks;}
    void setEgz (std::istream& stream) {stream >> egz;}
    void setEgz (const int& eg) {egz = eg;}
    void setName(const std::string & firstName) { this->firstName = firstName; }
    void setSurname(const std::string & secondName) { this->secondName = secondName; }
    void setNd();
    void setNd(std::initializer_list<int> list) {nd = list;}
    // functions
    void randomNumbers(int haha);
    double vid();
    int median();
    double galutinioM();
    double galutinioV();
};


#endif