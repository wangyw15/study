#define COMMON
#define var auto

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <algorithm>

#ifndef EMPLOYEE_LIST
#include "DataStructure/EmployeeList.h"
#endif

#ifndef EVENT_LIST
#include "DataStructure/EventList.h"
#endif

#ifndef UTIL
#include "Util/Util.h"
#endif

const auto DATA_PATH = "data/";
const auto EMPLOYEES_FILE_NAME = "employees.txt";
const auto EVENTS_FILE_NAME = "things.txt";
const auto SPLIT_LINE = "==============================";