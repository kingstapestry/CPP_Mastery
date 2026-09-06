# MyCPPUtils v1.3.1

King's C++ Object-Oriented Programming Utility Library.

This collection contains reusable helpers I use across multiple projects to reduce boilerplate and keep code clean.
Feel free to use it for your projects, just leave credit where it's due. 

## Features

- **Utils** – Collection of general helpers
- **DynamicMenu** – Interactive numbered console menus
- **EntityManager** – Generic containers that can store any type of object
- **Console** – Make console outputs cleaner, and some quality-of-life functions 
- **WebPortal (WIP)** – Lightweight localhost web server (powered by cpp-httplib) to visualize data in the browser

## Folder Structure

```bash
MyCPPUtils/
├── common/
│   └── Utils.h
├── menu/
│   └── DynamicMenu.h
├── web/
│   ├── httplib.h
│   └── WebPortal.h
├── data/
│   └── EntityManager.h
├── console/
│   └── Console.h
├── README.md
```


## How to Use in a Project

### Option 1 – Recommended for development
```bash
git clone https://github.com/kingstapestry/MyCPPUtils.git external/MyCppUtils
```

Then add the following to your project's **Additional Include Directories**:
```bash
$(ProjectDir)external/MyCPPUtils
```

### Option 2 - Submission for school projects/assignments (self-contained)

Copy the folders you need into a project (usually into an `external/` or `utils/` folder) so the project is fully self contained.

```bash
// Example:
#include "../external/MyCPPUtils/common/Utils.h"
```

## Dependencies

- **cpp-httplib** (single header) - required only if you use the WebPortal. See instructions below.

## Notes

- The purpose of this library is designed for rapid prototyping. 
- All components are header-only (except the external `httplib.h`).
- Feel free to modify anything to suit individual projects. 

## Author

Created by King | Last Updated: September 2026 | GitHub: https://github.com/kingstapestry

---

### How to download `httplib.h`

1. Go to the official repository: **https://github.com/yhirose/cpp-httplib**
2. Click on the file `httplib.h`
3. Click the **Raw** button
4. Right-click → **Save As...** and save it as `httplib.h`
5. Place the file here in your repo:

Alternative (command line):
```bash
curl -L https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h -o web/httplib.h
```