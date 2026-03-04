#pragma once

#include <string>
#include <vector>

using namespace std;

class Event 
{
private:
	static int nextId; // Shared ID counter for unique Event ID's
	int eventId; // Unique Event ID
	string eventName; // Event Name
	string eventDate; // Event Day : YYYY-MM-DD format

	vector <int> registeredAttendees; // ID's of attendee's registered to specific event
	vector<int> checkedIn; // ID's of all checked in attendees

public:
	// Constructor:
	Event();
	Event(const string& eventName, const string& eventDate);

	// Getters:
	int getId() const { return eventId; } 
	string getName() const { return eventName; }
	string getDate() const { return eventDate; }

	// Setters:
	void setName(const string& name);
	void setDate(const string& date);

	// Registration:
	void registerAttendee(int attendeeId); // Register an attendee to the event
	bool isRegistered(int attendeeId) const; // Check if attendee is registered

	// Check-In:
	void checkIn(int attendeeId); // Check-In a registered attendee
	bool isChecked(int attendeeId) const; // Check if registered attendee is checked-in

	// Get Lists:
	const vector<int>& getRegisteredAttendee() const { return registeredAttendees; }
	const vector<int>& getCheckedIn() const { return checkedIn; }
};