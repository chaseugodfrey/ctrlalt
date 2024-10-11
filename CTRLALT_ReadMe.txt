~ CTRL ALT PRODUCTIONS ~
# Usage Guide for CTRL ALT ENGINE / EDITOR 
# written by Chase Rodrigues

------- OUTLINE --------
1) GAME CONCEPT
2) CUSTOM ENGINE DEMO
3) TEAM COMPOSITION
------------------------

-----------------
1) GAME CONCEPT *
-----------------

a) Genre:		Real-Time Grid-Based Action Game

b) Concept:		Axol the axolotl fights through waves of red and blue chess armies to save his rabbit friend,
(High Concept)	Sir Nivins from the clutches of the evil red and blue Queens.

c) Concept:		Grid-based battle that spawns waves of enemies of either red or blue factions. Defeating enemies
(Detailed)		of a specific color increases an alignment towards the opposite faction, altering the way Axol 
				interacts with the enemies through different upgradable options, as well as the story ending.

d) Systems:		- Grid System (Movement, Collision, Interaction)
(to implement)		* Sets gameplay bounds for all gameobjects/entities to interact within
					* Alters to way we develop our physics/collision system as game entities will now use grid-based collision
					* AABB/Circle/etc. collisions will mainly be for GUI.
				- Wave System (Manager)
					* Manages spawning and destroying of enemies
				- Upgrade System
					* Manages character upgrades (abilities/power-ups/etc.)
					* Implementation undecided.
				- State Machine Behaviour
					* 
				- Action Queue System

- To be developed more -

-----------------------
2) CUSTOM ENGINE DEMO *
-----------------------
/brief: How to use CTRL ALT Engine for M1 Submission.

No input is required. Ensure that correct build options and project settings (refer to projectGuide.txt in solution folder.)
On opening .exe file, Engine initializes all Systems and loads "Scene 1" into Scene for display. A separate GLFW window is 
created for rendering entities in the Scene.

WARNINGS:
Currently only 1 Warning regarding APIENTRY macro definition.

===== Editor Functionality =====

-- Menu Bar
1) File/Exit
	- Calls Engine Exit function which destroys all entities and systems.
2) Create/Entity
	- "Creates" an entity dynamically through the clone factory during runtime.
	- Contains only transform and render components.
	- Adds it to Scene.
3) M1 Scenes
	- Contains 3 Scenes to demonstrate rubric requirements. Scene details will be explained in section below.

-- Play State Bar
Play & Stop buttons for future simulation playing purposes. Currently non functionable.
On the most right of the Play State Bar, FPS of the Engine is being displayed.

-- Inspector
Currently, the inspector only has one input field to a proxy variable that is not tied to any entity or other functionality other 
than for the sake of displaying. By inputting a single word (no spaces) and exiting the Engine, it serializies the word into a file
and loads it back upon restarting the engine.

Future use of this would be to display entity components and all its properties, and make entity properties modifiable during
Editor Runtime.

-- Hierarchy
Currently not displayed.

-- Scene
Currently non-functionable. Instead, for M1, a separate GLFW window is created to display the objects created in the Scene.
(Not ideal, however, lack of time to work on this functionality while remaining bug-proof.)
In the future, the rendering system will render onto a frame buffer and be converted into a ImGui::Texture which then can be displayed
onto the Scene Window.

-- Console
Displays console logs from any section of the code that calls it. Current implementation allows for any Engine file/system/entity to
display logging information. However, future use of this console will be meant for simulation debugging purposes, and any engine related
logging will be instead written into the engine's separate logger.

Allows scrolling and clearing of logs.

===== Scenes/Levels =====

These scenes are specifically designed for M1 rubrics and will be later removed once deserialization is fully functional. Currently, when
clicking the M1 Scenes from the Menu Bar, the main editor window will be the current context, and the separate rendering window will be
unfocused. ALT-TAB to refocus to the separate rendering window to view the Scene.


(*Note: Scene 1 & 2 contains some deserialization while Scene 3 is hard-coded).
(*Note2: Scene 1 & 3 uses static bools for the initialization of scenes. If attempting to reload into these scenes, some functionality
will not be there. More details in each scene's descriptors.)


Scene 1:
	- Loads 3 objects from file "scene1.txt", different locations.
	- Showcases rotation & scaling of objects.
	- Dynamically
	- Dynamically creates an object with a background texture.
	- Note*: If reloaded, background texture might not be created. Engine restart is required.

Scene 2:
	- Loads 2 objects from file.
	- Left object moves with physics while right object does not move.
	- Collision system checks for AABB collision (for now) through all its AABB colliders (2 in scene).
	- On Collision, prints "Collision Detected" in Editor Console.
	- On Exit, prints "Collision Exited" in Editor Console.

Scene 3:
	- Loads 0 objects from file.
	- Dynamically spawns 2500 objects from registry.
	- Unfortunately no math random functions used, therefore entities have been spawned progressively with diagonal offsets.
	- Note*: If reloaded, the 2500 entities might not be created. Engine restart is required.

===== Other functionality =====

Both functions need the current context window to be of the Main Editor Window. (Select any area in Editor to refocus window 
before executing these.)

1) Pressing W, A, S, D, Spacebar & LMB will log its OnClick event to the Editor Console.
2) Pressing G will draw a debugging line.


// END






