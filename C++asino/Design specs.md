### Classes
##### Player
- Object contains chip count, game history
- Object reads from / writes to file
- Auto saving

##### Game
- Runs game upon member function call
- Interfaces with Player to transfer game history and alter chip count

##### Menu
- Object prompts user input for progressing through / displaying menus according to scripts
- May be implemented in games themselves for cohesion

##### Deck
- Object contains arbitrary number of Card objects
- Object contains member functions for adding, removing, shuffling, etc contained cards

##### Card
- Object contains suit, rank, and state (face-up / face-down)
- Object contains member function to change state

