/* Resolves the conflict by stopping (output: robot name, the time to it should be stopped) one
 of the robots based on any assumed priorities (e.g., task urgency, remaining battery life
can be hardcoded in the beginning).*/


#include<bits/stdc++.h>
using namespace std;

// Class definition for Robot
class Robot {
public:
    // robo properties
    string name; // Robot name
    int currentX, currentY;    // current coordinates of the robot
    int conflictRegionX, conflictRegionY;    // conflict region
    string taskUrgency;        // task urgency we can get priority rating from the map
    int delay;                 // operational efficiency (delay in seconds),we can get priority rating from the map
    int timeToClear;           // Estimated time to clear conflict (in seconds),we can get priority rating from the map
    int batteryRemaining;      // Battery percentage remaining (0-100),we can get priority rating from the map

    // Constructor 
    Robot(
        string n,               // Robot name
        int cx, int cy,         // Current position (x, y)
        int crx, int cry,       // Conflict region position (x, y)
        string tUrgency,        // Task urgency (e.g., "critical", "high")
        int d,                  // Delay in seconds (Operational efficiency)
        int tClear,             // Estimated time to clear the conflict
        int b                   // Battery percentage remaining
    ) : name(n),
        currentX(cx), currentY(cy),
        conflictRegionX(crx), conflictRegionY(cry),
        taskUrgency(tUrgency),
        delay(d),
        timeToClear(tClear),
        batteryRemaining(b) {}

    // Function to calculate the priority of the robot
    int calculatePriority(map<string, int>& taskUrgencyMap,
                          map<int, int>& proximityMap,
                          map<int, int>& operationalEfficiencyMap,
                          map<int, int>& estimatedTimeToClearMap,
                          map<int, int>& batteryRemainingMap) {
        // Retrieve the ratings for Task Urgency, Proximity, Operational Efficiency,
        // Time to Clear, and Battery Remaining based on their respective maps
        int A_rating = taskUrgencyMap[taskUrgency];  // Task Urgency rating
        int B_rating = proximityMap[getProximityRating()]; // Proximity rating
        int C_rating = operationalEfficiencyMap[getOperationalEfficiencyThreshold()]; // Operational Efficiency rating
        int D_rating = estimatedTimeToClearMap[getTimeToClearThreshold()]; // Time to Clear rating
        int E_rating = batteryRemainingMap[getBatteryRemainingThreshold()]; // Battery Remaining rating

        // Calculate the priority using the provided formula
        int priority = (3 * A_rating + 2 * B_rating) - (3 * C_rating + 1.5 * D_rating + 0.5 * E_rating) + 40;
        return priority;
    }

    // Helper function to calculate the distance between current position and conflict region
    int calculateDistance() {
        return abs(currentX - conflictRegionX) + abs(currentY - conflictRegionY);
    }

    // Helper function to get operational efficiency rating threshold based on delay time
    int getOperationalEfficiencyThreshold() {
        if (delay > 30) return 30;  // Delay > 30 seconds
        if (delay > 20) return 20;  // Delay > 20 seconds and <= 30 seconds
        if (delay > 10) return 10;  // Delay > 10 seconds and <= 20 seconds
        if (delay > 5) return 5;    // Delay > 5 seconds and <= 10 seconds
        return 0;                   // No delay
    }

    // Helper function to get estimated time to clear threshold
    int getTimeToClearThreshold() {
        if (timeToClear > 20) return 20;  // More time required to clear conflict
        if (timeToClear > 15) return 15;
        if (timeToClear > 10) return 10;
        if (timeToClear > 5) return 5;
        return 2;  // Less time to clear conflict
    }

    // Helper function to get battery remaining threshold
    int getBatteryRemainingThreshold() {
        if (batteryRemaining < 20) return 20;  // Battery < 20%
        if (batteryRemaining < 40) return 40;  // Battery < 40%
        if (batteryRemaining < 60) return 60;  // Battery < 60%
        if (batteryRemaining < 80) return 80;  // Battery < 80%
        return 100;   // Battery > 80%
    }

    // Helper function to get proximity rating based on the distance
    int getProximityRating() {
        int distance = calculateDistance();
        if (distance == 0) return 0;  // Directly at the conflict region
        if (distance <= 5) return 5;   // 5 unit away
        if (distance <= 10) return 10;   // 10 units away
        if (distance <= 20) return 20;   // 20 units away
        return 21;                      // More than 20 units away
    }

    // Function to display robot details
    void displayRobot() const {
        cout << "Robot Name: " << name << endl;
        cout << "Current Position: (" << currentX << ", " << currentY << ")" << endl;
        cout << "Conflict Region: (" << conflictRegionX << ", " << conflictRegionY << ")" << endl;
        cout << "Task Urgency: " << taskUrgency << endl;
        cout << "Delay: " << delay << " seconds" << endl;
        cout << "Time to Clear: " << timeToClear << " seconds" << endl;
        cout << "Battery Remaining: " << batteryRemaining << "%" << endl;
    }
};

// Conflict detection function: Checks if the paths of two robots intersect
bool pathsIntersect(const vector<int>& path1, const vector<int>& path2) {
    for (int node1 : path1) {
        for (int node2 : path2) {
            if (node1 == node2) {
                return true; // Paths intersect at node1 == node2
            }
        }
    }
    return false; // No intersection found
}

// Conflict detection based on proximity and task priority
void resolveConflict(Robot& robot1, Robot& robot2,
                     map<string, int>& taskUrgencyMap,
                     map<int, int>& proximityMap,
                     map<int, int>& operationalEfficiencyMap,
                     map<int, int>& estimatedTimeToClearMap,
                     map<int, int>& batteryRemainingMap) {
    int priority1 = robot1.calculatePriority(taskUrgencyMap, proximityMap, operationalEfficiencyMap, estimatedTimeToClearMap, batteryRemainingMap);
    int priority2 = robot2.calculatePriority(taskUrgencyMap, proximityMap, operationalEfficiencyMap, estimatedTimeToClearMap, batteryRemainingMap);

    if (priority1 > priority2) {
        cout << robot2.name << " should be stopped at time: " << 0 << " seconds (lower priority)" << endl;
    } else {
        cout << robot1.name << " should be stopped at time: " << 0 << " seconds (lower priority)" << endl;
    }
}

int main() {
    // Define the maps based on the previously described ratings
    map<string, int> taskUrgencyMap = {
        {"critical", 10},
        {"high", 8},
        {"moderate", 6},
        {"low", 4},
        {"very low", 2}
    };

    // Proximity map based on distance to conflict region
    map<int, int> proximityMap = {
        {0, 10},   // Directly at conflict region
        {5, 8},    // 1 unit away
        {10, 6},    // 2 units away
        {20, 4},    // 3 units away
        {21, 2}     // 4+ units away
    };

    // Robot operational efficiency rating map (delay)
    map<int, int> operationalEfficiencyMap = {
        {30, 10},  // Delay > 30 seconds
        {20, 8},   // Delay > 20 seconds
        {10, 6},   // Delay > 10 seconds
        {5, 4},    // Delay > 5 seconds
        {0, 2}     // No delay
    };

    // Time to clear conflict map
    map<int, int> estimatedTimeToClearMap = {
        {20, 10},  // More time required to clear conflict
        {15, 8},
        {10, 6},
        {5, 4},
        {2, 2}     // Less time to clear conflict
    };

    // Battery remaining map
    map<int, int> batteryRemainingMap = {
        {20, 10},  // Battery < 20%
        {40, 8},   // Battery < 40%
        {60, 6},   // Battery < 60%
        {80, 4},   // Battery < 80%
        {100, 2}   // Battery > 80%
    };

    // Create a few example robots
    Robot robot1("Robot1", 2, 3, 5, 6, "critical", 31, 8, 40);
    Robot robot2("Robot2", 4, 4, 5, 6, "high", 18, 5, 60);

    // Display robot details
    robot1.displayRobot();
    robot2.displayRobot();

    // Detect and resolve conflict
    resolveConflict(robot1, robot2, taskUrgencyMap, proximityMap, operationalEfficiencyMap, estimatedTimeToClearMap, batteryRemainingMap);
      return 0;
}

/*
Reliability: The system employs discrepancy resolution in a manner where reliability is maintained when a weighting metric is utilized to determine which robot should have priority in calculating task parameters by estimating aspects such as The urgency of the task, proximity to the area of conflict; operational effectiveness; estimated time of which the robot can clear the area and the battery left on the robot.
This bew weighting metric employs predetermined rating maps to determine if there is any need for a particular robot to dominate the other forces in case of a conflict. This is a structured approach that considers reducing the number of subjective decisions depressing into a constant rule that accurately resolves conflicts in real-time while minimizing errors or missed intersections during a reaction and decision-making process.
Safety: Employing safety protocols to stop the robot with less priority also tackles the risk of overlapping direction paths, safely preventing the robots from colliding. With the algorithm, the critical conditions for these robots were appropriate, such as projected closeness to the battery and level remaining, enabling safe robot operation within these conditions. It also increases the movement and decision-making of the robots as they shift conditions in real-time up faster and prioritize expansive and more urgent tasks or the robots closest to the area of conflict. This flexibility in the robot's decision making, paired with well-laid-out criteria for making decisions, enables a guarantee of safety to be met without any lost time in efficiency.
*/