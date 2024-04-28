A small, yet feature-rich C++ based game engine capable of building projects for Windows, OSX, and Linux. Features a Lua scripting system, a basic 2D renderer running on SDL, a graphical user interface, templating, a robust scripting API, an input API, as well as a customizable component system. To begin use, run the solution and modify files in the assets directory.

Basic usage:

- **assets**: the main folder for holding all game-related objects
  - **components**: holds all user .lua files
    - Component.lua files have the following API:
      - OnStart(): called upon the component's creation (whether at game start or during runtime)
      - OnUpdate(): called once every frame
      - OnLateUpdate(): called once every frame, right after OnUpdate()
      - OnRender(): called once every frame, right after OnLateUpdate()
  - **fonts**: holds all .ttf files
  - **scenes**: holds all .scene files
    - Scene.scene files have the following format:
      - name: the name of the scene
      - actors: a list of all of the scene's initial actors
        - name: the actor's name
        - components: a list of components with their key and values
          - type: using type ExampleComponent will load ExampleComponent.lua from assets/components
  - **templates**: holds all .template files
    - a Template.template file has the same format as an actor in a .scene file
  - **textures**: holds all .png files
