# MyCppUtils

Personal C++ utility library for school assignments and small projects.

This collection contains reusable helpers I use across multiple assignments to reduce boilerplate and keep code clean.

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

