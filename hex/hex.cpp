int max_function(int deep,double alpha,double beta){
    if(deep == 0){
        return evaluate1();
    }
    int flag = 0;
    double best = - MAX_VALUE;
    for(int i = 0;i<11;i++){
        for (int j =0;j<11;j++){
            if(board[i][j]==0){
                board[i][j] = color + 1;
                double value = min_function(deep-1, alpha, best > beta ? best : beta);
                board[i][j] = 0;

                if(value>best)
                {
                    best = value;
                }
                if(value > alpha)
                {
                    flag = 1;
                    break;
                }
            }
        }
        if(flag)
            break;
    }
    return best;
}
int min_function(int deep,double alpha, double beta){
    if(deep == 0){
        return evaluate1();
    }
    int flag = 0;
    double best =  MAX_VALUE;
    for(int i = 0;i<11;i++){
        for (int j =0;j<11;j++){

            if(board[i][j]==0){
                board[i][j] = (!color) + 1;
                double value = max_function(deep-1, best < alpha ? best : alpha, beta);
                board[i][j] = 0;

                if(value>best)
                {
                    best = value;
                }
                if(value < beta)
                {
                    flag = 1;
                    break;
                }
            }
        }
        if(flag)
            break;
    }
    return best;
}
