# Coursework
Controls:
1. Press **W, A, S, D**: Move Player Up/Down/Left/Right
2. Press **Space**: Jump
2. Press **F**: Toggle Player Movement Method. There are 2 different methods through which player can change its position/orientation (Default is Method 1):
    1. Change position/orientation directly (without forces/torque )
    2. Change position/orientation via forces/torque
3. **Left Click**: Shoot Enemies

# Game Scenario
Reach the end of the maze (marked by a big door) to win the game. However, the door (a stateful object) will not open unless you have collected 10 coins. These coins are spread out across the maze. Red Capsules can be collected which will stop all enemies chasing you for 3 seconds. Each enemy has some health (maximum 10), and each shoot to the enemy will decrease its health by 1. If an enemy's health goes zero, it will die, but it will respawn from its original position after 3 seconds.

Crossing the opened door will result in you winning the game.
If time runs out, game is over.

# Features Implemented:

1. Menu System is controlled by a state machine
2. Stateful obstacle (Door)
3. Enemies chase the player through path finding
4. Third Person Camera Functionality
5. Layer Mask Functionality (I have done bit masking to achieve this). There are 4 different layers in my game:
    1. Collectibles (Objects the Player can collect)
    2. Player
    3. Enemy
    4. Static Objects (Walls and Floor)

    Player can interact with Collectibles, Enemy and Static Objects.  
    Enemy can only interact with Player Static Objects.  
    
    Therefore, Enemy is not able to collect any collectibles because `BroadPhase() in PhysicsSystem.cpp` also checks whether or not the 2 potential colliding objects can interact with each other using the bit mask given by the layer an object has.

6. Raycast Functionality (Player's Shooting Ability)
7. Projection/Impulse Collision Resolution Method Used to resolve collision
8. Coefficient of Restitution formed by combined elasticity values of the colliding objects
9. Enemy is a Stateful GameObject witht the following states:
    1. Chase State (Enemy will chase the player to a certain waypoint in grid)
    2. Idle State (Enemy figures out its next waypoint in grid, when in this state)
    3. Dumb State (Enemy will do nothing, this state is enabled when a player collects a powerup)
    4. Dead State (Enemy is dead in this state)
    5. Respawn State (Enemy respawns from its original in this state)
10. Enemy will recalculate the path to the player only when the player moves its position from one grid cell to another
11. Spatial Acceleration Structure Used

# Collision Detection:
Following collision detection functionality has been implemented:
1. AABB vs Sphere
2. AABB vs AABB
3. Sphere vs Sphere
4. Sphere vs OBB 
5. OBB vs OBB
6. Ray vs Plane/AABB/OBB/Sphere

`Note: Door is an OBB in my game. Unfortunately, my game does not display OBB vs OBB collision detection but I have tested it and it works. However, the player's bounding volume is a sphere, so when player reaches the door, OBB vs Sphere collision can be examined.`
