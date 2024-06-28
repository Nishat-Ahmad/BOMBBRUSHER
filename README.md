# BombBrusher™
A simple Minesweeper game implemented in C++ using SFML graphics library.


## Project status
_*The development for the project has officially been stopped.*_


## Installation
- SFML library installed on your system.
- Font file "minecraft_font.ttf" to be placed in the appropriate directory.
- Images folder containing all the images used in the game.
- Use the releases to find the dependencies for the project.
- Remember to download Required file and extract it. Also "install" the minecraft_font.tff to make it work properly.
  Also remember to add the images to the repo folder.


## How to Play
Use the mouse to interact with the game just like minesweeper. _There is no back feature ingame so you have to close it and than run it again._

1. Click on the "Play" button to start the game.
2. Choose the difficulty level (Easy, Medium, Hard).
3. Left-click to reveal a tile. The number on the tile represents the number of mines adjacent to it.
4. Right-click to place a flag on a suspected mine.
5. The game ends when all non-mine tiles are revealed or when a mine is clicked.


## Dependencies
- C++ standard libraries: `<iostream>`, `<functional>`, `<Windows.h>`, `<fstream>`, `<algorithm>`
- SFML libraries: `<SFML/Graphics.hpp>`


## Features
i. Three difficulty levels: Easy (10x10 grid), Medium (15x15 grid), Hard (20x20 grid).

ii. Pause functionality during gameplay by pressing p.

iii. Game also restarts by pressing p.


## Code Summary
### 1. `main.cpp`
   
  Overview:
  
  This file serves as the main entry point for the "BOMBBRUSHER" game.The primary responsibilities of this file include initializing the game
  window, handling user interactions, and managing the different game states and screens.
    
    Main Window Initialization:
    Creates and configures the main window using SFML.
   
    Game Loop Management:
    Implements a loop that keeps the main window active and responsive to user inputs.
   
    Pause Function:
    Contains a Pause function that displays a pause screen and waits for the user to unpause the game 
    by pressing 'P'.
   
    Difficulty Selection and Game Modes:
    Provides lambda functions to handle the opening of different game mode windows (easy, medium, hard) 
    and the high score window. Each difficulty level opens a new window with a corresponding 
    game configuration.
   
    High Score Window:
    Implements a high score window that displays buttons for different difficulties and a back
    button to return to the main window.
   
    Difficulty Selection Window:
    Opens a window where users can select the game's difficulty level.
    Each difficulty button initiates a new game with the specified difficulty.
   
    Button Handling:
    Utilizes ScreenButton objects to manage button creation, click handling, and hover effects.
    Buttons include "Play", "High Score", and difficulty-specific buttons ("Easy", "Medium", "Hard").
   
    TextBox Integration:
    Uses TextBox objects to display text on the main window and difficulty selection window.



### 2. `functions.cpp`
   
  Overview:
  
  This file implements the core functionality of the "BOMBBRUSHER" game using SFML and Windows libraries. 
  It includes the definition of three main classes—Board, bombCheck, and Game—each playing a crucial role in the game's mechanics and user interactions.
    
      Board Class:
      Purpose: Initializes and manages the main game board, including mine placement and button setup.
   
      Key Functions:
      Board(int difficulty = 10): Constructor to initialize the board with a specified difficulty level.
      allocateMemory(): Allocates dynamic memory for the board, mines, and buttons.
      Initialize_button(): Sets initial positions and states of buttons.
      Randomize_mines(): Randomly places mines on the board, ensuring the first click is safe.
      Initialize_board(): Calculates the number of adjacent mines for each tile.
      Print(RenderWindow* window): Renders the buttons and updates their textures based on the game state.
      assignCoordinates(RenderWindow* window): Determines the coordinates of the clicked button.
      ~Board(): Destructor to safely deallocate memory.
      
      bombCheck Class:
      Purpose: Extends Board to include gameplay mechanics such as mine and flag checks.
   
      Key Functions:
      checkMine(): Counts mines around the clicked tile.
      checkFlag(): Counts flags around the clicked tile.
      placeFlag(): Places a flag on a tile.
      removeFlag(): Removes a flag from a tile.
      lose(): Indicates a loss by revealing all mines.
      win(): Indicates a win by marking all tiles as used.
      revealSpace(): Reveals a tile if it's not a mine.
      expandSpace(RenderWindow* window): Expands the revealable area around a clicked tile.
      
      Game Class:
      Purpose: Integrates and manages the overall gameplay loop, handling user interactions 
      and game state transitions.
   
      Key Functions:
      Game(int difficulty = 10): Constructor to initialize the game with a specified 
      difficulty level.
      gamecontroller(RenderWindow* window): Manages the game flow by coordinating different 
      actions based on user input.


   
### 3. `Tile.cpp (button.cpp)`
  
  Overview:
  
  The Button class manages the behavior and appearance of individual tiles (or buttons) in the Minesweeper game.
  It handles textures, positioning, state management, and user interactions (clicks).
      
    Button Class:
    Purpose: Represents and manages a single tile (or button) in the Minesweeper game grid. 
    Handles texture loading, state management, and user interactions.
    
    Key Functions:
    
    Constructor:
    Button(): Initializes the button with default size, position, and preloads all textures.
    
    State Management:
    void setButtonState(btnState btn_state): Sets the state of the button.
    btnState getButtonState(): Retrieves the current state of the button.
    
    Positioning:
    void setPosition(int x, int y): Sets the position of the button.
    int getIndex_x(int starting_pos, int spacing_factor): Calculates the x-index based on position.
    int getIndex_y(int starting_pos, int spacing_factor): Calculates the y-index based on position.
    
    Interaction Handling:
    mouseClick Click(Vector2f mousePos): Handles mouse click events and returns the type of 
    click (left, right, idle).
    
    Rendering:
    void RenderButton(RenderWindow* window): Draws the button on the specified window.
    
    Text Management:
    void setText(int number_of_mines): Sets the text based on the number of adjacent mines.
    void UpdateText(int number_of_mines, RenderWindow* window): Updates and renders the text 
    if the button is revealed.
    
    Texture Updates:
    void updateTexture_Tile(): Updates the texture to the default tile.
    void updateTexture_Revealed(): Updates the texture to the revealed state.
    void updateTexture_Exploded(): Updates the texture to the exploded mine state.
    void updateTexture_Flag(): Updates the texture to the flag state.
    void updateTexture_Mine(): Updates the texture to the mine state.
      
  This class encapsulates all the behaviors and properties of a Minesweeper tile, managing its visual 
  representation, interaction logic, and state transitions.
  


### 4. `highscore.cpp`

  Overview
  The Score class manages the recording and sorting of game scores. It handles reading and writing scores to files, 
  sorting the scores using insertion sort, and tracking the time taken to complete a game.
    
    Score Class:
    Purpose: Manages game scores by reading from and writing to files, sorting scores, and tracking 
    game time.
    
    Key Functions:
    
    Constructor:
    Score(int difficulty = 10): Initializes the score manager for the specified difficulty. 
    Reads scores from the appropriate file (easy.txt, medium.txt, hard.txt) based on the difficulty level.
    
    Sorting:
    void insertionSort(): Sorts the scores array using insertion sort.
    
    Time Management:
    int getTime(): Returns the elapsed time since the game started.
    
    Data Accessors:
    string* getNames(): Returns the array of names.
    int* getScores(): Returns the array of scores.
    
    Game End Handling:
    void gameEnd(): Updates the scores at the end of the game. 
    Writes the top 10 scores back to the appropriate file, sorted in ascending order.
    
  This class encapsulates the functionality required to manage high scores in a Minesweeper game, 
  including reading and writing score data, sorting the scores, and calculating elapsed time.


### 5. `screenButton.cpp`

  Overview:
  
  Contains the class that generates all the screen buttons.
     
    ScreenButton Class
    Purpose: Creates and manages interactive buttons on the game screen. Each button can display text, 
    change color when hovered over, and execute a function when clicked.
  
    Key Functions:
    
    Constructor:
    ScreenButton(Vector2f position, Vector2f size, const string& buttonText, function<void()> onClickFunc, 
    Color defaultCol = Color::Transparent, Color hoverCol = Color::Cyan): Initializes the button 
    with position, size, text, click behavior, and colors. It also loads the font and sets up the 
    text and shape.
    
    Drawing:
    void draw(RenderWindow& window): Draws the button's shape and text on the given window.
    
    Containment Check:
    bool contains(Vector2f point): Checks if a given point is inside the button's boundaries.
  
    Click Handling:
    void handleClick(): Executes the function attached to the button's click event.
    
    Hover Handling:
    void handleHover(Vector2f mousePos): Changes the button's color if the mouse is hovering over it.
    
  This class encapsulates the functionality required to create and manage clickable, interactive buttons with hover effects in an SFML-based game. 
  It allows for dynamic interaction by attaching custom functions to button clicks.

### 6. `textBox.cpp`
   
  Overview:
  Contains the class that generates all the text boxes.
  
    TextBox Class:
    Purpose: Creates and manages text boxes for displaying text on the game screen. Each text box can 
    display a message and has a customizable appearance.
    
    Key Functions:
    
    Constructors:
    TextBox(Vector2f position, Vector2f size): Initializes a text box at the given position and size, 
    but without any prompt text.
    Loads the font.
    Sets up the text with a default size and color.
    Sets up the text box with the given size and position.
    Loads a texture for the text box.
    
    TextBox(Vector2f position, Vector2f size, const string& prompt): Initializes a text box at 
    the given position and size, and sets a prompt text inside the text box.
    Loads the font.
    Sets up the text with the given prompt, default size, and color.
    Sets up the text box with the given size and position.
    Loads a texture for the text box.
    
    Drawing:
    void draw(RenderWindow& window): Draws the text box and its text on the provided window.
    
    Texture Setup:
    void setTexture(): Applies the texture to the text box.
    
  This class encapsulates the functionality required to create and display text boxes with or without prompt text in an SFML-based application. 
  It provides methods for initializing the text box with various configurations and for rendering it on the screen.
      

## Authors and acknowledgment
This game was created by HassanIqbal715(also hassan671), Nishat Ahmad and AhmadSaeedZaidi.

## License
This project is licensed under the Apache-2.0 license.
