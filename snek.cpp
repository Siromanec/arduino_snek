#include <iostream>
using namespace std;
bool ALIVE = true;

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
                    {       if (grid[i][j]){
                            cout << "" << 1 << " ";
                            }
                            else{
                                cout << "" << 0 << " ";
                            }
                    }
                    cout << "\n";
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
                            grid[i][j] = false;
                    }
            }
        }

};
class Location{};
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
            
            //this -> short *coords = get_coords();
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
void game_loop(){
    // spawn
    Grid grid;
    Head head;
    char command;
    grid = head.set_coords(0, 0, grid);
    grid.print();

    while (ALIVE){
        // input
        cout << "enter command: ";
        cin >> command;
        cout << "\n";

        // make move

        grid = head.read_signal(command, grid);
        grid.print();
        cout << sizeof(grid);

        // 
    }
    cout << "game over!";
    // grid.write_game_over()
    // create templates to write

}
int main()
{
    // commands: u, d, r, l
    // must have some delay before new command
    // perhaps 166 ms (1000/24*4 - approx time for one stroke)
    // if longer then boost
    // the output must be slower than input 
    /*char command;
    Grid grid;
    
    grid.pxl_on(0,0);
    //grid.print();
    cout<<"\n";
    //cout << "your move: ";
    //cin >> command;
    grid.pxl_on(0,2);
    grid.pxl_on(0,3);
    grid.pxl_on(0,4);
    grid.pxl_on(0,5);
    //grid.print();

    Head head;
    head.coords;
    cout << head.coords[0] << " " << head.coords[1] << "\n";
    grid = head.set_coords(1, 2, grid);
    head.coords;
    cout << head.coords[0] << " " << head.coords[1] << "\n";
    //grid.print();*/
    game_loop();
    return 0;
}
//short main()
//{   
//    Grid grid;
//
//    std::cout << "Hello Mother" << std::endl;
//}