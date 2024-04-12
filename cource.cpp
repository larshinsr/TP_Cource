#include <iostream>
// #include <Myvector>
#include <algorithm>
#include <utility>
#include <limits.h>

template <typename T>
class Myvector {
private:
    T* data;
    size_t capacity;
    size_t size;
    const size_t INITIAL_CAPACITY = 10; // Initial capacity of the vector
    
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity]; // Allocate new array

        // Copy existing elements to the new array
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;      // Free memory of the old array
        data = newData;     // Point to the new array
        capacity = newCapacity; // Update capacity
    }

public:
    Myvector() : data(nullptr), capacity(INITIAL_CAPACITY), size(0) {
        data = new T[capacity];
    }

    // Constructor with initial capacity
    Myvector(size_t initialCapacity) : data(nullptr), capacity(initialCapacity), size(0) {
        data = new T[capacity];
    }

    // Destructor
    ~Myvector() {
        delete[] data;
    }

    // Copy constructor
    Myvector(const Myvector& other) : data(nullptr), capacity(other.capacity), size(other.size) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    // Assignment operator
    Myvector& operator=(const Myvector& other) {
        if (this != &other) {
            delete[] data;
            capacity = other.capacity;
            size = other.size;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Push element to the back of the Myvector
    void push_back(const T& value) {
        if (size >= capacity) {
            // If array is full, double the capacity
            size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
            resize(newCapacity);
        }
        data[size++] = value; // Add element and increment size
    }

    // Get size of the Myvector
    size_t getSize() const {
        return size;
    }

    // Access element at index
    T& operator[](size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    // Const access element at index
    const T& operator[](size_t index) const {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
    T* begin() {
        return data;
    }

    // Custom end function
    T* end() {
        return data + size;
    }

    // Const versions of begin and end functions
    const T* begin() const {
        return data;
    }

    const T* end() const {
        return data + size;
    }
};

template<typename T>
Myvector<Myvector<T>> deepcopy(const Myvector<Myvector<T>>& vec) {
    std::Myvector<std::Myvector<T>> copy;
    for (const auto& row : vec) {
        copy.push_back(row);
    }
    return copy;
}
const int SIZE = 9;
int distInSquare(int start_i, int start_j, int released_i, int released_j){
    int dist = (start_i-released_i) * (start_i-released_i) + (start_j - released_j) * (start_j - released_j);
    return dist;
}

int isEatingMoveAvailable(int current_i, int current_j, Myvector<Myvector<Myvector<std::pair<int, int>>>>& move_arr, Myvector<Myvector<int>>& boardArr, int currentPlayer) {
    for (auto& k : move_arr[current_i][current_j]) {
        int distInSqr = distInSquare(k.second, k.first, current_j, current_i);
        if (distInSqr != 1 && distInSqr != 2 && boardArr[k.first][k.second] == 0) {
            int m1 = (current_i + k.first) / 2;
            int m2 = (current_j + k.second) / 2;
            if (boardArr[m1][m2] == -1 || boardArr[m1][m2] == -1 || boardArr[m1][m2] == -1) {
                return 0;
            }
            if (currentPlayer == 1 && boardArr[m1][m2] == 2) {
                return 1;
            }
            if (currentPlayer == 2 && boardArr[m1][m2] == 1) {
                return 1;
            }
        }
    }
    return 0;
}
int isValid16GutiMoveAI(Myvector<Myvector<Myvector<std::pair<int, int>>>>& move_arr, int starting_j, int starting_i, int released_j, int released_i, int distInSqr, std::Myvector<std::Myvector<int>>& board_Arr, int currentPlayer) {
    // need to verify if a move to (released_i, released_j) is possible

    std::pair<int, int> target = std::make_pair(released_i, released_j);
    // cout << target << endl;
    for (auto& k : move_arr[starting_i][starting_j]) {
        if (k == target && board_Arr[target.first][target.second] == 0) {
            if (distInSqr == 1 || distInSqr == 2) {
                return 1;
            } else {
                int m1 = (starting_i + k.first) / 2;
                int m2 = (starting_j + k.second) / 2;
                if (board_Arr[m1][m2] == -1) {
                    return 1;
                }
                if (currentPlayer == 1 && board_Arr[m1][m2] == 2) {
                    return 2;
                }
                if (currentPlayer == 2 && board_Arr[m1][m2] == 1) {
                    return 2;
                }
            }
        }
    }
    return 0;
}

Myvector<std::pair<int, int>> get_all_pieces(Myvector<Myvector<int>>& board, int color) {
    Myvector<std::pair<int, int>> all_pieces;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == color) {  // counting red/human guti
                all_pieces.push_back(std::make_pair(i, j));
            }
        }
    }
    return all_pieces;
}

Myvector<Myvector<Myvector<std::pair<int, int>>>> compute_move_arr() {
    Myvector<Myvector<Myvector<std::pair<int, int>>>> arr(Myvector<Myvector<std::pair<int, int>>>(Myvector<std::pair<int, int>>()));

    arr[0][2] = {{0, 4}, {0, 6}, {1, 3}, {2, 4}};
    arr[0][4] = {{0, 2}, {0, 6}, {2, 4}, {1, 4}};
    arr[0][6] = {{0, 4}, {0, 2}, {1, 5}, {2, 4}};

    arr[1][3] = {{0, 2}, {1, 4}, {1, 6}, {2, 4}, {3, 5}};
    arr[1][4] = {{0, 4}, {1, 3}, {1, 5}, {2, 4}, {3, 4}};
    arr[1][5] = {{0, 6}, {1, 4}, {2, 4}, {3, 3}, {1, 3}};

    arr[2][0] = {{3, 1}, {4, 0}, {6, 0}, {4, 2}};
    arr[2][2] = {{2, 3}, {2, 4}, {3, 2}, {3, 3}, {4, 3}, {4, 4}};
    arr[2][3] = {{2, 2}, {2, 4}, {2, 5}, {3, 3}, {4, 3}};
    arr[2][4] = {{0, 2}, {0, 4}, {0, 6}, {1, 3}, {1, 4}, {1, 5}, {2, 2}, {2, 3}, {2, 5}, {2, 6},
                 {3, 3}, {3, 4}, {3, 5}, {4, 2}, {4, 4}, {4, 6}};
    arr[2][5] = {{2, 3}, {2, 4}, {2, 6}, {3, 5}, {4, 5}};
    arr[2][6] = {{2, 5}, {2, 4}, {3, 5}, {3, 4}, {3, 6}, {4, 6}};
    arr[2][8] = {{3, 7}, {4, 6}, {4, 8}, {6, 8}};

    arr[3][1] = {{2, 0}, {4, 1}, {5, 1}, {4, 2}, {5, 3}};
    arr[3][2] = {{2, 2}, {3, 3}, {3, 4}, {4, 2}, {5, 2}};
    arr[3][3] = {{2, 2}, {2, 3}, {2, 4}, {3, 2}, {3, 4}, {4, 4}, {4, 3}, {4, 2}, {3, 5}, {1, 5}, {5, 5}, {5, 1}, {5, 3}};
    arr[3][4] = {{2, 4}, {3, 3}, {3, 5}, {4, 4}, {1, 4}, {3, 2}, {3, 6}, {5, 4}};
    arr[3][5] = {{2, 4}, {2, 5}, {2, 6}, {3, 4}, {3, 6}, {3, 3}, {4, 4}, {4, 5}, {4, 6}, {5, 3}, {5, 5}, {5, 7}, {1, 3}};
    arr[3][6] = {{3, 4}, {3, 5}, {2, 6}, {4, 6}, {5, 6}};
    arr[3][7] = {{4, 7}, {2, 8}, {4, 6}, {5, 5}, {5, 7}};

    arr[4][0] = {{2, 0}, {4, 1}, {4, 2}, {6, 0}};
    arr[4][1] = {{4, 0}, {4, 2}, {4, 3}, {3, 1}, {5, 1}};
    arr[4][2] = {{3, 1}, {3, 2}, {3, 3}, {4, 3}, {5, 3}, {5, 2}, {5, 1}, {4, 1}, {4, 0}, {2, 0}, {2, 2}, {2, 4}, {4, 4}, {6, 4}, {6, 2}, {6, 0}};
    arr[4][3] = {{4, 2}, {3, 3}, {4, 5}, {5, 3}, {4, 1}, {2, 3}, {4, 6}, {6, 3}};
    arr[4][4] = {{4, 3}, {3, 3}, {3, 4}, {3, 5}, {4, 5}, {5, 5}, {5, 4}, {5, 3}, {4, 2}, {2, 2}, {2, 4}, {2, 6}, {4, 6}, {6, 6}, {6, 4}, {6, 2}};
    arr[4][5] = {{4, 4}, {3, 5}, {5, 5}, {5, 6}, {4, 3}, {4, 7}, {2, 5}, {6, 5}};
    arr[4][6] = {{4, 5}, {3, 5}, {3, 6}, {3, 7}, {4, 7}, {5, 7}, {5, 6}, {5, 5}, {2, 4}, {2, 6}, {2, 8}, {4, 8}, {6, 8}, {6, 6}, {6, 4}, {4, 4}};
    arr[4][7] = {{4, 6}, {3, 7}, {4, 8}, {5, 7}, {4, 5}};
    arr[4][8] = {{4, 7}, {2, 8}, {6, 8}, {4, 6}};

    // Зеркально отражаем остальные ходы
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 9; ++j) {
            arr[SIZE - 1 - i][j] = arr[i][j];
            for (auto& k : arr[SIZE - 1 - i][j]) {
                k.first = SIZE - 1 - k.first;
            }
        }
    }

    return arr;
}


Myvector<Myvector<int>> simulate_move(std::pair<int, int> piece, std::pair<int, int> move, Myvector<Myvector<int>>& board, Myvector<std::pair<int, int>>& skip, int color) {
    board[piece.first][piece.second] = 0;
    board[move.first][move.second] = color;
    for (const auto& i : skip) {
        int row = i.first;
        int col = i.second;
        board[row][col] = 0;
    }
    return board;
}

Myvector<Myvector<int>> get_valid_moves(Myvector<Myvector<int>>& board, int color, pair<int, int>& piece) {
    std::Myvector<std::Myvector<int>> valid_moves;
    int i = piece.first;
    int j = piece.second;
    auto move_arrr = compute_move_arr(); // Assuming compute_move_arr() returns a suitable data structure
    for (int ii = 0; ii < 9; ++ii) {
        for (int jj = 0; jj < 9; ++jj) {
            int distInSqr = distInSquare(j, i, jj, ii); // Assuming distanceInSquare1() is correctly defined
            int ret = isValid16GutiMoveAI(move_arrr, j, i, jj, ii, distInSqr, board, color); // Assuming isValid16GutiMoveAI() is correctly defined
            if (ret == 1) {
                valid_moves.push_back({ii, jj});
            } else if (ret == 2) {
                std::Myvector<std::pair<int, int>> step;
                int skip_i = (i + ii) / 2;
                int skip_j = (j + jj) / 2;
                step.push_back({skip_i, skip_j});
                // How to do this part with mymap, deepcopy, and eating_dfs is not clear from the original code
                // You might need to adapt this part based on your actual implementation
            }
        }
    }
    return valid_moves;
}

Myvector<Myvector<Myvector<int>>> get_all_moves(Myvector<Myvector<int>>& board, int color) {
    Myvector<Myvector<Myvector<int>>> moves;
    for (auto& piece : get_all_pieces(board, color)) {
        Myvector<Myvector<int>> valid_moves = get_valid_moves(board, color, piece);
        for (auto& i : valid_moves) {
            std::pair<int, int> move = {i[0], i[1]};
            Myvector<std::pair<int, int>> skip;
            // Populate skip according to your logic
            Myvector<Myvector<int>> temp_board = deepcopy(board); // Assuming deepcopy() is correctly defined
            Myvector<Myvector<int>> new_board = simulate_move(piece, move, temp_board, skip, color);
            moves.push_back(new_board);
        }
    }
    return moves;
}
Myvector<Myvector<int>> convert_to_Myvector(int matrix[9][9]) {
    Myvector<Myvector<int>> board(9, Myvector<int>(9));
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            board[i][j] = matrix[i][j];
        }
    }
    return board;
}
const int size = 9;
int fullyDefCells[9][9] = { {0, 0, 1, 0, 0, 1, 0, 0, 0 },
                            {0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            {1, 0, 1, 0, 0, 0, 1, 0, 1 },
                            {0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            {0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            {0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            {1, 0, 1, 0, 0, 0, 1, 0, 1 },
                            {0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            {0, 0, 1, 0, 0, 0, 1, 0, 0 } };


const int WHITE_SOLDIER = 20;
const int RED_SOLDIER = 20;
const int DEF_BONUS = 5;
const int FULLY_DEF_BONUS = 10;

const int RED_SOLDIER_CH = 1;
const int WHITE_SOLDIER_CH = 2;
const int VOID_CELL = -1;

bool isWhiteSoldier(int soldier) {             //white soldiers
    return WHITE_SOLDIER == soldier;
}

bool isRedSoldier(int soldier) {               //red soldiers
    return RED_SOLDIER == soldier;
}
int isInFullyDef(int matrix[9][9], int ch) {
    int bonus = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] == ch && matrix[i][j] == fullyDefCells[i][j]) {
                bonus += FULLY_DEF_BONUS;
            }
        }
    }

    return bonus;
}
int mainDiagonalParallel(int matrix[9][9], int ch) {
    int localBonus = 0;
    int bonus = 0;
    
    for (int i = 1; i < size+1; ++i) {                                //main diagonal
       
        if(matrix[i-1][i-1] == matrix[i][i] && matrix[i][i] == ch && matrix[i-1][i-1] == ch){
            localBonus += DEF_BONUS;
            
        }
    }
    bonus += localBonus;
    

    localBonus = 0;
    for (int i = 1; i < size - 2 + 1; ++i) {                            //higher diagonal
        
        if(matrix[i-1][i+2-1] == matrix[i][i+2] && matrix[i][i + 2] == ch && matrix[i - 1][i + 2 - 1])
            localBonus += DEF_BONUS;
    }
    bonus += localBonus;
   
    
    localBonus = 0; 
    for (int i = 3; i < size + 1; ++i) {                                //lower diagonal
        
        if (matrix[i - 1][i - 2 - 1] == matrix[i][i - 2] && matrix[i - 1][i - 2 - 1] == ch && matrix[i][i - 2] == ch) {
            localBonus += DEF_BONUS;
        }
    }
    bonus += localBonus;
    
    return bonus;
}
int sideDiagonalParallel(int matrix[9][9], int ch) {
    int bonus = 0;
    int localBonus = 0;
   
    for (int i = 1; i < size + 1; ++i) {                                //side diagonal
        
        if (matrix[i][size - i] == matrix[i-1][size - i] && matrix[i - 1][size - i] == ch && matrix[i][size - i]) {
            localBonus += DEF_BONUS;
        }
    }
    bonus += localBonus;
   
    

    localBonus=0;
    for (int i = 1; i < size - 2 + 1; ++i) {                            //hegher diagonal
      
        if (matrix[i - 1][size - i - 3 + 1] == matrix[i][size - i - 3] && matrix[i - 1][size - i - 3 + 1] == ch && matrix[i][size - i - 3] == ch) {
            localBonus += DEF_BONUS;
        }
    }
    bonus += localBonus;
    
    
    
    localBonus=0;
    for (int i = 3; i < size + 1; ++i) {                                //lower diagonal
        
        if (matrix[i - 1][size - i + 3 - 1] == matrix[i][size - i + 1] && matrix[i - 1][size - i + 3 - 1] == ch && matrix[i][size - i + 1] == ch) {
            localBonus += DEF_BONUS;
        }
    }
    bonus += localBonus;
    
      
    return bonus;
}
int columnCalc(int matrix[9][9], int ch) {
    int localBonus = 0;
    int bonus = 0;
   
    for (int j = 0; j < size; ++j) {
        for (int i = 1; i < size + 1; ++i) {
           
            if(i != 2 || i != 7) {
                if (matrix[i - 1][j] == matrix[i][j] && matrix[i - 1][j] == ch && matrix[i][j] == ch) {
                    localBonus+=DEF_BONUS;
                }
            }
            if(j == 0 || j == 8) {
                if (matrix[i - 2][j] == matrix[i][j] && matrix[i - 2][j] == ch && matrix[i][j] == ch) {
                    localBonus += DEF_BONUS;
                }
            }
        }
        
        bonus += localBonus;
        localBonus = 0; 
    }
    return bonus;    
}
int rowCalc(int matrix[9][9], int ch) {
    int localBonus = 0;
    int bonus = 0;
   
    for (int i = 0; i < size; ++i) {
        for (int j = 1; j < size + 1; ++j) {
           
            if(j != 2 || j != 7) {
                if(matrix[i][j-1] == matrix[i][j] && matrix[i][j-1] == ch && matrix[i][j] == ch){
                    localBonus+=DEF_BONUS;
                }
            }
            if (i == 0 || i == 8) {
                if (matrix[i][j - 2] == matrix[i][j] && matrix[i][j - 2] == ch && matrix[i][j] == ch) {
                    localBonus += DEF_BONUS;
                }
            }
        }
       
        bonus +=  localBonus;
        localBonus = 0;
    }
    return bonus;
    
}
int calculate(int matrix[9][9]) {
    int white = 0, red = 0;    
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] == 1) {
                red += RED_SOLDIER;
            }
            if (matrix[i][j] == 2) {
                white += WHITE_SOLDIER;
            }
        }
    }
    return white-red;
}
int Evalutate(int matrix[9][9]) {
    int white = 0, red = 0;
    white += rowCalc(matrix, WHITE_SOLDIER_CH);
    white += columnCalc(matrix, WHITE_SOLDIER_CH);
    white += mainDiagonalParallel(matrix, WHITE_SOLDIER_CH);
    white += sideDiagonalParallel(matrix, WHITE_SOLDIER_CH);
    red += rowCalc(matrix, RED_SOLDIER_CH);
    red += columnCalc(matrix, RED_SOLDIER_CH);
    red += mainDiagonalParallel(matrix, RED_SOLDIER_CH);
    red += sideDiagonalParallel(matrix, RED_SOLDIER_CH);
    return  white - red + calculate(matrix) + (isInFullyDef(matrix, WHITE_SOLDIER_CH) - isInFullyDef(matrix, RED_SOLDIER_CH));
}
int checkWinner(int matrix[9][9]) {
    int redSoldiersCount = 0;
    int whiteSoldiersCount = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (matrix[i][j] == RED_SOLDIER_CH) {
                ++redSoldiersCount;
            }
            if (matrix[i][j] == WHITE_SOLDIER_CH) {
                ++whiteSoldiersCount;
            }
        }
    }
    if (redSoldiersCount == 0) {
        std::cout << "White Won" << std::endl;
        return 1;
    }
    if (whiteSoldiersCount == 0) {
        std::cout << "Red Won" << std::endl;
        return 2;
    }
    return 0;
}
int minimax(Myvector<Myvector<int>>& board, int depth, bool maximizing_player) {
    Myvector<Myvector<int>> board = convert_to_Myvector(matrix);
    int winner = checkWinner(matrix);
    if (depth == 0 || winner != 0) {
        if (winner == WHITE_SOLDIER_CH)
            return INT_MAX; // Maximize score for white
        else if (winner == RED_SOLDIER_CH)
            return INT_MIN; // Minimize score for red
        else
            return Evalutate(matrix); // Evaluate the board
    }

    if (maximizing_player) {
        int max_eval = INT_MIN;
        Myvector<std::pair<std::pair<int, int>, std::pair<int, int>>> moves = generate_moves(board, WHITE_SOLDIER_CH);
        for (auto& move : moves) {
            Myvector<Myvector<int>> new_board = simulate_move(move.first, move.second, board, {}, WHITE_SOLDIER_CH);
            int eval = minimax(new_board, depth - 1, false);
            max_eval = std::max(max_eval, eval);
        }
        return max_eval;
    } else {
        int min_eval = INT_MAX;
        Myvector<std::pair<std::pair<int, int>, std::pair<int, int>>> moves = generate_moves(board, RED_SOLDIER_CH);
        for (auto& move : moves) {
            Myvector<Myvector<int>> new_board = simulate_move(move.first, move.second, board, {}, RED_SOLDIER_CH);
            int eval = minimax(new_board, depth - 1, true);
            min_eval = std::min(min_eval, eval);
        }
        return min_eval;
    }
}

// Function to call Minimax
std::pair<int, std::pair<int, int>> find_best_move(Myvector<Myvector<int>>& board, int color) {
    int best_eval = INT_MIN;
    std::pair<int, int> best_move = {-1, -1};
    Myvector<std::pair<std::pair<int, int>, std::pair<int, int>>> moves = generate_moves(board, color);
    for (auto& move : moves) {
        Myvector<Myvector<int>> new_board = simulate_move(move.first, move.second, board, {}, color);
        int eval = minimax(new_board, 3, false);
        if (eval > best_eval) {
            best_eval = eval;
            best_move = move.second;
        }
    }
    return {best_eval, best_move};
}
int main() {
    // std::Myvector<std::Myvector<std::Myvector<std::pair<int, int>>>> arr = compute_move_arr();

    // // Пример вывода всех возможных ходов для каждой ячейки
    // for (int i = 0; i < SIZE; ++i) {
    //     for (int j = 0; j < SIZE; ++j) {
    //         std::cout << "Possible moves for cell (" << i << ", " << j << "): ";
    //         for (auto& move : arr[i][j]) {
    //            std::cout << "(" << move.first << ", " << move.second << ") ";
    //         }
    //         std::cout <<std:: endl;
    //     }
    // }
    int matrix[9][9] = {    {-1, -1, 1, -1, 1, -1, 1, -1, -1 },
                            {-1, -1, -1, 1, 1, 1, -1, -1, -1 },
                            {0, -1, 1, 1, 1, 1, 1, -1, 0 },
                            {-1, 0, 1, 1, 1, 1, 1, 0, -1 },
                            {0, 0, 0, 0, 0, 0, 0, 0, 0 },
                            {-1, 0, 2, 2, 2, 2, 2, 0, -1 },
                            {0, -1, 2, 2, 2, 2, 2, -1, 0 },
                            {-1, -1, -1, 2, 2, 2, -1, -1, -1 },
                            {-1, -1, 2, -1, 2, -1, 2, -1, -1 } };
    
   
    int result = Evalutate(matrix);
    if (result < 0) {
        std::cout<<" Red Wins "<< result << std::endl;
    }
    else {
        std::cout<<" White Wins "<< result << std::endl;
    }

    return 0;
}
