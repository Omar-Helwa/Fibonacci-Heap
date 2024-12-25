#ifndef PATIENT_H
#define PATIENT_H

#include <iostream>
#include <string>

// forward dec

/**
 * @class Patient
 * @brief Represents a patient with details such as name, age, address, ID, symptoms, and gender.
 */
class Patient {
private:
    std::string description; ///< The name of the patient.
    std::string gender; ///< The gender of the patient.
    int age; ///< The age of the patient.

public:

    /**
     * @brief Constructor to initialize a Patient object with all details.
     * @param description The name of the patient.
     * @param age The age of the patient.
     * @param gender The gender of the patient.
     */

    Patient(){};

    /**
     * @brief Destructor for the Patient object.
     */
    ~Patient() = default;


};

#endif // PATIENT_H
