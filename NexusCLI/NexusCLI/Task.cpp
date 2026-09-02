#include "Task.h"

#include "MyCPPUtils/console/Console.h"
#include "MyCPPUtils/common/Utils.h"

int Task::_nextId = 1;

Task::Task(const std::string& title)
	: _id(_nextId++)
	, _title(title)
	, _priority(Priority::Medium)      
	, _status(Status::Pending)
	, _createdAt(std::time(nullptr)) {}

int Task::getId() const { return _id; }
std::string Task::getTitle() const { return _title; }
std::string Task::getDescription() const { return _description; }
Priority Task::getPriority() const { return _priority; }
Status Task::getStatus() const { return _status; }
std::time_t Task::getCreatedAt() const { return _createdAt; }

void Task::setId(int id) {
	_id = id;
}

void Task::setTitle(const std::string& title) { 
	_title = title; 
}

void Task::setDescription(const std::string& description) {
	_description = description;
}

void Task::setPriority(Priority priority) {
	_priority = priority;
}

void Task::setStatus(Status status) {
	_status = status;
}

void Task::setCreatedAt(std::time_t createdAt) {
	_createdAt = createdAt;
}

std::string Task::priorityToString(Priority priority) const {
	switch (priority) {
	case Priority::Low:	return "Low";
	case Priority::Medium: return "Medium";
	case Priority::High: return "High";
	default: return "UNKNOWN";
	}
}

std::string Task::statusToString(Status status) const {
	switch (status) {
	case Status::Pending: return "Pending";
	case Status::Completed: return "Completed";
	default: return "UNKNOWN";
	}
}

void Task::displayTask() const {
	std::vector<Task> oneTask = { *this };	// treat a single task as a 1-row table

	std::vector<Console::Column<Task>> columns = {
		{ "ID",       [](const Task& t) { return std::to_string(t.getId()); } },
		{ "STATUS",   [](const Task& t) { return t.statusToString(t.getStatus()); } },
		{ "PRIORITY", [](const Task& t) { return t.priorityToString(t.getPriority()); } },
		{ "CREATED",  [](const Task& t) { return Utils::timeToString(t.getCreatedAt()); } },
		{ "TITLE",    [](const Task& t) { return t.getTitle(); } }
	};

	Console::table(oneTask, columns);
}

std::string Task::toFileString() const {
	std::string priority = Utils::toString(static_cast<int>(_priority));
	std::string status = Utils::toString(static_cast<int>(_status));

	return
		Utils::toString(_id) + "|" +
		_title + "|" +
		_description + "|" +
		priority + "|" +
		status + "|" +
		std::to_string(_createdAt);
}

void Task::displayAllTasks(const Data::Manager<Task>& tasks) {
	if (tasks.empty()) {
		Console::error("No tasks found.");
		return;
	}

	std::vector<Console::Column<Task>> columns = {
		{ "ID",       [](const Task& t) { return std::to_string(t.getId()); } },
		{ "STATUS",   [](const Task& t) { return t.statusToString(t.getStatus()); } },
		{ "PRIORITY", [](const Task& t) { return t.priorityToString(t.getPriority()); } },
		{ "CREATED",  [](const Task& t) { return Utils::timeToString(t.getCreatedAt()); } },
		{ "TITLE",    [](const Task& t) { return t.getTitle(); } }
	};

	Console::title("All Tasks");
	Console::table(tasks.all(), columns);	// tasks.all() returns the vector
}

void Task::setNextId(int id) {
	_nextId = id;
}

Task Task::fromFileString(const std::string& line) {
	std::vector<std::string> parts;

	std::stringstream ss(line);
	std::string part;

	while (std::getline(ss, part, '|')) {
		parts.push_back(part);
	}

	if (parts.size() != 6) {
		return Task("");		// return default if error occurs
	}

	int id = std::stoi(parts[0]);
	std::string title = parts[1];
	std::string description = parts[2];
	
	int parsedPriorityInt = std::stoi(parts[3]);
	Priority priority = static_cast<Priority>(parsedPriorityInt);

	int parsedStatusInt = std::stoi(parts[4]);
	Status status = static_cast<Status>(parsedStatusInt);

	std::time_t createdAt = std::stoll(parts[5]);

	Task t(title);
	t.setId(id);
	t.setDescription(description);
	t.setPriority(priority);
	t.setStatus(status);
	t.setCreatedAt(createdAt);

	return t;
}