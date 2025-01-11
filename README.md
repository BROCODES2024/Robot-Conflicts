# Fleet Manager System - Conflict Resolution Module

This repository contains the implementation of a conflict resolution module for a Fleet Management System (FMS) designed to manage a group of mobile robots operating in a warehouse. The module dynamically detects and resolves conflicts in robot paths using a priority-based approach.

---

## Overview

### Problem Statement
The FMS oversees mobile robots tasked with navigating a warehouse, picking items, and delivering them to designated locations. Conflicts arise when:
1. Two robots attempt to access the same aisle or node simultaneously.
2. One robot's delay disrupts the schedule of others.

This repository solves these challenges by:
- Dynamically detecting conflicts in robot paths.
- Resolving conflicts by prioritizing robots based on various parameters, ensuring operational efficiency and safety.

---

## Tasks Completed

### **Task 1: Conflict Resolution Strategy**
- Designed a priority-based strategy to decide which robot should gain access to a conflicting region.
- Prioritized robots based on:
  - **Task Urgency**
  - **Proximity to the Conflict Region**
  - **Operational Efficiency** (measured as potential cascading impacts)
  - **Estimated Time to Clear** (conflict resolution speed)
  - **Battery Remaining**

#### Key Formula
Developed a scoring system for robots, factoring in both positive and negative impacts:
\`\`\`plaintext
P = (3 * A) + (2 * B) - [(3 * C) + (1.5 * D) + (0.5 * E)] + 40
\`\`\`
Where:
- \`A\`: Task urgency rating
- \`B\`: Proximity rating
- \`C\`: Operational efficiency impact
- \`D\`: Estimated time to clear
- \`E\`: Battery remaining

---

### **Task 2: Algorithm Design**
1. **Conflict Detection**:
   - Dynamically detects conflicts as robots approach the conflicting region.
   - Conflicting paths are represented as arrays of node IDs.

2. **Conflict Resolution**:
   - Implemented a class-based approach in C++ where each robot is an object with properties such as task urgency, proximity, operational efficiency, conflict resolution speed, and battery remaining.
   - Calculated priorities using predefined maps for each property, based on lookup tables.

3. **Maps for Ratings**:
   - Task urgency: Critical (10), High (8), Moderate (6), Low (4), Very Low (2).
   - Proximity: Based on Manhattan distance from the conflict region.
   - Operational efficiency: Higher delay causes higher ratings.
   - Estimated time to clear: More time results in higher ratings.
   - Battery remaining: Lower battery results in higher ratings.

4. **Decision-Making**:
   - The robot with the highest priority proceeds first, while others are stopped temporarily.

---

## Code Structure

- **\`robot.h\`**: Contains the \`Robot\` class definition with properties and methods for calculating priorities.
- **\`main.cpp\`**: Implements the algorithm for conflict detection and resolution, and demonstrates test cases.
- **\`priority_maps.h\`**: Contains predefined maps for property ratings based on lookup tables.

---

## How the Solution Ensures Reliability and Safety

1. **Dynamic Conflict Detection**:
   - Conflicts are detected in real-time as robots approach the region, ensuring no disruptions in other areas of the warehouse.

2. **Priority-Based Decision-Making**:
   - Assigns priority based on measurable parameters, minimizing subjective or arbitrary decisions.

3. **Scalable Design**:
   - The approach adapts to warehouses with more robots or complex layouts by leveraging modular design and extendable maps.

---

## Usage

1. Clone the repository:
   \`\`\`bash
   git clone https://github.com/your-username/fleet-manager-system.git
   cd fleet-manager-system
   \`\`\`

2. Compile the code:
   \`\`\`bash
   g++ main.cpp -o fleet_manager
   \`\`\`

3. Run the executable:
   \`\`\`bash
   ./fleet_manager
   \`\`\`

4. Customize robot properties and test cases in \`main.cpp\`.

---

## Future Enhancements

1. **Machine Learning for Operational Efficiency**:
   - Incorporate an ML model to predict cascading impacts more accurately based on historical data.

2. **Integration with Real-Time Sensors**:
   - Connect with IoT devices for real-time position and battery status updates.

3. **Advanced Path Planning**:
   - Use A* or Dijkstra’s algorithm for dynamic path adjustments to minimize conflicts.

---

