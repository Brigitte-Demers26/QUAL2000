#include "TestMenu.h"
#include "Menu.h"
#include <iostream>
#include <cassert>

/*
    I THINK I'm doing this right. But I'm not 100% certain. 
    Here's hoping I'm right!
*/
// Unit Testing:
void testDuplicateEventName()
{
    Menu mainMenu(true); // Pass true to skip TypeWriter delays

    mainMenu.addEvent(Event("Hymenaeus Event Management Systems Conference", "2026-09-09"));
    mainMenu.addEvent(Event("Comics! Comics! Comics!", "2026-03-06"));
    mainMenu.addEvent(Event("Humans. Are we Really as Smart as We Think?", "2026-05-20"));
    mainMenu.addEvent(Event("An Appreciation of Dogs", "2026-09-15"));
    mainMenu.addEvent(Event("An Appreciation of Cats", "2026-07-18"));

    assert(mainMenu.nameExist("Hymenaeus Event Management Systems Conference") == true);  // Duplicate
    cout << "[PASS] Duplicate Event Name successfully detected!" << endl;

    assert(mainMenu.nameExist("Penguine Cosplay 101") == false); // Not existing
    cout << "[PASS] Non-Duplicate Event Name successfully detected!" << endl;

    // Will cause an abort because it is a duplicate name:
    //assert(mainMenu.nameExist("Hymenaeus Event Management Systems Conference") == false); 
    // Will cause an abort because it is not a duplicate name:
    //assert(mainMenu.nameExist("Penguine Cosplay 101") == true); // Not existing
}
void testDuplicateAttendeeName()
{
    Menu mainMenu(true); // Pass true to skip TypeWriter delays

    mainMenu.addAttendee(Attendee("John Johnson", "john@something.com"));
    mainMenu.addAttendee(Attendee("Bob Bobson", "bob@something.com"));
    mainMenu.addAttendee(Attendee("Leroy Jenkins", "jenkins@something.com"));
    mainMenu.addAttendee(Attendee("Dude Dudebro", "dude@something.com"));

    assert(mainMenu.nameAExist("John Johnson") == true);  // Duplicate
    cout << "[PASS] Duplicate Attendee Name successfully detected!" << endl;

    assert(mainMenu.nameAExist("Maurice Chevalier") == false); // Not existing
    cout << "[PASS] Non-Duplicate Attendee Name successfully detected!" << endl;

    // Will cause an abort because it is a duplicate attendee name:
    // assert(mainMenu.nameAExist("John Johnson") == false);  // Duplicate
    // Will cause an abort because it is not a duplicate attendee name:
    //assert(mainMenu.nameAExist("Maurice Chevalier") == true); // Not existing
}
void testDuplicateEmail()
{
    Menu mainMenu(true); // Pass true to skip TypeWriter delays

    mainMenu.addAttendee(Attendee("John Johnson", "john@something.com"));
    mainMenu.addAttendee(Attendee("Bob Bobson", "bob@something.com"));
    mainMenu.addAttendee(Attendee("Leroy Jenkins", "jenkins@something.com"));
    mainMenu.addAttendee(Attendee("Dude Dudebro", "dude@something.com"));

    assert(mainMenu.emailExist("john@something.com"));
    cout << "[PASS] Duplicate Attendee Email successfully detected!" << endl;

    assert(!mainMenu.emailExist("bobby@something.com"));
    cout << "[PASS] Non-Duplicate Attendee Email successfully detected!" << endl;

    // Will cause an abort because it is a duplicate email address:
    //assert(!mainMenu.emailExist("john@something.com"));
    // Will cause an abort because it is not a duplicate email address:
    //assert(mainMenu.emailExist("bobby@something.com"));
}
void testValidDate()
{
    Menu mainMenu(true); // Pass true to skip TypeWriter delays
    // Case 1:
    assert(!mainMenu.isValidDate("2025-09-09")); // Invalid year
    cout << "[PASS] Invalid Date(Year) successfully detected!" << endl;
    // Case 2:
    assert(!mainMenu.isValidDate("2030-13-09")); // Invalid month
    cout << "[PASS] Invalid Date(Month) successfully detected!" << endl;
    // Case 3:
    assert(!mainMenu.isValidDate("2030-12-32")); // Invalid day
    cout << "[PASS] Invalid Date(Day) successfully detected!" << endl;
    // Case 4:
    assert(mainMenu.isValidDate("2026-09-09")); // Valid date
    cout << "[PASS] Valid Date successfully detected!" << endl;
    // Case 5:
    assert(mainMenu.isValidDate("2028-02-29")); // The next leap year
    cout << "[PASS] Valid Leap Year detected!" << endl;
}
void testCheckInLogic()
{
    Event test("Hymenaeus' Opulant New-Year Gala", "2027-01-01"); // Test event
    Attendee guest("John Johnson", "john@something.com"); // Checked-in/invited guest
    Attendee someGuy("Dude Dudeson", "dude@something.com"); // Not checked-in/uninvited guest

    // Case 1:
    test.checkIn(someGuy.getAId());
    assert(!test.isChecked(someGuy.getAId())); // If switched to assert(test.isChecked(someGuy.getAId())); it will fail. Good
    cout << "[PASS] Unregistered Attendee prevented from checking in!" << endl;

    test.registerAttendee(guest.getAId()); // Register John for event...
    test.checkIn(guest.getAId()); // Check's John in
    assert(test.isChecked(guest.getAId())); // Should work because John is registered to the event!
    cout << "[PASS] Registered Attendee successfully checked-in!" << endl;
}
void testDuplicateRegistration()
{
    Event test("Hymenaeus' Opulant New-Year Gala", "2027-01-01"); // Test event
    Attendee guest("John Johnson", "john@something.com"); // First guest

    test.registerAttendee(guest.getAId()); // Register John for event...
    test.registerAttendee(guest.getAId()); // Duplicate registration

    assert(test.getRegisteredAttendee().size() == 1); // Checking
    cout << "[PASS] Duplicate registration for " << test.getName() << " blocked." << endl;
}

// Integration Testing:
void integrationRegAndRetrieve()
{
    Menu mainMenu(true);

    // Creating Attendee...
    mainMenu.addAttendee(Attendee("John Johnson", "john@something.com"));
    // Verifying existence (Should be)
    assert(mainMenu.attendeeExist("John Johnson"));

    // See if attendee can be found in the vector storage...
    vector<Attendee>& list = mainMenu.getAttendees();
    assert(list.size() == 1);
    assert(list[0].getAEmail() == "john@something.com");

    cout << "[PASS] Integration: Attendee is stored and retrieved successfully!" << endl;
}
void integrationRegAndCheckIn()
{
    Menu mainMenu(true);

    Event test("Hymenaeus' Opulant New-Year Gala", "2027-01-01"); // Test event
    Attendee guest("John Johnson", "john@something.com"); // Checked-in/invited guest

    // Add venu and attendee:
    mainMenu.addEvent(test);
    mainMenu.addAttendee(guest);

    // Get event and register attendee:
    Event& testEvent = mainMenu.getEvents()[0];
    testEvent.registerAttendee(guest.getAId());

    // Check guest in:
    testEvent.checkIn(guest.getAId());

    // Check that it works the way it is suppossed to:
    assert(testEvent.isRegistered(guest.getAId()));
    assert(testEvent.isChecked(guest.getAId()));
    assert(testEvent.getCheckedIn().size() == 1);

    cout << "[PASS] Integration: Registration to Check-In successful!" << endl;
}
// Trying to see if the Event ID matches the ID of the attendee registered...
void intergrationEventMatchAttendee()
{
    Menu mainMenu(true); // Keep typewriter effect off

    int testEId;

    Event test("Hymenaeus' Opulant New-Year Gala", "2027-01-01"); // Test event
    Attendee guest("John Johnson", "john@something.com"); 

    mainMenu.addEvent(test);
    mainMenu.addAttendee(guest);

    Event& testing = mainMenu.getEvents()[0];
    Attendee& firstGuest = mainMenu.getAttendees()[0];

    testing.registerAttendee(firstGuest.getAId());
    
    // This should check that the Event ID matches to the Attendee registered ID:
    testEId = testing.getRegisteredAttendee()[0];
    assert(testEId == firstGuest.getAId());

    // Double check with the not checked in status first:
    assert(!testing.isChecked(firstGuest.getAId()));

    mainMenu.listEvents();
    mainMenu.attendenceReport();

    cout << "[PASS] Integration: Registered Attendee's ID matches the ID of Event registered to!" << endl;
}
