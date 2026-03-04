#include "Menu.h"
#include <limits> // Numeric limits
#include <iostream>
#include <algorithm>
#include <regex>
#include <ctime>
#include <sstream>

using namespace std;

Menu::Menu()
{

}
Menu::Menu(bool test)
{
    if (test) {
        writer.enableAnimation(false); // Disables TypeWriter effect when it is unwanted.
        writer.setDelay(0);  // Not sure if this is mandatory here or not fo rthis to work, but I will leave it here for now.
    }
}

vector<Event>& Menu::getEvents()
{
    return events;
}
vector<Attendee>& Menu::getAttendees()
{
    return attendees;
}

// Events:

// Get Date:
string Menu::getValidDate(const string& userPrompt)
{
    // Housekeeping:
    string input;
    writer.print(userPrompt);

    while (true)
    {
        getline(cin, input);

        if (input.empty())
        {
            writer.print("Event Date cannot be empty. Please enter a date in [YYYY-MM-DD] format: ");
        }

        // Calling to check if the date is valid, if yes, continue, if no prompt for input again:
        if (isValidDate(input))
        {
            break;
        }
        else
        {
            writer.print("Invalid date entered. Please enter a date in [YYYY-MM-DD] format: ");
        }
    }

    return input;
}
// Check if date is valid: Also used for unit testing
bool Menu::isValidDate(const string& date) const
{
    // Housekeeping:
    int year, month, day, cYear, cMonth, cDay;
    int days[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    time_t ts;

    // Validate format YYYY-MM-DD:
    regex pattern(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!regex_match(date, pattern)) return false;

    // Parse year, month, day:
    if (sscanf_s(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3) return false;

    // Check month and day ranges:
    if (month < 1 || month > 12 || day < 1) return false;

    // This should work for leap year calculations:
    if (month == 2 && isLeap(year)) {
        if (day > 29) return false;
    }
    else if (day > days[month - 1]) {
        return false;
    }

    // Compare with current date
    ts = time(nullptr);
    tm now;
    localtime_s(&now, &ts);
    cYear = now.tm_year + 1900;
    cMonth = now.tm_mon + 1;
    cDay = now.tm_mday;

    // Making sure the date entered is valid:
    if (year < cYear)
    {
        return false;
    }
    if (year == cYear && month < cMonth) 
    {
        return false;
    }
    if (year == cYear && month == cMonth && day <= cDay)
    {
        return false;
    }

    return true;
}
// Checking for a leap year (Need to double check if this works):
bool Menu::isLeap(int year) const
{
    // Hopefully StackedOverflow was right and this works:
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
// Get Name:
string Menu::getValidName(const string& userPrompt)
{
    // Housekeeping:
    string input;

    writer.print(userPrompt);

    do
    {
        getline(cin, input);
        // Rejects empty input:
        if (input.empty())
        {
            writer.print("Event Name cannot be empty. Please enter an Event Name: ");
        }
        // Rejects duplicate Event Name:
        else if (nameExist(input))
        {
            writer.print("An Event with that name already exists. Please enter a valid Event Name: ");
            input.clear();
        }
    } while (input.empty() || nameExist(input));

    return input;
}
// Checking for Duplicate names:
bool Menu::nameExist(const string& name)
{
    // Checking the Events list to see if the name already exists or not:
    for (const auto& event : events)
    {
        if (event.getName() == name)
        {
            return true;
        }
    }

    return false;
}

// Creates Event:
void Menu::createEvent()
{
    // Housekeeping:
    string eName, eDate;

    // Get Valid Event Name:
    eName = getValidName("Please enter the Event Name: ");

    // Get Valid Event Date:
    eDate = getValidDate(string("Please enter the date for ")
        + eName + " in [YYYY-MM-DD] format:");

    // Create a new event and store it:
    Event newEvent(eName, eDate);
    events.push_back(newEvent);

    writer.print(string("Successfully created [ID: ") 
        + to_string(newEvent.getId()) + "] " + newEvent.getName() 
        + " for " + newEvent.getDate() + ".");
}
// List Events:
void Menu::listEvents()
{
    writer.print(""); // Just to have some space in the output
    if (events.empty())
    {
        writer.print("No events exist. Please create an Event...");
        return;
    }

    // Goes through the Events vector to list all the events:
    writer.print("Avaliable Events:");
    for (size_t index = 0; index < events.size(); ++index) 
    {
        writer.print(to_string(index + 1) + ". " + events[index].getName());
    }

    writer.print(""); // Some more space
}

// Attendees:

// Get Email:
string Menu::getValidEmail(const string& userPrompt)
{
    // Housekeeping:
    string input;

    writer.print(userPrompt);

    do
    {
        getline(cin, input);
        // Rejects empty input, same thing as Event Name:
        if (input.empty())
        {
            writer.print("Attendee Email cannot be empty. Please enter Email: ");
        }
        // Rejects if Email already exists:
        else if (emailExist(input))
        {
            writer.print("An Attendee is already registered under that Email. Please Select a "
            "different Email address: ");
            input.clear();
        }
    } while (input.empty() || emailExist(input));

    return input;
}
// Checks if email exists:
bool Menu::emailExist(const string& email)
{
    // Goes through the attendees vector to ensure uniqueness of emails:
    for (const auto& attendee : attendees)
    {
        if (attendee.getAEmail() == email)
        {
            return true;
        }
    }

    return false;
}
// Gets Attendee Name:
string Menu::getValidAName(const string& userPrompt)
{
    string input;
    writer.print(userPrompt);

    do
    {
        getline(cin, input);
        if (input.empty())
        {
            writer.print("Attendee Name cannot be empty. Please enter an Attendee Name: ");
        }
        else if (nameAExist(input))
        {
            writer.print("An Attendee with that name is already registered. Please enter a valid"
                " Attendee Name: ");
            input.clear();
        }
    } while (input.empty() || nameAExist(input));

    return input;
}
// Checks if name is duplicate:
bool Menu::nameAExist(const string& name)
{
    for (const auto& attendee : attendees)
    {
        if (attendee.getAName() == name)
        {
            return true;
        }
    }

    return false;
}
// Creates/Registers Attendee(Does not register them to an event):
void Menu::registerAttendee()
{
    // Housekeeping:
    string aName, aEmail;
    size_t eventChoice = 0;

    // Get valid Attendee Name:
    aName = getValidAName("Please enter the Attendee's Name: ");

    // Get Valid Attendee Email:
    aEmail = getValidEmail("Please enter " + aName + "'s Email: ");

    // Create a new Attendee and stores them:
    Attendee newAttendee(aName, aEmail);
    attendees.push_back(newAttendee);

    writer.print("Successfully registered [ID: " +
        to_string(newAttendee.getAId()) + "] " + newAttendee.getAName() +
        ", Email: " + newAttendee.getAEmail());
    writer.print(""); // Gives a space between things

    // Select Event to be Registered into:
    if (!events.empty())
    {
        writer.print("Please select an Event by ID to register Attendee to: ");
        for (size_t index = 0; index < events.size(); ++index)
        {
            // Should list all available events for attendee's to be registered into:
            writer.print(to_string(index + 1) + ". " + events[index].getName());
        }

        cout << ">> ";
        cin >> eventChoice;
        // Not sure if I could have just used 80 here, but it works like this, so I will leave it.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (eventChoice < 1 || eventChoice > events.size()) {
            writer.print("Invalid Event selection. Please select a valid Event.");
            return;
        }

        // Register the attendee to the selected event
        Event& selectedEvent = events[eventChoice - 1];
        selectedEvent.registerAttendee(newAttendee.getAId());
        writer.print(aName + " has been registered to the event " + selectedEvent.getName() + " (not checked-in).");
    }

    // Makes sure user cannot select an invalid Event ID
    if (eventChoice < 1 || eventChoice > events.size())
    {
        writer.print("Invalid Event selection. Please select a valid Event: ");
        return;
    }

    Event& selectedEvent = events[eventChoice - 1];
    // Register attendee to event:
    selectedEvent.registerAttendee(newAttendee.getAId());
}
// List Attendees:
void Menu::listAttendees()
{
    writer.print("");
    // Checking if attendee's vector is empty or not:
    if (events.empty())
    {
        writer.print("No Attendee's registered...");
        return;
    }

    writer.print("Attendee's:");
    for (size_t index = 0; index < attendees.size(); ++index) {
        const Attendee& attendee = attendees[index]; // get the event

        writer.print((index + 1) + ". " + attendee.getAName());
    }

    writer.print("");
}
// Check in Attendee:
void Menu::checkAttendeeIn()
{
    // Housekeeping:
    string aEmail;
    size_t eventChoice;

    // Checking if events is empty:
    if (events.empty())
    {
        writer.print("No events exist to check into.");
        return;
    }

    // Checking if attendee's is empty:
    if (attendees.empty())
    {
        writer.print("No registered attendees.");
        return;
    }

    // List events:
    writer.print("Please select an event to check into:");
    for (size_t index = 0; index < events.size(); ++index)
    {
        writer.print(to_string(index + 1) + ". " + events[index].getName());
    }

    eventChoice = 0;
    cout << ">> ";
    cin >> eventChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (eventChoice < 1 || eventChoice > events.size())
    {
        writer.print("Invalid selection. Returning to menu...");
        return;
    }

    Event& selectedEvent = events[eventChoice - 1];

    // Get attendee email:
    writer.print("Please enter the Email of the Attendee you wish to check-in:");
    getline(cin, aEmail);

    // Find attendee by email:
    auto find = find_if(attendees.begin(), attendees.end(),
        [&](const Attendee& a) { return a.getAEmail() == aEmail; });

    if (find == attendees.end())
    {
        writer.print("There is no attendee registered with that Email.");
        return;
    }

    int attendeeId = find->getAId();

    // Check if the attendee is registered to this event
    if (!selectedEvent.isRegistered(attendeeId))
    {
        writer.print(find->getAName() + " is not registered for this event.");
        return;
    }

    // Check if already checked-in
    if (selectedEvent.isChecked(attendeeId))
    {
        writer.print(find->getAName() + " is already checked in for " + selectedEvent.getName() + ".");
        return;
    }

    // Check them in
    selectedEvent.checkIn(attendeeId);
    writer.print(find->getAName() + " has been checked in for " + selectedEvent.getName() + ".");
}

// Attendence Report:
void Menu::attendenceReport() const
{
    if (attendees.empty()) {
        writer.print("No attendees registered.");
        return;
    }

    if (events.empty()) {
        writer.print("No events created.");
        return;
    }

    for (const auto& event : events)
    {
        writer.print("=================================");
        writer.print("Event: " + event.getName());
        writer.print("Total Registered Attendees: " + to_string(event.getRegisteredAttendee().size()));
        writer.print("Total Checked-In: " + to_string(event.getCheckedIn().size()));

        writer.print("Registered Attendees and Status:");
        for (int id : event.getRegisteredAttendee()) // loop through all registered
        {
            auto find = find_if(attendees.begin(), attendees.end(),
                [&](const Attendee& attendee) { return attendee.getAId() == id; });

            // Display who is checked-in and who is not:
            if (find != attendees.end())
            {
                string status = event.isChecked(id) ? "Y" : "N";
                writer.print("- " + find->getAName() + " : " + status);
            }
        }

        writer.print("=================================");
        writer.print(""); // extra line for spacing between events
    }
}

bool Menu::attendeeExist(const string& name) const
{
    for (const auto& attendee : attendees)
    {
        if (attendee.getAName() == name)
            return true;
    }
    return false;
}

// Main Menu Loop:
void Menu::run()
{
    // HouseKeeping:
    int userChoice = 0;
    bool running = true;

    writer.print("Welcome to Hymenaeus Event Management Systems!");

    while (running)
    {
        writer.print("Please select an option:");
        writer.print("1. Create Event");
        writer.print("2. Register Attendee");
        writer.print("3. Check-In Attendee");
        writer.print("4. List Events");
        writer.print("5. List Attendee's");
        writer.print("6. Attendee Report");
        writer.print("7. Exit");
        cout << ">> ";

        // Input validation
        if (!(cin >> userChoice))
        {
            cin.clear();
            cin.ignore(numeric_limits<::streamsize>::max(), '\n');
            writer.print("Invalid input! Please enter a number.");
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover newline

        switch (userChoice)
        {
        case 1:
            createEvent();
            break;
        case 2:
            registerAttendee();
            break;
        case 3:
            checkAttendeeIn();
            break;
        case 4:
            listEvents();
            break;
        case 5:
            listAttendees();
            break;
        case 6:
            attendenceReport();
            break;
        case 7:
            writer.print("Goodbye!");
            running = false;
            break;
        default:
            writer.print("Invalid selection! Please type the number that corresponds"
            " with which option you wish to pick: ");
        }
    }
}