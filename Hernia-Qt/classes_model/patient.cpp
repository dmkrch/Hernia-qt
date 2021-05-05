#include "patient.h"

Patient::Patient() {}

/* constructor */
Patient::Patient(Gender g, int a) :
    gender(g), age(a) {}

/* copy constructor */
Patient::Patient(const Patient& p)
{
    this->age = p.age;
    this->gender = p.gender;
}
