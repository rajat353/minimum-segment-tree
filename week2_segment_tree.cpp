#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;


int minimum(int x, int y){return (x<y ? x:y);}

void nodeUpdate(int *tree,int arr[],int node,int value,int s,int e,int pos)
{
    if(node<s || node>e)
    {
        cout<<"\nInvalid Input\n";
        return;
    }
    if(s==e)
    {
        arr[s]+=value;
        tree[pos]+=value;
    }
    else
    {
        int mid=(s+e)/2;
        if(node>=s && node<=mid)
        {
            nodeUpdate(tree,arr,node,value,s,mid,2*pos+1);
        }
        else
        {
            nodeUpdate(tree,arr,node,value,mid+1,e,2*pos+2);
        }
        tree[pos]=minimum(tree[2*pos+1],tree[2*pos+2]);

    }
}

int rangeUpdate(int *tree,int arr[],int rs,int re,int s,int e,int pos,int val)
{
    for(int i=rs;i<=re;i++)
    {
        nodeUpdate(tree,arr,i,val,s,e,pos);
    }
}

int minQuery(int *tree,int rs, int re,int s,int e,int pos)
{
    if(rs<=s && re>= e)
    {
        return tree[pos];
    }
    else if(rs>e || re<s)
    {
        return INT_MAX;
    }
    else
    {
        int mid=(s+e)/2;
        int ltmin=minQuery(tree,rs,re,s,mid,2*pos+1);
        int rtmin=minQuery(tree,rs,re,mid+1,e,2*pos+2);
        return minimum(ltmin,rtmin);
    }
}


int construct(int arr[],int s,int e,int *tree,int index)
{
    if(s==e)
    {
        tree[index]=arr[s];
        for(int i=0;i<15;i++){cout<<" "<<tree[i];}
        cout<<endl;
        return arr[s];
    }
    int mid=(s+e)/2;
    int lt=construct(arr,s,mid,tree,2*index+1);
    int rt=construct(arr,mid+1,e,tree,2*index+2);
    tree[index]= minimum(lt,rt);
    return tree[index];
}

void print(int *tree,int arr[],int st,int sa)
{
    cout<<"\n\narray= ";
    for(int i=0;i<sa;i++){cout<<" "<<arr[i];}
    cout<<"\nTree= ";
    for(int i=0;i<st;i++){cout<<" "<<tree[i];}
}


int main()
{
    int arr[]={2,3,1,-4,-2,4,-1,5};
    int so=8,r1,r2,node,val,c=1,choice,any;
    int m=2*so-1;
    int *tree=new int[m];
    for(int i=0;i<15;i++){tree[i]=0;}
    cout<<"Construction of Segment Tree\n\n";
    construct(arr,0,so-1,tree,0);
    for(int i=0;i<m;i++){cout<<" "<<tree[i];}
    while(c)
    {
        cout<<"\n\nPress 1 for Range Minimum Query\nPress 2 to Increment a node by some value";
        cout<<"\nPress 3 to Increment a range by some value\nPress 4 to Exit";
        print(tree,arr,m,so);
        cout<<"\nEnter your choice- "; cin>>choice;
        switch(choice)
        {
            case 1: system("cls");
                    cout<<"Range Minimum Query";
                    print(tree,arr,m,so);
                    cout<<"\nEnter Range- ";
                    cin>>r1;
                    cin>>r2;
                    cout<<"\nmin value in this range= "<<minQuery(tree,r1,r2,0,so-1,0);
                    cout<<"\n\n\nPress any key to go back..."; _getch();
                    system("cls");
                    break;
            case 2: system("cls");
                    cout<<"Increment a node by some value";
                    print(tree,arr,m,so);
                    cout<<"\nUpdate node- "; cin>>node;
                    if(node>=0 && node<=so-1)
                    {
                        cout<<"value= "; cin>>val;
                        nodeUpdate(tree,arr,node,val,0,so-1,0);
                        print(tree,arr,m,so);
                        cout<<"\n\n\nPress any key to go back..."; _getch();
                        system("cls");
                        break;
                    }
                    else
                    {
                        cout<<"\n\nInvalid Node\n";
                        cout<<"\n\n\nPress any key to go back..."; _getch();
                        system("cls");
                        break;
                    }
            case 3: system("cls");
                    cout<<"Increment a range by some value";
                    print(tree,arr,m,so);
                    cout<<"\nEnter Range to update- ";
                    cin>>r1;
                    cin>>r2;
                    if(r1>=0 && r2<=so-1)
                    {
                    cout<<"value= "; cin>>val;
                    rangeUpdate(tree,arr,r1,r2,0,so-1,0,val);
                    print(tree,arr,m,so);
                    cout<<"\n\n\nPress any key to go back..."; _getch();
                    system("cls");
                    break;
                    }
                    else
                    {
                        cout<<"\n\nInvalid Range\n";
                        cout<<"\n\n\nPress any key to go back..."; _getch();
                        system("cls");
                        break;
                    }
            case 4: cout<<"\n\n\t----------EXIT----------\n\n";
                    c=0;
                    return 0;
            default:system("cls");
                    cout<<"Enter Valid Choice\n";
                    cout<<"\n\n\nPress any key to go back..."; _getch();
                    system("cls");
                     break;

        }
    }



}
