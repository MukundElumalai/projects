/*
    Compass - finding the closest police stations, hotels, hospitals in coimbatore district.
*/
#include<iostream>
#include<math.h>
#include<string>
#include<fstream>
#include<stdlib.h>
#include<windows.h>
using namespace std;

struct node{
    float *data;
    string name;
    node *left,*right;
};

float euc_dist(float x[2],float y[2]){
    return pow(pow(x[0]-y[0],2)+pow(x[1]-y[1],2),0.5);
}

void nearer(float x[2],float curr[2],float newer[2],string &old,string &fresh){
    if(euc_dist(x,curr) > euc_dist(x,newer)){
        curr[0]=newer[0];
        curr[1]=newer[1];
        old=fresh;
    }
}
int accuracy;
class kdtree{
public: node *root;
        int k;
    kdtree(int x){
        root=NULL;
        k=x;
        accuracy=0;
    }
    void insertion(node **ptr,float x[2],string y,int depth=0){
        if((*ptr)==NULL){
            (*ptr)=new node;
            (*ptr)->left=(*ptr)->right=NULL;
            (*ptr)->data=new float[k];
            for(int i=0;i<k;i++)
                (*ptr)->data[i]=x[i];
            (*ptr)->name=y;
        }
        else if((*ptr)->data[depth%k]  >  x[depth%k])
            insertion(&((*ptr)->left),x,y,depth+1);
        else
            insertion(&((*ptr)->right),x,y,depth+1);
    }
    void preorder(node *ptr){
        if(ptr!=NULL){
            cout<<endl<<ptr->name;
            cout<<"("<<ptr->data[0]<<","<<ptr->data[1]<<"),";
            preorder(ptr->left);
            preorder(ptr->right);
        }
    }

    void subtree_check(node *ptr,float x[2],float ans[2],string &place){
        if(ptr!=NULL){
            nearer(x,ans,ptr->data,place,ptr->name);
            subtree_check(ptr->left,x,ans,place);
            subtree_check(ptr->right,x,ans,place);
        }
    }
    int acc;
    void NN(node *ptr,float x[2],float ans[2],string &place,int d=0){
        acc=accuracy;
        if(x[d%k] < ptr->data[d%k]){
            if(ptr->left==NULL){
                ans[0]=ptr->data[0];
                ans[1]=ptr->data[1];
                place=ptr->name;
                return;
            }
            else{
                 NN(ptr->left,x,ans,place,d+1);
            }
            if(acc>0){
                nearer(x,ans,ptr->data,place,ptr->name);
                subtree_check(ptr->right,x,ans,place);
                --acc;
            }
        }
        else{
            if(ptr->right==NULL){
                ans[0]=ptr->data[0];
                ans[1]=ptr->data[1];
                place=ptr->name;
                return;
            }
            else{
                 NN(ptr->right,x,ans,place,d+1);
            }
            if(acc>0){
                nearer(x,ans,ptr->data,place,ptr->name);
                subtree_check(ptr->left,x,ans,place);
                --acc;
            }
        }
    }
};

void arrange(float x[15][2],string y[15],int n,int depth=0){
    if(n<=1)return;
    //cout<<depth<<" ";
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(x[i][depth%2] > x[j][depth%2]){
                //cout<<"\nswap:\n"<<y[i]<<" "<<x[i][0]<<endl<<y[j]<<" "<<x[j][0];
                string t;
                t=y[i];
                y[i]=y[j];
                y[j]=t;
                float temp=x[i][0];
                x[i][0]=x[j][0];
                x[j][0]=temp;
                temp=x[i][1];
                x[i][1]=x[j][1];
                x[j][1]=temp;
    }
    string t;
    t=y[n/2];
    y[n/2]=y[0];
    y[0]=t;
    float temp=x[n/2][0];
    x[n/2][0]=x[0][0];
    x[0][0]=temp;
    temp=x[n/2][1];
    x[n/2][1]=x[0][1];
    x[0][1]=temp;
    arrange(x+1,y+1,n/2,depth+1);
    arrange(x+n/2+1,y+n/2+1,(n-1)/2,depth+1);
}
void data_Read(char *fil,float latlon[100][2],string name[100],int &n){
    ifstream f(fil);
    string trash;
    while(!f.eof()){
        getline(f,name[n]);
        f>>latlon[n][0];
        if(latlon[n][0]>500000)
            latlon[n][0]-=1000000;
        f>>latlon[n][1];
        if(latlon[n][1]>500000)
            latlon[n][1]-=1000000;
        getline(f,trash);
        n++;
    }
    f.close();
    arrange(latlon,name,n);
}

void display(float nn[2],string ans){
    cout<<"\n\t"<<ans<<"\n\t";
    if(nn[0]<0){
        nn[0]+=1000000;
        cout<<"10."<<nn[0];
    }
    else if(nn[0]>100000)
        cout<<"11."<<nn[0];
    else{
        int cnt=0,val=nn[0];
        cout<<"11.";
        while(val>0){val/=10;cnt++;}
        cnt=6-cnt;
        while(cnt!=0){cout<<"0";cnt--;}
        cout<<nn[0];
    }
    cout<<",";
    if(nn[1]<0){
        nn[1]+=1000000;
        cout<<"76."<<nn[1];
    }
    else if(nn[0]>100000)
        cout<<"77."<<nn[1];
    else{
        int cnt=0,val=nn[1];
        cout<<"77.";
        while(val>0){val/=10;cnt++;}
        cnt=6-cnt;
        while(cnt!=0){cout<<"0";cnt--;}
        cout<<nn[1];
    }
}

void convert(float a[2],string la,string lo){
    a[0]=0;
    for(int i=3;i<9;i++){
        if(i<la.length())
            a[0]=a[0]*10+(la[i]-48);
        else
            a[0]*=10;
    }
    if(a[0]>500000)a[0]-=1000000;
    a[1]=0;
    for(int i=3;i<9;i++){
        if(i<lo.length())
            a[1]=a[1]*10+(lo[i]-48);
        else
            a[1]*=10;
    }
    if(a[1]>500000)a[1]-=1000000;
}

int main(){
    kdtree PS(2),FS(2),HP(2),HT(2);
    string lat,lon,ans;
    float latlon[100][2],nn[2],a[2]={0,0};string name[100];int n=0,temp;
//creating the kd trees
    data_Read("PS.txt",latlon,name,n);
    for(int i=0;i<n;i++)
        PS.insertion(&(PS.root),latlon[i],name[i]);
    n=0;
    data_Read("FS.txt",latlon,name,n);
    for(int i=0;i<n;i++)
        FS.insertion(&(FS.root),latlon[i],name[i]);
    n=0;
    data_Read("HP.txt",latlon,name,n);
    for(int i=0;i<n;i++)
        HP.insertion(&(HP.root),latlon[i],name[i]);
    n=0;
    data_Read("HT.txt",latlon,name,n);
    for(int i=0;i<n;i++)
        HT.insertion(&(HT.root),latlon[i],name[i]);
//actual application like display
    int choice=0;
    while(choice!=7){
        system("CLS");
        cout<<"\n\t-----COMPASS-----";
        cout<<"\n\n\tACCURACY:";
        for(int i=0;i<=accuracy;i++)cout<<"*";
        cout<<"\n\n\tlat:"<<lat<<"\n\tlon:"<<lon;
        cout<<"\n\n\t1.ENTER LOCATION\n\t2.SET ACCURACY\n\t3.POLICE STATION\n\t4.FIRE STATION\n\t5.HOSPITAL\n\t6.HOTEL\n\t7.EXIT";
        cout<<"\n\n\topt: ";
        cin>>choice;
        switch(choice){
        case 1: //have to get string input and somehow convert it to our format of values
                system("CLS");
                cout<<"\n\t-----COMPASS-----";
                cout<<"\n\n\t1.HELP\n\t2.ENTER\n\n\topt: ";
                cin>>temp;
                if(temp==1){
                    system("CLS");
                    cout<<"\n\t-----COMPASS-----";
                    cout<<"\n\n\tHELP:\n\t\n\tRetrieve latitude \n\tand longitude\n\t1.Enter your address\n\t2.Choose in Maps\n\n\topt: ";
                    cin>>temp;
                    if(temp==1){
                        string url="https://www.latlong.net/convert-address-to-lat-long.html";
                        ShellExecute(NULL,"open",url.c_str(),NULL,NULL,SW_SHOWNORMAL);
                    }
                    else{
                        string url="https://www.google.com/maps";
                        ShellExecute(NULL,"open",url.c_str(),NULL,NULL,SW_SHOWNORMAL);
                    }
                }
                system("CLS");
                cout<<"\n\t-----COMPASS-----";
                cout<<"\n\n\tlatitude: ";
                cin>>lat;
                cout<<"\tlongitude: ";
                cin>>lon;
                convert(a,lat,lon);
                break;
        case 2: system("CLS");
                cout<<"\n\t-----COMPASS-----";
                cout<<"\n\n\tOLD ACCURACY: "<<accuracy+1;
                cout<<"\n\tNEW ACCURACY: ";
                cin>>accuracy;
                accuracy=(accuracy-1)%5;
                break;
        case 3:
        case 4:
        case 5:
        case 6: system("CLS");
                cout<<"\n\t-----COMPASS-----";
                cout<<"\n\n\tYour Location:";
                cout<<"\n\t"<<lat<<","<<lon;
                cout<<"\n\n\tDestination:\n\t";
                if(choice==3)
                    PS.NN(PS.root,a,nn,ans);
                else if(choice==4)
                    FS.NN(FS.root,a,nn,ans);
                else if(choice==5)
                    HP.NN(HP.root,a,nn,ans);
                else
                    HT.NN(HT.root,a,nn,ans);
                display(nn,ans);
                cout<<"\n\n\t1.Find Directions \n\t2.Back\n\n\topt: ";
                cin>>temp;
                if(temp==1){
                    system("CLS");
                    cout<<"\n\t-----COMPASS-----";
                    cout<<"\n\n\tYour Location:";
                    cout<<"\n\t"<<lat<<","<<lon;
                    cout<<"\n\n\tYour Destination:";
                    display(nn,ans);
                    cout<<"\n\n\tCopy your location\n\tand destination in\n\tthe browser";
                    Sleep(7000);
                    string url="https://www.google.com/maps";
                    ShellExecute(NULL,"open",url.c_str(),NULL,NULL,SW_SHOWNORMAL);
                    char q;
                    cout<<"\n\tenter to continue: ";
                    cin>>q;
                }
                break;
        default:break;
        }
    }
}
