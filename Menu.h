#pragma once

#include "TypeWriter.h"
#include "Events.h"
#include "Attendees.h"
#include <vector>
#include <string>

using namespace std;

class Menu 
{
private:
	TypeWriter writer; // TypeWriter object because I had to do something fun with this for some reason...
	vector<Event> events; // Created events will be stored here
	vector<Attendee> attendees; // Created/Registered attendees will be stored here

public:
	Menu();
	Menu(bool test); // Testing constructor

	void run(); // Main Menu Loop

	// Event Functions:
	void createEvent(); // Create a New Event
	string getValidName(const string& userPrompt); // Get non-empty, unique event name
	bool nameExist(const string& name); // Checks if event name already exists
	string getValidDate(const string& userPrompt); // Get a valid date
	bool isValidDate(const string& date) const; // Validates date format & range
	bool isLeap(int year) const; // This should check if it is a leap year
	void listEvents(); // List all events

	// Attendee Functions:
	void registerAttendee(); // Registers an Attendee
	string getValidAName(const string& userPromt); // Get non-empty, unique attendee name
	bool nameAExist(const string& name); // Checks if attendee name already exists
	string getValidEmail(const string& userPrompt); // Get valid email
	bool emailExist(const string& email); // Checks if email exists
	bool attendeeExist(const string& name) const;
	void listAttendees();

	// Check-In Functions:
	void checkAttendeeIn(); // Check-In an attendee to a specific event

	// Reports:
	void attendenceReport() const; // Report of which events an attendee is checked into

	// For Testing: adding stuff manually
	void addEvent(const Event& e) { events.push_back(e); }
	void addAttendee(const Attendee& a) { attendees.push_back(a); }

	// For Testing: accessing stuff
	vector<Event>& getEvents(); // Access Events for testing
	vector<Attendee>& getAttendees(); // Access attendees for testing
};