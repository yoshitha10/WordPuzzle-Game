#include <iostream>
#include <iomanip>
using namespace std;

class board
{
private:
    char ans[14][14];

public:
    struct question{
        int Q_No;
        int points;
        string answer;
        pair<int,int> start;
        pair<int,int> end;
        string hint1;
        string hint2;
        bool across_or_down;       //if 1 across else if 0 down.
    }Q[28];
    
    int qm[4][28];
    int totalQuestions=28;

    board()
    {
        for(int i=0;i<14;i++)
        {
            for(int j=0;j<14;j++)
            {
                ans[i][j]=' ';
            }
        }
        
        for (int i=0;i<4;i++)
        {
            for (int j=0;j<28;j++)
                qm[i][j]=-1;
            
        }
    
        ans[1][0]='1';
        ans[0][2]='2';
        ans[0][4]='3';
        ans[0][6]='4';
        ans[0][8]='5';
        ans[0][10]='6';
        ans[0][13]='7';
        ans[3][1]='8';
        ans[3][7]='9';

        //Question Numbers
        for(int i=0;i<28;i++)
        {
            Q[i].Q_No=i+1;
        }

        //points
        Q[0].points=30;
        Q[1].points=30;
        Q[2].points=30;
        Q[3].points=30;
        Q[4].points=30;
        Q[5].points=30;
        Q[6].points=30;
        Q[7].points=30;
        Q[8].points=30;
        Q[9].points=30;
        Q[10].points=40;
        Q[11].points=40;
        Q[12].points=40;
        Q[13].points=40;
        Q[14].points=40;
        Q[15].points=40;
        Q[16].points=40;
        Q[17].points=40;
        Q[18].points=40;
        Q[19].points=50;
        Q[20].points=50;
        Q[21].points=50;
        Q[22].points=50;
        Q[23].points=50;
        Q[24].points=50;
        Q[25].points=50;
        Q[26].points=50;
        Q[27].points=50;

        //across-down
        Q[0].across_or_down=1;
        Q[1].across_or_down=0;
        Q[2].across_or_down=0;
        Q[3].across_or_down=0;
        Q[4].across_or_down=0;
        Q[5].across_or_down=0;
        Q[6].across_or_down=0;
        Q[7].across_or_down=1;
        Q[8].across_or_down=1;
        Q[9].across_or_down=1;
        Q[10].across_or_down=1;
        Q[11].across_or_down=1;
        Q[12].across_or_down=1;
        Q[13].across_or_down=0;
        Q[14].across_or_down=1;
        Q[15].across_or_down=1;
        Q[16].across_or_down=1;
        Q[17].across_or_down=0;
        Q[18].across_or_down=1;
        Q[19].across_or_down=1;
        Q[20].across_or_down=0;
        Q[21].across_or_down=1;
        Q[22].across_or_down=0;
        Q[23].across_or_down=1;
        Q[24].across_or_down=1;
        Q[25].across_or_down=1;
        Q[26].across_or_down=1;
        Q[27].across_or_down=1;

        //Answers
        Q[0].answer="EMPLOY";
        Q[1].answer="MISTAKE";
        Q[2].answer="LEAVE";
        Q[3].answer="YEAR";
        Q[4].answer="SUNSHINE";
        Q[5].answer="LIMITED";
        Q[6].answer="TURNING";
        Q[7].answer="SEA";
        Q[8].answer="NUMBER";
        Q[9].answer="VIRUS";
        Q[10].answer="SAVE";
        Q[11].answer="TAXI";
        Q[12].answer="ACTIVE";
        Q[13].answer="CARELESS";
        Q[14].answer="HERS";
        Q[15].answer="BEEF";
        Q[16].answer="DRAG";
        Q[17].answer="AVERAGE";
        Q[18].answer="TURKEY";
        Q[19].answer="IDEA";
        Q[20].answer="BRAIN";
        Q[21].answer="LATER";
        Q[22].answer="THAT";
        Q[23].answer="CHOICE";
        Q[24].answer="AHA";
        Q[25].answer="TENNIS";
        Q[26].answer="TUNNEL";
        Q[27].answer="SILENT";

        //Answer Co-ordinates
        Q[0].start.first=1;
        Q[0].start.second=1;
        Q[0].end.first=1;
        Q[0].end.second=6;

        Q[1].start.first=1;
        Q[1].start.second=2;
        Q[1].end.first=7;
        Q[1].end.second=2;

        Q[2].start.first=1;
        Q[2].start.second=4;
        Q[2].end.first=5;
        Q[2].end.second=4;

        Q[3].start.first=1;
        Q[3].start.second=6;
        Q[3].end.first=4;
        Q[3].end.second=6;

        Q[4].start.first=1;
        Q[4].start.second=8;
        Q[4].end.first=8;
        Q[4].end.second=8;

        Q[5].start.first=1;
        Q[5].start.second=8;
        Q[5].end.first=8;
        Q[5].end.second=8;

        Q[6].start.first=1;
        Q[6].start.second=13;
        Q[6].end.first=7;
        Q[6].end.second=13;

        Q[7].start.first=3;
        Q[7].start.second=2;
        Q[7].end.first=3;
        Q[7].end.second=4;

        Q[8].start.first=3;
        Q[8].start.second=8;
        Q[8].end.first=3;
        Q[8].end.second=13;

        Q[9].start.first=4;
        Q[9].start.second=4;
        Q[9].end.first=4;
        Q[9].end.second=8;

        Q[10].start.first=5;
        Q[10].start.second=1;
        Q[10].end.first=5;
        Q[10].end.second=4;

        Q[11].start.first=5;
        Q[11].start.second=10;
        Q[11].end.first=5;
        Q[11].end.second=13;

        Q[12].start.first=6;
        Q[12].start.second=5;
        Q[12].end.first=6;
        Q[12].end.second=10;

        Q[13].start.first=6;
        Q[13].start.second=6;
        Q[13].end.first=13;
        Q[13].end.second=6;

        Q[14].start.first=7;
        Q[14].start.second=1;
        Q[14].end.first=7;
        Q[14].end.second=4;

        Q[15].start.first=9;
        Q[15].start.second=10;
        Q[15].end.first=9;
        Q[15].end.second=13;

        Q[16].start.first=7;
        Q[16].start.second=10;
        Q[16].end.first=7;
        Q[16].end.second=13;

        Q[17].start.first=7;
        Q[17].start.second=12;
        Q[17].end.first=13;
        Q[17].end.second=12;

        Q[18].start.first=8;
        Q[18].start.second=4;
        Q[18].end.first=8;
        Q[18].end.second=9;

        Q[19].start.first=9;
        Q[19].start.second=1;
        Q[19].end.first=9;
        Q[19].end.second=4;

        Q[20].start.first=9;
        Q[20].start.second=10;
        Q[20].end.first=13;
        Q[20].end.second=10;

        Q[21].start.first=10;
        Q[21].start.second=6;
        Q[21].end.first=10;
        Q[21].end.second=10;

        Q[22].start.first=10;
        Q[22].start.second=8;
        Q[22].end.first=13;
        Q[22].end.second=8;

        Q[23].start.first=11;
        Q[23].start.second=1;
        Q[23].end.first=11;
        Q[23].end.second=6;

        Q[24].start.first=11;
        Q[24].start.second=10;
        Q[24].end.first=11;
        Q[24].end.second=12;

        Q[25].start.first=13;
        Q[25].start.second=1;
        Q[25].end.first=13;
        Q[25].end.second=6;

        Q[26].start.first=13;
        Q[26].start.second=8;
        Q[26].end.first=13;
        Q[26].end.second=13;

        Q[27].start.first=1;
        Q[27].start.second=8;
        Q[27].end.first=1;
        Q[27].end.second=13;

        //hint1
        Q[0].hint1="to keep someone at work";
        Q[1].hint1="a work which is not correct";
        Q[2].hint1="to allow something to stay at a particular place";
        Q[3].hint1="period of 12 months";
        Q[4].hint1="Ray's of light from sun";
        Q[5].hint1="to keep something below a certain amount";
        Q[6].hint1="a place where one road leads off from another";
        Q[7].hint1="large water body with salt";
        Q[8].hint1="related to math";
        Q[9].hint1="which corrupts computer files";
        Q[10].hint1="to keep something for later use";
        Q[11].hint1="a type of vehicle for hire with a driver used by a single or small group of passengers";
        Q[12].hint1="involving in activity";
        Q[13].hint1="not thinking enough about what you are doing so that you make mistakes";
        Q[14].hint1="this bag belongs to _____";
        Q[15].hint1="having disagreement with something Or cow meat";
        Q[16].hint1="to pull something along with difficulty";
        Q[17].hint1="the normal standard, amount or quality";
        Q[18].hint1="Country in the Middle East";
        Q[19].hint1="I got an _____";
        Q[20].hint1="organ protected by skull";
        Q[21].hint1="goodbye for the presnt";
        Q[22].hint1="used to refer to person or place";
        Q[23].hint1="availability of many options";
        Q[24].hint1="Expressing surprise";
        Q[25].hint1="a type of racket sport";
        Q[26].hint1="a passage under the ground";
        Q[27].hint1="one should keep their phone ______ in library";

    }

    void queHint2(int questionNo)
    {
        int n=questionNo;
        int x;
        cout<<"\nWhich letter you want to reveal: ";
        cin>>x;
        int flag=0;
        while(flag==0)
        {
            if(Q[n].across_or_down==1)
            {
                int i=Q[n].start.first;
                int j=Q[n].start.second+x-1;
                if(ans[i][j]==' ')
                {
                    cout<<"The letter "<<x<<"in the word"<<questionNo<<" is: "<< Q[n].answer[x-1];
                    flag=1;
                }
                else{
                    cout<<"\nThe letter is already revealed! Please check the board!";
                    flag=1;
                }
            }
            else{
                int i=Q[n].start.first+x-1;
                int j=Q[n].start.second;
                if(ans[i][j]==' ')
                {
                    cout<<"The letter "<<x<<"in the word"<<questionNo<<" is: "<< Q[n].answer[x-1];
                    flag=1;
                }
                else{
                    cout<<"\nThe letter is already revealed! Please check the board!";
                    flag=1;
                }
            }
        }
    }

    void update_board(int questionNo)
    {
        int x=questionNo;
        int i,j;
        int k=0;
        if(Q[x].across_or_down==1)
        {
            i=Q[x].start.first;
            for(j=Q[x].start.second;j<=Q[x].end.second;j++)
            {
                ans[i][j]=Q[x].answer[k];
                k++;
            }
            k=0;
        }
        else{
            j=Q[x].start.second;
            for(i=Q[x].start.first;i<=Q[x].end.first;i++)
            {
                ans[i][j]=Q[x].answer[k];
                k++;
            }
            k=0;
        }
    }

    void display()
    {

        cout<<"EASY"<<endl;
        cout<<endl;
        cout<<"1.Hire for work"<<endl;
        cout<<"2.Error"<<endl;
        cout<<"3.Calender duration"<<endl;
        cout<<"6.Changing direction"<<endl;
        cout<<"10.Opposite of send"<<endl;
        cout<<"11.Salon service"<<endl;
        cout<<"14.His and"<<endl;
        cout<<"17.Mean,medium"<<endl;
        cout<<"21.Not eealier"<<endl;
        cout<<"22.This and"<<endl;
        cout<<"25.Wimbeldon is a championship for this sport"<<endl;
        cout<<"26.Underground passage"<<endl; 
        cout<<"29.Opposite of stay"<<endl;        
        
        cout<<endl;
        cout<<"MEDIUM"<<endl<<endl;
        cout<<"4.Light of the nearest star"<<endl; 
        cout<<"5.Restricted or confined"<<endl;
        cout<<"8.An arithematic value"<<endl;
        cout<<"11.Vehichle for hire"<<endl;
        cout<<"12.Not passive"<<endl;
        cout<<"13.Not giving much attention or consideration about something"<<endl;
        cout<<"15.Meat from cattle"<<endl;        
        cout<<"19.Creative thought"<<endl;       
        cout<<"27.Making no sound"<<endl;

        cout<<endl;
        cout<<"HARD"<<endl<<endl;
        cout<<"7.Black or Baltic or Carribean"<<endl;
        cout<<"9.Bodily or computer infection"<<endl;
        cout<<"16.Pull along"<<endl;
        cout<<"18.Istanbul is the largest city in"<<endl;
        cout<<"20.Orange in skull"<<endl;
        cout<<"23.Selection"<<endl;
        cout<<"24.Eureka"<<endl;
        cout<<"28.TV or radio channel"<<endl;
        cout<<endl;


        // 0th row
        cout<<"\t ___\t ___\t ___\t ___\t ___\t     ___"<<endl;
        int c=2;
        cout<<" _\x1b[4m  \x1b[0m__\x1b[4m \x1b[0m_";
        for(int i=0;i<5;i++)
        {
            if(i==2)
            {
                cout<<"|_\x1b[4m"<<ans[0][c]<<"\x1b[0m_|_\x1b[4m \x1b[0m_";
            }
            else{
                cout<<"|_\x1b[4m"<<ans[0][c]<<"\x1b[0m_|\x1b[4m  \x1b[0m_";
            }
            c+=2;
        }
        cout<<"_\x1b[4m  \x1b[0m_|_\x1b[4m"<<ans[0][13]<<"\x1b[0m_|"<<endl;

        //1st row
        for(int i=0;i<7;i++)
        {
            cout<<"|_\x1b[4m"<<ans[1][i]<<"\x1b[0m_";
        }
        cout<<"|_\x1b[4m28\x1b[0m";
        for(int i=8;i<14;i++)
        {
            cout<<"|_\x1b[4m"<<ans[1][i]<<"\x1b[0m_";
        }
        cout<<"|"<<endl;

        //2nd row
        c=2;
        cout<<"     _\x1b[4m  \x1b[0m";
        for(int i=0;i<5;i++)
        {
            if(i==0 || i==2 || i==3 || i==4)
            {
                cout<<"|_\x1b[4m"<<ans[2][c]<<"\x1b[0m_|_\x1b[4m  \x1b[0m";
            }
            else{
                cout<<"|_\x1b[4m"<<ans[2][c]<<"\x1b[0m_|\t";
            }
            c+=2;
        }
        cout<<"_\x1b[4m  \x1b[0m_|_\x1b[4m"<<ans[2][13]<<"\x1b[0m_|"<<endl;

        //3rd row
        cout<<"    ";
        c=1;
        for(int i=0;i<4;i++)
        {
            cout<<"|_\x1b[4m"<<ans[3][c]<<"\x1b[0m_";
            if(i==3)
            {
                cout<<"|_\x1b[4m \x1b[0m_|";
            }
            c+=1;
        }
        c++;
        for(int i=0;i<8;i++)
        {
            cout<<"_\x1b[4m"<<ans[3][c]<<"\x1b[0m_|";
            c++;
        }
        cout<<endl;

        //4th row
        c=2;
        cout<<" \x1b[4m \x1b[0m__\x1b[4m \x1b[0m__\x1b[4m \x1b[0m";
        for(int i=0;i<7;i++)
        {
            if(i==1)
            {
                cout<<"|_\x1b[4m10\x1b[0m";   
            }
            else{
                cout<<"|_\x1b[4m"<<ans[4][c]<<"\x1b[0m_";
            }
            c++;
        }
        cout<<"|";
        c++;
        cout<<"_\x1b[4m \x1b[0m_|_\x1b[4m"<<ans[4][c]<<"\x1b[0m_|_\x1b[4m \x1b[0m__\x1b[4m \x1b[0m__|"<<"_\x1b[4m"<<ans[4][13]<<"\x1b[0m_|"<<endl;

        //5th row
        c=0;
        for(int i=0;i<5;i++)
        {
            if(i==0)
            {
                cout<<"|_\x1b[4m11\x1b[0m";   
            }
            else{
                cout<<"|_\x1b[4m"<<ans[5][c]<<"\x1b[0m_";
            }
            if(i==4)
            {
                cout<<"|";
                for(int i=0;i<3;i++)
                {
                    if(i==1)
                    {
                        cout<<"_|_\x1b[4m14\x1b[0m|";
                    }
                    else{
                        cout<<"_\x1b[4m \x1b[0m";
                    }
                    
                }
                cout<<"_|";
            }
            c++;
        }
        c=8;
        for(int i=0;i<6;i++)
        {
            if(i==1)
            {
                cout<<"_\x1b[4m12\x1b[0m|";
            }
            else{
                cout<<"_\x1b[4m"<<ans[5][c]<<"\x1b[0m_|";
            }
            c++;
        }

        //6th row
        c=2;
        cout<<endl;
        for(int i=0;i<3;i++)
        {
            if(i==2)
            {
                cout<<"_\x1b[4m \x1b[0m";
            }
            else if(i==0){
                cout<<" \x1b[4m \x1b[0m_";
            }
            else{
                cout<<"_\x1b[4m \x1b[0m_";
            }
        }
        cout<<"|_\x1b[4m"<<ans[6][c]<<"\x1b[0m_|_\x1b[4m \x1b[0m_|_\x1b[4m13\x1b[0m|";
        c=5;
        for(int i=0;i<6;i++)
        {
            cout<<"_\x1b[4m"<<ans[6][c]<<"\x1b[0m_|";
            c++;
        }
        cout<<"_\x1b[4m \x1b[0m_|_\x1b[4m18\x1b[0m|_\x1b[4m"<<ans[6][13]<<"\x1b[0m_|";

        //7th row
        c=1;
        cout<<endl<<"|_\x1b[4m15\x1b[0m|";
        for(int i=0;i<13;i++)
        {
            if(i==8)
            {
                cout<<"_\x1b[4m17\x1b[0m|";   
            }
            else if(i==4 || i==6)
            {
                cout<<"_\x1b[4m \x1b[0m_|"; 
            }
            else{
                cout<<"_\x1b[4m"<<ans[7][c]<<"\x1b[0m_|";
            }
            c++;
        }

        //8th row
        c=1;
        cout<<endl<<" _\x1b[4m \x1b[0m_|";
        for(int i=0;i<9;i++)
        {
            if(i==2)
            {
                cout<<"_\x1b[4m19\x1b[0m|";   
            }
            else if(i==1){
                cout<<"_\x1b[4m \x1b[0m_|";
            }
            else{
                cout<<"_\x1b[4m"<<ans[8][c]<<"\x1b[0m_|";
            }
            c++;
        }
        cout<<"_\x1b[4m21\x1b[0m|\x1b[4m  \x1b[0m_|_\x1b[4m"<<ans[8][12]<<"\x1b[0m_|_\x1b[4m \x1b[0m_"<<endl;

        //9th row
        c=0;
        for(int i=0;i<14;i++)
        {
            if(i==0)
            {
                cout<<"|_\x1b[4m20\x1b[0m|";
            }
            else if(i==5 || i==7)
            {
                cout<<"_\x1b[4m \x1b[0m_|";
            }
            else if(i==8)
            {
                cout<<"_\x1b[4m23\x1b[0m|";
            }
            else if(i==9)
            {
                cout<<"_\x1b[4m16\x1b[0m|";
            }
            else{
                cout<<"_\x1b[4m"<<ans[9][c]<<"\x1b[0m_|";
            }
            c++;
        }
        cout<<endl;

        //10th row
        c=0;
        for(int i=0;i<13;i++)
        {
            if(i==0)
            {
                cout<<" _\x1b[4m \x1b[0m_|";
            }
            else if(i==2 || i==3 || i==4)
            {
                if(i==4)
                {
                    cout<<"_\x1b[4m \x1b[0m_|";
                }   
                else{
                    cout<<"_\x1b[4m \x1b[0m__";
                }
            }
            else if(i==11)
            {
                cout<<"_\x1b[4m \x1b[0m_|";
            }
            else if(i==5)
            {
                cout<<"_\x1b[4m22\x1b[0m|";
            }
            else{
                cout<<"_\x1b[4m"<<ans[10][c]<<"\x1b[0m_|";
            }
            c++;
        }
        cout<<endl;

        //11th row
        c=0;
        for(int i=0;i<13;i++)
        {
            if(i==0)
            {
                cout<<"|_\x1b[4m24\x1b[0m|";
            }
            else if(i==7)
            {
                cout<<"   |";
            }
            else if(i==9)
            {
                cout<<"_\x1b[4m25\x1b[0m|";
            }
            else{
                cout<<"_\x1b[4m"<<ans[11][c]<<"\x1b[0m_|";
            }
            c++;
        }
        cout<<endl;

        //12th row
        c=0;
        for(int i=0;i<13;i++)
        {
            if(i==0 || i==7 ||i==9 || i==11)
            {
                if(i==0)
                {
                    cout<<" _\x1b[4m \x1b[0m_|";
                }
                else{
                    cout<<"_\x1b[4m \x1b[0m_|";
                }            
            }
            else if(i==2 || i==3 || i==4 || i==5)
            {
                if(i==5)
                {
                    cout<<"_\x1b[4m \x1b[0m_|";
                }
                else{
                    cout<<"_\x1b[4m \x1b[0m__";
                }   
            }
            else{
                cout<<"_\x1b[4m"<<ans[12][c]<<"\x1b[0m_|";
            }
            c++;
        }
        cout<<"_\x1b[4m \x1b[0m_"<<endl;

        //13th row
        c=0;
        for(int i=0;i<14;i++)
        {
            if(i==0)
            {
                cout<<"|_\x1b[4m26\x1b[0m|";
            }
            else if(i==7)
            {
                cout<<"_\x1b[4m27\x1b[0m|";
            }
            else{
                cout<<"_\x1b[4m"<<ans[13][c]<<"\x1b[0m_|";
            }
            c++;
        }
        cout<<endl;
    }
    
};
