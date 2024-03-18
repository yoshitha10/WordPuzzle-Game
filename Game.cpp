#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <pthread.h>
#include "login.h"
#include "Board.h"
using namespace std;

class WordQuest
{
public:
    struct Player {
        string username;
        int PNo;
        int score;
    }P[4];

    
    board Board;
    pthread_t thread1, thread2, thread3, thread4;
    pthread_mutex_t mutex;
    bool gameover=false;
    int questions_done=0;

    WordQuest()
    {
        pthread_mutex_init(&mutex, nullptr);
        for (int i=0;i<4;i++)
        {
            P[i].PNo=i;
            P[i].score=0;
        }
    }
    
    Player find_player(const int& pnoToFind) 
    {
        ifstream readFile("scores.csv");
        Player temp;
        bool found = false;
        while (readFile.good())   
        {
            string username;
            int PNo,score;
            char comma;
            readFile >> PNo >> comma >>username >> comma >> score;
            {
                temp.PNo=PNo;
                temp.score=score;
                temp.username=username;
                readFile.close();
                return temp;
            }
        }
        readFile.close();
        return temp;
    }

    void updatePlayerScore(int pno, int QNo, string inc_or_dec) 
    {
        Player curr_player=find_player(pno);
        int points;
        if (Board.qm[(curr_player.PNo)-1][QNo]==0)
            points=Board.Q[QNo].points;
        else if (Board.qm[(curr_player.PNo)-1][QNo]==10)
            points=Board.Q[QNo].points-10;
        else if (Board.qm[(curr_player.PNo)-1][QNo]==20)
            points=Board.Q[QNo].points-20;


        ifstream fileIn("Scores.csv");
        vector<Player> players;

        while (fileIn.good())   
        {
            //storing the contents of the Scores file in a vector
            string username;
            int PNo,score;
            char comma;
            fileIn >> PNo >> comma >>username >> comma >> score;
            Player temp;
            temp.PNo=PNo;
            temp.score=score;
            temp.username=username;
            players.push_back(temp);
        }
        fileIn.close();

        for (Player& p : players) 
        {
            if (p.PNo == curr_player.PNo) 
            {
                if (inc_or_dec=="increase")
                {
                    p.score += points; // Increase the score by the given value for the correct answer
                    break;
                }
                if (inc_or_dec=="deccrease")
                {
                    p.score -= points; // Deccrease the score by the given value for the choosing another chance
                    break;
                }
            }
        }

        ofstream fileOut("scores.csv");  //updating the changes made in the vector to the file
        for (const Player& p : players) 
        {
            fileOut << p.PNo << "," <<p.username << "," << p.score << "\n";
        }
        fileOut.close();
    }

    void check_question(int QNo)
    {
        for (int i=0;i<4;i++)
        {
            if (Board.qm[i][QNo]!=20)
            {
                return;
            }
        }
        cout<<"\nAll Players attempted to answer Word"<<QNo+1<<" taking all 2 hints...\nThe correct word is: "<<Board.Q[QNo].answer<<endl;
        cout<<"\nNo player can attempt this question now....!\n";
        Board.update_board(QNo);
        questions_done++;
        Board.qm[0][QNo]=100;

    }

    void print_scores()
    {
        ifstream readFile("scores.csv");
        string line;
        while (getline(readFile, line)) 
        {
            string pNo, username, score;

            size_t pos = 0;
            size_t commaPos1 = line.find(',', pos);
            pNo = line.substr(pos, commaPos1 - pos);
            pos = commaPos1 + 1;

            size_t commaPos2 = line.find(',', pos);
            username = line.substr(pos, commaPos2 - pos);
            pos = commaPos2 + 1;

            score = line.substr(pos);

            cout << "PNo: " << pNo << "\tUsername: " << username << "\tScore: " << score << endl;
        }

        readFile.close();

        ifstream file("scores.csv");
        string line1;
        string highestUser;
        int highestScore = -1; 

        if (file.is_open()) 
        {
            while (getline(file, line1)) 
            {
                size_t pos1 = line1.find(',');
                if (pos1 != string::npos) 
                {
                    string pno = line1.substr(0, pos1);

                    size_t pos2 = line1.find(',', pos1 + 1);
                    if (pos2 != string::npos) 
                    {
                        string username = line1.substr(pos1 + 1, pos2 - pos1 - 1);
                        string scoreStr = line1.substr(pos2 + 1);

                        int score = stoi(scoreStr);

                        if (score > highestScore) 
                        {
                            highestScore = score;
                            highestUser = pno + ". " + username;
                        }
                    }
                }
            }
            file.close();
        }

        if (highestScore != -1) 
        {
            cout << "\nUser with the highest score: " << highestUser << " with a score of " << highestScore << endl;
        } 
        else 
        {
            cout << "\nNo users found in the file." << endl;
        }
    }
    

    void get_hint(int PNo, const int& QNo)
    {
        PNo--;
        if (Board.qm[PNo][QNo]==0)
            {
                Board.qm[PNo][QNo]=10;
                cout<<"\nFirst Hint for the word "<<QNo+1<<" is: "<<Board.Q[QNo].hint1<<endl;
            }
            else if (Board.qm[PNo][QNo]==10)
            {
                Board.qm[PNo][QNo]=20;
                cout<<"\nSecond Hint for the word "<<QNo+1<<" :"<<endl;
                Board.queHint2(QNo);
            }
            else if (Board.qm[PNo][QNo]==20)
            {
                cout<<"\nNo more hints left for this word....!"<<endl;
            }
    }

    int choose_question(int PNo)
    {
        PNo--;
        int QNo;
        int done=0;
        while(done==0)
        {
            cout<<"\nEnter the question_no you want to answer: ";
            cin>>QNo;
            QNo--;
            done=1;
            for (int i=0;i<3;i++)
            {
                if (Board.qm[i][QNo]==100)
                {
                    cout<<"\nQuestion already done....Choose another question!\n "<<endl;
                    done=0;
                }
            }
        }
        if (Board.qm[PNo][QNo]==-1)
            Board.qm[PNo][QNo]=0;
        return QNo;
    }


    void game(int PNo)
    {
        while (!gameover) 
        {
            pthread_mutex_lock(&mutex);    // Locking the critical section
            if (gameover) 
            {
                pthread_mutex_unlock(&mutex);
                break;
            }
            Board.display();

            //Choosing a question
            int QNo;
            cout<<"\nPlayer "<<PNo<<"'s turn...."<<endl;
            QNo=choose_question(PNo);

            //Hints
            bool wantsHint;
            cout << "\nDo you want a hint? (1 for Yes, 0 for No): ";
            cin >> wantsHint;
            if (wantsHint)
                get_hint(PNo,QNo);

            //Answer
            auto start = chrono::high_resolution_clock::now(); // Start timer
            string answer;
            cout << "\nEnter your answer: ";
            cin >> answer;
            auto end = chrono::high_resolution_clock::now(); // End timer
            auto duration = chrono::duration_cast<chrono::seconds>(end - start);

            if (duration.count() >= 10) // Check if player exceeded the time limit (5 seconds)
            {
                cout << "Player " << PNo << " timed out! ";
                cout << "Player " << PNo%4 +1 << " gets the chance!\n";
                //PNo=PNo%4+1;
            }
            else
            {
                if (answer == Board.Q[QNo].answer) 
                {
                    cout << "Correct!" << endl;
                    Board.update_board(QNo);
                    //score addition
                    updatePlayerScore(PNo, QNo, "increase");
                    Board.qm[PNo-1][QNo]=100;
                    questions_done++;
                    if (questions_done==28)
                    {
                        cout<<"\nGame completed......!!!!!!"<<endl;
                        void print_scores();
                        gameover = true;  
                        pthread_mutex_unlock(&mutex);   
                        break;
                    }
                } 
                else 
                {
                    check_question(QNo);
                    if (questions_done==28)
                    {
                        cout<<"\nGame completed......!!!!!!"<<endl;
                        void print_scores();
                        gameover = true;  
                        pthread_mutex_unlock(&mutex);   
                        break;
                    }
                    bool tryAgain;
                    cout<<"\nIncorrect Answer...!!\nDo you want to try again? (...You will lose 10 points from your score...)"<<endl<<"\nEnter 1 for Yes, 0 for No:";
                    cin>>tryAgain;
                    if (tryAgain) 
                    {
                        //score reduction by 10
                        updatePlayerScore(PNo,QNo,"decrease");
                        cout<<"\nEnter your answer again: ";
                        cin>>answer;

                        if (answer == Board.Q[QNo].answer) 
                        {
                            cout << "Correct!" << endl;
                            Board.update_board(QNo);
                            //score addition
                            //int ptbr=find_points(PNo,QNo);
                            updatePlayerScore(PNo,QNo,"increase");
                            Board.qm[PNo-1][QNo]=100;
                            questions_done++;
                            if (questions_done==28)
                            {
                                cout<<"Game completed......!!!!!!"<<endl;
                                void print_scores();
                                gameover = true;  
                                pthread_mutex_unlock(&mutex);   
                                break;
                            }
                        }
                        else
                        {
                            cout<<"Incorrect answer";
                            check_question(QNo);
                            if (questions_done==28)
                            {
                                cout<<"Game completed......!!!!!!"<<endl;
                                void print_scores();
                                gameover = true;  
                                pthread_mutex_unlock(&mutex);   
                                break;
                            }
                        }

                    }
                }
            }
            cout<<"\nPlayer"<<PNo<<"'s turn is completed"<<endl;
            PNo=PNo%4+1;
            pthread_mutex_unlock(&mutex);
        }

    }

    void* player1Move() 
    {
        game(1);
        return nullptr;
    }

    void* player2Move() 
    {
        game(2);
        return nullptr;
    }

    void* player3Move() 
    {
        game(3);
        return nullptr;
    }

    void* player4Move() 
    {
        game(4);
        return nullptr;
    }

    void startGame() 
    {
        pthread_create(&thread1, nullptr, &WordQuest::player1MoveHelper, this); 
        pthread_join(thread1, nullptr);   
        
        pthread_create(&thread2, nullptr, &WordQuest::player2MoveHelper, this);  
        pthread_join(thread2, nullptr); 

        pthread_create(&thread3, nullptr, &WordQuest::player3MoveHelper, this); 
        pthread_join(thread3, nullptr);   
        
        pthread_create(&thread4, nullptr, &WordQuest::player4MoveHelper, this);  
        pthread_join(thread4, nullptr); 

        if (questions_done==28)
        {
            cout<<"\nGame completed......!!!!!!"<<endl;
            void print_scores();
        }
    }
    
    
    static void* player1MoveHelper(void* context)  
    {
        reinterpret_cast<WordQuest*>(context)->player1Move();
        return nullptr;
    }

    static void* player2MoveHelper(void* context) 
    {
        reinterpret_cast<WordQuest*>(context)->player2Move();
        return nullptr;
    }

    static void* player3MoveHelper(void* context)  
    {
        reinterpret_cast<WordQuest*>(context)->player3Move();
        return nullptr;
    }

    static void* player4MoveHelper(void* context) 
    {
        reinterpret_cast<WordQuest*>(context)->player4Move();
        return nullptr;
    }


    ~WordQuest()
    {
        pthread_mutex_destroy(&mutex);
    }

};

int main()
{
    cout<<endl;
    cout<<setw(80)<<setfill('-')<<"WORD QUEST"<<setw(80)<<setfill('-');
    cout<<"\n"<<endl;
    cout<<setw(77)<<setfill(' ')<<"RULES"<<endl;
    cout<<"\n1.Time Constraint: Players have 10 seconds to answer each question, emphasizing quick thinking."<<endl;
    cout<<"2.Two Attempts Limit: Each player can attempt a question twice(during every turn), additional attempts are not allowed."<<endl;
    cout<<"3.Hint Penalty: Taking one hint deducts 10 points; taking two hints results in a 20-point deduction."<<endl;
    cout<<"4.Strategic Choices: Players must decide when to use hints, as it affects their overall score."<<endl;
    cout<<"5.Scoring System: Points are earned for correct answers, but penalties for incorrect attempts impact the final score.\n"<<endl;
    cout<<setw(265)<<setfill('-');
    cout<<endl;
    
    WordQuest wordgame;
    cout<<"---------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    cout<<endl;

    //user details
    cout<<setw(87)<<setfill(' ')<<"Enter User Information"<<endl;
    const string userfile="user_info.csv";
    
    string username1,username2,username3,username4;
    cout<<"\nPlayer1: ";
    username1=signin(userfile);
    wordgame.P[0].username=username1;

    cout<<"\nPlayer2: ";
    username2=signin(userfile);
    wordgame.P[1].username=username2;

    cout<<"\nPlayer3: ";
    username3=signin(userfile);
    wordgame.P[2].username=username3;

    cout<<"\nPlayer4: ";
    username4=signin(userfile);
    wordgame.P[3].username=username4;
    cout<<"Players login completed.........!!"<<endl;

    const string scorefile="scores.csv";
    int p=30;
    ofstream file("scores.csv", ios::app);
    file<<1<<","<<username1<<","<<p<<"\n";
    file<<2<<","<<username2<<","<<p<<"\n";
    file<<3<<","<<username3<<","<<p<<"\n";
    file<<4<<","<<username4<<","<<p<<"\n";
    file.close();

    cout<<"\n------------------------------------------------\n";

    wordgame.startGame();
    return 0;
}

