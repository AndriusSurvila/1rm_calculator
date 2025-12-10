# 1RM Calculator

A command-line application written in C that calculates One-Repetition Maximum (1RM) for strength training exercises and generates a beautiful HTML report.

## Table of Contents

- [About](#about)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Formulas](#formulas)
- [Project Structure](#project-structure)
- [Team](#team)

## About

The **1RM Calculator** is a tool designed for athletes and fitness enthusiasts to estimate their One-Repetition Maximum - the maximum weight they can lift for a single repetition of an exercise. This helps in:

- Tracking strength progress over time
- Setting appropriate training weights
- Planning progressive overload programs
- Comparing performance across different exercises

## Features

- **Unlimited exercises** - Add as many exercises as you need
- **Dual formula calculation** - Uses both Epley and Brzycki formulas for accuracy
- **Beautiful HTML output** - Generates a styled report with light/dark theme toggle
- **Fast and lightweight** - Pure C implementation
- **Reusable modules** - Modular design for easy maintenance

## Installation

### Prerequisites

- GCC compiler (or any C compiler)
- Git (for cloning the repository)
- Basic command line knowledge

### Compilation

**On Windows:**
```bash
git clone https://github.com/AndriusSurvila/1rm_calculator.git 
cd 1rm_calculator
gcc -o 1rm_calculator.exe main.c modules/rm_calculator.c modules/html_templater.c
```

**On Linux/macOS:**
```bash
git clone https://github.com/AndriusSurvila/1rm_calculator.git 
cd 1rm_calculator
gcc -o 1rm_calculator main.c modules/rm_calculator.c modules/html_templater.c -lm
```

## Usage

### Running the Application

**Windows:**
```bash
./1rm_calculator.exe
```

**Linux/macOS:**
```bash
./1rm_calculator
```

### Example Session

```
=== 1RM Calculator - Enter Exercise Data ===

Enter exercise name (or 'done' to finish): Bench Press
Enter weight (kg): 100
Enter repetitions: 5

Enter exercise name (or 'done' to finish): Squat
Enter weight (kg): 140
Enter repetitions: 8

Enter exercise name (or 'done' to finish): done

=== Generating HTML Report ===

Success! HTML report generated: output.html
Total exercises processed: 2
```

### Viewing Results

Open `output.html` in any web browser to see your results with:
- Table of all exercises with calculated 1RM values
- Formula explanations
- Light/Dark theme toggle
- Responsive design

## Formulas

The application uses two scientifically validated formulas:

### 1. Epley Formula
```
1RM = Weight × (1 + 0.0333 × Reps)
```

### 2. Brzycki Formula
```
1RM = Weight × (36 / (37 - Reps))
```

**Final Result** = Average of both formulas for improved accuracy

### Limitations
- Most accurate for 1-10 repetitions
- Cannot calculate for ≥37 repetitions (formula limitation)
- Best used with compound exercises (bench press, squat, deadlift)

## Project Structure

```
1rm_calculator/
├── main.c                      # Main application logic
├── modules/                    # Module directory
│   ├── html_templater.c        # HTML templating module
│   ├── html_templater.h        # HTML templating module header
│   ├── rm_calculator.c         # 1RM calculation module
│   └── rm_calculator.h         # 1RM calculation module header
├── styles.css                  # CSS styles for output
├── templates/
│   ├── start.html             # HTML header template
│   ├── row_template.html      # Exercise row template
│   └── end.html               # HTML footer template
└── README.md                   # This file
```

### Module Description

#### `rm_calculator` Module
Provides 1RM calculation functionality:
- Calculate 1RM using Epley formula
- Calculate 1RM using Brzycki formula
- Average calculation for final result
- Number to string conversion utilities
- Exercise data chain creation

#### `html_templater` Module
Provides template-based HTML generation:
- Template file processing
- Variable substitution using `{key}` syntax
- Linked list for key-value replacements
- Reusable for other template-based projects

## Team

**Vilnius University | Faculty of Mathematics and Informatics**

| Role | Name |
|------|------|
| Architect | Edgar Dainarovič |
| Builder | Andrius Survila & Edgar Dainarovič |
| Critic | Edgar Dainarovič |
| Designer | Andrius Survila & Edgar Dainarovič |
| Exhibitor | Andrius Survila |
| Facilitator | Andrius Survila |

## Development Stages

- **Stage 1** - Project idea, team formation, static page design
- **Stage 2** - Reusable modules development (.h and .c files)
- **Stage 3** - Complete console application with HTML generation

## Contributing

This project was created as part of a university coursework. The modules are designed to be reusable and can be integrated into other projects.

## References

- [Formulas](https://en.wikipedia.org/wiki/One-repetition_maximum)

---

**Created by Edgar Dainarovič & Andrius Survila**
