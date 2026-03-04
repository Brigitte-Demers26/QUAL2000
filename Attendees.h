#pragma once
#include <string>

using namespace std;

class Attendee
{
private:
	static int nextAId; // Static counter for unique ID
	int attendeeId; // Unique ID for each attendee
	string attendeeName; 
	string attendeeEmail; 

public:
	// Constructors:
	Attendee();
	Attendee(const string& attendeeName, const string& attendeeEmail);

	// Getters:
	int getAId() const { return attendeeId; }
	string getAName() const { return attendeeName; }
	string getAEmail() const { return attendeeEmail; }

	// Setters:
	void setAName(const string& name);
	void setAEmail(const string& email);
};
