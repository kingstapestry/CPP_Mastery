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