
short VRx = A0;
short VRy = A1;
short SW = 2;

short xPosition = 0;
short yPosition = 0;
short SW_state = 0;
short mapX = 0;
short mapY = 0;

short count_loops = 0;
short fps = 24; // can also be speed
short game_speed = 50; // percents. 100 is one second. the more fps the more accurate
bool ALIVE = true;
bool SETUP = true;
class Grid{
    public:
        // nokia 5110 84x48
        static const short rows = 48;
        static const short cols = 84;
        bool grid[rows][cols];
        Grid(){
            this -> clear(); // i guess works like self.clear()
            
        }


        void print(){
            for(short i = 0; i < rows; i++)
            {
                    for(short j = 0; j < cols; j++)
                    {
                            if (grid[i][j]){
                             Serial.print(1);
                            }
                            else{
                             Serial.print(0);
                            }

                    }
                    Serial.print("\n");
            }
        }

        void pxl_on(short row, short col){
            grid[row][col] = true;
        }


        void pxl_off(short row, short col){
            grid[row][col] = false;
        }
        bool taken(short row, short col){
            if (grid[row][col]){return true;}
            else{return false;}
        }

        void clear(){
            for(short i=0; i<rows; i++)
            {
                    for(short j=0; j<cols; j++)
                    {
                            grid[i][j] = 0;
                    }
            }
        }

};

class Head{
    public:
        short coords[2] = {0, 0};
        short * get_coords(){
            // cout << coords << endl;
            return coords;
        }
        bool check_neighbors(){
            short * coords = get_coords();
            short neck;
            short tail;
            bool possible;
            short pool[4][2] = {{},{},{},{}};
        }
        short find_neck(){
            // prev_move_direction
            // store prev move
            // opposite is neck
        }
        Grid set_coords(short row, short col, Grid grid){
            coords[0] = row;
            coords[1] = col;
            if (not grid.taken(row, col)){
                grid.pxl_on(row, col);
            }
            else{
                // raise game over
                ALIVE = false;
            }
            // grid.print();
            return grid;
        // grid.pxl_off() where the tail isA
        }
        Grid read_signal(char command, Grid grid){
            
            //this -> int *coords = get_coords();
            // need to catch getting out of boundaries
            short row;
            short col;
            short grid_rows = grid.rows;
            short grid_cols = grid.cols;

            switch (command)
            {
            case 'u':
                row = coords[0] - 1;
                col = coords[1];
                row = ((row % grid_rows) + grid_rows) % grid_rows;
                break;
            case 'd':
                row = coords[0] + 1;
                col = coords[1];
                row = ((row % grid_rows) + grid_rows) % grid_rows;

                break;
            case 'r':
                row = coords[0];
                col = coords[1] + 1;
                col = ((col % grid_cols) + grid_cols) % grid_cols;

                break;
            case 'l':
                row = coords[0];
                col = coords[1] - 1;
                col = ((col % grid_cols) + grid_cols) % grid_cols;

                break;
            
            default:
                break;
            }
            grid = this -> set_coords(row, col, grid);
            return grid;
}

};


void setup() {
  Serial.begin(9600); 
  
  pinMode(VRx, INPUT);
  pinMode(VRy, INPUT);
  pinMode(SW, INPUT_PULLUP);
  

}

    Grid grid;
    Head head;
    char command;
    
void loop() {


  xPosition = analogRead(VRx);
  yPosition = analogRead(VRy);
  SW_state = digitalRead(SW);
  mapX = map(xPosition, 0, 1023, -512, 512);
  mapY = map(yPosition, 0, 1023, -512, 512);

  if      (mapX < -300 and -100 < mapY and mapY < 100){
    command = 'u'; // up
    }
  else if (mapX >  300 and -100 < mapY and mapY < 100){
    command = 'd'; // down
    }
  else if (mapY < -300 and -100 < mapX and mapX < 100){
    command = 'r'; // right
    }
  else if (mapY >  300 and -100 < mapX and mapX < 100){
    command = 'l'; // left
    }  
  else{
    
    }
  // this is for doing the grapical output, which must be slower
  // also i figured sending signal mustn`t be exclusive for a special tick
  // so it can do the command in the same time
  Serial.print(" | direction: ");
  Serial.println(command);
    if (SETUP){

    grid = head.set_coords(0, 0, grid);
    grid.print();
    SETUP = false;
    }
  if (count_loops == fps*100/game_speed){
    count_loops = 0;
    //  send_signal(command);
    // game_speed++;
        if (ALIVE){

        grid = head.read_signal(command, grid);
        grid.print();

        // 
    }
    else {Serial.println("game over!");}
    Serial.println(" | the move is done");
    }
  else{
    //command = ' ';
    count_loops++;
  }
  // Serial.print("X: ");
  // Serial.print(mapX);
  // Serial.print(" | Y: ");
  // Serial.print(mapY);
  // Serial.print(" | Button: ");
  // Serial.print(SW_state);
      // spawn



  delay(1000/fps);
  
}
