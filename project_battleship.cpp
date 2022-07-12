#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <iomanip>
using namespace std;

int array_hit[1][2]={0,0};

void Clear(int arr_size, int **arr){    //grid 初始化
    for(int i=0; i <arr_size; i++){
        for(int j=0; j < arr_size; j++){
            arr[i][j] = 0;
        }
    }
}


void gridDisplay(int arr_size, int **arr){     //印出grid
    cout << "Y" << endl;
    for(int i = arr_size-1; i >= 0; i--) {
        cout << i+1 << "\t";
        for(int j = 0; j<arr_size; j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }

    for(int j = 0; j <= arr_size; ++j)
        cout << j << "\t";
    cout << "X";
    cout << endl;

}


int gridsizeEntry(){               //輸入棋盤大小
    int n;
    do{
        cout << "Input size of grid:";
        cin >> n;
        if (n<=0)
            cout << "Wrong!" <<endl;
    }
    while(n<=0);

    return n;
}

int shipsizeEntry(){                 //輸入船隻大小
    int n;
    do{
        cout << "Input size of ship:";
        cin >> n;
        if (n<=0)
            cout << "Wrong!" <<endl;
    }
    while(n<=0);

    return n;
}

void shipPositionEntry(int sizeofship,  int **arr, int gridsizeEntry){     //輸入船隻方向
    int x,y,w,t;
    cout << "Input amount of ship: ";
    cin >> t;
    for(int i=0;i<t;i++){
        bool position2 = true;
        while(position2){
            bool position = true;

            while(position){
                cout << "Input position of x and y (boat" << i+1 << "):";
                cin >> x >> y;
                cout << "Input the direction of ship(up=1;right=2;left=3;down=4): ";
                cin >> w;
                if(x>=1 && x<= gridsizeEntry && y>=1 && y<= gridsizeEntry){
                    if(w==1 && y+sizeofship-1 <= gridsizeEntry)
                        position = false;
                    else if(w==2 && x+sizeofship-1 <= gridsizeEntry)
                        position = false;
                    else if(w==3 && x-sizeofship >= 0)
                        position = false;
                    else if(w==4 && y-sizeofship >= 0)
                        position = false;
                    else cout << "Wrong!\n";
                }
                else
                    cout << "Wrong!\n";
            }

            if(w==1){
                for(int i=0;i<sizeofship;i++){
                    if(arr[y-1][x-1]!=9){
                        position2 = false;
                        arr[y-1][x-1]=9;
                        y++;
                    }
                    else {cout << "Wrong!\n";
                        break;}
                }
            }

            else if(w==2){
                for(int i=0;i<sizeofship;i++){
                    if(arr[y-1][x-1]!=9){
                    position2 = false;
                    arr[y-1][x-1]=9;
                    x++;
                }
                else{
                    cout << "Wrong!\n";
                    break;}
                }
            }

            else if(w==3){
                for(int i=0;i<sizeofship;i++){
                    if(arr[y-1][x-1]!=9){
                        position2 = false;
                        arr[y-1][x-1]=9;
                        x--;
                    }
                    else{
                        cout << "Wrong!\n";
                        break;
                    }
                }
            }
            else if(w==4){
                for(int i=0;i<sizeofship;i++){
                    if(arr[y-1][x-1]!=9){
                        position2 = false;
                        arr[y-1][x-1]=9;
                        y--;
                    }
                    else{
                        cout << "Wrong!\n";
                        break;
                    }
                }
            }
        }
    }
}

bool gameExiting(int **arr){      
    int n;
    cout << "1. Start to battle " << endl;
    cout << "2. Absort (restart) " << endl;
    cout << "Are you ready to battle ?(1 to start) " ;
    cin >> n;
    if(n == 1)
       return true;
    else
       return false;
}

int WhereYouHit(int **arr2,int x,int y,int yn,int j,double &hit2,double round){
    srand(time(0));
    int random_emoticon=rand()%5;
    static const char *enum_str1[] = { "_(┐「﹃ﾟ｡)_", "Σヽ(ﾟД ﾟ; )ﾉ", "Σ(ﾟДﾟ；≡；ﾟдﾟ)", "┌|◎o◎|┘" ,"ฅ(๑*д*๑)ฅ!!"};
    static const char *enum_str2[] = { "(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧", "⁽⁽٩(๑˃̶͈̀ ᗨ ˂̶͈́)۶⁾⁾", "(●´ω｀●)ゞ", "ก็ʕ•͡ᴥ•ʔก้" ,"⎝(◕u◕)⎠"};
    if(yn==1){
        x--;
        y--;
        hit2++;
        arr2[y][x]=1;
        cout << "hit " <<enum_str2[random_emoticon]<< "  Hit rate:" << setprecision(4) << fixed << hit2/round*100 << "%"  << endl;
        j--;
    }
    else if(yn==2){
        x--;
        y--;
        arr2[y][x]=2;
        cout << "miss" <<enum_str1[random_emoticon]<< "  Hit rate:" << setprecision(4) << fixed << hit2/round*100 << "%" << endl;
    }

    return j;
}

void HittingDetection(int **arr,int x,int y,double &hit,double round){
    srand(time(0));
    int random_emoticon=rand()%5;
    static const char *enum_str1[] = { "_(┐「﹃ﾟ｡)_", "Σヽ(ﾟД ﾟ; )ﾉ", "Σ(ﾟДﾟ；≡；ﾟдﾟ)", "┌|◎o◎|┘" ,"ฅ(๑*д*๑)ฅ!!"};
    static const char *enum_str2[] = { "(ﾉ◕ヮ◕)ﾉ*:･ﾟ✧", "⁽⁽٩(๑˃̶͈̀ ᗨ ˂̶͈́)۶⁾⁾", "(●´ω｀●)ゞ", "ก็ʕ•͡ᴥ•ʔก้" ,"⎝(◕u◕)⎠"};
    x--;
    y--;
    if(arr[y][x] == 9){
        hit++;
        cout << "hit " <<enum_str1[random_emoticon]<< "  Hit rate:" << setprecision(4) << fixed << hit/round*100 << "%" <<endl;
        arr[y][x]=1; 
    }
    else{
        cout << "miss" <<enum_str2[random_emoticon]<< "  Hit rate:" << setprecision(4) << fixed << hit/round*100 << "%" << endl;
        arr[y][x]=2;
    }
}

void HittingpositionEntry(int **arr,double &round){
    int x,y;
    cout << "ROUND:" << static_cast<int>(round) << "  Input position to fire the missle: ";
    cin >> x >> y;
    array_hit[0][0]=x;
    array_hit[0][1]=y;
}

bool LosingDetection(int **arr,int arr_size){
    for(int i=0; i <arr_size; i++){
        for(int j=0; j < arr_size; j++)
            if(arr[i][j]==9)
                return true;
    }

    return false;
}

int Enemy_ship_size(){
    int n;
    cout << "Input size of enemy ship:";
    cin >> n;

    return n;
}



int main(){
    int j; //敵人剩多少船身
    int sizeofship; //船隻大小
    int n; //輸入棋盤大小
    int ** array; //我方棋盤
    int ** array2; //敵方棋盤
    int x=0,y,yn; //宣告X座標，Y座標，擊中(打敵方的)
    int First; //先攻後攻
    double hit=0; //敵方打到自己幾次
    double hit2=0; //自己打到敵方幾次
    double round=1; //回合
    double round2=0; //總局數
    double i=0;
    
    while(x!=-1){
        hit=0;
        hit2=0;
        round=1;
        round2++;
        n=gridsizeEntry();
        array = new int * [n];
        for (int i=0; i<n; i++)
        {
            array[i] = new int [n];
        }
        array2 = new int * [n];

        for (int i=0; i<n; i++)
        {
            array2[i] = new int [n];
        }

        //印棋盤1
        cout << "Your grid" << endl;; 
        Clear(n,array);
        gridDisplay(n,array);

        //印棋盤2
        cout << "Enemy's grid" << endl; 
        Clear(n,array2);
        gridDisplay(n,array2);

        //船的大小方向位置
        sizeofship=shipsizeEntry(); 
        shipPositionEntry(sizeofship,array,n);
        cout << "The position of your ship: " << endl;
        gridDisplay(n,array);

        //敵方船的大小
        j=Enemy_ship_size();

        //準備開始
        bool entry = gameExiting(array); 

        //先攻後攻
        if(entry==true){
            cout<<"Who attack first?(1:You,2:Enemy)";
            cin>>First;
        }

      //如果先攻
        if(First==1){
            while(entry==true){
                //打敵方船
                cout<<"ROUND:" << static_cast<int>(round) << "  Where do you like to hit your enemy? ( x=-1 to quit )";
                cin>>x;
                if(x==-1){break;}
                cin>>y;
                cout<<"Hit or not？（1：Yes，2：No）";
                cin>>yn;

                //有沒有贏
                j=WhereYouHit(array2,x,y,yn,j,hit2,round); 
                cout<<"Enemy's grid" << endl;
                gridDisplay(n,array2);
                if(j==0){
                    cout<<"you win"<<"ξ( ✿＞◡❛)▄︻▇▇〓▄︻┻┳═一"<<endl;
                    i++;
                    break;
                }

                //敵方打自己船
                HittingpositionEntry(array,round);
                HittingDetection(array,array_hit[0][0],array_hit[0][1],hit,round);
                cout<<"Your grid" << endl;
                gridDisplay(n,array); 

                //有沒有輸
                if(LosingDetection(array,n)==false){
                    cout << "You lose! "<<"⊂(°Д°⊂⌒｀つ≡≡≡(´⌒;;;≡≡≡";
                    break;
                }
                round++;
            }
        }
        else{//如果後攻
            while(entry==true){
            
            //敵方打自己船
            HittingpositionEntry(array,round);
            HittingDetection(array,array_hit[0][0],array_hit[0][1],hit,round);
            cout<<"Your grid" << endl;
            gridDisplay(n,array); 

            //有沒有輸
            if(LosingDetection(array,n)==false){
                cout << "You lose! "<<"⊂(°Д°⊂⌒｀つ≡≡≡(´⌒;;;≡≡≡"<<endl;
                break;
            }
            
            //打敵方船
            cout<<"Where do you like to hit your enemy? ( x=-1 to quit )";
            cin>>x;
            if(x==-1){break;}
            cin>>y;
            cout<<"Hit or not？（1：Yes，2：No）";
            cin>>yn;

            //有沒有贏
            j=WhereYouHit(array2,x,y,yn,j,hit2,round); 
            cout<<"Enemy's grid" << endl;
            gridDisplay(n,array2);
            if(j==0){
                cout<<"you win"<<"ξ( ✿＞◡❛)▄︻▇▇〓▄︻┻┳═一"<<endl;
                i++;
                break;
            }
            round++;
            }
        }

        for (int i=0; i<n; i++){
            delete [] array[i];
            delete [] array2[i];
        }
        delete [] array;
        delete [] array2;

        cout<<"Play again?(1:yes,-1:no):";
        cin>>x;
    }

    cout << "Game Over!\n" << "The winning rate is: " << i/round2*100 << "%" <<endl;

    return 0;

 }