#include "Attendees.h"

// Initializing static ID counter variable:
int Attendee::nextAId = 1;

// Default constructor
Attendee::Attendee() : attendeeId(nextAId++), attendeeName(""), attendeeEmail("") 
{

}

// Non-Default/Parameterized Constructor:
Attendee::Attendee(const string& name, const string& email)
	: attendeeId(nextAId++), attendeeName(name), attendeeEmail(email)
{

}

// Setters
void Attendee::setAName(const string& name) { attendeeName = name; }
void Attendee::setAEmail(const string& email) { attendeeEmail = email; }