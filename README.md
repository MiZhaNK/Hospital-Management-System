# Hospital-Management-System: The Hospital Management System efficiently handles various hospital operations like booking appointments, managing emergency care, scheduling surgeries, and observing patients. It uses specific data structures to ensure optimal performance:

Vector:
Purpose: Stores doctors, their available slots, surgery slots, and patients under observation.
Reason: Allows quick access and iteration, making the code simpler.

Queue:
Purpose: Manages patient appointments.
Reason: FIFO operations suit handling appointments in the order they are received.

Priority Queue:
Purpose: Manages surgeries based on priority.
Reason: Efficient retrieval of high-priority surgeries, suitable for urgency.

Vector of Pairs:
Purpose: Keeps track of doctor appointments and surgery slots.
Reason: Quick checking of availability and booking specific time slots.

Time Complexity Analysis
Booking an Appointment: O(D * n), where D is the number of doctors and n is the number of slots per doctor.
Deleting an Appointment: O(A), where A is the number of appointments.
Rescheduling an Appointment: O(A).
Assigning an Emergency Doctor: O(ED * n), where ED is the number of emergency doctors.
Putting a Patient Under Observation: O(A).
Scheduling a Surgery: O(D * n), where D is the number of surgeons.
Canceling a Surgery: O(S log S), where S is the number of surgeries.
Rescheduling a Surgery: O(S log S).

Module Explanation
Appointment Management:
Uses a vector for doctors and their slots, a queue for appointments, and a vector of pairs for tracking doctor availability.
Emergency Care:
Uses a vector for emergency doctors, a queue for emergency appointments, and a vector for patients under observation.
Surgery Scheduling:
Uses a priority queue for surgeries and a vector of pairs for tracking surgery slots.
Conclusion:
The system uses vectors, queues, and priority queues to ensure efficient handling of hospital operations, confirming its robustness and scalability through time complexity analysis.
