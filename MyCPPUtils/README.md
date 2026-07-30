# MyCPPUtils

King's Personal C++ utility library for projects.

This collection contains reusable helpers I use across multiple projects/assignments to reduce boilerplate and keep code clean.

## Features

- **DynamicMenu** – Easy console menus that can be built at runtime
- **VectorSort** – Generic sorting for vectors of structs by any member
- **WebPortal** – Lightweight localhost web server (powered by cpp-httplib) to visualize data in the browser
- **EntityManager** – Simple generic container/manager for collections of objects
- **Console & Utils** – Input helpers, screen clearing, and small quality-of-life functions

## Folder Structure

```bash
MyCPPUtils/
├── common/
│   └── Utils.h
├── sorting/
│   └── VectorSort.h
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

### Option 2 - For submission (self-contained)

Copy the folders you need into a project (usually into an `external/` or `utils/` folder) so the project is fully self contained.

```bash
#include "menu/DynamicMenu.h"
#include "sorting/VectorSort.h"
#include "web/WebPortal.h"
#include "data/EntityManager.h"
#include "console/Console.h"
#include "common/Utils.h"
```

## Dependencies

- **cpp-httplib** (single header) - required only if you use the WebPortal. See instructions below.

## Notes

- The purpose of this library is designed for rapid prototyping. 
- All components are header-only (except the external `httplib.h`).
- Feel free to modify anything to suit individual projects. 

## Author

King
GitHub: https://github.com/kingstapestry

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