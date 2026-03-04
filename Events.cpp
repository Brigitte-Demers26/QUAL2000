#include "Events.h"

// Initializing static ID counter variable:
int Event::nextId = 1;

// Default Constructor:
Event::Event() : eventId(nextId++), eventName(""), eventDate("") 
{

}

// Non-Default/Parameterized Constructor:
Event::Event(const string& name, const string& date)
	: eventId(nextId ++), eventName(name), eventDate(date)
{

}

// Setters
void Event::setName(const std::string& name) { eventName = name; }
void Event::setDate(const std::string& date) { eventDate = date; }

// Register an attendee to the event (only once):
void Event::registerAttendee(int attendeeId)
{
    if (!isRegistered(attendeeId))
    {
        registeredAttendees.push_back(attendeeId);
    }
}

// Check if an attendee is registered
bool Event::isRegistered(int attendeeId) const
{
    for (int id : registeredAttendees)
    {
        if (id == attendeeId)
            return true;
    }
    return false;
}

// Check in a registered attendee
void Event::checkIn(int attendeeId)
{
    if (isRegistered(attendeeId) && !isChecked(attendeeId))
    {
        checkedIn.push_back(attendeeId);
    }
}

// Check if an attendee is already checked in
bool Event::isChecked(int attendeeId) const
{
    for (int id : checkedIn)
    {
        if (id == attendeeId)
            return true;
    }
    return false;
}