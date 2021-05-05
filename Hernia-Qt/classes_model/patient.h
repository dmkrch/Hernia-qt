#ifndef PATIENT_SENTRY
#define PATIENT_SENTRY

#include <QString>

enum Gender
{
    ANY_MALE,
    MALE,
    FEMALE
};

class Patient
{
public:
    Patient();
    Patient(Gender g, int a);
    Patient(const Patient& p);

    Gender Get_Gender() { return gender; }
    int Get_Age() { return age; }

private:
    Gender gender;
    int age;
};


#endif
