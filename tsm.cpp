#include "tsm.h"

int dp[1 << (MAX_VER - 1)][MAX_VER];

int Left_Shift(int Num_Ver) {
    return 1 << Num_Ver;
}


void Run_DP(int graph[30][30], int Num_Ver, int Start_Idx) {
    
    for (int State = 1; State < Left_Shift( Num_Ver); State += 2) {
            for (int i = 0; i < Num_Ver; i++) {
                dp[State >> 1][i] = _INFI;
            }
    }

    dp[0][0] = 0;

    for (int State =  1; State < Left_Shift( Num_Ver); State += 2) {
        // turn 1
        if(State == 1){
            for(int u = 1; u < Num_Ver; u++){
                if(graph[Start_Idx][u] != 0){
                    dp[(State | Left_Shift(u)) >> 1][u] = graph[Start_Idx][u];  
                }
            }
            if(graph[Start_Idx][0] != 0){
                dp[(State | Left_Shift(Start_Idx)) >> 1][Start_Idx] = graph[Start_Idx][0];
            }
        }
        // another turn
        else {           
            for (int u = 1; u < Num_Ver; u++) {
                if (State & Left_Shift(u)) {
                    for (int v = 1; v < Num_Ver; v++) {
                        if (!(State & Left_Shift(v))) {
                            if(u == Start_Idx && graph[0][v] != 0){
                                dp[(State | Left_Shift(v)) >> 1][v] = (((dp[(State | Left_Shift(v)) >> 1][v]) >= (dp[State >> 1][u] + graph[0][v])) ? 
                                                        (dp[State >> 1][u] + graph[0][v]) : (dp[(State | Left_Shift(v)) >> 1][v]));
                            }
                            else if(v == Start_Idx && graph[u][0] != 0){
                                dp[(State | Left_Shift(v)) >> 1][v] = (((dp[(State | Left_Shift(v)) >> 1][v]) >= (dp[State >> 1][u] + graph[u][0])) ? 
                                                        (dp[State >> 1][u] + graph[u][0]) : (dp[(State | Left_Shift(v)) >> 1][v]));
                            }
                            else if(u != Start_Idx && v != Start_Idx && graph[u][v] != 0) {
                                dp[(State | Left_Shift(v)) >> 1][v] = (((dp[(State | Left_Shift(v)) >> 1][v]) >= (dp[State >> 1][u] + graph[u][v])) ? 
                                                        (dp[State >> 1][u] + graph[u][v]) : (dp[(State | Left_Shift(v)) >> 1][v]));
                            }
                            else continue;
                        }   
                    }
                }
            }  
        }

    }
}

void Find_MinCost(int graph[30][30], int Num_Ver, int Start_Idx, int& Min_Cost, int& Last_Ver) {
    Min_Cost = _INFI;

    for (int v = 1; v < Num_Ver; v++) {
        int Cost_Temp;

        if(v == Start_Idx && graph[0][Start_Idx] != 0){
            Cost_Temp = dp[Left_Shift( Num_Ver - 1) -1][v] + graph[0][Start_Idx];
            if (Cost_Temp < Min_Cost) {
                Min_Cost = Cost_Temp;
                Last_Ver = v;
            }
        }


        else if (v != Start_Idx && graph[v][Start_Idx] != 0) {
            Cost_Temp = dp[Left_Shift( Num_Ver - 1) - 1][v] + graph[v][Start_Idx];
            if (Cost_Temp < Min_Cost) {
                Min_Cost = Cost_Temp;
                Last_Ver = v;
            }
        }
    }
}

string CPath(int graph[30][30], int Num_Ver, int Start_Idx, int Last_Ver) {
    string path;
    int State = Left_Shift(Num_Ver) - 1;
    int pos = Last_Ver;

    path += (char)(Start_Idx + 'A'); // Start at the starting vertex
    path += ' ';
    if(Last_Ver == Start_Idx){
        path += 'A';
    }
    else {
        path += (char)(Last_Ver + 'A');
    }


    while (State != 1 + (1 << pos)) {
        int prev_pos = -1;
        for (int u = 1; u < Num_Ver; u++) {
            if((u == Start_Idx) && (State & Left_Shift(u)) && (u != pos) && (graph[0][pos] != 0) && (dp[State >> 1][pos] == dp[(State ^ Left_Shift(pos)) >> 1][u] + graph[0][pos])){
                prev_pos = u;
                break;
            }
            else if(pos == Start_Idx && (State & Left_Shift(u)) && u != pos && graph[u][0] != 0 && dp[State >> 1][pos] == dp[(State ^ Left_Shift(pos)) >> 1][u] + graph[u][0]){
                prev_pos = u;
                break;
            }
            else if (u != Start_Idx && pos != Start_Idx && (State & Left_Shift(u)) && u != pos && graph[u][pos] != 0 && dp[State >> 1][pos] == dp[(State ^ Left_Shift(pos)) >> 1][u] + graph[u][pos]) {
                prev_pos = u;
                break;
            }
        }
        if(prev_pos == -1){
            return " ";
        }

        path += ' ';
        if(prev_pos == Start_Idx){
            path += 'A';
        }
        else{
            path += (char)(prev_pos + 'A');
        }
        State ^= Left_Shift(pos);
        pos = prev_pos;
    }

    path += ' ';
    path += (char)(Start_Idx + 'A');


    string CPath;
    for (int v = path.size() - 1; v >= 0; v--) {
        CPath += path[v];
    }
    return CPath;
}

string Traveling(int graph[30][30], int Num_Ver, char Start_Ver) {

    int Start_Idx = Start_Ver - 'A';
    Run_DP(graph, Num_Ver, Start_Idx);

    int Min_Cost = _INFI;
    int Last_Ver;
    Find_MinCost(graph, Num_Ver, Start_Idx, Min_Cost, Last_Ver);

    if (Min_Cost == _INFI) {
        return "No valid tour exists.";
    }

    return CPath(graph, Num_Ver, Start_Idx, Last_Ver);
}

int pathlength(int G[30][30], int n, string Traveling) {
    int cost = 0;
    for (int i = 2; i < Traveling.size(); i += 2) {
        cost += G[(int)(Traveling[i - 2] - 'A')][(int)(Traveling[i] - 'A')];
    }
    return ((cost != 0) ? cost : -1);
}