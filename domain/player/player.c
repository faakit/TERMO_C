#include "player.h"

int TOTAL_DE_JOGADORES = 0;

typedef struct player {
  char *str_name;       // nome
  int played;           // qnts vezes jogou 
  float percent_win;    // porcentagem de vitorias
  int current_streak;   // sequencia de vitorias atual
  int max_streak;       // maior sequencia de vitorias 
  int wins[6];          // vitorias em n+1 jogadas
  int dead;             // derrotas
} * Player;

typedef struct allplayers {
  Player * list;
  int nPlayers;
} * AllPlayers;

Player initPlayer(){
  Player player = malloc(sizeof *player);
  player->str_name = malloc(50 * sizeof *player->str_name);
  player->played = 0;
  player->percent_win = 0;
  player->current_streak = 0;
  player->max_streak = 0;
  for(int i = 0; i < 6; i++){
    player->wins[i] = 0;
  }
  player->dead = 0;
  
  return player;
}

Player loadPlayer(){
  FILE *file = fopen(PLAYERS_FILE, "a+"); // a+ porque cria o arquivo caso não exista
  if (file == NULL) {
    exit(1);
  }
  
  Player player = initPlayer();
  char * str_name = malloc(50 * sizeof *player->str_name);

  fgets(str_name, 50, stdin);
  
  int playerFound = 0;
  do {
    fscanf(file, PLAYER_FORMAT_IN, player->str_name, &player->played, 
      &player->percent_win, &player->current_streak, &player->max_streak, 
      &player->wins[0], &player->wins[1], &player->wins[2], &player->wins[3], 
      &player->wins[4], &player->wins[5], &player->dead);

    if(strcmp(player->str_name,str_name) == 0){
      playerFound = 1;
      break;
    }
  } while (!feof(file));
  
  if(playerFound == 0){
    strcpy(player->str_name, str_name);
    player->played = 0;
    player->percent_win = 0;
    player->current_streak = 0;
    player->max_streak = 0;
    player->wins[0] = 0;
    player->wins[1] = 0;
    player->wins[2] = 0;
    player->wins[3] = 0;
    player->wins[4] = 0;
    player->wins[5] = 0;
    player->dead = 0;
  }

  free(str_name);
  fclose(file);

  return player;
}

char * getPlayerName(Player player){
  return player->str_name;
}

void savePlayer(Player player){
  FILE *file = fopen(PLAYERS_FILE, "r+"); // r+ pode ler e escrever, mas não cria arquivo
  if (file == NULL) {
    exit(1);
  }

  Player scannedPlayer = initPlayer();
  
  int playerFound = 0;
  do {
    int previousPosition = ftell(file);
    fscanf(file, PLAYER_FORMAT_IN, scannedPlayer->str_name, &scannedPlayer->played,
      &scannedPlayer->percent_win, &scannedPlayer->current_streak,
      &scannedPlayer->max_streak, &scannedPlayer->wins[0], &scannedPlayer->wins[1], 
      &scannedPlayer->wins[2], &scannedPlayer->wins[3], &scannedPlayer->wins[4], 
      &scannedPlayer->wins[5], &scannedPlayer->dead);

    if(strcmp(player->str_name,scannedPlayer->str_name) == 0){
      fseek(file, previousPosition, SEEK_SET);
      playerFound = 1;
      break;
    }
  } while (!feof(file));
  
  fprintf(file, PLAYER_FORMAT_OUT, player->str_name, player->played, 
    player->percent_win, player->current_streak, player->max_streak, 
    player->wins[0], player->wins[1], player->wins[2], player->wins[3], 
    player->wins[4], player->wins[5], player->dead);

  fclose(file);
  freePlayer(scannedPlayer);
}

void gameEnd(Player player, int round){
  player->played++;
  if(round == -1){
    player->dead++;
    if(player->current_streak > player->max_streak){
      player->max_streak = player->current_streak;
    }
    player->current_streak = 0;
  } else {
    player->wins[round]++;
    player->current_streak++;
    if(player->max_streak < player->current_streak){
      player->max_streak = player->current_streak;
    }
  }
  player->percent_win = (((float)player->played - (float)player->dead) / (float)player->played) * 100;
  savePlayer(player);
}

void resetStreak(Player player){
  if(player->current_streak > player->max_streak){
    player->max_streak = player->current_streak;
  }
  player->current_streak = 0;
  savePlayer(player);
}

void freePlayer(Player player){
  free(player->str_name);
  free(player);
}

int playerPlayedTimes(Player player){
  return player->played;
}

float playerWinRate(Player player){
  return player->percent_win;
}

int playerWinStreak(Player player){
  return player->current_streak;
}

int playerMaxStreak(Player player){
  return player->max_streak;
}

int playerWinsAt(Player player, int round){
  return player->wins[round-1];
}

int playerLoses(Player player){
  return player->dead;
}

AllPlayers readAll(){
  FILE *file = fopen(PLAYERS_FILE, "r"); 
  if (file == NULL) {
    exit(1);
  }

  AllPlayers players = malloc(sizeof *players);
  players->list = malloc(50 * sizeof(*players));
  players->nPlayers = 1;

  do {
    players->list[players->nPlayers-1] = initPlayer();
    fscanf(file, PLAYER_FORMAT_IN, 
      players->list[players->nPlayers-1]->str_name,
      &players->list[players->nPlayers-1]->played,
      &players->list[players->nPlayers-1]->percent_win, 
      &players->list[players->nPlayers-1]->current_streak,
      &players->list[players->nPlayers-1]->max_streak, 
      &players->list[players->nPlayers-1]->wins[0], 
      &players->list[players->nPlayers-1]->wins[1], 
      &players->list[players->nPlayers-1]->wins[2], 
      &players->list[players->nPlayers-1]->wins[3],
      &players->list[players->nPlayers-1]->wins[4], 
      &players->list[players->nPlayers-1]->wins[5], 
      &players->list[players->nPlayers-1]->dead
    );

    
    if(feof(file)){
      break;
    }
    
    players->nPlayers++;

  } while(players->nPlayers < 50);

  quickSort(players, 0, numberOfPlayers(players)-1);
  fclose(file);
  
  return players;
}

Player getFromAll(AllPlayers allPlayers, int index){
  return allPlayers->list[index];
}

int numberOfPlayers(AllPlayers allPlayers){
  return allPlayers->nPlayers;
}

void freeAllPlayers(AllPlayers players){
  for(int i = 0; i < numberOfPlayers(players); i++){
    freePlayer(getFromAll(players, i));
  }
  free(players->list);
  free(players);
}

void swapPlayers(Player one, Player two){
  int temp;
  float tempFloat;
  temp = one->current_streak;
  one->current_streak = two->current_streak;
  two->current_streak = temp;
  temp = one->dead;
  one->dead = two->dead;
  two->dead = temp;
  temp = one->max_streak;
  one->max_streak = two->max_streak;
  two->max_streak = temp;
  char * temp_str_name = malloc(50 * sizeof *temp_str_name);
  memmove(temp_str_name,one->str_name,strlen(one->str_name)+1);
  memmove(one->str_name,two->str_name,strlen(two->str_name)+1);
  memmove(two->str_name,temp_str_name,strlen(temp_str_name)+1);
  free(temp_str_name);
  tempFloat = one->percent_win;
  one->percent_win = two->percent_win;
  two->percent_win = tempFloat;
  temp = one->played;
  one->played = two->played;
  two->played = temp;
}

int partitionFunction(AllPlayers players, int low, int high) { 
	Player pivot = getFromAll(players, high); // Ultimo elemento
	int index = low - 1 ;

	for (int j = low; j <= high - 1; j++) { 
		if (playerWinRate(getFromAll(players, j)) > playerWinRate(pivot)){ 
			index++; 
			swapPlayers(getFromAll(players, index), getFromAll(players, j)); 
		} else if (
      (playerWinRate(getFromAll(players, j)) == playerWinRate(pivot)) &&
        playerWinStreak(getFromAll(players, j)) > playerWinStreak(pivot)
      ){
      index++; 
			swapPlayers(getFromAll(players, index), getFromAll(players, j));
    }
	} 
	swapPlayers(getFromAll(players, index+1),getFromAll(players, high)); 
	return (index + 1);   
} 

void quickSort(AllPlayers players, int low, int high) { 
	if (low < high) { 
		int pIndex = partitionFunction(players, low, high); 
		quickSort(players, low, pIndex - 1); 
		quickSort(players, pIndex + 1, high); 
	} 
} 