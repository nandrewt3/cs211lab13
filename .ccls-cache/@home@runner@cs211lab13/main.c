/*
	Program 2: Wumpus, version 2 

  Welcome (again) to Hunt the Wumpus, a classic text-based adventure game by Gregory Yob from  1972.  This is very similar to the first program, except now we are adding superbats and an arrow that can be used to shoot the Wumpus.  All arrays must be allocated dynamically, to give us practice in doing that.

  Course: CS 211, Fall 2022. Tues 2pm lab
  System: Windows using Replit
  Author: Nandrew Thai
*/
#include <stdio.h>
#include <stdlib.h>		// for srand


//--------------------------------------------------------------------------------
void displayCave()
{
    printf( "\n"
			"       ______18______             \n"
    		"      /      |       \\           \n"
    		"     /      _9__      \\          \n"
    		"    /      /    \\      \\        \n"
    		"   /      /      \\      \\       \n"
    		"  17     8        10     19       \n"
    		"  | \\   / \\      /  \\   / |    \n"
    		"  |  \\ /   \\    /    \\ /  |    \n"
    		"  |   7     1---2     11  |       \n"
    		"  |   |    /     \\    |   |      \n"
    		"  |   6----5     3---12   |       \n"
    		"  |   |     \\   /     |   |      \n"
    		"  |   \\       4      /    |      \n"
    		"  |    \\      |     /     |      \n"
    		"  \\     15---14---13     /       \n"
    		"   \\   /            \\   /       \n"
    		"    \\ /              \\ /        \n"
    		"    16---------------20           \n"
    		"\n");
}


//--------------------------------------------------------------------------------
void displayInstructions()
{
    printf( "Hunt the Wumpus:                                             \n"
    		"The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
    		"room has 3 tunnels leading to other rooms.                   \n"
    		"                                                             \n"
    		"Hazards:                                                     \n"
        	"1. Two rooms have bottomless pits in them.  If you go there you fall and die.   \n"
        	"2. Two other rooms have super-bats.  If you go there, the bats grab you and     \n"
        	"   fly you to some random room, which could be troublesome.  Then those bats go \n"
        	"   to a new room different from where they came from and from the other bats.   \n"
    		"3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and    \n"
        	"   is too heavy for bats to lift.  Usually he is asleep.  Two things wake       \n"
        	"    him up: Anytime you shoot an arrow, or you entering his room.  The Wumpus   \n"
        	"    will move into the lowest-numbered adjacent room anytime you shoot an arrow.\n"
        	"    When you move into the Wumpus' room, then he wakes and moves if he is in an \n"
        	"    odd-numbered room, but stays still otherwise.  After that, if he is in your \n"
        	"    room, he snaps your neck and you die!                                       \n"
        	"                                                                                \n"
        	"Moves:                                                                          \n"
        	"On each move you can do the following, where input can be upper or lower-case:  \n"
        	"1. Move into an adjacent room.  To move enter 'M' followed by a space and       \n"
        	"   then a room number.                                                          \n"
        	"2. Shoot your guided arrow through a list of up to three adjacent rooms, which  \n"
        	"   you specify.  Your arrow ends up in the final room.                          \n"
        	"   To shoot enter 'S' followed by the number of rooms (1..3), and then the      \n"
        	"   list of the desired number (up to 3) of adjacent room numbers, separated     \n"
        	"   by spaces. If an arrow can't go a direction because there is no connecting   \n"
        	"   tunnel, it ricochets and moves to the lowest-numbered adjacent room and      \n"
        	"   continues doing this until it has traveled the designated number of rooms.   \n"
        	"   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You  \n"
        	"   automatically pick up the arrow if you go through a room with the arrow in   \n"
        	"   it.                                                                          \n"
        	"3. Enter 'R' to reset the person and hazard locations, useful for testing.      \n"
        	"4. Enter 'C' to cheat and display current board positions.                      \n"
        	"5. Enter 'D' to display this set of instructions.                               \n"
        	"6. Enter 'P' to print the maze room layout.                                     \n"
        	"7. Enter 'X' to exit the game.                                                  \n"
        	"                                                                                \n"
        	"Good luck!                                                                      \n"
        	" \n\n");
}//end displayInstructions()

void displayElements(int elements[7])
{
	printf( "Cheating! Game elements are in the following rooms: \n"
    		"Player Wumpus Pit1 Pit2 Bats1 Bats2 Arrow  \n"
    		"%4d %5d %6d %5d %5d %5d %5d \n\n", 
			elements[0],
			elements[1],
			elements[2],
			elements[3],
			elements[4],
			elements[5],
			elements[6]
		);
}// End displayElements()

// This function lets the player input their own values for the game elements
void resetElements(int elements[7])
{
  int playerRoom, wumpusRoom, pit1, pit2, bat1, bat2, arrow;
	printf("Enter the room locations (1..20) for player, wumpus, pit1, pit2, bats1, bats2, and arrow: \n\n");
  scanf("%d %d %d %d %d %d %d", &playerRoom, &wumpusRoom, &pit1, &pit2, &bat1, &bat2, &arrow);
	elements[0] = playerRoom;
	elements[1] = wumpusRoom;
	elements[2] = pit1;
	elements[3] = pit2;
  elements[4] = bat1;
  elements[5] = bat2;
  elements[6] = arrow;
}// end resetElements()

// This function processes the guess from the player and lets them know if they've lost or won the game
void guessWumpus(int elements[7])
{
  int guess;
  printf("Enter room (1..20) you think Wumpus is in: ");   
  scanf("%d", &guess);

  if (guess == elements[1])
  {
    printf("You won!\n");
  }
  else
  {
    printf("You lost.\n");
  }
      
  printf("\nExiting Program ...\n");
  exit(0);
}// End guessWumpus()

// This function handles the different moves that the player can make depending on what room they're in 
void movePlayer(int elements[7], int *move)
{
	int room;
  scanf("%d", &room);  

  switch (elements[0])
  {
    case 1:
    if (room != 2 && room != 5 && room != 8)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 2:
    if (room != 1 && room != 3 && room != 10)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    } 
    break;
    case 3:
    if (room != 2 && room != 4 && room != 12)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 4:
    if (room != 3 && room != 5 && room != 14)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 5:
    if (room != 1 && room != 4 && room != 6)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 6:
    if (room != 5 && room != 7 && room != 15)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 7:
    if (room != 6 && room != 8 && room != 17)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 8:
    if (room != 1 && room != 7 && room != 9)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 9:
    if (room != 8 && room != 10 && room != 18)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 10:
    if (room != 2 && room != 9 && room != 11)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;  
    case 11:
    if (room != 10 && room != 12 && room != 19)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 12:
    if (room != 3 && room != 11 && room != 13)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 13:
    if (room != 12 && room != 14 && room != 20)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;    
    case 14:
    if (room != 4 && room != 13 && room != 15)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 15:
    if (room != 6 && room != 14 && room != 16)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 16:
    if (room != 15 && room != 17 && room != 20)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 17:
    if (room != 7 && room != 16 && room != 18)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 18:
    if (room != 9 && room != 17 && room != 19)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 19:
    if (room != 11 && room != 18 && room != 20)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    case 20:
    if (room != 13 && room != 16 && room != 19)
    {
      printf("Invalid move.  Please retry. \n");	
    }
    else
    {
      elements[0] = room;
      *move += 1;
    }
    break;
    
  }
}// End movePlayer()

void checkWumpus(int elements[7], int **moves)
{
  int i;
  for (i = 0; i < 3; i++)
  {  
    if (elements[1] == (moves[elements[0]-1][i]))
    {
    printf("You smell a stench. ");
    break;
    }
  }
}// End checkWumpus()

// This function checks adjacent rooms for pit1 and displays a message if it is present
void checkPit1(int elements[7], int **moves)
{
  int i;
  for (i = 0; i < 3; i++)
  {  
    if (elements[2] == (moves[elements[0]-1][i]))
    {
	  printf("You feel a draft. ");
    break;
    }
  }
}// End checkPit1()

// This function checks adjacent rooms for pit2 and displays a message if it is present
void checkPit2(int elements[7], int **moves)
{
  int i;
  for (i = 0; i < 3; i++)
  {  
    if (elements[3] == (moves[elements[0]-1][i]))
    {
	  printf("You feel a draft. ");
    break;
    }
  }
}// End checkPit2()

// This function checks adjacent rooms for bat1 and displays a message if it is present
void checkBat1(int elements[7], int **moves)
{
  int i;
  for (i = 0; i < 3; i++)
  {  
    if (elements[4] == (moves[elements[0]-1][i]))
    {
	  printf("You hear rustling of bat wings. ");
    break;
    }
  }
}// End checkBat1()

// This function checks adjacent rooms for bat2 and displays a message if it is present
void checkBat2(int elements[7], int **moves)
{
  int i;
  for (i = 0; i < 3; i++)
  {  
    if (elements[5] == (moves[elements[0]-1][i]))
    {
	  printf("You hear rustling of bat wings. ");
    break;
    }
  }
}// End checkBat2()

// If the player is in the room with pit1 they will receive the death message and the program will end
void pitFall1(int elements[7])
{
  if (elements[0] == elements[2])
  {
	printf("Aaaaaaaaahhhhhh....   \n");
	printf("    You fall into a pit and die. \n");
  printf("\nExiting Program ...\n");
  exit(0); 
  }
}// End pitFall1()

// If the player is in the room with pit2 they will receive the death message and the program will end
void pitFall2(int elements[7])
{
  if (elements[0] == elements[3])
  {
	printf("Aaaaaaaaahhhhhh....   \n");
	printf("    You fall into a pit and die. \n");    
  printf("\nExiting Program ...\n");
  exit(0);  
  }  
}// End pitFall2()

// If the player is in the room with the wumpus and the room number is even the player will die and the program will end
void wumpusEven(int elements[7])
{
  if (elements[1] % 2 == 0)
  {
    if (elements[0] == elements[1])
    {
      printf(	"You briefly feel a slimy tentacled arm as your neck is snapped. \n"
			"It is over.\n");
      printf("\nExiting Program ...\n");
      exit(0); 
    }
  }
}// End wumpusEven()

// If the player is in the same room as the wumpus and the room number is odd the wumpus will move to the lowest number adjacent room.
void wumpusOdd(int elements[7], int **moves)
{
  if (elements[1] % 2 != 0)
  {
    if(elements[0] == elements[1])
    {
      elements[1] = moves[elements[0]-1][0];
      printf( "You hear a slithering sound, as the Wumpus slips away. \n"
			"Whew, that was close! \n");
    }
  }
}

// If the player is in the same room as bat1, the bat will carry the player to a random room within the 20 rooms and move to a random room that does not contain the player, other bat, or its original room.
void batCarry1 (int elements[7])
{
  int originalBat = elements[4];
  if(elements[0] == elements[4])
  {
    elements[0] = rand() % 20 + 1;
    printf("Woah... you're flying! \n");
    printf("You've just been transported by bats to room %d.\n", elements[0]);   

    // The code below randomizes the bats location but then checks to see if it is the same as its original position, player position, or other bat position. If any of that is true it re-randomizes.
    elements[4] = rand() % 20 + 1;
    if(elements[4] == elements[0])
    {
      elements[4] = rand() % 20 + 1;
    }
    else if(elements[4] == elements[5])
    {
      elements[4] = rand() % 20 + 1;
    }
    else if(elements[4] == originalBat)
    {
      elements[4] = rand() % 20 + 1;
    }    
  }
} // End batCarry1()

// If the player is in the same room as bat2, the bat will carry the player to a random room within the 20 rooms and move to a random room that does not contain the player, other bat, or its original room.
void batCarry2 (int elements[7])
{
  int originalBat = elements[5];
  if(elements[0] == elements[5])
  {
    elements[0] = rand() % 20 + 1;
    printf("Woah... you're flying! \n");
    printf("You've just been transported by bats to room %d.\n", elements[0]);   

    // The code below randomizes the bats location but then checks to see if it is the same as its original position, player position, or other bat position. If any of that is true it re-randomizes.    
    elements[5] = rand() % 20 + 1;
    if(elements[5] == elements[0])
    {
      elements[5] = rand() % 20 + 1;
    }
    else if(elements[5] == elements[4])
    {
      elements[5] = rand() % 20 + 1;
    }
    else if(elements[5] == originalBat)
    {
      elements[5] = rand() % 20 + 1;
    }    
    
  }
} // End batCarry2()

// Checks to see if the current room is the one with the arrow in it
void arrowStatus(int elements[7])
{
  if(elements[0] == elements[6])
  {
    printf("Congratulations, you found the arrow and can once again shoot.\n");
    elements[6] = -1; 
  }
} // End arrowStatus()

// Function that allows the user to shoot the arrow
void shootArrow(int elements[7], int **moves, int *moveCounter)
{
  // Prompts the user to enter how many rooms they want to shoot through and what rooms
  int rooms,shoot[3];
  printf("Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves: ");
  scanf("%d", &rooms);

  switch(rooms)
  {
    case 1:
    // In the case that they choose to shoot 1 room the code below executes.
    scanf("%d", &shoot[0]);
    // This code checks to see if the room the user wants to shoot is adjacent, if it is not the arrow will ricochet to the lowest value adjacent room
    if(shoot[0] != moves[elements[0]-1][0] && shoot[0] != moves[elements[0]-1][1] && shoot[0] != moves[elements[0]-1][2])
    {
      printf("Room %d is not adjacent.  Arrow ricochets...\n", shoot[0]); 
      elements[6] = moves[elements[0]-1][0];
      // After richocheting the function checks to see if the arrow landed on the wumpus and if it did it will end the game telling the player they won by luck
      if(elements[1] == elements[6])
      {
	      printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
        "Accidental victory, but still you win!\n");
        printf("\nExiting Program ...\n");     
        exit(0);
      }          
      elements[1] = moves[elements[1]-1][0];
      *moveCounter += 1;
    }
    else
    {
      // The else branch will execute if the player chooses an adjacent room.
      elements[6] = shoot[0];
      // In this case the arrow location is set to the room the player chose to shoot, if the arrow location and wumpus location are the same, the game ends and tells the player they have good aim.
      if(elements[1] == elements[6])
      {
        printf( "Wumpus has just been pierced by your deadly arrow! \n"
        "Congratulations on your victory, you awesome hunter you.\n");
        printf("\nExiting Program ...\n");     
        exit(0);
      }      
      elements[1] = moves[elements[1]-1][0];
      *moveCounter += 1;
    }
    break;
    
    case 2:
    // In the case that they choose to shoot 2 rooms the code below executes.
    scanf("%d %d", &shoot[0], &shoot[1]);
    // This code checks to see if the room the user wants to shoot is adjacent, if it is not the arrow will ricochet to the lowest value adjacent room      
    if(shoot[1] != moves[shoot[0]-1][0] && shoot[1] != moves[shoot[0]-1][1] && shoot[1] != moves[shoot[0]-1][2])   
    {
      printf("Room %d is not adjacent.  Arrow ricochets...\n", shoot[1]); 
      elements[6] = moves[shoot[0]-1][0];
      // After richocheting the function checks to see if the arrow landed on the wumpus and if it did it will end the game telling the player they won by luck      
      if(elements[1] == elements[6])
      {
	      printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
        "Accidental victory, but still you win!\n");
        printf("\nExiting Program ...\n");     
        exit(0);
      } 
      // If it just so happens that the arrow ricochets back into the players room, the game ends and tells the player they shot themselves 
      if(elements[0] == elements[6])
      {
	      printf( "You just shot yourself, and are dying.\n"
        "It didn't take long, you're dead.\n");  
        printf("\nExiting Program ...\n");     
        exit(0);        
      }
      elements[1] = moves[elements[1]-1][0];
      *moveCounter += 1;      
    }
    else
    {
      // The else branch will execute if the player chooses an adjacent room.
      elements[6] = shoot[1];
      // In this case the arrow location is set to the room the player chose to shoot, if the arrow location and wumpus location are the same, the game ends and tells the player they have good aim.      
      if(elements[1] == elements[6])
      {
        printf( "Wumpus has just been pierced by your deadly arrow! \n"
        "Congratulations on your victory, you awesome hunter you.\n");
        printf("\nExiting Program ...\n");     
        exit(0);
      }      
      // If the player chose two rooms that end up leading back to the player position, the game ends while being insulted by the game.
      if(elements[0] == elements[6])
      {
        printf( "You just shot yourself.  \n"
        "Maybe Darwin was right.  You're dead.\n");
        printf("\nExiting Program ...\n");     
        exit(0);        
      }
      elements[1] = moves[elements[1]-1][0];
      *moveCounter += 1;
    }
    break;      

    case 3:
    // In the case that they choose to shoot 3 rooms the code below executes.  
    scanf("%d %d %d", &shoot[0], &shoot[1], &shoot[2]);
    // This code checks to see if the room the user wants to shoot is adjacent, if it is not the arrow will ricochet to the lowest value adjacent room           
    if(shoot[2] != moves[shoot[1]-1][0] && shoot[2] != moves[shoot[1]-1][1] && shoot[2] != moves[shoot[1]-1][2])
    {
      printf("Room %d is not adjacent.  Arrow ricochets...\n", shoot[2]); 
      elements[6] = moves[shoot[1]-1][0]; 
      // After richocheting the function checks to see if the arrow landed on the wumpus and if it did it will end the game telling the player they won by luck        
      if(elements[1] == elements[6])
      {
	      printf( "Your arrow ricochet killed the Wumpus, you lucky dog!\n"
        "Accidental victory, but still you win!\n");
        printf("\nExiting Program ...\n");     
        exit(0);
      } 
      // If it just so happens that the arrow ricochets back into the players room, the game ends and tells the player they shot themselves       
      if(elements[0] == elements[6])
      {
	      printf( "You just shot yourself, and are dying.\n"
        "It didn't take long, you're dead.\n");  
        printf("\nExiting Program ...\n");     
        exit(0);        
      }
      elements[1] = moves[elements[1]-1][0];
      *moveCounter += 1;       
    }
    else
    {
      // The else branch will execute if the player chooses an adjacent room.
      elements[6] = shoot[2];
      // In this case the arrow location is set to the room the player chose to shoot, if the arrow location and wumpus location are the same, the game ends and tells the player they have good aim.       
      if(elements[1] == elements[6])
      {
        printf( "Wumpus has just been pierced by your deadly arrow! \n"
        "Congratulations on your victory, you awesome hunter you.\n");
        printf("\nExiting Program ...\n");     
        exit(0);
      }      
      // If the player chose three rooms that end up leading back to the player position, the game ends while being insulted by the game.      
      if(elements[0] == elements[6])
      {
        printf( "You just shot yourself.  \n"
        "Maybe Darwin was right.  You're dead.\n");
        printf("\nExiting Program ...\n");     
        exit(0);        
      }
      elements[1] = moves[elements[1]-1][0];
      *moveCounter += 1;
    }
    break;     
  } // End switch()
} // End shootArrow()
//--------------------------------------------------------------------------------
int main(void) {
  int gameElementArray[7], moveCounter = 1;
  char moveSelection;

  // Array of the possible rooms the player can move to depending on which room they are currently in
  int rows = 20, columns = 3; // Rows and columns for the array
  int **playerMovesArray = (int **)malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++)
  {
    playerMovesArray[i] = (int *)malloc(columns * sizeof(int));  
  }

  playerMovesArray[0][0] = 2;
  playerMovesArray[0][1] = 5;
  playerMovesArray[0][2] = 8;
  playerMovesArray[1][0] = 1;
  playerMovesArray[1][1] = 3;
  playerMovesArray[1][2] = 10;
  playerMovesArray[2][0] = 2;
  playerMovesArray[2][1] = 4;
  playerMovesArray[2][2] = 12;  
  playerMovesArray[3][0] = 3;
  playerMovesArray[3][1] = 5;
  playerMovesArray[3][2] = 14;
  playerMovesArray[4][0] = 1;
  playerMovesArray[4][1] = 4;
  playerMovesArray[4][2] = 6;
  playerMovesArray[5][0] = 5;
  playerMovesArray[5][1] = 7;
  playerMovesArray[5][2] = 15;
  playerMovesArray[6][0] = 6;
  playerMovesArray[6][1] = 8;
  playerMovesArray[6][2] = 17;
  playerMovesArray[7][0] = 1;
  playerMovesArray[7][1] = 7;
  playerMovesArray[7][2] = 9;
  playerMovesArray[8][0] = 8;
  playerMovesArray[8][1] = 10;
  playerMovesArray[8][2] = 18;
  playerMovesArray[9][0] = 2;
  playerMovesArray[9][1] = 9;
  playerMovesArray[9][2] = 11;
  playerMovesArray[10][0] = 10;
  playerMovesArray[10][1] = 12;
  playerMovesArray[10][2] = 19;  
  playerMovesArray[11][0] = 3;
  playerMovesArray[11][1] = 11;
  playerMovesArray[11][2] = 13;
  playerMovesArray[12][0] = 12;
  playerMovesArray[12][1] = 14;
  playerMovesArray[12][2] = 20;
  playerMovesArray[13][0] = 4;
  playerMovesArray[13][1] = 13;
  playerMovesArray[13][2] = 15;
  playerMovesArray[14][0] = 6;
  playerMovesArray[14][1] = 14;
  playerMovesArray[14][2] = 16;
  playerMovesArray[15][0] = 15;
  playerMovesArray[15][1] = 17;
  playerMovesArray[15][2] = 20;
  playerMovesArray[16][0] = 7;
  playerMovesArray[16][1] = 16;
  playerMovesArray[16][2] = 18;
  playerMovesArray[17][0] = 9;
  playerMovesArray[17][1] = 17;
  playerMovesArray[17][2] = 19;
  playerMovesArray[18][0] = 11;
  playerMovesArray[18][1] = 18;
  playerMovesArray[18][2] = 20;
  playerMovesArray[19][0] = 13;
  playerMovesArray[19][1] = 16;
  playerMovesArray[19][2] = 19;

	// Seed the random number generator.
  // Change seed to time(0) to change output each time.
  // srand(time(0));
  srand(1);

  // Setting default game element array.
  gameElementArray[0] = rand() % 20 + 1;
  for (int i = 0; i < 7; i++)
  {
    for (int j = i; j > 0; j--)
    {
      if (gameElementArray[i] == gameElementArray[j])
      {
        gameElementArray[i] = rand() % 20 + 1;
      } 
    }
  }

	while(1)
  { 
    // Checking if current room has a wumpus
    wumpusOdd(gameElementArray, playerMovesArray);
    wumpusEven(gameElementArray);
    
    // Checking if current room has a pit
    pitFall1(gameElementArray);
    pitFall2(gameElementArray);

    // Checking if current room has a bat
    batCarry1(gameElementArray);
    batCarry2(gameElementArray);

    // Rechecks the hazards when the bats drop the player off in a new room
    batCarry1(gameElementArray);
    pitFall1(gameElementArray);
    pitFall2(gameElementArray);
    wumpusOdd(gameElementArray, playerMovesArray);
    wumpusEven(gameElementArray);   
    
    // Checking if current room has an arrow
    arrowStatus(gameElementArray);
    
    // Display current room
    printf("You are in room %d. ", gameElementArray[0]);

    // Checks adjacent rooms for either the wumpus pits, or bats.
    checkWumpus(gameElementArray, playerMovesArray);
    checkPit1(gameElementArray, playerMovesArray);
    checkPit2(gameElementArray, playerMovesArray);
    checkBat1(gameElementArray, playerMovesArray);
    checkBat2(gameElementArray, playerMovesArray);
    printf("\n\n");

    // Prompt user to input a command
    printf("%d. Enter your move (or 'D' for directions): ", moveCounter);
    scanf(" %c", &moveSelection);

    // Displays the directions to play the game.
    if (moveSelection == 'D' || moveSelection == 'd')
    {
      displayCave();
      displayInstructions();
    }

    // Exits the program.
    if (moveSelection == 'X' || moveSelection == 'x')
    {
	    printf("\nExiting Program ...\n");     
      exit(0);
    }   

    // Displays the map of the cave/maze.
    if (moveSelection == 'P' || moveSelection == 'p')
    {
	    displayCave();  
    }    

    // Shows all of the game elements and is a way to cheat the game.
    if (moveSelection == 'C' || moveSelection == 'c')
    {
      displayElements(gameElementArray);
    }      

    // Lets the player change the player's room, wumpus' room, and both pits.
    if (moveSelection == 'R' || moveSelection == 'r')
    {
      resetElements(gameElementArray);  
    }      

    // Lets the player input a guess for which room the wumpus is in.
    if (moveSelection == 'G' || moveSelection == 'g')
    {
      guessWumpus(gameElementArray);
    } 

    // Lets the player move their character to a different room.
    if (moveSelection == 'M' || moveSelection == 'm')
    {
      movePlayer(gameElementArray, &moveCounter);
    }       

    // Lets the player shoot an arrow at up to 3 rooms to kill the wumpus.
    if (moveSelection == 'S' || moveSelection == 's')
    {
      if(gameElementArray[6] != -1)
      {
        printf("Sorry, you can't shoot an arrow you don't have.  Go find it.\n");
        moveCounter += 1;
      }     
      else
      {
        shootArrow(gameElementArray, playerMovesArray,&moveCounter);
      }
    }    
  } // End while()	
	return 0;
} // End main()
