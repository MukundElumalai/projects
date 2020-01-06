//to implement the optimum 4-position dynamic programming algorithm along with 3,5-position algorithms
#include<iostream>
using namespace std;
int J,I;
int D[20][20];
char A[20][20];
int score1,score2,score3,score4,score5;
char *testdna,*refdna;

char anst[20],ansr[20];
int a1=0,a2=0;

//to find the max for three, four and five variables
int maxi(int a,int b,int c,int d,int e){
    if(a>=b && a>=c && a>=d && a>=e)return a;
    else if (b>=c && b>=d && b>=e)return b;
    else if(c>=d && c>=e)return c;
    else if(d>=e)return d;
    else return e;
}
int maxi(int a,int b,int c){
    if(a>=b && a>=c)return a;
    else if (b>=c)return b;
    else return c;
}
int maxi(int a,int b,int c,int d){
    if(a>=b && a>=c && a>=d)return a;
    else if (b>=c && b>=d)return b;
    else if(c>=d)return c;
    else return d;
}

//this calculates the better choice of gaps,matches for the alignment
int score_calc(int choice){
    D[0][0]=0;
    D[0][1]=-2;
    D[1][0]=-2;
    D[1][1]=0;
    for(int i=2;i<=I+1;i++){
        D[0][i]=D[0][i-1]-2;
        D[1][i]=D[1][i-1]-2;
    }
    for(int j=2;j<=J+1;j++){
        D[j][0]=D[j-1][0]-2;
        D[j][1]=D[j-1][1]-2;
    }
    int j=0;
    for(int j1=2;j1<=J+1;j1++){
        j=j1-2;
        int i=0;
        for(int i1=2;i1<=I+1;i1++){
            i=i1-2;
            //match
            if(refdna[i]==testdna[j])
                score1=D[j1-1][i1-1]+1;
            //mismatch
            else
                score1=D[j1-1][i1-1]-1;
            //gap in test string
            score2=D[j1-1][i1]-2;
            //gap in reference string
            score4=D[j1][i1-1]-2;
            //horizontal cross to minimize gap insertions
            if(i!=0){
                if(refdna[i-1]==testdna[j])
                    score3=D[j1-1][i1-2];
                else
                    score3=D[j1-1][i1-2]-2;
            }
            else
                score3=D[j1-1][i1-2]-2;
            //vertical cross to minimize gap insertion
            if(j!=0){
                if(refdna[i]==testdna[j-1])
                    score5=D[j1-2][i1-1];
                else
                    score5=D[j1-2][i1-1]-2;
            }
            else
                score5=D[j1-2][i1-1]-2;
            int maxscore;
            if(choice==5)maxscore=maxi(score1,score2,score3,score4,score5);
            else if(choice==4)maxscore=maxi(score1,score2,score3,score4);
            else maxscore=maxi(score1,score2,score4);
            D[j1][i1]=maxscore;

            // prioritizing less horizontal and vertical crosses
            if(A[j1-1][i1-2]=='c' || A[j1-2][i1-1]=='p'){
                if(maxscore==score2)
                    A[j1][i1]='v';
                else if(maxscore==score4)
                    A[j1][i1]='h';
                else if(maxscore==score1 ||choice==3)
                    A[j1][i1]='d';
                else if(maxscore==score3 ||choice==4)
                    A[j1][i1]='c';
                else
                    A[j1][i1]='p';
            }
            else{
                if(maxscore==score3 && choice!=3)
                    A[j1][i1]='c';
                else if(maxscore==score5 && choice==5)
                    A[j1][i1]='p';
                else if(maxscore==score2)
                    A[j1][i1]='v';
                else if(maxscore==score4)
                    A[j1][i1]='h';
                else
                    A[j1][i1]='d';
            }
        }
    }
    return D[J+1][I+1];
}

//printing the strings with gaps and matches
void print_path(int j,int i){
    if(i==1 && j==1)
        return;
    if(j==1){
        print_path(j,i-1);
        ansr[a2++]=refdna[i-2];
        anst[a1++]=' ';
    }
    else if(i==1){
        print_path(j-1,i);
        anst[a1++]=testdna[j-2];
        ansr[a2++]=' ';
    }
    else if(A[j][i]=='d'){
        print_path(j-1,i-1);
        anst[a1++]=testdna[j-2];
        ansr[a2++]=refdna[i-2];
    }
    else if(A[j][i]=='v'){
        print_path(j-1,i);
        anst[a1++]=testdna[j-2];
        ansr[a2++]=' ';
    }
    else if(A[j][i]=='c'){
        print_path(j-1,i-2);
        anst[a1++]=testdna[j-2];
        anst[a1++]=' ';
        ansr[a2++]=refdna[i-3];
        ansr[a2++]=refdna[i-2];
    }
    else if(A[j][i]=='p'){
        print_path(j-2,i-1);
        anst[a1++]=testdna[j-3];
        ansr[a2++]=refdna[i-2];
        anst[a1++]=testdna[j-2];
        ansr[a2++]=' ';
    }
    else if(A[j][i]=='h'){
        print_path(j,i-1);
        ansr[a2++]=refdna[i-2];
        anst[a1++]=' ';
    }
}

int main(){
    cout<<"Enter the length of ref-dna sequence\n";
    cin>>I;
    refdna=new char[I+1];
    cout<<"\nEnter the sequence\n";
    cin>>refdna;
    cout<<"Enter the length of test-dna sequence\n";
    cin>>J;
    testdna=new char[J+1];
    cout<<"\nEnter the sequence\n";
    cin>>testdna;
    cout<<endl<<score_calc(3);
    cout<<endl;
    print_path(J+1,I+1);
    ansr[a2++]='\0';
    anst[a1++]='\0';
    cout<<endl<<ansr<<endl<<anst;
}
